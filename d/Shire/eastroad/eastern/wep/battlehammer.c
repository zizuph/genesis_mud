inherit "/std/weapon";

#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("battlehammer");
    set_adj(({"heavy","bulky", "dwarven"}));
    set_short("heavy dwarven battlehammer");
    set_long("This "+short()+" is a very unwieldly weapon.  "+
      "A large bulky hammer on the end of a extremely large shaft.\n");
    add_name(({"battlehammer","hammer"}));

    set_wt(W_POLEARM);
    set_hit(21);
    set_pen(40);
    set_hands(W_BOTH);
    set_dt(W_BLUDGEON);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_POLEARM) + random(350));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25,40) + 20 + random(41));
}
