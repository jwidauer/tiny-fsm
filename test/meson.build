doctest_dep = dependency('doctest')

sources = [
    'main.cpp',
]

test_exe = executable(
    'tiny_fsm_test',
    sources,
    dependencies: [tiny_fsm_dep, doctest_dep],
)

test('tiny_fsm_test', test_exe)
