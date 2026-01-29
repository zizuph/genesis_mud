/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

string
query_to_jail()
{
  return "southeast";
}

void
create_palan_room()
{

    set_short("The western Harbour");
    set_long(BS("The harbour spreads out to the north and "
         +   "east from here. To the southeast you can see "
         +   "the magnificent palace and the central plaza. ",SL));

    add_exit(ROOM + "street13","east",0,1);
    add_exit(ROOM + "street16","north",0,1);
    add_exit(ROOM + "plaza","southeast",0,1);

    add_item(({"palace"}),
	     BS("From this point of view, you can make see the backside of the palace. " +
		"You see several parts of the building, a smaller part on the west side " +
		"of the palace and a part which has been well kept in shape further east. " +
		"Behind the palace, you can see lots of people on a large plaza and you " +
		"hear loud noises coming from the direction also.",SL));
    add_item(({"plaza"}),
	     BS("From here, you cannot see much of the plaza really, since most of it is " +
		"hidden behind the palace. You can hear a lot of different noises and see " +
		"many people milling about on the plaza to your southeast.",SL));
    add_item(({"harbour","ships","boats","ship","boat"}),
	     BS("Northeast from you is the boat harbour of Palanthas. Many ships of all kinds " + 
		"and sizes can be seen, such as rowing boats, small sailing ships, even a " +
		"large ocean-going corsair ship is in the bay.",SL));
}



