
/*
 * This is an example monster (humanoid npc) containing references 
 * and explanations for many of the basic features that a monster 
 * may have. It will be of help to those who are getting started on 
 * coding monsters in Genesis. Coded by Maniac@Genesis
 */

#pragma strict_types

inherit "/std/monster";            // Inherit for monsters
inherit "/d/Genesis/lib/intro";    // Inherit for introing monsters  

#include <ss_types.h>      // Monsters usually need skills
#include <macros.h>        // Useful general purpose macros 
#include <stdproperties.h> // Monsters require properties
#include <const.h>         // Useful constants e.g. genders
#include <tasks.h>         // Used in our special attack

#define ARMOUR_DIR "/doc/examples/armours/"


void
create_monster() 
{
    // D E S C R I P T I O N S

    /* 
     * If you want your monster to have a unique name, get the name 
     * banished (see "help banish"). Few monsters need to be unique 
     * though! If you furthermore want the monster's name to show up 
     * in the player's who list after introing, then use the efun 
     * set_living_name().
     */ 

    // Use "sman <function>" to look up the exact definitions. 
 
    set_name("borak");                     // (met) name
    add_name(({"warrior", "barbarian"}));  // Other name(s)
    set_race_name("human");                // Monster's race
    set_adj(({"grim", "black-haired"}));   // (non-met name) adjectives 
    set_title("the Barbarian");            // For introductions
    set_gender(G_MALE);

    set_long("A light-skinned lean-featured barbarian with a " +
             "furrowed brow and keen black eyes which " +
             "take in every detail of his surroundings. He has " +
             "long matted black hair and powerful looking limbs.\n"); 

    // S T A T S  
    /* 
     * The function default_config_npc() can be handy to set all of 
     * the npc's stats to the given number.
     */ 
    default_config_npc(80);

    /* 
     * Or, a call can be made to the function set_base_stat() 
     * for each stat you want to configure individually. 
     * The possible stats are SS_STR, SS_DEX, SS_CON, 
     * SS_INT, SS_WIS, SS_DIS, from /sys/ss_types.h 
     */ 
    set_base_stat(SS_DIS, 100); 


    // S K I L L S  
    /* 
     * For information about skills, see "man skills" and 
     * "man skill_list". 
     */ 
    set_skill(SS_UNARM_COMBAT, 75); 
    set_skill(SS_DEFENCE, 65); 
    set_skill(SS_AWARENESS, 60); 
    set_skill(SS_BLIND_COMBAT, 60); 
    set_skill(SS_LOC_SENSE, 45); 


    // P R O P E R T I E S 
    add_prop(CONT_I_HEIGHT, 189);     // Height (cm)
    add_prop(CONT_I_WEIGHT, 80000);   // Weight without inventory (grams)
    add_prop(CONT_I_VOLUME, 80000);   // Volume without inventory (ml) 

    /* We want to accept some items, this property is there by default */ 
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    /* 
     * There are a huge number of properties available to configure your 
     * monster. Some of the more common ones are summarised below. 
     * Others you can search for using "man -k *keyword*" or checking 
     * /sys/stdproperties.h. Read "man <property>" before using it. 
     * If the monster should always be able to succeed in attacking, use 
     * NPC_I_NO_FEAR. Use NPC_I_NO_LOOKS if you don't want an automatic 
     * appearance description subloc appearing in its desc. The properties 
     * LIVE_M_NO_BODY and LIVE_M_NO_CORPSE are useful for non-corporeal 
     * monsters or those with a special kind of remains. Undead monsters 
     * should have LIVE_I_UNDEAD set. Use LIVE_I_NEVERKNOWN if only its 
     * nonmet name is used, or LIVE_I_ALWAYSKNOWN if only its met name 
     * should be used (very rare). The properties LIVE_I_SEE_DARK and 
     * LIVE_I_SEE_INVIS can be used to give the monster special visual 
     * capabilities. The properties LIVE_I_NON_FORGET and LIVE_I_NON_REMEMBER 
     * refer to whether a player can forget and remember the monster's name. 
     * LIVE_I_QUICKNESS can speed up or slow down your monster in combat. 
     * For details about resistances to various types of attack, see 
     * "man resistance". 
     */ 


    // M I S C E L L A N E O U S 
    set_hp(query_max_hp());   // Start off healthy!(?)
    set_alignment(0);         // Alignment of the monster

    // A C T S  
    /* 
     * The acts will occur in random order at regular 
     * intervals until they are all used up, then it
     * starts again. The acts only occur when the monster 
     * is not in combat and players are present. 
     */ 
    set_act_time(3); 
    add_act("ponder booze and women."); 
    add_act("emote looks around restlessly."); 
    add_act("say Yam bam budda boo!"); 
    add_act("say This place needs livening up."); 

    // C O M B A T   A C T S
    /* 
     * The cacts will occur in random order at regular 
     * intervals until they are all used up, then it 
     * starts again. The acts only occur while the monster 
     * is in combat. 
     */ 
    set_cact_time(2); 
    add_cact("growl fanatically"); 
    add_cact("swear"); 
    add_cact("say Oola yakkatoola!"); 
    add_cact("say No-one gets away with that!");  
}


