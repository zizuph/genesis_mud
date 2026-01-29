// sybarun khopesh       /d/Avenir/common/city/obj/wield/khopesh.c
// creator(s):           Lilith, June 2002 implemented July 2003
// based upon:           /d/Genesis/genesis/doc/examples/weapons/elf_slayer
//                       /d/Avenir/inherit/weapon
// purpose:              To be wielded by dej-minha in the Forbidden City.
// notes:                This is a magical sword with 45/50 hit/pen.
//                       It is cloned by /d/Avenir/common/city/mon/dej-minha.c
//            Drawbacks: Wielder cannot be intoxicated, thus player heals
//                       more slowly. It cannot be wielded by Enemies of Sybarus.
//         Requirements: It checks for INT, DEX & SWORD; has intox limits.
//                       20 fatigue when wielded and 1/3 of fatigue when unwielded.
//              Effects: adds up to 20 levels of SS_WEP_SWORD, max of 100.
//     Associated files: /d/Avenir/common/city/obj/wep/intox_shadow.c
//                       To monitor use of alcohol.
/*
 * Revisions:
 * 	Lilith, Aug 2014: Added offering check to wield
 * 	Lucius, Sep 2017: Removed ENEMY check.
 * 	Lucius, Oct 2017: Fixup skill_bonus add/remove.
 *  Lilith, Sep 2021: Updated intox ck to >50% of max intox
 */
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>
#include <filter_funs.h>

#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/include/deities.h"
#include "/d/Avenir/include/relation.h"

#define SHADOW		"/d/Avenir/common/city/obj/wep/intox_shadow"
#define CLONE_LOG	"/d/Avenir/log/misc/khopesh"
#define WIELD_PROP	"_avenir_wield_khopesh"

private int skill_bonus = 0;
public object sword_shadow;

/* prototypes */
string
my_long()
{
    return "An ancient weapon that resembles "+
           "a cross between a scimitar and a sickle. "+
           "The carved handle is short and made of black "+
           "kesoit wood with a prominent blood-red grain. "+
           "There is a distinctive pattern of "+
           "wavy lines along the length of the blade, a "+
           "decoration resulting from its forging process. "+
           "The damask steel blade extends straight from "+
           "the quillons for some distance, then curves "+
           "wickedly back toward the handle and tapers to "+
           "a fine point. Both the inner and outer curves "+
           "have a keen edge. Well over a meter in length from "+
           "pommel to tip, this "+ short() +" is a weapon "+
           "to cast fear in the hearts of even the staunchest "+
           "foes.\n";
}

void
create_weapon()
{
    set_name("khopesh");
    add_name(({"sword", "scimitar", "weapon", "sickle",
        "kopis", "blade"}));
    set_pname("khopeshes");
    add_pname(({"swords", "scimitars", "weapons"}));
    set_adj("sybarun");
    add_adj(({"damask", "steel"}));
    set_short("sybarun khopesh");
    set_pshort("sybarun khopeshes");
    set_long(my_long);
    set_wf(this_object());

    add_item(({"handle", "carved handle", "pommel", "hollows"}),
        "This is a short handle made of black kesoit wood with a "+
        "prominent blood-red grain. The pommel "+
        "is rounded and polished to a high sheen. Wavy, twisting "+
        "hollows have been carved into the handle to improve its "+
        "grip.\n");
    add_item(({"damask steel", "steel", "wavy lines", "pattern"}),
        "The steel of this khopesh has been forged at extreme "+
        "temperature, pounded thin and folded repeatedly, giving "+
        "it both the great strength and wavy surface pattern "+
        "that is characteristic of damask steel.\n");
    add_item(({"blade"}),
        "It is made of damask steel, which is incredibly strong. "+
        "The surface of the blade is covered in a pattern of "+
        "wavy lines.\n");

    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_dt(W_SLASH); // Removed MAGIC_DT by order from AoB 060123 Ibun
    set_hit(45);
    set_pen(46);
	
	set_likely_break(1);
    set_likely_dull(1);
    set_likely_corr(1);    

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 2500); /* about 1/3 normal */
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45, 46) * 2); /* Magical */

    /* Designate this as a magic weapon */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "What good fortune you hold in your hands!\n", 10,
        "For the sword of the dej-minha is enchanted.\n", 20,
        "By grace of the Gods, those priviledged to wield it\n", 30,
        "may find their sword-handling skill greatly improved.\n", 40}));

    /* Let wizards know what the sword does */
    add_prop(OBJ_S_WIZINFO, "This sword raises SS_WEP_SWORD by 20 levels, "+
        "not to exceed 100. Wielder must have high enough DEX, INT, "+
        "and SWORD, as well as 20 fatigue. The player cannot be >50%"+
        "intoxicated or an Enemy of Sybarus in order to wield. "+
        "It takes 1/3 of fatigue when unwielded.\n");

    reset_euid();
    SCROLLING_LOG(CLONE_LOG, " khopesh was cloned.");
}


