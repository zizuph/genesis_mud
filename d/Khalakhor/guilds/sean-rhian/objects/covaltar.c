/* Small covered altar
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/10/98     Zima        Created
*/
inherit "/std/container";
#include <stdproperties.h>
 
void create_container() {
    set_name("altar");
    set_adj(({"small","covered"}));
    set_short("small covered altar");
    set_long(
       "It is a small rectangular altar, three times in length as in "+
       "width. It is covered with a snow-white cloth, in the "+
       "center of which is embroidered three interlocked circles.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}

