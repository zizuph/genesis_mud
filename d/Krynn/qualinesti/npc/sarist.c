/* File : sarist.c
 *
 * The elf captured by draconians. Part of quest.
 * Questioning idea borrowed from "/d/Krynn/solamn/hctower/spur/npc/qdrac.c"
 *
 * Blizzard, 02/2003
 *  
 */

#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include "../local.h"

inherit M_FILE
inherit "/d/Krynn/std/equip";

public string ask_help();
public string ask_companion();
public string ask_sarist();
public string ask_trap();
public string ask_qualthas();
public string ask_weapon();
public string ask_camp();
public void   do_answer(string what, object who);
public int    check_if_my_sword(object obj, object from);
public void   return_me(object obj, object from);
int           beat(string str);
int           question(string str);
string        ignore_me();

object weapon;
int gReleased;
                 
#define FOUND_SWORD        "_found_sword"
#define LOST_SCOUTS        "_lost_scouts"
#define SARIST_KILLED      "_sarist_killed"
#define ELF_CAMP_QUEST     "_elf_camp_quest"
#define BEAT_ELF           "_beat_elf"
#define BROKEN_WILL        "_broken_will"
#define ELF_QUESTIONED     "_elf_questioned"
#define I_RELEASED_ELF     "_i_released_elf"

/* Function name  : query_released
 * Description    : Checks if the elf is tied or not
 * Returns        : 1     if he is released
 *                  0     if he is tied
 */
public int
query_released()
{
    return gReleased;
}

/* Function name  : set_released
 * Description    : We set if the elf is tied with rope or released
 * Arguments      : int num   - true or not
 */
public void
set_released(int num)
{
    if ( num == 1 )
        gReleased = 1;
    else
        gReleased = 0;
      
}

public void
remove_descr()
{
    remove_prop(LIVE_S_EXTRA_SHORT);
}

void
create_krynn_monster()
{
    
    set_name("sarist");
    add_name( ({ "elven prisoner", "prisoner" }) );
    set_race_name("elf");
    set_adj("elven");
    set_short("elven prisoner");
    set_long("@@long_desc");
    set_gender(0);
    set_alignment(400);
    set_knight_prestige(-100);
    
    set_stats(({ 90, 120, 100, 110, 110, 100 }));

    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 60);
    
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 175);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, VBFC_ME("check_accept"));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_S_EXTRA_SHORT, " laying in the corner of the room");

    set_hp(1650);     // We make him somewhat hurt
    set_released(0);  // When we clone him, he is tied with rope.

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({ "companion", "about companion", "deorl", "about deorl",
        "Deorl", "about Deorl" }), VBFC_ME("ask_companion"));
    add_ask(({ "sarist", "about sarist" }), VBFC_ME("ask_sarist"));
    add_ask(({ "aid", "heal", "cure" }), VBFC_ME("ask_help"));
    add_ask(({ "help", "task", "about task"}), VBFC_ME("ask_help"));
    add_ask(({ "trap", "ambush", "about trap" }), VBFC_ME("ask_trap"));
    add_ask(({ "weapon", "about weapon" }), VBFC_ME("ask_weapon"));
    add_ask(({ "qualthas", "about qualthas" }), VBFC_ME("ask_qualthas"));
    add_ask(({ "follow", "follow me" }), VBFC_ME("follow"));
    add_ask( "name", VBFC_ME("ask_sarist"));
    add_ask(({ "speak", "tell" }), VBFC_ME("ignore_me"));
    add_ask(({ "camp", "about camp", "location", "location of camp", 
        "location of the camp" }), VBFC_ME("ask_camp"));
        

    seteuid(getuid(TO));
    equip(({ ARM + "stud_arm", ARM + "elven_boots" }));
}

string
long_desc()
{
    if ( !query_released() )
        return "This elf is probably one of the elven scouts. " +
            "His legs and wrists are tied up tightly with a strong rope so " +
            "he cannot move. However, he doesn't seem to be seriously " +
            "wounded.\n";
    else
        return "This is probably one of the elven scouts. He doesn't " +
            "seem to be seriously wounded but on his wrists you see " +
            "bloody marks left by a rope, that he was tied with.\n";
}

