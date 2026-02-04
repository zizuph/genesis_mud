/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * A bronze key. Goldberry June 8, 1999
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
    set_short("bronze key");
    set_pshort("bronze keys");
    set_adj(({"bronze", "small"}));
    set_long("It's a small bronze key.\n");

    add_prop(OBJ_I_VALUE, 0);
}
