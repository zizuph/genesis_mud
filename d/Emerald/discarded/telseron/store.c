inherit "/std/room";
inherit "/lib/store_support";
 
#include "/d/Emerald/defs.h"
 
int reset_room()
{
int i;
object torch;
 
/* directory no longer exists.
  for(i=0; i < 3; i++)
  {
    torch = clone_object(VILLAGE_DIR + "obj/largetorch");
    torch -> move(TO);
   }
*/
}
 
void
create_room()
{
    set_short("Stuffy store room");
    set_long("You are in the stuffy store room of the general store.\n");
 
    set_max_values(30, 3);
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TOWNSHIP_DIR + "shop", "down", 0);
  reset_room();
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
