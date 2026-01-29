inherit "/d/Shire/khazad/moria_room_deeps";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/khazad/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#define ORC_PATH "/d/Shire/orcmaker/"
#define TROLL_PATH "/d/Shire/khazad/npc/"
 
object orc, troll;
int i;
 
 
void
create_room()
{
  if (!orc)
  {
    for (i =  1; i <= 3; i++)
    {
      orc = clone_object(ORC_PATH + "orcmaker");
      orc->set_power(200 + random(50));
      orc->set_type(WARRIOR);
      orc->move_living(0, this_object());
    }
  }
 
  if (!troll)
  {
    for (i = 1; i <= 2; i++)
    {
      troll = clone_object(TROLL_PATH + "troll");
      troll->move_living(0, this_object());
    }
  }
 
  deep = 1;
  roomtype = 0;
  extraline = "The tunnel continues off to the north and south.\n";
 
  NORTH(DEEPS_DIR + "deeps002");
  SOUTH(DEEPS_DIR + "deeps006");

  make_the_room();
}
