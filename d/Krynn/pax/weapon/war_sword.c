/*
 * File : war_sword.c
 * Verminaard's war-sword.
 * It has a very powerfull special, that tries to hit all of your
 * current enemies.
 * 

 * Blizzard, 16.06.2003
 * Last modified: 10.06.2003, lowered the special damage and made it
 *                random (not almost always maximum as it was ;) ).
 * 2005-01-09 - Cotillion
 * - Don't hurt query_enemy(-1), they might not even be in the room.
 * - Use correct damage type
 *
 * 2005-08-30 - Blizzard
 * - Only npcs will stun players. Remove the checks if stun is allowed
 *   on Krynn again.
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

#define  TO_HIT     49
#define  TO_PEN     54

create_weapon()
{
    set_name(({"war-sword", "sword", "warsword"}));
    set_short("jet black war-sword");
    set_adj( ({ "composite", "jet", "black", "war" }) );
    set_long("This composite sword is similar to a great sword but due to " +
        "its construction it is both lighter and stronger. The sword is " +
        "made from up to ten strips of metal that are then twisted and " +
        "forged together to give a flexible but strong blade that can " +
        "resist more punishment than a standard sword. The blade edges " +
        "are also combined with carbon so that a sharper edge can be " +
        "achieved. This is why the sword has increased damage and a " +
        "lower weight. The sword is a martial weapon and does slashing " +
        "damage. Due to the method in which it is forged, the sword has " +
        "an intricate pattern of spirals and twists on its two faces.\n");

    add_item(({ "spirals", "twists", "blade", "pattern" }),
        "As you hold the " + short() + " up to the light, you notice " +
        "a pattern of spirals and twists, that seem to be dancing on " +
        "the dark blade.\n"); 
    
    set_hit(TO_HIT);
    set_pen(TO_PEN);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    set_wf(TO);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "The method used to create this " + short() + 
        "is not common, but thanks to it the sword is lighter and sharper " +
        "than other, the same sized weapons. It has a extremely lethal " +
        "special - the wielded makes a wide swing, in hope to his all " +
        "of his enemies at once. It will work only from the first line - " +
        "if the wielder is taking hits. The special may also stun the " +
        "enemies. Undeads get stunned for a little longer than others. " +
        "However, after performing the swing the wielder's " +
        "parry and defence will be lowered for some time.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "This sword was probably magically enchanted and it may possess " +
        "powers, not available for other weapons.\n", 10,
        "In hands of the skilled warrior this sword is extremely lethal, " +
        "and it may kill many enemies with a single swipe.\n", 40,
        "While fighting on the first line, the sword makes you to " +
        "perform a lethal swipe that hurts, and even stuns, all of " +
        "your enemies. The undeads will have even more problems to " +
        "stand against it. However, after such attack you will have your " +
        "guard lowered, what makes you to be hit easier.\n", 60 }) );
    
    set_likely_dull(2);
    set_likely_break(2);
    set_keep(1);
    
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VALUE, 2800 + random(500));
}

public int
calculate_damage(object ob, int result)
{
    int dex = ob->query_stat(SS_DEX);
    int str = wielder->query_stat(SS_STR);
    int wis = wielder->query_stat(SS_WIS);
    int skill, damage;
    
    skill = (((str * 2) + wis) / 4) + 10;
    
    if ( result > 100 )
        result = 100;
    
    if ( result < 0 )
        result = 0;
                    
    damage = F_PENMOD(query_pen(), skill);
       
    damage = damage - ((100 - result) * (13 / 10) );
    
    if ( damage < 100 )
        damage = 100;    
        
    if ( !random(500) )
        return (damage * 6);
    else
        return damage;

}

public int
calculate_result(object enemy)
{
    int success;
    
    success = wielder->resolve_task(TASK_ROUTINE, 
        ({ SS_WEP_SWORD, TS_DEX, TS_WIS }), enemy, 
        ({ SS_DEFENCE, SS_PARRY, TS_DEX }));

    if ( success > 0 )
        return success;
    else
        return 0;
}

/* Function name: print_wielder_messages
 * Description  : Prints special messages to the wielder
 * Arguments    : object *enemy_list   - list of all enemies of the player
 *                object *targets      - list of people who got hit 
 *                object *killed       - those who got killed by the special
 * Returns      : The combat message.
 */
