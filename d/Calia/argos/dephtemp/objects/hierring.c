/*
** The ring of the Hierophant
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 1/1/95      Created
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
    set_adj("raven");
    set_adj("silver");
    set_adj("jeweled");
    set_short("jeweled raven ring");
    set_long(break_string(
       "It is a silver ring made from the image of a raven, the tips " +
       "of its outstretched wings joined to encircle the finger. It "+
       "is encrusted with precious rubies.\n",70));
    set_ac(0);
    set_at(A_FINGERS);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 520);  /* she is hard to kill...make it worth it*/
}
