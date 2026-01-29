/*  Based upon 
 *  /d/Avenir/common/outpost/mon/aglyna
 *  Gives rides to destinations in the City,
 *  Keeps outlanders from wandering around into
 *  forbidden places
 */

inherit "/d/Avenir/common/city/mon/chair_steed";
inherit "/std/act/asking";
inherit "/std/act/trigaction";

#include "/d/Avenir/common/city/city.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include <macros.h>
#include <stdproperties.h>

int   last_met;
varargs int check_present(int dont_remove = 0);

void
create_chair_steed()
{
    set_name("bondservant");
    set_race_name("human");
    add_name(({"steed", "servant", "slave", "man", "bondsman",
	"chair", "sedan chair", "sedan", "rickshaw"}));
    set_pname("bondservants");
    set_short("sedan chair pulled by a bondservant");
    set_pshort("bondservants pulling sedan chairs");
    set_adj(({"sedan", "chair", "ziggurat"}));
    set_long("This bondsman's purpose in life is to serve others "+
      "by pulling sedan chairs through the Forbidden City. "+
      "He appears to be healthy and well-fed, and the sedan "+
      "chair he pulls is in excellent repair. It is large "+
      "enough for one person only. If you need assistance "+
      "getting in, the bondsman might help if you ask.\n");
    add_item(({"chair", "sedan chair", "sedan"}),
      "A comfortable sedan chair, large enough for one person. "+       
      "It is pulled by a male bondservant.\n");

    set_gender(G_NEUTER);

    last_met = time();
    set_alarm(100.0, 100.0, check_present);

    set_places("gate", ({
	ZIG + "level1/landing",
	ENTRY + "ez5",
	ENTRY + "ez4",
	ENTRY + "ez3",
	ENTRY + "ez2",
	ENTRY + "ez1",
	ENTRY + "ez0"
    }));
    set_places("zigg",({
	ENTRY + "ez0",
	ENTRY + "ez1",
	ENTRY + "ez2",
	ENTRY + "ez3",
	ENTRY + "ez4",
	ENTRY + "ez5",
	ZIG  + "level1/landing"
    }));

    set_default_answer(VBFC_ME("what_me"));
}

/*
 * Function name: as_hook_riders_entered_room
 * Returns:       the string the players riding the steed will
 *                see when the steed enters a room.
 */
public string
as_hook_riders_entered_room()
{
    string where;

    if (query_trip_type() == "zigg")
	where = "south";
    else
	where = "north";

    return "The bondservant"+ 
    ONEOF(({" continues to pull you "+ where, 
	" detours around some congestion and then "+
	"continues " + where }))
    + ".\n";
}

/*
 * Function name: check_present
 * Description:   Fly away if no one is around. Not using this right now.
 * Returns:
 */
varargs int
check_present(int dont_remove = 0)
{
    object   *objs;

    if(!environment(this_object()))
	return 0;

    objs = deep_inventory(environment(this_object()));

    objs = filter(objs, interactive) - ({ 0 });

    if(!sizeof(objs) && !dont_remove && ((time() - last_met) > 100))
	remove_object();

    return !!sizeof(objs);
}


/*
 * Function name: allow_rider
 * Description:   This function is called when the aglyna is asked
 *                to allow someone to ride it.
 * Arguments:     question - The question as put
 */
int
allow_rider(string str)
{
    return 1;
}


string
what_me()
{
    command("say I'm not permitted to answer questions.");
    command("say All I can tell you is to mount the chair "+
      "if you want me to take you to or from the Ziggurat.\n");
    return "";    
}

/* Function name: can_mount
 * Description:   Is the living skilled enough to mount the steed?
 *                Called by do_mount. Replace with your own criteria
 *                if needed. notify_fail isn't used.
 * Arguments:     object - the living object
 * Returns:       int - true if succeeds
 */
public int
can_mount(object o)
{
    return 1;
}

/* Function name: can_dismount
 * Description:   Can the living dismount? Might be useful to prevent
 *                dismount on certain locations (e.g. while flying).
 *                Called by sh_do_dismount. Replace with your own criteria
 *                if needed.
 * Arguments:     object - the living object
 * Returns:       int - true if succeeds
 */
public int
can_dismount(object o)
{
    return 1;
}


void
init_living()
{
    ::init_living();

    // reset my internal clock of who I have met
    if(check_present(1))
	last_met = time();
}


/*
 * Function name: return_anger
 * Description  : When the NPC is emoted on negatively, this function 
 *                is called after a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_anger(object actor, string adverb)
{
    int i;

    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
      (environment(actor) != environment()))
    {
	return;
    }

    i = random(10);

    /* Do the stuff. */
    switch(i)
    {
    case 0..2:
	{
	    command("say You are cruel, to treat me so.");
	    return;
	}
    case 3..5:
	{
	    command("whimper slight");
	    command("say I am but a humble servant, why must you "+
	      "use me so ill?");
	    return;
	}
    case 6..9:
	{
	    command("smile submis");
	    return;
	}
    }
}

/*
 * Function name: return_strut
 * Description  : When the NPC is emoted on this function 
 *                is called after a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_strut(object actor, string adverb)
{
    int i;

    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
      (environment(actor) != environment()))
    {
	return;
    }

    i = random(10);

    /* Do the stuff. */
    switch(i)
    {
    case 0..2:
	{
	    command("peer "+ OB_NAME(actor));
	    return;
	}
    case 3..5:
	{
	    command("smile "+ OB_NAME(actor));
	    return;
	}
    case 6..9:
	{
	    command("strut");
	    return;
	}
    }
}

/*
 * Function name: return_good
 * Description  : When the NPC is emoted on negatively, this function 
 *                is called after a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_good(object actor, string adverb)
{
    int i;

    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
      (environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    i = random(10);

    switch(i)
    {
    case 0..2:
	{
	    command("smile sweet "+ OB_NAME(actor));
	    return;
	}
    case 3..5:
	{
	    command("purr");
	    return;
	}
    case 6..9:
	{
	    command("sigh happ "+ OB_NAME(actor));
	    return;
	}
    }
}


/*
 * Function name: emote_hook
 * Description  : This hook is called whenever an emotion is performed on this
 *                NPC. If it is an emotion that we hook on, call a little
 *                alarm and then call the return function.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 */
void
emote_hook(string emote, object actor, string adverb)
{
    /* See if we want to trigger on the emote. If so, call a little alarm
     * for the reaction function.
     */
    switch(emote)
    {       
    case "grope":
    case "fondle":
    case "lick":
    case "slap":
    case "kick":
    case "poke":
    case "french":       
    case "finger":     
    case "fondle":    
    case "ignore": 
    case "pinch":             
    case "puke":     
    case "spank":
    case "tickle":
    case "snarl":
    case "startle":
    case "duh":  
	set_alarm(3.0, 0.0, &return_anger(actor, adverb) );
	return;
    case "admire":
    case "dance":  
    case "cringe":
    case "grovel":  
    case "dance":    
    case "worship":      
	set_alarm(3.0, 0.0, &return_strut(actor, adverb) );
	return;
    case "hug":
    case "kiss":
    case "cuddle":
    case "snuggle":
    case "caress":
    case "comfort":
    case "dance":     
    case "greet":  
    case "hold":              
    case "love":
    case "pat":
    case "nuzzle":
    case "ruffle":
    case "thank":
	set_alarm(3.0, 0.0, &return_good(actor, adverb));
	return;
    }
}
