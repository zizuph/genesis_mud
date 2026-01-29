/* A small money pouch carried by Kretans
**
** Date     Coder       Action
** -------- ----------- ---------------------------------------
** 1/25/96  Zima        Created
*/
inherit "/std/receptacle";
#include <stdproperties.h>
 
void create_container() {
    set_name("pouch");
    set_adj(({"small","brown","leather","kretan"}));
    set_short("small leather pouch");
    set_pshort("small leather pouches");
    set_long("It is a small brown leather pouch.\n");
 
    add_prop(CONT_I_WEIGHT, 250);
    add_prop(CONT_I_MAX_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 50);
    add_prop(CONT_I_MAX_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 10);
}
