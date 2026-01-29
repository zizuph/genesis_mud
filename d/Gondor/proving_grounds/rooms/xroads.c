
/*


Ithilien Proving Grounds

This area is for using your juniors to test NPCs, weapons, armour etc

Do NOT put any exits to the game in this area.


Palmer - May 08, 2006


*/


#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include "/d/Gondor/common/lib/clock.h"



public void create_gondor();



public void
create_gondor()
{
    set_short("between two large trees in Ithilien");
    set_long("A crossroads in the Ithilien Proving Grounds - NOT in the game.\n\n" +
             "To the north is the Haradrim proving grounds.\n" +
             "To the south is the Mage proving grounds.\n" +
             "To the west is the Ranger proving grounds.\n" +
             "To the east is the Orc proving grounds.\n" +
             "Go down for armour and weapons.\n\n");


    add_exit("r_room4","west");
    add_exit("o_room1","east");
    add_exit("h_room4","north");
    add_exit("m_room1","south");
    add_exit("armoury","down");


}

