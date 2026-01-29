/* 
 * Apple crate for Finwe
 *
 * Varian, February 2020
 */

#pragma strict_types

inherit "/std/container";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

#define MAX_APPLES_CRATE    7
#define IS_WESTAPPLE        "_honeycrisp_apple"

public void
create_container()
{
    set_name("crate");
    add_name("_apple_crate");

    set_adj("square");
    add_adj( ({"wooden", "apple"}) );

    set_short("square wooden crate");
    set_long("This is a square wooden box. It is designed to " +
        "only hold certain large apples from the Westfarthing.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 6000);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_VOLUME, 3000);

    set_keep(1);
}

public int
prevent_enter(object obj)
{
    if(!obj->id(IS_WESTAPPLE))
    {
        write("You realize only apples from the Westfarthing can be " +
            "put into this crate.\n");
        return 1;
    }

    return 0;
}