/*
 * Function     : wield
 * Description  : Wield a weapon
 * Arguments    : Object what - The weapon to wield
 * Returns      : string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
mixed
wield(object what)
{
    object tp = environment(this_object());
    int sword_skill, go, tox_max;

    /* Is it broken? If so, dont wield */
    if (query_prop(OBJ_I_BROKEN))
        return "It is broken in such a way that you cannot wield it.\n";

    if (!living(tp) || tp->query_prop(WIELD_PROP))
        return 0;

    /* I'm an infidel/enemy of Sybarus, the sword doesn't like me */
    if (IS_INFIDEL(this_player()))
    {
        this_player()->heal_hp(-50);
        return "The "+ short() +" twists out of your grasp and "+
               "lands on your foot, causing you great pain.\n"+
               "The Gods of Sybarus will not allow their gifts "+
               "to be used by their Enemies.\n";
    }

    /* Does living have alcohol level > 50% max intox ? If so, don't wield */
	tox_max = tp->intoxicated_max() / 2;
    if (this_player()->query_intoxicated() > (tox_max) &&
	(!tp->query_prop(I_MADE_OFFERING)))
    {
        return "You are too intoxicated to wield the "+
               "blade-heavy "+ short() +". You might "+
               "hurt yourself with it.\n";
    }


    /* Lets set some stat and skill requirements to wield */
    go = tp->query_stat(SS_DEX) / 3;          /* Mortal: 100/3 = 33 */
    go += tp->query_skill(SS_WEP_SWORD) / 3;  /* Mortal: 100/3 = 33 */
    go += tp->query_stat(SS_INT) / 3;         /* Mortal: 100/3 = 33 */
                                              /* random(100) < 50 fails */
    if ((random(go) < 50))
    {
        tp->add_fatigue(-20);
        return "You try to wield the "+ short() +", but fail.\n";
    }

    /* All checks have passed, proceed with wielding */
    tp->add_fatigue(-20);
    tp->catch_msg("You feel like a master with this "+ short() +
        " in your hand.\n");
    say(QCTNAME(tp)+" wields the "+ short() +" with an expression "+
        "of wonder.\n");

    SCROLLING_LOG(CLONE_LOG, capitalize(tp->query_real_name()) +
            " wielded a khopesh.");

    skill_bonus = min(20, 100 - tp->query_skill(SS_WEP_SWORD));
    if (skill_bonus > 0)
    {
	tp->set_skill_extra(SS_WEP_SWORD,
	    tp->query_skill_extra(SS_WEP_SWORD) + skill_bonus);
    }

    tp->add_prop(WIELD_PROP, 1);

    sword_shadow = clone_object(SHADOW);
    sword_shadow->shadow_me(tp);
    tp->set_khopesh_sword(this_object());

    return 1;
}

mixed
unwield(object wep)
{
    object owner = query_wielded();

    if (owner->query_prop(WIELD_PROP) && skill_bonus > 0)
    {
        owner->set_skill_extra(SS_WEP_SWORD,
            owner->query_skill_extra(SS_WEP_SWORD) - skill_bonus);
    }

    skill_bonus = 0;
    owner->remove_prop(WIELD_PROP);
    owner->add_fatigue(-(owner->query_fatigue() / 3));
    owner->remove_khopesh_intox_shadow();

    return 0;
}
