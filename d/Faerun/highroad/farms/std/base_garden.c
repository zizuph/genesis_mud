/*
 * Base orchard room for Faerie
 * Finwe, August 2004
 *
 * Thanks to Altrus for his help tweaking the code!
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/flowers/flowers.h"
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit FAERUN_OUTDOOR_BASE;

int flower;
int flower_counter = 0;

void reset_room();
void create_garden_room() {}

static string *standard_flowers;
static private string *flower = standard_flowers;

string *flowers_used = WILDFLOWERS;

public void
set_flowers(mixed x)
{
    if (stringp(x))
        standard_flowers = ({ x });
    else if (pointerp(x))
        standard_flowers = x;
    else
        standard_flowers = flowers_used;
}

public void
create_faerun_room()
{
    ::create_faerun_room();
    seteuid(getuid(TO));

    reset_room();
    set_short("A flower garden");
//    set_long(short() + ". " + extraline + "\n");

    add_item(({"path", "gravel path"}),
        "The path winds through the thick flowerbeds. It is made of crushed " +
        "gravel and crunches beneath your feet.\n");
    add_item(({"flowerbeds", "flowerbed", "beds", "bed"}),
        "The flowerbeds are thick and full of many flowers. They are " +
        "vibrant and all  shapes, and sizes. The flowers fill the beds " +
        "with a symphony of colors.\n");
    add_item(({"flowers", "wildflowers"}),
        "Many different types of flowers grow around the house. They " +
        "are different colors, shapes, and sizes, and provide a splash " +
        "of color around the house.\n");
    add_item(({"wall", "stone wall"}),
        "It is about waist high and made of flat stones piled on top of " +
        "each other.\n");
    add_item(({"stones", "flat stones"}),
        "They are stacked on top of each other and make up the stone " +
        "wall. The stones are different colors of gray, brown, red, and " +
        "other earth tones, and of irregular shapes and sizes.\n");
    add_item(({"bees", "honeybees", "honeybee", "bumblebees", "bumblebee"}),
        "They are large and buzz loudly in the orchard. They fly from each flower in the garden.\n");

    set_room_tell_time(random(ROOM_TELL_TIME) + 30);
    add_room_tell("Large bumblebees bounce from flower to flower.");
    add_room_tell("Soft fragrance drifts through the garden.");
    add_room_tell("Butterflies flit around the garden.");
    add_room_tell("A hummingbird flies around.");
    add_room_tell("A bird sings cheerfully.");


    create_garden_room();
    set_flowers(flowers_used);
    flower = 0;


}

init()
{
    ::init();
    add_action("sniff_air", "sniff");
    add_action("sniff_air", "smell");
    add_action("check_flowers", "pick");
//    add_action("list_flowers", "list");

}



string get_flower(string str)
{
    object picked_flower;

    picked_flower = clone_object(FLOWERS_DIR + str);
    picked_flower->move(this_player(), 1);
    write ("You pick a " + picked_flower->query_short() + ".\n");

    say (QCTNAME(this_player()) + " picks flower from the garden.\n");

}

void pick_flower(string str)
{

    int ran_fr;
    string what_flower;
    object picked_flower;



    if(lower_case(str) != "flower")
    {
        write("Pick what, a flower?\n");
        return;
    }


    if(flower_counter >= MAX_FLOWERS)
    {
        write("All the flowers have been picked.\n");
        return;
    }

    what_flower = ONE_OF_LIST(standard_flowers);
    picked_flower = clone_object(FLOWERS_DIR + what_flower);
    picked_flower->move(this_player(), 1);
    write ("You pick a " + picked_flower->query_short() + ".\n");

    say (QCTNAME(this_player()) + " picks a flower from the garden.\n");
    return;

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

check_flowers(str)
{
    int ran_fr;
    int ran_fl;
    string what_flower;
    object picked_flower;

    ran_fr = random(sizeof(standard_flowers));
    what_flower = standard_flowers[ran_fr];


    if (flower_counter >= MAX_FLOWERS)
    {
        write ("You notice that all the flowers have been picked.\n");
        return 1;
    }
    else
    {
        pick_flower(str);
        flower_counter++;
        return 1;
   }

}


void
reset_room()
{
    flower_counter = 0;
}

string garden_descr()
{
    return "Many flowers grow in the garden. ";
}

