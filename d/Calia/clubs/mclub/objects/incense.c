/* A quantity of incense which can be loaded into the censor in the
** sanctuary (rooms/shsanct) to create a cloud of incense (objects/incloud)
**
** HISTORY
** Date        Action
** ----------- ------------------------------
** 4/15/95     Created
**
**/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
create_object()
{
   set_name(({"incense",INCENSE_QTY}));
  set_adj("purplish");
  set_short("handful of purplish incense");
  set_pshort("handfuls of purplish incense");
  set_long(
     "It is a handful of incense, an aromatic purple ash.\n");
  add_prop(OBJ_I_VOLUME,10);
  add_prop(OBJ_I_WEIGHT,10);
  add_prop(OBJ_I_VALUE,0);
}
