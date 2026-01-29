/* Mail of a Stratarch
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
    set_adj(({"tempered","orichalcum","kretan"}));
    set_short("tempered orichalcum mail");
    set_long("It is suit of augmented mail made of high-quality tempered "+
             "orichalcum. An escutcheon on the breast is cast with a "+
             "relief of a ferocious seven-headed hydra.\n");
    set_ac(34);
    set_at(A_TORSO);
    set_am(({-1,1,0}));
}
