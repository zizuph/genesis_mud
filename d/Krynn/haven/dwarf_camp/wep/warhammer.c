
inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Krynn/haven/local.h"

public void
create_weapon()
{
    set_name("warhammer");
    add_name(({"weapon","club","hammer","mace"}));
    set_pname("warhammers");
    add_pname(({"maces","clubs","weapons","hammers"}));
    set_adj(({"steel","two-handed"}));
    set_short("two-handed warhammer");
    set_pshort("two-handed warhammers");
    set_long("This warhammer, though only about half a meter "+
      "in length, is quite heavy. It's forged of fine steel, "+
      "and is heavily weighted towards the end. You imagine "+
      "that it could pack quite a bit of punch if swung "+
      "properly.\n");

    set_default_weapon(27, 35, W_CLUB, W_BLUDGEON, W_BOTH);

    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(27,35));
}
