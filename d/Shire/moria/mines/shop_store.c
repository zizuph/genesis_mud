/*
 *   The storage room of the Bree drugstore
 */

#include "defs.h"
#include "/sys/stdproperties.h"

inherit "/lib/store_support";

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_room() {
    set_short("Ugluk's storage room");
    set_long(
      "You have entered the dusty storage room of Ugluk's new "
      + "shop. This is where the shopkeeper keeps all his items that "
      + "are for sale in the store. "
      + "You better leave the stuff here alone, or else the shopkeeper "
      + "will be upset with you.\n");

    add_exit(THIS_DIR + "shop","south");

    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    reset_room();
}

#define INSERT(fil) clone_object(MORIA_DIR + fil)->move(TO)

reset_room() {
    if (!present("torch"))
	INSERT("obj/torch");
    if (!present("sack"))
	INSERT("obj/lootsack");
    if (!present("meat"))
	INSERT("obj/orcmeat");
}
