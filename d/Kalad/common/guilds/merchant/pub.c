inherit "/d/Kalad/room_std";
inherit "/lib/pub";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
void
create_room()
{
   ::create_room();
set_short("The private pub of the Merchants Guild of Kabal");
   set_long("You are within the stone building.\n"+
      "Inside you can see a common area, where travellers may rest from "+
      "their journeys and perhaps grab a bite to eat or drink. In the far "+
      "corner is a polished wooden counter. Behind and above the counter is "+
      "a large menu. In the corner a flight of stairs leads up.\n");
   add_item(({"counter"}),
      "This countertop looks like its been lovingly polished and shined by "+
      "someone. It's so clean and shiny you can see your image reflected "+
      "from it.\n");
   add_item(({"stairs"}),
      "A wooden staircase that winds its way up to the second floor of the "+
      "inn.\n");
   add_item(({"corner"}),"It is dark and filled with shadows.\n");
   add_item(({"menu"}),"It is written in a flowing script, perhaps you "+
      "should read it?\n");
   add_cmd_item("menu", "read", "@@read");
add_exit(CVAN(guild/hall2),"west",0,-1,-1);
   INSIDE;
   add_drink(({"beer", "beers", "kabal", "kabal beer"}),
      "beer", "kabal", 125, 10, 24, 0, 0,
      "A local drink, its what most of the regulars order.\n", 0);
   add_drink(({"wine", "wines", "ruby", "ruby wine"}),
      "wine", "ruby", 250, 30, 120, 0, 0,
      "A ruby-colored wine that sparkles in the sunlight.\n", 0);
   add_food(({"orange", "oranges"}),
      "orange", "juicy", 30, 30, 0, 0,
      "A freshly-picked orange, it looks quite appetizing.\n", 0);
   add_food(({"steak", "steaks"}),
      "steak", "grilled", 270, 180, 0, 0,
      "A thick juicy steak, fresh from the grill.\n", 0);
   add_food(({"chicken", "roasted chicken", "roast"}),
      "chicken", "roast", 150, 150, 0, 0,
      "A sumptious-looking roast. Its smell is quite pleasing.\n", 0);
   ob1 = clone_object("/d/Kalad/common/caravan/shop/jeik");
   ob1 -> move_living("xxx", TO);
   set_alarm(1.0,0.0,"reset_room");
}
void
init()
{
   ::init();
   init_pub();
}
int
read(string str)
{
   write("" +
      "   Kabal beer               24cc\n" +
      "   Ruby wine               120cc\n" +
      "   An orange                30cc\n" +
      "   Grilled steak           180cc\n"+
      "   Roasted chicken         150cc\n\n" +
      "If you type 'buy 10 beer' you can get 10 beers at once, you\n" +
      "could even type 'buy 15 beer'!\n");
   return 1;
}
block()
{
   if(!(present("hej_tjop_biljett",TP)))
      {
      write("You don't have a ticket!\n");
      return 1;
   }
   return 0;
}
