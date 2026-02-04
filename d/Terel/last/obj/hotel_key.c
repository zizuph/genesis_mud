/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * An iron key. Mortricia 920929
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/key";


/*
 * Function name: create_key
 * Description:   Sets default names and id
 */
create_key()
{
    ::create_key();

    set_name("key");
    set_pname("keys");
    set_short("iron key");
    set_pshort("iron keys");
    set_adj(({"iron", "small"}));
    set_long("It's a small iron key.\n");

    add_prop(OBJ_I_VALUE, 0);
}
