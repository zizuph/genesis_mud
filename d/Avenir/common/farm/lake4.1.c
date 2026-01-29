#include "defs.h"
inherit (THIS_DIR + "lake_base.c");

void reset_room();

void
create_room()
{

    make_the_room();
    add_exit("boathouse","west", "@@boathouse|west", 1 , 1);
    add_exit("reed","northwest", "@@reed|northwest", 1, 1);
    add_exit("reed","southwest", "@@reed|southwest", 1, 1);
    add_exit("reed","north", "@@reed|north", 1, 1);
    add_exit("lake5.1","south", 0, 1, 1);
    add_exit("lake3.1","northeast", 0, 1, 1);
    add_exit("lake4.2","east", 0, 1, 1);
    add_exit("lake5.2","southeast", 0, 1, 1);
    add_prop(ROCK, 1);
    add_prop(LAKE, 1);
    reset_room();

}

void
reset_room()
{


}

int
boathouse(string str)
{

    string text;

    if (!environment(this_player())->id("boat"))
        return 0;
    write("The reed is thinner here and doesnt stop anyone " +
        "from passing through.\n");
    if (this_player()->query_option(2))
        text = find_object(THIS_DIR + "boathouse")->short();
    else
        text = find_object(THIS_DIR + "boathouse")->long();

    tell_room(environment(this_player()), text);
    return 0;
}

string
query_default_drift()
{
    return "west";
}
