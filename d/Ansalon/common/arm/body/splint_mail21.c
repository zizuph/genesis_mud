/*
 * splint_mail.c
 * Splint mail, worn by Ergothian elites
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
    add_adj("splint");
    add_adj("shiny");
    add_name("shirt");
    set_short("shiny splint mail shirt");
    set_long("A well-polished shirt of splint mail.  This armour features "+
        "vertical strips of metal riveted to a strong leather backing "+
        "underneath.\n");
    set_at(A_BODY);
    set_ac(21);
    add_prop(OBJ_I_VOLUME, 4500);
}
