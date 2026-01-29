/*
 *      /d/Gondor/rohan/plains/plain.c
 *
 *     Standard file for the plains of Rohan
 *     v4.0    By Hamurabbi(e90jp1@hh.se) in Sep 1991 - Mar 1992
 *     Debugged by Randor in 2-Apr-93
 *     Updated by Olorin 18-jan-1995
 *
 *      Modification log:
 *      24-Jan-1997, Olorin: Major revision.
 *      01-Oct-2004, Tigerlily: tweaked herb setup 
 *      15-Feb-2009, Eowul: Removed herb setup tweaks
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/*
 *      Prototypes:
 */
public string  describe(string str);
public string  river_desc();
public string  track();
public void    set_npc_number(int n);
public void    set_npc_file(string s);

/*
 *      Global variables:
 */
private string  ExtraLine,
                Geo,
                Wet,
                Grass,
                Where,
                Land,
		NpcFile,
                RWhere,
                RName,
                TFrom,       // direction that tracks lead from
                TTo;         // direction that tracks lead to
private int     RHard,
                Special;
private object	*Npcs;

public void    set_extraline(string s)      { ExtraLine = s; }
public void    set_geo(string s)            { Geo = s; }
public void    set_wet(string s)            { Wet = s; }
public void    set_grass(string s)          { Grass = s; }
public void    set_where(string s)          { Where = s; }
public void    set_land(string s)           { Land = s; }
public void    set_rwhere(string s)         { RWhere = s; }
public void    set_rname(string s)          { RName = s; }
public void    set_river_name(string s)     { RName = s; }
public void    set_tfrom(string s)          { TFrom = s; }
public void    set_tto(string s)            { TTo = s; }
public void    set_npc_file(string s)       { NpcFile = s; }

public void    set_rhard(int i)             { RHard = i; }
public void    set_special(int i)           { Special = i; }
public void    set_npc_number(int n)        { Npcs = allocate(n); }

/*
 * Function name: create_plain
 * Description:   Creator, redefine this function in your room file.
 */
public void
create_plain()
{
    set_extraline("This is just an example room.");
    set_land("Rohan");
    set_where("central");
}

/*
 * Function name: create_gondor
 * Description:   Creator.
 */
nomask void
create_gondor()
{
    int     i, s,
            seed;
    object  clock = find_object(CLOCK);
    string  fname;

    create_plain();

    set_short("in the " + Where + " parts of " + Land);
    set_long(describe);

    if (!item_id("ground"))
        add_item(({ "ground", "grass" }), track);

    if (strlen(RName))
    {
        if (!item_id("river"))
            add_item(({ "river", "stream", lower_case(RName) }), river_desc);
        BEACH;
        add_prop(OBJ_I_CONTAIN_WATER, 1000000);
        if (RHard == 1)
            add_item(({ "ford" }), BSN(
                "To the " + RWhere + " you can see a ford crossing the "
                    + RName + " between low banks. The trampled grass shows "
                    + "you that several horses passed here recently."));
    }

    switch (Special)
    {
    case 1:
        add_item(({"bank", "clouds", "bank of clouds" }), BSN(
            "The bank of clouds looks familiar, maybe they look like "
                + "snow covered mountains."));
        break;
    case 2:
        add_item(({"mountains", "white mountains", "ered nimrais", }),
            BSN("The mighty White Mountains stretch from east to west. "
                + "They are peaked with blending white snow."));
        break;
    case 3:
        add_item(({"forest", "fangorn", "forest fangorn", "fangorn forest", }),
            BSN("It looks as if thousands of eyes are staring out at you "
                + "from the dense, gloomy forest to the west. You get an "
                + "uneasy feeling about it."));
        break;
    case 4:
        add_item(({"forest", "fangorn", "forest fangorn", "fangorn forest", }),
            BSN("It looks as if thousands of eyes are staring out at you "
                + "from the dense, gloomy forest to the west. You get an "
                + "uneasy feeling about it."));
        break;
    case 5:
        add_item(({"road", "broad road", "westroad" }), BSN(
            "The road looks to be in good repair, but there does not "
                + "seem to be much travel on it."));
        break;
    case 6:
        add_item(({"mountains", "misty mountains", "hithaeglir" }), BSN(
            "The magnificient Misty Mountains rise to the west. "
                + "Their snowcovered peaks are hidden in the clouds. "
                + "They are impossible to access from here."));
        break;
    case 7:
        add_item(({"mountains", "misty mountains", "hithaeglir" }), BSN(
            "The magnificient Misty Mountains rise to the west. "
                + "Their snowcovered peaks are hidden in the clouds. "
                + "They are impossible to access from here."));
        break;
    }
    
    fname = explode(file_name(TO), "/")[5];
    for (i = 0, s = strlen(fname); i < s; i++)
        seed += fname[i] * (i + 1) * 23;
    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("plains"), seed + 1),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs(), seed + 2), }),
                  ({"plain", "plains", "ground", "grass",}), 5);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    if (sizeof(Npcs))
    {
	set_alarm(4.0, 0.0, &clone_npcs(Npcs, NpcFile, 10.0));
    }
}
    

