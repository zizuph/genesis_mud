#include "defs.h"

inherit TRICKSTER_STD_ROOM;
inherit "/d/Genesis/lib/post";

void create_room()
{
 set_short("Trickster Post Office");
 set_long("This is tricksters post office. It has been placed in "+
   "rather big room with prety smooth walls. Total chaos is taking "+
   "place here. People , screaming loudly ,run in different directions "+
   "with some papers. Near the walls you see shelves with huge amount "+
   "of different letters and packages to be dispatched. On the eastern "+
   "wall you see a sign.\n");

 add_item("people","You try to catch one , but he breaks free from "+
   "your grasp and proceeds running. People appear to be very busy.\n");
 add_item(({"walls","wall"}),"Walls appear to be prety smooth. "+
   "Shelves are placed all around near walls.\n");
 add_item(({"shelf","shelves"}),"Shelves are placed near the walls. "+
   "They seem to be collapsing under the load of tons of latters "+
   "and packages placed on them and awaiting for a dispatch.\n");
 add_item(({"letters","packages"}),"Tons of latters and packages "+
   "are placed upon the shelves and awaiting for a dispatcher to "+
   "send them out to different destinations.\n");
 add_item("sign","It contains some important information. Read it.\n");

 add_cmd_item("sign","read","You can <mail council> and <mail "+
   "guildmaster> here.\n");

 add_exit(TRICKSTERS+"discuss","north");
}

void init()
{
 ::init();
 post_init();
}

void leave_inv(object ob, object to)
{
 ::leave_inv(ob,to);
 post_leave_inv(ob,to);
}

void add_aliases(object reader)
{
 reader->set_alias("council",(SERVER)->query_council());
 reader->set_alias("guildmaster",({(SERVER)->query_guildmaster()}));
}

