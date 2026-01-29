/**********************************************************************
 * - pub.c                                                          - *
 * - A special pub where players are able to sit at                 - *
 * - tables and have conversations at the table.                    - *
 * - Created by Damaris@Genesis 03/2005                             - *
 * - Cleaned up and optimized by Tapakah, 06/2021                   - *
 **********************************************************************/

#pragma strict_types

#include <files.h>
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

#define FOOD   "/d/Khalakhor/sw_speir/samorgan/obj/fooddrink/"
#define WAITER "/d/Khalakhor/sw_speir/samorgan/npc/sakeller"

inherit KSTDROOM;

inherit "/d/Khalakhor/lib/special_table";
inherit "/d/Khalakhor/lib/tavern";
inherit "/d/Khalakhor/sw_speir/samorgan/room/fireplace";

string
menustuff ()
{
  action_tavern_menu("menu");
  return "";
}

void
create_khalakhor_room()
{
  set_short("SaKeller's Tavern");
  set_long("   This is a charming little tavern. It is filled "+
           "with tables and chairs. A large hearth is placed in the "+
           "southern wall, which houses a most inviting fire within its "+
           "depths. The fire gives off a warm light along with torches "+
           "set in the walls. A long wooden bar stretches along the "+
           "northern wall with the barmaid serving drinks. There is a "+
           "menu on the bar.\n");
  add_item(({"bar", "wooden bar"}),
           "A dark stained bar that has been made out of wood. "+
           "It stretches the length of the northern wall and has "+
           "a menu on it.\n");
  add_item(({"tables", "table"}),
           "The tables are made of a wood and are darkened with stained "+
           "spilled ale and wine. There are chairs arranged around them.\n");
  add_item(({"fireplace", "hearth", "fire", "mantle"}),
           "The large hearth is a most spectacular sight. There "+
           "is a large mantle, which houses a coat of arms just above "+
           "it. The fire dances alluringly "+
           "with golden flames within the depths.\n");
  add_item(({"coat of arms"}),
           "The large coat of arms rests above the mantle of the "+
           "hearth. It has two swords crossed in front of a dragon's "+
           "head. The inscription is faded and worn.\n");
  add_item(({"inscription"}),
           "The inscription is so worn that you are unable to make it "+
           "out.\n");
  add_item(({"firebox", "box"}),
           "There is a box next to the fireplace filled with dry logs.\n");
  add_item(({"log", "logs", "wood"}),
           "There are logs in the firebox. You might try to put a log "+
           "on the fire.\n");
  add_item(({"poker", "holder"}),
           "You see a poker sitting in a holder next to the fireplace.\n");
  add_item(({"torch", "torches"}),
           "The torches are placed securely in the walls and "+
           "cannot be removed.\n");
  add_item(({"north"}),
           "There is a fireplace in that direction.\n");
  add_item(({"south"}),
           "The village is back in that direction.\n");
  add_item(({"northwest", "northeast", "southwest", "southeast","east", "west"}),
           "There is a wall in that direction.\n");
  
  add_item(({"wall", "walls"}),
           "The walls are made from a smooth dark wood.\n");
  add_item(({"plaque", "small plaque", "gold plaque"}),
           "      The gold plated plaque reads:\n"+
           "          +-------------------+\n"+
           "          |     tablehelp     |\n"+
           "          +-------------------+\n");
  add_cmd_item(({"plaque","small plaque", "gold plaque"}),"read",
               "      The gold plated plaque reads:\n"+
               "          +-------------------+\n"+
               "          |     tablehelp     |\n"+
               "          +-------------------+\n");
  add_item("menu", menustuff);
  add_exit("vil1008", "south");
  set_tavern_name("SaKeller's Tavern");

  string *menu = get_dir(FOOD);
  object item;
  string item_file;
  object *food, *drink;
  foreach (string item_file: menu) {
    item_file = FOOD + item_file;
    item = clone_object(item_file);
    if (objectp(item))
      if (IS_FOOD_OBJECT(item))
        add_tavern_food(item_file);
      else if (IS_DRINK_OBJECT(item))
        add_tavern_drink(item_file);
      else
        continue;
    	item->remove_object();
        
  }
        
  set_tavern_waiter(WAITER);
  add_npc(WAITER, 1);
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_LIGHT, 2);
  add_fail(({"southwest", "southeast", "northwest", "northeast", "east", "west"}),
           "You walked into a wall.\n"+
           "OUCH! That's gotta hurt!\n");
  add_fail(({"north"}),
           "You have managed to fall straight into the fireplace by not "+
           "paying attention to where you were going!\n\n"+
           "You scream in agony as you suffer second degree burns, before "+
           "managing to stumble back from the fire.\n");
  config_default_trade();
}

void
init ()
{
  ::init();
  init_tavern();
  init_table();
  init_fire();
}

void
reset_room ()
{
  ::reset_room();
  
  if (! present("waiter")) {
    clone_object(WAITER)->move(TO);
    tell_room(TO, "The proprietor steps in from the back of the house.\n", 0);
  }
}
