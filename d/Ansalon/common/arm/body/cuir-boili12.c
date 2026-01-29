
/*
 * cuir-boili.c
 * Cuir-boili armor, worm by ogres in
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
    set_name("cuir-boili");
    set_adj("cuir-boili");
    add_name("shirt");
    set_short("cuir-boili shirt");
    set_long("This is a large-sized shirt of armour, made from leather "+
        "which has been boiled in oil and toughened.\n");
    set_at(A_BODY);
    set_ac(12);
    add_prop(OBJ_I_VOLUME, 4600);
}
