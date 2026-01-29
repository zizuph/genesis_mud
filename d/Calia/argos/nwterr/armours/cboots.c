/* common boots
**
** HISTORY
** Date       Coder      Action
** ---------- ---------- ----------------------------------
** 10/15/96   Zima       Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("boots");
    add_name(({"pair","pair of boots"}));
    set_adj(({"brown","leather","soft"}));
    set_short("pair of brown leather boots");
    set_pshort("pairs of brown leather boots");
    set_long(
       "It is a pair of low-cut boots, made of soft brown leather.\n");
    set_ac(4);
    set_at(A_FEET);
    set_am( ({ 0, 0, 0 }) );
}
