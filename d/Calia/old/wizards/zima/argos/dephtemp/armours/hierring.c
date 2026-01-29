/*
** The ring of an Hierophant of Dephonia
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 12/10/94    Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_armour() {
    set_name("ring");
    set_adj(({"gold","jeweled"}));
    set_short("gold jeweled ring");
    set_long(
       "It is a gold ring made from the image of a raven, the tips " +
       "of its outstretched wings joined to encircle the finger. It is "+
       "encrusted with twelve brilliant diamonds.\n");
    set_ac(0);
    set_at(A_FINGERS);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  1000);
}
