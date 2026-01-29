/*
 *  The Hobbiton Pub
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/pub";
inherit "/lib/trade";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define MY_PRICES ({ 8, 12, 35, 63 })

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("The Green Dragon");
   set_long("You are inside The Green Dragon. This is where the bashed up "
    + "adventurers come to drink away their sorrows and forget their pains. "
    + "The pub has been decorated with dark blue wallpaper and smells like "
    + "booze. There are several tables here with chairs beside them. On the "
    + "floor lies a once red rug, which is now covered with dirt and ashes. "
    + "The place is lit by several candles. Before the south wall is a "
    + "counter, behind which the bartender is. Behind him is a "
    + "pricelist.\n");

   add_item(({"rug","red rug"}),
      "The rug was once beautiful and red, but now it is ugly and grey.\n");

   add_item(({"table","tables","chair","chairs"}),
      "All the tables and chairs are taken by other hobbits.\n");

   add_item(({"wallpaper", "blue wallpaper", "dark blue wallpaper"}),
      "You notice nothing special about the dark blue wallpaper.\n");

   add_item("counter", 
      "Above the wooden counter are some candles and a shelf. On the shelf "
    + "are several brands of liquor. Behind the counter is the barkeeper of "
    + "this establishment.\n");

   add_item(({"barkeeper","bartender", "brugan"}), 
      "The barkeeper, Brugan, is a hobbit with a big belly. He seldom puts "
    + "down his wiping cloth, trying to keep the glasses as shiny as "
    + "possible. Brugan looks at you, waiting for you to order "
    + "something.\n");

   add_item(({"pricelist","list","prices"}), "@@price_long");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   add_exit(STAND_DIR + "bw_road4", "north", 0);

   /* Set up the trading system */
   config_default_trade();
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,   1,    3 })); /* Max_pay   */
   set_money_give_reduce(({     0,     4,   0,    6 })); /* Threshold */

   add_drink(({"ginger ale","ale"}),"ale","ginger",90,1,MY_PRICES[0],
             "glass of ginger ale", "glasses of ginger ale",
             "The ginger ale has a pink colour and smells like "
                + "beer mixed with a lot of water.\n", 0);
   add_drink(({"pint","beer"}),({"pint","beer"}),"prime",110,33,MY_PRICES[1],
             "pint of prime beer", "pints of prime beer",
             "The prime beer is of prime quality. It was brewn "
                + "in and imported from an Elven village in Grey Havens.\n",
             0);
   add_drink("wine", "wine", "red", 70, 62, MY_PRICES[2],
             "glass of red wine", "glasses of red wine",
             "The sparkling red colour of the wine comes from "
                + "the riped grapes that were harvested on the land of the "
                + "Tooks some years ago.\n", 0);
   add_drink("whiskey", "whiskey", "dry", 40, 84, MY_PRICES[3],
             "glass of dry whiskey", "glasses of dry whiskey",
             "The dry whiskey is a bit warm and has a strong "
                + "smell to it. It was distilled by the Brandybucks of the "
                + "West-farthing.\n",0);
   reset_room();
}

reset_room() {
   if (!present("go_board"))
      clone_object(STAND_DIR + "go_board")->move(this_object());
   if (!present("go_rules"))
      clone_object(STAND_DIR + "go_rules")->move(this_object());
   if (!present("go_player"))
      clone_object(STAND_DIR + "go_player")->move(this_object());
}

init() {
   ::init();
   init_pub();
   add_action("do_read","read",0);
}

do_read(str) {
   if (!str || str == "")
      return 0;
   if (str == "pricelist" || str == "list" || str == "prices")
   {
      write(price_long());
      return 1;
   }
   return 0;
}

price_long() {
   return (
      "The pricelist reads:\n\n"
    + "   Ginger ale      ...   " + MY_PRICES[0] + " copper coins\n"
    + "   Beer            ...  " + MY_PRICES[1] + " copper coins\n"
    + "   Wine            ...  " + MY_PRICES[2] + " copper coins\n"
    + "   Whiskey         ...  " + MY_PRICES[3] + " copper coins\n\n");
}

