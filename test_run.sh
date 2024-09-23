#!/bin/sh -e

TEST_ARGS=$@

exec_test()
{
    TARGET=$1
    cd tests/${TARGET}
    rm -rf build/CMakeFiles/app.dir/src/*.gc* build/CMakeFiles/app.dir/runner/*.gc*
    west build -b native_sim_64 -t run ${TEST_ARGS}
    cnt=`find build/CMakeFiles/app.dir/src -name "*.gcno" | wc -l`
    if [ $cnt -ne 0 ]; then
      lcov --capture --directory build/CMakeFiles/app.dir/src/ --output-file build/lcov.info > /dev/null 2>&1
      genhtml build/lcov.info --output-directory build/lcov-output --show-details --legend > /dev/null 2>&1
      echo "\n======\nCOVERAGE: tests/${TARGET}/build/lcov-output/index.html\n=====\n"
    fi
    cd ..
}

exec_test led
