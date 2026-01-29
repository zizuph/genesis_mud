#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit CREST_ARMOUR;

void
create_crest_armour()
{
    set_crest_desc(DRAGON_CREST);
    set_crest_id(DRAGON_ID);

    set_name("hauberk");
    set_adj(({"blackened","black", "steel"}));
    set_short("blackened steel hauberk");
    set_long("This "+short()+" covers ones torso and arms.  Made up of "+
      "links of steel that have been blackened for some unknown "+
      "purpose.  No light reflects off the blackened surface "+
      "as you look upon it.\n");

    set_keep(1);
    set_likely_break(2);
    set_likely_cond(3);
    set_at(A_TORSO | A_ARMS);
    set_ac(45);
    set_am(({-1, 1, 0}));

    // This object is extermely resistant to magical effects
    add_prop(OBJ_I_RES_MAGIC,  75);
    add_prop(OBJ_I_RES_FIRE,   50);
    add_prop(OBJ_I_RES_COLD,   50);
    add_prop(OBJ_I_RES_ACID,   80);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(OBJ_I_RES_LIFE,  100);
    add_prop(OBJ_I_RES_EARTH,  70);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This "+short()+" has been enchanted and "+
	"radiates a strange magic.", 15, "  Furthermore the blackened "+
	"metal seems to be a residue of the enchantment process.  ", 35,
	"The residue seems to be a web of magic inversed upon itself "+
	"which appears to protect the wearer from magic.\n", 70}));
    add_prop(OBJ_S_WIZINFO,"This "+short()+" provides good protection "+
      "to the wearer as well adds a small amount of magic resistance.\n\n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(45, A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45) + 200 + random(250));
}


varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{

    if (protectee == query_worn())
    {
	if (prop == MAGIC_I_RES_MAGIC)
	    return ({10, 1});
    }
    else
	return ::query_magic_protection(prop, protectee);
}

public mixed
wear(object arm)
{
    ::wear(arm);
    this_player()->add_magic_effect(arm); 
    return 0;
}

public mixed
remove(object arm)
{
    ::remove(arm);
    query_worn()->remove_magic_effect(arm);
    return 0;
}
