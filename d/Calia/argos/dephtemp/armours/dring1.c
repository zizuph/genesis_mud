/*
** The ring of an Dephonian Priest or Priestess - low level/value
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 12/10/94    Created
** 04/23/13    Fixed to work on any finger. (Gorboth)
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_armour() {
    set_name("ring");
    set_adj("silver");
    set_short("silver ring");
    set_long(
       "It is a silver ring made from the image of a raven, the tips " +
       "of its outstretched wings joined to encircle the finger. It is "+
       "not jeweled but still looks of value.\n");
    set_ac(0);
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  200);
}
