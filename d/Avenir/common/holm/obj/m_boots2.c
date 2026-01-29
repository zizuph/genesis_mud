// These boots raise sneak and hide
// Lilith 1/20/97
// Revisions: Manat Dec 2000: Fix of skill boost for sneak and hide so it 
//                            can't get over 100
//            Lilith Sep 2021: Fixed intox ck to 50% of max intox, and 
//                             updated AC to 35. They were pretty wimpy for magical boots 


inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";

#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/basic.h"

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#define PROP "__holm_sneak_boots"

static void
create_armour(void)
{
    set_name("boots");
    set_short("pair of fur-lined leather boots");
    set_pshort("pairs of fur-lined leather boots");
    set_long("These boots are from the hide of a pahloor, a "+
      "creature of minor magical ability which is exceptionally "+
      "talented at evading notice. The leather is rather thick and "+
      "has been treated with a hardening agent. These boots have "+
      "been polished to a fine sheen.\n");
    add_item(({"fur", "lining", "fur-lining"}), "The fur is black, short, "+
      "and very thick. It makes the boots very comfortable to wear.\n");
    set_adj("leather");
    add_adj(({"fur-lined", "fur", "lined"}));

    set_default_armour(35, A_FEET, 0, 0);
    set_am(({ 1, 1, -2}));
    set_af(this_object());
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({"These boots have the virtues of "+
        "the creature from whose hide they were made.\n", 30,
        "They increase your effectiveness at both sneaking and "+
        "hiding.\n", 60}));
    add_prop(OBJ_S_WIZINFO, "These boots will add sneek and hide of "+
          "15 to the wearer. They cannot be "+
          "worn by enemies of Sybarus, and drunks don't benefit "+
          "from wearing them, either.\n");

    add_prop(OBJ_I_VALUE, 600);
}

public mixed
wear(object ob)
{
	int tox_max;

    /* Does living have high alcohol level? If so, no extra protection */
    tox_max = wearer->intoxicated_max() / 2;	
    if (wearer->query_intoxicated() > (tox_max)) 
	{
		wearer->catch_msg("The alcohol in your system will prevent "+
           "the magic of the boots from working for you, but you "+
		   "can still wear them.\n");
        return 0;
	}

    /* I'm an infidel/enemy of Sybarus, I can't wear them */
    if (IS_INFIDEL(wearer))
    {
	    return "You just can't seem to fit your feet into the "+
	    short() +".\n";
    }

    if (!wearer->query_prop(PROP))
    {
	    wearer->add_prop(PROP, 1);
	    ALTER_SKILL(wearer, SS_HIDE, 15);
	    ALTER_SKILL(wearer, SS_SNEAK, 15);
    }

    return 0;
}

public int
remove(object ob)
{
    if (wearer->query_prop(PROP))
    {
    	wearer->remove_prop(PROP);
	    ALTER_SKILL(wearer, SS_HIDE, -15);
	    ALTER_SKILL(wearer, SS_SNEAK, -15);
    }

    return 0;
}