public string
describe(string str)
{
    object  clock = find_object(CLOCK);
    string  time,
            long_descf;

    if (str)
        return "";
    long_descf =
        "You are standing in the " + Where + " parts of " + Land
      + " in Rohan. The land is " + Geo + " and " + Wet
      + ". The ground is covered with " + Grass + " grass.";

    time = clock->query_time_of_day();
    long_descf += " It is " + time + " in Rohan.";

    switch (time)
    {
    case "night":
        long_descf += " The moon is spreading its silver light over the "
          + "grass covered plains. All is calm and quiet.";
        break;
    case "early morning":
        long_descf += " The sun has barely made it over the horizon. The "
          + "air is fresh and new. Some birds have awoken and their "
          + "songs fill the air with pleasant music.";
        break;
    case "morning":
        long_descf += " The sun has worked its way up the sky. Now is a "
          + "perfect time for travelling, not too warm and not too cold.";
        break;
    case "noon":
        long_descf += " The sun shines down from right above your head. "
          + "All is calm, not even a bird is singing.";
        break;
    case "afternoon":
        long_descf += " The sun is moving towards the west, slowly "
          + "descending on its way around the world. The birds are "
          + "singing and rabbits are playing all around you.";
        break;
    case "evening":
        long_descf += " The sun paints the horizon with its firelike "
          + "colours towards the west. The birds and animals are "
          + "slowly moving home to their nests and lairs.";
        break;
    }

    switch (Special)
    {
    case 1:
        long_descf += " To the south you see something that you think is a "
          + "low bank of clouds.";
        break;
    case 2:
        long_descf += " To the south you can see the mighty White Mountains.";
        break;
    case 3:
        long_descf += " To the west is the forest Fangorn.";
        break;
    case 4:
        long_descf += " To the north is the forest Fangorn.";
        break;
    case 5:
        long_descf += " To the south you see a broad road.";
        break;
    case 6:
        long_descf += " The mighty Misty Mountains are to the west.";
        break;
    case 7:
        long_descf += " The mighty Misty Mountains rise to the north.";
        break;
    }

    switch (LOW(RName))
    {
    case "snowbourn":
        long_descf += " The white river Snowbourn is to the "+ RWhere+".";
        break;
    case "entwash":
        long_descf += " The musty river Entwash is to the "+RWhere+".";
        break;
    case "deeping stream":
        long_descf += " The Deeping Stream is to the "+RWhere+".";
        break;
    case "isen":
        long_descf += " The black river Isen is to the "+RWhere+".";
        break;
    case "limlight":
        long_descf += " The river Limlight is to the "+RWhere+".";
        break;
    case "anduin":
        long_descf += " The great river Anduin is to the "+RWhere+".";
        break;
    case "mering stream":
        long_descf += " The Mering stream is to the "+RWhere+".";
        break;
    }

    if (RHard == 1)
        long_descf += " One can cross the " + RName + " on a ford here.";
    if (strlen(ExtraLine))
        long_descf += " " + ExtraLine;
    return BSN(long_descf);
}

public int
stream()
{
    write("You manage to cross the river.\n\n");
    return 0;
}

public int
no_cross()
{
    if (!TP->query_wiz_level())
    {
        write("You don't dare to cross the river here. It looks too strong.\n");
        return 1;
    }
    return 0;
}

