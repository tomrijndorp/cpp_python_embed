cc_library(
    name = 'config',
    hdrs = ['pyconfig.h'],
    strip_include_prefix = '',
)

cc_library(
    name = 'python',
    hdrs = glob(['Include/**/*.h']),
    srcs = [ 'libpython3.8.dylib' ],
    strip_include_prefix = 'Include',
    include_prefix = '',
    deps = [':config'],
    visibility = ['//visibility:public'],
)