/* The elf will not accept give if he is tied. 
 */
mixed
check_accept()
{
    if ( gReleased == 0 )
        return " is tied with a rope and cannot hold that.\n";
    
    return 0;

}

void
init_living()
{
    ADA("beat");
    ADD(question, "interrogate");
    ADA("question");
    ADD(beat, "torture");
}

int
question(string str)
{
    object player = TP;
 
    if ( str == "elf" || str == "prisoner" || str == "elven prisoner" ||
        str == "sarist" || str == "Sarist" )
    {
        say(QCTNAME(TP) + " attempts to question " + QTNAME(TO) + ".\n", TP);
        TP->catch_msg("You attempt to question " + QTNAME(TO) + ".\n");
        
  // Player is doing a quest for Qualthas
        if (player->query_prop(LOST_SCOUTS))            
        {
           set_alarm(1.0, 0.0, &do_answer("help", player));
     
           return 1;
        }
        
  // Player beat elf, will give informations about the camp.
        if (player->query_prop(BEAT_ELF))
        {
            set_alarm(1.0, 0.0, &do_answer("camp", player));
            
            return 1;
        }
     
  // Unsuccessful questioning
        command("snicker");
        command("say I won't tell you anything.");

        return 1;
    }
    
    notify_fail("Question who?\n");
    return 0;
}

int
beat(string str)
{
    object player = TP;
   
    if ( (str == "elf" || str == "prisoner" || str == "elf prisoner" ||
        str == "sarist" ) &&
        gReleased == 0 )
    {

  // It is possible to beat him to the death...        
        TP->catch_msg("You beat the elven prisoner in hope to weaken " +
             "his will.\n");
        say(QCTNAME(TP) + " tortures the elven prisoner in hope to " +
             "weaken his will.\n", TP);
        TO->heal_hp(-80);

  // Knights shouldnt beat the elf...
        if ( player->test_bit("Krynn", 1, 0) )
        {
            command("emote spits.");
            command("say What a honourable knight.");
            player->change_prestige(-50);
        }   
       
        if ( !player->query_prop(BEAT_ELF) )
            player->add_prop(BEAT_ELF, 1);        
            
  // Too much beating... Ops.
        if ( TO->query_hp() <= 0 )
        {
            player->catch_msg("You continue beating the elf. After a moment " +
                "you notice he is not breathing.\n");
            say(QCTNAME(TP) + " continues beating the elf. After a moment " +
                "you notice the prisoner is not breathing.\n", TP);
            player->add_prop(SARIST_KILLED, 1);
            TO->do_die(player);
            
            return 1;
        }

  // Sarist will start speaking when his hps drop to 1/2   
        if ( TO->query_hp() <= (query_max_hp() / 2) )
        {
            command("say Stop it...");
            command("say I will speak...");
            command("emote sighs.");
            if ( !query_prop(BROKEN_WILL) )
                add_prop(BROKEN_WILL, 1);
            
            return 1;
        }
        

  // Sent by Qualthas
        if (player->query_prop(LOST_SCOUTS))
        {
            command("say You scum!");
            command("emote grits his teeth.");
            
            return 1;
        }

        switch (random(5))
        {
        case 0:
            command("shout You coward! I am tied up and cannot fight!");
            command("say Release me and then we'll see..."); 
        break;
        case 1:
        case 2:
            command("emote grits his teeth.");
        break;
        case 3:
            command("emote scowls at you.");
        break;
        case 4:
            command("say You coward! Release me!");
        break;
        }
         
        return 1;
    }
    
 // While released, Sarist wont just watch as player beats him... ;)   
    if ( TO->query_released() )
    {
        command("say Ha! I warned you!");
        command("kill " + player->query_real_name() );
        return 1;
    }
    
    notify_fail("Beat who?\n");
    return 0;
}

string
what_me()
{
    command("emote just stares at you and says nothing.");
    return "";
}

