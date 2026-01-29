/*
 * This room is cloned for each person using the utterdark transport
 * pool.
 *
 * Revisions:
 * 	Lucius, Jun 2017: Fixed a bug that caused players to become
 * 			  'stuck' due to auto-following "pets".
 *
 */
#pragma strict_types

#include "/d/Avenir/common/city/zigg/zigg.h"
#include <config.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

/* From /d/Genesis/obj/statue.c */
#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"
#define OFFERED_PROP	"_live_i_offered_coin"
#define TICK     2.0
#define PURITY "/d/Avenir/common/city/zigg/obj/purity"

inherit "/std/room";
inherit RLOG;

private static int goodbye;
private static object player;
private static string dest = "bazaar";

/*
 * Destination : ({"path to destination", "description of arrival spot",
 * 		   "what player comes out of", travel time - max 28, })
 */

private static mapping m_dest = ([
    "holm" : ({ HOLM + "shore/sh16", "on a rocky beach", "pool",
    		(10 + random(19))}),
  "bazaar" : ({ BAZAAR + "admin/fount", "on a stone path next to "+
		"a golden fountain", "fountain", (11 + random(11))}),
"ziggurat" : ({ CITY + "zigg/level1/entrance", "on a black stone floor "+
		"next to a tranquil fountain", "fountain", (11 + random(15))}),
]);

public string
block_dir(void)
{
    return "You are too busy tumbling through cold, dark water!";
}

public void
set_dest(string str)
{
    dest = str;
}

public string
query_dest(void)
{
    return dest;
}

public int
query_time(void)
{
    return m_dest[dest][3];
}

public void
create_room(void)
{
    setuid();
    seteuid(geteuid());

    /* XXX improve */
    set_short("fathomless dark water");
    set_long("You are surrounded by dark water, swept along by rapid "+
        "currents through the lightless reaches of an icy sea. You float "+
        "helplessly, tumbling about, without even a glimmer of light "+
        "to show you up from down.\n");

    /* XXX add items */

    /* All of sybarus is inside. */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
    /* No magic props. */
    add_prop(ROOM_M_NO_MAGIC, block_dir);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, block_dir);
    add_prop(ROOM_M_NO_SCRY, 1);
    /* No teleport props. */
    add_prop(ROOM_M_NO_TELEPORT, block_dir);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, block_dir);
    /*emergency exit*/
    add_exit("rift_room", "down", 0, 0, 1);
}

