/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object knife=0;
void
reset_room()
{
    if (knife) return;
    knife=clone_object(WEAPON_DIR+"ogknife");
    knife->move(THIS);
}
 
/* room definition */
void
create_room()
{
   set_short("An olive grower's dwelling");
   set_long(break_string(
       "You walk into the small dwelling of a local olive grower.  This one-" +
       "room hut is sparsely furnished with a bed and a table.  A keg sits " +
       "in a stand next to the door, and there is a " +
       "rock hearth on the northern wall with a small fire.  " +
       "A small grecian lamp sits on the mantle, its small flame " +
       "giving light to the room.  " +
       "A doorway " +
       "leads back out into the surrounding pasture.\n",70));
 
    add_prop(ROOM_I_INSIDE,1);
    add_item("bed",
             "A small bed covered with dirty blankets.\n");
    add_item("mantle", break_string(
             "A short wooden shelf nailed into the hearth over the fire.  " +
             "A grecian lamp sits on top.\n",70));
    add_item("lamp", break_string(
             "A bowl-shaped lamp, with a handle on one side and a wick " +
             "extension on the other.  The lamp is made of brass and is " +
             "lit sitting on the mantle above the fireplace.\n",70));
    add_item("keg", break_string(
       "A wooden barrel which is filled with olive oil, sometimes used " +
      "as fuel for the grecian lamps common in this area.\n",70));
    add_item("table", 
             "A table made of olive wood surrounded by four chairs.\n");
    add_item("hearth", break_string( 
             "A small fireplace made of stone, it takes up most of the " +
             "northern wall of the dwelling.  A small fire burns inside " +
             "it, giving a little warmth.  A grecian lamp sits on " +
             "on the hearth's mantle.\n",70));
 
 
    /* exits */
    add_exit(ROOM_DIR+"ogrove1","out",0);
    call_out("reset_room",1);
}
