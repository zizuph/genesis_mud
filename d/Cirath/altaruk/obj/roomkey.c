/* roomkey.c: Key to room above the bootmakers shop in
 * Altaruk.
 */

inherit "/std/object";
#include "../defs.h"

void
create_object()
{
    set_short("room key");
    set_long("The key is made from bone with a tiny boot" +
             " attached. It's for the room that Lorian the"+
             " boot maker rents out.\n");
    set_adj("room");
    set_name("key");
    add_name("_altaruk_room_key_");
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 5);
}
