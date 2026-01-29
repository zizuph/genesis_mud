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
        "canyon.\n");
    add_item(({"stream","crystal lake","lake","glacier"}), "To your " +
        "north a stream flows from Crystal Lake down a glacier into " +
        "the canyon below. It follows the canyon south.\n");

    add_cmd_item(({"precipice","down precipice","canyon","down canyon",
        "down"}), "climb", "There is nowhere along the edge of the " +
        "precipice for you to climb down into the canyon from here.\n");

    add_exit(ROOM + "path23", "north", 0);
    add_exit(ROOM + "path25", "southwest", 0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "on the edge of Dirken Canyon in the Tharkadan Mountains";
}

string
long_descr()
{
    return "You stand on the edge of a precipice overlooking a steep " +
        "canyon running through the Tharkadan Mountain Range. A trail " +
        "runs along the edge of the canyon to your north and " +
        "southwest.\n";
}