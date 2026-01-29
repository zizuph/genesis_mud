/*
 * File : war-mace.c
 *
 * A typical dwarven weapon, with extra bonus for hill dwarves. It has a 
 * damaging special, which may stun the victim.
 * (stun: /d/Krynn/common/objects/legs_wound.c)
 * 
 * Blizzard, 5.07.2003
 * Last update: 20.07.2003, Blizzard:
 * Added defence penalty for hill dwarves.
*
* Louie 2005-07- Removed stun special, players cannot prevent
* other players from not being able to move/do commands.
* Adjusted HIT/PEN to be within correct range for balance
* as defined in <man weapons>.
*/


/*
 * Note by Navarre, November 22th 2005:
 *
 * This item was one of many inappropriate items that was created.
 * It got continously upgraded as time went by. Its time to set it back to
 * an acceptable state. Especially since it is guarded by rising_hero size
 * npcs.
 * - I allow all dwarves to get the special features of the weapon, not just
 *   Neidars, it is after all a dwarven mace, not a neidar mace.
 * - I lowered the difference in stats of the weapon from 14 in pen and 14 in hit
 *   between dwarves and non dwarves. They still get the speed and the attack special.
 *   So it is still a big advantage for them.
 * - I capped the max damage for the special attack that is added to the mace to be 300
 *   instead of 400.
 * - Add_fatigue was changed from -3 to -7 to atleast add a slight effect, people were
 *   recovering from the fatigue penalty before they got hit from the penalty again
 *   which made the penalty non-noticable.
 */

// Navarre Nov 4th 2008, fixing missing period in the hit descriptions.

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <options.h>

#define TO_HIT           40
#define TO_PEN           39
#define DEFENCE_PENALTY   5

object   wielder;
int      alarm_id;

create_weapon()
{
    set_name(({"war-mace", "mace", "club" }));
    set_adj( ({"dwarven", "war" }) );
    set_short("dwarven war-mace");
    set_long("Like others of its type, this dwarven mace is made entirely " +
        "of steel, with a blunt head mounted upon an eighteen inch long " +
        "shaft. The head is a double-sided hammer, with small spikes " +
        "sticking from it, which are to increase the damaging effect. In " +
        "result, the weapon reminds you of a warhammer, but it is not as " +
        "massive. There are several small rondels protecting and " +
        "strengthening the grip. By the design, this weapon would " +
        "obviously suit the hill dwarven fighting style.\n");
    
    add_item(({ "rondel", "rondels", "disks", "disk" }),
        "The rondels are small disks of metal shaped into the decorative " +
        "design. They are also to strengthen the grip.\n");
    add_item(({ "head", "hammer", "hammer-head" }),
        "What differs this weapon from others of its type is the head. " +
        "Usually, it has a form of the ball, while this one is ended with " +
        "a double-sided hammer, with a small but sharp spikes on it.\n");
    add_item(({ "spikes", "spike" }),
        "The spikes are placed in three vertical lines around the " +
        "hammer head. One in the middle, and two at its both sides.\n");
    add_item( "shaft",
        "The shaft is about eighteen inches long and made entirely of " +
        "prime quality dwarven steel.\n");
    add_item( "grip",
        "The grip of the weapon is strengthened by several small disks " +
        "of metal.\n");
             
    set_hit(TO_HIT);
    set_pen(TO_PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_RIGHT);

    set_wf(TO);
    set_keep(1);
    set_likely_dull(1);
    set_likely_break(1);
    
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }) );
    add_prop(OBJ_S_WIZINFO, "This war-mace was constructed by a Neidar " +
        "blacksmith long time ago, and after that blessed by clerics of " +
        "Reorx. It was designed for dwarves and the Neidar favourite " +
        "features have been taken under consideration. That is why the " +
        "mace is the most effective in the hands of the hill dwarves, when " +
        "the other races may find it a bit uncomfortable to grip. Neidars " +
        "enjoy swinging this mace and it comes to them with an amazing ease " +
        "(they gain additive quickness of 15). This mace has also a " +
        "damaging special, which if hits the legs, makes the victim " +
        "unable to walk for a short while. The special will make the " +
        "wielder tired faster. Also if the wielded is a hill dwarf, every " +
        "hit delivered to his enemies will make him more tired. Also the " +
        "offensive fighting style leaves the dwarf more vulnerable to " +
        "attacks.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "The mace has been designed by a dwarven blacksmith and blessed by " +
        "the clerics of Reorx.\n", 10,
        "In dwarven circles it is affectionately known as the 'Knee-Crusher' " +
        "and is rumoured to have been forged by the legendary dwarven " +
        "blacksmith. However, if you ask a dwarf about the name of the " +
        "creator, they usually just grunt at you. The sure thing is " +
        "the mace has been given to the hill dwarf clansmen, that they " +
        "may carve a place for themselves amongst the giants and ogres " +
        "in their area. The nickname of the weapon comes from the fact " +
        "that ogres and giants are much bigger than dwarves, whose the " +
        "best way to defeat those wild creatures was to smash their " +
        "knees so they may finish them at their own level. The war-mace " +
        "has been passed from hero to hero, occasionally finding its " +
        "way into non-dwarven hands.\n", 20,
        "The weapon is the most effective in the hands of the hill dwarven " +
        "warrior, while other races may find it a bit uncomfortable " +
        "to grip. However, the offensive style of fighting leaves the " +
        "dwarf more vulnerable to attacks, and is more physicaly " +
        "draining for him.\n", 65 }) );
        
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, 1800 + random(300));
}

