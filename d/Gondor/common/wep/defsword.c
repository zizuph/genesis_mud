/*
 *      /d/Gondor/common/wep/defsword.c
 * 
 * Yet another magic weapon created by Xeros of GondorMud for use in the
 * Gondor domain in Genesis. Should always be placed somewhere _very_ tough
 * to get, since it is powerful (although there are much more powerful items),
 * and not picky in who it lets use it. 28 Nov 1993 
 *
 *      Modification log:
 *       9-mar-97, Olorin:      General revision,
 *                              reduced stat requirements.
 *       6-oct-01, Alto:        Fixed unwield room tell bugs.
 *      25-sep-06, Toby:        Fixed new line in wield function
 *                              Removed BSN
 *                              Fixed the MAGIC_AM_ID_INFO
 *      18-jun-08, Toby:        Fixed a missing space
 *
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>  
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define MIN_SKILL       60
#define MIN_INT         80
#define MIN_WIS         80
 
static int     Added_Skill1,
               Added_Skill2;

object  wielder;


public void
create_weapon()
{
    int     wh = 40 + random(6),
            wp = 30 + random(7);

    set_name("defender");
    set_pname("swords");
    add_pname("swords");
    add_pname("shortswords");
    add_name( ({ "weapon", "shortsword", "sword"}) );
    set_adj( ({ "red", "violet-edged", "short", }) );
    set_short("violet-edged red shortsword");
    set_long("This shortsword has a plain, notched red blade, that is "+
        "edged with a dazzling, transparent violet material. The pommel "+
        "holds a single, deep blue gemstone. The hilt, backwards "+
        "curving to form a C shaped guard over the hand, shelters a dark "+
        "hardwood handle wrapped tightly with a braided gold wire. ");

    set_default_weapon(wh,wp,W_SWORD,W_SLASH | W_IMPALE,W_ANYH, TO);
    
    add_prop(OBJ_I_LIGHT,  1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ( ({ 50 + random(25), "enchantment"}) ) );
    add_prop(MAGIC_AM_ID_INFO,({
            "The "+short()+" you hold in your hands radiates a variable aura of enchantment. ", 1, 
            "Furthermore, being swift, this sword hits fairly often but lightly. ", 30,
            "It is also capable of enhancing its owner's defensive skills, for a price. ", 50,
            "Tainted by its previous owners, the " +short()+ " has become quite cunning " +
            "and greedy, demanding a lot of concentration to master. ", 65,                               
            "It is also rather intelligent and wise, thus it will drain and burn those "+
            "that are mentally weaker than itself. ", 75}));

    add_prop(OBJ_S_WIZINFO,"The item can increase the wielder's "+
        "SS_PARRY (5 + 1/6 of the wielder's current skill) and SS_DEFENCE "+
        "(5 + 1/5 of the wielder's current skill), if the player's SS_INT "+
        "and SS_WIS total above the sword's int and wis which are calculated "+
        "by the following:  int="+MIN_INT+"+random("+(MIN_INT/2+1)+") and wis="+
        MIN_WIS+"+random("+(MIN_WIS/2+1)+"). "+
        "If the player's SS_WEP_SWORD is below "+(MIN_SKILL+1)+", they do not incur any "+
        "penalties or benefits from wielding the weapon. If they are below "+
        "the sword's int and wis, they lose all mana, 1/10 of their hp, "+
        "and can't use the weapon. If they are below 1/2 their max mana, "+
        "they will also fail to wield the weapon, and lose half their remaining "+
        "mana in the process. Success in wielding leads to loss of 1/5 "+
        "the wielder's mana, but they gain the _TEMPORARY_ skill benefits.");

    //add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_WEAPON(wp, W_SWORD) - 4000));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(wp, W_SWORD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE,  F_VALUE_WEAPON(wh,wp));
}

public int
wield(object wep)
{
    int     swordint =  MIN_INT + random(MIN_INT/2 + 1),
            swordwis =  MIN_WIS + random(MIN_WIS/2 + 1);

    Added_Skill1 = 0;
    Added_Skill2 = 0;

    if ( (TP->query_stat(SS_INT) + TP->query_stat(SS_WIS)) < (swordint + swordwis))
    {
        WRITE("A malevolent voice pierces your thoughts: You simpleton! "+
            "You fool! How dare you even attempt to use me. Put me down "+
            "this instant before I slice you to ribbons and scatter your "+
            "parts across the land!\n");
        TP->add_mana(-(TP->query_mana()));
        TP->heal_hp(-((TP->query_hp())/10));
        WRITE("You feel a tremendous mental drain as laughter echos through "+
            "your head and a burst of flame erupts from the "+short()+".\n");
        SAY(" is burned in an attempt to wield the "+short()+".\n");
        return -1;
    }

    if ( TP->query_skill(SS_WEP_SWORD) <= MIN_SKILL)
    {
        WRITE("You wield the "+short()+".\n");
        SAY(" wields the "+short()+".\n");
        return 1;
    }

    if ( (TP->query_max_mana()/2) > TP->query_mana())
    {
        WRITE("The "+short()+" demands too much of your mental power and "+
            "you fail to wield it.\n");
        TP->add_mana(-(TP->query_mana())/2);
        WRITE("You feel mentally drained from your attempt to wield the "+short()+".\n");
        SAY(" looks extremely drained by "+POSSESSIVE(TP)+" failed attempt to "+
            "wield the "+short()+".\n");
        return -1;
    }

    Added_Skill1 = (5 + ((TP->query_skill(SS_PARRY)) / 6));
    Added_Skill2 = (5 + ((TP->query_skill(SS_DEFENCE)) / 5));

    if ((TP->query_skill(SS_PARRY) + Added_Skill1) > 100)
        Added_Skill1 = (100 - (TP->query_skill(SS_PARRY)));    
    if ((TP->query_skill(SS_DEFENCE) + Added_Skill2) > 100)
        Added_Skill2 = (100 - (TP->query_skill(SS_DEFENCE)));    
    TP->set_skill_extra(SS_PARRY,
        TP->query_skill_extra(SS_PARRY) + Added_Skill1);
    TP->set_skill_extra(SS_DEFENCE,
        TP->query_skill_extra(SS_DEFENCE) + Added_Skill2);
    WRITE("A melodic voice whispers in your mind: 'Greetings Master.'\n");
    WRITE("You wield the "+short()+".\n");
    SAY(" wields the "+short()+".\n");
    TP->add_mana(-((TP->query_mana())/4));
    WRITE("You feel an irresistable mental drain from the "+short()+".\n");
    return 1;
}  

public int
unwield(object wep) 
{
    object wielder = query_wielded();

    wielder->set_skill_extra(SS_PARRY,
        (wielder->query_skill_extra(SS_PARRY)-Added_Skill1));
    
    wielder->set_skill_extra(SS_DEFENCE,
       (wielder->query_skill_extra(SS_DEFENCE)-Added_Skill2));

    wielder->catch_tell("A sad voice whispers in your mind: "
        + "'Farewell for now, Master.'\n");
    wielder->catch_tell("With regret you unwield the "+short()+".\n");

    say(QCTNAME(wielder)+" unwields the "+short()+".\n");
    return 1; 
}
