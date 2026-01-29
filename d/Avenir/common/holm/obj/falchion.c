// basket-hilt falchion  /d/Avenir/common/holm/obj/falchion.c
// creator(s):           Lilith, Jan 1997
// purpose:              To be wielded by Hunter shadow-elves
// note:                 This is a magical Sword of Quickening. 
//            Drawbacks: Wielder cannot be more than 50% intoxicated, thus 
//                         player regens health more slowly.
//         Requirements: It checks for DEX, AWARENESS, and SWORD.
//                       It cannot be wielded if gloves are worn
//                       and if intox > 50%. Uses mana and fatigue.
//              Effects: Adds LIVE_I_QUICKNESS prop +55 to wielder.
//                       Adds disarm prevention prop to wielder.
//     Associated files: /d/Avenir/common/holm/obj/falchion_shadow.c
//                       To monitor wearing of hand-armour and 
//                       use of alcohol.
/*
 * Revisions:
 *	Lilith, May 1999: Updated glove_check function.
 *	Lilith, Aug 1999: Added shadowing.
 *	Lilith, Aug 2002: Added infidel check.
 *	Lilith, Jul 2003: Added hoard_test and removed undead check
 *	Lilith, Dec 2003: Updated hit/pen per man wep guide
 *	Lilith, Feb 2004: Removed cwicweolfor name
 *	Lilith, Oct 2004: Added likely break etc
 *	Lilith, Aug 2014: Added check for offering prop in the wield function
 *	Cotillion, Feb 2015: LIVE_I_QUICKNESS 100 -> 55
 * 	Cotillion, Apr 2015: Removed stealth added non-breaking due to lack of AoB approval
 * 	Lucius, Sep 2017: Removed ENEMY check.
 *  Zizuph, May 2021: Add function to remove quickness as per man documents.
 *  Lilith, Sep 2021: Fixed intox check to 50% of max.
 *  Lilith, Dec 2021: Removed anti-ranger and anti-undead checks.
 */
#pragma strict_types 

inherit "/d/Avenir/inherit/weapon";
inherit "/lib/keep";

#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/include/deities.h"
#include "/d/Avenir/include/relation.h"

#define MINIM        50
#define COST         30
#define INCR         55
#define WIELD_PROP   "wielded_avenir_soq_"
#define ALTAR_PROP   "_offered_at_altar"
#define F_QUESTOR    "_on_falchion_quest"
#define METAL        "/d/Avenir/common/holm/obj/quicksilver"
#define F_QUEST_LOG  "/d/Avenir/log/quest/falchion_quest"
#define F_CLONE_LOG  "/d/Avenir/log/misc/falchion_clones"
#define SHADOW       "/d/Avenir/common/holm/obj/falchion_shadow"

#define TP    	this_player()
#define TO	    this_object()
#define HIS(x)	(x)->query_possessive()


object sword_shadow;
int alarm_id, alarm_id2, alarm_id3;

/* 
 *  Long desc of the sword
 */
string 
my_long()
{
    return "A handsome, broad sword of medium length with a gently "+
           "curving edge.  The steel blade is vaguely sickle-shaped, "+
           "double-edged, and has a tapering point, making it effective "+
           "as both a cutting and thrusting weapon.  Crimson and black "+
           "silk laces are braided around the steel handle, which is "+
           "long enough to fit two hands.  The pommel is fitted with an "+
           "incredibly detailed golden spider whose arching legs secure "+
           "it to the handle.  A basket-hilt of gold-plated steel has "+
           "been woven in an elaborate web of surprising beauty and "+
           "functionality.\n   Some runes have been etched into the "+
           "blade, near the hilt.\n";
}

/* 
 *  For the runes add_item
 */
string 
exa_runes()
{
    string str;
    
    if (TP->query_prop(WIELD_PROP))
    {
        str = "With the falchion live in your hand and the "+
              "vibrant rapport whispering along your nerve-"+
              "endings, the runes speak to you of blood "+
              "sacrifice, the spider goddess Aclolthayr, "+
              "speed and grace in combat, and magical forging "+
              "upon a simple anvil.\n";
    }
    else if (TP->query_skill(SS_LANGUAGE) > 30 + random(25))
    {
        str = "The first rune appears to be a symbol for ritual "+
              "sacrifice, or perhaps execution. The second one is a "+
              "glittering spiral. The third implies something like "+
              "'haste', while the latter symbol is that of an anvil.\n";
    }   
    else
        str = "The first and third symbols are meaningless to you. "+
              "The second one, however, is a glittering spiral, and "+
              "The fourth symbol resembles an anvil.\n";

    return "There are four runes etched into the blade, all of which "+
           "seem to be in constant, twisting motion. You recognize the "+
           "glyphs as being Sybarite in origin.\n"+ str;
}


