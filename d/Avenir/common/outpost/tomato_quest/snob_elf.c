// 'Snob' elf for the tomato-drop quest.
// creator(s):        Kazz  April 1995
// revision history:  April 1995:    made him 'movable' by
//				     triggering on players' spitting.
//		      Denis, May'96: Changed the usage of quest_killers to
//				     statserv. Minor changes. Changed to use
//				     emote_hook instead of trig_new.
//		      Denis, Jul'96: Cleaned up a bit *grin*.
//				     Removed triggers completely.
//                    Lilith, Jun 04 updated desc, updated restrict path
// purpose:           snob elf to use as tomato target for tomato_quest
// note:              He is actually an infidel in disguise as a shadow elf.
#pragma strict_types

#include <money.h>
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/smis/sys/statserv.h"

inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/intro";

public void create_monster()
{
    if(!IS_CLONE)
       return;
    
    set_name("pompour");
    add_name(({"elf", "dark elf", "infidel", "snob" }));
    set_long( "This elf looks down on nearly everybody, including you.\n"+
        "He apears to be somewhat ill-at-ease, and his fine clothes "+
        "seem to be a bit large for him, as if they were borrowed.\n" );
    set_race_name ("elf");
    set_title("sneering elf");
    set_stats ( ({50,80,50,60,50,40}) );

    set_alignment(-300);
    set_whimpy( 70 );

//    wander the fort.
    set_restrain_path( OUTPOST + "fort" );
    set_monster_home( OUTPOST + "fort5" );
    set_random_move(10+random(10));
    
    set_skill( SS_UNARM_COMBAT,60 );
    set_skill( SS_AWARENESS, 40 );
    set_skill( SS_DEFENSE, 50 );
    set_skill( SS_WEP_AXE, 50 );
    set_skill( SS_BLIND_COMBAT, 50 );
    
    seteuid(getuid());
    
    set_act_time(5);
    add_act("emote looks at you and shakes his head.");
    add_act("emote pulls back from you, and wrinkles his nose.");
    add_act("emote mumbles something to himself.");
    add_act("emote mutters something about a brat.");
    add_act("emote struts around.");
    add_act("emote adjusts his cape across both shoulders.");
    add_act("emote looks at your clothes and then adjusts his.");

    set_cact_time(1+random(2));
    add_cact("emote sighs: What a nuisance you are." );
    add_cact("emote says: Please leave me alone." );
    add_cact("emote yells: Guards! Get over here and protect me!" );
}

public void equip_me()
{
    clone_object(OBJ + "white_cape")->move(this_object());
    clone_object(OBJ + "white_clothes")->move(this_object());
    clone_object(OBJ + "white_hat")->move(this_object());
    command("wear all");
    MONEY_MAKE_CC(10 + random(13))->move(this_object());
    MONEY_MAKE_SC(10 + random(7))->move(this_object());
}


/*
 * Function name: emote_hook
 * Description:   move the elf when someone spits in the room.
 *                nifty code from Asmodean
 */
public void emote_hook(string emote, object actor, string adverb)
{
    if(emote == "spit")
    {
        int num_exits;

        command("say You're disgusting.");

        num_exits = sizeof(environment()->query_exit_cmds());
        command(environment()->query_exit_cmds()[random(num_exits)]);
    }
}

public void do_die(object killer)
{
    if(!interactive(killer))
	STATSERV_LOG_EVENT("outpost", killer->query_name() +
				      " killed the snob elf");
    else
	STATSERV_LOG_EVENT("outpost", "Kills of the snob elf");
    ::do_die( killer );   
}

public void leave_the_fort()
{
    tell_room(environment(this_object()),
	QCTNAME(this_object()) + " leaves in the port's direction.\n");
    remove_object();
}

public void remove_placed_object()
{
    set_alarm(10.0, 0.0, leave_the_fort);
}
