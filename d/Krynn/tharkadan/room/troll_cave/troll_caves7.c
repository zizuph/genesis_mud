#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"
#include <money.h>

inherit CAVERNS_BASE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave",}));
object troll, troll2, troll_boss;
int treasure_unfound = 1;

void
reset_tharkadan_room()
{
    if(!objectp(troll))
    {
        troll = clone_object(LIVING + "cave_troll");
        troll->move(TO, 1);
    }

    if(!objectp(troll2))
    {
        troll2 = clone_object(LIVING + "cave_troll");
        troll2->move(TO, 1);
    }

    if(!objectp(troll_boss))
    {
        troll_boss = clone_object(LIVING + "two_headed_cave_troll");
        troll_boss->move(TO, 1);
    }

    treasure_unfound = 1;

    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(TROLL_CAVES + "troll_caves6","north",0);
 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"narrow cave","cave","cave network","network"}),
        "You stand within a narrow cave network that runs through " +
        "the Tharkadan mountain range. The roof here is quite low " +
        "making you feel claustrophobic, and there is a rank " +
        "animalistic smell that makes you think that this cave network " +
        "is occupied.\n");
    add_item(({"stalagmites","thin stalagmites", "low roof","roof"}),
        "The roof here is covered with thin stalagmites, reminding you " +
        "of milky white icicles or finger nails reaching down for you.\n");
    add_item(({"remains","skeletal remains","pile","great pile",
        "kender corpses", "great pile of skeletal remains","dwarf corpses",
        "human corpses","corpses","human corpse","kender corpse",
        "dwarf corpse"}), "In the middle of the cave is a putrid pile " +
        "of skeletal remains. You can make out human, dwarf, and even " +
        "kender corpses that have been gnawed and in various stages " +
        "of decay.\n");

    seteuid(getuid(TO));

    add_search(({"remains","skeletal remains","pile","great pile",
        "kender corpses", "great pile of skeletal remains","dwarf corpses",
        "human corpses","corpses","human corpse","kender corpse",
        "dwarf corpse"}), 5,"search_remains", 1);

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "a narrow cave within the Tharkadan mountain range.\n" +
        "A great pile of skeletal remains";
}

string
long_descr()
{
    return "You stand within a narrow cave network that runs through " +
        "the Tharkadan mountain range. Thin stalagmites hang around " +
        "you like icicles from the low roof of the cave, which " +
        "continues into darkness to your north. On the ground " +
        "in the middle of the cave is a pile of skeletal remains of " +
        "the unfortunate victims of the cave trolls.\nA great pile " +
        "of skeletal remains.\n";
}

string
search_remains(object searcher, string what)
{
    if(objectp(troll) || objectp(troll2) || objectp(troll_boss))
    {
           return "You can't get close enough to the remains to search " +
               "them properly with the trolls prowling around!\n";
    }

    if (CAN_SEE_IN_ROOM(searcher) && treasure_unfound)
      {
            object box, gem, wand, disk, coins;

            box = clone_object(TOBJ + "magical_strongbox");
            gem = clone_object("/d/Genesis/gems/obj/diamond_black");
            wand = clone_object(TOBJ + "light_wand");
            disk = clone_object(TOBJ + "multi_disk");
            coins = MONEY_MAKE_GC(12 + random(12));

            box->move(TP, 1);
            gem->move(box, 1);
            wand->move(box, 1);
            disk->move(box, 1);
            coins->move(box, 1);

            treasure_unfound = 0;

            say(QCTNAME(TP) + " searches through the pile of skeletal " +
                   "remains, and finds a gem-encrusted strongbox!\n");	    
	    return ("You search through the pile of skeletal remains, " +
                   "and finds a gem-encrusted strongbox!\n");	    
    }

    return "You search through the pile of skeletal remains but find " +
        "nothing useable or of value. It looks like someone has already " +
        "gone through the remains searching for something!\n";
}