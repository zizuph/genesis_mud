// file name: ~Avenir/common/dark/l3/altar.c
// note: Imps quest main room, here you get it, here you finish it.
//       Both taking and finishing can be done by <talk ghost> or asking
//       it something.
//       Unlike most of the Utterdark rooms, this room isn't dark.
//       Ghost is unkillable (isn't monster actually).
//
// to-do: Make imps really perform some rituals when the ghost was killed by
//        someone. Also if an evil player gives the hammer to an imp
//        instead of smashing them, make them able to kill the ghost
//        using it.
//        Make this adjust players alignment. (Smashing imps is considered
//        a good deed.)
/*
 * Revisions:
 * Cirion, Feb 1996: Changed add_exp to use
 * 		     the /inherit/quest.c reward_quest function
 * Denis,  Apr 1996: Added use of statserv for logging various events.
 * Lilith, Jul 1997: Made cosmetic changes so the spider altar is cloned here.
 * Lilith, Jul 2014: Updated chats for ghost and cleaned up some funcs
 * Lucius, Jun 2017: Cleanups and typo fixes.
 *
 */
#pragma strict_types

#include "l3_defs.h"
#include "/d/Avenir/smis/sys/statserv.h"

inherit "/std/room";
inherit "/d/Avenir/inherit/quest";

#include "/d/Avenir/common/dark/dark.h"
#include <cmdparse.h>

int ghost_is_here;	// 1 - Ghost is here
			// 0 - Ghost was set free by someone
int alarm_id;		// Alarm id for delayed quest messages
int ghost_is_awaken;	// 1 - Ghost will not be surprised to see anyone
			// 0 - will
int ghost_is_alive;	// 1 - It will transform into something able to kill
			//     (~Avenir/common/dark/mon/ghost.c)
			// 0 - That something was alradey killed by someone
object hammer_object;	// The pointer to sacrificial hammer.
object spider_altar;	// The altar to Aclolthayr.

/*-----[ Prototypes ]-----*/
private void reward_player(object player);
public void ghost_whisper(object player); 
public void ghost_hint(object player);


/*-----[ Room definition ]-----*/
void
create_room()
{
    set_short("Temple");
    set_long("The black stone walls of this enormous room rise "+
      "up to form a dome overhead. The walls are lined with "+
      "veins of red mineral that emanate a strong heat. The "+
      "room's only adornment is the altar in its center. The "+
      "air in here is hot and dry, and the altar gives off a "+
      "heavy sense of dread. The only exit from this room is "+
      "an archway on the south wall.\n"+"@@ghost_long");

    add_exit("/d/Avenir/common/dark/l3/entry","south",0, 5, 1);

    IN

    add_item(({"wall","walls"}),
      "The walls of the temple are smooth, and form a massive dome. "+
      "The rock has strange patterns of red veins running through "+
      "it, almost as if it were a series of symbols in some ancient, "+
      "runic language. The veins emanates a very strong heat, making "+
      "this room quite warm. On the south wall is an imposing arch"+
      "way, through which is the only exit from the temple.\n");

    add_item(({"arch","archway"}),
      "The terrible arch is made from an unknown, blood red stone, "+
      "and across the top spidery symbols interwoven with spirals "+
      "have been carved in thin, blue lines. Through the "+
      "arch you can see the entry foyer of the temple.\n");

    add_item(({"symbol","symbols", "runes", "language", "runic symbols"}),
      "The runic symbols on the wall are too high up for you to make "+
      "out clearly, so you cannot ascertain what they might mean.\n");

    add_item(({"ghost","guardian"}),"@@ghost_look");

    if (!spider_altar)
	spider_altar = clone_object(ACLO_ALTAR)->move(TO);

    ghost_is_here=1;
    ghost_is_awaken=0;
    ghost_is_alive=1;
}

/*-----[ Commands avalaible here ]-----*/
void init()
{
    ::init();
    add_action("ghost_talk","talk");
    add_action("ghost_talk","ask");
    add_action("ghost_attack","kill");
}

