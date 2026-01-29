/*
 * Base file for the farms and homesteads
 * Finwe, August 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_OUTDOOR_BASE;

void create_farm_room() {}

public void
create_faerun_room()
{
    ::create_faerun_room();
    extraline = "More descr here.";

    set_room_tell_time(random(ROOM_TELL_TIME) + 30);

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

    create_farm_room();

}

/*
 * Function name : set_add_chicken_noises
 * Description   : adds descr of chicken noises
 */
void  set_add_chicken_noises()
{
    add_room_tell("A hen clucks quietly.");
    add_room_tell("A hen suddenly squawks loudly.");
    add_room_tell("A chicken pecks at something on the ground.");
    add_room_tell("A rooster struts around.");
    add_room_tell("A chicken flaps its wings suddenly.");
}


/*
 * Function name : set_add_farm_noises
 * Description   : adds descr of farm noises
 */
void  set_add_farm_noises()
{
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Some clouds float lazily across the sky.");
    add_room_tell("Some chickens scratch in the dirt.");
    add_room_tell("A horse neighs in the distance.");
    add_room_tell("A cow moos in the distance.");
}


/*
 * Function name : set_add_road
 * Description   : adds descr of road in village
 */
void set_add_road()
{
    add_item(({"road", "path", "trail"}),
        "The road is well trodden and bare of grass. On either side " +
        "of it grow bushes, grasses, and flowers.\n");
    add_item(({"bushes"}),
        "They are thick and grow alongside the road. The bushes are " +
        "healthy looking and grow in groups among the grass.\n");
    add_item(({"grasses"}),
        "The grass has been cut but still moves about in the wind. It " +
        "is a healthy green color with various wildflowers growing in " +
        "it. Some bushes grow in the grass as well as tall clover.\n");
    add_item(({"flowers", "wildflowers"}),
        "Many different types of flowers grow here. Some are tall, while " +
        "others are short or even hidden among the grasses, visible " +
        "only when the grasses move. They are different colors, shapes, " +
        "and sizes.\n");
    add_item(({"meadow", "grassland", "field", "meadows"}),
        "This is a wide area of land covered with wild grasses. The grasses " +
        "wave in the breeze and are up to your ankles. Growing in the grass " +
        "are flowers and clover.\n");
    add_item(({"grasses", "wild grasses", "tall grasses", "tall grass",
            "grasses", "grass"}),
        "It is an emerald green, healthy looking, and covers the meadow. " +
        "Clover and wild flowers grow between the grasses.\n");
    add_item(({"wagon ruts", "ruts", "rut"}),
        "They are narrow grooves that run down the center of the road. " +
        "They were made from constant travel by wagons that travel it.\n");
}

/*
 * Function name :
 * Description   : adds descr of
 */
void set_add_clover()
{
    add_item(({"clover"}),
        "This is a tall plant with three to five leaves on each stalk. " +
        "The leaves are unusually large and a deep emerald green. Large " +
        "purple flowers grow among the clover.\n");
    add_item(({"clover flower", "clover flowers", "purple flowers",
            "purple flower"}),
        "The large purple flowers are a ball of dense, purple spikes. " +
        "They are the size of a fist and smell sweet.\n");
}


/*
 * Function name : set_wood_planks
 * Description   : adds descr of wood planks used in buildings
 */
void set_wood_planks(string str)
{
    add_item(({"planks", "plank", "wood planks", "wood plank", "board",
            "boards"}),
        "The planks are long, wide, and thick. They have been cut from old " +
        "trees and planed smooth. The planks look weathered but still " +
        "in good condition. " + str + "\n");
}


/*
 * Function name : set_add_game_path
 * Description   : adds descr of game path from garden to orchard
 */
