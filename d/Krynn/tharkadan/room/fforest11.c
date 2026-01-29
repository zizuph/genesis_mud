#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","eversnow", 
                                           "conifforest", }));
object ogre;

void
reset_tharkadan_room()
{
    set_searched(0);

    if(!objectp(ogre))
    {
       ogre = clone_object(LIVING + "ogre");
       ogre->arm_me();
       ogre->move(TO, 1);
    }
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "fforest8","west",0);
    add_exit(ROOM + "fforest9","northwest",0);
    add_exit(ROOM + "fforest12","southeast",0);
    add_exit(ROOM + "fforest7","southwest",0);
    add_exit(ROOM + "fforest10","south",0);

    add_item(({"woods","mountain woods","forest","vale","trees",
        "fallen forest","valley"}),
        "You stand within the depths of an alpine forest where aspen, " +
        "fir and lodgepole pine form a secluded mountain woods known as " +
        "'the Fallen Forest'.\n");
    add_item(({"aspen","aspen trees"}),"Native to cold regions with " +
        "cool summers, aspen trees grow in large numbers in the woods " +
        "to your east.\n");
    add_item(({"fir","fir trees"}),"Growing throughout the Tharkadan " +
        "Range are large fir trees, evergreen coniferous trees common " +
        "to mountainous regions.\n");
    add_item(({"lodgepole pine","lodgepole pine trees","pine",
        "pine trees"}), "A thin and narrow-crowned tree also known as " +
        "the twisted pine that is common in alpine regions such as the " +
        "Tharkadan Range.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_forest_snow");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return short_forest_desc();
}

string
long_descr()
{
    return long_forest_desc()+"\n";
}

