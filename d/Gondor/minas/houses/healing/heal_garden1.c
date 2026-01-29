inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
  set_short("The garden in front of the Houses of Healing");
  set_long(break_string("This is a green and beautiful little garden in front "+
    "of some fair stone houses. A greensward of trees and some flowers are "+
    "set around you in the garden, and a path leads north to "+
    "the main street in the Sixth Circle.\n",75));
  add_prop(ROOM_I_NO_ATTACK,1);
  add_item("houses","These fair houses made of white stone are set apart for the care of\n"+
    "those who are grievously sick or the tending of those who are hurt in\n"+
    "battle or dying. The entrance door is to the south.\n");
  add_item("flowers","There are some lovely lilies growing here.\n");
  add_exit(MINAS_DIR + "s2crc6","north",0,0);
  clone_object(HOH_DIR + "doors/heal_door_out")->move(TO);
}

