/* 
   created by Vitwitch 08/2021 
   based closely on work of :
   Aridor (1993) /d/Krynn/solamn/vin_mount/room/road3
   Arman (2020) /d/Krynn/tharkadan/room/ledge6
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit "/d/Krynn/solamn/vin_mount/room/room_base";
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills"}));
static int gTiredness = 15;
static int gClimbSkillMin;
static int gSkeletonHere = 0;

/* FUNCTIONS */

public int
do_smell( string arg )
{
    this_player()->catch_mesg("Fresh air chills the nose into numbness.\n");
    return 1;
}

string
season_descr()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
        str = "Greenery dotted with brighter colour fills the meadow, " +
            "inviting a closer look.";
        break;
    case AUTUMN:
    case WINTER:
        str = "Snow has dusted the vegetation all about, cloaking "+
            "the meadow but not preventing a closer look.";
        break;
    }
    return str;
}

string
short_descr()
{
    return "A rough climbing route up and over the mountains";
}

string
long_descr()
{
    string str = "Only a climber's " +
        "experienced eye can trace out the route upward and downward. " +
        "Climbers can read the jumble of fissured cliff faces and ridge " +
        "lines like a map of high roads and byways.\n\n" +
        "An alpine meadow spreads out around you and offers the chance " +
        "for you to take a breather. " + season_descr();

    if ( gSkeletonHere )
        str += " The bleached bones of an old dismembered "+
              "skeleton lie here among the rocks.";

    return str + "\n";
}

void
set_skeleton_here()
{
    gSkeletonHere = 1;
    return;
}

void
set_climb_skill_min( int val )
{
    gClimbSkillMin = val;
    return;
}

int
vin_herb_trail_tiredness()
{
    return gTiredness;
}

int
climb_up()
{
    if( this_player()->query_skill(SS_CLIMB) < gClimbSkillMin )
    {
        write("You look at the faint route marks before you. You " +
          "realise that you do not have the ability to climb any further.\n");
        say(QCTNAME(this_player()) +
          " looks at the upward route through the mountains," +
          " but makes no move to climb higher.\n");
        return 1;
    }
    return 0;
}

void
create_vin_herb_trail_room()
{
}

void
reset_vin_mount_room()
{
    set_searched(0);
}

void
create_vin_mount_room()
{

    OUTSIDE;

    create_vin_herb_trail_room();

    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item("weather","Casting an eye to the skies in all directions, "+
              "things seem calm enough to you for now.\n");

    add_item(({"route","climbing route"}),
	     "The climbing route is faint at best -- seldom followed " +
             "and only discernible to the skilled eye.\n");

    add_item(({"mountains","mountain"}),
	     "These are high mountains indeed. Only skilled climbers " +
             "are able to find their way between the jagged peaks " +
             "from one side of the range to the other. Alpine meadows " +
             "offer a welcome respite from the sheerness of these " +
             "high places.\n");

    add_item(({"cliffs","cliff","cliff faces","ridge","ridges","ridge lines"}),
	     "Stark steep cliffs and ridge lines standing proud, " +
             "seem entirely unbowed by erosion. Fissures and outcrops " +
             "offer scant purchase for the hands and " +
             "feet of mortals who dare to pass this way.\n");

    add_item(({"greenery","meadow","alpine meadow","ground"}),
	     "Herbiage and other green growing things cling to life " +
             "in the many hard-to-reach alpine meadows that exist " +
	     "along this climbing route.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "ground", }), 3);
}

