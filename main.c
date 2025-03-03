#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "./loadable_cache/cache.h"
#include "cut_list.h"
#include "piece_values.h"
#include "vec.h"

#define BUFFER_LEN 256

ValueType optimize_wrapper(KeyType key) {
    return _optimize(key.starting, key.value_list);
}

void usage(char *program_name);
int main(int argc, char *argv[]) {
    char pv_file[BUFFER_LEN];
    if (argc != 2 || !strcmp(argv[1], "-h"))
        usage(argv[0]);
    int arg_len;
    if (1 != sscanf(argv[1], "%s%n", pv_file, &arg_len) ||
        arg_len != strlen(argv[1]))
        usage(argv[0]);
    Vec value_list = read_piece_values(pv_file);
    if (value_list == NULL) {
        fprintf(stderr, "Error in value list.\n");
        return 1;
    }

    Cache *cache = load_cache_module("./liblast_recently_used.so");
    if (cache == NULL) {
        fprintf(stderr, "Failed to load cache module\n");
        return 1;
    }

    ProviderFunction get_me_a_value = optimize_wrapper;
    get_me_a_value                  = cache->set_provider_func(get_me_a_value);

    unsigned int rod_len;
    while ((rod_len = prompt_for_length())) {
        InputValues iv = {value_list, rod_len,
                          new_cutlist(value_list, rod_len)};
        CutList *cl    = get_me_a_value(iv);
        cutlist_print(cl);
        cutlist_free(cl);
    }

    CacheStat *stats = cache->get_statistics();
    print_cache_stats(fileno(stdout), stats);
    free(stats);

    cache->cache_cleanup();
    free(cache);

    return 0;
}
noreturn void usage(char *program_name) {
    fprintf(stderr,
            "Usage:\n"
            "%s [-h] file_name\n"
            "Invalid filename \n",
            program_name);
    exit(1);
}
