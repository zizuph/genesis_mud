#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";
int is_open = 0;
int can_taken = 0;

void
create_room()
{
    set_short("The kitchen");
    set_long("This is the kitchen of the building. " +
        "In the middle is a big stove and the brick flue " +
        "is raising up through the ceiling. All over the " +
        "walls are various hooks and shelves for the utensils. " +
        "Nothing much is left and the shelves gape empty. Along " +
        "the wall is a bench where someone has placed a few " +
        "plates for the oven.\n");
    add_item("kitchen","@@long");
    add_item("bench","@@desc_bench");
    add_item("can","@@desc_can");
    add_item(({"leg","legs"}), "On a first glance one leg " +
        "of the bench seems to be shorter than the others. But " +
        "you quickly realise this is an illusion. It is the " +
        "floor that is not straight.\n");
    add_item("hooks","You cast a quick glance at the wall hooks. " +
        "Alas, they are all empty.\n");
    add_item(({"plate","plates"}),"You reach forward and examine " +
        "the metal plates on the bench. Without doubt they are for " +
        "baking bread in the oven.\n");
    add_item(({"flue","channel"}),"@@desc_flue");
    add_item(({"tin","baking tin"}),"@@desc_tin");
    add_item("shelves","You take a slow walk around the kitchen " +
        "trying to find something on the various shelves, but to " +
        "no avail. There is simply nothing to be found on them.\n");
    add_item("stove","When you examine the old black iron stove " +
        "you get black from soot. It's very big and heavy and " +
        "impossible to move from its place. On the stove is a big " +
        "cauldron.\n");
    add_item("cauldron","@@desc_cauldron");
    add_item("oven","You walk around the stove and see the " +
        "oven door at the other side. " + "@@desc_oven@@");
    add_item(({"hook","security hook"}),"You take a quick look at the " +
        "small security hook. It is used to secure the oven door so that " +
        "it won't be opened by mistake.\n");
    add_item(({"floor","wall","walls","ceiling"}),"The walls, floor " +
        "and ceiling have all the touch of a typical kitchen of a " +
        "mansion like this.\n");
    add_item("soot","The only thing to see inside the flue is soot. " +
        "Black and fat soot that makes your fingers black.\n");
    add_item("leaning floor", "Time took its toll to the floor in this " +
        "corner. Its leaning a bit so the bench standing here wobbles " +
        "a bit because all the legs on it doesn't connect with the " +
        "floor.\n");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("hall","south");
    reset_room();
}

void
reset_room()
{
    is_open = 0;
    can_taken = 0;
}

void
init()
{
    ::init();
    add_action("do_open", "open");
    add_action("do_close", "close");
    add_action("get_can","get");
    add_action("get_can","take");
}

int
get_can(string str)
{

    object obj;

    if (strlen(str) && (str == "can"))
        if (can_taken == 0)
        {
            obj = clone_object(THIS_DIR + "obj/can");
            obj->move(this_player());
            write("You lift the bench and grab the can " +
                "that is used to stabilise the bench.\n");
            say(QCTNAME(TP) + " lifts the bench and gets " +
                "a metal can from the floor.\n");
            can_taken = 1;
            remove_item("can");
            return 1;
        }
    return 0;
}


string
desc_flue()
{
    say(QCTNAME(TP)+ " steps up on the stove and looks " +
        "up inside the flue. A quick look tells you " +
        "there was nothing of intrest up there.\n");
    return "You climb the stove and examine the flue. " +
        "It looks very solid and shaking it doesnt make " +
        "you change this opinion. The smoke channel is dark so " +
        "when you lean forward and look up, you cant see " +
        "anything but soot.\n";
}

string
desc_cauldron()
{
    say(QCTNAME(TP)+ " leans over the cauldron on top of " +
        "the stove to see whats inside.\n");
    return "You grab the cauldron and lean it over so you " +
        "can see what's inside. To your disappointment it's empty. " +
        "At least it was clean.\n";
}

string
desc_can()
{

    if (can_taken == 0)
        return "The wooden bench at the wall stands with one leg in " +
            "a metal can. Most likely to stabilise the bench because " +
            "of the leaning floor in the corner. If you would take " +
            "the can, the bench would probably wobble if someone sat " +
            "on it.\n";
    return "";
}

string
desc_bench()
{
    if (can_taken == 1)
    {
        return ("You make room on the wooden bench besides " +
            "the metal plates and take a seat. Its a robust bench but " +
            "it wobbles slightly over your weight. This probably because " +
            "the floor is leaning a little here close to the wall.\n");
    }
    return ("You make room on the wooden bench besides " +
        "the metal plates and take a seat. Its a robust bench but " +
        "you notice that one leg stands in a metal can. Most likely " +
        "to stabilise the bench so it wont wobble on the slightly " +
        "leaning floor here close to the wall.\n");
}

string
desc_oven()
{
    if (is_open == 0)
        return ("The door is shut and secured with a small " +
            "security hook.\n");
    else
        return ("The door is wide open and a quick peek inside " +
            "shows a baking tin.\n");
}

int
do_open(string str)
{
    if (strlen (str) && (str == "oven" || str == "oven door"
        || str == "hook" || str == "door"))
    {
        if (is_open == 0)
        {
            write("You lift the hook gently and open the " +
                "oven door. When you look inside you see " +
                "a baking tin but nothing else.\n");
            is_open = 1;
            return 1;
        }
        else
        {
            write("The oven door is already open!\n");
            return 0;
        }
    }
}

int
do_close(string str)
{
    if (strlen (str) && (str == "oven" || str == "oven door"
        || str == "hook" || str == "door"))
    {
        if (is_open == 0)
        {
            write("The oven door is already closed!\n");
            return 0;
        }
        else
        {
            write("You close the oven door and secure it " +
                "with the hook.\n");
            is_open = 0;
            return 1;
        }
    }
}

string
desc_tin()
{

    if (is_open == 1)
        return ("Inside the oven is a small baking tin. " +
            "The tin is black from soot and you decide to leave it alone.\n");
    else
        return ("What tin? Perhaps inside the closed oven?\n");

}
