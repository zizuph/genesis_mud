/*
 * Garden of Telseron
 * Coded by Finwe, September 1996
 * The code of the garden is based on the orchard code in Roke.
 */
 
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Emerald/defs.h"
#include "garden.h"
#include <ss_types.h>
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
 
#define FRUIT    ({ "apple", "cherries", "watermelon", "peach", \
                    "orange", "kiwi", "plum", "nectarine", \
                    "cantaloupe", "grapes", "strawberry", \
                    "grapefruit", "blueberry", "pear", \
                    "lemon", "lime" })
 
#define FLOWERS  ({ "carnation", "daisy", "gardenia", "jasmine", \
                   "stephanotis", })
 
#define TOTAL_FRUITS 15         /* total fruits to choose from */
#define MAX_FLOWERS   3         /* max num of flowers per room */
#define MAX_FRUIT     3         /* maximum num of fruits in each room */
 
int fruit;
int flower;
int flower_counter;
int fruit_counter;
 
void reset_room();
 
void
create_garden()
{
}
 
create_room()
{
    reset_room();
    set_short("The royal garden");
    set_long("   You stand in the royal garden. The perfection " +
        "of the plants takes your breath away. A symphony of " +
        "flowers, shrubs, and trees grows here. " +
        "A floral tapestry appears from the different " +
        "hues, varied heights of the plants and assorted " +
        "blossoms. Their profusion of colors create a dazzling " +
        "kaleidoscope as the plants contend for your attention. " +
        "The fragrance from all the blossoms intoxicates your " +
        "senses. You long to remain here as you drink in the beauty " +
        "of the garden. ");
 
    add_item("path",
        "The pathway is made of flagstones. Growing between the " +
        "stones is thyme. As you tread through the garden, " +
        "the plant releases a gentle fragrance.\n");
    add_item(({"bushes", "shrubs"}),
        "Many fragrant and colourful bushes grow here. They grow " +
        "in groups among the flowerbeds. Some act as sentinels as " +
        "they stand guard on either side of the statues.\n");
    add_item("flowers",
        "A blaze of color announces the flowers here. The colors " +
        "are staggering as you look over the beds. Perennials " +
        "and annuals are combined, creating a border that follows " +
        "the garden path.\n");
    add_item(({"tree", "trees"}),
        "Tall trees grow here. Some are shade, some are fruit " +
        "trees, and some are grown simply for their burst of " +
        "colors. Ripe fruit glistens in the sun.\n");
    add_item("sky",
        "The azure sky can be seen through the branches of the " +
        "trees.\n");
 
 
    set_tell_time(35);
    add_tell("The master gardener walks by.\n");
    add_tell("The master gardener pulls some weeds.\n");
    add_tell("The master gardener passes by.\n");
    add_tell("A gentle breeze caresses your face.\n");
    add_tell("Some birds sing in the trees.\n");
    add_tell("A servant gathers some fruit for the Queen.\n");
    add_tell("A servant picks some flowers.\n");
    add_tell("The florist picks some flowers for his shop.\n");
    add_tell("You hear some joyful laughing nearby.\n");
    add_tell("Some elves wander by.\n");
    add_tell("An elf stops and picks a flower.\n");
    add_tell("Butterflies land gently on the flowers.\n");
    add_tell("A hummingbird darts in and out of the flowers.\n");
    add_tell("A bumblebee visits each flower here.\n");
 
    fruit = 0;
    flower = 0;
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
    if ((str == "air") || (str == "flowers"))
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
        say (QCTNAME(this_player()) + " wrinkles their noise.\n");
        return 0;
    }
    return 1;
}
 
pick_fruit(str)
{
    int ran_fr;
    int ran_fl;
    string what_fruit;
    string what_flower;
    object picked_fruit;
    object picked_flower;
 
    ran_fr = random(sizeof(FRUIT));
    ran_fl = random(sizeof(FLOWERS));
    what_fruit = FRUIT[ran_fr];
    what_flower = FLOWERS[ran_fl];
 
 
    if (fruit_counter == MAX_FRUIT)
    {
        write ("You notice that all the fruit has been picked.\n");
        return 1;
    }
    else
    {
        if ((str == "fruit"))
        {
 
            picked_fruit = clone_object(TOWNSHIP_DIR + 
                "fruit/" + what_fruit);
            picked_fruit->move(this_player(), 1);
            write ("You pick a " + picked_fruit->query_short() + ".\n");
 
            say (QCTNAME(this_player()) + " picks some fruit from the " +
                "garden.\n");
            fruit_counter = fruit_counter + 1;
            return 1;
         }
   }
 
   if (flower_counter == MAX_FLOWERS)
    {
        write ("You notice that all the flowers has been picked.\n");
        return 1;
    }
    else
    {
        if ((str == "flower"))
        {
            picked_flower = clone_object(TOWNSHIP_DIR + 
                "flowers/" + what_flower);
            picked_flower->move(this_player(), 1);
            write ("You pick a " + picked_flower->query_short() + ".\n");
            say (QCTNAME(this_player()) + " picks a flower from the " +
                "garden.\n");
            flower_counter = flower_counter + 1;
            return 1;
         }
    }
    return 0;
}
 
 
void
reset_room()
{
    fruit_counter = 0;
    flower_counter = 0;
}
 
void
enter_inv(object ob, object from)
{
   start_room_tells();
   ::enter_inv(ob, from);
}
