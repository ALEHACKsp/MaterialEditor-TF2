#pragma once
#include "../MaterialSystem/MaterialSystem.h"

struct mstudioanimdesc_t;
struct mstudioseqdesc_t;
struct model_t;
class IClientRenderable;
class Vector;
struct studiohdr_t;
class IMaterial;
class CStudioHdr;
struct studiohwdata_t;
using StudioDecalHandle_t = void *;
using QAngle = Vector;
using LightCacheHandle_t = void *;
class Ray_t;
class ColorMeshInfo_t;
class LightDesc_t {};

struct DrawModelState_t
{
	studiohdr_t *m_pStudioHdr;
	studiohwdata_t *m_pStudioHWData;
	IClientRenderable *m_pRenderable;
	const matrix3x4 *m_pModelToWorld;
	StudioDecalHandle_t	m_decals;
	int m_drawFlags;
	int m_lod;
};

typedef unsigned short ModelInstanceHandle_t;

enum
{
	MODEL_INSTANCE_INVALID = (ModelInstanceHandle_t)~0
};

struct ModelRenderInfo_t
{
	Vector origin;
	QAngle angles;
	IClientRenderable *pRenderable;
	const model_t *pModel;
	const matrix3x4 *pModelToWorld;
	const matrix3x4 *pLightingOffset;
	const Vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;
};

struct StaticPropRenderInfo_t
{
	const matrix3x4 *pModelToWorld;
	const model_t *pModel;
	IClientRenderable *pRenderable;
	Vector *pLightingOrigin;
	short skin;
	ModelInstanceHandle_t instance;
};

enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};

enum
{
	ADDDECAL_TO_ALL_LODS = -1
};

struct DrawModelInfo_t
{
	studiohdr_t *m_pStudioHdr;
	studiohwdata_t *m_pHardwareData;
	StudioDecalHandle_t m_Decals;
	int				m_Skin;
	int				m_Body;
	int				m_HitboxSet;
	void *m_pClientEntity;
	int				m_Lod;
	ColorMeshInfo_t *m_pColorMeshes;
	bool			m_bStaticLighting;
	Vector			m_vecAmbientCube[6];
	int				m_nLocalLightCount;
	LightDesc_t		m_LocalLightDescs[4];
};

class IVModelRender
{
public:
	virtual int	DrawModel(int flags,
		IClientRenderable *pRenderable,
		ModelInstanceHandle_t instance,
		int entity_index,
		const model_t *model,
		Vector const &origin,
		QAngle const &angles,
		int skin,
		int body,
		int hitboxset,
		const matrix3x4 *modelToWorld = NULL,
		const matrix3x4 *pLightingOffset = NULL) = 0;

	virtual void ForcedMaterialOverride(IMaterial *newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL) = 0;
	virtual void SetViewTarget(const CStudioHdr *pStudioHdr, int nBodyIndex, const Vector &target) = 0;
	virtual ModelInstanceHandle_t CreateInstance(IClientRenderable *pRenderable, LightCacheHandle_t *pCache = NULL) = 0;
	virtual void DestroyInstance(ModelInstanceHandle_t handle) = 0;
	virtual void SetStaticLighting(ModelInstanceHandle_t handle, LightCacheHandle_t *pHandle) = 0;
	virtual LightCacheHandle_t GetStaticLighting(ModelInstanceHandle_t handle) = 0;
	virtual bool ChangeInstance(ModelInstanceHandle_t handle, IClientRenderable *pRenderable) = 0;
	virtual void AddDecal(ModelInstanceHandle_t handle, Ray_t const &ray, Vector const &decalUp, int decalIndex, int body, bool noPokeThru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS) = 0;
	virtual void RemoveAllDecals(ModelInstanceHandle_t handle) = 0;
	virtual void RemoveAllDecalsFromAllModels() = 0;
	virtual matrix3x4 *DrawModelShadowSetup(IClientRenderable *pRenderable, int body, int skin, DrawModelInfo_t *pInfo, matrix3x4 *pCustomBoneToWorld = NULL) = 0;
	virtual void DrawModelShadow(IClientRenderable *pRenderable, const DrawModelInfo_t &info, matrix3x4 *pCustomBoneToWorld = NULL) = 0;
	virtual bool RecomputeStaticLighting(ModelInstanceHandle_t handle) = 0;
	virtual void ReleaseAllStaticPropColorData(void) = 0;
	virtual void RestoreAllStaticPropColorData(void) = 0;
	virtual int	DrawModelEx(ModelRenderInfo_t &pInfo) = 0;
	virtual int	DrawModelExStaticProp(ModelRenderInfo_t &pInfo) = 0;
	virtual bool DrawModelSetup(ModelRenderInfo_t &pInfo, DrawModelState_t *pState, matrix3x4 *pCustomBoneToWorld, matrix3x4 **ppBoneToWorldOut) = 0;
	virtual void DrawModelExecute(const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld = NULL) = 0;
	virtual void SetupLighting(const Vector &vecCenter) = 0;
	virtual int DrawStaticPropArrayFast(StaticPropRenderInfo_t *pProps, int count, bool bShadowDepth) = 0;
	virtual void SuppressEngineLighting(bool bSuppress) = 0;
	virtual void SetupColorMeshes(int nTotalVerts) = 0;
	virtual void AddColoredDecal(ModelInstanceHandle_t handle, Ray_t const &ray, Vector const &decalUp, int decalIndex, int body, Color_t cColor, bool noPokeThru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS) = 0;
	virtual void GetMaterialOverride(IMaterial **ppOutForcedMaterial, OverrideType_t *pOutOverrideType) = 0;
};

inline IVModelRender *g_pModelRender;