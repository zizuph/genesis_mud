
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "sw.h"

init()
{
    ::init();
    add_action("make_me_the_head_gm","accept");
}

create_room()
{
    set_short("GM appointment room");
    set_long("This is the room where the wizard masters of the "+
        "Spellweavers may bring a new Head Guildmaster for "+
        "appointment to that position.  The mortal may <accept> the "+
        "position "+
        "here.  There is a portal here which leads back into the "+
        "Guildmasters' room of the Spellweavers' guild home.\n");

    add_exit(SWG+"gm_room","portal");

    add_prop(ROOM_I_INSIDE, 1);

}

int
make_me_the_head_gm()
{
	string *names;
	int n;
	
	names = allocate(3);
	for(n = 0; n < 3; n++) names[n] = read_file(GMFILE, n +1, 1);
	names[2] = TP->query_name();
	rm(GMFILE);
	for(n = 0; n < 3; n++) write_file(GMFILE, 
	
    write("You are now the Head Guildmaster, the Lord High "+
        "Magistrate of the Spellweavers.  Congratulations.\n");
    say(QCTNAME(TP)+" has accepted the position of Head "+
        "Guildmaster, the Lord High Magistrate of the "+
        "Spellweavers.\n");

    set_bin_bits(0, 12, 13, TP, 3);

	return 1;
}

