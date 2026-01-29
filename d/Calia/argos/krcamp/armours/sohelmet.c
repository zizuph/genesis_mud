/* Helmet of a Kretan Soldier
**
** HISTORY
** Date       Coder   Action
** ---------- ------- -----------------------------------
** 1/25/96    Zima    Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_armour() {
    set_name("helmet");
    set_adj(({"charred","orichalcum","kretan"}));
    set_short("charred orichalcum helmet");
    set_long("It is a helmet made of orichalcum chainmail, charred black "+
             "and bearing the emblem of a seven-headed hydra on the helm.\n");
    set_ac(15);
    set_at(A_HEAD);
    set_am( ({-2,3,-1}));
}
