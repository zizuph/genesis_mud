inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"

inherit "/lib/keep";

#define ARMOUR_CLASS 47

void
create_armour()
{
    set_name("armour");
    add_name("platemail");
    set_pname("armours");
    add_pname("platemails");

    set_adj("ornamented");
    add_adj("golden");

    set_short("ornamented golden platemail");
    set_long("This suit of platemail is that worn " +
      "by the Lord of Kalaman. The finest of steel " +
      "has been used in the crafting of this armour, " +
      "covered with a thin layer of golden paint " +
      "and ornamented with the trappings of a noble. " +
      "You do not doubt it offers the best of protection.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This platemail has been magically strengthened by a " +
	"White Robed Magician of Krynn as a gift to the " +
	"Lord of Kalaman, giving the wearer better protection.\n",20}));
    add_prop(MAGIC_AM_MAGIC, ({30,"enchantment"}));
    add_prop(OBJ_I_WEIGHT, 13000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
    add_prop(KALAMAN_NOBUY,1);
}