string
ignore_me()
{
 // We have not been questioned yet by the player and noone has broken 
 // our will
    if ( !query_prop(BROKEN_WILL) && !(TP->query_prop(ELF_QUESTIONED)) )
    {
        switch (random(4))
        {
        case 0:
            command("emote refuses to cooperate.");
        break;
        case 1:
            command("emote spits.");
        break;
        case 2:
            command("say I will tell nothing.");
        break;
        case 3:
            TP->catch_msg(QCTNAME(TO) + " ignores you.\n");
            say(QCTNAME(TO) + " ignores " + QTNAME(TP) + ".\n", TP);
        break;
        default:
            command("say I will tell nothing.");
        break;
        }
        return "";            
    }
 // We have enough the beating and the player has not questioned us yet
    else if ( query_prop(BROKEN_WILL) && !(TP->query_prop(ELF_QUESTIONED)) )
    {
        TP->catch_msg(QCTNAME(TO) + " scowls at you.\n");
        say(QCTNAME(TO) + " scowls at " + QTNAME(TP) + ".\n", TP);
        command("say So? What do you want to know?");
        return "";
    }
 // We told them everything we can.
    else if ( TP->query_prop(ELF_QUESTIONED) )
    {
        command("say I will tell you nothing more!");
        return "";
    }
    
    return "";
}

int 
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
       return 1;
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
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE((TO), attacker))
    {
        command("say Show yourself!"); 
    }
    else
    {
        if ( !query_released() )
        {
            command("say How brave!");
            command("emote laughs.");
            command("say Release me and then we'll see what you can!");
        }        
        else
            command("say Let's test your skills!");
    }
    
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
    remove_prop(LIVE_S_EXTRA_SHORT);
    
    ::attacked_by(attacker);
    set_alarm(1.0, 0.0, &react_attack(attacker));
}

void
notify_death(object killer)
{
    if ( killer->query_prop(ELF_CAMP_QUEST) )
        killer->add_prop(SARIST_KILLED, 1);
        
    ::notify_death(killer);
}

/* Function name   : ask_help
 * Description     : answer to question about help
 */
public string
ask_help()
{
    set_alarm(1.0, 0.0, &do_answer("help", TP));
    return "";
}

/* Function name   : ask_trap
 * Description     : answer to question about trap
 */
public string
ask_trap()
{
    set_alarm(1.0, 0.0, &do_answer("trap", TP));
    return "";
}

/* Function name   : ask_companion
 * Description     : answer to question about companion
 */
public string
ask_companion()
{
    set_alarm(1.0, 0.0, &do_answer("companion", TP));
    return "";
}

/* Function name   : ask_sarist
 * Description     : answer to question about sarist
 */
public string
ask_sarist()
{
    set_alarm(1.0, 0.0, &do_answer("sarist", TP));
    return "";
}

/* Function name   : ask_qualthas 
 * Description     : answer to question about qualthas
 */
public string
ask_qualthas()
{
    set_alarm(1.0, 0.0, &do_answer("qualthas", TP));
    return "";
}

/* Function name   : ask_camp 
 * Description     : answer to question about camp
 */
public string
ask_camp()
{
    set_alarm(1.0, 0.0, &do_answer("camp", TP));
    return "";
}
    
/* Function name   : ask_weapon 
 * Description     : answer to question about weapon
 */
public string
ask_weapon()
{
    set_alarm(2.0, 0.0, &do_answer("weapon", TP));
    return "";
}

/* Function name   : do_answer
 * Description     : answers to the questions

 * Arguments       : string what  - topic
 *                   object who   - the player who asked
 */
