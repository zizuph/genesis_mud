inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

object man;

create_room()
{
  set_short("Entryhall of the Houses of Healing");
  set_long(BSN("This is the large entryhall of the Houses of Healing. "+
    "Two long corridors branch off to the east and west. Double "+
    "doors lead out of the building to the north. Facing the "+
    "entrance, on the opposite wall, is a large tapestry with "+
    "beautiful images from history. There is also a scent of "+
    "herbs and ointments lingering in the air."));
  add_item(({"tapestry","images"}),BSN(
    "The images on the tapestry depict Isildur planting the sapling "+
    "of the White Tree in the court of the Citadel in Minas Tirith, "+
    "after fleeing with it from Minas Ithil when Sauron first sacked "+
    "the Tower of the Moon in S.A. 3429."));
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_NO_ATTACK,1);
  add_exit(HOH_DIR + "ne_stair","east",0,1);
  add_exit(HOH_DIR + "nw_stair","west",0,1);
  clone_object(HOH_DIR + "doors/heal_door_in")->move(this_object());
  add_stuff();
}

add_stuff()
{
  if (!man) {
    man = clone_object(MINAS_DIR+"npc/herbmaster");
    man->move(TO);
    }
}

reset_room()
{
  add_stuff();
}

