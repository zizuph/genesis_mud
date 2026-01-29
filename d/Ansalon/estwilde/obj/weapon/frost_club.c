
inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"

#define WEAPON_HIT 44
#define WEAPON_PEN 50


void
create_weapon()
{
    set_name("warhammer");
    add_name(({"hammer","club"}));
    add_name("weapon");
    set_adj("giants");
    add_adj("giant's");
    add_adj("frost");
    set_short("frost giant's warhammer");
    set_long("This massive warhammer was once used by a frost " +
      "giant. Huge and heavy, the head of this warhammer twinkles " +
      "like a piece of ice in the sun. While chill to touch, " +
      "this club is far sturdier than you would imagine. Its " +
      "banded head would have little trouble crushing the life out " +
      "a warhorse!\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_M_NO_SELL,"The shopkeeper cannot afford to buy " +
      "the magical weapon. You will have to keep hold of it.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"Truly ancient " +
	"is this warhammer, crafted in the Age of Dreams by frost giant shamans with " +
	"the primitive powers of the elements. This clubs "+
	"enchantment makes its slightly better to hit " +
	"than a good two-handed warhammer, as well as greatly "+
	"increasing the clubs ability to do damage to a target.\n", 60}));

    add_prop(OBJ_I_WEIGHT, 16000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));

}

