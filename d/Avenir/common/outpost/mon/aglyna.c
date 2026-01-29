/*  Last update:  07 Jun 99: Lilith -- updated aglyna 
 *                to prevent Outlanders from riding 
 *                except at the request of a sybarite.
 *  /d/Avenir/common/outpost/mon/aglyna
 */

inherit "/d/Avenir/inherit/air_steed";
inherit "/std/act/asking";
inherit "/std/act/trigaction";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"


#define AGLYNA_ALLOWS "_avenir_aglyna_allows_rider"

int   last_met;


varargs int check_present(int dont_remove = 0);

void
create_air_steed()
{
    set_name("aglyna");
    set_race_name("aglyna");
    add_name("steed");
    set_pname("nargathu");
    set_pshort("terrible aglyna");

    set_adj("terrible");

    set_long("It is an aglyna, a sinuous, lizard-creature with "
       + "huge, bat-like wings extending out from its body.\nIts "
       + "head is wedge-shaped, with huge, long-lashed eyes "
       + "that gleam with intelligence. Each foot ends in three "
       + "razor-sharp talons that can rend flesh from bone with "
       + "a single swipe. Its tail is as long as its body, and " 
       + "barbed at the tip.\nThe aglyna's back is soft and scaly.\n");


    set_alarm(100.0, 100.0, check_present);
    last_met = time();

    set_places("dead",   ({ OUTPOST + "seawall",
                            SHIP + "bazaar/sea1",
                            SHIP + "bazaar/sea2",
                            SHIP + "bazaar/sea3",
                            SHIP + "sea/darksea5",
                            SHIP + "sea/darksea6",
                            DEAD + "path/landing",
                            DEAD + "path/path1",
                            DEAD + "path/path3",
                            DEAD + "path/path5",
                            DEAD + "path/path7",
                            DEAD + "hill/hill13",
                            DEAD + "path/entry" }));

    set_places("seawall", ({ DEAD + "path/entry",
                            DEAD + "hill/hill13",
                            DEAD + "path/path7",
                            DEAD + "path/path3",
                            DEAD + "path/path1",
                            DEAD + "path/landing",
                            SHIP + "sea/darksea5",
                            SHIP + "sea/darksea6",
                            SHIP + "bazaar/sea2",
                            SHIP + "bazaar/sea3",
                            SHIP + "bazaar/sea1",
                            OUTPOST + "seawall" }));

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

    if(query_trip_type() == "seawall")
       where = "south";
    else
       where = "north";

    return QCTNAME(this_object()) + " " +
           ONEOF(({"lets out a screeching cry as it continues "
           + "to fly " + where, "beats its great wings", 
             "dives and ascends with dizzying speed on its "
           + "way " + where, "continues to fly " + where,
             "stops for a moment, hovering in mid-air, "
           + "and then continues its flight " + where }))
           + ".\n";
}


/*
 * Function name: check_present
 * Description:   Fly away if no one is around
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
    string name;
    object person;

    name = lower_case(str);    
    person = find_player(name);
   
    if (!person || (environment(person) != environment(this_object())))
    {
        write("You get the feeling that the "+ short() +" does "+
            "not understand who you want to ride it.\n");
        command("emote blinks its long-lashed eyes.\n");
        return 1;
    }
       
    person->add_prop(AGLYNA_ALLOWS, 1);
    command("emote shivers and twitches its scaled skin over "+
        "rippling muscles.");
    write("You get the feeling that the aglyna will submit to "+
        "your will and allow "+ capitalize(name) +" to ride.\n");
    return 1;
}


/*
 * Function name: catch_question
 * Description:   This function is called in each living being someone asks a
 *                question to.
 * Arguments:     question - The question as put
 */
public int
catch_question(string str)
{
    mixed ret;
    string par;
    string file, arg, person;

    // allow people to ride if a sybarite asks ...
    if (parse_command(str, ({}), 
        "[to] [please] 'give' / 'allow' / 'permit' [the] %s", 
        person))
    {
        if (!IS_SYBARITE(this_player()))
        {
            command("emote shakes its wedge-shaped head and snaps "+
                "its jaws angrily.");
            return 1;
        }
       
        allow_rider(person);
        return 1;
    }
    ret = ::catch_question(str);
    return ret;
}

string
what_me()
{
    command("emote switches its tail around.");
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
    int allow;

    if (o->query_skill(SS_ANI_HANDL) < 20)
    {
        o->catch_tell("You are not skilled enough to handle this " +
            short(o) + ".\n");
        return 0;
    }
   
    if (!IS_SYBARITE(o))
    {
        allow = o->query_prop(AGLYNA_ALLOWS);
        if (!allow)
        {
            command("emote bucks wildly.");         
            return 0;
        }
    }        

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
    if (o->query_prop(AGLYNA_ALLOWS))
        o->remove_prop(AGLYNA_ALLOWS);
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
            command("snarl at "+ OB_NAME(actor));
            command("kill "+ OB_NAME(actor));
            return;
        }
        case 3..5:
        {
            command("growl menacing");
            return;
        }
        case 6..9:
        {
            command("rears up and lashes its tail angrily.");
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
            command("nudge "+ OB_NAME(actor));
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

    if (!IS_SYBARITE(actor) && i > 5)
    {
        command("growl "+ OB_NAME(actor));
        return;
    }

    switch(i)
    {
        case 0..2:
        {
            command("lick "+ OB_NAME(actor));
            return;
        }
        case 3..5:
        {
            command("purr");
            return;
        }
        case 6..9:
        {
            command("nibble "+ OB_NAME(actor));
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
