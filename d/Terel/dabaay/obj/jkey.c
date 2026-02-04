/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * Jenglea's key. 
 * Goldberry January, 2000
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
    add_name("jenglea's key");
    set_short("blackened-steel key");
    set_pshort("blackened-steel keys");
    set_adj(({"blackened", "steel", "blackened-steel"}));
    set_long("It's a small steel key, that has been blackened.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, 0);
}
