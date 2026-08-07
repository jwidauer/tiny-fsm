
inc_dir = include_directories('.')

# Make this library usable from the system's
# package manager.
headers = [
    'tiny-fsm/actions/by_default.hpp',
    'tiny-fsm/actions/invoke_callback.hpp',
    'tiny-fsm/actions/maybe.hpp',
    'tiny-fsm/actions/nothing.hpp',
    'tiny-fsm/actions/on.hpp',
    'tiny-fsm/actions/one_of.hpp',
    'tiny-fsm/actions/transition_to.hpp',
    'tiny-fsm/actions/utils.hpp',
    'tiny-fsm/actions/will.hpp',
    'tiny-fsm/actions.hpp',
    'tiny-fsm/state_machine.hpp',
    'tiny-fsm/types/types.hpp',
    'tiny-fsm/types/utils.hpp',
    'tiny-fsm/utils/array_utils.hpp',
    'tiny-fsm/utils/static_string.hpp',
]

install_headers(headers, preserve_path: true)

# Make this library usable as a Meson subproject.
tiny_fsm_dep = declare_dependency(include_directories: inc_dir)
