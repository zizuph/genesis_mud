//
// Sacristy Cabinet - holds ritualistic tools and vestments for kirk
//
// Zima  June 5, 98
//
#pragma strict_types
inherit "/std/receptacle";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
 
public void
create_receptacle()
{
    set_name("cabinet");
    set_adj("tall");
    set_short("tall cabinet");
    set_long("It is tall wooden cabinet made of ornately carved "+
        "oak with thick lead crystal doors, etched with three "+
        "interlocked circles with a small brass lock. It looks "+
        "very sturdy and secure.\n");
 
    set_key(679806052); // may be changed by cloning room
    set_pick(100);
 
    add_prop(CONT_I_WEIGHT,     100000);
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME,     200000);
    add_prop(CONT_I_MAX_VOLUME, 400000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     1); // glass doors
    add_prop(OBJ_M_NO_GET,     "The cabinet is far to heavy and bulky " +
                               "for you to move.\n");
    add_prop(OBJ_I_VALUE, 800);
}
