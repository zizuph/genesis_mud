/*
 * Base file for the Barrow downs
 * Original concept and area by Dondon, October 1993
 * Expanded and enlarged by Finwe, December 2001
 * 2020-02-26 - Cotillion
 * - Restored to working order after undocumented change
 */

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

void create_barrow_room() {}
void make_grey_wights();
void make_black_wight();
void make_dark_wights();
void add_torch();


static string add_shaft_functions = "";

/*
 * cavern vars and routines
 */
int alarm_id;
int handle_status,  // status of handle 0 = it's not moved, 1 = moved
    handle_pulled,  // number of times handle moved with wights in room
    exit_status;    // exit open or closed. 0 = closed, 1 = open
void handle_moved();


//string what_time;

// We use 'create_Room' instead of 'create_shire_room' because
// this is an indoors room
public void create_room()
{
    set_short("A tunnel inside a barrow beneath the Downs");

    add_item(({"ground", "floor"}),
        "The ground is covered with crisscrossed stone blocks. " +
        "Once fine looking and smooth, the blocks are chipped and " +
        "cracked from countless centuries.\n");
    add_item(({"walls", "wall"}),
        "The walls are made of stone blocks. They are chipped and " +
        "cracked. Faint, painted decorations adorn the walls.\n");
    add_item(({"decorations", "faint painted decorations", "painted decorations",
            "faint, painted decorations"}),
        "The decorations are happy scenes of days long past, " +
        "probably of the people once buried here. Now, the " +
        "decorations are faded, leaving only a faint impression of " +
        "their glory.\n");
    add_item("ceiling",
        "The ceiling is rough looking. It is made from stone blocks " +
        "that are now cracked. Some roots hang from the ceiling " +
        "and have cracked the stone blocks leaving a rough looking " +
        "surface.\n");
    add_item("roots",
        "The roots are of various sizes. Some appear to be tree, " +
        "shrub, and grass roots.\n");
    add_item(({"stone blocks", "blocks", "stone block", "block",
            "stones", "stone"}),
        "The stone blocks are grey. They were once smooth and " +
        "level, but now are cracked and chipped from the passage " +
        "of time. They make up the walls, ceiling and floor.\n");
    add_item(({"piles of dirt", "piles of earth", "clods of dirt",
            "clods of earth", "dirt", "earth", "clods"}),
        "The piles of dirt are dark and lay in various sized " +
        "piles about the room. They have a rich, loamy look to them.\n");
    add_item(({"passage", "passageway", "tunnel", "tunnels"}),
        "The tunnel is deep inside the barrow. It is dark and gloomy. " +
        "The walls, floor, and ceiling are faced with stones that " +
        "are cracked with age.\n");
    add_item("wind",
        "The wind cannot be seen, but can be felt as it blows past you.\n");
    add_item(({"water", "dripping water"}),
        "It looks dark and filthy, dripping from the ceiling. The " +
        "water drips into the floor and disappears.\n");

    set_room_tell_time(60+random(120));
    add_room_tell("A cold breeze blows past you.");
    add_room_tell("A cold wind rushes past you.");
    add_room_tell("A feeling of death permeates the area.");
    add_room_tell("Something in the distance whispers: Come to me...");
    add_room_tell("Something in the distance whispers: Follow me. " +
        "I will reward you well.");
    add_room_tell("Water drips in the distance.");
    add_room_tell("Songs of torment echo from somewhere.");

    create_barrow_room();

    /* Let's hope this prevents the cloning problems. */
    setuid();
    seteuid(getuid());
}


string psg_desc1()
{
    return "A tunnel inside a barrow beneath the Downs. The " +
        "passage smells dusty and of death. It is cold, wet, and " +
        "gloomy. The walls are made of stone that is cracked and " +
        "crumbling. Roots grow from cracks in the ceiling. ";
}

string psg_desc2()
{
    return "This is beneath the Downs inside a dark tunnel. The " +
        "passage smells dusty and of death and the " +
        "walls are made of crumbly stone. Roots grow from cracks " +
        "in the ceiling in this cold and gloomy place. ";
}

string psg_desc3()
{
    return "Somewhere inside a dark tunnel beneath the Downs " +
        "east of the Great Forest. Roots grow from the ceiling, " +
        "pushing stones aside. The tunnel is dark and dank, an " +
        "evil and haunted place, some say. ";
}

string psg_desc4()
{
    return "You stand in a dark tunnel. The walls are made of " +
        "stones that are cracked and weathered from countless " +
        "ages. The passage is moist from dripping water and very " +
        "cold. ";
}

string psg_desc10()
{
    return "You stand under the barrows in a dark passage. This " +
        "looks like one of the oldest part of barrow as there are " +
        "few stones on the walls and roots hang everywhere from " +
        "the walls and roof.  ";
}

string psg_desc11()
{
    return "This is a dank, dark passage. The walls have collapsed " +
        "leaving little room to move about. The passage smells " +
        "really bad like an old grave. ";
}

string psg_desc12()
{
    return "The passageway ends here. It is fallen in on itself, " +
        "making movement difficult. There is barely enough room " +
        "to turn around and walk out of here. ";
}


public string long_desc()
{
    string desc;

    desc = CAP(query_short()) + ". ";

    if (strlen(extraline))
	    desc +=extraline;

    if (functionp(vbfc_extra))
	    desc +=vbfc_extra();

    return (desc);
}

