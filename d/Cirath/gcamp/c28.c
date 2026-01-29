inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
create_room()
 {
  set_short("Walkway on the Gith Fortress");
  set_long("You are standing on top of a narrow walkway that runs "
  	+"along the length of the wall which encircles the large "
  	+"gith encampment.  From up here there is a good view of the "
  	+"camp below you, as well as the valley which stretches to "
  	+"the north away from the fortress.\n");
  add_item(({"mountainside","mountain"}),"The mountain looms to the south, "
  	+"its flat face stretching up above the towers situated against "
  	+"it, before becoming covered in small rocky outcroppings.\n");
  add_item("wall","It is a large sanstone wall circling the gith "
  	+"camp.  There is a narrow walkway atop it that you are "
  	+"standing on.\n");
  add_item("walkway","You are standing on top of a narrow walkway atop "
  	+"the wall of the gith fortress.\n");
  add_item(({"towers","tall towers","tower"}),"These two tall stone towers "
  	+"stretch up against the side of the mountain behind them like "
  	+"two thin reeds.\n");
  add_item(({"cave","caves"}),"They lie both to your the south and "
  	+"southwest.\n");
  add_item("valley","The rocky valley leads away to the north.\n");
  
    add_exit(CAMP + "c31","southeast");
  add_exit(CAMP + "c27","northwest");
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith2",1,1,GITH_NPC+"gith2",1);
}

