#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit CITY_OUT;
#include "/d/Krynn/common/herbsearch.h";

#define KRHERB "/d/Krynn/common/herbs/"
#define H1 "/d/Shire/common/herbs/pawnrose"
#define H2 "/d/Shire/common/herbs/huckleberry"
#define H3 "/d/Gondor/common/herbs/foxglove"
#define H4 KRHERB + "saskatoon"

object door;

void
reset_kalaman_room()
{
    set_searched(random(2));
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("A private garden in Kalaman");

    add_item(({"stone path","path"}),
      "A neat path, made of small brown stones, weaves its way around the garden.\n");

    add_item(({"great trees","trees","tree"}),
      "Trees of great size and beauty fill the garden. They have been well taken " +
      "care of and are obviously the pride of some local gardener.\n");
    add_item(({"flowers","flower"}),
      "Flowers of all kinds fill the garden.\n");

    seteuid(getuid(TO));
    set_search_places(({"garden","park","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

    add_exit(CITY + "g1","northeast",0);
    add_exit(CITY + "g2","east",0);
    add_exit(CITY + "g5","southeast",0);

    add_cmd_item(({"fence","gate"}),"climb","@@climb_fence");

    door = clone_object(KOBJ + "garden_gate2a");
    door->move(TO);
    reset_kalaman_room();
}

string
long_descr()
{
    return "You find yourself standing in a beautiful garden in the middle " +
    "of Kalaman. " +season_garden()+ "A stone path leads away from " +
    "here to your " +
    "northeast, east and southeast." +
    "\n";
}

string
climb_fence()
{
    if(TP->query_skill(SS_CLIMB) < 20)
    {
	write("You try and climb the fence, but your " +
	  "climbing ability really does suck. Guess you'll " +
	  "have to get used to the grass on this side of the " +
	  "fence.\n");
	say(QCTNAME(TP) + " pitifully tries to climb the fence " +
	  "but fails miserably.\n");
	return "";
    }
    write("You easily scale the fence to the " +
      "street on the other side.\n");
    say(QCTNAME(TP) + " climbs over the high fence.\n");
    TP->move_living("M",CITY + "r9",1,0);
    return "";
}
