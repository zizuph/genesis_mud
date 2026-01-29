/* A common shield
** Date       Coder     Action
** ---------- --------- -----------------------------------
** 10/15/96   Zima      Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("shield");
    set_adj(({"light","iron","round","small"}));
    set_short("light iron shield");
    set_long("It is a small round shield made of iron, decorated only with "+
             "a ring of knobs around its circumference.\n");
    set_ac(10);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
}
