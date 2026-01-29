#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

#define MINSTREL "/d/Terel/guilds/minstrels/living/travelling_repairer2"

object minstrel;

void
reset_kalaman_room()
{
    if(!objectp(minstrel))
    {
        minstrel = clone_object(MINSTREL);
        minstrel->move(TO, 1);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("large dirt courtyard full of wagon tracks");

    add_item(({"courtyard","dirt courtyard","large dirt courtyard"}),
      "You stand in a large dirt courtyard, used by merchant wagons " +
      "coming to trade their wares within the city of Kalaman.\n");
    add_item(({"kalaman","city"}),
      "To your east you can see the high walls of the city of Kalaman.\n");
    add_item(({"wooden structure","structure","building"}),
      "A large wooden building stands before you to the north. This is " +
      "where merchants rest and their guards wash away trail dust with " +
      "cheap ale!\n");
    add_item(({"wooden palisade","palisade"}),
      "A wooden palisade surrounds the building in the middle of the yard. " +
      "While likely to stop goblin raids, you doubt it would hold back any " +
      "serious attempts to breach it.\n");
    add_item(({"tracks","wagon tracks"}),
      "Wagon tracks run chaotically throughout the yard, although none of " +
      "them seem to be recently made.\n");

    add_exit("/d/Ansalon/kalaman/caravan/inside","in",0);
    add_exit("/d/Krynn/solamn/eplains/rooms/eplain-24-2-K", "northeast", 0);

    reset_kalaman_room();
}



string
long_descr()
{
    return "You stand in a large dirt courtyard to the west of the " +
    "city of Kalaman. Before you is a large wooden structure, used " +
    "by merchant wagons as a watering station for their horses and a " +
    "cheap resting point for their guards. A wooden palisade surrounds " +
    "the structure, offering it a little protection. At present the yard is " +
    "largely empty, probably due to the dangers merchants face from " +
    "Lord Soth's undead minion when coming to Kalaman. " +
     tod_descr1() + "\n";
}
