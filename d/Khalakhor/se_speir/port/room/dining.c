/**********************************************************************
 * - dining.c                                                       - *
 * - A dining room in Port MacDunn where players are able to sit at - *
 * - tables and have conversations at the table.                    - *
 * - Created by Damaris@Genesis 01/2005                             - *
 **********************************************************************/
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
inherit "/d/Khalakhor/std/room";

inherit "/d/Khalakhor/lib/special_table";
inherit "/d/Khalakhor/lib/tavern";

#include "fireplace.c"

object barley;

string
menustuff(void)
{
  action_tavern_menu("menu");
  return "";
}
public int *
query_local_coords()
{
    return ({14, 8});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

void
create_khalakhor_room()
{
    set_short("Private dining room");
    set_long("    This is a private dining room. It actually began as a "+
      "storage room for the Wild Rover, but when Barley Mae, the "+
      "distant cousin of Murah Drummon of the Clan Macdunn, came to "+
      "stay, he was given this space to do with as he wished. So "+
      "Barley Mae took the liberty of creating this private dining "+
      "room. There are a few tables with chairs around them "+
      "scattered in no special pattern. A warm inviting fireplace "+
      "was added in the southern wall as it was far too cold to "+
      "dine in. Clay lanterns adorn the walls to give soft light "+
      "to this area. A small menu is posted on the north wall along "+
      "with a small plaque beneath it.\n");
    add_item(({"area", "room", "dining room", "here"}), query_long);
    add_item(({"lantern", "clay lantern", "clay lanterns", "imported lanterns", "imported lantern", "lanterns"}),
      "The lanterns are made of clay and were imported from a "+
      "distant land by Barley Mae.\n");
    add_item(({"wall", "walls"}),
      "The walls are standard gray in colour, nothing too unusual "+
      "about them. There are a few clay lanterns attached to them at "+
      "various places.\n");
    add_item(({"south wall", "southern wall", "south"}),
      "A large stone fireplace in that wall.\n");
    add_item(({"north wall", "northern wall"}),
      "Nothing of real interest there.\n");
    add_item(({"east wall", "east", "eastern wall"}),
      "A doorway leading back to the pub is there.\n");
    add_item(({"west", "west wall"}),
      "A small doorway there that leads to the ally beyond.\n");
    add_item(({"doorway", "doorways"}),
      "there are two doorways, one leading back to the pub on "+
      "the east wall and the one that least out into the ally "+
      "in the west wall. The ally doorway once through it will "+
      "automatically lock.\n");
    add_item(({"ally doorway"}),
      "The doorway to the ally is in the west wall and is for "+
      "going out of only.\n");
    add_item(({"ally"}),
      "You can't see the ally from here but the doorway is to "+
      "the west.\n");
    add_item(({"floor", "flooring", "ground"}),
      "The floor is made of hardwood that is dark and quite scuffed "+
      "up with age.\n");
    add_item(({"ceiling", "up"}),
      "The ceiling is gray in colour without anything unusual or "+
      "out of the ordinary with it.\n");
    add_item(({"tables", "table"}),
      "These are nice round wooden tables with chairs placed around "+
      "them. Try <tablehelp> to learn more.\n");
    add_item(({"chair", "chairs"}),
      "There are plenty of wooden chairs for sitting in at the "+
      "tables. Try <tablehelp> to learn more.\n");
    add_item(({"fireplace"}),
      "The fireplace is in the southern wall and in a holder next "+
      "to it is an iron poker.\n");
    add_item(({"mantle", "fireplace mantle"}),
      "The mantle surrounding the fireplace is made of a gray stones.\n");
    add_item(({"fire", "flames"}),
      "The flames dance and spark along the burning logs like "+
      "a burning seduction. \n");
    add_item(({"log", "logs"}),
      "The logs are in a bin next to the fire place. You probably "+
      "could put a log on the fire if you wanted.\n");
    add_item(({"poker", "iron poker"}),
      "There is a cast iron poker resting in a small holder next to "+
      "the fireplace. This is used to stoke up the fire.\n");
    add_item(({"holder"}),
      "This holder is next to the fireplace and it has an iron "+
      "poker in it.\n");
    add_item(({"bin", "log bin", "wood bin", "storage bin"}),
      "This bin is filled with logs for the fireplace.\n");
    add_item(({"north", "northeast", "northwest", "southeast", "southwest"}),
      "There is a wall in that direction.\n");

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
    add_exit("pub", "east");
    add_exit("road_12_8", "west");
    set_tavern_name("Barley Mae's Private Dining");

//  add_tavern_drink("wine", "red", "red wine", "red wines", "This" +
//    " red wine is from tavern module.\n", 1200, 200, 50);
//  add_tavern_food("stew", "warm", "warm stew", "warm stews", "This" +
//    " warm stew is from tavern module.\n", 1000, 60);

    add_tavern_drink("/d/Khalakhor/se_speir/port/obj/milk");
    add_tavern_drink("/d/Khalakhor/se_speir/port/obj/coffee");
    add_tavern_drink("/d/Khalakhor/se_speir/port/obj/stea");
    add_tavern_drink("/d/Khalakhor/se_speir/port/obj/cocoa");
    add_tavern_drink("/d/Khalakhor/se_speir/port/obj/cmilk");
    add_tavern_drink("/d/Khalakhor/se_speir/port/obj/rwine");
    add_tavern_drink("/d/Khalakhor/se_speir/port/obj/lwine");
    add_tavern_drink("/d/Khalakhor/se_speir/port/obj/dale");

    add_tavern_food("/d/Khalakhor/se_speir/port/obj/corncake");
    add_tavern_food("/d/Khalakhor/se_speir/port/obj/eggs");
    add_tavern_food("/d/Khalakhor/se_speir/port/obj/beef");
    add_tavern_food("/d/Khalakhor/se_speir/port/obj/cmuffin");
    add_tavern_food("/d/Khalakhor/se_speir/port/obj/sham");
    add_tavern_food("/d/Khalakhor/se_speir/port/obj/eel");
    add_tavern_food("/d/Khalakhor/se_speir/port/obj/oyster");
    add_tavern_food("/d/Khalakhor/se_speir/port/obj/clams");
    add_tavern_food("/d/Khalakhor/se_speir/port/obj/sausage");
    
 //   add_tavern_wares(({
 //                     "/d/Khalakhor/se_speir/port/obj/bottle",
 //                     "/d/Khalakhor/se_speir/port/obj/tavern_key",
 //                    });

    set_tavern_waiter("/d/Khalakhor/se_speir/port/npc/barley");

    clone_object("/d/Khalakhor/se_speir/port/npc/barley")->move(this_object());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
    add_fail(({"southwest", "southeast", "northwest", "northeast", "north"}),
      "You walked into a wall.\n"+
      "OUCH! That's gotta hurt!\n");
    add_fail(({"south"}),
      "You have managed to fall straight into the fireplace by not "+
      "paying attention to where you were going!\n\n"+
      "You scream in agony as you suffer second degree burns, before "+
      "managing to stumble back from the fire.\n");

    config_default_trade();
}

void
reset_room () 
{
  ::reset_room();
  if (! barley) {
    barley = clone_object("/d/Khalakhor/se_speir/port/npc/barley");
    barley->move(this_object());
  }
}

void
init()
{
    ::init();
    init_tavern();
    init_table();
    init_fire();
}
