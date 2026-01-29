/* A room on the first floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

#define MAILREADER       "/secure/mail_reader"

init()
{
    object reader;
    string *r;
    ::init();

    seteuid(getuid());
    reader = clone_object(MAILREADER);
    if(!reader)
    {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(this_player());
}

leave_inv(ob, to)
{
    object reader;
    ::leave_inv(ob); 

    reader = present("mailread", ob);
    if (reader) reader->remove_object();

}

create_room()
{
    set_short("Tower Post Office");

    set_long("You stand in the post office of the Marble Tower. In" +
        " this room you can receive missives sent to you from" + 
        " anywhere in the world, and send them as well. The Tower" +
        " postmaster keeps this place in perfect order, parchment"+
        " stabled in neat stacks, ink in small bottles with nary a"+
        " stain to be seen anywhere. " + basic_desc + " To the west"+
        " a corridor stretches.\n");
        
    add_item(({"parchment", "parchments", "stack", "stacks"}), "The"+
        " stack of blank parchment is probably refilled often.\n");

    add_item(({"ink", "bottles"}), "It's a handful of ink bottles" +
        " that are used for writing.\n");

    add_exit(TOWER + "tower_corr_1_3.c", "west", 0, 1);

    make_college_room();
}