public void
wield_message()
{
 

}

public mixed
wield(object ob)
{   
    wielder = TP;

    if ( wielder->query_race() != "dwarf" && !wielder->query_npc() )
    {
        set_hit(TO_HIT - 3);
        set_pen(TO_PEN - 3);
        wielder->update_weapon(TO);

        write("You wield the " + short() + ", but you realize it was not " +
            "designed for your hands.\n");
        say(QCTNAME(wielder) + " wields the " + short() + ", but " + 
            HE(wielder) + " seems to be disappointed.\n");
        return 1;
    }
    
    //Else you are a dwarf or a npc
    set_hit(TO_HIT + 3);
    set_pen(TO_PEN + 3);
    wielder->update_weapon(TO);
       
    wielder->add_prop(LIVE_I_QUICKNESS, 
    wielder->query_prop(LIVE_I_QUICKNESS) + 15);
    wielder->query_combat_object()->cb_update_speed();
        
    write("You grasp the " + short() + " confidently. It fits your " +
          "hand perfectly.\n");
    say(QCTNAME(wielder) + " grasps the " + short() + " confidently " +
        "in " + HIS(wielder) + " hand.\n");
        
    if ( TP->query_skill(SS_DEFENCE) > 5 )
    {
        TP->set_skill_extra(SS_DEFENCE,
        TP->query_skill_extra(SS_DEFENCE) - DEFENCE_PENALTY);
    }

   write("You tighten your grip on the " + short() + " and make a few " +
        "quick swings with it. It is extremely well balanced and was " +
        "obviously designed for someone like you!\n");
   say(QCTNAME(wielder) + " tightens " + HIS(wielder) + " grip on the " + 
        short() + " and makes a few quick swings, testing " +
       "its balance.\n");

  return 1;
}

public int
unwield(object what)
{
    set_this_player(query_wielded());
    
    if ( TP->query_race_name()=="dwarf" || TP->query_npc())
    {
        TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - 15);
        TP->query_combat_object()->cb_update_speed();

        TP->set_skill_extra(SS_DEFENCE,
            TP->query_skill_extra(SS_DEFENCE) + DEFENCE_PENALTY);

        if ( alarm_id )
            remove_alarm(alarm_id);
    }
    
    set_hit(TO_HIT);
    set_pen(TO_PEN);
    TP->update_weapon(TO);

    return 0;
}

/* did_hit borrowed from the spiked steel tessto, by Arman. */