/*-----[ Reset ghost's ability to transform itself into something ]-----*/
/*-----[ dangerous                                                ]-----*/
void reset_room()
{
    ghost_is_alive=1;
}

/*-----[ Indicate that here is a ghost (non-living actually)      ]-----*/
string ghost_long()
{
    if (ghost_is_here)
	return "There is a pale, transparent elvish ghost standing "+
	"near altar.\n";
    else
	return "";
}

/*-----[ Long ghost description ]-----*/
string ghost_look()
{
    if (ghost_is_here)
    {
	return
	"The ghost of a tall elven guardian floats in the air before the "+
	"altar. He is ages old, and wears an expression of infinite "+
	"weariness. He seems to be guarding the altar from something.\n"+
	"He is quite incorporeal, and does not look as if he can be harmed.\n";
    }
    return "You see no ghost here.\n";
}

/*--1--[ First phrase of ghost, peering quizically ]----*/
public int 
ghost_talk(string str)
{
    object player = TP;
    string nothing;

    remove_alarm(alarm_id);
    NF(capitalize(query_verb())+" who?\n");

    if (ghost_is_here &&
	parse_command(str,({})," 'ghost' / 'guardian' %s ",nothing))
    {
	// Does player want to receive xp?
	if (TP->query_prop(GHOST_ASKED_FOR_HELP) &&
	    TP->query_prop(ROOMS_FREED_FROM_IMPS) >= IMPS_ROOMS_NUMBER)
	{
	    reward_player(TP);

	    write("You tell the ghost that you have killed all imps and "+
	      "broken all of the statues.\n");
	    tell_room(TO,
	      QCTNAME(TP)+" says to the ghost that "+PRONOUN(TP)+
	      " has killed all imps and broken all of the statues.\n",TP);
	    tell_room(TO,
	      "The ghost bows deeply saying: Thank you, great warrior.\n"+
	      "The ghost disappears, having completed "+
	      "his task in this world.\n");

	    TP->remove_prop(ROOMS_FREED_FROM_IMPS);
	    hammer_object->self_destruct();
	    ghost_is_here=0;
	    return 1;
	}

	if (!ghost_is_awaken)
	{
	    ghost_is_awaken=1;
	    tell_room(TO,
	      "The ghost steps back, trying to wield a weapon which no longer exists.\n"+
	      "You can see that there is nothing left but the image of an elf.\n"+
	      "The ghost says: Ahh.. You seem not to be a winged gargoyle...\n"+
	      "                Those accursed creatures will never perform their dark\n"+
	      "                ritual of releasing here!\n");
	}
	else
	{
	    player->catch_tell(
	      "You try to speak to the ghost, but he seems to struggle to answer. "+
	      "Perhaps if you wait patiently, he will find the words.\n");
	    tell_room(TO, QCTNAME(TP)+" asks ghost about something.\n"+
		"The ghost looks at "+ OBJECTIVE(TP) +
		" imploringly, seeming to beg for patience.\n",TP);
	}

	STATSERV_LOG_EVENT("impquest", "Quest asked");
	alarm_id=set_alarm(15.0,0.0,&ghost_whisper(player));
	return 1;
    }
}

/*--2--[ Second phrase of ghost, giving quest ]-----*/
public void
ghost_whisper(object player)
{
    if (environment(player)!=TO)
	return;

    player->catch_tell("The ghost looks like he is struggling to speak.\n");

    if (player->test_bit("Avenir",0,0))
    {
	player->catch_tell("\nThe ghost mentally whispers to you: Thank you for "+
	  "your help earlier. It was a brief rest, but much needed.\n");
	return;
    }

    if (player->query_prop(GHOST_ASKED_FOR_HELP))
    {	
	player->catch_tell(
	  "\nThe ghost mentally whispers to you: "+
	  "Find the sacrificial hammer, for only it has the power to destroy "+
	  "the imps once they have turned to stone....\n"+
	  "The ghost seems to pause for breath, as though communicating "+
	  "takes great effort.\n");
	alarm_id=set_alarm(15.0,0.0,&ghost_hint(player));
	return;
    }
    else
    {
	player->catch_tell(
	  "\nThe ghost mentally whispers to you: "+
	  "Can you please help me?\n"+
	  "I am not strong enough to destroy them all...\n"+
	  "But if they succeed in their dark ritual of releasing, it will be "+
	  "the end of all races! The only thing that can help is to find the "+
	  "sacrificial hammer which has the power of earth within and break all "+
	  "of the statues that the winged creatures turn into when you kill them...\n"+
	  "The ghost seems to pause for breath, as though communicating "+
	  "takes great effort.\n");
	alarm_id=set_alarm(15.0,0.0,&ghost_hint(player));
	player->add_prop(GHOST_ASKED_FOR_HELP,1);
    }

    tell_room(TO,
      "\nThe ghost says: I am so tired... Please destroy the winged ones!\n");
}