void 
create_weapon()
{
    set_name("falchion");
    add_name(({"sword_of_quickness", "sword", "weapon"}));
    set_adj(({"basket-hilt", "broad"}));
    add_adj(({"basket", "hilt"}));  /* Removed 'runed' reference */
    set_short("basket-hilt falchion");
    set_keep(1);
    set_long(my_long());                                   
    set_hit(50);
    set_pen(46);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    // only one magical falchion at a time.
    set_hands(W_LEFT);
    set_wf(TO);

    add_item(({"hilt", "basket", "handle", "basket hilt"}),
        "Gold-plated steel has been woven in an elaborate, dizzying, "+
        "web-like pattern that forms a basket hilt for protection of "+
        "the wielding hand. The handle itself is rather long, to "+
        "help balance the weight of the blade.\n");
    add_item(({"pattern", "patterns", "weave" }),
        "This weave was done by someone obviously expert in the art of "+
        "working molten metal. The pattern is such that the eye cannot "+
        "follow the sinuous lines without becoming confused.\n");
    add_item(({"pommel", "pommel on falchion", "spider", "golden spider",
        "spider on pommel"}), 
        "A golden spider perches on the end of the handle. It is so "+
        "incredibly detailed that it seems alive.\n");
    add_item(({"laces", "silk laces", "ribbons", "black laces", 
        "crimson laces"}),
        "Silken ribbons in crimson and black have been laced around "+
        "the long handle, improving the grip.\n");
    add_item(({"blade", "runes", "rune", "etching", "runes on falchion"}), 
        "@@exa_runes@@");

    add_prop(SPECIAL_OFFERING, 1);
    add_prop(ACLOLTHAYR_OFFERING, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 2000); /* about 1/4 normal */
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50, 40) * 2); /* Magical */

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "life" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This "+ short() +" is enchanted.\n", 10,
        "You detect a faint resonance emanating from within it.\n", 15,
        "You must establish rapport with it before you can wield.\n", 20,
        "Rapport cannot be established if you are wearing gloves "+
		"or if you are too intoxicated.\n", 25,
        "When rapport is established the nerves are stimulated.\n", 30,
        "This improves the speed of your reflexes during combat.\n", 40}));
    add_prop(OBJ_S_WIZINFO, "This sword will increase LIVE_I_QUICKNESS "+
        "by "+ INCR +" if the person has high enough DEX, AWARENESS, "+
        "and SWORD, as well as "+ COST +" mana. The player cannot be "+
        " more than 50% intoxicated or wearing anything on his/her hands "+
        "to wield, and will lose 1/2 of max fatigue upon unwielding.\n");
    seteuid(getuid(this_object()));
    SCROLLING_LOG(F_CLONE_LOG, " falchion was cloned.");

}

/*
 * Function     : glove_check
 * Description  : This function checks to see if ob is hand
 *                armour that is being worn.
 * Arguments    : obj ob - the object to be tested.
 * Returns      : int 0: Not worn hand armour, 
 *                int 1: worn hand armour.                        
 */
