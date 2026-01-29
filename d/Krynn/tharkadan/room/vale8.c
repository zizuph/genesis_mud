#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

#define HAS_SEARCHED   "_has_found_tharkadan_track"

int see_trail = (25 + random(25));
int found_trail;

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",
    "conifforest",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "vale4","northeast",0);     
    add_exit(ROOM + "vale7","north",0);
    add_exit(ROOM + "vale9","northwest",0);
    add_invis_exit(ROOM + "path17", "southeast", "@@go_southeast");

    add_item(({"valley","vale","wide vale","protected vale",
        "isolated valley","floor","centre"}),
        "You stand within a wide vale rimmed by mountains. Aspens and " +
        "firs grow in abundance here, although the most notable feature " +
        "of this valley is the towering peak that rises from its " +
        "centre.\n");
    add_item(({"aspen","aspen trees","aspens"}), "Native to cold " +
        "regions with cool summers, aspen trees grow in large numbers " +
        "here.\n");
    add_item(({"fir","fir trees","firs"}), "Growing throughout the " +
        "Tharkadan Range are large fir trees, evergreen coniferous " +
        "trees common to mountainous regions.\n");
    add_item(({"trees","tree"}),"Aspens and firs grow in abundance " +
        "here and the vale.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_snow");
    add_item(({"towering peak","peak","ancient volcano","volcano"}),
        "In the centre of the valley rises a towering peak, standing " +
        "alone amongst a sea of aspen and fir trees.\n");
    add_item(({"trail","passage","track"}),"@@add_item_trail");

    add_search(({"here","vale","ground"}), 5, "search_track", 1); 
    add_cmd_item(({"trail","the trail"}), "reveal", "@@reveal_trail");   

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "protected vale before a towering peak";
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
        case SPRING:
        case SUMMER:
	    str = "mountains. ";
	    break;
        case AUTUMN:
        case WINTER:
	    str = "ice-capped mountains. ";
	    break;
    }
    return str;
}

string
add_item_trail()
{
   if((TP->query_skill(SS_TRACKING) > see_trail) || 
       TP->query_prop(HAS_SEARCHED) ||
       TP->query_guild_name_lay() == "Holy Order of the Stars")
       return "To your southeast you detect a trail made recently by " +
           "the passage of a number of people leading out of the vale " +
           "through the mountains. The footprints look human, although " +
           "you notice some older tracks that look like the heavy " +
           "boots of dwarves. If you wanted to, you could <reveal> " +
           "the trail to others in your team.\n";
   else
       return "Examine what?\n";
}

string
track_long()
{
    if((TP->query_skill(SS_TRACKING) > see_trail) || 
        TP->query_prop(HAS_SEARCHED) ||
        TP->query_guild_name_lay() == "Holy Order of the Stars")
        return "To your southeast you detect a trail made recently by " +
            "the passage of a number of people leading out of the vale " +
            "through the mountains.";
   else
     return "";
}

string
long_descr()
{
    return "You stand in a wide vale rimmed by " +mountain_desc()+
       "Aspens and firs grow in abundance here and the vale is somewhat " +
       "protected from the wind and cold. Rising from the the floor of " +
       "this isolated valley like a lone tree on a prairie is a " +
       "towering peak, possibly an ancient volcano. " +track_long()+ "\n";
}

string
reveal_trail()
{
    if((TP->query_skill(SS_TRACKING) > see_trail) || 
        TP->query_prop(HAS_SEARCHED) ||
        TP->query_guild_name_lay() == "Holy Order of the Stars")
    {
        object * team = TP->query_team_others();
        if (sizeof(team) > 0)
        {
             write("You reveal the trail southeast to everyone in your " +
                 "team.\n");
             say(QCTNAME(TP)+ " reveals a trail heading southeast to " +
                 "you.\n");

             foreach(object teammates: team)
             {
                 teammates->add_prop(HAS_SEARCHED, 1);
             }
             return "";
        }

        write("You have no teammates to reveal the trail to.\n");
        return "";
    }

    return "What?\n";
}

int
go_southeast()
{
    if((TP->query_skill(SS_TRACKING) > see_trail) || 
        TP->query_prop(HAS_SEARCHED) ||
        TP->query_guild_name_lay() == "Holy Order of the Stars")
    {
        write("You follow the trail southeast...\n");
        return 0;
    }

    write("There is no obvious exit southeast.\n");
    return 1;
}

string
search_track(object searcher, string what)
{
    int tracking_skill = searcher->query_skill(SS_TRACKING);

    if (CAN_SEE_IN_ROOM(searcher))
    {
        if (tracking_skill <  random(75))
	{
            if(tracking_skill < 40)
                return ("Your search reveals nothing special. Although " +
                    "being quite a poor tracker it is likely you " +
                    "missed something.\n");
            else
		return ("Your search reveals nothing special.\n");
	    }

	    searcher->add_prop(HAS_SEARCHED, 1);
	    return ("You discover a trail made recently by the passage " +
                "of a number of people leading southeast out of the " +
                "vale through the mountains.\n");
	    
    }
   return 0;
}
