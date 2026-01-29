#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));

void
reset_tharkadan_room()
{
    set_searched(random(2));
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_snow");
    add_item(({"path","trail","pass","valley pass","highlands"}),
        "You stand on the edge of a precipice that drops into a steep " +
        "canyon on a trail running through the Tharkadan Mountain " +
        "Range.\n");
    add_item(({"canyon","dirken canyon","precipice","glacier","edge",
        "steep canyon"}), "You stand on the edge of a precipice that " +
        "drops into a steep canyon known as Dirken Canyon. A stream " +
        "flowing from Crystal Lake to your north runs through the " +
        "canyon. You notice the remains of a massive stone bridge lie " +
        "on the canyon floor.\n");
    add_item(({"remains","canyon floor"}), "On the canyon floor lie " +
        "the remains of a massive stone bridge - clearly a casualty " +
        "of the Cataclysm long ago.\n");
    add_item(({"stream","crystal lake","lake","glacier"}), "To your " +
        "north a stream flows from Crystal Lake down a glacier into " +
        "the canyon below. It follows the canyon south.\n");
    add_item(({"bridge","bridgehead","stone bridgehead",
        "massive stone bridgehead","stone bridge"}), "To your west " +
        "rise two ancient stone towers that make up the head of a " +
        "massive dwarven bridge. Built long ago to allow passage " +
        "across Dirken Canyon, this bridge provided access to the " +
        "western side of the Tharkadan Mountain Range. You notice " +
        "that such passage would not have occurred for a long time, " +
        "with most of the bridge now lying on the floor of the canyon - " +
        "clearly a casualty of the Cataclysm.\n");
    add_item(({"stone towers","towers","twin stone towers"}), "Once " +
        "formidable towers forming the head of a massive stone bridge " +
        "crossing Dirken Canyon, these two towers are now derelict and " +
        "neglected... the bridge they once guarded having fallen into " +
        "the canyon around the time of the Cataclysm.\n");

    add_cmd_item(({"precipice","down precipice","canyon","down canyon",
        "down"}), "climb", "There is nowhere along the edge of the " +
        "precipice for you to climb down into the canyon from here.\n");
    add_cmd_item(({"towers","tower"}), "enter", "The two towers of the " +
        "bridgehead are derelict, having collapsed in on themselves " +
        "and filled with rubble. You cannot enter them.\n");
    add_cmd_item(({"towers","tower"}), "climb", "The two towers of the " +
        "bridgehead are derelict, having collapsed in on themselves " +
        "and filled with rubble. You cannot climb them.\n");

    add_exit(ROOM + "path24","northeast",0);
    add_exit(ROOM + "xxx","west","@@no_go");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "before a massive stone bridgehead on the edge of Dirken " +
        "Canyon";
}

string
long_descr()
{
    return "You stand before a massive stone bridgehead on the edge of " +
        "a steep canyon running through the Tharkadan Mountain Range. " +
        "A trail runs along the edge of the canyon to your northeast " +
        "and between the twin stone towers of the bridgehead to your " +
        "west.\n";
}

int
no_go()
{
    write("The massive stone bridge long ago fell into Dirken Canyon, " +
        "leaving behind two neglected towers that made up the " +
        "bridgehead, and making passage west across the canyon here " +
        "impossible.\n");
    say(QCTNAME(TP)+ " steps between the two towers of the bridgehead " +
        "and briefly looks down into the canyon before returning.\n");
    return 1;
}