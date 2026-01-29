/*
 * /d/Ansalon/dargaard/obj/weapon/mishakal_blade.c
 *
 * Author: Arman
 *
 * Navarre July 3rd fixed typo.
 * Petros  July 14, 2010 - fixed typo with unwield
 * Arman   Dec 2021, made a spell enhancer
 */
 
inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
    seteuid(getuid(TO));
    set_name("blade");
    set_adj("holy");
    set_short("holy blade");
    add_name("sword");
    set_long("This is a sword of ancient design that has not been seen since "+
      "long before the Cataclysm. The blade is cast from a strange steel alloy "+
      "that is surrounded by a pure white nimbus that seems to disperse the "+
      "darkness around you. The blue-steel hilt is of "+
      "elaborate make and is engraved with what looks like elvish runes.\n");
    set_default_weapon(35,35,W_SWORD, W_SLASH | W_IMPALE, W_RIGHT);
    set_magic_spellpower(10);
    set_spellpower_elements(({
        SS_ELEMENT_LIFE, SS_ELEMENT_AIR, SS_ELEMENT_WATER
    }));
    set_wf(TO);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({"This is a holy blade once wielded in the Age of Dreams by a disciple of " +
	"the old goddess, Mishakal. During the Cataclysm the blade was broken, " +
	"however was later restored by heroes who returned the broken pieces of " +
	"it to the goddesses temple in Xak Tsaroth. The enchantment of this blade "+
	"is such that it becomes more powerful when wielded by warriors of good. "+
	"The blade also glows with a holy light that can disperse some of the "+
	"deepest darkness.\n", 10}));
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_LIGHT, 1);

    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);

    add_item("runes","Elvish runes run along the guard of this hilt. You could " +
      "try and read them.\n");
    add_cmd_item(({"runes","guard","hilt"}),"read",
      "@@read_writing");

}

string
read_writing()
{
    if(TP->query_skill(SS_LANGUAGE) < 50 && TP->query_race() != "elf")
	return "Along the guard of the hilt are elvish runes which you are unable "+
	"to interpret.\n";
    else
	return "Along the guard of the hilt is written in elvish 'Quen Illumini'. " +
	"You notice at the beginning and end of these runes is the symbol of " +
	"infinity, two circles joined.\n";
}

void
delayed_wield(object wielder)
{
    if(E(TO) != wielder)
	return;

    if(wielder->query_alignment() > 100)
    {
	wielder->catch_tell("The holy blade flares to light, and you feel " +
          "the blade infuse itself with holy righteousness.\n");
        tell_room(E(E(TO)),"The holy blade wielded by " + QTNAME(wielder) +
          " flares up, radiating brightly with a divine light!\n", wielder);

	set_hit(35 + (wielder->query_alignment() / 100));
	set_pen(35 + (wielder->query_alignment() / 150));
        set_magic_spellpower(35 + (wielder->query_alignment() / 150));
        TO->add_prop(OBJ_I_LIGHT, 6);
	wielder->update_weapon(TO);
	return;
    }

    set_hit(35);
    set_pen(35);
    set_magic_spellpower(10);
    query_wielded()->update_weapon(TO);
}

mixed
wield(object what)
{
    set_alarm(1.0, 0.0, &delayed_wield(E(TO)));
    return 0;
}

void
delayed_unwield(object wielder)
{
    if(E(TO) == wielder)
    {
        E(TO)->catch_tell("The holy blade dims considerably as you unwield it.\n");
        tell_room(E(wielder),"The holy blade wielded by " + QTNAME(wielder) +
            " dims as it is released.\n", wielder);
    }
    TO->add_prop(OBJ_I_LIGHT, 1);
}

mixed
unwield(object what)
{
    set_alarm(1.0, 0.0, &delayed_unwield(query_wielded()));
    return 0;
}

/*
 * Function name: remove_broken
 * Description  : The weapon got broken so the player has to stop
 *                wielding it.
 * Arguments    : int silent - true if no message is to be genereated
 *                             about the fact that the weapon broke.
 */
varargs void
remove_broken(int silent = 0)
{
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);

    return;
}


/*
 * Function name: set_dull
 * Description:   Use this to increases the dull status on weapons.
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 */
int
set_dull(int du)
{
    return 0;
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}