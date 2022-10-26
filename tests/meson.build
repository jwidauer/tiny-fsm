doctest_dep = dependency('doctest')

test_src = ['main.cpp', 'state_machine_test.cpp']

test_exe = executable(
    'unit_tests',
    test_src,
    dependencies: [doctest_dep, tiny_fsm_dep],
)

test('unit_tests', test_exe)
