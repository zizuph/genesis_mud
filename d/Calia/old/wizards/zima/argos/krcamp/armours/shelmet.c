/* Helmet of a kretan sentry
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
    set_name("casque");
    add_name("helmet");
    set_adj(({"black","studded","kretan"}));
    set_short("black studded casque");
    set_long("It is a small studded casque or helmet, enameled black "+
             "and bearing the emblem of a seven-headed hydra on the helm.\n");
    set_ac(9);
    set_at(A_HEAD);
    set_am( ({0,1,-1}));
}
