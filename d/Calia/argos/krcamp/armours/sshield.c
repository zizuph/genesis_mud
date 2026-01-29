/* Shield of a kretan sentry
**
** HISTORY
** Date       Coder      Action
** ---------- ---------- ----------------------------------
** 1/25/96    Zima       Created
** 8/22/21    Greneth    Changed AC to 20
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
 
void create_armour() {
    set_name("shield");
    set_adj(({"black","studded","kretan"}));
    set_short("black studded shield");
    set_long("It is a round studded shield, enameled black with the emblem "+
             "of a seven-headed hydra in red.\n");
    set_ac(20);
    set_at(A_SHIELD);
    set_am( ({0,0,0}));
}