public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, 
        int dam)
{
    object wound, me;
    string place, str;
    mixed  hitres;
    int    penet, skill;
    
    me = query_wielded();
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if ( wielder->query_race() == "dwarf" || wielder->query_npc() )
    {                       /* Only dwarves get the special */
     
        skill = wielder->query_skill(SS_WEP_CLUB);
        
        if ( !random(18 - (skill / 10)) )
        {
            penet  = wielder->query_stat(SS_STR) + (TO_PEN * 2) + skill;
       
       /* Penet capped. 2.01.2004 - Blizzard.
        */
            penet  = MIN(300, penet);
            
            hitres = enemy->hit_me(penet, W_BLUDGEON, me, -1);
            
            if ( !random(4) )
                place = "legs";
            else
                place = hdesc;
                
            if (hitres[0] < 0)
                hitres[0] = 0;
            
            switch ( hitres[0] )
            {
            case 0..10:
                str = ", leaving a small bruise";
            break;
            case 11..60:
                str = ", leaving a badly looking bruise";
            break;
            default:
                str = ". You hear a bone crushing sound";
            break;
            }
 
            me->catch_msg("You deftly flip the grip on your " +
                short() + " and with a powerful swing you slam it into the " + 
                place + " of " + QTNAME(enemy) + str + ".\n");
            enemy->catch_msg(QCTNAME(wielder) + " deftly flips the grip on " +
                HIS(wielder) + " " + short() + " and with a powerful swing " +
                HE(wielder) + " slams it into your " + place + str + ".\n");
            me->tell_watcher(QCTNAME(wielder) + " deftly flips the grip on " +
                HIS(wielder) + " " + short() + " and with a powerful swing " +
                HE(wielder) + " slams it into the " + place + " of " +
                QTNAME(enemy) + str + ".\n", enemy);
                
 
            wielder->add_fatigue(-1);        /* Each special makes the 
                                                wielder a bit more tired. */
            if ( enemy->query_hp() <= 0 )
            {
                enemy->do_die(wielder);

                return 1;
            }

/*
            if ( (hitres[0] > 0) && place == "legs" )           
*/
            if ( (hitres[0] > 0) && place == "legs" &&
                wielder->query_npc() )
            {                                // If we hit our enemy in the 
                                             // legs, we make him unable 
                setuid();                    // to move for a while. 
                seteuid(getuid(TO));
                wound = present("Legs_Wound", enemy);
               
                if ( wound )
                {
                    wound->remove_object();
                    wound = clone_object(KROBJECT + "legs_wound");
                }
                else
                {
                    wound = clone_object(KROBJECT + "legs_wound");
                }
            
                wound->move(enemy, 1);

            }
            
            return 1;
        }

    }

    switch(phurt)
    {
    case -1:
    case -2:
	if (!wielder->query_option(OPT_GAG_MISSES))
	{
	    wielder->catch_msg("You swing your " + short() + " at " + 
	        QTNAME(enemy) + " but miss.\n");
	}
	if (!enemy->query_option(OPT_GAG_MISSES))
	{
	    enemy->catch_msg(QCTNAME(wielder) + " swings the " + short() +
	      " at you but misses.\n");
	}
	wielder->tell_watcher_miss(QCTNAME(wielder) + " swings the " + 
	    short() + " at " + QTNAME(enemy) + " but misses.\n", enemy);
	break;

    case 0:
	wielder->catch_msg("You almost scratch the " + hdesc + " of " + 
	    QTNAME(enemy) + " with the " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " almost scratches you with the " +
	  short() + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " almost scratches the " + 
	    hdesc + " of " + QTNAME(enemy) + " with the " + short() + 
	    ".\n", enemy);
	break;

    case 1..4:
	wielder->catch_msg("You graze the " + hdesc + " of " +
	  QTNAME(enemy) + " with a savage swing of your " + 
	  short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " grazes your " + hdesc +
	  " with a savage swing of the " + short() + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " grazes the " + hdesc +
	  " of " + QTNAME(enemy) + " with a savage swing of the " +
	  short() + ".\n",enemy);
	break;

    case 5..9:
	wielder->catch_msg("You pound the " + hdesc + " of " +
	  QTNAME(enemy) + " mightily with your " + short() + ", bruising " + 
	      POSSESSIVE(enemy) + " " + hdesc + " moderately.\n");

	enemy->catch_msg(QCTNAME(wielder) + " pounds your " + hdesc + 
	    " with a mighty swing of the " + short() + ", bruising it " +
	    "moderately.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " pounds the " + hdesc +
	  " of " + QTNAME(enemy) + " with the " + short() + 
	  ", bruising it moderately.\n",enemy);
	break;

    case 10..19:
	wielder->catch_msg("You hurt " + QTNAME(enemy) + " badly with " +
	  "a wicked blow of your " + short() + ", tearing bloody trails " +
	  "along " + POSSESSIVE(enemy) + " " + hdesc +
	  " with its spikes.\n");
	enemy->catch_msg(QCTNAME(wielder) + " hurts you badly with " +
	  "the " + short() + ", tearing bloody trails along your " +
	  hdesc + " with its spikes.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " hurts " + QTNAME(enemy) +
	  " badly with the " + short() + ", tearing bloody trails " +
	  "along their " + hdesc + " with its spikes.\n",enemy);
	break;

    case 20..29:
	wielder->catch_msg("You tear bloody chunks from the " +
	  hdesc + " of " + QTNAME(enemy) + " with the spikes " +
	  "of your " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " tears bloody chunks " +
	  "from your " + hdesc + " with the " + short() +
	  "!\n");
	wielder->tell_watcher(QCTNAME(wielder) + " tears bloody chunks " +
	  "from the " + hdesc + " of " + QTNAME(enemy) + " with " +
	  "the " + short() + "!\n",enemy);
	break;

    case 30..46:
	wielder->catch_msg("You hammer the " + hdesc + " of " +
	  QTNAME(enemy) + " with a powerful swing of your " +
	  short() + ", breaking many bones.\n");
	enemy->catch_msg(QCTNAME(wielder) + " hammers your " + hdesc +
	  " with a powerful swing of the " + short() + ", breaking many " +
	  "of your bones!\n");
	wielder->tell_watcher(QCTNAME(wielder) + " hammers the " + hdesc + 
	  " of " + QTNAME(enemy) + " with a powerful swing of the " +
	  short() + ", breaking many bones!\n",enemy);
	break;

    case 47..69:
	wielder->catch_msg("You violently crush the " + hdesc + 
	  " of " + QTNAME(enemy) + " into a shapeless bloody mass " +
	  "with your " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " violently crushes your " +
	  hdesc + " into a shapeless bloody mass with the " + short() + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " violently crushes " +
	  "the " + hdesc + " of " + QTNAME(enemy) + " into a " +
	  "shapeless bloody mass with the " + short() + ".\n",enemy);
	break;

    case 70..89:
	wielder->catch_msg("You smash the " + hdesc + " of " +
	  QTNAME(enemy) + " into the ground, mortally wounding " +
	  OBJECTIVE(enemy) + " " +
	  "with a devastating swing of your " + short() + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " smashes your " +
	  hdesc + " into the ground with a devastating blow of the " +
	  short() + ". Things are starting to look dimmer, and " +
	  "you are on the verge of falling into a deep darkness.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " smashes the " + hdesc +
	  " of " + QTNAME(enemy) + " into the ground with a " +
	  "devastating swing of the " + short() + ".\n",enemy);
	break;

    default:
	wielder->catch_msg("You hear the sickening sound of bones " +
	  "breaking, as your " + short() + " massacres the " + hdesc + 
	  " of " + QTNAME(enemy) + ". The spikes penetrate deep " +
	  "into " + POSSESSIVE(enemy) + " flesh, leaving blood " +
	  "flowing from deep gaping wounds in the shattered limb.\n");
	enemy->catch_msg("You hear the sickening sound of your bones " +
	  "breaking as " + QTNAME(wielder) + " massacres your " + 
	  hdesc + " with " + POSSESSIVE(wielder) + " " + short() + 
	  ". The spikes penetrate deep into your flesh, leaving blood " +
	  "flowing from deep gaping wounds in the shattered limb.\n");
	wielder->tell_watcher("You hear the sickening sound of bones " +
	  "breaking as " + QTNAME(wielder) + " massacres the " + hdesc +
	  " of " + QTNAME(enemy) + " with " + POSSESSIVE(wielder) + 
	  " " + short() + ". The spikes penetrate deep into the " +
	  "flesh of " + QTNAME(enemy) + ", leaving blood flowing " +
	  "from the shattered limb.\n", enemy);
	break;

    }

    if ( phurt < 7 )
        return 1;

    if ( wielder->query_race_name()=="dwarf" )
    {
        wielder->add_fatigue( -(random(7)) );       
                                        // Make the wielder become tired
                                        // faster, if he has a speed
    }                                   // bonus (hill dwarves).

    return 1;
}
