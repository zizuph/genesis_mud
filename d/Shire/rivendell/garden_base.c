/*
 * Base room for garden in Imladris
 * Coded by Finwe, 1998
 */

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include "/d/Faerun/open/herb_list.h"


inherit "/std/room";
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";

void create_garden_room() {}

#define FRUIT    ({ "apple", "cherries", "peach"})
#define VEGGIES  ({ "tomato", "cucumber", "corn", "lettuce",\
                   "carrot" })
#define MAX_VEGGIES   3         /* max num of veggies per room */
#define MAX_FRUIT     3         /* maximum num of fruits in each room */

int fruit;
int veggie;
int veggie_counter;
int fruit_counter;
string herb_here; 

void reset_room();

void
create_garden()
{
}

create_room()
{
    add_prop(ROOM_S_MAP_FILE, "rivendell.txt");

    reset_room();
    set_short("The garden of Imladris");
    set_long("@@garden_desc@@");

    add_item(({"last homely house", "house"}),
        "The house is constructed of stone with ornately carved " +
        "dark beams. The beams form criss-cross diamond " +
        "patterns across the face of the house. Gables extend from " +
        "the roof. The roof is covered with cedar shingles.\n");
    add_item(({"shingles", "cedar shingles"}),
        "The cedar shingles are weather worn but still " +
        "in good condition.\n");
    add_item("roof",
        "The roof is steeply pitched, allowing snow and " +
        "rain to roll off the house quickly and easily.\n");
    add_item("gables",
        "The extend from the roof, allowing more space in " +
        "the upper rooms.\n");
    add_item(({"beam", "beams"}),
        "The beams are made from dark oak. They are polished " +
        "to a deep luster and decorate the face of the house.\n");
    add_item("path",
        "The pathway is made of flat stones that fit close " +
        "together. Growing between the stones are mosses.\n");
    add_item(({"mosses", "moss"}),
        "The moss is velvet green and grows between the " +
        "stones in the path.\n");
    add_item(({"tree", "trees"}),
        "Tall fruit trees grow throughout the garden. The " +
        "branches are large and spread wide shading the garden. " +
        "The trees are heavy with fruit.\n");
    add_item(({"flowers", "flower"}),
        "A vast array of flowers grow in the garden. They are " +
        "in a rainbow of colors, different shapes, sizes, and " +
        "heights. All are beautiful and healthy.\n");
    add_item(({"bushes", "bush"}),
        "The bushes are large and well formed. Some are as tall " +
        "as an elf while others are small, barely taller than " +
        "your knee. The bushes have been expertly cared for " +
        "and seem perfect.\n");
    add_item(({"fruit", "fruits"}),
        "You see fruit that is ripe and ready to be picked. It " +
        "all looks delicious and tantilizing as it hangs on the " +
        "plants. Some fruits look edible and ready to be " +
        "picked.\n");
    add_item(({"vegetables", "vegetable"}),
        "The vegetables are tucked in between the flowers, " +
        "bushes, and under the trees. The fruit hangs on the " +
        "bushes ready to be picked. You see some are ready to " +
        "be picked.\n");
    add_item(({"plant", "plants"}),
        "Growing in the garden are a wide variety of flowers, " +
        "bushes, vegetables, and trees. If you could grow plants " +
        "like this, you would be a true gardener.\n");
    add_item(({"fence", "split-rail fence", "split rail fence"}),
        "The fence is constructed of timbers that have been " +
        "split in two. They are secured to posts that have " +
        "been sunk into the ground.\n");
    add_item(({"fence post", "fence posts", "posts", "post"}),
        "The fence posts are sunk deep into the ground, " +
        "offering a secure foundation for the fence. The rails " +
        "are securely attached to the posts.\n");
    add_item(({"rails", "fence rails", "fence rail", "rail"}),
        "The fence rails are made from split cedar. They are " +
        "weathered and securely fastened to the fence posts.\n");
    add_prop(ROOM_I_NO_TELEPORT, 
        "A great elven power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT, 
        "A great elven power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT_TO, 
        "A great elven-power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT_FROM, 
        "A great elven-power prevents that from happening.\n");

    add_prop(ROOM_M_NO_STEAL,
        "Evil acts like that are not permitted in Imladris.");

    create_garden_room();

    herb_here = ONE_OF_LIST(({GONDOR_HERB_DIR + "astaldo",
                GONDOR_HERB_DIR + "athelas",
                GONDOR_HERB_DIR + "attanar",
                GONDOR_HERB_DIR + "seregon",
                GONDOR_HERB_DIR + "suranie",
                SHIRE_HERB_DIR + "huckleberry",
                SHIRE_HERB_DIR + "lianor_berry",
                SHIRE_HERB_DIR + "grass",
                KRYNN_HERB_DIR + "solinaith",
                KRYNN_HERB_DIR + "tiger_lily",
                "/d/Faerun/herbs/herb_files/amaranth"}));

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"bush","bushes","trees", "flowers"}));
    add_herb_file(herb_here);

    fruit = 0;
    veggie = 0;
    create_garden();
}

