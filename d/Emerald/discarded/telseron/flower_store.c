inherit "/std/room";
inherit "/lib/store_support";
 
#include "/d/Emerald/defs.h"
 
int reset_room()
{
/*
int i;
object vase;
 
  for(i=0; i < 3; i++)
  {
    vase = clone_object(TOWNSHIP_DIR + "obj/l_vase");
    vase -> move(TO);
   }
*/
}
 
void
create_room()
{
    set_short("Cold room");
    set_long("   The storage room for flowers that are sold. Blocks " +
        "of ice are surround the room.\n");
 
    set_max_values(30, 3);
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TOWNSHIP_DIR + "flower_shop", "down", 0);
  reset_room();
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
