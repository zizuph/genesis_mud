
/* 
 * This is an example monster (humanoid npc) containing references 
 * to and explanations about some of the basic features that a 
 * monster can have. 
 * Coded by Maniac. 
 */ 

#pragma strict_types               // See "man pragmas" 

inherit "/std/monster";            // Inherit for monsters 
inherit "/d/Genesis/lib/intro";    // Inherit for intro-ing monsters 

#include <ss_types.h>              // Monsters usually need skills 
#include <macros.h>                // Useful general purpose macros 
#include <stdproperties.h>         // For reference to properties 
#include <const.h>                 // Useful constants e.g. genders 
#include <cmdparse.h>              // Used for action types here 
#include <wa_types.h>              // Attack / hitloc related defs 

void 
create_monster() 
{

    /* 
     * DESCRIPTIONS. 
     * If your monster must have a unique name, i.e. one that no 
     * player can use, get the name banished (see "help banish"). 
     * If you want the monster's name to show up in players' "who 
     * lists" after introductions, then use the efun 
     * "set_living_name". 
     * "sman <function>" gives exact documentation. 
     */ 

    set_name("auleb");                        // (met) name 
    add_name(({"warrior", "barbarian"}));     // Other name(s) 
    set_race_name("human");                   // Race 
    set_adj(({"spirited", "black-haired"}));  // (non-met name) adjectives 
    set_title("the Barbarian");               // Title for introductions 
    set_gender(G_MALE);                       // male gender 

    // Long description can be seen by examining the npc. 
    set_long("A light-skinned lean-featured barbarian with a " + 
            "furrowed brow and keen black eyes. He has " + 
            "long matted black hair and powerful looking " + 
            "limbs.\n"); 


    /* STATS. 
     * The function default_config_npc() can be handy to set 
     * all of the npc's stats to the given number, e.g. 
     * default_config_npc(80); 
     * It's also possible a call could be made to the function 
     * set_base_stat() for each stat you want to configure 
     * individually. e.g. set_base_stat(SS_DIS, 100); 
     * The possible stats are SS_STR, SS_DEX, SS_CON, 
     * SS_INT, SS_WIS, SS_DIS, from /sys/ss_types.h. 
     * Here the function set_stats() is used to set them 
     * all in one go, in the standard order i.e. from 
     * SS_STR to SS_DIS as listed above.  
     */ 
    set_stats(({95, 95, 90, 55, 65, 95})); 


    /* SKILLS. 
     * Set up the monster's skills. Just some basic ones here. 
     * For information about skills, see "man skills" and 
     * "man skill_list". 
     */ 
    set_skill(SS_WEP_SWORD, 85); 
    set_skill(SS_UNARM_COMBAT, 55); 
    set_skill(SS_DEFENCE, 65); 
    set_skill(SS_AWARENESS, 60); 
    set_skill(SS_BLIND_COMBAT, 60); 
    set_skill(SS_LOC_SENSE, 45); 



    // PROPERTIES..  
    add_prop(CONT_I_HEIGHT, 194);     // Height (cm) 
    add_prop(CONT_I_WEIGHT, 80000);   // Weight without inventory (grams) 
    add_prop(CONT_I_VOLUME, 80000);   // Volume without inventory (ml) 

    /* 
     * PROPERTIES CONTINUED..
     * This monster will accept some items, but by default monsters 
     * refuse to accept anything. So the property providing the 
     * effect, "no accept give", is removed. 
     */ 
    remove_prop(LIVE_M_NO_ACCEPT_GIVE); 

    /* 
     * PROPERTIES CONTINUED.. 
     * There are a great many properties available to configure your 
     * monsters. Some of the more common ones are summarised below. 
     * Others you can search for using "man -k *keyword*" or checking 
     * the file "/sys/stdproperties.h". Information about an individual 
     * property is available in "man <property>". 
     *   If the monster should always be able to succeed in attacking, 
     * use NPC_I_NO_FEAR. NPC_I_NO_LOOKS will stop a description of 
     * appearance (based on opinion) appearing in its description. The 
     * properties LIVE_M_NO_BODY and LIVE_M_NO_CORPSE are useful for 
     * non-corporeal monsters or those with unusual remains. Undead 
     * monsters should have LIVE_I_UNDEAD set. 
     *   Use LIVE_I_NEVERKNOWN if only the non-met name of the monster 
     * should ever be seen, or LIVE_I_ALWAYSKNOWN if only its met name 
     * should be used (very rare). 
     *   The properties LIVE_I_SEE_DARK and LIVE_I_SEE_INVIS can be used 
     * to give the monster special visual capabilities. The properties 
     * LIVE_I_NON_FORGET and LIVE_I_NON_REMEMBER refer to whether a 
     * player can forget and remember the monster's name. LIVE_I_QUICKNESS 
     * can speed up or slow down your monster in combat (see also 
     * "man combat"). For details about resistances to various types 
     * of attack, see "man resistance". 
     */ 


    set_alignment(0);         // Neutral alignment 

    /* 
     * ACTS. 
     * The acts will occur in random order at intervals 
     * until they are all used up, then the cycle starts 
     * again. The interval durations are based on the number 
     * of "heartbeats" you specify in the act time. The 
     * acts only occur when the monster is not in combat 
     * and players are present. 
     */ 
    set_act_time(3);      // an act every three "heartbeats" 
    add_act("ponder booze."); 
    add_act("ponder the deadly guardians of the ancient ruins."); 
    add_act("hmm"); 
    add_act("say The hallowed platinum armband of Jru'kq'h " + 
            "must be found!"); 


    /* 
     * COMBAT ACTS. 
     * Similar in cycling/interval handling to acts, but 
     * only occur while the monster is in combat. 
     */ 
    set_cact_time(2); 
    add_cact("scowl savagely"); 
    add_cact("swear"); 
    add_cact("say No-one gets away with that!"); 

    // clone and ready equipment 
    equip(({ "../armours/mail", "../weapons/elf_slayer" }));
}

