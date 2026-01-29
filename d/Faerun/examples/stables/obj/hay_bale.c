/*
* large bale of hay sold in Bree tack shop
* Palmer
* Jan, 2003
* Modified by Finwe, March 2004
 */

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Shire/sys/defs.h"

void
create_food()
{
    ::create_food();

    set_name(({"hay", "bale", "bale of hay"}));
    set_pname("bales of hay");
    set_adj("golden");
    set_short("bale of hay");
    set_pshort("bales of hay");
    set_long("This is a large bale of golden hay. It is sun dried and " +
        "something only a steed would love to eat.\n");
    set_amount(6000);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 2000);
}

init()
{
    ::init();
}
