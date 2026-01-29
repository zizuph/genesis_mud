inherit "/std/room";

#include <stdproperties.h>
#include "/d/Avenir/common/dark/dark.h"

init()
{
   ::init();
   add_action("do_crawl","crawl");
}

void
create_room()
{
   set_short("very low tunnel");
   set_long("The tunnel ceiling dips even further here, and"
         +" the passage abruptly ends, leaving only a small hole in the north"
         +" wall.  The tunnel widens out to the south.\n");
   
   add_item(({"hole","small hole"}), break_string("The hole is much too"
         +" tiny for anyone to walk through.  However, it might be"
         +" possible to crawl northward through it.\n",75));

   add_exit (L4 + "cr02", "south", 0);
   add_prop(ROOM_I_LIGHT,0);
IN
   
}

int
do_crawl(string str)
{

  int i;
  object *inv;
  
  notify_fail("Crawl where?\n");
   
  if (str != "north" && str != "northward" && str != "northwards")
    return 0;
  
  notify_fail ("You are too burdened to crawl into that hole.\n");
  // make sure player has nothing worn and wielded
  // guild and quest items do not count(they're undroppable)
  inv = all_inventory( this_player() );
  
  for ( i = 0 ; i < sizeof (inv); i++ )
    if (!inv[i]->query_prop(OBJ_M_NO_DROP) &&
	(inv[i]->query_wielded() || inv[i]->query_worn()))
      return 0;

  write("You squeeze your way into the hole and crawl to the north.\n");
  say(QCTNAME(this_player())+" crawls north.\n");
  this_player()->move_living("north","/d/Avenir/common/dark/l4/s2", 1);
  return 1;
}
