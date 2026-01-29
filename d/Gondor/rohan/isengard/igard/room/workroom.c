/*
 *  workroom.c
 *
 *  Work area for wizards in Isengard.
 *
 *  Last modified by Alto, 23 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define   CHAIR3_NAME     "third chair"
#define   CHAIR2_NAME     "second chair"
#define   CHAIR_NAME      "first chair"
#define   SAVE		(IGARD_TEXT + "guest_list")

public void    create_gondor();
public void    init();
public void    leave_inv(object ob, object dest);
public string  look_at(string arg);     /* VBFC for chairs */
public int     push_button(string str);
public int     add_guest(string name);
public int     remove_guest(string name);
public int     prevent_enter(object ob);

object button;
string *guests = ({});

int
prevent_enter(object ob)
{
    int     i;
    string name;
    object owner;

    name = ob->query_real_name();
    owner = find_player("alto");

    restore_object(SAVE);
    name = LOW(name);

    if (living(ob) == 0)
        {
        owner->catch_tell("A nonliving object entered the Isengard "
            + "workroom.\n");
        return 0;
        }

    if (ob->query_npc())
        {
        owner->catch_tell("A NPC object entered the Isengard workroom.\n");
        return 0;
        }

    if ((i = member_array(name, guests)) >= 0)
        {
        owner->catch_tell("A green light briefly flashes above the door.\n");
        ob->catch_tell("Welcome to the workroom of Isengard.\n");
        return 0;
        }

    if(present("_green_button_pushed_", TO))
        {
        owner->catch_tell("A yellow light briefly flashes above the door.\n");
        ob->catch_tell("You enter the workroom of Isengard.\n");
        return 0;
        }

    owner->catch_tell("A red light flashes above the door as " +
        CAP(name) + " tries to enter the Isengard workroom.\n");
        ob->catch_tell("It appears you are locked out of the Isengard "
            + "workroom.\n");
    return 1;
}

string
long_desc()
{
    return "This room overlooks Wizard's Vale in "
        + "the Gap of Rohan. The room is built into the eastern face of "
        + "the mountain over Nan Curunir, high above the ring wall of Isengard "
        + "below. The walls and floor are undecorated stone, although the "
        + "eastern wall is breached by a large window. In the middle of the "
        + "room are three comfortable chairs surrounding a sturdy oaken "
        + "table. There are no exits and the only way in or out of the room "
        + "is by means of teleportation.\n";
}

public void
create_gondor()
{
    string  name;

    set_short("The workroom of Isengard");
    set_long(&long_desc());

    add_chair(CHAIR3_NAME,
     "[down] [in] / [on] [the] [third] 'chair' / 'armchair'",
     1, "in");

    add_chair(CHAIR2_NAME,
     "[down] [in] / [on] [the] [second] 'chair' / 'armchair'",
     1, "in");

    add_chair(CHAIR_NAME,
     "[down] [in] / [on] [the] [first] 'chair' / 'armchair'",
     1, "in");

    add_item( ({ "first chair" }), &look_at(CHAIR_NAME) );

    add_item( ({ "second chair" }), &look_at(CHAIR2_NAME) );

    add_item( ({ "third chair" }), &look_at(CHAIR3_NAME) );

    add_item(({"room", "workroom", "headquarters", "surroundings",
        "area"}), long_desc);

    add_item(({"chairs", "comfortable chairs"}), 
        "Three comfortable chairs.\n");
    add_item(({"chair", "comfortable chair"}), 
        "Which one? There are three of them.\n");
    add_item(({"table", "oaken table", "oak table"}), "The grand "
        + "oaken table is surrounded by three comfortable chairs. "
        + "There are stacks upon stacks of scrolls and manuscripts "
        + "strung across its surface. There are two buttons mounted "
        + "beneath it on one side.\n");
    add_item(("surface of table"), "There are stacks upon stacks of "
        + "scrolls and manuscripts strung across its surface.\n");
    add_item(({"scroll", "scrolls", "handwriting"}), "The handwriting on "
        + "the scrolls "
        + "is flowing and spidery. Your eyes cross in an attempt to "
        + "make sense of them until you get a headache and give up.\n");
    add_item(({"manuscript", "manuscripts", "plans"}), "There are thousands "
        + "of manuscripts, which appear to outline the plans for a great "
        + "and expansive fortress.\n");
    add_item(({"wall", "walls"}), "Which one? There are "
        + "walls to the north, south, east and west.\n");
    add_item(({"north wall", "northern wall", "west wall", "western wall",
        "south wall", "southern wall"}), "This wall is unadorned stone.\n");
    add_item(({"floor", "ground", "ceiling", "roof"}), "It is unadorned "
        + "stone.\n");
    add_item(({"east wall", "eastern wall"}), "It is breached by a "
        + "large window.\n");
    add_item(({"window", "large window"}), "The window overlooks the "
        + "Wizard's Vale and ring wall of Isengard. You are high up in "
        + "the mountain Nan Curunir and gazing through the window "
        + "brings on the sudden disorientation of vertigo\n");
    add_item(({"mountain", "mountains", "face"}), "The room "
        + "is built into the mountain over Nan Curunir overlooking the "
        + "fastness of Isengard.\n");
    add_item(({"nan curunir"}), "The Nan Curunir is known among the "
        + "common folk as the Wizard's Vale.\n");
    add_item(({"wizard's vale", "vale", "plain", "fastness", "isengard"}),
        "Far below you is the fastness of Isengard. It is built in "
        + "the valley of Nan Curunir, with a ring wall running from "
        + "its northwest to southwest extremity. Within the ring wall is "
        + "a plain spanning one mile in all directions. In the center of "
        + "the plain is a tall tower.\n");
    add_item(({"gap", "gap of rohan", "rohan"}), "It spreads out below "
        + "the window. From here you can see the Wizard's Vale.\n");
    add_item(({"wall", "ring wall"}), "The great ring wall of Isengard "
        + "surrounds the plain within.\n");
    add_item(({"tower", "orthanc"}), "It is presently under construction, "
        + "which is why this workroom exists in the first place!\n");
    add_item(({"stone", "interior"}), "The stone surrounding you is part of "
        + "the mountain interior.\n");
        
    add_item(({"button", "buttons"}), "Which one? There are two of them, "
        + "one red and one green.\n");
    add_item(({"red button"}), "This button locks the workroom.\n");
    add_item(({"green button"}), "This button unlocks the workroom.\n");

    add_prop(ROOM_I_INSIDE, 0);

    FIX_EUID
    restore_object(SAVE);

}

