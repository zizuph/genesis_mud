/*   crystal_shards.c
 *
 *  A pile of crystal shards.
 *
 * Baldacin@Genesis, Feb 2004.
 */
 
inherit "/std/object";
#include "../ldefs.h"
#include <stdproperties.h>
#include <macros.h>
 
void
create_object() 
{
    set_name("shards");
    set_adj("small");
    add_adj("pile");
	set_short("small pile of crystal shards");
    set_long("This is a small pile of crystal shards. The only thing "+
		"left from some sort of crystal object.\n"); 
    add_prop(OBJ_I_WEIGHT,  800);
    add_prop(OBJ_I_VOLUME,  400);
    add_prop(OBJ_I_VALUE, 0);
}