hash_sources = files(
        'hash-functions.h',
        'bernstein-hash.c',
        'fibonacci-hash.c',
        'modulo-hash.c',
        'oat-hash.c',
)
all_sources += hash_sources
public_hash_headers = files(
        'hash-functions.h',
)

# follow semantic versionning (https://semver.org)
# MAJOR <=> incompatible API changes
# MINOR <=> add backwards-compatible functionality
# PATCH <=> backwards-compatible bug fixes
hash_major = '0'
hash_minor = '1'
hash_patch = '0'
hash_version = hash_major + '.' + hash_minor + '.' + hash_patch

hashmap_major = '0'
hashmap_minor = '1'
hashmap_patch = '0'
hashmap_version = hashmap_major + '.' + hashmap_minor + '.' + hashmap_patch

libhash = shared_library('hashlib',
        hash_sources,
        install : true,
        version : hash_version
)

