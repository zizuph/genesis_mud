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
inherit "/d/Avenir/inherit/avenir_time.c";
string desc_lake();
int horseshoe_in_place;
int query_shoe();


void
create_room()
{
    object chest;

    set_short("The tower room");
    set_long("This is the tower room of the mansion. " +
        "You look around through the windows to watch the " +
        "surrounding areas. This tower room must have " +
        "been the owners favourite place. The view is magnificent " +
        "and you can look out in all directions. There is a nice " +
        "smell of tared rope in the room.\n");
    add_item("floor","You cast a brief look and notice the floor " +
        "is made of thick wooden planks.\n");
    add_item(({"window","windows"}),"You examine the windows a bit " +
        "closer. There is one window in each wall of the tower " +
        "and above the windows someone has painted a landscape " +
        "with great care on the planks. The painting surrounds " +
        "the whole room. Below the painting and beside the " +
        "windows some fishing nets and various tared ropes " +
        "with beautiful knots hang. The one who designed this " +
        "was probably someone who loved the sea.\n");
    add_item("west window","@@desc_west_window");
    add_item("east window", "@@desc_east_window");
    add_item("north window", "@@desc_north_window");
    add_item("south window", "@@desc_south_window");
    add_item("nail","@@desc_nail");
        add_item("handles","@@desc_handles");
    add_item("nets", "Small fishing nets hang on the wall " +
        "beside the windows. They are hung with great care " +
        "and build up to the fantastic feeling of the room.\n");
    add_item(({"ropes","knots","tared ropes"}),"Along the walls " +
        "some tared ropes are hung. Various knots have been tied " +
        "on them and you are amazed by the beauty of some of " +
        "them. You recognize a bowline, a sheet bend and the " +
        "square knot, but the rest are mysteries to you. Its the " +
        "tar smell from these ropes you felt as soon you " +
        "entered the tower room.\n");
    add_item("bowline", "The master knot of all knots. " +
        "You look at the loop at the end of the rope " +
        "and wonder how it can hold so tight and still be so " +
        "easy to loosen up if you want to untie it.\n");
    add_item("square knot", "The knot used by " +
        "sailors use to tie ropes together with ends of " +
        "equal size.\n");
    add_item("sheet bend", "This one is the knot used by " +
        "sailors to tie ropes together with ends of unequal " +
        "size.\n");
    add_item("painting", "You look closer at the landscape " +
        "painting on the wall. You " +
        "soon discover that it is some of the surroundings " +
        "that has been painted here on the wall as you can " +
        "see the tower you are standing in above some trees " +
        "on the west wall. There are no people you can see " +
        "but the details are stunning. Trees, a mill and a " +
        "house can be seen in different directions and you " +
        "get a feeling of being somewhere else. In another " +
        "place or time perhaps, but still close. Its hard " +
        "to remove your eyes from this awesome painting.\n");
    add_item(({"wall","walls"}),"You turn around to look at the " +
        "walls. They are all made of the same wooden planks as the " +
        "floor and each wall has a window in it.\n");
    add_item(({"planks","wooden planks"}),"Both the floor and the " +
        "walls are made from the same kind of wooden planks. Thick " +
        "planks made of pine. You stroke a plank and feel its smoothe " +
        "surface.\n");
    add_item(({"vanes"}),"The vanes is painted with great care and " +
        "the fine details amazes you.\n");
    add_item(({"rock"}),"The rock is painted with great care and " +
        "the fine details amazes you.\n");
    add_item(({"mill"}),"The mill is painted with great care and " +
        "the fine details amazes you.\n");
    add_item(({"house"}),"The house is painted with great care and " +
        "the fine details amazes you.\n");
    add_item(({"weathermill"}),"The weathermill is painted with great " +
        "care and the fine details amazes you.\n");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("stairs","down");

    reset_room();
}

