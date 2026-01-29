/*
 *   The storage room of the Michel Delvings butchery
 */
 
inherit "/d/Shire/room";
inherit "/lib/store_support";
 
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
 
#define MAX_REFRESH 10
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
 
void
create_room()
{
   set_short("Herbshop storage room");
   set_long(break_string(
      "You have entered the cold storage room of the butchery. "
    + "This is where the owner of the shop stores all his items that "
    + "are for sale. "
    + "You can steal whatever you want before anyone saw you. "
    + "The butcher is busy in the room nearby.\n",70));
 
   add_exit(MICH_DIR + "butchery","up");
 
   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
}
