/* Helmet of an Imperial guard
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
    set_name("helmet");
    set_adj(({"plumed","tempered","black","orichalcum","kretan"}));
    set_short("black tabarded helmet");
    set_long("It is a tabarded helmet made of tempered orichalcum and "+
             "enameled black. It is decorated with a black plume on "+
             "top and an inescutcheon on the tabard bearing a seven-headed "+
             "hydra.\n");
    set_ac(23);
    set_at(A_HEAD);
    set_am( ({0,0,0}));
}
