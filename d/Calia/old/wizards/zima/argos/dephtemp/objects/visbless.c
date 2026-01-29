/* Blessing of Dephonia - invisible object
**
** In the Vision Quest, the player must be wearing the robe and the
** medallion, and must be poisoned by the "blessed wine", then he
** must pray in the chapel (rooms/chapel) the prayer designated
** for him/her (see rooms/chapel). He/she then receives this "blessing"
** for saying the prayer in the proper state.
**
** Having this blessing object (along with the robe and medallion)
** allows him/her to take the ceremonial dagger in the sacristry
** (rooms/sacris) which is needed for the next step
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
  set_name(VDQ_BLESSING);
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
  add_prop(OBJ_I_VALUE,0);
  set_no_show(1); /* invisible to player */
  add_prop(OBJ_I_NO_DROP,1);
  add_prop(OBJ_I_NO_GIVE,1);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_M_NO_GIVE,1);
}
