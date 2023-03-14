import os
import sys
import pathlib
import glob
import shutil
import setuptools

from setuptools.dist import Distribution
from setuptools.command.install import install
from wheel.bdist_wheel import bdist_wheel, get_platform

project_name = "Skaia"

class BinaryDistribution(Distribution):
    def has_ext_modules(self):
        return True


class BinaryDistWheel(bdist_wheel):
    def finalize_options(self):
        bdist_wheel.finalize_options(self)


class InstallPlatformLibrary(install):
    def finalize_options(self):
        install.finalize_options(self)
        if self.distribution.has_ext_modules():
            self.install_lib = self.install_platlib

setuptools.setup(
    name=project_name,
    version="0.1",
    author="Rehan Ali",
    author_email="rsa165.ali@gmail.com",
    description="Python bindings for the game engine Skaia",
    url="https://github.com/rsa16/Skaia",
    packages=setuptools.find_packages(".", exclude=["examples"]),
    include_package_data=True,
    distclass=BinaryDistribution,
    cmdclass={
        "install": InstallPlatformLibrary
    },
    zip_safe=False,
    platforms=[ "macosx", "win32", "linux" ],
    python_requires=">=3.7",
    setup_requires=[ "wheel" ],
    install_requires=[ "cppyy>=2.3.1" ],
    license="GPLv3",
    classifiers=[
        "Intended Audience :: Developers",
        "Development Status :: 3 - Alpha",
        "Topic :: Software Development :: Libraries :: Application Frameworks",
        "License :: OSI Approved :: GNU General Public License v3 (GPLv3)",
        "Programming Language :: C++",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Operating System :: MacOS :: MacOS X",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: POSIX :: Linux"
    ]
)