void  set_add_game_path()
{
    add_item(({"ground"}),
        "The ground is covered with overgrown grass. It looks like it's " +
        "been trampled here by many animals that wander this way. There " +
        "is a faint line in the grass.\n");
    add_item(({"line", "faint line"}),
        "It looks like a game trail, a path that animals wander. It runs " +
        "through the grass and disappears.\n");
    add_item(({"path", "game path"}),
        "It is a faint line that many animals have traveled on. The path " +
        "cuts through the grass and is barely visible. It's only noticeable " +
        "because of a few bent blades of grass.\n");
    add_item(({"grass"}),
        "The grass is lush and thick, and about ankle high. It looks like " +
        "it has been eaten by animals that wander this way.\n");
    add_item(({"bent blades of grass"}),
        "They are grasses that have been walked on by animals. They " +
        "mark the direction the animals went through the area, and " +
        "only visible by skilled trackers.\n");
    add_item(({"tracks", "animal tracks"}),
        "They are imprints in the grass. The tracks were made by many " +
        "animals that have travelled here and are various sizes. \n");
    add_item(({"trees"}),
        "They are various sizes and grow in groups everywhere. The trees " +
        "provide shade and are surrounded by bushes and grasses.\n");
    add_item(({"bushes"}),
        "They are low plants with many branches. The bushes grow in clumps " +
        "and around the trees.\n");
}

/*
 * Function name : set_add_rocky_ground
 * Description   : adds descr of rocky ground
 */
void  set_add_rocky_ground()
{
    remove_item("grass");
    add_item(({"grass", "clumps of grass", "clumps"}),
        "The grass is gray colored and thin. It grows sparsley across " +
        "the area. It looks trampled and short to the ground.\n");
    add_item(({"ground", "rocky ground"}),
        "The ground is packed hard and rough looking. It is rocky with " +
        "patches of grass growing on it.\n");    
    add_item(({"rocks", "rock", "stones", "stone"}),
        "They are small and smooth. The rocks and stones are strewn across " +
        "the ground.\n");
    add_item(({"path", "game path"}),
        "It is a faint line that many animals have traveled on. The path " +
        "cuts through the ground and is barely visible. It's only " +
        "noticeable because of the animal tracks.\n");
    add_item(({"tracks", "animal tracks"}),
        "They are imprints in the grass. The tracks were made by many " +
        "animals that have travelled here and are various sizes. \n");

}


string path1_descr()
{
    return "Thick grass covers the area. It spreads out to the north " +
        "and beyond. The grass comes up to your ankles. A thin path " +
        "meanders around here, winding around trees and bushes that grow " +
        "in small groups.";
}

string path2_descr()
{
    return "The thin path wanders through the thick grass. It looks like " +
        "it was made by animals that wander on it. Thick grass covers " +
        "the area, which has been trampled down by countless animals.";
}

string path3_descr()
{
    return "The grassland spreads out before you, in a sea of green. Trees " +
        "and bushes grow in scattered groups. The grass is ankle deep " +
        "and grows up to the tree trunks.";
}

string path4_descr()
{
    return "Animal tracks cover the grass, having been trampled flat by " +
        "many animals. Some trees have claw marks in them from savage beasts.";
}

string path5_descr()
{
    return "Trees and bushes dot the area. They look rugged and windblown. " +
        "Grass covers the ground, but trampled down by many animals. Tracks " +
        "cover the ground.";
}

string path6_descr()
{
    return "The grass begins to thin here. Hard, rocky ground is exposed " +
        "revealing brown dirt and rocks. It is packed with tufts of grass " +
        "growing in clumps among the stones.";
}

string path7_descr()
{
    return "The hard packed ground looks rough and stony. It's brown and " +
        "strewn with loose rocks. Patches of grass grow here and a faint " +
        "path meanders across the ground.";
}

string path8_descr()
{
    return "The grass begins to thin here, revealing the rocks and dirt. " +
        "The ground is packed hard and uneven. In the distance grow trees " +
        "and bushes.";
}

string path9_descr()
{
    return "A stone wall surrounds an orchard to the south. The orchard " +
        "looks vibrant and in good care. The trees grow in straight lines " +
        "and full of fresh fruit. Beyond the orchard is a large farmhouse.";
}
