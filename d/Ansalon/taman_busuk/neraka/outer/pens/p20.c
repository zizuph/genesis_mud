/* Ashlar, 24 May 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit NOUTROOM;
inherit NSLAVEPEN;

void
create_neraka_room()
{
    set_slavemax(random(3)+2);	
    set_slavetype(1);

	set_short("in a slave pen");
    set_long("@@long_descr@@");
    set_extra_long("You are in a slave pen, which is nothing more than a " +
        "pit in the ground covered with a metal grating. The ground is " +
        "covered with mud or worse, and the smell is very bad. A tunnel " +
        "leads southeast. ");

    add_item(({"pen","slave pen","pit"}),
        "It is a pit dug in the ground, covered with a metal grating. The " +
        "walls are steep and while you can climb them the slaves are " +
        "probably too weak.\n");
    add_item("walls","The walls are steep and slippery.\n");
    add_item(({"ground","mud"}),
        "The ground is covered with a deep layer of nasty-smelling mud.\n");
    add_item(({"grating","metal grating","grate","metal grate"}),
        "A heavy metal grating helps to keep the slaves in the pen.\n");
    add_item("tunnel","It leads east.\n");

    add_exit(NOUTER+"black/b23","up","@@leave_pen@@");
    add_exit(NOUTER+"pens/p21","southeast");
    reset_room();
}

