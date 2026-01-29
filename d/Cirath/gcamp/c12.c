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
  set_long("You are in the center of the fortress of gith.  There "
  	+"are fewer tents here, but some still remain.  This camp "
  	+"looks as if it has been here a long time, that much is "
  	+"evidenced by the well used firepits, and tattered tents.  "
  	+"To the south, rising like an enormous wave of stone, "
  	+"lies the face of a sheer cliff which provides protection "
  	+"for the back side of the fortress.  Twin towers rise on "
  	+"the southwest and southeast corners of the fortress, "
  	+"giving a commanding view over the valley before the camp.\n");
  add_item("firepits","They are formed of a loose circle of rocks "
  	+"surrounding a pile of old ashes.  Small trails of smoke "
  	+"periodically wisp out of the old ashes towards the sky.\n");
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
 add_prop(ROOM_I_HIDE,-1);
  add_exit(CAMP + "c6","northeast");
  add_exit(CAMP + "c7","north");
  add_exit(CAMP + "c16","southeast");
  add_exit(CAMP + "c8","northwest");
  add_exit(CAMP + "c18","southwest");
  add_exit(CAMP + "c17","south");
  add_exit(CAMP + "c13","east");
  add_exit(CAMP + "c11","west");
  add_exit(CAMP + "t11","enter",0,0,1);
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith2",1,2,GITH_NPC+"gith2",1);
}


