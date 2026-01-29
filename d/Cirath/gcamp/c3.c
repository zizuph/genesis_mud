inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"
#include "defs.h"

void
create_room()
 {
  set_short("Gith Fortress");
  set_long("You are inside the gith fortress now, tents and shelters "
  	+"surround you, obvious living quarters for the evil gith.  "
  	+"Tall stone walls ring the fortess, and at the southern end, "
  	+"braced against the craggy mountainside, two tall towers look "
  	+"out over the valley and encampment.\n");
  add_item("mountainside","The mountain looms to the south, its flat "
  	+"face stretching up above the towers situated against it, before "
  	+"becoming covered in small rocky outcroppings.\n");
   add_item(({"shelters","tents"}),"They are scattered through out the "
	+"fortress, mainly "
  	+"against the inside of the stone walls of the fortress.  It looks "
  	+"as if they could house a large number of gith.  You might be able "
  	+"to get inside them somehow.\n");
   add_item(({"towers","tall towers","tower"}),"These two tall stone towers "
  	+"stretch up against the side of the mountain behind them like "
  	+"two thin reeds.\n");
  add_prop(ROOM_I_HIDE,-1);
  add_exit(CAMP + "c1","north");
  add_exit(CAMP + "c2","west");
  add_exit(CAMP + "c7","south");
  add_exit(CAMP + "c4","east");
  add_exit(CAMP + "c8","southwest");
  add_exit(CAMP + "c6","southeast");
  add_exit(CAMP + "t2","enter",0,0,1);
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith1",1,2,GITH_NPC+"gith1",1);
}

