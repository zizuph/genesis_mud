/*
 * storeroom_key.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/cave_defs.h"

inherit "/std/key";

/*
 * Function name: create_key
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_key()
{
    set_adj("large");
    add_adj("rusty");
    set_long("It is a large key made from rusted iron.\n");
    set_key(STOREROOM_KEY);
}