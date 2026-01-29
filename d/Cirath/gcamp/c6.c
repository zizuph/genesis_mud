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
  set_long("The gith encampment continues here, with shelters stretched "
  	+"out around you.  Rough firepits sit outside the entrances to  "
  	+"some of these shelters, obviously providing a place for these "
  	+"creatures to cook whatever form of food they eat.\n");
  add_item("mountainside","The mountain looms to the south, its flat "
  	+"face stretching up above the towers situated against it, before "
  	+"becoming covered in small rocky outcroppings.\n");
  add_item(({"firepit","firepits"}),"It is composed of a few random rocks "
  	+"arranged in a circle.  Scorch marks cover the rocks, and ashes "
  	+"fill the shallow pit in their middle.\n");
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
  add_prop(ROOM_I_HIDE,-1);
  add_exit(CAMP + "c3","northwest");
  add_exit(CAMP + "c4","north");
  add_exit(CAMP + "c13","south");
  add_exit(CAMP + "c14","southeast");
   add_exit(CAMP + "c7","west");
  add_exit(CAMP + "c12","southwest");
  add_exit(CAMP + "c5","east");
  add_exit(CAMP + "t5","enter",0,0,1);
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith2",1,2,GITH_NPC+"gith2",1);
}

