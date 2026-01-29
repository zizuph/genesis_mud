/*
 * /d/Shire/cypress/guilds/wrunner/rooms/garden
 * Garden in Wild Elves Guild
 * By Finwe, July 2001
 *
 * Added a fountain to drink water, and general herbs
 * -- Finwe, Nov 2007
 *
 * 2007/11/03 Last update
 * 2011/07/20 Lavellan - Removed command_driver inherit.
 */

#include "../wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Shire/std/room/room_tell";
//inherit "/cmd/std/command_driver";
inherit AREA_ROOM;
inherit "/d/Gondor/common/lib/herbsearch.c";
inherit "/d/Sparkle/area/faerie/lib/base_water";

// fruits for trees:
#define FRUIT    ({"fig", "mango", "peach", "pear", "starfruit", })
#define MAX_FRUIT     5         /* maximum num of fruits in each room */
#define FRUIT_DIR   "/d/Sparkle/guilds/arcane/fruit/"

static private string *fruits = FRUIT;
int fruit;
int fruit_counter;


void
create_room()
{

    setuid();
    seteuid(getuid());

    set_short("An exquisite private garden");
    set_long("This is an exquisite private garden, shared only by the " +
        "Wild elves. Its peaceful surroundings offer a place of contemplation " +
        "and relaxation from the many problems the elves face. The garden " +
        "is full of many plants that are all expertly cared for. Tall " +
        "trees surround the garden, preventing intrusions or escapes. A " +
        "small spring bubbles up from the ground and flows into a " +
        "small pool.\n");

    add_item(({"plants", "plant"}),
        "The plants are numerous. Some are well known while " +
        "others are rare and probably not known to anyone but " +
        "the caretakers themselves. They are healthy and look " +
        "well tended.\n");
    add_item(({"flowers", "flower"}),
        "The flowers are all different shapes, sizes, and " +
        "colors. The many varieties of flowers create a " +
        "tapestry of color that grow throught the garden.\n");
    add_item(({"bushes","bush","shrubs", "shrub"}),
        "The bushes are of varying heights and perfectly " +
        "clipped. They add a bit of diversity to the garden, " +
        "growing among the flowers and trees. Some of the bushes " +
        "are in flower, adding to the color of the garden. The " +
        "bushes are clipped so as to resemble their natural " +
        "state and not to detract from the garden.\n");
    add_item(({"flowering shrubs", "flowering bushes",
            "flowering bush", "flowering shrub"}),
        "The flowering shrubs are different heights and sizes. " +
        "Some are in bloom with deep-throated, simple, or ornate " +
        "flowers as well as every imaginable color.\n");
    add_item(({"ancient trees"}),
        "The ancient trees appear to be the oldest living plant. " +
        "They are giant whose crowns seem hidden in the sky. " +
        "Their branches stretch out, shading everything beneath " +
        "them.\n");
    add_item(({"forest", "woods", "ancient forest", "ancient woods"}),
        "The ancient forest surrounds the garden. " +
        "Various trees of different ages grow in " +
        "the garden from young saplings to ancient trees. They " +
        "all look cared for and in perfect health.\n");
    add_item(({"saplings", "new trees", "young trees"}),
        "The saplings are recently planted. They look healthy " +
        "and perfect.\n");
    add_item(({"trees", "tree"}),
        "The trees of the garden are made up of many different " +
        "trees. The most common are beech, maple, and oak. Many " +
        "of them look ancient, as if they have been cared for by " +
        "the elves for many millenia.\n");
    add_item(({"ancient oak trees", "ancient oaks", "oak trees", "oak"}),
        "The ancient oak trees tower over everything in " +
        "the garden. Their branches are ancient and covered " +
        "with large, green, serrated leaves. Their trunks are " +
        "gray and white in color and very thick.\n");
    add_item(({"ancient beech trees", "ancient beech",
            "beech trees", "beech"}),
        "The trees are tall and ancient looking. They are " +
        "covered with a multitude of green leaves that rustle in " +
        "the wind. Their trunks are smooth and large, silver " +
        "colored, and surprisingly smooth looking.\n");
    add_item(({"ancient maples", "ancient maple trees",
            "maple trees", "maples"}),
        "The ancient maple trees are giants in the forest. Their " +
        "trunks are large with age, and rough looking. Their " +
        "large branches grow out and upwards and are covered " +
        "with many large, green leaves.\n");

    add_item(({"spring"}),
        "It is a crack in the ground from which water bubbles up. The " +
        "spring is hidden from view, but fills the garden with a quite, " +
        "relaxing sound. The water flows over some rocks and collects " +
        "in a pool.\n");
    add_item(({"pool"}),
        "It is irregular in shape and full of cool water. The water looks " +
        "refreshing and is a popular place where elves come to get a " +
        "cool drink.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A bumblebee dances from flower to flower.");
    add_room_tell("Small birds dart from flower to flower.");
    add_room_tell("Some birds chirp overhead.");
    add_room_tell("The fragrance from some flowers waft by.");
    add_room_tell("A gentle breeze blows by.");
    add_room_tell("A bird flies into the trees above.");
    add_room_tell("Some leaves fall to the ground.");
    add_room_tell("Leaves rustle in the breeze.");
    add_room_tell("Water bubbles up from a hidden spring.");
    add_room_tell("Cool water bubbles over some rocks and falls into a pool.");

    add_exit(ROOM_DIR + "hall", "north");

    add_herb_file(SHIRE_HERB_DIR + "nasturtium");
    add_herb_file(KRYNN_HERB_DIR + "fdlhead");
    add_herb_file(GONDOR_HERB_DIR + "wstrawberry");
    add_herb_file("/d/Faerun/herbs/herb_files/lavender");
    add_herb_file("/d/Faerun/herbs/herb_files/lobelia");
    add_herb_file("/d/Faerun/herbs/herb_files/portabello_mushroom");

    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    set_search_places(({"garden","flowers", "trees"}));

    set_drink_from( ({"spring", "pool", "fountain", "water"}) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);

    fruit = 0;

    reset_room();

}

