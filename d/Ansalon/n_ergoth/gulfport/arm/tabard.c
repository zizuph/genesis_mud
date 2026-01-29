
/*
 * tabard.c
 * A tabard bearing the arms of Ergoth
 * City of Gulfport, Northern Ergoth
 * Created by Tibbit, 2 May 1998
 *
 */

inherit "/std/armour";

#include "../local.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("tabard");
    set_adj("ergoth");
    add_adj("red");
    add_adj("ergothian");
    add_adj("army"); 

    set_short("red tabard of the Ergothian army bearing "+
        "the arms of Ergoth");
    set_pshort("red tabards of the Ergothian army each "+
        "bearing the arms of Ergoth");

    set_long("This red, thigh-length tabard is "+
        "of the kind worn by soldiers in the Ergothian "+
        "army.  It bears to the arms of Ergoth, to whit: "+
        "Gules, a sword in bend argent, in base a crown "+
        "embattled Or; that is, a white sword placed "+
        "diagonally with the tip in the top-left "+
        "(as you face the tabard), and a golden crown "+
        "beneath the sword, with an embattled edge "+
        "such as might be seen on a castle wall.  "+
        "The tabard is made from heavy cloth, "+
        "for purposes of durability."+
        "\n");

    set_at(A_ROBE);
    set_ac(3);

    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3,A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));

}

