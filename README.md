ta-lib for Debian
-----------------

Build the Debian binary packages from the root
directory. Make sure that you prepare auto-configure and
auto-make. After cloning from Git, type:

	sh autogen.sh
	dpkg-buildpackage -I.\*

The `*.deb` packages for `ta-lib` and `ta-lib-dev` will appear in
the parent directory.
