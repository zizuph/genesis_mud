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
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "path12","north",0);
    add_exit(ROOM + "path14","southeast",0);

    add_item(({"lowlands","hills","hills of blood","hilly terrain"}),
       "To your southeast the mountain path opens up to the " +
       "base of the mountain ranges where the lowlands break out into " +
       "hilly terrain known as the Hills of Blood - named due to being " +
       "the location of particularly vicious battles during the " +
       "Dwarfgate War.\n"); 
    add_item(({"desolated lands","plains of dergoth","dergoth","plains"}),
       "Beyond the Hills of Blood is the desolated plains of Dergoth. " +
       "Here is where the thousands of participants in the Dwarfgate " +
       "War met their end over three hundred years ago in a magical " +
       "blast that destroyed both armies and the land for miles. " +
       "Still inhospitable, the plains are rumoured to be haunted by " +
       "the spirits of the warriors slain.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_snow");
    add_item(({"path","road","rugged pass","rugged path","trail"}),
      "@@add_item_path");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return short_mountain_desc() + ", overlooking the Hills of Blood";
}

string
long_descr()
{
    return long_mountain_desc() + "The trail begins to slope downwards " +
        "to the southeast as the path through the mountains open before " +
        "you to the lowlands know as the Hills of Blood. Beyond the " +
        "hills you can make out the desolated lands known as the Plains " +
        "of Dergoth.\n";
}