void
reset_room()
{
    object chest, letter, pouch;

    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
        return;

    horseshoe_in_place = 0;
    chest = (present("_sailors_chest", TO));
    if (chest)
        chest->remove_object();
    chest = clone_object(THIS_DIR + "obj/chest");
    chest->move(TO, 1);
    add_item("small coin", "@@desc_coin");
    chest->add_prop("_ready", 1); // ready = no keyhole
    letter = clone_object(THIS_DIR + "obj/letter");
    letter->move(chest, 1);
    pouch = clone_object("/d/Avenir/common/bazaar/Obj/misc/gem_pouch");
    pouch->fill_pouch();
    pouch->move(chest, 1);
}

void
init()
{
    ::init();
    add_action("look_out","look");
    add_action("hang_horseshoe","hang");
    add_action("get_shoe","get");
    add_action("push_nail","push");
    add_action("push_nail","press");
    add_action("untie_knots","untie");
    add_action("turn_coin","turn");
    add_action("turn_coin","twist");
    add_action("turn_coin","press");

}

int
turn_coin(string str)
{

    if ((str == "small coin") && (!(query_shoe())))
    {
        write("You try to " +query_verb()+ " the small " +
            "coin on the chest. Alas, nothing you try " +
            "works. It is stuck there and nothing you try " +
            "could change this at the moment.\n");
        say(QCTNAME(TP) + " tries to manipulate a small " +
            "coin that is stuck on the chest.\n");
        return 1;
    }
    return 0;

}


string
desc_coin()
{
    string text;
    object chest;

    chest = (present("_sailors_chest", TO));
    if (chest->query_prop("_ready"))
    {
        return "It is made of a scented wooden round that is " +
            "filigreed at the edges. One side has the symbol of " +
            "Sybarus, the trefoil, in bas relief. The other side " +
            "you cannot see.\n";
    }
}

string
desc_handles()
{
    string text;
    object chest;

    chest = (present("_sailors_chest", TO));
    if (chest)
    {
        return "On each side of the chest are two sturdy " +
            "rope handles used to lift the chest. Now it " +
            "seems they are useless as the chest is secured " +
            "to the floor and cannot be moved from its place.\n";
    }
}

int
hang_horseshoe(string str)
{
    object horseshoe, chest, coin;

    notify_fail("Hang what where?");
    if (strlen(str) &&
        ((str == "horseshoe") || (str == "horseshoe on nail")))
    {
        horseshoe = (present("_horseshoe", TP));
        if (horseshoe)
        {
            if (query_shoe())
            {
                write("There is already a horseshoe hanging " +
                    "on the nail.\n");
                return 1;
            }
            write("You reach up and hang your horseshoe on the " +
                "nail above the south window.\n");
            say(QCTNAME(TP) + " reaches up and hangs a horseshoe " +
                "on the nail above the window in the south " +
                "wall.\n");
            horseshoe->remove_object();
            horseshoe_in_place = 1;
            chest = present("_sailors_chest", TO);
            if (chest && (chest->query_prop("_ready")))
            {
                chest->remove_prop("_ready"); // show keyhole
                tell_room(ENV(TP), "A soft click can be heard from " +
                    "the chest in the middle of the room and you " +
                    "also hear the sound of a small coin " +
                    "falls rolling down on the floor.\n");
                coin = clone_object("/d/Avenir/common/obj/syb_coin");
                coin->move(TO, 1);
            }
            return 1;
       }
       return 0;
   }
   return 0;
}


