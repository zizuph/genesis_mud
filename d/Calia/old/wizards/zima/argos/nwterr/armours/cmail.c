/* a common shirt of mail
** Date       Action
** ---------- -----------------------------------
** 10/15/96   Created
*/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("mail");
    add_name("shirt");
    set_adj("leather");
    set_short("shirt of leather mail");
    set_long("It is a shirt of leather mail, decorated with links of "+
             "chainmail across the breast.\n");
    set_ac(13);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
}
