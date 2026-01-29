inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"

void
create_weapon()
{
    set_name("battle standard");
    add_name(({"battle standard of the witchking", "standard", "polearm", }));
    add_name(BSW_BATTLE_STANDARD);

    set_adj(({"battle", "large", "ancient", }));

    set_short("battle standard of the Witchking");
    set_long(BSN("This is the battle standard of the Witchking. Earnur, last "
      + "King of Gondor, conquered it in the battle of Fornost in the year "
      + "1975 of the Third Age. He later gave it to Mardil Voronwe, his "
      + "Steward, before he went to Minas Morgul to fight the Lord of Morgul, "
      + "who had been the Witchking of Angmar before he conquered Minas "
      + "Ithil 27 years after the battle of Fornost. The battle standard "
      + "is an iron pole about twelve feet long from which is hanging a cross "
      + "beam. The cross beam carries a flag which shows a death's head on "
      + "a sable field."));

    set_default_weapon( 5, 10, W_POLEARM, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON( 5, 10) + 100 - random(200));
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(5, W_POLEARM) + 5000 + random(400)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

    add_prop(OBJ_S_WIZINFO, "This is the battle standard of the Witchking of "
      + "Angmar. Returning it the the quest masters in Minas Morgul and Minas "
      + "Tirith will be rewarded.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

string
query_recover()
{
    return 0;
}