int 
glove_check(object ob)
{
    int     at;

    if (!(ob->query_worn()))
        return 0;

    at = ob->query_at();

    if (at & A_R_HAND)
        return 0;
    else if (at & A_HANDS)
        return 1;
    else
        return 0;
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
    int go, tox_max;
    object *gloves;

    /* Is it broken? If so, dont wield */
    if (query_prop(OBJ_I_BROKEN))
        return "It is broken in such a way that you cannot wield it.\n";

    /* I'm an infidel/enemy of Sybarus, the sword doesn't like me */
    if (IS_INFIDEL(this_player()))
    {
        this_player()->heal_hp(-50);
        return "The "+ short() +" twists out of your grasp and "+
               "lands on your foot, causing you great pain.\n"+
               "The gods of Sybarus will not allow their gifts "+
               "be used by their Enemies.\n";
    }

    /* This was done back in the days of the Emerald vamps and when
	 * the permitted values for haste in objects was much higher.
	 * I'm removing it, since guilds are balanced relative to each
	 * other and code targeting specific guilds is now unfair.
	 * -Lilith Dec 2021 
    /* We enhance and accelerate life, not death.
     * Undeads may use it, but do not get the full benefits.
    
    if (this_player()->query_prop(LIVE_I_UNDEAD))
    {
	TP->catch_msg("You grasp the hilt of the "+ short() +
	    ", you become aware of a flicker of life spreading across "+
	    "your palm. Something within you seeks to answer but the "+
	    "sensation dies out as you struggle to do so.\n");

	return 1;
    }    
     */
    /* Is living wearing hand armour? If so, don't wield */
    if (sizeof(gloves = filter(all_inventory(TP), "glove_check", TO)))
        return "The flesh of your palm must be in contact with the "+
               "hilt. You cannot establish rapport with the "+ short()+
               " while wearing gloves.\n";

    /* Does player have more than 50% alcohol level? If so, don't wield */  
    tox_max = TP->intoxicated_max() / 2;	
    if (TP->query_intoxicated() > (tox_max) && (!TP->query_prop(I_DRANK_WITH_SYBARUN_GOD)))
        return "You have too much alcohol in your system to establish "+
               "rapport with the "+ short() +".\n";

    /* Does living have enough mana? If not, don't wield */
    if (TP->query_mana() <= COST) 
        return "You do not have the mental energy necessary to establish "+
               "rapport.\n";
    
    /* Lets set some stat and skill requirements to wield */
    go = TP->query_stat(SS_DEX) / 4;          /* Mortal: 100/4 = 25 */
    go += TP->query_skill(SS_WEP_SWORD) / 3;  /* Mortal:  90/3 = 30 */
    go += TP->query_skill(SS_AWARENESS) / 2;  /* Mortal:  90/2 = 45 */
                                              /* random(100) < 50 fails */
    if ( (random(go) < MINIM) && (!TP->query_prop("_soq_wielder")) )
    {
        TP->add_mana(-(COST/3));    
        return "You try to wield the "+ short() +", but fail to establish "+
               "rapport.\n";
    }

    /* All checks have passed, proceed with wielding */
    TP->add_mana(-COST);
    TP->catch_msg("With full contact between the skin of your palm and the "+
        "hilt of the "+ short() +", you become aware of a deep and full "+
        "resonance originating within it.\nSomething within you answers "+
        "the vibrant non-sound whispering along your nerve-endings, and "+
        "you feel intensely, profoundly, alive.\n");
    say(QCTNAME(TP)+" balances the hilt of the "+short()+" in "+
        TP->query_possessive() +" hand.\n");

    if (!TP->query_prop(WIELD_PROP))
    {
        TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) + INCR);
        TP->add_prop(WIELD_PROP, 1);

        /* With the basket-hilt and the connection between palm and 
           hilt so strong it is nearly impossible to force to unwield */
		/* Removing this. Rangers are being recoded to the standard guild
		   library and this ability will no longer be "unbalanced".
		   -Lilith Dec 2021
        TP->add_prop("_ranger_i_not_disarm", 
           TP->query_prop("_ranger_i_not_disarm") +1 );
		*/
    }

    (sword_shadow = clone_object(SHADOW))->shadow_me(TP);
    sword_shadow->set_sword(this_object());

    SCROLLING_LOG(F_CLONE_LOG, capitalize(TP->query_real_name()) +
            " wielded a falchion.");

    return 1;
}


/*
 * Function    : remove_falchion_perks
 * Description : Remove the quickeness benefit of the falchion
 *               when player is wearing glove on left hand.
 */
int
remove_falchion_perks()
{
    object owner = query_wielded();

    if (owner->query_prop(WIELD_PROP))
    {
        owner->remove_prop(WIELD_PROP);
        owner->add_prop(LIVE_I_QUICKNESS,
            owner->query_prop(LIVE_I_QUICKNESS) - INCR);
        owner->add_prop("_ranger_i_not_disarm",
            owner->query_prop("_ranger_i_not_disarm") - 1);
	owner->add_fatigue(-(owner->query_fatigue() / 2));
        return 1;
    }
    return 0;
}


/* 
 * Function    : unwield
 * Description : Unwield a weapon
 * Arguments   : object wep - the weapon to unwield
 */
mixed 
unwield(object wep)
{
    object owner = query_wielded();

    remove_falchion_perks();

    if (objectp(sword_shadow))
    {
	owner->remove_falchion_shadow();
	sword_shadow->remove_shadow();
	sword_shadow = 0;

	if (!query_interactive(environment(this_object())))
	    return 0;

	owner->catch_tell("You break rapport with the "+ short() +
	    ".\nFor a moment, "+
	    "the ever-present hum reverberates along your nerve-endings like "+
	    "a hammer striking a bell, and then it is gone, leaving you with "+
	    "profound and mystifying sense of loss.\n");
    }

    return 0;
}

