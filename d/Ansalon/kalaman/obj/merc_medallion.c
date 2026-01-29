inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS 2

object wearer;

void
create_armour()
{
    set_name("medallion");
    add_name("_kalaman_merc_medallion");
    set_pshort("medallions of the Istarian Merchant");
    set_short("medallion of the Istarian Merchant");
    set_long("This medallion of solid gold is an artifact from the distant "+
      "past, the Medallion of the Istarian Merchant. "+
      "Etched on it is the symbol of a griffin's wing.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_NECK);
    set_af(TO);

    add_prop(OBJ_S_WIZINFO, "This is a quest object that needs to be returned "+
      "to the quest giver for the reward to be given out. When worn, this medallion "+
      "raises ones skills SS_TRADING by 10, and their SS_APPR_OBJ and "+
      "SS_APPR_VAL by 20.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This medallion has been blessed, and is one of the "+
	"few holy relics that survived the cataclysm.",10,
	"It has been blessed by the Goddess Shinare, Goddess "+
	"of wealth, industry, and commerce.",30,"The blessing "+
	"increases ones ability to appraise objects as well "+
	"as the persons trading ability.\n",60}));
    add_prop(MAGIC_AM_MAGIC,({10,"enchantment"}));
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50));
}

mixed
wear(object what)
{
    TP->set_skill_extra(SS_TRADING, TP->query_skill_extra(SS_TRADING) +10);
    TP->set_skill_extra(SS_APPR_OBJ, TP->query_skill_extra(SS_APPR_OBJ) + 20);
    TP->set_skill_extra(SS_APPR_VAL, TP->query_skill_extra(SS_APPR_VAL) + 20);

    wearer = TP;
    return 0;
}
mixed
remove(object what)
{
    wearer->set_skill_extra(SS_TRADING, TP->query_skill_extra(SS_TRADING) - 10);
    wearer->set_skill_extra(SS_APPR_OBJ, TP->query_skill_extra(SS_APPR_OBJ) -20);
    wearer->set_skill_extra(SS_APPR_VAL, TP->query_skill_extra(SS_APPR_VAL) -20);

    wearer = 0;
    return 0;
}
