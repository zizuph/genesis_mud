/*
** The ring of an Argosian Nobleman, House of Benedictus
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 11/12/94    Created
*
* Modified:
* - Carnak 2018-02-05: Ring used to be worn on BOTH left and right ring finger.
*                      Now worn on finger of choice.
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
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