public void
print_wielder_messages(object *enemy_list, object *targets, object *killed)
{
    string tmp_str;
    
    switch ( sizeof(targets) )
    {
    case 0:
        if ( sizeof(killed) )
        {
            if ( sizeof(enemy_list) )
            {
                /* Those who got hit, died. But we still have enemies to fight... */         
                tmp_str = "that your attack was successful. " +
                    "However, you realize this battle is not over yet..";
            }
            else
            {
                /* None of our enemies survived, and those who live are not in our room */
                tmp_str = "the dead bodies of your enemies laying on " +
                    "the ground around you";
            }
        }
        else
        {
            /* We simple did not hit anyone. */
            wielder->catch_msg("\nWhen you recover your balance you " +
                "realize that your attack missed!\n\n");
                
            return;
        }
        break;
    case 1:
        if ( sizeof(enemy_list) > 1 )
        {
            /* We hit only one enemy, but there are more of them! */
            tmp_str = "that " + COMPOSITE_LIVE(targets) + " is staggering " +
                "and bleeding badly. You try to catch a breath since " +
                "there are more enemies waiting..";
        }
        else
        {        
            /* We hit only one enemy and he was our only opponent */
            tmp_str = "that " + COMPOSITE_LIVE(targets) + " is staggering " +
                "and bleeding badly";
            
            if ( sizeof(killed) )
            {
                /* We managed to hit some people and only one of those, who got hit, 
                   survived */
                tmp_str += ", but " + COMPOSITE_LIVE(killed) + 
                    ((sizeof(killed) > 1) ? " were " : " was ") + "less lucky";
            }
        }
        break;
    default:
        if ( sizeof(enemy_list) > sizeof(targets) )
        {
            /* We hit a few people ... */
            tmp_str = "that " + COMPOSITE_LIVE(targets) + " are " +
                "bleeding badly and hardly keeping their footing";
            /* ... and we managed to kill someone */
            if ( sizeof(killed) )
            {
                tmp_str += ", but " + COMPOSITE_LIVE(killed) + 
                    ((sizeof(killed) > 1) ? " were " : " was ") + "less lucky";

            }
            else
            {
                /* ... but someone avoided our attack! */
                tmp_str += ". However, some of your enemies managed " +
                    "to avoid your attack";
            }
                    
        }
        else
        {
            /* We managed to hit all our enemies. */ 
            tmp_str = "that " + COMPOSITE_LIVE(targets) + " are " +
                "bleeding badly and hardly keeping their footing";
        }
        break;
    }
         
    wielder->catch_msg("\nWhen you recover your balance you notice " +
        tmp_str + ".\n\n");

}

/* Function name: print_target_messages
 * Description  : Prints special messages to the targets
 * Arguments    : object tmp      - person who gets the message
 *                object *targets - list of people who got hit
 *                object *killed  - those who got killed by the special
 *                object *lucky   - those who managed to avoid the special
 * Returns      : The combat message.
 */
public void
print_target_messages(object tmp, object *targets, object *killed, 
    object *lucky)
{
    string ret_str;
    
