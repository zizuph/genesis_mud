inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
create_room()
 {
  set_short("Gith Fortress");
  set_long("You are in the central portion of the camp of gith "
  	+"warriors.  Tents and shelters surround you on all sides "
  	+"with the gates at the entrance, now far behind you.  "
  	+"Ahead lies only more tents, and the towering sheet of "
  	+"rock formed by the side of the mountain before you.\n");
  add_item("mountainside","The mountain looms to the south, its flat "
  	+"face stretching up above the towers situated against it, before "
  	+"becoming covered in small rocky outcroppings.\n");
  add_item("staircase","Made from rough hewn stone blocks braced by "
  	+"wooden beams, this staircase leads to the top of the wall.\n");
  add_item("wall","It is a large stone wall that protects the camp.\n");
  add_item("walkway","It runs along the top of the wall apparently, and "
  	+"looks as if it could be used by guards to keep an eye on the "
  	+"camp.\n");
  add_item(({"shelters","tents"}),"They are scattered through out the "
  	+"fortress, mainly "
  	+"against the inside of the stone walls of the fortress.  It looks "
  	+"as if they could house a large number of gith.  You might be able "
  	+"to get inside them somehow.\n");
  add_item(({"towers","tall towers","tower"}),"These two tall stone towers "
  	+"stretch up against the side of the mountain behind them like "
  	+"two thin reeds.\n");
  add_exit(CAMP + "c7","northeast");
  add_exit(CAMP + "c8","north");
  add_exit(CAMP + "c17","southeast");
  add_exit(CAMP + "c9","northwest");
  add_exit(CAMP + "c19","southwest");
  add_exit(CAMP + "c18","south");
  add_exit(CAMP + "c12","east");
  add_exit(CAMP + "c10","west");
   add_exit(CAMP + "t10","enter",0,0,1);
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith2",1,2,GITH_NPC+"gith2",1);
}

