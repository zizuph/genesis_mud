inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
    set_name("robe");
    add_name("_dont_react_to");
    set_ac(10);
    set_at(A_ROBE);
    set_adj("dazzling");
    add_adj("expensive");
    set_short("dazzling expensive robe");
    set_long("This expensive looking robe is made from strange material that seems to " +
      "change its colour as the wearer moves, creating a dazzling display meant to impress " +
      "friends and confuse enemies.\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This robe has been enchanted to dazzle friends and confuse foes that would " +
	"try and harm the wearer. The enchantment is simple. The changing colours mask " +
	"somewhat the movements of the wearer, making it more difficult for enemies to hit " +
	"them.\n",20}));
    add_prop(MAGIC_AM_MAGIC, ({15, "enchantment"}));
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50));
}


