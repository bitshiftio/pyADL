import sys
from distutils.core import setup, Extension
if(sys.platform == 'linux2'):
		extra_compile_args = ['-DLINUX']
else:
	extra_compile_args = None

setup (name = 'pyADL',
       version = '0.01',
       description = 'Python AMD ADL Wrapper',
       author = 'netxshare',
       url = 'http://www.bitshift.io',

	   	ext_modules = [
						  Extension(
									'pyADL',
									extra_compile_args=extra_compile_args,
									include_dirs = ['./ADL_SDK/include/'],
									sources = ['pyADL.cpp','adl.cpp']
									)
						  ]
		   )