private void
spammage(int traveling, int breathing)
{
    /* Counting down to extinction. */
    if (goodbye)
	return;

    /* Fail-safe */
    if (!present(player))
    {
	set_alarm(1.0, 0.0, remove_object);
	return;
    }

    /* At destination. */
    if (traveling >= m_dest[dest][3])
    {
	switch(traveling - m_dest[dest][3])
	{      
	case 0:
	    tell_room(TO, "You finally notice the water above your head "+
	        "shimmering with light.\n");
	    break;
	case 1:
	    tell_room(TO, "Your momentum begins to slow but then a current "+
	        "of warm water surges from beneath you, sending you rushing "+
	        "up and up.\n");
	    break;
	case 2:
	    	    
	    if (player->move_living("M", m_dest[dest][0], 1, 0) == 0)
	    {
		logrotate(LOG + "pool",
		    time2format(time(), "mmm dd yyyy tt: ") +
		    TP->query_cap_name() +" entered the pool and "+
		    "arrived at the "+ dest +".\n");		    
		    
		player->catch_tell("Coughing and sputtering you are deposited "+
		m_dest[dest][1] +".\n");  
		clone_object(PURITY)->move(player);
	
		tell_room(m_dest[dest][0], QCTNAME(player) +" arrives coughing "+
		    "and sputtering out of the "+ m_dest[dest][2] +".\n", 
		    player, player);
	    }
	    else /* In case of failure... */
	    {	    
		tell_room(TO, "You seem to be stuck.\n"+
		    "Try leaving up or down.\n");	
		    
		add_exit(m_dest[dest][0], "up", 0, 0, 1);	    
	    }
	    return;
        }
    }
    else 
    {
	//Traveling Messages		
	switch(traveling)
	{
	case 1:
	    tell_room(TO,"You are enjoying the easy feeling of floating "+
	        "weightlessly.\n");
	    break;
	case 3:	    
	    tell_room(TO,"Something brushes against your leg.\n");
	    break;
	case 5:		    
	    tell_room(TO,"The darkness is absolute and all you can hear "+
	        "is the throbbing of your own heart as you sink helplessly "+
	        "through the black water.\n");
	    break;    	    
	case 7:
	    tell_room(TO,"The water begins to rush around you as you "+
	        "sink into a fast moving current.\n");
	    break;
	case 9:
	    tell_room(TO,"You are swept along by the current, gaining "+
	        "speed as you tumble and flip with the twisting flow of "+
	        "the water.\n");
	    break;
	case 11:
	    tell_room(TO,"The current pulls you through a long, rough-hewn "+
	        "tunnel.\n");
	    break;
	case 13:
	    tell_room(TO,"You hear the muted sound of water rubbing over "+
	        "rock.\n");
	    break;
	case 15:
	    tell_room(TO,"You clip your arm painfully against something "+
	        "that feels like jagged stone.\n");
	    break;
	case 17:
	    tell_room(TO,"The icy water steals your body heat, leaving "+
	        "you cold to your very core.\n");
	    break;
	case 19:
	    tell_room(TO,"You spin around rapidly, momentarily caught in "+
	        "an eddy formed by water and stone.\n");
	    break;
	case 21:
	    tell_room(TO,"You struggle against the current, hoping " +
	        "to swim upwards, but it is no use.\n");
	    break;
	case 23:
	    tell_room(TO,"Your arms are starting to feel heavy and numb "+
	        "with cold.\n");
	    break;
	default:
	    if(player->query_prop(MAGIC_I_BREATHE_WATER))
	    {
		//Breathing fine message
		if(!(traveling%6))   
		{ 
		    player->catch_msg("You breathe the water easily.\n");
		}
	    }
	    else
	    {
		//Can't breath messages.	
		switch(++breathing)
		{
		case 1:
		    tell_room(TO,"You start wondering how long you can "+
		    "stay underwater like this.\n");
		    break;
		case 2:
		    tell_room(TO,"You feel a weak pressure from inside. "+
		    "You let out some air.\n");
		    break;
		case 3:
		    tell_room(TO,"Some air bubbles flow out your mouth, "+
		    "floating upwards. You cant help wishing you were "+
		    "going the same way.\n");
		    break;
		case 4:
		    tell_room(TO,"If you only could fill your lungs with "+
		    "air again!\n");
		    break;
		case 5:
		    tell_room(TO,"You are having problems concentrating on "+
		    "what you are doing. All you can think about is air.\n");
		    break;
		case 6:
		    tell_room(TO,"A sudden feeling of weakness overwhelms "+
		    "you.\n");
		    break;
		case 7:
		    tell_room(TO,"Your vision fades for a second.\n");
		    break;
		case 8:
		    tell_room(TO,"You don't think you can last much "+
		    "longer without breathing.\n");		
		    break;
		case 9:
		    tell_room(TO,"Panic strikes you with a cold grasp "+
		    "around your heart.\n");
		    break;
		case 10:
		    tell_room(TO,"OUT!! You have to get out!!\n");		
		    break;  
		case 11:
		    tell_room(TO,"You briefly lose senses.\n");
		    break;
		case 12:
		    tell_room(TO,"A scream builds up within you and "+
		    "forces itself out your lips. You swallow water.\n");
		    break;
		case 13:
		    tell_room(TO,"You are struggling! Your lungs fill "+
		    "with water!\n");
		    break;
		case 14:
		    tell_room(TO,"Panic makes you gasp for air. You "+
		    "inhale water instead!\n");
		    break;
		case 15:
		    tell_room(TO,"Your eyes feel as if they are popping "+
		    "out of your head. The pressure is killing you!\n");
		    break;
		case 16:
		    tell_room(TO,"You are dying! You must get out!!!\n");
		    break;
		}
	    }
	    break;
	}    
    }
    /* keep going. */
    set_alarm(TICK, 0.0, &spammage(++traveling, breathing));
}

public void
drift_away(object ob)
{
    if (ob && environment(ob) == TO)
    {
	ob->move(COM + "void");	   
	tell_room(TO, "The "+ ob->short() +
	    " drifts away with the currents.\n");
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
   
    if (!living(ob))
    {
	set_alarm(1.5, 0.0, &drift_away(ob));
	return;
    }
 
    if (!IS_CLONE)
	return;

    /* Don't bug out on auto-follow pets. */
    if (!query_interactive(ob))
	return;

    player = ob;
    player->add_prop(LIVE_M_MOUTH_BLOCKED, "A few bubbles escape your "+
        "lips and float away.\n");
    set_alarm(TICK, 0.0, &spammage(1));
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    /* This is a cloned room that gets destroyed when left.
     * If a player linkdies here, have them recover at the rift_room.
     */
    if (living(ob) && objectp(to) && (file_name(to) == OWN_STATUE))
    {
	ob->add_prop(PLAYER_S_LD_IN_ROOM, L2 + "rift_room");
	ob->remove_prop(LIVE_M_MOUTH_BLOCKED); 
	goodbye = set_alarm(5.0, 0.0, remove_object);
	return;
    }

    /* Non-players return here.
     * Comes after linkdeath check because players are no longer
     * interactive at this point if linkdead.
     */
    if (!query_interactive(ob))
	return;

    goodbye = set_alarm(5.0, 0.0, remove_object);
    ob->remove_prop(LIVE_M_MOUTH_BLOCKED);
    ob->remove_prop(OFFERED_PROP);
}

public int
do_swim(string str)
{
    write("You try to swim but cannot seem to propel yourself against this "+
	"strange water.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action( do_swim, "swim" );
}
