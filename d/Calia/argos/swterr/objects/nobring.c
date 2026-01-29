/*
** The ring of an Argosian Nobleman, House of Benedictus
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 11/12/94    Created
** 04/17/14    Fixed to use A_ANY_FINGER (Gorboth)
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void
create_armour()
{
    set_name("ring");
    set_adj("gold");
    set_adj("noblemans");
    set_adj("argosian");
    set_short("argosian noblemans ring");
    set_long(break_string(
       "It is a gold ring, worn by a nobleman of Argos. It is crafted " +
       "with a winged horse flying with her foal, encirled in lettering " +
       "reading: Benedictus.\n",70));
    set_ac(0);
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
