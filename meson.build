project(
    'tiny-fsm',
    'cpp',
    version: '1.0.0',
    default_options: [
        'cpp_std=c++17',
        'warning_level=3',
        'werror=true',
    ],
)

subdir('include')

tiny_fsm_dep = declare_dependency(
    include_directories: include_directories('include'),
)

subdir('examples')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
    name: 'tiny-fsm',
    description: 'A tiny finite state machine library for C++17',
    version: meson.project_version(),
    libraries: tiny_fsm_dep,
)
