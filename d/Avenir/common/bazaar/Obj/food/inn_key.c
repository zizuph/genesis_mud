// file name: /d/Avenir/common/bazaar/Obj/misc/inn_key.c
// creator(s): Ilyian, May 17, 1995
// last update: Lucius, Jan 2005: Updated to work with
// 		the inn having been moved to the port.
// purpose: Room key for the Dancing Potato Inn
// note:
// bug(s):
// to-do:

inherit "/std/key";

#include <stdproperties.h>

public void
create_key(void)
{
    ::create_key();

    set_name("key");
    add_name(({"inn_key", "port_inn_key"}), 1);
    set_pname("keys");
    set_short("small brass key");
    set_pshort("small brass keys");
    set_adj(({"brass", "small"}));
    set_long("It is a tiny brass key, although it dosen't appear "+
             "to be the type that would fit in any lock. Engraved in "+
             "tiny letters along it is: 'the Stormy Haven Inn'.\n");

    add_prop(OBJ_I_VALUE, 60);
}