/*
 * Function name:   init
 * Description :    mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();
    add_action("push_button", "push");
    add_action("push_button", "press");
    add_action("add_guest", "welcome");
    add_action("remove_guest", "unwelcome");
    init_room_chairs();  /* add chair verbs */
} /* init */

/*
 * Function name:   leave_inv
 * Description :    mask parent to be sure that departing players
 *             are removed from chair/sofa occupants
 */

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */

/*
 * Function name:   look_at
 * Description :    VBFC to describe chair/sofa + occupants
 */

public string
look_at(string arg)
{
    string chair_text;

    chair_text = "A comfortable looking chair to sit in while "
        + "working late into the night on the construction of "
        + "Isengard.\n";

    if (arg == CHAIR_NAME)
    {
     return chair_text + sitting_on_chair(CHAIR_NAME, this_player(), 0);
    }

    if (arg == CHAIR2_NAME)
    { 
     return chair_text + sitting_on_chair(CHAIR2_NAME, this_player(), 0);
    }

    if (arg == CHAIR3_NAME)
    {
     return chair_text + sitting_on_chair(CHAIR3_NAME, this_player(), 0);
    }
} /* look_at */


int
push_button(string str)
{
    object actor, greenb;
    actor = TP;

    if (!strlen(str))
        NF0("Push what?\n");

    if (TP->query_real_name() != "alto")
        {
        write("You try to push the button and get a quick magical shock. "
            + "Apparently that is Alto's way of saying 'hands off'.\n");
        say(QTNAME(actor) + " fiddles with something under the table "
            + "and quickly draws " + TP->query_possessive() + " hand "
            + "back in pain.\n");
        return 1;
        }

    switch (str)
    {
    case "button":
        NF0("Which button do you wish to push? The red or the green?\n");
    case "green button":
        if(present("_green_button_pushed_", TO))
        {
        actor->catch_tell("You already pushed the green button.\n");
        return 1;
        }

        write("You push the green button. Now anyone may enter.\n");
        say(QTNAME(actor) + " fiddles with something on under the table.\n");

        button = clone_object(IGARD_OBJ + "green_button_obj.c");
        button->move(TO);

        break;
    case "red button":
        write("You push the red button. Now only those on the guest "
            + "list may enter.\n");
        say(QTNAME(actor) + " fiddles with something under the table.\n");

        greenb = present("_green_button_pushed_", TO);
        greenb->remove_object();

        break;
    default:
        NF0("What do you want to push?\n");
    }        
    return 1;
}

int
add_guest(string name)
{
    int     i;
    object  who = this_interactive();

    restore_object(SAVE);

    guests += ({ name });

    save_object(SAVE);

    write("You add " + name + " to the guestlist.\n");

    return 1;
}

int
remove_guest(string name)
{
    int     i;
    object  who = this_interactive();

    restore_object(SAVE);
    name = LOW(name);
    if ((i = member_array(name, guests)) < 0)
        return 0;
    guests = exclude_array(guests, i, i);
    save_object(SAVE);

    write("You remove " + name + " from the guestlist.\n");

    return 1;

}


int
query_lock()
{
    int     i;
    object owner;

    owner = find_player("alto");

    if(present("_green_button_pushed_", TO))
        {
        return 0;
        }

    else
        {
        return 1;
        }

}

