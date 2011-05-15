from distutils.core import setup, Extension

setup (name = 'pyADL',
       version = '0.01',
       description = 'Python AMD ADL Wrapper',
       author = 'netxshare',
       url = 'http://www.bitshift.io',

       ext_modules = [
                      Extension(
                                'pyADL',
                                sources = ['pyADL.cpp','adl.cpp']
                                )
                      ]
       )
