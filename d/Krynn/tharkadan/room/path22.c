#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
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
    add_item(({"path","trail","pass","valley pass"}),
      "You stand on a trail running through the Tharkadan Mountain " +
      "Range. Snow-covered peaks and ridgelines rise around you, " +
      "while further to your southwest you can see the highlands " +
      "end in a precipice that drops into a steep canyon.\n");
    add_item(({"canyon","dirken canyon","precipice","glacier"}),
      "To your southwest the highlands end in a precipice tha drops " +
      "into a steep canyon known as Dirken Canyon.\n");

    add_exit(ROOM + "path21","northwest",0);
    add_exit(ROOM + "path23","southwest",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "a valley pass in the Tharkadan Mountains";
}

string
long_descr()
{
    return long_mountain_desc()+ "To your southwest the trail leads " +
       "to a precipice that drops into a steep canyon.\n";
}
