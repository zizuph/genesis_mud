/* Helmet of a Stratarch
**
** HISTORY
** Date       Coder   Action
** ---------- ------- -----------------------------------
** 1/30/96    Zima    Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_armour() {
    set_name("helm");
    set_adj(({"plumed","tempered","orichalcum","kretan"}));
    set_short("plumed orichalcum helm");
    set_long("It is a large helm made of tempered orichalcum, adorned "+
             "with a large red plume on the top and an inescutcheon bearing "+
             "a seven-headed hydra on the front.\n");
    set_ac(22);
    set_at(A_HEAD);
    set_am( ({0,0,0}));
}
