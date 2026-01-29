// file name:        port6.c
// creator(s):       Ilyian
// revision history: Denis, Sep'96: Changes due to the port inheritance recode.
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include "port.h"
inherit PORT_ROOM;

static void
create_port_room()
{
    set_short("Southern side of port cavern");
    set_long("The ledge runs along the southern cavern wall here, " +
             "with the choppy dark lake to the north. To the west is a " +
             "newly constructed warehouse, poised dangerously over the " +
             "waters. The mist is especially heavy here, obscuring " +
             "your vision to the east.\n");

    IN
    LIGHT

    add_exit(PORT+"ware","west",0);
    add_exit(PORT+"port3","east",0);
    add_exit(PORT+"ware2", "south", 0);

    add_rift_no_see_item();
    add_wall_item();
    add_ceiling_in_item();
    add_no_swim_cmditems();

    add_item("warehouse",
	     "The warehouse is quite large and made out of " +
             "sturdy wood. As it is wider than the ledge, its northern " +
             "half rests on thick wooden poles that descend into the water.\n");
}
