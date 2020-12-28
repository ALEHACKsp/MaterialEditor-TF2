#pragma once
#include <cstdint>
#include "../Utils/Utils.h"

typedef uint64_t VertexFormat_t;
typedef uint32_t MorphFormat_t;
class ITexture;
class IMaterial;

using matrix3x4 = float[3][4];

class VMatrix
{
private:
	Vector m[4][4];

public:
	const matrix3x4 &As3x4() const {
		return *((const matrix3x4 *)this);
	}
};

class Vector4D {
	float x, y, z, w;
};

enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_NV_DST16,
	IMAGE_FORMAT_NV_DST24,
	IMAGE_FORMAT_NV_INTZ,
	IMAGE_FORMAT_NV_RAWZ,
	IMAGE_FORMAT_ATI_DST16,
	IMAGE_FORMAT_ATI_DST24,
	IMAGE_FORMAT_NV_NULL,
	IMAGE_FORMAT_ATI2N,
	IMAGE_FORMAT_ATI1N,
	IMAGE_FORMAT_DXT1_RUNTIME,
	IMAGE_FORMAT_DXT5_RUNTIME,
	NUM_IMAGE_FORMATS
};

enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};

enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,
	MATERIAL_PROPERTY_OPACITY,
	MATERIAL_PROPERTY_REFLECTIVITY,
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS
};

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_IGNORE_ALPHA_MODULATION = (1 << 30),
};

enum MaterialVarType_t
{
	MATERIAL_VAR_TYPE_FLOAT = 0,
	MATERIAL_VAR_TYPE_STRING,
	MATERIAL_VAR_TYPE_VECTOR,
	MATERIAL_VAR_TYPE_TEXTURE,
	MATERIAL_VAR_TYPE_INT,
	MATERIAL_VAR_TYPE_FOURCC,
	MATERIAL_VAR_TYPE_UNDEFINED,
	MATERIAL_VAR_TYPE_MATRIX,
	MATERIAL_VAR_TYPE_MATERIAL,
};

typedef unsigned short MaterialVarSym_t;

class IMaterialVar
{
public:
	typedef unsigned long FourCC;

	char *m_pStringVal;
	int m_intVal;
	Vector4D m_VecVal;

	uint8_t m_Type;
	uint8_t m_nNumVectorComps;
	uint8_t m_bFakeMaterialVar;
	uint8_t m_nTempIndex;
	//CUtlSymbol m_Name;

public:
	virtual ITexture			*GetTextureValue(void) = 0;
	virtual char const			*GetName(void) const = 0;
	virtual MaterialVarSym_t	GetNameAsSymbol() const = 0;
	virtual void				SetFloatValue(float val) = 0;
	virtual void				SetIntValue(int val) = 0;
	virtual void				SetStringValue(char const *val) = 0;
	virtual char const			*GetStringValue(void) const = 0;
	virtual void				SetFourCCValue(FourCC type, void *pData) = 0;
	virtual void				GetFourCCValue(FourCC *type, void **ppData) = 0;
	virtual void				SetVecValue(float const *val, int numcomps) = 0;
	virtual void				SetVecValue(float x, float y) = 0;
	virtual void				SetVecValue(float x, float y, float z) = 0;
	virtual void				SetVecValue(float x, float y, float z, float w) = 0;
	virtual void				GetLinearVecValue(float *val, int numcomps) const = 0;
	virtual void				SetTextureValue(ITexture *) = 0;
	virtual IMaterial			*GetMaterialValue(void) = 0;
	virtual void				SetMaterialValue(IMaterial *) = 0;
	virtual bool				IsDefined() const = 0;
	virtual void				SetUndefined() = 0;
	virtual void				SetMatrixValue(VMatrix const &matrix) = 0;
	virtual const				VMatrix &GetMatrixValue() = 0;
	virtual bool				MatrixIsIdentity() const = 0;
	virtual void				CopyFrom(IMaterialVar *pMaterialVar) = 0;
	virtual void				SetValueAutodetectType(char const *val) = 0;
	virtual IMaterial			*GetOwningMaterial() = 0;
	virtual void				SetVecComponentValue(float fVal, int nComponent) = 0;
	virtual int					GetIntValueInternal(void) const = 0;
	virtual float				GetFloatValueInternal(void) const = 0;
	virtual float const			*GetVecValueInternal() const = 0;
	virtual void				GetVecValueInternal(float *val, int numcomps) const = 0;
	virtual int					VectorSizeInternal() const = 0;
};

class IMaterial
{
public:
	virtual const char				*GetName() const = 0;
	virtual const char				*GetTextureGroupName() const = 0;
	virtual PreviewImageRetVal_t	GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool *isTranslucent) const = 0;
	virtual PreviewImageRetVal_t	GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0;
	virtual int						GetMappingWidth() = 0;
	virtual int						GetMappingHeight() = 0;
	virtual int						GetNumAnimationFrames() = 0;
	virtual bool					InMaterialPage(void) = 0;
	virtual	void					GetMaterialOffset(float *pOffset) = 0;
	virtual void					GetMaterialScale(float *pScale) = 0;
	virtual IMaterial				*GetMaterialPage(void) = 0;
	virtual IMaterialVar			*FindVar(const char *varName, bool *found, bool complain = true) = 0;
	virtual void					IncrementReferenceCount(void) = 0;
	virtual void					DecrementReferenceCount(void) = 0;
	virtual int 					GetEnumerationID(void) const = 0;
	virtual void					GetLowResColorSample(float s, float t, float *color) const = 0;
	virtual void					RecomputeStateSnapshots() = 0;
	virtual bool					IsTranslucent() = 0;
	virtual bool					IsAlphaTested() = 0;
	virtual bool					IsVertexLit() = 0;
	virtual VertexFormat_t			GetVertexFormat() const = 0;
	virtual bool					HasProxy(void) const = 0;
	virtual bool					UsesEnvCubemap(void) = 0;
	virtual bool					NeedsTangentSpace(void) = 0;
	virtual bool					NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool					NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool					NeedsSoftwareSkinning(void) = 0;
	virtual void					AlphaModulate(float alpha) = 0;
	virtual void					ColorModulate(float r, float g, float b) = 0;
	virtual void					SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool					GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;
	virtual void					GetReflectivity(Vector &reflect) = 0;
	virtual bool					GetPropertyFlag(MaterialPropertyTypes_t type) = 0;
	virtual bool					IsTwoSided() = 0;
	virtual void					SetShader(const char *pShaderName) = 0;
	virtual int						GetNumPasses(void) = 0;
	virtual int						GetTextureMemoryBytes(void) = 0;
	virtual void					Refresh() = 0;
	virtual bool					NeedsLightmapBlendAlpha(void) = 0;
	virtual bool					NeedsSoftwareLighting(void) = 0;
	virtual int						ShaderParamCount() const = 0;
	virtual IMaterialVar			**GetShaderParams(void) = 0;
	virtual bool					IsErrorMaterial() const = 0;
	virtual void					SetUseFixedFunctionBakedLighting(bool bEnable) = 0;
	virtual float					GetAlphaModulation() = 0;
	virtual void					GetColorModulation(float *r, float *g, float *b) = 0;
	virtual MorphFormat_t			GetMorphFormat() const = 0;
};