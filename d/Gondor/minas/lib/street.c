/*
 *	/d/Gondor/minas/lib/street.c
 *
 *      Originally by Elessar.
 *	Rewritten by Olorin, December 1995
 *
 *      Copyright (c) 1995, 1997 by Christian Markus
 *
 *	Modification log:
 *      26-Jan-1997, Olorin: General revision.
 *      12-Jun-2001, Alto: Revised to make city more resemble
 *                         Minas Tirith in preparation for siege.
 *      21-Nov-2005, Finwe: Added circle namme to short descr.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/*
 *      Prototypes:
 */
public string  describe();

/*
 *      Global variables:
 */
string  Area_Name,
        Circle,
        Extra_Line,
        Street_Name,
        Street_Type;
int     Activity,       /* 0 = low,  1 = normal,  2 = high */ 
        Street_Light,   /* 0 = none, 1 = not lit, 2 = lit  */
        Wealth;         /* 0 = poor, 1 = average, 2 = rich */

public void   set_areaname(string s)   { Area_Name = s; }
public void   set_circle(string s)     { Circle = s; }
public void   set_extraline(string s)  { Extra_Line = s; }
public void   set_streetname(string s) { Street_Name = s; }
public void   set_streettype(string s) { Street_Type = s; }
public void   set_activity(int i)      { Activity = i; }
public void   set_streetlight(int i)   { Street_Light = i; }
public void   set_wealth(int i)        { Wealth = i; }

public void
create_street()
{
}

nomask void
create_gondor()
{
    object  clock = find_object(CLOCK);
    int     war = clock->query_war();

    create_street();

//    set_short(LANG_ADDART(Street_Type) + " in Minas Tirith");
//    set_short(LANG_ADDART(Street_Type) + " in the " + Circle + " circle in Minas Tirith");
    set_short("On " + Street_Name + " in the " + lower_case(Circle) + " circle in Minas Tirith");

    set_long(describe);

    if (!item_id(Street_Type))
        add_item(Street_Type, "The " + Street_Type + " is made of "
            + "square stones.\n"); 

    switch (Wealth) /* changed to reflect different architecture - Alto */
    {
    case 0:
        add_item(({"house", "houses"}), BSN(
            "The houses on this " + Street_Type + " are for the most part "
            + "constructed with a single floor and flat roof. Many of them "
            + "stand vacant."));
        add_item(({"roof", "roofs"}), "They are on top of the houses.\n");
        break;
    case 1:
        add_item(({"house", "houses"}), BSN(
            "The houses on this " + Street_Type + " are a mixture of single "
            + "and double-storied structures. All are constructed from "
            + "native white stone capped with red ceramic tiles. Although "
            + "once a thriving neighbourhood, many of the houses are now "
            + "vacant."));
        add_item(({"stone", "native stone", "tiles", "red tiles", 
            "ceramic tiles"}), "The houses are made from stone quarried "
            + "from the foothills of Mount Mindolluin. Many of them are "
            + "capped with curved red ceramic tiles made by local "
            + "craftsmen.\n");
        break;
    case 2:
        add_item(({"house", "houses"}), BSN(
            "The houses on this " + Street_Type + " are tall and constructed "
            + "with multiple floors. Many have small courtyards before them, "
            + "in which beautiful flower gardens grow. Some of the gardens, "
            + "however, look abandoned, as do the houses beyond them."));
        add_item(({"courtyard", "courtyards", "garden", "gardens"}), "Lining "
            + "the street are a number of lovely flower gardens, from which "
            + "comforting fragrances arise. In the glory of the city, these "
            + "must have been breathtakingly beautiful. Now, however, many "
            + "of the gardens have been left untended.\n");
        break;
    }
    if ((Street_Light > 0) && !item_id("lamps"))
        add_item(({"lights", "street lamp", "street lamps", "lamps", }), 
        "The streets are lit by oil lamps hanging from the houses.\n");
}

