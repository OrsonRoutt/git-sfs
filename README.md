# git-sfs (Git-Shit File Storage)

A set of simple C++ programs to circumvent Git LFS metering by unpacking/packing large files to/from small chunks.

## Setup

To setup `git-sfs` for your repository, do the following:
1. Download the latest release from the [Releases](https://github.com/OrsonRoutt/git-sfs/releases) page and place the contents in the root directory of your repository.
2. Configure `git-sfs` by editing `sfs_settings.txt`. Its format is as follows:
```
<gitignore path>
<gitignore sfs marker>
<chunk size (bytes)>
<sfs chunk extension>
```
The default configuration (setup for GitHub) is as follows:
```
.gitignore
# :!git-sfs
103809024
sfs
```
3. Add SFS files to your root `.gitignore` by putting them at the bottom of the file below a .gitignore sfs marker line. With default settings, this would look like so:
```
<rest of gitignore>
...
# :!git-sfs
path/to/file1
path/to/file2
path/to/file3
path/to/file4
```
4. If you were using LFS before, make sure SFS files are actually ignored by Git.

## Usage

To use `git-sfs`, run either of the executables, `sfs-unpack` or `sfs-pack` (+`.exe` on Windows).
- `sfs-unpack`: Takes all SFS files (defined in `.gitignore`) and splits them into chunk files of the chunk size. This makes them able to be committed.
    - Chunk files are named like so: `<filename>.<chunk num>.<chunk extension>`
- `sfs-pack`: Takes all SFS chunk files and packs them into their corresponding SFS file. This updates or creates the SFS file.

The intended usage of these executables is as such:
- `sfs-unpack`: Run before committing after changing an SFS file/s.
- `sfs-pack`: Run after pulling changes to SFS files.
    - If the contents of the files is not important for what you're doing, you don't have to run `sfs-pack`.
