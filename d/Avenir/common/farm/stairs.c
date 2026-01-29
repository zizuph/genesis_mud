#pragma strict_types
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>
#include "./defs.h"

inherit "/std/room";

void
create_room()
{
    set_short("The stairs");
    set_long("You are standing in a small spiral staircase. " +
        "You realize you must be behind the wall to a room " +
        "in the eastern part of the house.\n");
    add_item("wall","You hold your head close to the wall " +
        "and although you can't see anything you realize you " +
        "could probably overhear anything spoken in the " +
        "room behind the wall.\n");
    add_item("stairscase", "The staircase is made of some " +
        "unknown material. It looks like metal but feels like stone. " +
        "When you touch it with your hand it feels smooth and " +
        "it does not give away any sound when you walk on it.\n");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("tower","up","@@mess_up");
    add_exit("potato_cellar","down","@@mess_down");
    (THIS_DIR + "tower")->teleledningsanka();

    reset_room();
}

void
reset_room()
{

}

void
init()
{
    ::init();
        add_action("break_wall", "break");
}

string
mess_up()
{
    write("Finally you reach the top of the stairs and arrive " +
        "into the tower room.\n");

}

int
break_wall(string str)
{
    string text;

    if (str == "wall")
    {
        write("You put your shoulder to the wall and try to break " +
            "it down. It bulges a little but nothing else. It seems " +
            "to be impossible to break it down so you give up your " +
            "attempt.\n");
        return 1;
    }
    return 0;
}

string
mess_down()
{
    object potato_cellar;

    potato_cellar = find_object(THIS_DIR + "potato_cellar");

    if (!(potato_cellar->query_ladder()))
    {
        tell_room(potato_cellar, "A door opens in the ceiling " +
            "and you see a ladder comes tumbling down from " +
            "above.\n");
        potato_cellar->drop_ladder();
    }
}