//                        E Q U I P M E N T
/*
 * Function:     equip_me
 * Description:  Equip this monster. This is best called 
 *               from the code which clones the monster before
 *               moving it into its start room. 
 */ 
void
equip_me()
{
    seteuid(getuid());      // Required for the right to clone!
    clone_object(ARMOUR_DIR+"mail")->move(this_object()); 
    command("wear mail"); 
}


//                   S P E C I A L   A T T A C K 

/* 
 * See "sman special_attack" for a description of this function.
 * Here we implement a simple stun special where Borgak attempts 
 * to head-butt his enemy. 
 */ 
int
special_attack(object enemy)
{
    int result, stun_duration;
    string impact, reaction, onlooker_reaction;

    // Only execute the special attack 1 in 8 rounds on average
    if (random(8))
        return 0;  // Continue with the normal attacks

    /*
     * See "man tasks" for a thorough explanation of the task system. 
     * Here we apply resolve_task to calculate whether the monster has
     * managed to head-butt his opponent. 
     */ 
    result = resolve_task(TASK_ROUTINE+50, 
                          ({ TS_DEX, TS_DIS, SS_UNARM_COMBAT }), 
                          enemy, 
                          ({ TS_DEX, TS_WIS, SS_DEFENCE })); 

    if (result < 1) 
    {
        tell_object(enemy, query_The_name(enemy) + 
                           " misses you with an attempted head-butt" +
                           " and falls flat on " + query_possessive() + 
                           " face.\n"); 
        tell_watcher(QCTNAME(this_object()) + " misses " + 
                     QTNAME(enemy) + " with an attempted head-butt" +
                     " and falls flat on " + query_possessive() + 
                     " face.\n", enemy); 
        command(({"grumble", "sigh", "swear"})[random(3)]); 
        return 0;
    } 

    stun_duration = min(max(result / 5, 5), 15);   // Stun duration in seconds
    switch (stun_duration) 
    {
        case 1..5 : 
            impact = " a glancing "; 
            reaction = " feel a bit groggy"; 
            onlooker_reaction = " looks a bit groggy"; 
            break; 
        case 6..10 : 
            impact = " a powerful "; 
            reaction = " feel quite dizzy"; 
            onlooker_reaction = " looks quite dizzy"; 
            break; 
        case 11..15 :  
            impact = " a vicious ";
            reaction = " feel very shocked"; 
            onlooker_reaction = " looks very shocked"; 
            break; 
    } 

    tell_object(enemy, query_The_name(enemy) + " strikes you with" +
                impact + "head-butt. You" + reaction + ".\n"); 
    tell_watcher(QCTNAME(this_object()) + " strikes " + QTNAME(enemy) + 
                 " with" + impact + "head-butt. " + QCTNAME(enemy) + 
                 onlooker_reaction + ".\n", enemy); 
    enemy->add_attack_delay(stun_duration, 1);   // Check the sman entry! 

    return 0;   // We want this attack to be additional to standard combat.     
}


//                   I N T R O D U C T I O N S
/* 
 * The monster may introduce itself in ways different to the defaults 
 * provided in /d/Genesis/lib/intro.c, by masking the functions.
 */   

/*
 * Function name: greet
 * Description:   This function makes the npc do a greeting to people it
 *                already know and to fellow npc's. It is possible to
 *                redefine, note however that it should never contain an
 *                'introduce myself' command.
 * Arguments:     object who - the living that introduced to me
 *
 */                   
public void
greet(object who)
{
    // This guy won't greet an enemy
    if (member_array(who, query_enemy(-1)) > -1) 
        command("kick " + OB_NAME(who)); 
    else 
        command("nod briefly " + OB_NAME(who)); 
}


/*
 * Function name:   introduce
 * Description:     This function makes the npc do an introduction to a
 *                  player that has not been introed to it earlier. The
 *                  function may be redefined to create variety.
 * Arguments:       object who - the living that introduced to me
 *
 */
public void
introduce(object who)
{
    // This guy won't intro to an enemy
    if (member_array(who, query_enemy(-1)) > -1) 
        command("kick " + OB_NAME(who)); 
    else 
    {
        command("introduce myself to " + OB_NAME(who));
        command("bow slightly");
    } 
}                     


//                     R E A C T    T O    A T T A C K S

/* 
 * A monster may do or say something if it is attacked. 
 * Also other monsters may react, for instance team members, 
 * so they should be notified.  
 */  


