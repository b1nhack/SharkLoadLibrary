# SharkLoadLibrary

LoadLibrary for Children's Paradise.

:sailboat: Folk From [DarkLoadLibrary](https://github.com/bats3c/DarkLoadLibrary) and thanks.

## Feature

New feature: **LOAD_REMOTE_FILE**

## Usage

```C
PDARKMODULE DarkModule = DarkLoadLibrary(
	LOAD_REMOTE_FILE, // control flags
	"http://xxxx/demo.dll", // remote dll url, if loading from remote
	NULL, // dll buffer to load from if loading from memory
	0, // dll size if loading from memory
	L"Demo" // dll name if loaded from memory and remote
);
```

## Build && Test

### Environmental requirements

* libcurl

  Install from vcpkg: 

  ```shell
  .\vcpkg install curl:x64-windows-static
  ```

  and set vcpkg->Use Static Libraries `YES`

Build it :)

### Test

I made a test dll named demo.dll.

It has a export function named Demo and just pop a dialog.

use `Python3` start a server: 

```shell
python -m http.server
```

url maybe like `http://127.0.0.1:8000/demo.dll`

use url replace `http://xxxx/demo.dll`

Build && Run