/* 
 * The function special_attack() is called by the standard combat 
 * routines. See "sman special_attack" for a description. 
 * Here is an implementation of a simple stun special where the 
 * monster attempts to head-butt his enemy. 
 */ 
int
special_attack(object enemy)
{
    int result, stun_duration; 
    string impact, reaction, onlooker_reaction; 

    // Only execute the special attack 1 in 8 rounds on average 
    if (random(8)) 
        return 0;  // Combat round continues 

    // See "man combat" (and "sman cb_tohit" and "man cb_tohit") 
    if (query_combat_object()->cb_tohit(W_NONE, 55, enemy) <= 0) 
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
        return 0; // Combat round continues 
    } 

    stun_duration = 8 + random(15);   // Stun duration in seconds 
    switch (stun_duration) 
    {
        case 1..12 : 
            impact = " a glancing "; 
            reaction = " feel a bit groggy"; 
            onlooker_reaction = " looks a bit groggy"; 
            break; 
        case 13..17 : 
            impact = " a powerful "; 
            reaction = " feel quite dizzy"; 
            onlooker_reaction = " looks quite dizzy"; 
            break; 
        default : 
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
    enemy->add_attack_delay(stun_duration, 1);   // Standard stun handling. 

    return 0;   // Combat round continues 
} 



