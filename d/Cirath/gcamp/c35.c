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
  set_long("You have reached the southeastern corner of the walkway"
  	+"overlooking the gith fortress.  Sprawled out below you "
  	+"tents and makeshift shelters shield a large portion of "
  	+"the fierce gith warriors from the sun.  Directly to your "
  	+"south, a narrow ladder cut into the stone leads upwards "
  	+"to a tower which looks out over the valley and the gith "
  	+"camp.\n");
  add_item(({"mountainside","mountain"}),"The mountain looms to the south, "
  	+"its flat face stretching up above the towers situated against "
  	+"it, before becoming covered in small rocky outcroppings.\n");
  add_item("wall","It is a large sanstone wall circling the gith "
  	+"camp.  There is a narrow walkway atop it that you are "
  	+"standing on.\n");
  add_item("ladder","It is cut into the surface of the tower itself "
  	+"with hardly enough room for your foot to fix in the hole.\n");
  add_item(({"shelters","tents"}),"They are scattered through out the "
        +"fortress, mainly "
        +"against the inside of the stone walls of the fortress.  It looks "
        +"as if they could house a large number of gith.  You might be able "
        +"to get inside them somehow.\n");
  add_item("walkway","You are standing on top of a narrow walkway atop "
  	+"the wall of the gith fortress.\n");
  add_item(({"towers","tall towers","tower"}),"These two tall stone towers "
  	+"stretch up against the side of the mountain behind them like "
  	+"two thin reeds.\n");
  add_item("valley","The rocky valley leads away to the north.\n");
  
  add_exit(CAMP + "c36","up");
  add_exit(CAMP + "c32","north");
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(GITH_NPC+"gith3",1,1,GITH_NPC+"gith3",1);

}