/* *****************  Falchion quest functions below  ***************** */

/* 
 * Function name:   do_vision
 * Description:     The special effect alarm when this object is offered 
 *                  at an altar to Aclolthayr. It is Called by the altar,
 *                  through the function altar_special, below.
 * Arguments:       None. 
 * Returns:         1 - success; 0 - failure.
 */
int
do_vision()
{
    if (living(environment(TO)))
    {
        environment(TO)->catch_tell("\n     Your vision blurs as a fine spider's "+
            "web seems to weave itself before your eyes.\n   ...you see before "+
            "you a busy marketplace...\n                 ...coals glow in a "+
            "shadow-draped room and you hear the clang of metal against metal.\n"+
            "      You feel a sense of urgency.\nYour blood pounds in your "+
            "ears and the strange webbing unravels.\n");
        SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
            " was sent a vision.\n");
        return 1;
    }
    return 0;
}

/* 
 * Function name:   do_blood
 * Description:     The special effect alarm when this object is offered 
 *                  at an altar to Aclolthayr. It is Called by the altar,
 *                  through the function altar_special, below.
 * Arguments:       object altar - the altar that caused this function
 *                  to be called.
 */

void
do_blood(object altar)
{
    object metal;    
    
    tell_room(environment(altar), "The legs on the "+ altar->short() +
        " seem to shift, causing the chains to rattle.\nIn a sudden, "+
        "bewildering flash, the pool of blood at your feet is trans"+
        "formed into a glossy sheet of silvery metal.\n");

    setuid();
    seteuid(getuid());
    metal=clone_object("/d/Avenir/common/holm/obj/quicksilver");
    metal->move(environment(altar), 1);

    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
        " caused blood to be transformed.\n");

    alarm_id = 0;
    alarm_id2 = 0;
}

/* 
 * Function name:   altar_special
 * Description:     The special effect when this object is offered at an altar 
 *                  to Aclolthayr. It is Called by the altar.
 * Arguments:       altar - The altar object. 
 * Returns:         1 - success; 0 - failure.
 */
int
altar_special(object altar, object player)
{
    if (alarm_id)
    {
        tell_object(player, "You've tried that already.\n");
        return 0;
    }

    /* Lets prevent multiple people from doing the quest with this sword. */
    if (query_prop(ALTAR_PROP) && (!player->query_prop(F_QUESTOR)))
    {
        tell_object(player, "The falchion is no longer an acceptable "+
            "offering.\n");
        return 0;
    }
    if (query_prop(ALTAR_PROP) && 
       (query_prop(ALTAR_PROP) != player->query_real_name()))
    {
        tell_object(player, "The falchion is no longer an acceptable "+
            "offering.\n");
        return 0;
    }
    if (!player->query_prop(I_MADE_BLOOD_OFFERING))
    {
	tell_object(player, "It must be cleansed in the blood sacrifice "+
            "before you can offer it.\n");
        return 1;
    }	

    tell_object(player, "You hold the "+ short() +" high in the air "+
        "above your head and extend it toward the "+ altar->short() +
        ".\nSomething blows through you like a cool breeze, making "+
        "your nerve-endings tingle.\nEcstacy overwhelms you, pounding "+
        "into your head, forcing you to your knees.\nA cry of joy "+
        "and pain rips from your throat as the overwhelming Presence "+
        "of the goddess Aclolthayr settles fleetingly within your mind.\n");

    tell_room(environment(player), QCTNAME(player) +" holds "+ 
        HIS(player) +" "+ short() +" high above "+ HIS(player) +
        " head and extends it toward the "+ altar->short() +".\n"+
        QCTNAME(player) +" falls to "+ HIS(player) +" knees, "+
        "crying out a sound of both pleasure and pain.\n", player);

    SCROLLING_LOG(F_QUEST_LOG, capitalize(TP->query_real_name()) +
        " offered the falchion at altar.\n");

    add_prop(ALTAR_PROP, player->query_real_name());
    player->add_prop(F_QUESTOR, 1);

    if (player->query_prop(I_MADE_BLOOD_OFFERING))
    {
        alarm_id = set_alarm(200.0, 0.0, &do_vision());
        alarm_id2 = set_alarm( 100.0, 0.0, &do_blood(altar));
    }
    return 1;
}


                        
