cmake_minimum_required(VERSION 3.13)

project(ModelConverter)


add_executable(ModelConverter
    main.cpp
)

target_include_directories(ModelConverter PRIVATE
    # ${Boost_INCLUDE_DIR}
    C:/Source/OpenCascade/OCE-0.18/include/oce/
)

target_link_libraries(ModelConverter LINK_PUBLIC
    # ${Boost_LIBRARIES}
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/freetype.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/FWOSPlugin.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/PTKernel.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKBin.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKBinL.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKBinTObj.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKBinXCAF.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKBO.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKBool.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKBRep.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKCAF.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKCDF.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKernel.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKFeat.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKFillet.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKG2d.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKG3d.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKGeomAlgo.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKGeomBase.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKHLR.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKIGES.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKLCAF.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKMath.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKMesh.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKOffset.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKPCAF.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKPLCAF.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKPrim.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKPShape.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKService.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKShapeSchema.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKShHealing.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKStdLSchema.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKStdSchema.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKSTEP.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKSTEP209.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKSTEPAttr.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKSTEPBase.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKSTL.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKTObj.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKTopAlgo.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKV3d.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKVRML.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXCAF.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXCAFSchema.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXDEIGES.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXDESTEP.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXMesh.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXml.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXmlL.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXmlTObj.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXmlXCAF.lib
    C:/Source/OpenCascade/OCE-0.18/Win64/lib/TKXSBase.lib
    )
