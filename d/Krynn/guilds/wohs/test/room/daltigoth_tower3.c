/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_BASE;

#define HEARTROOM_ACTIVATED  "_wohs_test_heartroom_activated"
#define WOHS_TELL_ROOM(y, x)    tell_room(TO, x, 0, y)

object pool;

void
reset_tower_room()
{
    if(!objectp(pool))
    {
       pool = clone_object("/d/Krynn/guilds/wohs/test/obj/lunitari_pool");
       pool->move(TO);
    }
}

void
create_tower_room()
{
   set_short("a wide, open hall within the crimson tower of High Sorcery");
   set_long("@@long_desc");

   add_item(({"pool","central pool","captured light","light","lunitari",
       "energies","captured energies","red light"}), "@@pool_desc");
   add_item(({"hall","wide open hall","wide hall","open hall",
       "vaulted ceilings","ceilings"}), "You stand in a wide, open hall " +
       "that forms the entry of the crimson tower of High Sorcery. The " +
       "hall is dominated by a large shallow pool in the centre of " +
       "the room, shining red with the light of the neutral moon of " +
       "magic, Lunitari. The ceilings rise high above you, with " +
       "staircases to the north and south spiralling to the upper " +
       "levels of the tower.\n");
   add_item(({"double doors of black oak","double doors","doors","oak",
       "black oak","door"}), "To your east standing closed are thick " +
       "double doors of black oak.\n"); 
   add_item(({"staircases","stairs","broad staircases"}),"To your north " +
       "and south staircases rise to the upper levels of the tower.\n");

   set_tell_time(20);
   add_tell("The water of the shallow pool churns violently onto the " +
       "floor of the hall as the tower lurches!\n");
   add_tell("The staircases rising to your north and south shake " +
       "violently, as if struck by a wave of force!\n");
   add_tell("The stones of the tower begin to crack as spiderwebs of " +
       "energy spread across them.\n");
   add_tell("Beyond the closed doors of the Tower you hear the sound " +
       "of warhorns, magical explosions, and screams.\n");
   add_tell("The walls of the tower groan, as if they were being " +
       "constricted by a powerful coil of force.\n");

   add_exit(WOHS_TEST + "room/daltigoth_tower2", "east", "@@leave_tower");
   add_exit(WOHS_TEST + "room/daltigoth_tower4", "southwest", 0);
   add_exit(WOHS_TEST + "room/daltigoth_tower5", "northwest", 0);

   add_cmd_item(({"from pool","water","from shallow pool"}),
       "drink","@@drink_water");

   add_cmd_item(({"pool","shallow pool","water"}),({"enter","dive","swim"}),
       "@@enter_pool");

   reset_tower_room();
}

string
long_desc()
{
      if(TP->query_prop(HEARTROOM_ACTIVATED))
          return "You are in a wide, open hall with vaulted ceilings " +
              "and a central pool that seems to radiate chaotically " +
              "with captured energies of the Tower! On either side of " +
              "the pool broad staircases twist and groan as the Tower " +
              "constricts to the powerful forces set in motion.\n";

      return "You are in a wide, open hall with vaulted ceilings and " +
          "a central pool that seems to shine red with the captured " +
          "light of Lunitari. On either side of the pool broad " +
          "staircases lead to the upper levels of the tower.\n";
}

string
pool_desc()
{
      if(TP->query_prop(HEARTROOM_ACTIVATED))
          return "Occupying the centre of the hall is a large shallow " +
              "pool. Energies seem to be charging within it as the " +
              "Tower's magic begins to unravel, and it radiates with a " +
              "red light that reminds you of the enchantments activated " +
              "by the magical mirrors in the Hall of Shifting Shadows. " +
              "To the north and south of the pool staircases writhe " +
              "and twist as the Tower is constricted by a powerful " +
              "force.\n";

      return "Occupying the centre of the hall is a large shallow pool " +
          "that shines red with the magically captured light of " +
          "Lunitari. To the north and south of the pool staircases rise " +
          "to the upper levels of the tower.\n";

}

string
enter_pool()
{
      if(TP->query_prop(HEARTROOM_ACTIVATED))
          return "You step into the pool. Radiant energies swirl around " +
              "your feet like those of the Rivers of Time in the well " +
              "at Wayreth, however nothing happens. It feels like you " +
              "are missing something?\n";

      return "You step into the pool. Nothing happens, apart from your " +
          "feet getting wet.\n";
}

int
leave_tower()
{
      if(TP->query_prop(HEARTROOM_ACTIVATED))
      {
          write("The double doors of black oak have been sealed closed " +
              "by magical wards. You can no longer exit that way.\n");
          return 1;
      }

      write("The double doors of black oak open as you approach them, " +
          "and you exit the tower.\n");
      return 0;          
}

string
drink_water()
{
    if(TP->drink_soft(TP->drink_max() / 16, 0))
    {
	write("You taste the water of the pool... It is quite " +
            "refreshing, however no different from normal water " +
            "irrespective of its colour.\n");
	say(QCTNAME(TP)+ " drinks some water from the pool.\n");
	return "";
    }
    else
	write("You are quite full of water at the moment, and don't " +
            "feel like drinking anymore.\n");
    return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && TP->query_prop(HEARTROOM_ACTIVATED))
    {
       set_alarm(2.0,0.0, &WOHS_TELL_ROOM(ob, "The shallow red pool " +
           "radiates with a powerful red energy!\n"));

       start_room_tells();
    }
}