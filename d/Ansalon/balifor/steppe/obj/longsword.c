inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("sword");
    add_name("longsword");
    set_adj("kestrel-marked");
    add_adj("kestrel");
    add_adj("marked");
    set_short("kestrel-marked longsword");
    set_long("This is a well-balanced and well looked after " +
      "longsword made of the finest steel in Ansalon. On its " +
      "hilt is the crimson kestrel insignia, the mark of a " +
      "master swordsman of the realms. A strange crimson " +
      "line runs up the middle of the sword's blade.\n");
    set_default_weapon(44, 39, W_SWORD, W_SLASH | W_IMPALE, W_RIGHT);
    set_likely_dull(0);
    set_likely_break(0);

    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VALUE, 5000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({"This sword is typical of that used by true " +
	"blade masters, made of the finest steel by the finest " +
	"weaponsmith. The thing that makes this unique is an enchantment " +
	"that strengthens the blade, making it hard for it to dull, " +
	"as well as making it far more easier for the wielder to hit " +
	"and do damage.\n",60}));
}
