/* A dirty workbench
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 3/9/98      Zima         Created
**
*/
inherit "/std/container";
#include <stdproperties.h>
 
void create_container() {
    set_name("workbench");
    set_adj(({"long","crude","wooden","dirty"}));
    set_short("long wooden workbench");
    set_long(
       "It is a long wooden workbench, its top stained with spots "+
       "where things have been spilled on it.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}