int
get_shoe(string str)
{
    object horseshoe;

    if ((str) && (str == "horseshoe"))
    {
        if (query_shoe())
        {
            write("You reach up and pick the horseshoe from " +
                "the nail.\n");
            say(QCTNAME(TP) + " reaches up and picks a horseshoe " +
                "from the nail it hangs on.\n");
            horseshoe = clone_object(THIS_DIR + "obj/horseshoe");
            horseshoe->move(TP, 1);
            horseshoe_in_place = 0;
            return 1;
        }
    }
    return 0;

}
int
look_out(string str)
{
    object yard, labal;

    if (strlen(str) && (str == "east"))
        {
            write(desc_lake());
            say(QCTNAME(TP) + " walks forward and looks "
                +str+ " through the window.\n");
            return 1;
        }

    if (strlen(str) && (str == "south" || str == "west"
        || str == "north") || (str == "out"))
    {
        write("You look " +str+ " through the " +str+ " window and " +
            "see the fantastic view of the surrounding area. ");
        say(QCTNAME(TP) + " walks forward and looks " +str+ " through " +
            "the window.\n");

        if (str == "south")
        {
            (THIS_DIR + "yard")->teleledningsanka();
            yard = find_object(THIS_DIR + "yard");
            labal = (present("_labal", yard));
            if (labal)
                write("Far down in the stable yard you see someone, " +
                    "but its hard to see who it is from up here.\n");
            else
                write("\n");
            return 1;
        }
        write("\n");
        return 1;
    }
    else
    {
        write("Look in which direction?\n");
        return 1;
    }
}


string
desc_lake()
{
    string text;

    text = "You look east and between the trees " +
        "on the east side of the house you see something " +
        "that looks like a lake. From up here its hard to " +
        "see how big it can be as you can only see a small " +
        "part of it.\n";
    return text;

}


string
desc_east_window()
{
    string text;

    say(QCTNAME(TP) + " walks up to the east window.\n");
    text = "You look at the east window. It " +
        "looks very much the same as the other windows. Above " +
        "it, on the painting that surrounds the tower room, " +
        "you see a huge rock hidden among some trees.\n";
    return text;
}

string
desc_west_window()
{
    string text;

    say(QCTNAME(TP) + " walks up to the west window.\n");
    text = "You look at the west window. It " +
        "looks very much the same as the other windows. Above " +
        "it, you see the tower you stand in on the painting that " +
        "surrounds the room.\n";
    return text;
}

string
desc_north_window()
{
    string text;

    say(QCTNAME(TP) + " walks up to the north window.\n");
    text = "You look at the north window. It " +
        "looks very much the same as the other windows. Above " +
        "it, on the painting that surrounds the tower room, " +
        "you see the vanes and the roof of a weathermill.\n";
    return text;
}

string
desc_south_window()
{
    string text;

    say(QCTNAME(TP) + " walks up to the south window.\n");
    text = "You look at the south window. It " +
        "looks very much the same as the other windows. Above " +
        "it, on the painting that surrounds the tower room, " +
        "you see a small house hidden in a grove with birches. " +
        "Above the painted house you see a small nail in " +
        "the wall.\n";
    return text;
}

string
desc_nail()
{
    string text;

    text = "Its a small nail hit into the wall. ";

    say(QCTNAME(TP) + " streches up and looks at " +
        "a spot above the south window.\n");
    if (query_shoe())
        text += "On the nail someone has hung a horseshoe " +
            "for luck. ";
    else
        text += "Right now the nail sits empty, but one " +
            "can see it has been used to hang something on. " +
            "Probably some charm for luck or some another " +
            "obscure object. Looking closer you see that the " +
            "paint around the nail has lost its touch in the " +
            "shape of an upside down U.";
    text += "\n";
    return text;

}

int
push_nail(string str)
{

    if (strlen(str) && (str == "nail"))
    {
        write("You reach up and try to push the nail. Alas, " +
            "nothing happens. It seems to be hit hard into " +
            "the wall. Still there is something unusual with " +
            "this nail.\n");
        say(QCTNAME(TP) + " reaches up and starts to push the " +
            "nail above the south window into the wall.\n");
        return 1;
    }
    return 0;
}

int
query_shoe()
{
    return horseshoe_in_place;
}

int
untie_knots(string str)
{
    if (strlen(str) && ((str == "knot") || (str == "knots") ||
        (str == "bowline") || (str == "square knot") || (str == "sheet bend")))
    {
        write("You decide to untie the knot, but when you grab the " +
            "rope you decide after all to leave it. Someone has " +
            "really made an effort to make this room special, " +
            "and you dont want to ruin his attempt.\n");
        return 1;
    }
    return 0;
}
