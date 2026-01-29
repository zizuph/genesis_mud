/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object bucket=0;
int BASIN_FULL=0;
 
void
reset_room () {
    object room;
    room=this_object();
    if (!(bucket)) {
       bucket=clone_object(OBJ_DIR+"bucket");
       bucket->move(room);
    }
}
 
/* room definition */
void
create_room()
{
   set_short("A shepherd's dwelling");
   set_long(break_string(
       "You walk into the small dwelling of a local shepherd.  This one-" +
       "room hut is sparsely furnished with a bed, a table, and a stand, " +
       "on top of which you see a basin of water.  There is also a " +
       "rock hearth on the northern wall with a small fire.  A doorway " +
       "leads back out into the surrounding pasture.\n",70));
 
    add_item("bed", break_string(
       "Barely large enough for two people, it has a simple wooden frame " +
       "and is covered with old blankets.\n",70));
 
    add_item("water into basin","What?\n");
    add_cmd_item("water into basin","pour","@@pour_water");
    add_item("water in basin","What?\n");
    add_cmd_item("water in basin","pour","@@pour_water");
 
    add_item("blankets", break_string(
             "They are handwoven wool blankets of no special design. " +
             "They are tossed carelessly on the bed.\n",70));
 
    add_item("fire", break_string(
             "The small fire burns in the hearth, giving a comforting " +
             "warmth to the room.\n",70));
 
    add_item("table", break_string(
             "A sturdy oak table surrounded by four chairs.  There are " +
             "some dishes sitting on it.\n",70));
    add_item("dishes", "A dirty plate and cup sit on the table.\n");
    add_item("stand", break_string(
             "The only piece of furniture that might have some value, " +
             "this simple but elegantly crafted stand is made of oak " +
             "and sits by the door. There is a water basin sitting on " +
             "top of it, and a piece of soap hanging on it from a " +
             "rope.\n",70));
    add_item("feet","@@exa_feet");
    add_cmd_item("feet","wash","@@wash_feet");
    add_item("soap", break_string(
             "It is a piece of home-made soap, made from boiling animal " +
             "fat with some flowers for fragrance. It is attatched to " +
             "the stand with a short piece of rope.\n",70));
    add_item("rope",
             "It has a piece of soap on it and is tied to the stand.\n");
    add_cmd_item("rope","untie","@@untie_rope");
    add_item("basin",break_string(
             "It is a large ceramic bowl, decorated with painted leaves, " +
             "sitting on the stand. "+
             "@@basin_desc",70));
    add_item("hearth", break_string(
             "A small fireplace made of stone, it takes up most of the " +
             "northern wall of the dwelling.  A small fire burns inside " +
             "it, giving a little warmth.\n",70));
 
    add_prop(ROOM_I_INSIDE,1);
 
    /* exits */
    add_exit(ROOM_DIR+"past1","out",0);
    reset_room();
}
 
string
exa_feet() {
   if (present("DUNG_OBJ",this_player()))
      return break_string("Your feet are covered in sheep dung. You wish " +
                          "you could wash them.\n",70);
   else
      return "You look at your feet. You notice nothing special.\n";
}
 
int
wash_feet() {
   object dung;
   dung=present("DUNG_OBJ",this_player());
 
   if (BASIN_FULL) {
      if (dung) {
         dung->remove_object();
         BASIN_FULL=0;
         write(break_string(
            "You wash the dung from your feet in the basin using the " +
            "soap, and throw the dirty water out the door.\n",70));
      }
      else
         write(break_string(
            "Your feet are already pretty clean. At least they don't "+
            "stink too much.\n",70));
   }
   else
      write("There is no water in the basin.\n");
   return 1;
}
 
string
basin_desc() {
   if (BASIN_FULL) return "It is full of water.\n";
   else            return "It is empty.\n";
}
 
int
untie_rope() {
   write("You try to untie the rope but the know is too tight.\n");
   return 1;
}

int
pour_water() {
   object sbucket;
   sbucket=present("_argos_shepherds_bucket",this_player());
   if (sbucket) {
      if (sbucket->query_prop("_argos_shepherds_bucket_full")) {
         sbucket->add_prop("_argos_shepherds_bucket_full",0);
         BASIN_FULL = 1;
         write("You pour the water from the bucket into the basin.\n");
      }
      else write("The bucket is empty.\n");
   }
   else write("You don't have any water.\n");
   return 1;
}