void make_black_wight()
{
    object wight;

    if(!present("wight"))
    {
        wight = clone_object(DOWNS_NPC + "wight")->move(this_object());
        tell_room(TO,"An ink black mist fills the room, then coalesces " +
        "into a black barrow wight...\n");
    }
}


void make_grey_wights()
{
	object wight;
    int i;

    if (!present("wight"))
    {
        for (i=1; i<=3; i++ )
            wight = clone_object(DOWNS_NPC + "g_wight")->move(this_object());
        tell_room(TO,"A grey mist fills the room, then coalesces " +
            "into a grey barrow wight...\n");
    }
}


void make_dark_wights()
{
    object wight;
    int i;

    if(!present("wight"))
    {
        for (i=1; i<=4; i++ )
            wight = clone_object(DOWNS_NPC + "d_wight")->move(this_object());

        tell_room(TO,"A dark mist fills the room, then coalesces " +
        "into a dark barrow wight.\n");
    }
}


void add_torch()
{
    object torch;
  	if(!present("torch"))
        torch = clone_object(DOWNS_OBJ + "torch")->move(this_object());
}


/*
 * Function name : set_add_shaft_functions
 * Arguments     : str: none
 * Description   : adds functions to the shafts
 */

void set_add_shaft_functions()
{
    add_item(({"ladder", "iron ladder"}),
        "The iron ladder is securely attached to the wall. It is " +
        "rusty yet looks strong enough to support you. It leads " +
        "up into the darkness and probably out of the Barrow.\n");
    add_item(({"hole", "hole in the ceiling", "hole in ceiling"}),
        "The hole is gaping and takes up a large portion of the " +
        "ceiling. It is rough looking and leads back up into the Barrow.\n");
}

/*
 * routines for the caverns, moving handles, etc.
 */


/* Have to kill the wight or fool him (sneak, hide, or be invis) to go back south*/

int check_exit()
{
    if (!present ("wight"))
    {
        return 0;
    }
    else if (TP->query_skill(SS_SNEAK) > 30)
    {
        write(" You manage to sneak past the wight.\n");
        say(QCTNAME(TP)+" managed to sneak past the wight.\n");
        return 0;
    }
    else if (TP->query_skill(SS_HIDE) > 30)
    {
        write ("You manage to hide from the wight and escape.\n");
        say (QCTNAME(TP)+" hides and escapes the Wight's attention.\n");
        return 0;
    }

    write ("Wight rasps: Nothing leaves here alive...\n");
    say ("Wight bars " + QCTNAME(TP) + " from leaving.\n");
    return 1;
}

int check_handle()
{
    if (present ("wight"))
    {
        write("The wight blocks you from going there.\n");
        return 1;
    }

    if (exit_status==1)
    {
        write("\nYou fall through the hole into a dark shaft.\n\n");
        return 0;
    }

    write("There is no way to go there from here.\n");
    return 1;
}


int handle(string str)
{
    if (str == "handle" || str == "lever")
    {
        if (handle_status == 0) // handle not moved
        {
            if (!present("wight")) // no wights here
            {
            // Be strong, or teamed up with a strong guy
                if (TP->query_stat(SS_STR) < 40)
                {
                    write("The handle moves a little.\n");
                    return 1;
                }
                handle_status=1; // handle moved
                exit_status=1;
                handle_moved();
                return 1;
            }
            // nope, not strong enough or wight in room when handle moved.
            if (handle_pulled!=2)
            {
                write("The wight rasps: NOOOoooooo....\n"+
                    "The wight raises his voice to an urgent scream.\n");
                say("The wight stops " + QCTNAME(TP) + " from moving " +
                    "the handle.\n" +
                    "The wight raises his voice in a terrifying scream.\n");
                write("The wight touches the handle, freezing it in place.\n");
                alarm_id = set_alarm(3.0,0.0,"get_a_wight");
                handle_status = 0;
                return 1;
            }
            else
            {
                write("The wight rasps: You shall never get free...\n");
                write("The handle moves slightly, but remains in place.\n");
                handle_status = 0;
                return 1;
            }
        }
        write("The handle has already been moved, opening up an exit.\n");
        return 1;
    }
}

void handle_moved()
{
    write ( "You push and pull and drag....\n" +
        "Slowly, with a squeaking sound the handle moves. The " +
        "floor begins to crumble beneath your feet and a gaping " +
        "hole appears.\n");
    say ( QCTNAME(TP)+" pushes and pulls at the handle.\n" +
        "Slowly, with a squeaking sound the handle moves. The " +
        "floor beneath your feet begins to crumble away and a " +
        "gaping hole appears.\n");
    exit_status = 1;
}

get_a_wight()
{
    object wight;

    if (handle_pulled!=2)
    {   // only 3 per reset
        // Ordinarily we'd use make_black_wight() except that
        // won't clone a wight if there's one in the room, and
        // we want another to appear foolish morts who pull the
        // handle, so we clone it this way.
        wight = clone_object(DOWNS_NPC + "wight")->move(this_object());
        tell_room(TO,"An ink black mist fills the room, then coalesces " +
        "into a black barrow wight.\n");
        handle_pulled++;
//	    tell_room((TO), "A grey mist seeps up from the ground " +
//        "and coalesces into a wight.\n", wight);
	}
        remove_alarm(alarm_id);
}

// climb out of the shaft message
public int climb_out()
{
        write("\nYou climb out of the dark shaft.\n\n");
        return 0;
}
