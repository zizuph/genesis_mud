/*
 * mm_hut.c
 *
 * Used in nyreese/cadu_q9.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("hut");
    set_short("burned down hut");
    set_adj(({"burned","down"}));

    set_long("This hut belongs to Cadu's Society of Justice. Someone "+
             "has burned it down. In the ashes, you see the remains of a "+
             "weird looking gnomish machine.\n");

    add_item("machine", "It was used to dispense membership buttons.\n");
    add_prop(OBJ_I_NO_GET, "Are you kidding me???\n");
}

/*
void
init()
{
    ::init();
}

int
enter(string s)
{
    notify_fail("Enter what?\n");
    if (s != "hut")
        return 0;

    TP->move_living("into the hut", NYREESEDIR + "mm_inside");
    return 1;
}
*/
