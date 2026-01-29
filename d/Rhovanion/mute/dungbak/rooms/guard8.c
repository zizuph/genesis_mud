inherit "/std/room";
inherit "/lib/pub";
inherit "/lib/trade";

#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#include <language.h>
#include <ss_types.h>
create_room() {
   int i;
   set_short("rufus\n");
   set_long("You have just entered a very large room of large, " +
      "stone blocks filled with stone tables and wooden " +
      "chairs, benches and casks, and stools by what " +
      "appears to be a bar.  The place is filled with the raucous " +
      "banter of its patrons, and it reaks of spirits.\n");
   add_prop(ROOM_I_INSIDE,1);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item(({"table","tables"}),"These are light, stone " +
      "tables varying in size and shape from small and round " +
      "to long and rectangular.  They are spread out haphazardly " +
      "about the room.\n");
   add_item(({"chair","chairs"}),"These poorly crafted " +
      "wooden objects barely qualify as chairs however you " +
      "can sit in them.\n");
   add_item(({"bench","benches"}),"These are poorly " +
      "crafted, wooden benches lining the walls.\n");
   add_item(({"cask","casks"}),"These large, wooden " +
      "barrels are stacked up in various places along the " +
      "walls and are probably filled with some alcoholic " +
      "beverage no doubt.\n");
   add_item(({"stool","stools"}),"These extremely " +
      "poorly crafted, wooden stools look barely able " +
      "to support your weight.\n");
   add_item("bar","This is a long bar, set against the " +
      "entirety of the north wall constructed of stone but " +
      "with a solid wood top.  A foul looking, reptilian " +
      "wyrmman bartender stands behind it serving `customers'." +
      "Also behind the bar hangs a sign.\n");
   add_item("bartender","This ugly wyrmman serves the " +
      "other wyrmman who frequent this room at a tidy profit. " +
      "He'll no doubt serve you as well!\n");
   add_item("sign","The sign bears writing of a " +
      "foreign dialect.  Perhaps if you are well-versed " +
      "enough you may read it.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/guard21","south");
   
   config_default_trade();
   add_drink(({"chang-er grog","grog"}),"grog","chang-er",
      50, 10, 144, "mug of chang-er grog","mugs of chang-er grog",
      BS("This putrid, grey mess smells of some sort of foul reptilian " +
         "odour and is almost chunky looking.\n"), 0);
   add_drink(({"meat wine","wine"}),"wine","meat",
      150, 45, 288, "mug of meat wine","mugs of meat wine",
      BS("This dank, off red colored drink reaks of rotten " +
         "flesh.  Who knows what it was fermented off of.\n"), 0);
   add_food(({"black bread","bread"}),"bread","black",30, 72,
      "loaf of black bread","loaves of black bread",
      BS("This is a loaf of black bread.  It has an odd, strong " +
         "flavor about it.\n"),0);
   add_food(({"boar intestines","intestines"}),"intestines","boar",
      50, 108,"bowl of boar intestines","bowls of boar intestines",
      BS("This is a bowl of boiled boar intestines simmering in " +
         "its own juices.\n"),0);
   for (i = 0; i < 5; i++)
   clone_object("/d/Rhovanion/mute/dungeon1/wguard9.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wguard10.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wbarmaid.c")->move(TO);
}
init()
{
   ::init();
   init_pub();
   add_action("do_read","read",0);
}
do_read(str)
{
   notify_fail("Read what?\n");
   if (!str)
      return 0;
   if (str != "sign")
      return 0;
   if (this_player()->query_skill(SS_LANGUAGE) <=20)
      {
      write("You don't understand what it says.\n");
      say(QCTNAME(this_player()) + " smells his finger.\n");
      return 1;
   }
   {
      write(price_long());
      return 1;
   }
}
price_long() {
   return ("The sign says:\n\n"
      + "     Chang-er Grog  -  12 silver\n"
      + "     Meat Wine      -  24 silver\n"
      + "     Black Bread    -   6 silver\n"
      + "     Boar Intestines-   9 silver\n\n");
}