reset_room()
{
    set_searched(0);
    fruit_counter = 0;

}


/*
 * Function name:	init
 * Description	:	add the drinking and river verbs
 */
public void
init()
{
    ::init();
    init_drink();
    add_action("check_fruit", "pick");

}

/*
 * Fruit trees routines
 */

string get_fruit(string str)
{
    object picked_fruit;

    picked_fruit = clone_object(FRUIT_DIR + str);
    picked_fruit->move(this_player(), 1);
    write ("You pick a " + picked_fruit->query_short() + ".\n");
 
    say (QCTNAME(this_player()) + " picks some fruit from a tree.\n");

}

void pick_fruit(string str)
{

    int ran_fr;
    string what_fruit;


    if(lower_case(str) == "fruit")
    {
        ran_fr = random(sizeof(FRUIT));
        what_fruit = FRUIT[ran_fr];
        get_fruit(what_fruit);
    }
    else if(member_array(str, fruits) == -1)
    { 
        write("You do not see any of that fruit growing in the orchard.\n");
        fruit_counter = fruit_counter - 1; 
        return;
    }
    else
    { 
        get_fruit(str); 
        return;
    }
}

check_fruit(str)
{
    int ran_fr;
    int ran_fl;
    string what_fruit;
    object picked_fruit;

    ran_fr = random(sizeof(FRUIT));
    what_fruit = FRUIT[ran_fr];


    if (fruit_counter >= MAX_FRUIT)
    {
        write ("You notice that all the fruit has been picked.\n");
        return 1;
    }
    else
    {
        pick_fruit(str);
        fruit_counter = fruit_counter + 1;
        return 1;
   }

}
