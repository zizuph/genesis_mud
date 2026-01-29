/* Shield of a kretan warrior
**
** HISTORY
** Date       Coder      Action
** ---------- ---------- ----------------------------------
** 1/30/96    Zima       Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("shield");
    set_adj(({"polished","orichalcum","kretan"}));
    set_short("polished orichalcum shield");
    set_long("It is a polished kite shield made of orichalcum emblazoned "+
             "with a circular inescutcheon bearing a seven-headed hydra.\n");
    set_ac(20);
    set_at(A_SHIELD);
    set_am( ({0,0,0}));
}
