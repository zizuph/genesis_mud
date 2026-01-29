/* Small covered altar - contents guarded by any manachs in room
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 5/30/98     Zima        Created
*/
#include "/d/Khalakhor/guilds/sean-rhian/defs.h"
inherit  SR_OBJ+"valtar";
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
 
void create_container()
{
  ::create_container();
  add_prop(CONT_M_NO_REM,"@@chk_guard");
   add_prop(CONT_M_NO_INS,"@@chk_guard");
}
 
mixed chk_guard()
{
   object monk=present(SR_NPC_ID,ENV(TO));
   object pend=present(SHAM_PENDANT,TP);
   if (objectp(monk) && (!objectp(pend)) && (!(TP->id(SR_NPC_ID))))
      return ("The "+(monk->short())+" prevents you from disturbing "+
              "the altar.\n");
   else
      return 0;
}
