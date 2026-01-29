/* 
 *    /d/Gondor/rohan/isengard/isengate
 *
 *    Opus, Aug 1997
 *
 *    Copyright (c) 1997 by Robert Miller
 *
 *    Modification log:
 */
#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/bits.h"

#define GUARD_NPC (ISEN_DIR + "npc/gate_guard")
#define ISENGARD_I_KNOCKED_ON_GATE "_isengard_i_knocked_on_gate"

// Global variables:
static object  Guard1, 
	       Guard2;
      // guards guarding the gate

static function Isen_Stage;
      // Checks what stage Isengard is currently in

// Prototypes
public void    reset_room();
public void    intruders();
public int     did_knock();
public int     pass_guards(object pl);
public int     pass_gate();
public int     query_disguised(object pl);
public int     in_combat();
public string  long_desc();
public string  gate_desc();
public string  tower_desc();
public string  ruin_desc();
public string  tunnel_desc();
public string  sky_desc();

public void
create_isengard()
{
    Isen_Stage = Master->query_isen_stage;

    set_short("the outer gates of Isengard");
    set_long(long_desc);
    add_item( ({"gate", "gates", "great gate", "great gates", "door",
		"doors", "solid door", "solid doors", "exterior gate",
		"exterior gates"}), gate_desc);
    add_item( ({"fortress", "isengard", "great fortress"}), BSN(
	"The fortress is ancient, but still seems to be maintained and "+
	"guarded. Carved out of a volcano long dead, the outer wall is "+
	"more than a hundred feet high. Beyond the wall stands a tall, "+
	"dark tower: the Tower of Orthanc, home of Saruman."));
    add_item( ({"wall", "ringwall", "ring", "volcanic ring", 
		"volcanic ringwall", "outer ring", "outer ringwall",
		"outer wall"}), BSN(
	"Towering high above the ground, this ringwall protects Isengard "+ 
	"from any possible threats. The wall is very steep and seems to "+
	"be unclimbable."));
    add_item( ({"ground", "path", "road", "pathway", "roadway"}), BSN(
	"This road crosses the barren Isengard Valley leading up to the "+ 
	"gates of Isengard."));
    add_item( ({"iron", "black iron", "solid black iron", "metal",
		"black metal", "solid iron"}), BSN(
	"This strange, black metal forms the hinges that hold the "+
	"mighty gates in place."));
    add_item( ({"hinges", "sturdy hinges", "hinge", "sturdy hinge"}), BSN(
	"Formed from a strange, black metal, these hinges hold the "+
	"great gates in place."));
    add_item( ({"volcano", "dead volcano", "extinct volcano"}), BSN(
	"The fortress has been contructed in what was once, some time ago, "+
	"a rageing volcano. The ringwall is all that remains of this old "+
	"work of nature."));
    add_item( ({"towers", "watch tower", "watch towers", "guard tower",
		"guard towers"}), tower_desc);
    add_item( ({"valley", "isengard valley"}), BSN(
	"A barren wasteland surrounds Isengard making up the Isengard "+
	"Valley. It has been cleared of trees by orcs of Isengard a long "+
	"time ago."));
    add_item( "ruins", ruin_desc);
    add_item( ({"tunnel", "ringwall tunnel"}), tunnel_desc);
    add_item( ({"sky", "cloud", "clouds", "star", "stars"}), sky_desc);
    add_item( ({"rock", "black rock", "strange rock", 
		"strange black rock"}), BSN(
	"The entire ringwall was constructed from this strange, black rock "+     
	"that was once a the wall of a volcano."));

    add_cmd_item("gate", "knock", did_knock);
    
    add_exit(ISEN_DIR + "tunnel1", "north", pass_gate, 0, 1);
    add_exit(ISEN_DIR + "isenroad/isenroad4", "south", in_combat, 0, 1);

    reset_room();
}

public void
reset_room()
{

    if ( (Isen_Stage() < ROHAN_STAGE_BATTLE_END) ||
	 (Isen_Stage() == ROHAN_STAGE_DEFEAT))
    {
	Guard1 = clone_npc(Guard1, GUARD_NPC);
	Guard2 = clone_npc(Guard2, GUARD_NPC);
	if (!sizeof(Guard1->query_team_others()))
	    Guard1->team_join(Guard2);
    }
    else
    {
	// No guards while Ents rule Isengard
	if (objectp(Guard1))
	{
	    Guard1->move_living("north", VOID);
	    Guard1->remove_object;
	}
	if (objectp(Guard2))
	{    
	    Guard2->move_living("north", VOID);
	    Guard2->remove_object;
	}
    }
}

