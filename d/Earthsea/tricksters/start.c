#include "defs.h"

inherit TRICKSTER_STD_ROOM;

void create_room()
{
 set_short("Cramped living quarters");
 set_long(BS(
   "This dim dark room has several lumpy sacks in the corners.  There "+
   "is a readable sign on the wall.  You can leave these cramped "+
   "quarters by going east.\n"));

 add_item(({"sack","sacks","lumpy sack","lumpy sacks"}),
   "These sacks look like places to sleep in, the lumpy ones appear "+
     "occupied.\n");
 add_cmd_item("sign","read","The sign reads: <start here>\n");

 add_exit(TRICKSTERS+"discuss","east");
}

void init()
{
 ::init();
 add_action("do_start","start");
}

int do_start(string where)
{
 NF("Say what?? Where da hell is "+where+"???\n");
 if(!where || where!="here") return 0;

 TP->set_default_start_location(TRICKSTERS+"start");
 write("From now and on you will awake in these halls\n");
 return 1;
}

