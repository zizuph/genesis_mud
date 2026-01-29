inherit "/std/room";

#include "defs.h"
#include "/d/Shire/lib/herbsearch.c"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_room() {
   set_short("grassy field");
   set_long("@@my_long");

   add_item(({"bush","dense bush", "bushes", "dense bushes"}), break_string(
      "The dense bushes block the view of whatever is behind them. They "
    + "look like the bushes that commonly grow in the Shire.\n",70));

   add_item(({"grass","tall grass"}), break_string(
      "The grass is tall and green, a pleasure for the eye. There is "
    + "hardly any grass growing here.\n",70));

   /* Enable the searching for grass */
   add_prop(OBJ_I_SEARCH_TIME, 10);
   add_prop(OBJ_S_SEARCH_FUN, "herb_search");
   add_herb_file(STAND_HERB + "grass");

   add_prop(ROOM_I_INSIDE,0);

   // set_noshow_obvious(1);

   add_exit(STAND_DIR + "field2","south",0,1);
   add_exit(STAND_DIR + "camp1","east","@@check_enter",1,1);

    ("/d/Shire/common/hobbiton/camp1")->load_me();
}

my_long() {
   int sk;
   string str;

   sk = this_player()->query_skill(SS_AWARENESS);

   str = "Here the bushes are many, and the grasses are sparse "
       + "patches of tall grass. The grassy field is being forced aside "
       + "by dense bushes. The bushes seem to block all exits except south.";
   if (sk <= 15)
   {
      str = break_string(str + "\n", 70)
          + "There is one obvious exit: south.\n";
   }
   else
   {
      str += " However, to the east, behind the bushes, you notice some "
           + "sounds...";
      str = break_string(str + "\n", 70)
          + "There are two obvious exits: south, east.\n";
   }
   return str;
}

check_enter() {
   int sk;

   sk = this_player()->query_skill(SS_AWARENESS);

   if (sk <= 15)
   {
      write("There is no obvious exit east.\n");
      return 1;
   }
   else
   {
      write("You silently crawl east through the bushes.\n");
      say(QCTNAME(this_player()) + " silently crawls east through the bushes.\n");
      return 0;
   }
}

