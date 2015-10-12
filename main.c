/*
 * A unit test and example of how to use the simple C hashmap
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hashmap.h"

#define KEY_MAX_LENGTH (256)
#define KEY_PREFIX ("somekey")
#define KEY_COUNT (1024*1024)

typedef struct data_struct_s {
    char key_string[KEY_MAX_LENGTH];
    int number;
} data_struct_t;

int main(int argc, char* argv) {
    int index;
    int error;
    map_t testmap, demomap;
    char key_string[KEY_MAX_LENGTH];
    data_struct_t* value;
    char *demoval, *demokey, *demoret;

    testmap = hashmap_new(2000000ul);

    /* First, populate the hash map with ascending values */
    for (index=0; index<KEY_COUNT; index+=1) {
        /* Store the key string along side the numerical value so we can free it later */
        value = malloc(sizeof(data_struct_t));
        snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
        value->number = index;

        error = hashmap_put(testmap, value->key_string, value);
        assert(error==MAP_OK);
    }

    /* Now, check all of the expected values are there */
    for (index=0; index<KEY_COUNT; index+=1) {
        snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);

        error = hashmap_get(testmap, key_string, (void**)(&value));

        /* Make sure the value was both found and the correct number */
        assert(error==MAP_OK);
        assert(value->number==index);
    }

    /* Make sure that a value that wasn't in the map can't be found */
    snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, KEY_COUNT);

    error = hashmap_get(testmap, key_string, (void**)(&value));

    /* Make sure the value was not found */
    assert(error==MAP_MISSING);

    /* Free all of the values we allocated and remove them from the map */
    for (index=0; index<KEY_COUNT; index+=1) {
        snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);

        error = hashmap_get(testmap, key_string, (void**)(&value));
        assert(error==MAP_OK);

        error = hashmap_remove(testmap, key_string);
        assert(error==MAP_OK);

        free(value);
    }

    /* Now, destroy the map */
    hashmap_free(testmap);

    printf("Map test passed.\nSample code now running:\n");

    // create new map
    demomap = hashmap_new();

    // temporary values
    demokey = "Test Key value";
    demoval = "Test Data value - THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";

    if(hashmap_put(demomap, demokey, &demoval) == MAP_OK)
        printf("Insterted data in map!\n");
    else
        printf("There was an error while inserting the data in the map\n");

    printf("The map size is now: %d\n", hashmap_length(demomap));
    
    if (hashmap_get(demomap, demokey, &demoret) == MAP_OK)
        printf("Found key \n");
    else
        printf("Not found\n");
        
    printf("Read value was \"%s\", which is %s to the original value.\n", demoret, (demoret==demoval)?"equal":"not equal");
    return 1;
}
