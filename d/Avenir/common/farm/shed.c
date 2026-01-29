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
int fork = 1;
int planks = 5;
int query_fork();

void
create_room()
{
    set_short("The tool shed");
    set_long("This is a small shed used for storing tools and " +
        "equipment. You quickly cast a brief look around in " +
        "the shed but its disappointingly empty. Through the " +
        "ceiling and walls a few beams of light find their " +
        "way in and give faint light to the shed.\n");
    add_item(({"beams","light beams"}),"The source cast a few " +
        "beams of light through some invisible cracks " +
        "in the ceiling and the walls.\n");
    add_item("ceiling","You look up at the ceiling and see " +
        "dust flying around in the beams of light from " +
        "invisible cracks.\n");
    add_item("straws","These are just a few old straws " +
        "scattered around the floor.\n");
    add_item("floor","@@desc_soil");
    add_item("soil","@@desc_soil");
    add_item(({"wall","walls"}),"You take a step closer to " +
        "examine the walls but find nothing sensational " +
        "about them.\n");
    add_item(({"pile","planks","heap"}),"@@desc_heap");
    add_item(({"shed","tool shed"}),"@@long");
    add_prop(OBJ_S_SEARCH_FUN, "search_eq");
    add_exit("yard","out");
    set_terrain(TERRAIN_RESIDENCE);
    reset_room();
}

void
reset_room()
{
    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
        return;
    planks = 5;
    fork = 1;
}

void
init()
{

    ::init();
        add_action("get_plank","get");
        add_action("get_planks","get");
        add_action("push_planks","push");
        add_action("push_planks","move");
}


int
get_plank(string str)
{
    object obj, pitchfork;

    if (strlen(str) && (str == "plank"))
    {
        if (planks)
        {
            obj = clone_object(THIS_DIR + "obj/plank");
            obj->move(this_player());
            write("You pick up a wooden plank from the corner.\n");
            say(QCTNAME(TP) + " gets a wooden plank from the " +
                "ground.\n");
            planks-- ;
            if (!(planks))
            {
                if (query_fork())
                {
                    pitchfork = clone_object(THIS_DIR + "obj/pitch_fork");
                    pitchfork->move(TO);
                    write("In the soil below the last plank you " +
                        "spot a hidden pitch fork.\n");
                    say("After " +QCTNAME(TP)+ " picks up the " +
                        "plank from the ground something shows " +
                        "up that was previously hidden below " +
                        "the heap of planks.\n");
                    fork = 0;
    }
            }
            return 1;
        }
    }
    return 0;
}

int
get_planks(string str)
{
    object obj, pitchfork;

    if (strlen(str) && ((str == "planks") || (str == "heap")))
    {
        if (!(planks))
            return 0;
        if ((planks) == 1)
            write("There is only one plank left.\n");
            return 1;
        obj = clone_object(THIS_DIR + "obj/plank");
        obj->move(this_player());
        write("You try to grab a few planks but find it too " +
            "inconvinient to take more than one at the time.\n");
        say(QCTNAME(TP) + " gets a wooden plank from the ground.\n");
        planks-- ;
        if (!(planks))
        {
             if (query_fork())
             {
                 pitchfork = clone_object(THIS_DIR + "obj/pitch_fork");
                 pitchfork->move(TO);
                 write("In the soil below the last plank you " +
                     "spot a hidden pitch fork.\n");
                 say("After " +QCTNAME(TP)+ " picks up the " +
                     "plank from the ground something shows " +
                     "up that was previously hidden below " +
                     "the heap of planks.\n");
                 fork = 0;
 }
        }
        return 1;
    }
    return 0;
}

int
push_planks(string str)
{
    object pitchfork;

    if (strlen(str) && ((str == "planks") || (str == "heap")
        || (str == "pile")))
    {
        if (planks)
        {
            if ((fork))
            {
                pitchfork = clone_object(THIS_DIR + "obj/pitch_fork");
                pitchfork->move(TO);
                fork = 0;
                write("You move the pile of planks a bit to the left " +
                    "and spot something in the dark soil below. You " +
                    "bend down and see its an old pitch fork laying " +
                    "here alone on the ground.\n");
                say(QCTNAME(TP) + " bends down and pushes the planks " +
                    "over a bit to the left and gets a surprised look " +
                    "in " +TP->query_possessive()+ " face.\n");
                return 1;
            }
            write("You push around the planks on the floor. How boring.\n");
            return 1;
        }
        return 0;
    }
    return 0;
}


string
desc_heap()
{
    string text;

    if ((planks) > 2)
    {
        text = "The heap consists of a few old wooden planks. " +
            "They seem completely useless though, as time has " +
            "taken its tribute to them. No wonder they where " +
            "left here.\n";
        return text;
    }
    if (planks == 2)
    {
        text = "Two wooden planks have been thrown into a corner. " +
            "They seem completely useless though as time has " +
            "taken its tribute to them. No wonder they where " +
            "left here.\n";
        return text;
    }
    if (planks == 1)
    {
        text = "You see a single wooden plank on the ground. " +
            "Around the plank the ground is darker which makes " +
            "you draw the conclusion that there where more " +
            "planks here not long ago.\n";
        return text;
    }

    text = "What? \n";
    return text;
}

string
desc_soil()
{
    string text;

       text = "The floor is made of hard packed soil stamped into " +
            "a hard surface. Scattered around are a few straws. ";

        if ((planks) > 2)
        {
            text += "In a corner you spot a few wooden planks in " +
                "a pile on the floor.\n";
            return text;
        }

        if (planks == 2)
        {
            text += "A couple of planks lie on the ground in a " +
                "corner.\n";
            return text;
        }
        if (planks == 1)
        {
            text += "You see a single wooden plank on the grund. " +
                "Around the plank the ground is darker which " +
                "makes you draw the conclusion that there where " +
                "more planks here not long ago.\n";
        return text;
        }
        if (fork)
        {
            text += "In the soil below the last plank you spot a " +
                    "hidden pitch fork";
            return text;
        }
        text += "\n";
        return text;
}

int
query_planks()
{
    return planks;
}

int
query_fork()
{
    return fork;
}

string
search_eq(object player, string str)
{
    object ob;

    if (planks)

    switch (str)
    {
        case ("planks"):
        case ("heap"):
        case ("pile"):
        {
            write("After your close examination of the planks " +
                "you draw the conclusion that they are old, " +
                "rotten and probably of no use at all. The " +
                "only thing your examination didnt tell was " +
                "the weight of a plank but to figure out that, " +
                "without guessing, you better get a plank " +
                "from the pile.\n");
            break;
            }
        default:
            return "";
    }
}
