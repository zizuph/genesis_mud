/* Player with this invisible has received the chosen revelation in the
** chapel (rooms/chapel)
**
** HISTORY
** Date        Action
** ----------- ------------------------------
** 2/1/95      Created
**
**/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
create_object()
{
  set_name(VDQ_REVELATION);
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
  add_prop(OBJ_I_VALUE,0);
  set_no_show(1); /* invisible to player */
  add_prop(OBJ_I_NO_DROP,1);
  add_prop(OBJ_I_NO_GIVE,1);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_M_NO_GIVE,1);
}
