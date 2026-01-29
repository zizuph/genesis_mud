/* Altar of a village kirk
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/9/98      Zima        Created
** 3/7/98      Zima        Converted to ON container
**
*/
inherit "/std/container";
#include <stdproperties.h>
#include "defs.h"
 
void create_container() {
    set_name("altar");
    set_adj("wooden");
    set_short("altar");
    set_long(
       "It is a wooden altar with a pedestal base, ornately carved with "+
       "angels and shamrocks around its border. Three interlocked circles "+
       "are set in its center. Its surface gleams as if it has been well "+
       "polished over the years.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}