public string
describe()
{
    int     i;
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            long_descf,
            moon;

    long_descf = Street_Name + " in the " + Area_Name + " parts of the "
      + Circle + " circle of Minas Tirith.";

    switch (time)
    {
    case "night":
    case "evening":
    case "early morning":
        // Calc light at night
        long_descf += " The " + Street_Type; 
        if (Street_Light == 2)
            long_descf += " is lit by a warm light from the lit "+
			  "street lamps.";
        else if ((moon = clock->query_moon()) == "dark")
        {
            long_descf += " lies in darkness,";
            if (Street_Light == 0)
                long_descf += " as there are no street lamps in this "+
			      "part of the city.";
            else
                long_descf += " as the street lamps have not been lit yet.";
        }
        else
            long_descf += " looks gloomy in the silvery light from the "
              + moon+" moon.";
        break;
    }
    // Calc activity : Early morning, daytime, evening, night
    switch (time)
    {
    case "early morning":
        switch (Activity)
        {
        case 0:
            long_descf += " There is nobody in the " + Street_Type
              + " but from the houses you hear the sounds of rattling pans "
              + "and people shouting. All unmistakable signs that the city "
              + "is awakening to a new day.";
            break;
        case 1:
            long_descf += " There are a few people in the " + Street_Type
              + ", mostly guards of the night watch near the end of their "
              + "patrols.";
            break;
        default:
            long_descf += " There are a number of people moving about the "
              + Street_Type + ". Shops are opening for the day, and guards "
              + "of the day watch are relieving their weary comrades of "
              + "the night patrol.";
            break;
        }
        break;
    case "morning":
    case "noon":
    case "afternoon":
        switch (Activity)
        {
        case 0:
            long_descf += " There are a few people in the " + Street_Type
              + ", but it is mostly quiet. Every now and then a citizen "
              + "may pass by on some unknown errand.";
            break;
        case 1:
            long_descf += " There are some people in the " + Street_Type
              + ". Citizens come and go on their way to other parts of the "
              + "city, or to visit the few shops here. Most walk with "
              + "eyes downcast, although now and then someone will look "
              + "nervously at the eastern sky.";
            break;
        default:
            long_descf += " The " + Street_Type + " is relatively busy. "
              + "Shops, inns and other businesses are open, and everybody "
              + "is busy with various errands. Mules and wagons "
              + "pulled by oxen rumble through the center of the "
              + Street_Type + ", and city guards keep a careful "
              + "watch.";
            break;
        }
        break;
    case "evening":
        switch (Activity)
        {
        case 0:
            long_descf += " Citizens are returning to their homes after "
              + "a long day of work, and the " + Street_Type
              + " is slowly emptying."; 
            break;
        case 1:
            long_descf += " There are a few people in the " + Street_Type
              + ". Most of them are on their way home, while the few shops "
              + "are closing up for the night.";
            break;
        default:
            long_descf += " There are still many citizens in the " + Street_Type
              + ". Most are finishing their errands, but the "
              + "shopkeepers are closing up for the night. The inns and pubs "
              + "are still open, but you do not hear the sounds of laughter and "
              + "music one would expect from such places.";
            break;
        }
        break;
    default:
        switch (Activity)
        {
        case 0:
            long_descf += " The " + Street_Type + " lies empty. The houses "
              + "are dark and empty with no signs of life.";
            break;
        case 1:
            long_descf += " The " + Street_Type + " is quiet with a few "
              + "citizens moving quietly by. The few shops are closed, and "
              + "the houses are dark and quiet.";
            break;
        default:
            long_descf += " There are still some people in the "
              + Street_Type + ". The light shines from bars and taverns, but "
              + "there is little laughter or song. Now and then a city guard "
              + "walks by on his rounds.";
            break;
        }
        break;
    }
    if (strlen(Extra_Line))
        long_descf += " " + Extra_Line;
    return BSN(long_descf); 
}

public string
query_circle()
{
    return Circle;
}

public int
block_npc() 
{
    if (TP->query_npc()) 
	return 1;
    return 0;
}
