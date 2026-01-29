inherit "/std/room";

#include <composite.h>
#include "chapel.h"
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>

void
create_room()
{
   set_short("Wedding chapel");
   
   set_long("   You step into a small chapel. The air around you is very "+
      "hushed, with only very soft music coming from the organist in "+
      "the corner. This chapel is lit by the sunlight streaming in "+
      "the large stained-glass windows which are set into the walls "+
      "which overlook the garden outside. The pews are set in two "+
      "rows, on either side of the wide aisle, set under the windows. "+
      "At the front of the room you can see the podium where the marriage "+
      "is officiated. An embroidered tapestry hangs on either side of the "+
      "podium.\n\n");
   
   add_item("organist","In one corner of the room you see a small organ "+
      "from which you can hear lovely music. The organist looks up at "+
      "you and smiles when she notices you looking her way.\n");
 
   add_item("podium", "The sturdy podium is made from a highly polished " +
       "wood, with two long crystal panels in the front.\n");

   add_item(({"panel","panels"}), "Rainbows dance across the panels as the light reflects off them.\n");
   add_item("wood","This is a highly polished wood from one of the many trees growing in the forest around the chapel.\n");
  
   add_item(({"tapestry","tapestries"}),"The tapestries are woven by the local elven women. "+
      "They are brilliantly hued and add a touch of festivity "+
      "to the chapel. They both depict laughing and singing and joy.\n");
   add_item(({"pews","pew","seats"}),"The seats are made from highly polished wood, similar to that of the podium.\n");
   add_item(({"wall","walls"}),"The walls are made of a whitewashed plaster. They look to have been textured with a rough cloth.\n");
   add_item(({"aisle","carpet"}),"The wide aisle is carpeted with a rich red carpet. The "+
      "carpet makes your steps soundless as you move on it.\n");
   add_item(({"windows","window","stained glass"}),"These windows are breathtakingly "+
      "beautiful. The scenes on them display the flora and fauna "+ 
      "of the area around the church.\n@@outside_window@@\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(CHAPEL_DIR + "rectory", "south");
}   


void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   set_alarm(2.0,0.0,"make_music",this_player());
}

int
is_chapel()
{
   return 1;
}

string
outside_window()
{
   object *out_there;
   object outside;
   
   if (!LOAD_ERR(CHAPEL_DIR+"outside")) 
      outside = find_object(CHAPEL_DIR+"outside");
   if (!outside)
      return "The windows are darkened and you can't see outside.";
   else
      {
      out_there  = FILTER_LIVE(all_inventory(outside));
      if (!sizeof(out_there))
         return "Outside, there is no one in the garden.";
      else
         return "Outside, through the windows you can see "+
      COMPOSITE_LIVE(FILTER_LIVE(all_inventory(outside)))+".";
   }
}

void
make_music(object ob)
{
   ob->catch_msg("The sound of beautiful music surrounds you as "+
      "you enter the chapel.\n");
}
