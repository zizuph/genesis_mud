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
        "covered with mud or worse, and the smell is very bad. " +
        "A sturdy gate blocks off the northeast exit.\n");

    add_item(({"pen","slave pen","tunnel"}),
        "It is a tunnel dug underground, widened to allow people to move.\n");
    add_item(({"ground","mud","bottom"}),
        "The ground is covered with a deep layer of nasty-smelling mud.\n");
    add_item(({"gate","sturdy gate"}),
        "The gate is barred from the other side and is quite impossible " +
        "to open from this side.\n");

    remove_prop(ROOM_I_LIGHT);

    add_exit(NOUTER+"pens/p25","west");
    add_exit(NOUTER+"pens/gates","northeast","@@go_gates");
    reset_room();
}

int
go_gates()
{
	write("You cannot go through the gate.\n");
    return 1;
}

