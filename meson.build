project('clisp', 'c', default_options: [
  'c_std=c99',
  'buildtype=debug'])

clisp_src = files(
  'main.c'
)

mpc_inc = include_directories('extern/mpc')
mpc_dep = declare_dependency(sources: 'extern/mpc/mpc.c', include_directories: mpc_inc)

cc = meson.get_compiler('c')
readline = cc.find_library('readline')

executable('clisp',
           clisp_src,
           dependencies: [readline] + mpc_dep,
           include_directories: mpc_inc)
