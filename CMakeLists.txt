cmake_minimum_required(VERSION 3.15)

project(ModelConverter)


add_executable(ModelConverter
    main.cpp
)

target_include_directories(ModelConverter PRIVATE
    # ${Boost_INCLUDE_DIR}
    d:/dev/OCE-0.18/include/oce/
)

target_link_libraries(ModelConverter LINK_PUBLIC
    # ${Boost_LIBRARIES}
    d:/dev/OCE-0.18/Win64/lib/freetype.lib
    d:/dev/OCE-0.18/Win64/lib/FWOSPlugin.lib
    d:/dev/OCE-0.18/Win64/lib/PTKernel.lib
    d:/dev/OCE-0.18/Win64/lib/TKBin.lib
    d:/dev/OCE-0.18/Win64/lib/TKBinL.lib
    d:/dev/OCE-0.18/Win64/lib/TKBinTObj.lib
    d:/dev/OCE-0.18/Win64/lib/TKBinXCAF.lib
    d:/dev/OCE-0.18/Win64/lib/TKBO.lib
    d:/dev/OCE-0.18/Win64/lib/TKBool.lib
    d:/dev/OCE-0.18/Win64/lib/TKBRep.lib
    d:/dev/OCE-0.18/Win64/lib/TKCAF.lib
    d:/dev/OCE-0.18/Win64/lib/TKCDF.lib
    d:/dev/OCE-0.18/Win64/lib/TKernel.lib
    d:/dev/OCE-0.18/Win64/lib/TKFeat.lib
    d:/dev/OCE-0.18/Win64/lib/TKFillet.lib
    d:/dev/OCE-0.18/Win64/lib/TKG2d.lib
    d:/dev/OCE-0.18/Win64/lib/TKG3d.lib
    d:/dev/OCE-0.18/Win64/lib/TKGeomAlgo.lib
    d:/dev/OCE-0.18/Win64/lib/TKGeomBase.lib
    d:/dev/OCE-0.18/Win64/lib/TKHLR.lib
    d:/dev/OCE-0.18/Win64/lib/TKIGES.lib
    d:/dev/OCE-0.18/Win64/lib/TKLCAF.lib
    d:/dev/OCE-0.18/Win64/lib/TKMath.lib
    d:/dev/OCE-0.18/Win64/lib/TKMesh.lib
    d:/dev/OCE-0.18/Win64/lib/TKOffset.lib
    d:/dev/OCE-0.18/Win64/lib/TKPCAF.lib
    d:/dev/OCE-0.18/Win64/lib/TKPLCAF.lib
    d:/dev/OCE-0.18/Win64/lib/TKPrim.lib
    d:/dev/OCE-0.18/Win64/lib/TKPShape.lib
    d:/dev/OCE-0.18/Win64/lib/TKService.lib
    d:/dev/OCE-0.18/Win64/lib/TKShapeSchema.lib
    d:/dev/OCE-0.18/Win64/lib/TKShHealing.lib
    d:/dev/OCE-0.18/Win64/lib/TKStdLSchema.lib
    d:/dev/OCE-0.18/Win64/lib/TKStdSchema.lib
    d:/dev/OCE-0.18/Win64/lib/TKSTEP.lib
    d:/dev/OCE-0.18/Win64/lib/TKSTEP209.lib
    d:/dev/OCE-0.18/Win64/lib/TKSTEPAttr.lib
    d:/dev/OCE-0.18/Win64/lib/TKSTEPBase.lib
    d:/dev/OCE-0.18/Win64/lib/TKSTL.lib
    d:/dev/OCE-0.18/Win64/lib/TKTObj.lib
    d:/dev/OCE-0.18/Win64/lib/TKTopAlgo.lib
    d:/dev/OCE-0.18/Win64/lib/TKV3d.lib
    d:/dev/OCE-0.18/Win64/lib/TKVRML.lib
    d:/dev/OCE-0.18/Win64/lib/TKXCAF.lib
    d:/dev/OCE-0.18/Win64/lib/TKXCAFSchema.lib
    d:/dev/OCE-0.18/Win64/lib/TKXDEIGES.lib
    d:/dev/OCE-0.18/Win64/lib/TKXDESTEP.lib
    d:/dev/OCE-0.18/Win64/lib/TKXMesh.lib
    d:/dev/OCE-0.18/Win64/lib/TKXml.lib
    d:/dev/OCE-0.18/Win64/lib/TKXmlL.lib
    d:/dev/OCE-0.18/Win64/lib/TKXmlTObj.lib
    d:/dev/OCE-0.18/Win64/lib/TKXmlXCAF.lib
    d:/dev/OCE-0.18/Win64/lib/TKXSBase.lib
    )
