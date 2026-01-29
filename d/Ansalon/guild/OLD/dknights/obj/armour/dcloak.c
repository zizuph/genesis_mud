/******************************************************
 *  Black cloak for The Death Knights of Krynn        *
 *  By Elmore, April - 2001                           *
 ******************************************************/

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../../local.h"

void
create_armour()
{
    set_name("cloak");
    add_name(DKNIGHT_ARMOUR);
    set_ac(5);
    set_at(A_ROBE);
    set_am( ({ 10, 10, 3 }) );
    set_adj("black");
    add_adj("shredded");
    set_short("shredded black cloak");
    set_long("This shredded cloak, has been made from some of the "+
      "finest silk that can be found in Krynn. However "+
      "fire and age has shredded the edges this one. Due to "+
      "the high quality of the silk, it still looks quite "+
      "protective though.\n");    

    add_prop(OBJ_I_VOLUME, 1050);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(4, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4));
}
