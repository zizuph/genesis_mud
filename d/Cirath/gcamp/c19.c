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
  set_long("This corner of the encampment looks to have been the "
  	+"subject of some form of attack long ago.  The tall wall "
  	+"that has stood as a protection to the gith and a barrier "
  	+"to you, is somewhat in disrepair.  Chunks of stone lay "
  	+"piled on the ground near a large crack in the wall.  "
  	+"Caves look to have been carved out of the mountain and "
  	+"stretch off south and southwest into its black underbelly.  "
  	+"The tents that have stood around the rest of the camp are "
  	+"conspicuously absent here.\n");
  add_item(({"stone","chunks of stone","chunks"}),"These lay "
  	+"scattered around the ground here, apparently originating "
  	+"from the huge wall that encircles the fortress.  A good "
  	+"portion of them probably came from the large crack that "
  	+"trails up the wall like a lightning bolt.\n");
  add_item(({"mountainside","mountain"}),"The mountain looms to the south, "
  	+"its flat face stretching up above the towers situated against "
  	+"it, before becoming covered in small rocky outcroppings.\n");
  add_item("wall","It is a large stone wall that protects the camp.  "
  	+"A large portion here has been destroyed, leaving a large "
  	+"crack in the wall.\n");
  add_item("crack","This crack looks as if the fortress was "
  	+"somehow attacked at some past point and the invaders "
  	+"managed to smash a hole in the wall.  Upon further "
  	+"inspection you could probably crawl into the crack to "
  	+"escape from the fortress.\n");
  add_item("walkway","It runs along the top of the wall apparently, and "
  	+"looks as if it could be used by guards to keep an eye on the "
  	+"camp.\n");
  add_item(({"towers","tall towers","tower"}),"These two tall stone towers "
  	+"stretch up against the side of the mountain behind them like "
  	+"two thin reeds.\n");
  add_item(({"cave","caves"}),"They lie both to your the south and "
  	+"southwest.\n");
  add_prop(ROOM_I_HIDE,-1);
  add_exit(CAMP + "c10","north");
  add_exit(CAMP + "c20","southwest");
  add_exit(CAMP + "c21","south");
  add_exit(CAMP + "c11","northeast");
  add_exit(CAMP + "c18","east");
   add_exit(CAMP + "p1","crawl","@@block",0,1);
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith3",1,2,GITH_NPC+"gith3",1);
}

int
block()
{
     object guard = present ("gith",TO);
  if(objectp(guard))
  {
      TP->catch_msg(QCTNAME(guard)+" shoves you back.\n");
      return 1;
    }
  return 0;
}

