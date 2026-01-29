/*
 * Base file for roads and gates in Bree
 * Finwe, June 2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";
inherit "/d/Shire/bree/base_common";
 
// orchard vars
int apples;

void create_road_room() {}

// roads inside bree
public void
create_area_room()
{

    set_area("in");
    set_areaname("Bree");
    set_land("Eriador");
    set_areatype(0);
    set_areadesc("road");
    add_item(({"road", "ground"}),
        "The road is made hard packed dirt. Wagon ruts run down " +
        "the middle of the road.\n");
    add_item(({"ruts", "wagon ruts"}),
        "The wagon ruts are depressions in the road made from " +
        "years of carts running up and down the road.\n");
    add_item("depressions",
        "They are ruts in the road, formed by years of carts driving " +
        "up and down the road.\n");
    add_item("grass",
        "The grass is green but trampled in places along the road. " +
        "This is probably from the constant travel along the road.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
    
    create_road_room();
    set_add_sky();
    add_std_herbs("trees");
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
init()
{   
    ::init();
}



int test_size()
{

 if (this_player()->query_wiz_level()) return 0;

    switch (TP->query_race())
    {
    case "human":
    case "elf":
    case "dwarf":
    case "goblin":
    case "troll":
/*
        write("You quickly find out that you are too big for the"
            + " little hole!\n");
        say(QCTNAME(TP) + " tries to enter the hobbit " +
            "hole, but is too big to do so.\n", TP);
        return 1;
*/      write("You duck as you enter the little hobbit hole.\n");
        say(QCTNAME(TP) + " ducks as "+HE_SHE(TP)+" enters the little " +
            "hobbit hole.\n",TP);
        break;
    }

    return 0;
}


// Orchard functions
int
sniff_air(string str)
{
    if((str == "air"))
    {
        write("You take a deep cleansing breath, full of the sweet " +
            "smell of apple blossoms.\n");
        say(QCTNAME(TP) + " takes a deep breath and " +
            "sighs contentedly.\n");
        return 1;
    }

    if((str == "blossom") || (str == "apple blossom"))
    {
        write("You take a deep breath filled with the sweet smell " +
            "of apple blossom.\n");
        say(QCTNAME(TP) + " sniffs the apple blossom and sighs contentedly.\n");
        return 1;
   }
return 1;
}

int
get_apple(string str)
{
    object fruit;
    
    if((str == "apple") || (str == "apples") || (str == "fruit"))
    {
        if (apples == 3)
        {
            write("It looks like all apples on the lower branches " +
                "have been picked.\n");
            return 1;
        }
          setuid();
          seteuid(getuid());
          fruit = clone_object(FOOD_DIR + "apple");
          fruit->move(this_player(), 1);

        write("You reach for an apple on a lower branch and " +
            "pick a large, red, juicy one.\n");
        say(QCTNAME(TP) + " picks an apple from the tree.\n");
        apples = apples + 1;
        return 1;
    }
    return 0;
}