/* 
 * Reactions to introduction/greetings start here. 
 * 
 * A monster may introduce itself in ways different to the defaults 
 * provided in /d/Genesis/lib/intro.c, by masking the provided functions. 
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
    // He won't greet an enemy! 
    if (member_array(who, query_enemy(-1)) > -1) 
    { 
        command("kick " + OB_NAME(who)); 
    } 
    else if (!objectp(query_attack())) 
    {  
        command("nod briefly " + OB_NAME(who)); 
    } 
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
    // He won't intro to an enemy 
    if (member_array(who, query_enemy(-1)) > -1) 
    { 
        command("kick " + OB_NAME(who)); 
    } 
    else 
    { 
        command("introduce myself to " + OB_NAME(who)); 
        command("bow " + OB_NAME(who)); 
    } 
} 



/* 
 * Reactions to attacks start here. 
 * 
 * A monster may do or say something if it is attacked. 
 * Also other monsters may react if this npc is attacked, 
 * for instance team-mates, who would have to be notified. 
 */ 
/* 
 * Function:      notify_attacked 
 * Description:   Called from an associated npc when it is attacked, 
 *                for example one in the same team. This npc will 
 *                assist if not already fighting. 
 * Arguments:     object friend -   the friend who was attacked 
 *                object attacker - the attacker 
 */ 
void
notify_attacked(object friend, object attacker)
{
    // If not fighting anyone, assist. 
    if (!objectp(query_attack())) 
    { 
        command("assist " + OB_NAME(friend)); 
    } 
}



/* 
 * Function:    react_attack 
 * Description: React to an attack. This called by alarm from 
 *              the function "attacked_by" below. 
 * Arguments:   object attacker  -  the attacker. 
 */ 
    void 
react_attack(object attacker)
{
    // Vary reactions depending on darkness/invisibility 
    if (!CAN_SEE_IN_ROOM(this_object())) 
    { 
        command("say Dark or light, you're dead!"); 
    } 
    else if (!CAN_SEE(this_object(), attacker)) 
    { 
        command("say Curse you, who did that?!"); 
    } 
    else 
    { 
        command("say to " + OB_NAME(attacker) + 
                " May your deathwish be granted, fool!"); 
    } 

    /* 
     * Here you could give team-members the chance to react. 
     * The called function would have to be defined in them. 
     */ 
    query_team_others()->notify_attacked(this_object(), attacker); 

    /* 
     *   To assemble a team of npcs, somewhere there must be 
     *   code to choose a leader and call team_join(team_member) 
     *   for each team-mate. This could be carried out in 
     *   the code that clones the npcs, for example, or 
     *   alternatively in the npc code itself - when they 
     *   first encounter each other. Here, the former case 
     *   is assumed. 
     */ 
}



/* 
 *   Function:     attacked_by 
 *   Description:  Called by the combat system when a living is 
 *                 attacked. See "sman attacked_by" for documentation. 
 *   Arguments:    object attacker  -  the attacking living. 
 */ 
    public void 
attacked_by(object attacker) 
{ 
    ::attacked_by(attacker); 
    set_alarm(1.0, 0.0, &react_attack(attacker)); 
} 



// Reactions to emotes start here. 

/* 
 * Function:     react_aggression 
 * Description:  Called from this npc's implementation of "emote_hook" 
 *               when he receives a threatening or offensive emote. 
 * Arguments:    emote   -  the verb of the emote e.g. "kick" 
 *               actor   -  the emote actor 
 */ 
void 
react_aggression(string emote, object actor) 
{
    if (member_array(actor, query_enemy(-1)) > -1) 
    { 
        command("finger " + OB_NAME(actor)); 
    } 
    else if (!objectp(query_attack())) 
    { 
        command("kill " + OB_NAME(actor)); 
    } 
}



/* 
 * Function:      react_ingratiatory 
 * Description:   Called from this npc's implementation of emote_hook 
 *                when he receives an ingratiatory emote. 
 * Arguments:     emote  - the verb of the emote e.g. "compliment" 
 *                actor  - the emote actor 
 */ 
void 
react_ingratiatory(string emote, object actor) 
{
    if (member_array(actor, query_enemy(-1)) > -1) 
    { 
        command("laugh hatefully " + OB_NAME(actor)); 
    } 
    else if (!objectp(query_attack())) 
    { 
        command("smile " + OB_NAME(actor)); 
    } 
}



