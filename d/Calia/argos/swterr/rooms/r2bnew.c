/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A path through the forest");
   set_long(
       "A light breeze carries a distant pecking sound as you walk " +
       "along the path through the forest. You think it must be a " +
       "woodpecker, but the pitch is a little high for such. The " +
       "path seems a little more used here as it widens toward the "+
       "east.\n");
 
    add_item("path",
        "A narrow dirt path winding through the woods, it widens "  +
        "towards the east. You notice a thicket of underbrush piled "+
        "along its north side.\n");
    add_item(({"thicket","underbrush"}),
        "It is a large mound of brown, hardenend underbrush piled on the "+
        "north side of the path.\n");
    add_item(({"canopy","leaves"}),
        "The dense canopy of leaves provides a peaceful shade " +
        "as you walk along the winding path.\n");
    add_item("forest",
        "A mixture of maples, oaks and evergreens, the forest " +
        "surrounds you with its beautiful hardwoods. Wildflowers " +
        "sprout sporadically, searching for patches of sunlight " +
        "filtering through the canopy of leaves.\n");
    add_item(({"flowers","wildflowers"}),
        "Small white flowers on long leafy stems, they grow sporadically " +
        "on the shady floor of the forest.\n");
    add_item("leaves",
        "Some have fallen from the trees onto the path, and crunch under " +
        "your feet as you walk along.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r2a","west",0);
    add_exit("r2c","east",0);
}
 
int do_crawl(string parms) {
   string *p;
   if (!parms) return 0;
   p = explode(parms," ");
   if ((member_array("underbrush",p)>=0)||(member_array("thicket",p)>=0)) {
      write("You crawl through the thicket of underbrush.\n");
      this_player()->move_living("into the thicket of underbrush",
                                 "/d/Calia/clubs/mclub/rooms/path1");
      return 1;
   }
   return 0;
}
 
void init() {
   ::init();
   add_action(&do_crawl(), "crawl");
   add_action(&do_crawl(), "enter");
}
