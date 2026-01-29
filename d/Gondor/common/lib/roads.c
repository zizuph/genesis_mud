/*
 *	/d/Gondor/common/lib/roads.c
 *
 *	This file is to replace /d/Gondor/common/lib/road.c
 *	It is a file to inherit in outdoor rooms that represent
 *	part of a major road.
 *
 *	Olorin, August 1995
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/*
 *      Prototypes:
 */
public string  long_desc();
public int     check_lightlevel();

/*
 *	Global variables
 */
static string  Street      = "an old broken path",
               Where       = "central",
               County      = "Tharbad",
               Land        = "old Gondor",
               Extraline   = "",
               Mountain    = "Greyflood slopes",
               Vegetation  = "tangled undergrowth",
               Forest      = "forest",
               RName       = "",
               RWhere      = "";
static int     RHard       = 0;

void    set_where(string str)       { Where = str; }
void    set_county(string str)      { County = str; }
void    set_land(string str)        { Land = str; }
void    set_extraline(string str)   { Extraline = str; }
void    set_mountain(string str)    { Mountain = str; }
void    set_vegetation(string str)  { Vegetation = str; }
void    set_forest(string str)      { Forest = str; }
void    set_river_name(string str)  { RName = str; }
void    set_rwhere(string str)      { RWhere = str; }
void    set_rhard(int i)            { RHard = i; }

public int     query_road() { return 1; }

public void
create_roads()
{
    ::create_gondor();
}

nomask void
create_gondor()
{
    add_prop(ROOM_I_LIGHT, check_lightlevel);

    create_roads();

    set_short(Street + " in " + Land);
    set_long(long_desc);

    if (!item_id("road"))
        add_item("road",
            "You are on a dusty road in "+Land+". You are not sure where "
          + "it leads.\n");
    if (!item_id("ground"))
        add_item("ground", "You see a dusty road.\n");
}

public string
long_desc()
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            desc = CAP(Street)+" in the "+Where
                 + " parts of "+County+" in "+Land+".",
            moon;

    switch (time)
    {
    case "early morning":
    case "morning":
        desc += " It is "+time+" in "+Land+". The "+time+" fog makes it "
          + "difficult to see far. In the east, the sun is rising.";
        break;
    case "noon":
        desc += " It is "+time+" now, and a hot day in "+Land+".";
        break;
    case "afternoon":
    case "evening":
        desc += " The sun is setting at the western horizon. It is "
          + time+" in "+Land+". A light breeze touches your face.";
        break;
    case "night":
        switch(moon = clock->query_moon())
        {
            case "dark":
                desc += " There is no moon in the sky, only the stars are "
                     +  "shining and twinkling, giving little light.";
                break;
            case "full":
                desc += " The full moon is up in the sky, bathing the "
                     +  "lands of "+County+" in its silvery light.";
            default:
                desc += " The stars are twinkling in the clear "+time+" sky. "
                     +  "The "+moon+" moon casts its silvery light over the "
                     +  Vegetation+". The land of "+Land+" seems quiet.";
        }
        break;
    }

    if (strlen(Extraline))
        desc += " " + Extraline;
    return BSN(desc);
}

public int
crossing()
{
    int     test = TP->query_skill(SS_SWIM),
            diff;

    if (TP->query_encumberance_weight() > 80)
        RHard *= 2;

    if (TP->query_fatigue() < RHard)
    {
        write("You are too tired to cross the river.\n");
        return 1;
    }

    SAYBB(" enters the river to the " + RWhere + ".");
    write("You enter the river.\n");

    if ((diff = (RHard - test)) <= 0)
    {
        write("You manage to cross the river.\n");
        return 0;
    }
    else if (diff < 10)
    {
        write(BSN("The current gets you and you are dragged down into "
          + "the water, hitting your knee on a rock."));
        TP->add_fatigue( - RHard);
        TP->reduce_hit_point(2 * diff);
        if (TP->query_hp() <= 0)
        {
            write("You drown in the river.\n");
            SAY(" tries to cross but fails and drowns.");
            TP->do_die(TO);
            log_file("traps", TP->query_name() + " (" + test + ") "
                + "drowned in the river " + RName + " on "
                + ctime(time()) + ".\n");
        }
        else
        {
            write(BSN("You see that the water is a little too much for you "
                + "right here. Maybe you could cross, but why risk it, you "
                + "think, when you return to the shore."));
            SAYBB(" tries to cross but fails.");
        }
    }
    else
    {
        write(BSN("The flowing water overruns you, and you slide down "
          + "under the surface, hitting your head on a rock. You are hurt."));
        TP->add_fatigue( - 5 * RHard);
        TP->reduce_hit_point(5 * diff);
        if (TP->query_hp() <= 0)
        {
            write("You drown in the river.\n");
            SAY(" tries to cross but fails and drowns.");
            TP->do_die(TO);
            log_file("traps", TP->query_name() + " (" + test + ") "
                + "drowned in the river " + RName + " on "
                + ctime(time()) + ".\n");
        }
        write(BSN("You fail to cross here. The flowing water is too strong "
            + "for you, and you are lucky to reach the bank again."));
        SAY(" tries to cross but fails miserably.");
    }
    return 1;
}

/*
 * Function name: swim
 * Description:   Can we cross a body of water by swimming?
 * Argument:      diff  - the difficulty
 *                tired - the fatigue
 * Returns:       0 - success, 1 - failure.
 */
public int
swim(int diff = 10, int tired = 10)
{
    object  tp = TP;
    int     skill = tp->query_skill(SS_SWIM);

    diff = diff/2 + random(diff) + 1;
    if (tp->query_encumberance_weight() > 80)
    {
        tired *= 2;
	diff  *= 2;
    }

    if (skill < diff)
    {
        write("This water is too difficult for you to swim safely.\n"
            + "You are struggling.\n"
            + "You start to inhale water!\n"
            + "Your body washes back to near your starting point.\n");
	tp->reduce_hit_point(diff - skill);
        SAYBB(" fails to make it to the other shore.");
        return 1;
    }
    if (tp->query_fatigue() < tired)
    {
        write("You are too tired to cross the river.\n");
        SAYBB(" is too tired to cross the river.");
        return 1;
    }

    write("You swim across the river" 
	  + (strlen(RName) ? " " + RName : "") + ".\n");
    return 0;
}

public int
check_lightlevel()
{
    switch (tod())
    {
        case "early morning":
        case "evening":
            return 2;
            break;
        case "morning":
        case "noon":
        case "afternoon":
            return 3;
            break;
        default:
            return 1;
            break;
    }
}



void
set_street(string str)
{
/* Street = LOW(str);  */
Street = str;
    if (Street[0..1] != "a " &&
        Street[0..2] != "an " &&
        Street[0..3] != "the ")
    {
        Street = LANG_ADDART(Street);
    }
}
