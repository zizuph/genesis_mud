/*
 * Mantooth, the iconic magebane sword. It provides higher hit/pen
 * against enemies with high spellcraft, as well as has a special
 * that dispels all active spell effects on the target.
 *
 * - Arman Kharas, July 2018
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_weapon()
{
    set_name("mantooth");
    add_name("sword");
    add_name("longsword");
    add_adj("ancient");
    set_short("ancient longsword");
    set_long("This is an ordinary-looking longsword of ancient " +
        "design, crafted in a style that hasn't been smithed in over " +
        "a thousand years. The hilt is of black steel, and is " +
        "tightly wrapped in greying leather from pommel to guard.\n");

    set_hit(35);
    set_pen(35);
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_dt(W_SLASH | W_IMPALE);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"The longsword is a blade of legend and is known by many " +
        "names - Spellcleaver, Darkstar, Magefool, and Mantooth.\n", 25,
        "Folklore of the Silvanesti elves tell of this " +
        "blade being able to shatter the enchantments and protections " +
        "of spellcasters, and is credited with the undoing of the " +
        "dark elf sorceress Silvyana 500 years ago and the binding " +
        "of the ogre mage Shril. It is more powerful against those " +
        "enemies with high spellcraft skills.\n", 55}));
    add_prop(OBJ_S_WIZINFO, "This is the iconic Dragonlance sword " +
        "Mantooth. Also known as Spellcleaver, Darkstar, and Magefool, " +
        "against opponents with high spellcraft skills it changes " +
        "from a good non-magical blade (35/35 hit/pen) to potentially " +
        "a formidable one-handed magical sword (55/45 hit/pen " +
        "when target's guru spellcraft skill level is superior guru).\n" +
        "Additionally, this blade has a 1 in 3 chance of dispelling " +
        "an active spell effect on a target with a successful hit.\n" +
        "This sword is also more difficult to wield if the wielder " +
        "has high spellcraft skill.\n");
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35) + 500 + random(500)); 
}

mixed
wield(object what)
{
    if(TP->query_skill(SS_SPELLCRAFT) > (50 + random(60)))
    {
        TP->add_mana(-30);
        return "The " + short() + " resists your attempt to wield it!\n";
    }

    return 0;
}

void
state_change(int hit, int pen)
{
    set_hit(hit);
    set_pen(pen);
 
    if (wielded && wielder)
        wielder->update_weapon(this_object());
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int hit, pen;
    int spell_skill = enemy->query_skill(SS_SPELLCRAFT);
    object * effects = enemy->query_magic_effects();

    if(spell_skill > 40)
    {
        // max hit 55, max pen 45 where enemy has 100 spellcraft
        hit = 35 + (spell_skill / 5);
        pen = 35 + (spell_skill / 10); 

        if(!random(5))
        {
            wielder->catch_tell("Your " + short() + " starts humming " +
                "aggressively!\n");
            tell_room(E(wielder), "The " + short() + " wielded by " +
                QTNAME(wielder) + " humming aggressively!\n",
                wielder);
        }
    }
    else
    {
        hit = 35;
        pen = 35; 
    }

    // One in three chance that the hit will dispel a spell effect 
    // on the target.

    if (sizeof(effects) && !random(3))
    {
        object effect = one_of_list(effects);
        string effect_name = effect->query_spell_effect_name();

        if(effect_name)
        {
            wielder->catch_msg("Upon contact with " +QTNAME(enemy)+ 
                ", your " +short()+ " dispels " +HIS(enemy)+ " " +
                effect_name + " spell!\n");
            enemy->catch_msg("Upon contact with you, " +QTPNAME(wielder)+
                " " +short()+ " severs your " + effect_name + 
                " spell, dispelling it!\n");
            enemy->tell_watcher("Upon contact with " +QTNAME(enemy)+
                ", " +QTPNAME(wielder) + " " + short() + " severs " +
                HIS(enemy)+ " " + effect_name + " spell!\n", wielder);
        }

        effect->dispel_effect(enemy);  
    }      

    state_change(hit, pen);

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