    switch( sizeof(targets) )
    {
    case 0:   /* Noone was _just_ hurt (death was possible thou) */
        if ( member_array(tmp, lucky) != -1 )
        {
            if ( sizeof(killed) )
            {
                if ( sizeof(lucky) == 1 )
                {  
                    /* We managed to jump aside, someone before us had died. */
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(killed) +  
                        " being almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ". You desperately jump back, " +
                        "in the last moment avoiding this lethal attack";
                }
                else if ( sizeof(lucky) > 1 )
                {  
                    lucky -= ({ tmp }); 
                    /* We managed to jump aside, as well as someone before us. Someone 
                       died, however. */
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(killed) +
                        " being almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ". Then, as you see " + 
                        COMPOSITE_LIVE(lucky) + " jumping aside, " +
                        "you react instinctively and do the same, in " +
                        "the last moment avoiding the lethal attack";
                } 
            }
            else
            {
                if ( sizeof(lucky) == 1 )
                {
                    /* We managed to jump aside. */
                    ret_str = "\nIn a desperate attempt you jump back, " +
                        "in the last moment avoiding the lethal attack of " + 
                        QTNAME(wielder);
                }
                else if ( sizeof(lucky) > 1 )
                {
                    lucky -= ({ tmp });
                    /* We avoid the attack; someone avoided it too */
                    ret_str = "\nAs you see " + COMPOSITE_LIVE(lucky) + 
                        " jumping aside, you react instinctively and do " +
                        "the same, in the last moment avoiding the lethal " +
                        "attack";
                }
            }
        }
        break;
    case 1:  /* One person got hit - we or someone else. */
        if ( member_array(tmp, targets) != -1 )                // We are hit.
        {
            if ( !sizeof(lucky) )
            {
                if ( sizeof(killed) )
                {
                    /* We get hit by the special; Noone avodied it; Someone died */
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(killed) +  
                        " being almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ". You try to jump aside, but " +
                        "your moves are to slow and a moment later you " +
                        "stagger backwards, as you are hit by the " +
                        "lethal attack";
                }
                else if ( sizeof(killed) == 0 )
                {
                    /* We are hit, noone avoided the attack and noone died. */
                    ret_str = "\nUnfortunately, you were standing too " +
                        "close to " + QTNAME(wielder) + " and there was " +
                        "no time to avoid " + HIS(wielder) + " lethal " +
                        "attack. You stagger backwards, as the sharp blade " +
                        "tears into your body";
                }
            }
            else
            {
                /* We are hit; someone avoided the attack; someone died. */
                if ( sizeof(killed) )
                {
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(killed) + 
                        " being almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ". Then, as you see " +
                        COMPOSITE_LIVE(lucky) + " jumping aside, you " +
                        "try to do the same. However, a moment later, " +
                        "you feel a terrible pain and you realize that you " +
                        "have not managed to avoid this lethal attack";
                }
                else if ( sizeof(killed) == 0 )
                {
                    /* We are hit, but someone before us managed to avoid the attack;
                       someone died too. */
                    ret_str = "\nSeeing " + COMPOSITE_LIVE(lucky) + 
                        " jumping aside, you try to do the same. " +
                        "However, you were standing too close to " +
                        QTNAME(wielder) + " and you had no time to avoid " +
                        HIS(wielder) + " lethal attack. You stagger " +
                        "backwards, as the sharp blade tears into your body";
                }
            }
        }
        else if ( member_array(tmp, lucky) != -1 )   
        {                                    // That was not us who got hit
            if ( sizeof(lucky) == 1 )
            {
                /* We avoided the attack. */
                if ( sizeof(killed) )
                {
                    /* ...but someone got killed, someone else got hurt. */
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(targets) + 
                        " staggering backwards and " + COMPOSITE_LIVE(killed) + 
                        ", who " + ((sizeof(killed) > 1 ) ? "have " : "has ") +
                        "been almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ". You react instinctively and " +
                        "jump aside, in the last moment avoiding the " +
                        "lethal attack";
                }
                else if ( sizeof(killed) == 0 )
                    /* ...noone got killed, but someone got hurt */
                {
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(targets) +
                        " staggering backwards, as he got hit by the " +
                        "lethal attack of " + QTNAME(wielder) + ". You " +
                        "react instinctively and jump aside, in the last " +
                        "moment avoiding the heavy blade";
                }
            }
            else if ( sizeof(lucky) > 1 )
            {
                lucky -= ({ tmp });            // Reduce lucky ones by tmp.
                /* Someone else avoided too! */
                if ( sizeof(killed) )
                {
                    /* ...but someone got killed, and someone else got hurt */
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(killed) + 
                        " being almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ", while " + 
                        COMPOSITE_LIVE(targets) + " is only sent staggering " + 
                        "backwards by the force of attack. Luckily, you" + 
                        ((sizeof(lucky) > 1 ) ? ", " : " and ") + 
                        COMPOSITE_LIVE(lucky) + " managed to avoid the attack";
                }
                else if ( sizeof(killed) == 0 )
                {
                    /* ...noone got killed, but someone got hurt */
                    ret_str = "\nYou notice that " + COMPOSITE_LIVE(targets) +
                        "is sent staggering backwards by the force of the " +
                        "lethal attack of " + QTNAME(wielder) + ". Luckily, " +
                        "you" + ((sizeof(lucky) > 1 ) ? ", " : " and ") + 
                        COMPOSITE_LIVE(lucky) + " managed to avoid the attack";

                }    
            }
        }
        break;
    default:                                    /* We get hit */
        if ( member_array(tmp, targets) != -1 )
        {
            targets -= ({ tmp });
            if ( !sizeof(lucky) )
            {
                if ( sizeof(killed) )
                {
                    /* We get hit by the special; noone avodied it; someone got hit;
                       someone died */
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(targets) +
                        " staggering backwards and " + COMPOSITE_LIVE(killed) +
                        ", who " + ((sizeof(killed) > 1) ? "have " : "has ") +
                        "been almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ". You try to jump aside, but " +
                        "your moves are to slow and a moment later you " +
                        "feel a terrible pain, as you are hit by the " +
                        "lethal attack";
                }
                else
                {
                    /* We are hit, noone avoided the attack, someone got hit, noone died. */
                    ret_str = "\nAs you see " + COMPOSITE_LIVE(targets) +
                        " sent staggering backwards by the force of the " +
                        "lethal attack, you try to jump aside. " +
                        "Unfortunately, you were standing too " +
                        "close to " + QTNAME(wielder) + " and a moment " +
                        "later you feel a terrible pain when the sharp " +
                        "blade tears into your body";
                }
            }
            else
            {
                /* We are hit; someone avoided the attack; someone got hit or died. */
                if ( sizeof(killed) )
                {
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(killed) + 
                        " being almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ". Then, as you see " +
                        COMPOSITE_LIVE(lucky) + " jumping aside, you " +
                        "try to do the same. However, a moment later, " +
                        "you stagger backwards and you realize that like " +
                        COMPOSITE_LIVE(targets) + ", you have not managed " +
                        "to avoid this lethal attack";
                }
                else 
                {
                    /* We are hit, but someone before us managed to avoid the attack;
                       others got hurt, but noone died. */
                    ret_str = "\nSeeing " + COMPOSITE_LIVE(lucky) + 
                        " jumping aside, you try to do the same. " +
                        "However, you were standing too close to " +
                        QTNAME(wielder) + " and you had no time to avoid " +
                        HIS(wielder) + " lethal attack. You are sent " +
                        "staggering backwards, as the sharp blade tears " +
                        "into your body. For a short while you notice that " +
                        COMPOSITE_LIVE(targets) + ((sizeof(targets) > 1) ?
                            " were" : " was") + " hit too";
                }
            }
        }
        else if ( member_array(tmp, lucky) != -1 )   
        {                                    // That was not us who got hit
            if ( sizeof(lucky) == 1 )
            {
                /* We avoided the attack. */
                if ( sizeof(killed) )
                {
                    /* ...but someone got killed, someone else got hurt. */
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(targets) + 
                        " staggering backwards and " + COMPOSITE_LIVE(killed) + 
                        ", who " + ((sizeof(killed) > 1 ) ? "have " : "has ") +
                        "been almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ". You react instinctively and " +
                        "jump aside, in the last moment avoiding the " +
                        "lethal attack";
                }
                else
                    /* ...noone got killed, but someone got hurt */
                {
                    ret_str = "\nYou notice that " + COMPOSITE_LIVE(targets) +
                        ((sizeof(targets) > 1) ? " are" : " is") + 
                        "sent staggering backwards by the force of the " +
                        "lethal attack of " + QTNAME(wielder) + ". You " +
                        "react instinctively and jump aside, in the last " +
                        "moment avoiding the heavy blade";
                }
            }
            else if ( sizeof(lucky) > 1 )
            {
                lucky -= ({ tmp });            // Reduce lucky ones by tmp.
                /* Someone else avoided too! */
                if ( sizeof(killed) )
                {
                    /* ...but someone got killed, and someone else got hurt */
                    ret_str = "\nYou notice " + COMPOSITE_LIVE(killed) + 
                        " being almost torn apart by the heavy blade of " +
                        QTNAME(wielder) + ", while " + COMPOSITE_LIVE(targets) + 
                        ((sizeof(targets) > 1) ? " are" : " is") + " only " +
                        "sent staggering backwards by the force of attack. " +
                        "Luckily, you" + 
                        ((sizeof(lucky) > 1 ) ? ", " : " and ") + 
                        COMPOSITE_LIVE(lucky) + " managed to avoid the attack";
                }
                else
                {
                    /* ...noone got killed, but someone got hurt */
                    ret_str = "\nYou notice that " + COMPOSITE_LIVE(targets) +
                        ((sizeof(targets) > 1) ? " are" : " is") +
                        "sent staggering backwards by the force of the " +
                        "lethal attack of " + QTNAME(wielder) + ". Luckily, " +
                        "you" + ((sizeof(lucky) > 1 ) ? ", " : " and ") + 
                        COMPOSITE_LIVE(lucky) + " managed to avoid the attack";

                }    
            }
        }
        break;
    }
 
