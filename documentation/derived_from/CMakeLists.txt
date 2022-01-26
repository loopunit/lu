project(derived_from)

include(ExternalProject)

# Index of any 3rd party project that this project is derived from in any way

ExternalProject_Add(gsl-lite
  GIT_REPOSITORY    https://github.com/gsl-lite/gsl-lite.git
  GIT_TAG           4b5e9ab7474841fc2d7efc2e0064ef81785535d1
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/gsl-lite"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/gsl-lite"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(jfalcou_spy
  GIT_REPOSITORY    https://github.com/jfalcou/spy.git
  GIT_TAG           fb0eb880ebbd15b43e04067398feca4be805e798
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/jfalcou_spy"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/jfalcou_spy"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(boost_ext_di
  GIT_REPOSITORY    https://github.com/boost-ext/di.git
  GIT_TAG           48eccb76aee03f0eceafe9bf47a713a8c0e7d810
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/boost_ext_di"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/boost_ext_di"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(boost_ext_sml
  GIT_REPOSITORY    https://github.com/boost-ext/sml.git
  GIT_TAG           767ea7f3e255e43293560c4d629c50b0115c806e
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/boost_ext_sml"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/boost_ext_sml"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(boost_ext_ut
  GIT_REPOSITORY    https://github.com/boost-ext/ut.git
  GIT_TAG           5fbda77ebd30bad7f2d696dad5a8e46470b82275
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/boost_ext_ut"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/boost_ext_ut"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(boost_ext_te
  GIT_REPOSITORY    https://github.com/boost-ext/te.git
  GIT_TAG           f18e0a3462575b5159c43d5a54023ea72461f4bc
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/boost_ext_te"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/boost_ext_te"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(foonathan_type_safe
  GIT_REPOSITORY    https://github.com/foonathan/type_safe.git
  GIT_TAG           2809f17824e1c6b61aa710015bba73e3d0b26728
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/foonathan_type_safe"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/foonathan_type_safe"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(foonathan_memory
  GIT_REPOSITORY    https://github.com/foonathan/memory.git
  GIT_TAG           37e0a7e92344bd1c710a9f12c9054494ecaaa76c
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/foonathan_memory"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/foonathan_memory"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(foonathan_atum
  GIT_REPOSITORY    https://github.com/foonathan/atum.git
  GIT_TAG           c546d09fcd66b249aeed05918939f307fe074878
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/foonathan_atum"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/foonathan_atum"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(thpatch_win32_utf8
  GIT_REPOSITORY    https://github.com/thpatch/win32_utf8.git
  GIT_TAG           2103997ef3acf595ba7f560ef473f72275f58756
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/thpatch_win32_utf8"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/thpatch_win32_utf8"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(DuffsDevice_tiny_utf8
  GIT_REPOSITORY    https://github.com/DuffsDevice/tiny-utf8.git
  GIT_TAG           a71a1c4c681ed1eb178db641b3e1bc6298bb2327
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/DuffsDevice_tiny_utf8"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/DuffsDevice_tiny_utf8"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(giacomodrago_fcmm
  GIT_REPOSITORY    https://github.com/giacomodrago/fcmm.git
  GIT_TAG           a074dc72cf368bd611c0d1476a1ba0b451f26bfe
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/giacomodrago_fcmm"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/giacomodrago_fcmm"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(mattreecebentley_plf_colony
  GIT_REPOSITORY    https://github.com/mattreecebentley/plf_colony.git
  GIT_TAG           7243b4601b5d7e989550c158a9918ea5a05feaf4
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/mattreecebentley_plf_colony"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/mattreecebentley_plf_colony"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(martinus_robin-hood-hashing
  GIT_REPOSITORY    https://github.com/martinus/robin-hood-hashing.git
  GIT_TAG           9145f963d80d6a02f0f96a47758050a89184a3ed
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/martinus_robin-hood-hashing"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/martinus_robin-hood-hashing"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(digint_tinyfsm
  GIT_REPOSITORY    https://github.com/digint/tinyfsm.git
  GIT_TAG           be0823aaceafbf01b3e82c70754a4f53b855dddb
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/digint_tinyfsm"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/digint_tinyfsm"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(p-ranav_glob
  GIT_REPOSITORY    https://github.com/p-ranav/glob.git
  GIT_TAG           c2ac194335ddbb72f373cce0b34f221e78579b16
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/p-ranav_glob"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/p-ranav_glob"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(cameron314_readerwriterqueue
  GIT_REPOSITORY    https://github.com/cameron314/readerwriterqueue.git
  GIT_TAG           8e7627d18c2108aca178888d88514179899a044f
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/cameron314_readerwriterqueue"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/cameron314_readerwriterqueue"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(cameron314_concurrentqueue
  GIT_REPOSITORY    https://github.com/cameron314/concurrentqueue.git
  GIT_TAG           38e6a6f0185a98c3aaf2a95aa109ba041221d527
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/cameron314_concurrentqueue"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/cameron314_concurrentqueue"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(marzer_tomlplusplus
  GIT_REPOSITORY    https://github.com/marzer/tomlplusplus.git
  GIT_TAG           8e669aa6990e0ed219c169d491472d749f54c393
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/marzer_tomlplusplus"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/marzer_tomlplusplus"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(eyalz800_zpp_bits
  GIT_REPOSITORY    https://github.com/eyalz800/zpp_bits.git
  GIT_TAG           6ad5505eaf91f36aafdb2d405c49c20897a201a1
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/eyalz800_zpp_bits"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/eyalz800_zpp_bits"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(gvinciguerra_PGM-index
  GIT_REPOSITORY    https://github.com/gvinciguerra/PGM-index.git
  GIT_TAG           aac467887be5ba354ea2d23f7bc51f6e212f0f04
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/gvinciguerra_PGM-index"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/gvinciguerra_PGM-index"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(yhirose_cpp-fstlib
  GIT_REPOSITORY    https://github.com/yhirose/cpp-fstlib.git
  GIT_TAG           4b2c3b2b9398d28b70492e97f8295f31424e7be1
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/yhirose_cpp-fstlib"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/yhirose_cpp-fstlib"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(DeveloperPaul123_eventbus
  GIT_REPOSITORY    https://github.com/DeveloperPaul123/eventbus.git
  GIT_TAG           275e0cff588c1d89bb148c30c1f4d8c10f179f34
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/DeveloperPaul123_eventbus"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/DeveloperPaul123_eventbus"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(gabime_spdlog
  GIT_REPOSITORY    https://github.com/gabime/spdlog.git
  GIT_TAG           2382c87aa30277e11b21a50c2fef6f7f891e8fc0
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/gabime_spdlog"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/gabime_spdlog"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(nlohmann_json
  GIT_REPOSITORY    https://github.com/nlohmann/json.git
  GIT_TAG           293f67f9ff1a3c7d16cf0959c95761e89b9b64e9
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/nlohmann_json"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/nlohmann_json"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(taskflow_taskflow
  GIT_REPOSITORY    https://github.com/taskflow/taskflow.git
  GIT_TAG           a7ffe9a4114dafc6a977cb74c1005f15bb57e62b
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/taskflow_taskflow"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/taskflow_taskflow"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(Neargye_magic_enum
  GIT_REPOSITORY    https://github.com/Neargye/magic_enum.git
  GIT_TAG           4ed0b743e85c263b2002db82ff24e9559ff890aa
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/Neargye_magic_enum"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/Neargye_magic_enum"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(gulrak_filesystem
  GIT_REPOSITORY    https://github.com/gulrak/filesystem.git
  GIT_TAG           f437344e7945e343d86fcf97c84e815b03c6851f
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/gulrak_filesystem"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/gulrak_filesystem"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(bombela_backward-cpp
  GIT_REPOSITORY    https://github.com/bombela/backward-cpp.git
  GIT_TAG           5ffb2c879ebdbea3bdb8477c671e32b1c984beaa
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/bombela_backward-cpp"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/bombela_backward-cpp"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(ocornut_imgui
  GIT_REPOSITORY    https://github.com/ocornut/imgui.git
  GIT_TAG           3e0d6ec895483e33a663d3cfc1c58f1cafbe978c
  SOURCE_DIR        "${CMAKE_CURRENT_LIST_DIR}/ocornut_imgui"
  BINARY_DIR        "${CMAKE_CURRENT_LIST_DIR}/ocornut_imgui"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

