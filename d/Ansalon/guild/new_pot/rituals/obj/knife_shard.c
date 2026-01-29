/* Zizuph November 2022
 */
#pragma strict_types

inherit "/std/heap";

#include <macros.h>
#include <stdproperties.h>

public void create_heap()
{
    set_short("knife shard");
    set_pshort("knife shards");
    add_name("_pot_knife_shard");
    add_name("shard");
    add_pname("shards");
    add_adj(({"knife", "weapon"}));
    set_long("This is a small metallic shard coming from a shattered weapon.\n");

    add_prop(HEAP_I_UNIT_VOLUME, 10);
    add_prop(HEAP_I_UNIT_WEIGHT, 10);
    add_prop(OBJ_I_VALUE, 0);
    
    add_prop(HEAP_S_UNIQUE_ID, "_pot_knife_shard");
    set_heap_size(1);
} 

int is_ritual_object()
{
    return 1;
}

int is_knife_shard()
{
    return 1;
}

/*
 * Function name: query_recover
 * Description  : Get the recover string, so that the gem type is 
 *                preserved.
 * Returns      : string - the recover string.
 */
public string
query_recover(void)
{
    /* Don't auto load if we are about to destroy. */
    if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;

    return (MASTER + ":" + num_heap());
}

/*
 * Function name: init_recover
 * Description  : Re-initialise the race and organ.
 * Arguments    : string - the recover arguments.
 */
public void
init_recover(string arg)
{
    int size;

    if (sscanf(arg, "%d", size) == 1)
    {
        set_heap_size(size);
    }
}