    /* Default message, should not happen though */
    if ( !strlen(ret_str) && member_array(tmp, targets) )
    {
        ret_str = "\nYou try to jump aside, but you are sent staggering " +
            "backwards, as the heavy blade tears into your body";
    }
      
    tmp->catch_msg(ret_str + ".\n\n");
}

public void
print_others_messages(object *targets, object *enemy_list)
{
    string tmp_str = "";

    if ( sizeof(targets) )
    {
        tmp_str = COMPOSITE_LIVE(targets) + " staggering " +
            "and bleeding badly";
    }
    else
    {
        tmp_str = "the heavy blade cutting the air";
    } 
    
    wielder->tell_watcher("\nAs you see " + tmp_str + ", you feel lucky you " +
        "were not a target of this lethal attack.\n\n", enemy_list);

}

public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
    int dam)
{
    object *enemy_list, tmp, stun, drawback, horse;
    object *targets = ({ });   // List of those who got hit by the special
    object *killed  = ({ });   // List of those who got killed by the special
    object *lucky   = ({ });   // Those who managed to avoid the special
    int    pen, size, i, sword_skill, result;
    string tmp_str, place;
    
    sword_skill = wielder->query_skill(SS_WEP_SWORD);
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    enemy_list = filter(all_inventory(environment(wielder)),
        &operator(==)(wielder, ) @ &->query_attack());
    
    if ( sizeof(enemy_list) < 2 )  
        return 0;                   // The special will work if we are a  
                                    // a target of at least two enemies.

    if ( !random(18 - (sword_skill / 10)) )    
    {   
        horse = wielder->query_steed();
        
        if ( horse )
        {
            wielder->catch_msg("You whirl your " + horse->steed_short() +
                " around, making a wide swing with your " + short() + ".\n");
            tell_room(E(wielder), QCTNAME(wielder) + " whirls " +
                HIS(wielder) + " " + horse->steed_short() + " around, " +
                "making a wide swing with " + HIS(wielder) + " " +
                short() + ".\n", wielder);
        }
        else
        {
            wielder->catch_msg("You stand firmly on the ground and blindly " +
                "make a wide swing with the " + short() + "!\n");
            tell_room(E(wielder), QCTNAME(wielder) + " stands firmly on the " +
                "ground and makes a wide swing with " + HIS(wielder) + " " +
                short() + "!\n", wielder);
        }

        if ( !wielder->query_npc() )    /* Make the wielder more tired */
            wielder->add_fatigue(-(wielder->query_max_fatigue() / 12));
         
        seteuid(getuid());
        
        drawback = present("War_Sword_Special", wielder);

        /* Let's decrease the wielder's ability to defend himself after   
           such attack. */
        if ( drawback )   
        {
            drawback->remove_it_and_set_new_penalty(wielder);
            clone_object(POBJ + "warsword_object")->move(wielder, 1);
        }
        else
        {
            clone_object(POBJ + "warsword_object")->move(wielder, 1);
        }
                
        for ( i = 0, size = sizeof(enemy_list); i < size; i++)
        {
            tmp = enemy_list[i];
            
            if ( calculate_result(tmp) )  // Check if we managed to hit
            {                             // this one. Add him to the
                targets += ({ tmp })  ;   // list if yes.
            }
            else                        // Else we add him to the list
            {                           // of those who were lucky enough
                lucky += ({ tmp });     // to avoid the special
            }

            if ( E(tmp) != E(wielder) ) // Check if the enemy is in
            {                           // the room with us. If not
                targets -= ({ tmp });   // remove him from target list,
                lucky   -= ({ tmp });   // as well as from the lucky ones.
            }
            
            if ( member_array(tmp, targets) != -1 ) // We have managed to hit 
            {                                       // this one.
                result = calculate_result(tmp);
                pen = calculate_damage(tmp, result);
                
                if ( pen > 500 )
                {
                    log_file("war_sword", extract(ctime(time()), 4) + ": " +
                        (interactive(tmp) ? tmp->query_name() : file_name(tmp)) +
                        " was hit for " + pen + " hp.\n", 500000);
                }
                                    
                //  tmp->heal_hp(-pen);
                tmp->hit_me(pen, W_SLASH, wielder, -1);

                stun = present("war_sword_stun", tmp);
                
                if ( tmp == wielder->query_enemy(0) )
                {
                    if ( stun )
                    {
                        stun->remove_sword_stun(tmp);
                        tmp->catch_msg("...but another blow makes " +
                            "you stagger again.\n");
                        //                       say("...but another blow sends " + HIM(tmp) +
                        //                           " stagering backwards again.\n", tmp);
 
                    }
      
        // Remove this check if stun is allowed on Krynn              
                    if ( query_wielded()->query_npc() )
                    {
                        stun = clone_object(POBJ + "sword_stun");
                        stun->move(tmp, 1); 
                    }
                }
                else if ( random(2) )
                {
                    if ( stun )
                    {
                        stun->remove_sword_stun(tmp);
                        tmp->catch_msg("...but another blow sends you " +
                            "staggering backwards.\n");
                        say("...but another blow sends " + HIM(tmp) +
                            " staggering backwards again.\n", tmp);
                    }
                    
        // Remove this check if stun is allowed on Krynn
                    if ( query_wielded()->query_npc() )
                    {
                        stun = clone_object(POBJ + "sword_stun");
                        stun->move(tmp, 1);
                    }
                }    
            }    
            
            /* I print hit messages to each target when he is hit, so he knows
               who got hit, avoided or died. But he will not see if someone is
               hit after him. (he is stunned then) */

            print_target_messages(tmp, targets, killed, lucky);
                
            if ( tmp->query_hp() <= 0 )
            {
                //                wielder->catch_msg("You hear a death cry coming from " +
                //                    "a nearby.\n");
                    
                killed += ({ tmp });
                place = ({ "chest", "right arm", "left arm", "stomach", 
                           "right leg", "left leg", "neck" })[random(6)];

                wielder->catch_msg("Hardly keeping " + HIS(tmp) +
                    " footing, " + QTNAME(tmp) + " makes a few steps. " +
                    "Then, trying to stop the bleeding from the gash " +
                    "on " + HIS(tmp) + " " + place + ", " +
                    HE(tmp) + " tumbles to the ground.\n");
                tmp->catch_msg("Hardly keeping your footing, you make " +
                    "a few steps. Then, trying to stop the bleeding from " +
                    "the gash on your " + place + ", you tumble " +
                    "to the ground and slowly lose your consciousness.\n");
                say("Hardly keeping " + HIS(tmp) + " footing, " +
                    QTNAME(tmp) + " makes a few steps. Then, trying to " +
                    "stop the bleeding from the gash on " + HIS(tmp) +
                    " " + place + ", " + HE(tmp) + " tumbles to the " +
                    "ground.\n", ({ wielder, tmp }) );
                    
                tmp->do_die(wielder);

                targets -= ({ tmp });
            }
        }
         
        print_wielder_messages(enemy_list, targets, killed);
        print_others_messages(targets, enemy_list);
                
        return 1;   
    }
    
    return 0;    
        
}

