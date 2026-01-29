#pragma strict_types

inherit "/std/heap";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>

void
create_heap()
{
    set_name("phial");
    add_name(({"holy water", "phial of holy water","_oots_holy_water"}));
    add_pname(({"holy waters", "phials of holy water","phials"}));    
    set_adj(({"holy", "water"}));
    set_short("phial of holy water");
    set_pshort(({"phials of holy water","holy waters"}));
    
    set_long("This is a small phial of holy water.\n");

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 46);

    set_heap_size(1);
    set_keep();

    if(!query_prop(HEAP_S_UNIQUE_ID)) 
        add_prop(HEAP_S_UNIQUE_ID, MASTER + "_oots_holy_water"); 
    add_prop(HEAP_I_UNIT_VALUE, 0); 
}

/*
 * Function name: query_auto_load
 * Returns      : string - the auto-load string.
 */

public string
query_auto_load()
{
    /* Don't auto load if we are about to destroy. */
    if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;
    return (MASTER + ":" + num_heap());
}

/* 
 * Function name: init_arg
 * Description  : Called when autoloading. It will set the number of waters in the heap.
 * Arguments    : string arg - the auto-load argument.
 */
void
init_arg(string arg)
{
    int sum;
    if (sscanf(arg, "%d", sum) == 1)
    {
	set_heap_size(sum);
    }
}

/*
string
query_recover()
{
    return (MASTER + ":" + num_heap());
}
*/