/* 
 * Npcs are notified when people emote to them. See 
 * "sman emote_hook" for documentation. 
 * 
 * On a related note, see also "sman emote_hook_onlooker" for a 
 * description of a function that's called when people emote in 
 * the room (e.g. just "smile") or to other present livings. 
 */ 
public void 
emote_hook(string emote, object actor, string adverb, object *oblist, 
        int cmd_attr) 
{ 
    if (actor->query_npc()) 
        return; 

    // Reactions to threatening or offensive emotes 
    if (cmd_attr & ACTION_THREATENING || 
            cmd_attr & ACTION_OFFENSIVE) 
    { 
        react_aggression(emote, actor); 
    } 
    // Reactions to ingratiatory emotes 
    else if (cmd_attr & ACTION_INGRATIATORY) 
    { 
        react_ingratiatory(emote, actor); 
    } 
} 



/* 
 *  Function:     react_give 
 *  Description:  React to receiving an object from a living. This 
 *                is called by alarm from "enter_inv" below. Most 
 *                monsters deal with attempts to give items to them 
 *                in the default way, i.e. just they don't accept. 
 *                This guy accepts and responds though. 
 * 
 *  Arguments:    object gift   -    the given object 
 *                object giver  -    the living who gave it 
 */ 
void 
react_give(object gift, object giver) 
{ 
    /* 
     * If the gift giver has gone or can't be seen, what should 
     * be done? This monster will get suspicious and drop the 
     * item. 
     */ 
    if (!objectp(giver) || 
            !objectp(present(giver, environment(this_object()))) || 
            !CAN_SEE(this_object(), giver) ||
            !CAN_SEE_IN_ROOM(this_object())) 
    { 
        command("peer suspiciously"); 
        command("drop " + OB_NAME(giver)); 
        return; 
    } 
    // .. else if the giver is an enemy, don't accept it.. 
    else if (member_array(giver, query_enemy(-1)) > -1) 
    { 
        if (query_attack() == giver) 
        { 
            command("thank " + OB_NAME(giver) + " sarcastically"); 
            command("poke " + OB_NAME(giver) + " eye"); 
        } 
        command("drop " + OB_NAME(gift)); 
        return; 
    } 
    /* 
     * .. else if the item is important to the monster, do something 
     * with it. Here's just an illustrative example. Provided 
     * he is not poisoned and the item contains alcohol, he'll 
     * drink it .. 
     */ 
    else if (!objectp(present("poison", this_object())) && 
            gift->query_alco_amount() > 0) 
    { 
        command("grin " + OB_NAME(giver)); 
        // .. try to drink it 
        if (command("drink " + OB_NAME(gift))) // if he could drink it .. 
        { 
            // .. if he's now poisoned, attack the giver. 
            if (objectp(present("poison", this_object()))) 
            { 
                command("scowl " + OB_NAME(giver)); 
                command("kill " + OB_NAME(giver)); 
            } 
            else 
            { 
                command("smile " + OB_NAME(giver)); 
                command("thank " + OB_NAME(giver)); 
            } 
            return; 
        } 
        command("shrug"); 
    } 

    // give it back 
    command("say Keep this!"); 
    if (!command("give " + OB_NAME(gift) + " to " + 
                OB_NAME(giver))) 
    { 
        command("drop " + OB_NAME(gift)); 
    } 
} 



/* 
 * The function enter_inv is defined in /std/container.c 
 * It is a very useful and widely used. In this case it's 
 * used in reacting to something given to this monster 
 * by a living. See "sman enter_inv" for general information. 
 */ 
void 
enter_inv(object obj, object from) 
{ 
    // Call the inherited function code 
    ::enter_inv(obj, from); 

    // If it's a gift, set up a reaction one second after.. 
    if (living(from)) 
        set_alarm(1.0, 0.0, &react_give(obj, from)); 
} 
