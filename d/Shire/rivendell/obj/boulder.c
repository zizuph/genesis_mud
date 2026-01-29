/*
 * Boulder at west end of ford of Bruinen. Players may 
 * search it for herbs.
 * By Finwe, September 2000
 */

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/defs.h"
#include "local.h"
inherit "/std/object";
#include <stdproperties.h>


void
create_object()
{
    set_name("boulder");
    set_adj(({"large", "moss covered"}));
    set_long("The boulder is half buried in the ground. Its " +
        "jagged features are testament that it probably was " +
        "part of the mountain at one time. Pockets of earth " +
        "have accumulated on it and a velvet green moss covers " +
        "the shaded areas of the boulder.\n");
    add_item(({"earth", "pockets of earth"}),
        "They are shallow areas on the boulder full of " +
        "accumulated earth. Small, stunted trees and plants " +
        "grow in the pockets.\n");

//This boulder is too large to take and sell.
    add_prop(OBJ_I_VALUE, 0 );
    add_prop(OBJ_I_WEIGHT, 10000000);
    add_prop(OBJ_I_VOLUME, 3999999);

}
