// raises animal-handling skill 25 and increases poison-resistance 15
// can be used for handling the snake staff
// Lilith  1/20/97
/*
 * Revisions:
 * 	Lucius, Aug 2017: Removed ENEMY check.
 *  Lilith, Sep 2021: Updated intox ck to be >50% of max, AC to 25
 */
#pragma strict_types

inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>

#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/common/common.h"

#define MANA_COST	30
#define G_PROP		"_avenir_ah_gloves"

void
create_armour()
{
    set_name("gloves");
    set_short("pair of leather gloves");
    set_pshort("pairs of leather gloves");
    set_adj("leather");
    add_adj(({"red", "reddish", "brown"}));
    set_long("These gloves are made from very thick leather. "+
      "They have been dyed a dark reddish-brown.\n");

    set_default_armour(25, A_HANDS, 0, 0);
    set_am(({ 2, -1, -1}));
    set_af(this_object());
    set_keep(1);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "life" }));
    add_prop(MAGIC_I_RES_POISON, 15);

    add_prop(MAGIC_AM_ID_INFO, ({"The leather of these gloves have "+
       "been soaked in the blood of an empathic animal-handler and "+
       "further treated in some way that embues the wearer with some "+
       "of that individual's animal handling abilities.\n", 30}));
    add_prop(OBJ_S_WIZINFO, "These gloves will add poison resistance of "+
          "15 and animal handling of of 25 to the wearer. The gloves are "+
          "resistant to poison (15). The cost is 30 mana. They cannot be "+
          "worn by enemies of Sybarus, and drunks don't benefit "+
          "from wearing them, either.\n");

    add_prop(OBJ_I_VALUE, 400);
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (protectee == query_worn())
    {
        if (prop == MAGIC_I_RES_POISON)
	    return ({ 15, 1});
    }
    else
      return ::query_magic_protection(prop, protectee);
}

mixed
wear(object ob)
{
    object tp = this_player();
	int tox_max;

    if (tp->query_mana() <= MANA_COST)
    {
        return "You do not have the mental strength to wear "+
               "these gloves.\n";
    }

    /* I'm an infidel/enemy of Sybarus, I can't wear them */
    if (IS_INFIDEL(this_player()))
    {
        return "You just can't seem to fit your hands into the "+
               short() +".\n";
    }

    /* Does living have high alcohol level? If so, no extras */
	tox_max = tp->intoxicated_max() / 2;	
    if (tp->query_intoxicated() > (tox_max)) 
    {
        tp->catch_msg("The alcohol in your system interferes with "+
           "the magic of the gloves.\n");
        return 0;
    }
    tp->add_prop(G_PROP, 1);
    tp->add_mana(-MANA_COST);
    tp->catch_msg("You feel an increased sensitivity to the animal "+
            "life nearby.\n");
    tp->set_skill_extra(SS_ANI_HANDL,
        this_player()->query_skill_extra(SS_ANI_HANDL) + 25);
    tp->add_magic_effect(this_object());
    return 0;
}

mixed
remove(object ob)
{
    object tp = query_worn();

    if (!tp->query_prop(G_PROP))
    {
        return 0;
    }
    else
    {
        tp->set_skill_extra(SS_ANI_HANDL,
            tp->query_skill_extra(SS_ANI_HANDL) - 25);
        tp->remove_magic_effect(this_object());

        if (!interactive(environment(this_object())))
            return 0;
        tp->catch_tell("You feel a sense of loss as your heightened awareness "+
            "of animal life diminishes.\n");
        return 0;
    }
}