public string
long_desc()
{
    string desc =
	"Here, at the end of the valley, a great fortress rises up "+
	"from the feet of the mountains. Carved out of an extinct "+
	"volcano, its outer ringwall is more than a hundred feet high.";
    
    switch (Isen_Stage())
    {
    case ROHAN_STAGE_PEACE..ROHAN_STAGE_BATTLE_END:
    case ROHAN_STAGE_DEFEAT:
	desc += " The exterior gates are protected by two huge "+
	    "watch towers hewn out of the rock of the ringwall, "+
	    "in addition to the guards that regularly patrol "+ 
	    "outside the gate.";
	break;
    case ROHAN_STAGE_VICTORY:
	desc += " The gates have been destroyed by tremendous force. "+
	    "Only ruins remain of the watch towers and the tunnel "+
	    "leading through the ringwall has collapsed, making "+
	    "entry impossible.";
	break;
    default:
	break;
    }
    return BSN(desc);
}

/*
 *  Function name: pass_gate()
 *  Description:   Determins if a player can use this particular add_exit
 *  Returns:       1: if player cannot pass
 *                 0: if the player can pass
 */
public int
pass_gate()
{
    object enemy;

    
    if (Isen_Stage() == ROHAN_STAGE_VICTORY)
    {
	write("The gates have been destroyed making it impossable to gain "+
	    "entrance to Isengard.\n");
	return 1;
    }
    if (TP->query_wiz_level())
    {    
	write("Welcome to Isengard, Wizard.");
	return 0;  // wizards are always welcome 
    }    
    if (objectp(enemy = TP->query_attack()) &&
	((enemy == Guard1) || (enemy == Guard2)))
    {
	write(QCTNAME(enemy) + " prevents you from leaving!");
	return 1;  //cannot pass if fighting the guards
    }
    if (objectp(present(Guard1, TO)) || objectp(present(Guard2, TO)))
    {    
	if (pass_guards(TP))
	    return 0; //Can pass
	else 
	    return 1; //Cannot pass
    }
    else
    {
	if ( (Isen_Stage() < ROHAN_STAGE_BATTLE_END) ||
	     (Isen_Stage() == ROHAN_STAGE_DEFEAT))
	{
	    if (TP->query_prop(ISENGARD_I_KNOCKED_ON_GATE))    
		//Player  knocked on gate and was able to pass
		return 0; //Let the player pass
	    else //Player knocked on the gate and was not able to pass
	    {    
		write("The gates are closed and silent. They appear unmovable.\n");
		return 1; //Cannot pass
	    }
	}
	else
	{
	    write("The gates are closed and silent. They appear unmoveable.");
	    return 1;   //Cannot pass
	}
    }
}

/*
 *  Function:    query_disguised()
 *  Description: Determins if a player is wearing armour from Isengard.
 *               in attemps to fool the guards by being disguised.
 *  Returns:     1: if disguised, 0: if not.
 */
public int
query_disguised(object pl)
{
    object head_armour = pl->query_armour(A_HEAD); 
    object body_armour = pl->query_armour(A_TORSO);

    if (objectp(head_armour) && head_armour->query_prop(ISEN_I_ARMOUR) &&
	objectp(body_armour) && body_armour->query_prop(ISEN_I_ARMOUR))
    {
	return 1; //Isengard armour on both head and body, they're disguised
    }
    return 0; //Not disguised
}

/*
 *  Function:    did_knock()
 *  Description: After a player knock on the gate, determins if they are
 *               able to pass into Isengard.
 *  Returns:     nothing: It sets a global variable Knocked to 1/0.
 */