public void
do_answer(string what, object who)
{
    if ( !objectp(who) || E(who) != E(TO))
    {
        return;   /* We wont speak if the player is gone */
    }
    
    switch (what)
    {
    case "help":
 // Player is doing a quest for Qualthas
        if ( who->query_prop(LOST_SCOUTS) )
        {
            command("say Help me to leave this place. I must speak with " +
                "Qualthas.");
            command("say Release me. Then I will need a weapon in " +
                "case we encounter draconians.");
            return;
        }
 // Player beat us so we do not trust him
        else if ( query_prop(BROKEN_WILL) )
        {
            command("say Help me? You?");
            command("emote laughs.");
            command("say Don't try to fool me.");
        }
 // Player is not doing a quest so we just ask him to help us
        else
            command("say Help me to leave this place.");
    break;
    case "weapon":
 // Player is doing a quest for Qualthas but we do not have our sword
        if ( !query_prop(FOUND_SWORD) && who->query_prop(LOST_SCOUTS) )
        {
            command("say Draconians took my sword but maybe it is still " +
                "somewhere around. Could you find it for me?");
            command("say When I have it I will follow you. Just ask me to " +
                "do it.");
        }
 // We have got the sword already
        else if ( query_prop(FOUND_SWORD) )
        {
            command("say Good that I have my sword with me!");
            command("emote tigthens the grip on his long elven blade."); 
        }
 // We do not have a sword and player is not doing a quest for Qualthas
        else if ( !query_prop(FOUND_SWORD) && 
            !(who->query_prop(LOST_SCOUTS)) )
        {
            command("say What? I had a sword but those dracs took it from " +
                "me!");
        }
    break;
    case "companion":
 // The player is doing a quest for Qualthas OR someone has beaten us hard!
        if ( who->query_prop(LOST_SCOUTS) || query_prop(BROKEN_WILL) )
        {
            command("say I do not know what happened to Deorl after we " +
                "attacked those dracs. We were winning, but then the " +
                "aurak showed up... That was a trap.");
            command("emote sighs.");
        }
 // Simple. No quest. No hard beating ;)
        else
            command("say I will tell you nothing!");
    break;
    case "sarist":
 // Player is doing a quest for Qualthas
        if ( who->query_prop(LOST_SCOUTS) )
        {
            command("emote peers around.");
            command("say Yes, I am Sarist. Are you sent by Qualthas?");
        }
 // After hard beating we confirm our name...
        else if ( query_prop(BROKEN_WILL) )
        {
            command("say Yes, I am Sarist.");
        }    
 // No quest. No hard beating ;) Forget about it!
        else
            command("say I will tell you nothing!");
    break;
    case "trap":
 // Quest for Qualthas OR we are after hard beating 
        if ( who->query_prop(LOST_SCOUTS) || query_prop(BROKEN_WILL) )
        {
            command("say We fought draconians. Then something happened " +
                "to me. I do not remember...");
        }
 // No quest. No hard beating. 
        else 
            command("say I will tell you nothing!");
    break;
    case "qualthas":
 // Player is doing a quest for Qualthas
        if ( who->query_prop(LOST_SCOUTS) )
        {
            command("say Qualthas? You know him?");
            command("say Then Deorl is alive and warned him. Help me " +
                "and let's leave this place."); 
        }
 // Hard beating again...Uh.
        else if ( query_prop(BROKEN_WILL) )
        {
            command("say He is our leader.");
            command("emote stares at you.");
        }
 // No quest. No beating. No info ;)
        else
            command("say I will tell you nothing!");
    break;
    case "camp":
 // Player is doing a quest for Qualthas
        if ( who->query_prop(LOST_SCOUTS) )
        {
            command("say What? You don't know? Who sent you then?");
            who->catch_msg("emote peers at you.\n");
            say(QCTNAME(TO) + " peers at " + QTNAME(who) + ".\n");
        }
 // After hard beating we give out the info...unless we have been questioned
 // already by that player.
        else if ( query_prop(BROKEN_WILL) &&
            !(who->query_prop(ELF_QUESTIONED)) )
        {
            command("say The camp? Where do you think it may be? In " +
                "Qualinesti of course!");
            command("emote laughs.");
            set_alarm(3.0, 0.0, &do_answer("camp__1", who));
        }
 // No more info, ever if he beats us again!
        else if ( who->query_prop(ELF_QUESTIONED) )
            command("say I will tell you nothing more.");
 // No quest. But no beating either ;) No info in that case.
        else 
            command("say I will tell you nothing!");
    break;
    case "camp__1":
        command("say Qualthas has set a camp not so far from the edge " +
            "of the forest... but deep enough that cowards like you " +
            "do not dare to enter!");
        command("emote smirks.");
        set_alarm(3.0, 0.0, &do_answer("camp__2", who));
    break;
    case "camp__2":
        command("say Even if you do... you will die quickly. We are " +
            "quite nice for guests like you.");
        command("emote laughs silently.");
        command("say That is all I have to say.");
 // We have told everything we could to this one. Remember that.
        if ( !(who->query_prop(ELF_QUESTIONED)) )
            who->add_prop(ELF_QUESTIONED, 1);
    break;        
    default:
            command("say I do not quite understand...");
    break;
    }
    
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    
    if ( !living(from) )
        return;
    
    if ( obj->check_weapon() )
        set_alarm(2.0, 0.0, &check_if_my_sword(obj, from));        
 // We want only correct weapon!
    else
        set_alarm(2.0, 0.0, &return_me(obj, from));

}

