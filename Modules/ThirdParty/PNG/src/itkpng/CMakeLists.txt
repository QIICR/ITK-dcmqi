project(ITK3P_PNG)
include_regular_expression("^(png|itk|z).*$")

include_directories(${ITK3P_PNG_SOURCE_DIR} ${ITK3P_PNG_BINARY_DIR})

# source files for png
set(PNG_SRCS
pngget.c    pngrio.c    pngwrite.c
png.c       pngmem.c    pngrtran.c  pngtrans.c  pngwtran.c
pngerror.c  pngpread.c  pngrutil.c  pngwutil.c
pngread.c   pngset.c   pngwio.c
)

# Kitware: added `OR APPLE` to allow Universal Binary builds on Intel Macs.
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "(arm|aarch64)" OR APPLE)
  list(APPEND PNG_SRCS
    arm/arm_init.c
    arm/filter_neon_intrinsics.c
    arm/palette_neon_intrinsics.c)
endif()

if(WIN32)
  if(BUILD_SHARED_LIBS)
    add_definitions(-DPNG_BUILD_DLL)
  else(BUILD_SHARED_LIBS)
    set(PNG_STATIC 1)
  endif(BUILD_SHARED_LIBS)
endif(WIN32)

configure_file(${ITK3P_PNG_SOURCE_DIR}/pngDllConfig.h.in
               ${ITK3P_PNG_BINARY_DIR}/pngDllConfig.h)

set(MANGLE_PREFIX slicer_itk)
configure_file(${ITK3P_PNG_SOURCE_DIR}/itk_png_mangle.h.in
               ${ITK3P_PNG_BINARY_DIR}/itk_png_mangle.h
               @ONLY)

add_library(itkpng ${PNG_SRCS})
target_link_libraries(itkpng ${ITKZLIB_LIBRARIES})

target_include_directories(itkpng
  INTERFACE "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${ITK3P_INSTALL_INCLUDE_DIR}/itkpng>;$<BUILD_INTERFACE:${ITK3P_PNG_BINARY_DIR}>"
)

# Apply user-defined properties to the library target.
if(ITK_LIBRARY_PROPERTIES)
  set_target_properties(itkpng PROPERTIES ${ITK_LIBRARY_PROPERTIES})
endif(ITK_LIBRARY_PROPERTIES)

install(TARGETS itkpng
  EXPORT ${ITK3P_INSTALL_EXPORT_NAME}
  RUNTIME DESTINATION ${ITK3P_INSTALL_RUNTIME_DIR} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${ITK3P_INSTALL_LIBRARY_DIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${ITK3P_INSTALL_ARCHIVE_DIR} COMPONENT Development
  )

install(FILES
  ${ITK3P_PNG_BINARY_DIR}/pngDllConfig.h
  ${ITK3P_PNG_SOURCE_DIR}/png.h
  ${ITK3P_PNG_SOURCE_DIR}/pngconf.h
  ${ITK3P_PNG_BINARY_DIR}/itk_png_mangle.h
  DESTINATION ${ITK3P_INSTALL_INCLUDE_DIR}/itkpng # itk_png.h #include "itkpng/png.h"
  COMPONENT Development)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-cast-qual")
endif(CMAKE_COMPILER_IS_GNUCC)
