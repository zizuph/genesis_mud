inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

int guard;     /* 1 if peephole is open
                  0 if peephole is closed */
void
reset_room()
{
    if (!present("guard"))
        room_add_object(G_MON + "guard", 1, 
            "The guard arrives for his shift.\n");
}

void
create_room()
{
    set_short("Guard Room");
    set_long(break_string(
"This is the main entrance to the secret location of the Blackhands thief " +
"guild.  This is the antechamber of a larger hall to the north, " + 
"with other exits leading off into adjoining rooms to the east and west." +
"  There are lanterns on the walls here, providing light.  " +
"Although this is a dirty, underground chamber, the walls are smooth and " +
"well polished.  It is as if someone had taken a great care in creating " +
"these halls, although now they are in a state of disrepair.\nThere is a " +
"closed, sturdy oak door to the south.\n", 78));

    add_exit(G_ROOMS + "master_room", "west", 0);
    add_exit(G_ROOMS + "pub", "east", 0);
    add_exit(G_ROOMS + "ghall1", "north", "@@block");

    add_item(({"door", "oak door", "sturdy door", "sturdy oak door"}),
        break_string(
"This is a sturdy oak door, reinforced with iron bands.  There is a peephole" +
" in the center of the door, at about eye-level.  This door looks as if it " +
"was made to keep out intruders.\n", 78));

    add_item("lock", "A standard dead bolt, operated soley by the guard.\n");

    add_item("peephole", "@@peep_desc");

    add_item(({"lanterns", "lantern"}), break_string(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n", 78));

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

string
peep_desc()
{
    if (guard) return "Its open, but the guard is in the way.\n";
    else return break_string(
"This is designed so people on the inside can see people on the outside.\n" +
"At the moment, it is closed.\n", 78);
}

int
block()
{
    if (MEMBER(TP)) return 0;
    if(TP->query_wiz_level())
    {
        write(BS("Only members of the guild are allowed that way, but " +
            "we'll make an exception just this once.\n"));
        return 0;
    }
    write("Only members of the guild are allowed that way.\n");
    return 1;
}

void
set_guard()
{
    if (guard) 
    {
        guard = 0;
        return;
    }
    else guard = 1;
}

void
init()
{
    ::init();
    add_action ("open", "open");
    add_action ("open", "unlock");
    add_action ("knock_door", "knock");
} 

int
knock_door(string str)
{
    notify_fail("Knock on what?\n");
    if (!str) return 0;
    if (str != "door" && str != "on door") return 0;
    write ("The door is so dense, it absorbs the impact.\n");
    return 1;
}

int
open (string str)
{
    notify_fail("Do what?\n");
    if (!str) return 0;
    if (str != "door" && str != "oak door" && str != "sturdy door" &&
        str != "sturdy oak door" && str != "peephole") return 0;
    if (str == "peephole")
    {
        write ("The guard won't let you touch that.\n");
        return 1;
    }
    write (break_string ("You unlock and open the door, quickly passing " +
        "through to the south.  You shut the door behind you.\n", 78));
    say (break_string (QCTNAME(this_player()) + " quickly opens the door " +
        " and passes through to the south, closing the door behind " +
        this_player()->query_objective() + ".  The guard locks the " +
        "door.\n", 78));
    tell_room(G_ROOMS + "guild_ent1", break_string("The door abruptly opens " +
        "and " + QTNAME(TP) + " arrives from the north.  " +
        capitalize(this_player()->query_pronoun()) + " closes the door behind " +
        this_player()->query_objective() + ".\n", 78));
    this_player()->move_living("M", G_ROOMS + "guild_ent1", 1);
    return 1;
}

void
check_players()
{
    int i;
    object *ob;
    ob = all_inventory();
    if (!present("guard", TO)) return;
    if (interactive(ob[i = random(sizeof(ob))]))
        set_this_player(ob[i]);
    else return;
    if (MEMBER(TP)) 
    {
        write ("The guard grunts at you, in recognition.\n");
        say ("The guard grunts at " + QTNAME(TP) + ", in recognition.\n");
        return;
    }
    write(BS("The guard looks at you very closely.  He says, 'Hey!  Your " +
        "not a Blackhand!  You don't belong here!'\n"));
    say(BS("The guard looks at " + QTNAME(TP) + ", and says, 'Hey! Your " +
        "not a Blackhand!  You don't belong here!'\n"));
    call_out("bonk_player", 3);
}

void
bonk_player()
{
    write(BS("Before you can escape, the guard hits you over the head " +
        "with the flat edge of his sword.  You quickly lose consiousness.\n"));
    say(BS("The guard takes out his sword, and bonks " + QTNAME(TP) + 
        " over the head with the flat edge of the blade.  " + QCTNAME(TP) +
        " sinks to the ground, unconsious.\nThe guard then picks up " +
        QTNAME(TP) + ", and throws " + TP->query_objective() + " over his " +
        "shoulder.\n"));
    TP->move(G_ROOMS + "uncon");
    call_out("whistle", 3);
}

void
whistle()
{
    tell_room(TO, "The guard lets out a shrill whistle.\n");
    call_out("go_to_jail", 3);
}

void
go_to_jail()
{
    tell_room(TO, "Another guard arrives.  The first guard leaves north, " +
        " carrying " + QCTNAME(TP) + "'s unconsious body with him.\n");
}
