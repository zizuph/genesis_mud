/*  Armour coded by Arren, June 93 */

inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

create_armour()
{
    set_name("coat of mail");
    add_name(({"mail", "chainmail"}));
    set_adj("burnished");
    add_adj("Rohirrim");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_short("burnished coat of mail");
    set_pshort("coats of mail");
    set_long(BSN("This is a burnished chainmail, reaching almost down to "+
    "the knees. A vent from the knees to the waist "+
    "in the front divides the skirt to make riding possible."));

    set_af(TO);
    set_default_armour(25, A_TORSO | A_ARMS, ({-2,3,-1}), 0);

    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 11400);
    add_prop(OBJ_I_VOLUME, 4600);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35)+random(200)-100);
}

wear(object ob)
{
    write("You wear the " + query_short(TO) + " on your arms and "+
    "shoulders.\n");
    say(QCTNAME(TP) + " wears the " + query_short(TO) + ".\n");
    return 1;
}
