/* Ashlar, 24 May 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit NIOUTROOM;
inherit NSLAVEPEN;

void
create_neraka_room()
{
    set_slavemax(random(2));	

	set_short("in a slave pen");
    set_long("@@long_descr@@");
	set_long("You are in a slave pen, which is nothing more than a " +
        "tunnel dug underground. The bottom of the tunnel is " +
        "covered with mud or worse, and the smell is very bad.\n");

    add_item(({"pen","slave pen","tunnel"}),
        "It is a tunnel dug underground, widened to allow people to move.\n");
    add_item(({"ground","mud","bottom"}),
        "The ground is covered with a deep layer of nasty-smelling mud.\n");

    remove_prop(ROOM_I_LIGHT);

    add_exit(NOUTER+"pens/p3","southwest");
    add_exit(NOUTER+"pens/p5","east");
    add_exit(NOUTER+"pens/p9","northwest");
    add_exit(NOUTER+"pens/p10","southeast");
    reset_room();
}

