
inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

create_room()
{
set_short("Outside the tavern");
set_long(break_string("You find yourself on a rough dirt road that"
     +" leads through town curving here from northeast to west.  Just"
     +" to the south stands an old, dilapidated tavern which you can"
     +" apparently enter."
     +"\n",75));

AE(RHUN+"stown6/crossroads","northeast",0);
AE(RHUN+"stown6/road_w","west",0);
AE(RHUN+"stown6/tavern","south",0);

add_prop(ROOM_I_LIGHT,1);

add_item(({"building","tavern","inn"}), break_string("The tavern is"
     +" a run-down old wooden building.  It apparently has been deserted,"
     +" save for the owner, who stays on, devoted to his business.\n",75));

}

