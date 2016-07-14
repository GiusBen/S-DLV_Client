# IMPORTANT
#
# This file is included in the top level CMakeLists.txt and
# it's where you're supposed to set up those variables used
# throughout the whole project. The idea is to have them all
# listed in this single file, so after editing these paths
# according to your needs you should be ready to build without
# touching any other cmake files.

set(PUGIXML_DIR "/usr/local/lib/pugixml-1.7")
set(PUGIXML_HDR "${PUGIXML_DIR}/src")
set(PUGIXML_LIB "${PUGIXML_DIR}/lib/libpugixml_1_7.a")