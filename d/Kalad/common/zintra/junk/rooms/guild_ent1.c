inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

int guard;     /* 1 if peephole is open
                  0 if peephole is closed */
int knocked;   /* 1 when door has been knocked for the first time.  Prevents
                           two players from knocking at once.
                  0 when ready to be knocked */
void
create_room()
{
    set_short("Sturdy door");
    set_long(break_string(
"You have come to the end of a passage leading underground beneath the " +
"city of Kalad.  There are lanterns here on the walls, providing " +
"light.  There is also a note on the wall.\nThere is a closed, sturdy oak " +
"door to the north.\n", 78));


    add_exit(G_ROOMS + "passage", "south", 0);

    add_item(({"lanterns", "lantern"}), break_string(
"There are two, one on each wall.  They are providing a dim, flickering " +
"light.  They are firmly attached to the wall.\n", 78));

    add_item(({"knocker", "iron knocker"}), break_string(
"This is an iron knocker, attached to the door.  Perhaps you should knock it" +
" if you want to get in.\n", 78));

    add_item("peephole", "@@peep_desc");

    add_item(({"door", "oak door", "sturdy door", "sturdy oak door"}), 
        break_string(
"This is a sturdy oak door reinforced with iron bands.  There is a peephole " +
"in the center, at about eye-level.  There is a large iron knocker right " +
"below the peephole.  This door looks as if it was meant to keep out " +
"intruders.\n", 78));

    add_item("lock", "Funny, you don't see a lock on this side.  Hmmm...\n");

    add_item("note", break_string(
"Due to temporary lack of membership, the password is 'redrum.'  Just tell " +
"the guard that, when (and if) he prompts you.\n", 78));

    add_prop(ROOM_I_INSIDE, 1);
}

string
peep_desc()
{
    if (guard) return "The peephole is open, and you can see a shadowy " +
                      "figure behind it.\n";
    else return 
"This is designed so people on the inside can see people on the outside,\n" +
"such as yourself.  At the moment, it is closed.\n";
}

void
init()
{
    ::init();
    add_action("open", "open");
    add_action("knock_door", "knock");
    add_action("tell_guard", "tell");
}

int
open(string str)
{
    notify_fail("Open what?\n");
    if(!str) return 0;
    if(str != "peephole" && str != "door" && str != "oak door" && 
         str != "sturdy door" && str != "strudy oak door") return 0;
    if (str = "peephole") 
    {
        if (guard)
	{
            write ("The peephole is already open.\n");
             return 1;
        }
        write ("You can't see how to open the peephole from this side.\n");
        return 1;
    }
    write ("The door is locked.\n");
    return 1;
}

int
knock_door(string str)
{
    if (str == "door" || str == "on door")
    {
        notify_fail ("The door is so dense, it absorbs the impact.  " +
                     "Try using the knocker.\n");
        return 0;
    }
    if (str == "knocker" || str == "on door with knocker" ||
        str == "the knocker" )
    {
        write ("Knock knock knock.\n");
        say (QCTNAME(this_player()) + " knocks the knocker really hard.\n");
        tell_room (G_ROOMS + "guard_room", "You hear a rather loud knocking " +
                   "noise coming from the other side of the door.\n");
        if (knocked) return 1;
        knocked = 1;
        call_out("react", 5);
        return 1;
     }
    notify_fail("Knock on what?\n");
    return 0;
} 

void
react()
{
    call_other(G_ROOMS + "guard_room", "load_room_fun");
    if (!present ("guard", find_object(G_ROOMS + "guard_room"))) return;
    guard = 1;
    call_other(G_ROOMS + "guard_room", "set_guard");
    say ("The peephole slides open and someone says something to " +
         QCTNAME(this_player()) + ".\n");
    write ("The peephole sildes open.  A shadowy figure says, 'Tell me" +
            " the password.'\n");
    tell_room(G_ROOMS + "guard_room",
"The guard moves to the door.  He slides open the peephole and whispers\n" +
"something through it to someone on the other side.\n");
    call_out("end_react", 20);
}

void
end_react()
{
    if (guard)
    {
    say ("The guard shouts out obsenities through the peephole at " + 
         QCTNAME(this_player()) + ", and rudely snaps it shut.\n");
    write ("The guard shouts out obsenities through the peephole at " + 
            "you, and rudely snaps it shut.\n");
    tell_room(G_ROOMS + "guard_room", break_string( "The guard shouts out " +
        "obsenities through the peephole at someone, and rudely snaps it " +
        "shut.\n", 78));
    knocked = 0;
    guard = 0;
    call_other(G_ROOMS + "guard_room", "set_guard");
    }
    else return;
}

int
tell_guard(string str)
{
    notify_fail("Tell who what?\n");
    if (!str || str != "guard redrum") return 0;
    write( break_string( "The guard grunts in recognition, and opens the " +
        "door a tiny bit for you.  Its just enough to slip through, and you " +
        "do so.  The guard quickly closes the door behind you, and snaps " +
        "the peephole shut.\n", 78));
    say( break_string( "Quicker than you can react, the door suddenly opens " +
        "a crack.  After " + QTNAME(this_player()) + " slips through, the " +
        "door promptly closes behind " + this_player()->query_objective() +
        ".  The peephole snaps shut.\n", 78));
    tell_room(G_ROOMS + "guard_room", break_string( "The guard opens the " +
        "door a tiny bit.  " + QCTNAME(this_player()) + " slips through, " +
        "and the guard closes the door behind " + this_player()->
            query_objective() + ".  The guard closes the peephole.\n", 78));
    call_other(G_ROOMS + "guard_room", "set_guard");
    guard = 0;
    knocked = 0;
    this_player()->move_living("M", G_ROOMS + "guard_room", 1);
    return 1;
}
















