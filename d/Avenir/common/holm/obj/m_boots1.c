// adds magical fire and acid resistance
// Lilith  1/20/97
/*
 * Revisions:
 * 	Lucius, Aug 2017: Removed ENEMY check.
 *  Lilith, Sep 2021: updated intox check to 50% of max, AC to 35
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"


void
create_armour()
{
    set_name("boots");
    set_short("pair of scarlet-gold scale boots");
    set_pshort("pairs of scarlet-gold scale boots");
    set_long("These boots are made of scale obtained from the "+
      "Worm that dwells in the fiery depths of the Utterdark. "+
      "When the scale is treated to make it suitable for armour, "+
      "its unique patterns are changed to a golden colour that "+
      "is a striking contrast to the scarlet background.\n");
    add_item(({"pattern", "patterns"}), "The patterns are raised "+
      "and sinuous. They are gold in colour.\n");
    set_adj("scale");
    add_adj(({"scarlet", "gold", "scarlet-gold"}));

    set_default_armour(35, A_FEET, 0, 0);
    set_am(({ -1, 2, -1}));
    set_af(this_object());
    set_keep(1);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "transformation" }));
    add_prop(MAGIC_I_RES_ACID, 40);
    add_prop(MAGIC_I_RES_FIRE, 40);
    add_prop(MAGIC_AM_ID_INFO, ({"Born of fire, tempered in lava, "+
          "these boots have the virtues of the creature from whose "+
          "scales they are made.\n", 30,
 	      "They are resistant to fire and acid.\n", 35,
		  "But only when the wearer is not blitzed.\n", 40 }));
    add_prop(OBJ_S_WIZINFO, "These boots will add fire resistance of "+
          "20 and acid resistance of 15 to the wearer. The boots are "+
          "resistant to acid (40) and fire (40). They cannot be "+
          "worn by enemies of Sybarus, and drunks don't benefit "+
          "from wearing them, either.\n");
    add_prop(OBJ_I_VALUE, 600);
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (protectee == query_worn())
    {
        if (prop == MAGIC_I_RES_FIRE)
	    return ({ 20, 1 });
        if (prop == MAGIC_I_RES_ACID)
            return ({ 15, 1 });
      }
    else
      return ::query_magic_protection(prop, protectee);
}

mixed
wear(object ob)
{
    object tp = this_player();
	int tox_max;

    if (query_worn())
    {
        tp->remove_magic_effect(this_object());
    }

    /* Does living have high alcohol level? If so, no extra protection */
    tox_max = tp->intoxicated_max() / 2;	
    if (tp->query_intoxicated() > (tox_max)) 
	{
		tp->catch_msg("The alcohol in your system and the magic of the "+
		    "are incompatible but you can still wear the boots.\n");
		return 0;
	}

    /* I'm an infidel/enemy of Sybarus, I can't wear them */
    if (IS_INFIDEL(this_player()))
    {
        return "You just can't seem to fit your feet into the "+
               short() +".\n";
    }

    tp->add_magic_effect(this_object());
    return 0;
}

int
remove(object ob)
{
    object tp = query_worn();
    tp->remove_magic_effect(this_object());
    return 0;
}
