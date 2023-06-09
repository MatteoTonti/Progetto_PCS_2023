add_test([=[TestConstructors.TestVertex]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestConstructors.TestVertex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestConstructors.TestVertex]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestConstructors.TestEdge]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestConstructors.TestEdge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestConstructors.TestEdge]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestConstructors.TestTriangle]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestConstructors.TestTriangle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestConstructors.TestTriangle]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestSorting.TestHeapSort]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestSorting.TestHeapSort]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestSorting.TestHeapSort]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestSorting.TestInsertion]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestSorting.TestInsertion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestSorting.TestInsertion]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestImport.TestVertices]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestImport.TestVertices]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestImport.TestVertices]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestImport.TestEdges]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestImport.TestEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestImport.TestEdges]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestImport.TestTriangles]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestImport.TestTriangles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestImport.TestTriangles]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[TestRefine.TestBisect]=]  C:/Users/matte/Desktop/Progetto_PCS/Projects/Release/raffinamento_test.exe [==[--gtest_filter=TestRefine.TestBisect]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestRefine.TestBisect]=]  PROPERTIES WORKING_DIRECTORY C:/Users/matte/Desktop/Progetto_PCS/Projects/Release SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  raffinamento_test_TESTS TestConstructors.TestVertex TestConstructors.TestEdge TestConstructors.TestTriangle TestSorting.TestHeapSort TestSorting.TestInsertion TestImport.TestVertices TestImport.TestEdges TestImport.TestTriangles TestRefine.TestBisect)