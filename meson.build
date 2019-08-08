project('hashtable-sandbox', 'c',
        default_options : [
            'warning_level=3',
            'werror=true',
            'buildtype=release',
            'strip=true',
        ],
        license : 'MIT',
        meson_version: '>= 0.47',
)

cc = meson.get_compiler('c')
configuration_inc = include_directories('src')

flags = ['-Wshadow',
      '-Wstrict-prototypes',
      '-Wmissing-prototypes',
      '-Wno-padded',
]
add_project_arguments(cc.get_supported_arguments(flags), language : 'c')

all_sources = []

subdir('src')

if get_option('tests')
    subdir('tests')
endif # get_option('tests')

#
# DEVTOOLS
#

uncrustify = find_program('uncrustify', required : false)
if uncrustify.found()
    run_target('checkstyle',
        command : [
            uncrustify,
            '-l', 'c',
            '-c', join_paths(meson.source_root(), 'devtools', 'uncrustify.cfg'),
            '--check',
            all_sources,
        ],
    )
    run_target('fixstyle',
        command : [
            uncrustify,
            '-l', 'c',
            '-c', join_paths(meson.source_root(), 'devtools', 'uncrustify.cfg'),
            '--replace',
            all_sources,
        ],
    )
endif # uncrustify

codespell = find_program('codespell', required : false)
if codespell.found()
    run_target('spelling',
        command : [
            codespell,
            all_sources,
        ]
    )
endif # codespell
