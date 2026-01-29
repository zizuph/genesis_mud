// 'Brat' for the tomato-drop quest.
// creator(s):        Kazz
// revision history:  April 1995
//		      Denis, May'96: Changed the usage of quest_killers log to
//				     statserv. Lots of changes here and there.
//		      Denis, Jul'96: Removed triggers completely.
// purpose:           asks player to hit snob-elf with rotten tomato
//		      Brat is unable to hit snob-elf, and player can only
//		      hit him by dropping from tower_middle2
// note:	      This guy is the beginning of the quest.

#pragma strict_types
#include <money.h>
#include "tomato_drop.h"				// quest header
#include "/d/Avenir/smis/sys/statserv.h"		// statserv header
#include "/d/Avenir/common/outpost/outpost.h"

inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/intro";

/* Prototypes.
 */
string give_quest();
string no_reward();
void move_me();

/*
 * Function name: create_monster()
 */
void create_monster()
{
    if(!IS_CLONE)
       return;
    
    set_name("gritor");
    add_name("dwarf");
    add_name("brat");
    add_name("boy");
    set_long("This young dwarf looks sneaky and mischievious.\n" );
    set_race_name ("dwarf");
    set_adj( "young" );
    set_stats ( ({20,25,20,20,20,20}) );

    set_alignment(-100);
    set_pick_up(1);
    set_whimpy( 70 );
    
//    wander the fort.
    set_restrain_path(OUTPOST + "fort");
    set_monster_home(OUTPOST + "fort6");
    set_random_move(6 + random(5));
    
    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_DEFENSE, 20);
    set_skill(SS_BLIND_COMBAT, 10);

    seteuid(getuid());
    
    set_act_time(2);
    add_act("emote looks around as if deciding something."); 
    add_act("emote grins at you with a twinkle in his eye.");
    add_act("emote giggles childishly.");
    add_act("emote skids to a stop and looks out of breath.");
    add_act("emote snickers.");
    add_act("emote glances up at the tower window and frowns.");
    add_act("emote makes a face at you.");
    add_act("emote peers around.");
    add_act("emote bounces a tomato in his hand as if judging it's weight.");

    set_chat_time(3);
    add_chat("I can't believe I keep missing him.");
    add_chat("Cool tomatoes, huh?");
    add_chat("Now, where is that elf.");
    add_chat("Hey, can you help me?");
    add_chat("Heh, heh, he hates it when someone spits.");
    add_chat("There is something about that elf that just doesn't seem right.");

    set_cact_time(1 + random(2));
    add_cact("emote screams: What did I do?");
    add_cact("emote cries: You jerk!" );
    add_cact("emote yells: Help, I'm being attacked for no reason!" );

    add_ask( ({"help", "quest", "tomato", "tomatoes", "elf", "missing"}),
	     give_quest, 1);
    add_ask( ({"reward"}), no_reward, 1);
    
    add_act(move_me);
}

/*
 * Function name: move_me
 * Description:   to keep the brat out of the same room as the snob_elf
 *		  Code provided by Grace ... *thanks Grace*
 */
void move_me()
{
    object snob_elf, room;

    room = environment(TO);
    if ((snob_elf = present("pompour", room)))
    {
	tell_room(room, QCTNAME(TO) + " gasps: Yikes!\n");
        TO->move_living("quickly", query_monster_home(), 1);
    }
}

/*
 * Function name: equip_me()
 * Description:   Clones stuff.
 */
void equip_me()
{
    clone_object(TOMATOQ_DIR + "tomato")->move(this_object());
    clone_object(TOMATOQ_DIR + "tomato")->move(this_object());
    MONEY_MAKE_CC(8 + random(5))->move(this_object());
}

/*
 * Function name: give_quest()
 * Description:   Give the quest info to the player
 * Returns:       
 */
string give_quest()
{
    object tp = this_player();
    object to = this_object();
    object tomato;
  
    if(tp->test_bit("avenir", TOMATOQ_GROUP, TOMATOQ_BIT))
    {
        tp->catch_msg("Aww, you already got him before, I want someone new.\n");
	STATSERV_LOG_EVENT("outpost", "Tried to start tomato again");
        return "sigh";
    }
  
    // player already asked for quest
    if(tp->query_prop(TOMATOQ_QUEST_VERSION))
    {
        command( "say Didn't I already give you one?" );
        command( "emote looks closely at you and nods." );
        command( "say Yah, I did." );
        command( "say Go get him already!");
        return "bounce";
    }

    command( "emote says: Alright!" );
    command( "oops" );
    tp->catch_msg(QCTNAME(to) + " whispers: Not so loud!\n" +
		  QCTNAME(to) +
		  " whispers: You know that snobby elf in white?\n"+
		  QCTNAME(to) +
		  " whispers: Well, I can't hit him with ... one of these.\n");
    tell_room(environment(tp),
		  QCTNAME(to) + " whispers to " + QCTNAME(tp) + ".\n", tp);

    tomato = clone_object(TOMATOQ_DIR + "tomato" );
    tp->catch_msg(QCTNAME(to) + " secretly slips you a mushy tomato.\n" );
    tomato->move(tp);
  
    command( "smirk" );
    tp->catch_msg(QCTNAME(to) +
	     " whispers: So, if you splatter him with that, it'd be great!\n" );
    tp->catch_msg(QCTNAME(to) + " thanks you.\n" );

    tp->add_prop(TOMATOQ_QUEST_VERSION, TOMATOQ_ACCEPTED);

    STATSERV_LOG_EVENT("outpost", "Started the tomato quest");
    
    return "cackle merrily";
}

/*
 * Function name: no_reward
 * Description:   reward is given only when the tomato hits the elf
 * Returns:       
 */
string no_reward()
{
    command( "say Huh?" );
    command( "emote looks at you strangely." );
    return "cough";
}

/*
 * Function name: do_die()
 * Description:   Logs the fact of killing the quest npc.
 * Arguments:     killer - who killed us.
 */
void do_die(object killer)
{
    if(!interactive(killer))
        STATSERV_LOG_EVENT("outpost", killer->query_name() + " killed the brat");
    else
	STATSERV_LOG_EVENT("outpost", "Kills of the brat");

    ::do_die( killer );
}

/*
 * Function name: remove_placed_object
 * Description:   'Runs away' when the tomato quest is switched off.
 */
void remove_placed_object()
{
    tell_room(environment(TO), "Suddenly " + QTNAME(TO) + " runs away.\n");
    remove_object();
}
