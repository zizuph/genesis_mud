#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

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

    add_exit(ROOM + "vale7","southeast",0);
    add_exit(ROOM + "vale11","north",0);
    add_exit(ROOM + "vale6","northeast",0);
    add_exit(ROOM + "vale9","south",0);     
    add_exit(ROOM + "vale12","west",0);

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
    add_item(({"towering peak","peak","ancient volcano","volcano","foot"}),
        "Before you rises the steep walls of a towering peak, likely " +
        "once an ancient volcano, standing alone amongst a sea of aspen " +
        "and fir trees.\n");
    add_item(({"walls","steep walls","icy walls"}), "Steep, icy walls " +
        "of a towering peak rise high above you. You notice a ledge " +
        "approximately fifteen meters up the wall that seems to be the " +
        "start of a narrow path around the side of the peak.\n");
    add_item(({"ledge","wall","narrow path","path"}), "Approximately " +
        "fifteen meters up the side of the wall before you is a ledge " +
        "that seems to be the beginning of a path that winds around the " +
        "side of the peak. Getting to that ledge from here though looks " +
        "very difficult.\n");

    add_cmd_item(({"walls","peak","towering peak","wall","steep walls",
        "to ledge","up","up to the ledge","up the ledge","up ledge",
        "ledge"}),
        "climb","@@climb_walls");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

int
filter_tool(object obj)
{
    if (obj->id("_20_meter_rope"))
        return 1;
    else 
        return 0;
}

string
climb_walls()
{

    string fail_str = "The steep walls of the peak are too icy to " +
        "climb without assistance. A rope of appropriate length with " +
        "a grapple would probably provide you with the purchase you " +
        "need to climb up to the ledge.\n";

    if(TP->query_tool(-1))
    {
        object * rope = filter(TP->query_tool(-1), filter_tool);

        if(!sizeof(rope))
	    return fail_str;

        if(!rope[0]->query_held())
            return "You need to be holding the rope to attempt to " +
                "climb the cliff.\n";

        if(!rope[0]->rope_has_grapple())
            return "Without a grapple attached you won't be able to " +
                "get the rope stabilised on the ledge.\n";

        if(TP->query_stat(SS_STR) < 65)
        {
            write("You swing the " +rope[0]->short()+ " furiously and " +
                "hurl the grapple with all your strength up towards " +
                "the ledge, but it falls well short. You are not " +
                "strong enough to throw the grapple up to the ledge.\n");
            say(QCTNAME(TP) + " furiously swings " +HIS(TP)+ " " +
                rope[0]->short()+ " around before hurling its grapple " +
                "up the wall of the peak. It doesn't travel very far " +
                "before plummeting down to the ground.\n");
            return "";
        }

        if(!TP->query_skill(SS_WEP_MISSILE))
        {
            write("You swing the " +rope[0]->short()+ " around your " +
                "head and hurl the grapple with all your strength, but " +
                "your accuracy was off and it missed the edge of the " +
                "ledge. You'll need more skill with throwing items " +
                "before having any chance of getting the grapple to hit " +
                "the ledge!\n");
            say(QCTNAME(TP) + " swings a " +rope[0]->short()+ " around " +
                HIS(TP)+ " head before hurling it up the wall of the " +
                "peak. It doesn't connect with anything and tumbles " +
                "back down to the ground.\n");
            return "";
        }

        if(TP->query_skill(SS_WEP_MISSILE) < (random(50) + 10))
        {
            write("You swing the " +rope[0]->short()+ " around your " +
                "head and hurl the grapple with all your strength, but " +
                "your accuracy was off and it missed the edge of the " +
                "ledge.\n");
            say(QCTNAME(TP) + " swings a " +rope[0]->short()+ " around " +
                HIS(TP)+ " head before hurling it up the wall of the " +
                "peak. It doesn't connect with anything and tumbles " +
                "back down to the ground.\n");
            return "";
        }

        write("You swing the " +rope[0]->short()+ " around your head " +
            "and hurl it with all your strength, accurately landing " +
            "the grapple on the edge of the ledge.\nYou quickly secure " +
            "it for climbing, and scale the steep wall of the cliff to " +
            "the ledge.\n");
        say(QCTNAME(TP) + " swings a " +rope[0]->short()+ " around " +
            HIS(TP)+ " head before hurling it up the wall of the peak. " +
            "It accurately lands on the edge of a ledge, firmly " +
            "secured.\n");
        TP->move_living("up, scaling the steep wall of the peak and " +
            "disappearing over a ledge", ROOM + "ledge1", 1, 0);
        return "";
    }

    return fail_str;
}

string
short_descr()
{
    return "at the foot of a towering peak in an isolated valley";
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
long_descr()
{
    return "You stand at the foot of a towering peak in the centre of " +
       "a wide vale rimmed by " +mountain_desc()+
       "Aspens and firs grow in abundance here and the vale is somewhat " +
       "protected from the wind and cold.\n";
}

