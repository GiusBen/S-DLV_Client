# IMPORTANT
#
# This file is included in the top level CMakeLists.txt and
# it's where you're supposed to set up those variables used
# throughout the whole project. The idea is to have them all
# listed in this single file, so after editing these paths
# according to your needs you should be ready to build without
# touching any other cmake files.
# Hopefully.

# pugixml 1.7 root library
set(PUGIXML_DIR "")

# pugixml 1.7 header files directory (e.g. "${PUGIXML_DIR}/src")
set(PUGIXML_HDR "")

# pugixml 1.7 library - you can either build it yourself and
# link against it (e.g. "${PUGIXML_DIR}/lib/libpugixml.a") or
# simply compile pugi's header files along with your sources
set(PUGIXML_LIB "")