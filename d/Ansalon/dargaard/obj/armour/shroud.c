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
    set_name("shroud");
    add_name("cloak");
    set_ac(10);
    set_at(A_ROBE);
    set_am( ({ 20, 10, 0 }) );
    set_adj("death");
    add_adj("shredded");
    set_short("shredded death shroud");
    set_long("Made from fine white silk, this shroud once covered the "+
             "bodies of the dead. The original color has gradually "+
             "changed from white to gray. The sides of the shroud has "+
             "been shredded and an iron brooch connects two of the "+
             "sides together making a a crude cloak.\n");    
    add_prop(OBJ_I_VOLUME, 666);
    add_prop(OBJ_I_WEIGHT, 666);
    add_prop(OBJ_I_VALUE, 100);
}

