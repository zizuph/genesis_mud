
inherit "/std/room";

#include <stdproperties.h>
#include "/d/Avenir/common/dark/dark.h"

void
init()
{
   ::init();
   add_action("do_crawl","crawl");
}

void
create_room()
{
   set_short("Very low tunnel");
   set_long("The tunnel ceiling dips even further here, and"
         +" the passage abruptly ends, leaving only a small hole in the south"
         +" wall. The tunnel widens out to the north.\n");
   
   add_exit("/d/Avenir/common/dark/l4/s1","north",0);
   
   add_item(({"hole","small hole"}), break_string("The hole is much too"
         +" tiny for anyone to walk through.  However, it might be"
         +" possible to crawl southward through it.\n",75));

   AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
	  "passageway"}), "Very uninteresting stone in general, however "+
      "the south wall has a hole leading into darkness.\n");
   
   add_prop(ROOM_I_LIGHT,0);
   IN
   
 }

do_crawl(string str)
{

  int i;
  object *inv;
  
  notify_fail("Crawl where?\n");
   
   if (str != "south" && str != "southward" && str != "southwards")
     return 0;

  notify_fail ("You are too burdened to crawl into that hole.\n");
  // make sure player has nothing worn and wielded
  // guild and quest items do not count(they're undroppable)
  inv = all_inventory( this_player() );
  
  for ( i = 0 ; i < sizeof (inv); i++ )
    if (!inv[i]->query_prop(OBJ_M_NO_DROP) &&
	(inv[i]->query_wielded() || inv[i]->query_worn()))
      return 0;

  write("You squeeze your way into the hole and crawl to the south.\n");
  say(QCTNAME(this_player())+" crawls south.\n");
  this_player()->move_living("south","/d/Avenir/common/dark/l4/s3", 1);
  return 1;

}





