/**********************************************************************
 * - pub.c                                                          - *
 * - Created by Damaris 3/2001                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Updated by Valen   2/2002                                      - *
 * - Recoded by Damaris 3/2003                                      - *
 **********************************************************************/

#pragma strict_types

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/tavern";
inherit "/lib/trade.c";
#include "../defs.h"
#include "/d/Khalakhor/sys/basic.h"
#include "sitting.c"
#include <money.h>

#define NUM sizeof(MONEY_TYPES)

string
query_wood_sign()
{
    return(
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
      "          |              Sesha's nook              |\n"+
      "          |________________________________________|\n"+
      "          |                                        |\n"+
      "          | Look at the menu and sit at a table or |\n"+
      "          | at the bar. Take a load off and grab   |\n"+
      "          | some food and drink before you head    |\n"+
      "          | back out.                              |\n"+
      "          |                                        |\n"+
      "          | Drink or eat here or take it with you. |\n"+
      "          |                                        |\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
}

string
menustuff(void)
{
  action_tavern_menu("menu");
  return "";
}

public void
create_khalakhor_room()
{
    set_short("Sesha's nook");
    set_long("   This is a charming little nook in " +
      "the corner of the tree. It is filled with small green " +
      "vines that run along the length of the wall. Sesha is " +
      "happy to tend to your needs as she quietly inspects her " +
      "drinks and edible items. On the "+
      "bar itself there is a menu and a small wooden sign.\n");
    add_item(({"room", "area", "inn", "pub"}), query_long);
    add_item(({"bar stools", "stools", "stool", "bar stool", "chair", "chairs"}), seat_desc);
    add_my_desc(seat_desc, this_object());
    add_item(({"sign"}), query_wood_sign);
    add_cmd_item("sign","read", query_wood_sign);
    add_item("menu", menustuff);
    add_item(({"table", "tables", "wooden table", "wooden tables"}),
      "The wooden tables are scattered around the room.\n");
    add_item(({"walls", "wall"}),
      "The walls are simply made from bark and there is a "+
      "mysterious light emanating from it.\n");
    add_item(({"floor", "ground"}),
      "The floor on which you are standing seems very firm, and is " +
      "made from the tree. It appears the tree has grown limbs " +
      "intertwine just to create the floor.\n");
    add_item(({"bar"}),
      "It resembles a bar that has been made from the very limbs " +
      "of the tree.There is a menu and a sign on it.\n");
     add_item(({"ceiling"}),
      "The ceiling is made from intertwining limbs.\n");
    add_item(({"lattern", "latterns", "light"}),
      "There a few latterns scattered along the walls firmly attached.\n");
    set_tavern_name("Sesha's nook");

    add_tavern_drink(GOBJ + "cider");
    add_tavern_drink(GOBJ + "cocoa");
    add_tavern_drink(GOBJ + "rum");
    add_tavern_drink(GOBJ + "water");
    add_tavern_food(GOBJ + "biscuit");
    add_tavern_food(GOBJ + "muffin");
    add_tavern_food(GOBJ + "scone");
    add_tavern_food(GOBJ + "pheasant");
    add_tavern_food(GOBJ + "psoup");
    add_tavern_food(GOBJ + "pheasant");
    set_tavern_waiter(NPC + "sesha");
    clone_object(NPC + "sesha")->move(this_object());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);

    add_exit("tree", "west");
    add_fail("auto", "You walked into a wall!\n"+
      "Ouch! That's gotta hurt!\n");
      

    config_default_trade();
}

int
lay_bar(string str)
{
     if((str == "head on bar") || (str == "bar") || (str =="on bar"))
     {
       write("You lay your head on the bar for a moment.\n");

          /* This what others in room see. */
       say(QCTNAME(TP)+" lays "+HIS(TP)+" head on the bar for a moment.\n");
      return 1;
      }
      if((str == "head on table") || (str == "table") || (str =="on table"))
      {
       write("You lay your head on the table for a moment.\n");

                /* This what others in room see. */
       say(QCTNAME(TP)+" lays "+HIS(TP)+" head on the table for a moment.\n");
       return 1;
      }
   else
  {
   notify_fail("Lay what?\n");
   return 0;
  }

}
public void
init()
{
     ::init();
     init_tavern();
     init_seat();
     add_action(lay_bar, "lay");
     add_action(lay_bar, "rest");
}
