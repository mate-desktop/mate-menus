#!/usr/bin/bash

set -eo pipefail

# Use grouped output messages
infobegin() {
	echo "::group::${1}"
}
infoend() {
	echo "::endgroup::"
}

# Required packages on Ubuntu
requires=(
	ccache # Use ccache to speed up build
	meson  # Used for meson build
)

# https://git.launchpad.net/ubuntu/+source/mate-menus/tree/debian/control
requires+=(
	autopoint
	git
	gobject-introspection
	gsettings-desktop-schemas
	libgirepository1.0-dev
	libglib2.0-dev
	make
	mate-common
	mate-panel
)

infobegin "Update system"
apt-get update -y
infoend

infobegin "Install dependency packages"
env DEBIAN_FRONTEND=noninteractive \
	apt-get install --assume-yes \
	${requires[@]}
infoend
