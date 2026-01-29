/*
 * scale_mail.c
 * Scale mail, worn by Ergothian guards
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
    set_name("mail");
    add_adj("scale");
    add_adj("shiny");
    add_name("shirt");
    set_short("shiny scale mail shirt");
    set_long("A well-polished shirt of scale mail.  This armour features "+
        "overlapping scales of metal, each riveted to the leather "+
        "layer underneath.\n");
    set_at(A_BODY);
    set_ac(19);
    add_prop(OBJ_I_VOLUME, 4500);
}
