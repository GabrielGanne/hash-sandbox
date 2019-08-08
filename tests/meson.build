includedirs = include_directories('.', '../src')

test_hash_sources = files(
        'check.h',
        'primes.h',
        'test_hash.c',
)
all_sources += test_hash_sources
test_hash = executable('test-hash',
        test_hash_sources,
        include_directories : includedirs,
        link_with : libhash,
)
test('test-hash', test_hash)
