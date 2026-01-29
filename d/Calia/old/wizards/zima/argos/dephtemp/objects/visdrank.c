/* Drank from the bowl invisible object
**
** In the Vision Quest, the player must drink from the silver bowl
** in rooms/sanct. This object is added to the player to indicate
** that he/she has done this action. This object is required for the
** player to make the chant which is the last step of the quest.
**
** HISTORY
** Date        Action
** ----------- ------------------------------
** 1/1/95      Created
**
**/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
create_object()
{
  set_name(VDQ_DRANK_OBJ);
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
  add_prop(OBJ_I_VALUE,0);
  set_no_show(1); /* invisible to player */
  add_prop(OBJ_I_NO_DROP,1);
  add_prop(OBJ_I_NO_GIVE,1);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_M_NO_GIVE,1);
}