public int
check_if_my_sword(object obj, object from)
{
 /* Already done, or player is not doing the rescue elf quest. */
    if ( obj->id("_sarist_sword_") && !(from->query_prop(LOST_SCOUTS)) )
    {
        command("say Thanks! I will make use of it.");
        command("emote wields his long elven blade.");
        command("wield elven blade");
        add_prop(FOUND_SWORD, 1);
        
        return 1;
    } 
 /* Correct blade and the player was sent by Qualthas */
    if ( obj->id("_sarist_sword_") && from->query_prop(LOST_SCOUTS) )
    {
        command("say Yes, that's my sword!");
        command("emote wields his long elven blade.");
        command("wield elven blade");
        command("say Let's move!");
        add_prop(FOUND_SWORD, 1);
        
        return 1; 
    }
    
 /* Wrong weapon */
    command("say That's not my blade!");
    command("give " + (obj->query_name()) + " to " + from->query_real_name());
    
    return 0;
    
}

public void
return_me(object obj, object from)
{
    command("say I do not need that! Find my sword.");
    command("give " + (obj->query_name()) + " to " + from->query_real_name());
}

string
follow()
{
   string who;

   // Sarist will follow only if he is released.
   if ( query_released() )
   {
       if (query_follow())
           return "";
       
       if (!present(TP,E(TO)))
           return "";
       
       // ... but if we do not have the weapon we wont follow.  
       if ( !(query_prop(FOUND_SWORD)) )
       {
           command("say Find my sword first! I need a weapon in case " +
               "we encounter dracs!");
           return "";
       }
       
 // We do not like this one!
       if ( TP->query_prop(ELF_CAMP_QUEST) )
       {
           command("say Forget it!");
           return "";
       }
       
 // We will not follow someone who is not doing the quest.
       if ( !TP->query_prop(LOST_SCOUTS) )
       {
           command("say I do not trust you!");
           return "";
       }
       
 // We will follow only the one who released us.       
       if ( !TP->query_prop(I_RELEASED_ELF) )
       {
           command("say I can not trust you!");
           return "";
       }
       
 // ... but we will follow the player if he released us and we are armed 
       if ( query_prop(FOUND_SWORD) && TP->query_prop(I_RELEASED_ELF) )  
       {       
           set_follow(TP);

           command("say Ok. Let's get out of this place. I must speak " +
               "with Qualthas as soon as possible.");
           command("say When we are outside I will go on my own. I know " +
               "some shortcuts.");
           return "";

       }
 // Sorry, you havent brought our sword and havent even released us - 
 // we do not trust you.
       else 
       {
           command("say I do not trust you.");
           return "";

       }

   }
 // How? We ARE tied up with a rope!
   else
   {
       command("say Can't you see I am tied up? Release me first!");
       return "";
   }
   
}

public string
query_i_follow()
{
    return query_follow()->query_real_name();
}
