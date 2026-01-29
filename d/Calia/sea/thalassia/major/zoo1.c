
/* 	Zoo of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";

#include "defs.h"
#include SEA_QUESTS

void
create_water_room()
{
    set_short("The Major Zone Zoo");
    set_long("You have entered a strange building in this city.  "+
        "There are many aquariums here containing different types "+
        "of sea creatures. They seem to be well-kept and fed "+
        "on a regular basis. This appears to be a zoo of some "+
        "sort. It continues off to the east.\n");

    add_item(({"aquarium","aquariums","many aquariums"}),
        "Each of the glass aquariums contain different types of "+
        "animals that inhabit parts of the sea. You notice a "+
        "sea-lion, a sea-elephant, barracudas, sharks, demon toads, "+
        "sea snakes and various other creatures that you don't "+
        "recognize.\n");

    add_item(({"barracuda","barracudas"}),"This creature looks "+
        "very fast and powerful. It is light grey in color, "+
        "with dark green stripes. It appears to be annoyed by "+
        "your being here, swimming around very quickly, baring "+
        "its large mouthful of spearlike teeth.\n");

    add_item(({"shark","sharks"}),"This is the infamous great "+
        "white shark. It is very large, long and bullet shaped. "+
        "It's black eyes appear lifeless and evil. It is always "+
        "hungry and will eat anything...or anyone.\n");

    add_item(({"toad","toads","demon toad","demon toads"}),
        "Two enormous green-lidded eyes set in a gnarled "+
        "reptilian head. When its nostrils flare and its long "+
        "scarlet mouth opens, it reveals a pink, flickering "+
        "tongue. The extraordinarily dense weight of scaly flesh "+
        "is supported on massive webbed feet and limbs as thick "+
        "as elm trunks. When it breathes, its whole body shakes "+
        "and shudders.\n");

    add_item(({"snake","snakes","sea snake","sea snakes"}),
        "This snake is a watery relative of the cobra "+
        "and mamba snakes, and just as deadly. It is ten feet "+
        "long and has white and black stripes along its "+
        "entire body.\n");

    add_item(({"sea-lion","sea-lions"}),"The sea-lion is a deep "+
        "green coloured, scaled animal about eight feet in length. "+
        "It has a mane that is made of some sort of fur, also "+
        "green in colour. Instead of legs, it has two fins and "+
        "a large fish-like tail.\n");

    add_item(({"sea-elephant","sea-elephants"}),"A magnificent "+
        "creature like none you have ever seen before is this "+
        "sea-elephant. It is a very large animal, about fifteen "+
        "feet in length, and grey in colour. It has a very large "+
        "trunk, just like it's land-based counter-part, and two "+
        "large white tusks growing from the sides of it's mouth. "+
        "Like most other creatures in the sea, it does not have "+
        "legs, but fins and a large tail to move about.\n");

    add_swim_exit(THALM+"major41","west");
    add_swim_exit(THALM+"zoo2","east");

}

int
do_break(string str)
{
    if (str == "aquarium" || str == "aquariums" || str == "glass")
    {
        write("You don't dare break the aquariums as the animals inside "+
            "would surely escape!\n");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action("do_break","break");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->query_prop(THAL_E_ADMIN_PROP))
    {
        ob->catch_msg("\n\nYou have successfully found the zoo. "+
            "You can return to the east administration office of the "+
            "Royal Palace and ask for your reward.\n\n");
        ob->add_prop(THAL_E_ADMIN_PROP,2);
    }
}

