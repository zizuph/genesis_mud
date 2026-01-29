
/*
 * scale_mail_greaves.c
 * Scale mail greavds, worn by Elite guards
 * Gulfport, Northern Ergoth
 * Tibbit, 22 May 1998
 *
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("greaves");
    add_adj("scale");
    add_adj("scalemail");
    add_adj("mail");
    set_short("pair of scale mail greaves");
    set_pshort("pairs of scale mail greaves");

    set_long("These protective greaves consist of steel "+
        "scales overlapping, secured to an underlying leayer of leather.\n");

    set_at(A_LEGS);
    set_ac(19);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 1000);

}

