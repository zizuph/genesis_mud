/* Mail of an imperial guard
**
** HISTORY
** Date       Coder     Action
** ---------- --------- -----------------------------------
** 1/30/96    Zima      Created
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("mail");
    set_adj(({"black","tempered","orichalcum","kretan"}));
    set_short("black tempered mail");
    set_long("It is suit of tempered orichalcum mail, enameled black and "+
             "bearing an escutcheon on the breast cast with a "+
             "relief of a ferocious seven-headed hydra.\n");
    set_ac(37);
    set_at(A_TORSO);
    set_am(({-1,1,0}));
}
