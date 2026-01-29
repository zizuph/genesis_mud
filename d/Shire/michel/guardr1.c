/* Change Log:
    Changed the hobbits and sausage so they loaded with
    the more modern add_object and add_npc functions,
    which will enable to room to reload the objects
    properly.
    Raymund, 7/27/20
    
*/

inherit "/d/Shire/room";
 
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
 
object ob, sausage;

void
reset_room()
{
 /*  if(!ob)
  {
   ob = clone_object(MICH_DIR +"npc/militia");
   ob->move(this_object());
   ob = clone_object(MICH_DIR +"npc/militia");
   ob->move(this_object());
 }
   if(!sausage)
   {
        sausage = clone_object(MICH_DIR + "obj/sausage");
        sausage->move(TO);
   }*/
}


void 
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   set_short("A lodging house");
   set_long("This lodging house in the town of Michel Delving is "+
   "used as a place for Bounders and Shirriffes to stay when not "+
   "out on patrol.  There are many beds here, but none of them seem "+
   "filled.  West will take you back to the street.\n");

   add_item(({"beds","bed"}),
   "The beds are all in a row, military style.  None of them look very "+
   "neat though.\n");
    add_object(MICH_DIR + "obj/sausage", 1);
    add_npc(MICH_DIR +"npc/militia", 2);
   add_prop(ROOM_I_INSIDE,1);
   add_exit(MICH_DIR + "gamroad2","west",0,2);
 
   reset_room();
 }