public int
did_knock()
{
    if (Isen_Stage() == ROHAN_STAGE_VICTORY)
    {
	write("There are no longer any gates here to knock on.\n");
	return 1;
    }
    if (objectp(Guard1) || present(Guard2))
    {
	write("The guards look at you funny for knocking on the gate.\n");
	TP->remove_prop(ISENGARD_I_KNOCKED_ON_GATE, 1);
    }
    else
    {
	switch (TP->query_alignment())
	{
	case -1200..-150:  //evil aligned players
	    if (TP->test_bit("Gondor",ISEN_ENTRY_GROUP,ISEN_ENTRY_BIT))
		//Player did the entrance quest
	    {
		write("A guard from above shouts to you: Welcome back "+
		      "to Isengard, come on inside.\n");
		say("A guard from above shouts to " + QCTNAME(TP) +
		    ": Welcome back to Isengard, come on inside.\n");
		write("The gates open just wide enough for you to enter.\n");
            say("The gates open just wide enough for " + QCTNAME(TP) +
                " to enter.\n");
            TP->add_prop(ISENGARD_I_KNOCKED_ON_GATE, 1);
		// Able to pass
	    }
	    else
	    {
		write(BSN("A guard from above shouts to you: You do not "+
		      "have permission to enter Isengard and cannot enter "+
		      "til you have it."));
		say("A guard from above shouts to " + QCTNAME(TP) +
		    ": You do not permission to enter Isengard and "+
		    "cannot enter until you have it.\n");
		TP->remove_prop(ISENGARD_I_KNOCKED_ON_GATE, 1);
		//Cannot pass
	    }
	    break;
	default:
	    if(query_disguised(TP))
		//Player is disguised
	    {
		write("A guard from above shouts to you: Welcome back "+
		      "to Isengard, come on inside.\n");
		say("A guard from above shouts to " + QCTNAME(TP) +
		    ": Welcome back to Isengard, come on inside.\n");
		write("The gates open just wide enough for you to enter.\n");
            say("The gates open just wide enough for " + QCTNAME(TP) +
                " to enter.\n");
            TP->add_prop(ISENGARD_I_KNOCKED_ON_GATE, 1);
		//Able to pass
	    }
	    else
	    {
		write("A guard from above shouts to you: How dare you "+
		      "show your face at our gates! Leave now, while you "+
		      "still have the chance!\n");
		say("A guard from above shouts to " + QCTNAME(TP) +
		    ": How dare you show your face at our gates! Leave "+
		    "now, while you still have the chance!\n");
		TP->remove_prop(ISENGARD_I_KNOCKED_ON_GATE, 1);
		//Cannot pass
		intruders();  //Calls function to dispatch guards to get
			      //rid of the threat if they dont leave.
	    }
	    break;
	}
    }
    return 1;
}

/*
 *  Function:    pass_guards
 *  Description: checks to see if a player can pass the guards and enter
 *               into Isengard.
 *  Argument:    object pl - player object to be checked
 *  Returns:     1: can pass, 0: cannot pass. 
 */
public int
pass_guards(object pl)
{
    object  guard = Guard1;

    if (!objectp)
	guard = Guard2;

    switch (pl->query_alignment())
    {
    case -1200..-150:
	if (pl->test_bit("Gondor", ISEN_ENTRY_GROUP, ISEN_ENTRY_BIT))
	{
	    guard->command("say to " + pl->query_real_name() + 
			   " Welcome back to Isengard, go right on in.");
	    pl->catch_msg(QCTNAME(guard) + 
		" opens the gate just wide enough for you to enter.\n");
	    say(QCTNAME(guard) + " opens the gate just wide enough for " +
		QCTNAME(pl) + " to enter.\n", pl);
	    // Can pass:
	    return 1;
	}
      pl->catch_msg(QCTNAME(guard) + " steps in front of you blocking your path.\n");
      say(QCTNAME(guard) + " steps in front of "+ QCTNAME(pl) +
	    " blocking " + pl->query_possessive() + " path.\n", pl);
	guard->command("say to " + pl->query_real_name() +
	      " Where do you think you are "+
	      "going?\n\tYou cannot enter unless you are a friend of "+
	      "Isengard.");
	//Cannot pass
	return 0;
	break;
    default:
	if (query_disguised(pl))
	{
	    guard->command("say to " + pl->query_real_name() +
		" Welcome back to Isengard, go right in.");
	    pl->catch_msg(QCTNAME(guard) + 
		" opens the gate just wide enough for you to enter.\n");
	    say(QCTNAME(guard) + " opens the gate just wide " +
		"enough for " + QTNAME(pl) + " to enter.\n", pl);
	    // Can enter:
	    return 1;
	}
	pl->catch_msg(QCTNAME(guard) + " yells to you: How dare you show up here, "+
	      "at our gates!\n\tLeave now, while you still get the chance!\n");
	say(QCTNAME(guard) + " yells to "+ QCTNAME(pl) +": How dare you "+ 
	    "show your face here, at our gates!\n\tLeave now, while "+
	    "you still get the chance!\n", pl);
	// Cannot pass
	intruders();  //calls a function that will send guards to
		      //deal with the players that do not leave.
	return 0;
	break;
    }
    return 0;
}

