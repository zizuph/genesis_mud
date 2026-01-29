inherit "/std/book";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
/* by Korat.
 * This is a ruined map that will aid the player to find
 * a hidden entrance to the deep dwarven area
 */
void
create_book()
{
  set_name("map");
    set_adj("teared");
  set_long("It seems to be a map of somewhere. Sadly, most of "+
      "the map is ruined by humidity, making it not "+
      "worth much.\n");
   set_max_pages(1);
   add_prop(OBJ_I_VALUE, 10);
   set_keep();
}
varargs void
read_book_at_page(int which, string verb)
{
   switch(which)
   {
      case 1:
      TP->more("/d/Kalad/common/wild/pass/citadel/quest_map",1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
      break;
   }
}
