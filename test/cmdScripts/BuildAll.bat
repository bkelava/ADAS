cd C:\VISION_SDK_02_12_01_00\ti_components\networking\nsp_gmacsw_4_15_00_00
xdc --xdcpath="C:/VISION_SDK_02_12_01_00/ti_components/os_tools/bios_6_46_00_23/packages" -P packages/ti/nsp/drv/
cd C:\VISION_SDK_02_12_01_00\vision_sdk
gmake -s -j depend
gmake -s -j sbl_sd
gmake -s -j
gmake -s -j appimage