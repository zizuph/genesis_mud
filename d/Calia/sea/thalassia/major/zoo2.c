
/* 	Zoo of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";

#include "defs.h"

void
create_water_room()
{
    set_short("Major Zone Zoo");
    set_long("You have entered a strange building in this city. "+
        "There is a very large air-filled container with clear "+
        "glass sides here. Inside of this container are many "+
        "different types of animals that you might see on the "+
        "surface lands. This appears to be a zoo of some sort. "+
        "It continues off to the west.\n");

    add_item(({"container","large container","very large container"}),
        "It is split up into different sections, each containing a "+
        "different species. "+
        "\n");

    add_item(({"section","sections","animal","animals"}),"Inside of "+
        "each section you see different animals that you might see on "+
        "land. You recognize an elephant, a couple of cows, a horse, "+
        "a few wolves and about a dozen gopheroos darting around. "+
        "They all seem quite comfortable and have plenty to eat "+
        "and drink.\n");

    add_item("glass","The glass appears to be fairly thin, but strong "+
        "enough to hold back the water. Near the top you notice an "+
        "intricately designed air system to continuously give the animals "+
        "fresh, breathable air as well as some hatches to feed them "+
        "through.\n");

    add_item(({"elephant","elephants"}),"This large grey beast is "+
        "wandering around in its grass, hay and mud filled section. "+
        "It occasionally reaches down with it's large trunk to pick "+
        "up some hay and feed itself. It appears very happy and well "+
        "taken care of.\n");

    add_item(({"cow","cows"}),"The cows seem very docile and somewhat "+
        "sleepy, just like any other cow you might find in the Calian "+
        "foothills. They have plenty of grass in their section to eat, "+
        "as well as a large trough full of fresh water to drink.\n");

    add_item(({"horse","horses"}),"This magnificent horse is "+
        "galloping around in its section, leaping over small ponds, "+
        "putting on quite a good show for you. Its pure white coat "+
        "appears to be well looked after. There is plenty of fresh "+
        "grass and a trough containing apples and water for it to "+
        "eat and drink.\n");

    add_item(({"wolf","wolves"}),"The wolves are on the far side of their "+
        "section and appear to be resting within the camouflage of the "+
        "tall grass of their home. You notice what is left of a few "+
        "rabbit corpses near the front of the section indicating that "+
        "they are being fed well and regularily.\n");

    add_item(({"gopheroo","gopheroos"}),"These tiny creatures are running "+
        "around, apparently able to slip in and out of each section with "+
        "ease. Upon close examination you notice small burrow holes "+
        "in each of the sections where they pop their heads up occasionally "+
        "to take a look around.\n");

    add_swim_exit(THALM+"zoo1","west");

}

int
do_break(string str)
{
    if (str == "container" || str == "containers" || str == "glass")
    {
        write("You don't dare break the containers as the animals inside "+
            "would surely drown!\n");
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