init()
{
    add_action("sniff_air", "sniff");
    add_action("sniff_air", "smell");
    add_action("pick_fruit", "pick");
    ::init();
}


sniff_air(str)
{
    if ((str == "air"))
    {
        write ("You take a deep breath. The heady fragrance leaves " +
               "you smiling contendedly.\n");
        say (QCTNAME(this_player()) + " takes a deep breath and " +
             "sighs contentedly.\n");
        return 1;
    }
    else
    {
        write ("You wrinkle your nose.\n");
        say (QCTNAME(this_player()) + " wrinkles their nose.\n");
        return 0;
    }
    return 1;
}

pick_fruit(str)
{
    int ran_fr;
    int ran_fl;
    string what_fruit;
    string what_veggie;
    object picked_fruit;
    object picked_veggie;

    ran_fr = random(sizeof(FRUIT));
    ran_fl = random(sizeof(VEGGIES));
    what_fruit = FRUIT[ran_fr];
    what_veggie = VEGGIES[ran_fl];

    if (fruit_counter == MAX_FRUIT)
    {
        write ("You notice that all the fruit has been picked.\n");
        return 1;
    }
    else
    {
        if ((str == "fruit"))
        {
            picked_fruit = clone_object(FRUIT_DIR + what_fruit);
            picked_fruit->move(this_player(), 1);
            write ("You pick a " + picked_fruit->query_short() + ".\n");

            say (QCTNAME(this_player()) + " picks some fruit from the " +
                "garden.\n");
            fruit_counter = fruit_counter + 1;
            return 1;
         }
   }



   if (veggie_counter == MAX_VEGGIES)
    {
        write ("You notice that all the vegetables have been picked.\n");
        return 1;
    }
    else
    {
        if ((str == "vegetable"))
        {
            picked_veggie = clone_object(FRUIT_DIR + what_veggie);
            picked_veggie->move(this_player(), 1);
            write ("You pick a " + picked_veggie->query_short() +
                ".\n");

            say (QCTNAME(this_player()) + " picks a vegetable from the " +
                "garden.\n");
            veggie_counter = veggie_counter + 1;
            return 1;
         }
    }
    return 0;
}


void
reset_room()
{
    fruit_counter = 0;
    veggie_counter = 0;
    set_searched(0);
}

void
enter_inv(object ob, object from)
{
   start_room_tells();
   ::enter_inv(ob, from);
}


string
garden_desc()
{
    switch(random(4))
    {
        case 0:
            return "The garden is large and surrounds the " +
            "house. Many different flowers and bushes grow " +
            "here. Planted among the flowers and bushes are a " +
            "variety of vegetables. Tall trees grow in the " +
            "garden, offering shade and shelter from the " +
            "elements.\n";
            break;
        case 1:
            return "You stand in beautiful " +
            "gardens. It is evident that this is tended by " +
            "expert hands, elven hands that know the fine art " +
            "of gardening. Plants you don't know grow " +
            "abundantly here. Among them you see " +
            "vegetables growing. Tall trees grow here shading " +
            "the garden and offering peace and quiet.\n";
            break;
        case 2:
            return "A breathtaking array of plants grow here. " +
            "Some you recognize while others are unknown to " +
            "you. They are all expertly cared for and are a " +
            "wonder to behold. An odd thing about the garden " +
            "is that even though flowers grow abundantly here, " +
            "so do vegetables and edible plants. The gardener " +
            "is obviously an expert because these plants " +
            "wouldn't grow anywhere else but here, all under " +
            "the careful eye of an elf.\n";
            break;
        case 3:
            return "Flowers, bushes, and trees grow in a " +
            "dizzying array here. There are so many that it " +
            "would take a long time to catalogue them all. The " +
            "trees are some of the largest you have ever seen. " +
            "Growing under them are large bushes and flowers. " +
            "Tucked among the plants are many edible plants.\n";
            break;

        default:
            return "Tall trees dominate the garden here. Under " +
            "the trees are lovely plants and bushes. Everything " +
            "grows beautifully, all under the careful eye of an " +
            "expert elven gardener.\n";
            break;
     }
}
