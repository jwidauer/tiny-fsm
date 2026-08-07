project(
    'tiny-fsm',
    'cpp',
    license: 'MIT',
    license_files: ['LICENSE'],
    version: configure_file(
        input: 'version',
        output: 'VERSION',
        copy: true,
    ),
    default_options: ['warning_level=3', 'cpp_std=c++17'],
)

# Add include directory with public headers
subdir('include')

# Add test directory with tests
subdir('test')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
    name: meson.project_name(),
    filebase: meson.project_name(),
    description: 'Tiny, but powerful, Finite State Machine for C++17',
    subdirs: meson.project_name(),
    version: meson.project_version(),
)
