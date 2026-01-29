inherit "/d/Shire/room";
 
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
 
object ob;
 
create_room() {
   set_short("The guards room");
   set_long("You are staying inside a small room where local \n" +
        "militia hobbits are resting and storing their weapons. \n" +
        "There are few benches and a wooden table in the center " +
        "of the room. \n");
 
    add_item("benches","There are three ordinary looking " +
    "wooden benches. \n");
 
    add_item("table","This is a big wooden table with some snack \n"
       + "laying on it. The guards are eating and drinking whenever \n" +
            "they feel they are hungry. \n");
   add_prop(ROOM_I_INSIDE,1);
   add_exit("/d/Shire/common/greyhaven/md2","east",0,2);
 
   reset_room();
 }
reset_room() {
   if(!ob) {
   ob = clone_object(MICH_DIR +"npc/militia");
   ob->move(this_object());
   ob = clone_object(MICH_DIR +"npc/militia");
   ob->move(this_object());
} }
