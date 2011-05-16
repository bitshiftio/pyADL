from distutils.core import setup, Extension
import sys

if(sys.platform == 'linux2'):
		extra_compile_args = ['-DLINUX']
else:
	extra_compile_args = None

setup (name = 'adl',
       version = '0.02',
       description = 'Python AMD ADL Wrapper',
       author = 'netxshare',
       url = 'http://www.bitshift.io/pyADL/',

	   	ext_modules = [
						  Extension(
									'ADL',
									extra_compile_args=extra_compile_args,
									include_dirs = ['./ADL_SDK/include/'],
									sources = ['pyADL.cpp','adl.cpp']
									)
						  ]
		   )
