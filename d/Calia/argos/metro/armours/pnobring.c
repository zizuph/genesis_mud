/*
** The ring of the noble house of Pistus (Loyal)
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 5/5/95      Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_armour() {
    set_name("ring");
    set_adj(({"silver","jeweled"}));
    set_short("gold jeweled ring");
    set_long(
       "It is an elegant silver ring with a large purple jewel. An "+
       "inscription around the jewel reads: ARGOS - HOUSE OF PISTUS.\n");
    set_ac(0);
    set_at(A_FINGERS);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,   50);
}
