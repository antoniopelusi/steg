# steg

Embed and extract text in an image using a password.

The text will be encrypted and embedded using a random path.

&nbsp;

## Install:

	make install

&nbsp;

## Test:

	make test

&nbsp;

## Usage:
**Write**:

	steg -w <image> <password> <text>

**Read**:

	steg -r <image> <password>

&nbsp;

## Supported image formats:
- .png