/* 
 * Function:      notify_attacked
 * Description:   Called when a friend is attacked. 
 * Arguments:     object friend -   the friend who was attacked
 *                object attacker - the attacker
 */ 
void
notify_attacked(object friend, object attacker)
{
    if (!objectp(query_attack()))   // If not fighting anyone
        command("assist " + OB_NAME(friend)); 
}


/* 
 * Function:    react_attack() 
 * Description: React to an attack. This called by alarm from 
 *              attacked_by() below.
 * Arguments:   object attacker  -  the attacker.
 */ 
void
react_attack(object attacker)
{
    if (!CAN_SEE_IN_ROOM(this_object()))
        command("say Dark or light, you're dead!"); 
    else if (!CAN_SEE(this_object(), attacker)) 
        command("say Curse you, who did that?"); 
    else 
        command("say to " + OB_NAME(attacker) + 
                " I'll have your head for this!");

    // Here you could make team-members react if you teamed them
    query_team_others()->notify_attacked(this_object(), attacker); 

    /* 
     *  The best place to set up the team of npcs is usually the 
     *  code which clones them. Choose a leader and call 
     *  team_join(team_member) in it for each team member. 
     */ 
}


/* 
 *  Function:     attacked_by() 
 *  Description:  A hook called by the combat system when a living
 *                is attacked. 
 *  Arguments:    object attacker  -  the attacking living. 
 */ 
public void
attacked_by(object attacker)
{
    ::attacked_by(attacker); 
    set_alarm(1.0, 0.0, &react_attack(attacker)); 
}


//                   R E A C T   T O   E M O T E S 

// See "sman emote_hook" for a description of this function.
public void
emote_hook(string emote, object actor, string adverb)
{
    if (actor->query_npc()) 
        return;             // Don't want to get into some nasty recursion.

    switch (emote) 
    {
        case "smile" :
        case "grin" :
            if (member_array(actor, query_enemy(-1)) > -1) 
                command("smile sarcastically " + OB_NAME(actor)); 
            else
                command("peer " + OB_NAME(actor)); 
            break;
        case "kick" :
        case "spit" :
        case "slap" : 
            if (!objectp(query_attack()))
                command("kill " + OB_NAME(actor)); 
            else 
                command("glare " + OB_NAME(actor));
            break;
        case "kiss" :
        case "snuggle" :
        case "french" :  
            if (member_array(actor, query_enemy(-1)) > -1)
                command("puke " + OB_NAME(actor)); 
            else if (actor->query_gender() == G_FEMALE) 
            {
                if (my_opinion(actor) < 25) 
                    command("french " + OB_NAME(actor)); 
                else 
                    command(({"puke", "gag"})[random(2)]); 
            } 
            else
                command("kick " + OB_NAME(actor)); 
            break; 
    } 
}


/* 
 * See "sman emote_hook_onlooker" for a description of the function  
 * for reacting to emotes carried out on other people in the room
 * or having no target. 
 */ 


//                        R E A C T   T O   G I F T S
/* 
 * Obviously not every monster needs to receive objects 
 * and react to them, but some, especially quest npcs, 
 * may need to. 
 */ 

/* 
 *  Function:     react_give
 *  Description:  React to being given an object by a living. This is
 *                called by alarm from enter_inv() below. 
 *  Arguments:    object obj   -    the given object
 *                object from  -    the living who gave it
 */ 
void 
react_give(object obj, object from)
{
    /* 
     * Well, if the gift giver has gone or can't be seen, what to 
     * do? You might have a different reaction in mind, especially
     * based on the type of item it is. 
     */ 
    if (!objectp(from) ||
        !objectp(present(from, environment(this_object()))) || 
        !CAN_SEE(this_object(), from) ||
        !CAN_SEE_IN_ROOM(this_object())) 
    {
        command("peer suspiciously"); 
        command("drop "+OB_NAME(obj));
    }
    else if (member_array(from, query_enemy(-1)) > -1) 
    {
        command("glare suspiciously " + OB_NAME(from)); 
        command("drop " + OB_NAME(obj)); 
    } 
    /* 
     * If the item is special to the monster, do something with 
     * it, otherwise he could just give it back.
     */  
    else if (obj->query_alco_amount() > 0) 
    {
        command("grin " + OB_NAME(from)); 
        if (!command("drink " + obj->query_pname())) 
        {
            command("curse"); 
            command("give " + obj->query_pname() + " to " + OB_NAME(from)); 
        }
    } 
    else 
    {
        command("say You can keep this!");
        command("give "+OB_NAME(obj)+" to "+OB_NAME(from));
    }
}


/* 
 * The function enter_inv is defined in /std/container.c
 * It is a very useful function to know, so take some
 * time to learn how it works! In this case we use it 
 * to react to something being given to this monster 
 * by a living. 
 */ 
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);   // Remember to call this!!
    if (living(from)) 
        set_alarm(1.0, 0.0, &react_give(obj, from));
}
