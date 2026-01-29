inherit "/std/armour";

#include <stdproperties.h>;
#include <wa_types.h>;
#include "/d/Emerald/defs.h";


void
create_armour()
{
    set_name("bracelet");
    add_name("_emerald_sick_kid_quest_bracelet_");
    set_short("silvery handmade bracelet");
    set_long("This small bracelet seems to be made for a child. "+
       "It has some runes of protection on it that seem to be "+
       "elvish. The runes appear to be protection against some sort of "+
       "sickness.\n");
    set_adj(({"handmade", "silvery"}));

    set_ac(5);
    set_at(A_L_HAND);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 12);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_I_RES_POISON, 5);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchanted"}));
    add_prop(MAGIC_AM_ID_INFO, ({
	"The bracelet seems to have some minor magic in it.\n", 0,
	"The bracelet seems to have some protection magic in it.\n", 10,
	"The bracelet seems to have some protection against sickness.\n", 40,
	"The bracelet seems to provide protection against sickness and "+
	  "poison.\n", 60}));
}

string stat_object() {
  return (::stat_object() + "POISON RESISTANCE: 5\n");
}
