/* Helmet of a kretan warrior
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
    set_adj(({"polished","orichalcum","kretan"}));
    set_short("polished orichalcum helmet");
    set_long("It is a polished helmet made of double mailed orichalcum,"+
             "with a circular inset on the helm bearing a seven-headed "+
             "hydra.\n");
    set_ac(18);
    set_at(A_HEAD);
    set_am( ({-1,1,0}));
}
