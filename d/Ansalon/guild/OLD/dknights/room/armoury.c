
/**  DARGAARD KEEP ROOM **/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit GUILD_IN;

object weapon_rack, armour_rack, chest;

void
reset_dargaard_room()
{
   if(!objectp(chest))
   {
      chest = clone_object(GUILD_OBJ + "chest");
      chest->move(TO);
   }

   if(!objectp(weapon_rack))
   {
      weapon_rack = clone_object(GUILD_OBJ + "rack_weapon");
      weapon_rack->move(TO);
   }

   if(!objectp(armour_rack))
   {
      armour_rack = clone_object(GUILD_OBJ + "rack_armour");
      armour_rack->move(TO);
   }

}

void
create_dargaard_room()
{
    set_short("Armoury of Dargaard Keep");
    set_long("You are standing in the armoury of Dargaard Keep. Weapon "+
             "and armour racks are placed near the west and east wall. "+
             "To the north a heavy chest has been placed, its iron "+
             "frame has almost rusted away. Tapestries of epic battles "+
             "and large weapons and shields covers the walls making you "+
             "gasp in awe. The only exit out of this room is to the "+
             "southwest.\n");

    add_exit(GUILD_ROOM + "room12","southwest",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}

