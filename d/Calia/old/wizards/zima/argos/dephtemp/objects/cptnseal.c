/*
** A hall pass; given by the Captain of the Guard (rooms/captngrd)
** required to use stairwell (checked by guard) (rooms/stair1)
**
** HISTORY
** Date       Coder     Action
** ---------- --------- ----------------------------------
** 1/1/95     Zima      Created
*/
inherit "/std/object";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void
create_object()
{
     set_name(({"seal",CAPTNSEAL}));
    set_adj("silver");
    set_adj("small");
    set_short("small silver seal");
    set_long(break_string(
       "It is a small silver seal, more like a coin, which bears " +
       "a raven on one side and a shield with two crossed spears on the" +
       " other.\n",70));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 6);
}
