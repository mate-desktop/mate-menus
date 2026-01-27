#!/usr/bin/bash

# Use grouped output messages
infobegin() {
	echo "::group::${1}"
}
infoend() {
	echo "::endgroup::"
}

# Required packages on Fedora
requires=(
	ccache # Use ccache to speed up build
	meson  # Used for meson build
)

# https://src.fedoraproject.org/cgit/rpms/mate-menus.git
requires+=(
	autoconf-archive
	chrpath
	gcc
	git
	gobject-introspection-devel
	gsettings-desktop-schemas
	make
	mate-common
	mate-panel
	redhat-rpm-config
)

infobegin "Update system"
dnf update -y
infoend

infobegin "Install dependency packages"
dnf install -y ${requires[@]}
infoend