public int
crossing()
{
    int     test = TP->query_skill(SS_SWIM),
	    fat = TP->query_fatigue(),
	    tmpRHard = RHard,
            diff;

    if (TP->query_encumberance_weight() > 80)
        tmpRHard *= 2;

    if (fat < TP->query_max_fatigue() &&
	fat < tmpRHard)
    {
        write("You are too tired to cross the river.\n");
        return 1;
    }

    SAYBB(" enters the river to the " + RWhere + ".");
    write("You enter the river.\n");

    if ((diff = (tmpRHard - test)) <= 0)
    {
        write("You manage to cross the river.\n");
        return 0;
    }
    else if (diff < 10)
    {
        write(BSN("The current gets you and you are dragged down into "
          + "the water, hitting your knee on a rock."));
        TP->add_fatigue( - tmpRHard);
        TP->reduce_hit_point(2 * diff);
        if (TP->query_hp() <= 0)
        {
            write("You drown in the river.\n");
	    /* ok, perhaps they're visible if they drown */
            say(QCTNAME(TP) + " tries to cross but fails and drowns.\n");
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
          + "under the surface hitting your head on a rock. You are hurt."));
        TP->add_fatigue( - 5 * diff);
        TP->reduce_hit_point(5 * diff);
        if (TP->query_hp() <= 0)
        {
            write("You drown in the river.\n");
            say(QCTNAME(TP) + " tries to cross but fails and drowns.\n");
            log_file("traps", TP->query_name() + " (" + test + ") "
                + "drowned in the river " + RName + " on "
                + ctime(time()) + ".\n");
            TP->do_die(TO);
	    return 1;
        }
        write(BSN("You fail to cross here. The flowing water is too strong "
            + "for you, and you are lucky to reach the bank again."));
        SAYBB(" tries to cross but fails miserably.");
    }
    return 1;
}

public int
drown()
{
    if (SECURITY->query_wiz_dom(TP->query_real_name()) == "Gondor")
    {
        write("This river is still closed for mortals, Wizard of Gondor!\n");
        return crossing();
    }
    write("The river is much too rapid to cross right here.\n");
    return 1;
}

public int
closed()
{
    write(BSN("You dare not enter this dark gloomy forest yet. Maybe "
      + "another day, you think, there will be more monsters there, "
      + "then I'll get back there."));
    return 1;
}

public string
track()
{
    int     test = TP->query_skill(SS_TRACKING);
    string  gen,
            beskr = "You look down and find the ground " + Geo + " and "
                  + Wet + ". It is covered by " + Grass + " grass.";

    SAYBB(" examines the ground.");

    if ((test >= query_prop(ROOM_I_HIDE)) && stringp(TFrom) && stringp(TTo))
    {
        gen = TP->query_pronoun();
        beskr += " You see that the grass have been bruised and many "
          + "straws are crushed, as if many steelcled feet have passed "
          + "here not too long ago. The tracks lead from the " + TFrom
          + " to the " + TTo + ".";
        SAYBB(" smirks as if "+gen+" had discovered "
          + "something on the ground.");
    }
    return BSN(beskr);
}

public string
river_desc()
{
    string  beskr;

    switch (RHard)
    {
    case 1:
        beskr = "It looks like there is a ford right here. The "
          + RName + " flows very gently here.";
        break;
    case 2..5:
        beskr = "The river " + RName + " flows quite gently right here. "
          + "It looks that it should be quite easy to cross it here.";
        break;
    case 6..10:
        beskr = "The river " + RName + " seems to flow quite gently right "
          + "here. It might be quite easy to cross it here.";
        break;
    case 11..20:
        beskr = "Here the river " + RName + " flows away really fast and "
          + "it might be quite hard to cross it here.";
        break;
    case 21..30:
        beskr = "Here the river " + RName + " flows away seemingly gently, "
          + "but it is quite broad and might be quite hard to cross here.";
        break;
    case 31..40:
        beskr = "The " + RName + " rushes away really fast here. Foam whirls "
          + "in the air and mists flow in the air. It is nearly impossible to "
          + "cross here.";
        break;
    case 41..50:
    default:
        beskr = "At this place the river "+RName+" is impossible to cross. "
          + "The water roars and splashes as it races towards its outlet.";
        break;
    }

    return BSN(beskr);
}

public void
init()
{
    ::init();
    if (strlen(RName))
        init_drink();
}

/*
 * Function name: clone_npc
 * Description:   Clone one npc into this room and arm it.
 * Arguments:     npc  - the object pointer to the npc.
 *                file - the file name of the npc.
 *                path - monster restrain path 
 * Returns:       the object pointer the the npc.
 */
public varargs object
clone_npc(object npc, string file, mixed path = (ROH_DIR + "plains"))
{
    if (objectp(npc))
        return npc;

    npc = ::clone_npc(npc, file, path);
    npc->set_random_move(5);

    return npc;
}
