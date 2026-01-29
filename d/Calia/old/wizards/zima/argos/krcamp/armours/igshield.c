/* Shield of an imperial guard
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
    set_adj(({"black","tempered","kretan"}));
    set_short("black tempered shield");
    set_long("It is a large kite shield made of black-enameled tempered "+
             "orichalcum. It is emblazoned with an inescutcheon bearing "+
             "a large writhing seven-headed hydra.\n");
    set_ac(20);
    set_at(A_SHIELD);
    set_am( ({0,0,0}));
}
