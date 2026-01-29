/* Ashlar, 24 May 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit NIOUTROOM;
inherit NSLAVEPEN;

void
create_neraka_room()
{
    set_slavemax(random(3)+2);	

	set_short("in a slave pen");
    set_long("@@long_descr@@");
	set_long("You are in a slave pen, which is a small burrow dug in " +
        "the ground. This looks like a sleeping place for the slaves. " +
        "a narrow metal shaft leads up and lets in fresh air and some " +
        "light.\n");

    add_item(({"pen","slave pen","burrow"}),
        "It is a burrow dug underground.\n");
    add_item(({"ground","mud","bottom"}),
        "The ground is covered with a deep layer of nasty-smelling mud.\n");
    add_item(({"shaft","metal shaft","narrow metal shaft","narrow shaft"}),
        "The shaft is too narrow to climb through, even for children, " +
        "but it serves to let in fresh air and food is probably dropped " +
        "down it.\n");

    add_exit(NOUTER+"pens/p2","northwest");
    reset_room();
}