/*
 *  Function:    intruders()
 *  Description: Function waits a certain amount of time after a threat
 *               has been told to leave, if they dont, a group of guards
 *               will be dispached to deal with the problem.
 *  Returns:     Nothing
 */
public void
intruders()
{
    /* 
     *  sets an alarm
     *  clones a random number of guards and a commander
     *  attacks the intruder if still there
     */
}

/*
 *  Function:    in_combat
 *  Description: gives a chance that an NPC will block the player from
 *               leaving if they are in combat with a NPC in the room.
 *  Returns:     1: got blocked, 0: made it past
 */
public int
in_combat()
{
    return 0;
}

/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just leaved this inventory
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!objectp(ob) || !interactive(ob))
	return;

    ob->remove_prop(ISENGARD_I_KNOCKED_ON_GATE);
}

string
gate_desc()
{
    string gtdesc;

    switch (Isen_Stage())
    {
    case ROHAN_STAGE_VICTORY:
	gtdesc = "The gates have been destroyed by some tremendous force. "+   
	   "There is no way to gain entrance into Isengard since the tunnel "+
	   "and gates have been destroyed.";
	break;
    default:
	gtdesc = "The great gates of the fortress of Isengard are made of "+
	   "solid, black iron. Sturdily wrought hinges, of a stronger "+
	   "metal, support the gates and strengthen the already solid "+
	   "doors. Twenty feet tall and equally wide, the gates lead "+
	   "through the volcanic ring into the heart of Isengard.";
	break;
    }
    return BSN(gtdesc);
}

string
tower_desc()
{
    string twrdesc;
    
    switch (tod())
    {
    case "night":
	twrdesc = "Through the night air, two guard towers loom high above.";
	break;
    default:
	twrdesc = "Looming high above are two guard towers. "+
	   "They are used to aid in the protection of Isengard since "+
	   "they rise well above the volcanic ring.";
	break;
    }
    return BSN(twrdesc);

}

string
tunnel_desc()
{
    string tunndesc;

    switch (Isen_Stage())
    {
    case ROHAN_STAGE_VICTORY:
	tunndesc = "The gates and tunnel have been destroyed by some "+ 
	   "great force preventing anyone from passing through them and "+
	   "entering the heart of Isengard.";
	break;
    default:
	tunndesc = "Beyond the gates covering this tunnel, remains the only "+
         "entrance into "+
	   "and out of Isengard. The tunnel has been dug right through the "+
	   "volcanic ringwall and is guarded from above as well as within.";
	break;
    }
    return BSN(tunndesc);

}

string
ruin_desc()
{
    string ruindesc;

    switch (Isen_Stage())
    {
    case ROHAN_STAGE_VICTORY:
	ruindesc = "These ruins were once the great gates leading through "+
	    "the ringwall into the heart of Isengard. The result of some "+
	    "great force, nothing remains but rubble and debris.";
	break;
    default:
	ruindesc = "There are no ruins visable around here."; 
	break;
    }
    return BSN(ruindesc);
}

string
sky_desc()
{
    string skydesc;
    
    string time = tod();

    switch (tod())
    {
    case "night":
	skydesc = "The night sky is clear and full of stars. The darkness "+ 
	   "limits how far one can see.";
	break;
    case "early morning":
    case "morning":
	skydesc = "The " +time+ " sun begins its journey into the sky "+
	   "casting shadows across the lands of Rohan including this "+
	   "pathway.";
	break;
    case "noon":
	skydesc = "The noontime sun shines high in the sky warming up the "+
	   "entire area. Looking about, there are no areas free of the "+
	   "sun since no shadows are present.";
	break;
    case "afternoon":
    case "evening":
	skydesc = "The " +time+ " sun begins to decend in the sky, once "+
	   "again forming shadows that stretch across the plains and "+
	   "land around.";
	break;
    default:
	skydesc += "Something is wrong, please notify a wizard!";
	break;
    }
    return BSN(skydesc);

}
