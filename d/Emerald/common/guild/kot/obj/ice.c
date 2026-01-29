/*
 * ICE.c
 * 
 * This object is loaded into the room to replace the lack of
 * corpse of victim of the Telberin's Fire and Ice spell
 *
 * by Alaron August 12, 1996
 */

#include "../telberin.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit "/std/object";

void
create_object()
{
    set_name("shards");
    set_adj("pile");
    add_name("pile");
    add_adj("ice");
    set_short("pile of ice shards");

    set_long("It is a pile of thin, cracked ice shards. They are "+
	     "extremely cold and are giving off a large amount of "+
	     "mist, but don't seem to be melting at all.\n");

    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME,60);
    
    add_prop(OBJ_M_NO_GET,"They seem a bit too cold to carry.\n");
}