/*--3--[ Third phrase of ghost, giving hints ]-----*/
public void
ghost_hint(object player)
{
    if (environment(player)==TO)
	player->catch_tell(
	  "\nThe ghost mentally whispers to you:\n"+
	  "If memory does not fail me, the hammer it is down in the tunnels hidden in "+
	  "a stone which can be opened by three shining keys, pieces of the Source. "+ 
	  "I was unable to find the keys, but maybe you will?\n"+
	  "Use the hammer to destroy the imps in their stone form, and then I "+
	  "might have some rest...\n");
    return;
}

/*----[ We are rewarding here (nice, eh?) ]-----*/
private void
reward_player(object player)
{
    if (!player->test_bit("Avenir",0,0))
    {
	reward_quest("Imp Quest", player, 0, 0, GHOST_QUEST_REWARD, 400, 1300);
	WRITE_LOG(player);

	STATSERV_LOG_EVENT("impquest", "Quest completed");
    }
}

/*----[ 'kill' command handler ]-----*/
int ghost_attack(string str)
{
    object ghost;
    object player;

    player=this_player();
    NF(capitalize(query_verb())+" who?");
    if (ghost_is_here&&(str=="ghost"||str=="guardian"))
    {
	player->catch_tell(
	  "You try to hit the ghost, but your blows simply pass through him.\n");
	tell_room(
	  QCTNAME(player)+ " tries to hit the ghost but "+POSSESS(player)+
	  " blows simply pass through him.\n");

	if (ghost_is_alive)
	{
	    tell_room(TO,
	      "The ghost gathers the powers of the dead within him "+
	      "and transforms into a more solid form. "+
	      "From nowhere a shining double-bladed polearm "+
	      "appears in his hands as a weapon of the past.\n");
	    ghost=clone_object(MON+"ghost");
	    ghost->arm();
	    ghost->move(TO);
	    ghost_is_here=0;
	    ghost->command("kill "+player->query_real_name());
	}
	return 1;
    }
}

/*-----[ Blah, someone killed our ghost, but don't think that none  ]-----*/
/*-----[ will be able to solve our quest.                           ]-----*/
void ghost_died()
{
    ghost_is_alive=0;
    ghost_is_here=1;
}

/*-----[ They were unable to kill the ghost! He returns back in     ]-----*/
/*-----[ his immaterial state                                       ]-----*/
void ghost_returns()
{
    ghost_is_here=1;
}

/*
 * Function name: reset_ghost
 * Description:   Is called from the impquest daemon (entry.c) to
 *                reset the ghost if someone solved the quest before.
 */
void reset_ghost()
{
    ghost_is_here=1;
    tell_room(TO,
      "An elven ghost, thrown by unknown force, flies in, screaming.\n");
}

/*
 * Function name: query_ghost_is_here
 * Description:   tells if ghost is here (the quest haven't been solved yet).
 * Returns:       1 if ghost is here.
 */
int query_ghost_is_here()
{
    return ghost_is_here || objectp(present(L3_GHOST));
}

/*
 * Function name: set_hammer_object
 * Description:   is called from rock when player gets a hammer to
 *                notify this place of its object pointer.
 * Arguments:     hammer - Sacrificial hammer object pointer.
 */
void set_hammer_object(object hammer)
{
    hammer_object = hammer;
}
