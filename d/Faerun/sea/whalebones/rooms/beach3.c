/*  /d/Faerun/sea/whalebones/rooms/beach3.c
 *
 *   By Nucifera, 2020
 *
 */

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <terrain.h>
#include "defs.h"
#include <tasks.h>

inherit BASE_WHALEB_OUTDOOR;

#define SKILL_1 104 /* climb skill, aka, SS_CLIMB */
#define SKILL_2 106 /* locaiton sense skill, aka, SS_LOC_SENSE */
#define TASK_CLIMBUP 300 /* difficulty of the task, see <man tasks> */
#define XDEX 5 /* Only 5% of dexterity counts towards the task! */
//#define CLIFF ROOM_DIR + "cliff"

//calls do_climb to check if climb syntax has been entered
int do_climb(string str);


void
create_whaleb_outdoor()
{
    extraline = "There is a gentle "
        +"crunch underfoot of shells and the remains of various sea life"
        +". Columns of skeletal substance from large seaborne vertebrate "
        +"have scattered themselves along the entire length of coast "
        +"around you. Waves from the Sea of Swords grow choppy as they la"
        +"p at the debris strewn shore of Finback Island.";

    set_short("Somewhere on the narrow bone littered beach of Finback "
        +"island");

    add_item(({"path", "footsteps"}), "There is not a footstep in sight o"
        +"n this sandy wasteland but your own.");

    add_item(({"floor", "ground"}),
        "Your immered to the ankle in sand, pebbles, and other debris dep"
        +"osited by the ebbing water. A You notice weathered bone fragmen"
        +"ts by your feet.\n");

    add_item(({"crunch","sand"}), "Bones and shells produce a distinct cr"
        +"unching sound underfoot.\n");

    add_item(({"shell", "shells"}), "Shells of every shape and color, or "
        +"atleast fragments which look like shells are inundated in the c"
        +"oarse grey-tinged sand.\n");

    add_item(({"sea","water"}),"Flawless turquoise water forming the "
        +"Sea of Swords to your east is broken by choppy white waves as t"
        +"hey aproach the shore at your feet.\n");

    add_item(({"bone", "bones", "substance", "substances", "vertebrate"}),
        "You identify them as the weathered bone structures of massive se"
        +"aborne mammals.\n");

    add_item(({"driftwood"}),"A collection of the remains from shaped pie"
        +"ces of timber and bazaarly knotted remains of organic debris ar"
        +"e haphazardly scattered between the bones and shells.\n");

    add_item(({"debris","reffuse","flotsam"}), "Reffuse and flotsam dragg"
        +"ed in my the foaming water litter the beach.\n");

    add_item(({"pebbles"}), "Pebbles and assorted rocks broken away from "
        +"the cliff to your west produce the course sand beneath you.\n");

    add_item(({"fragment", "fragments"}), "Fragments of bones, shells and"
        +"other various reffuse litter the shore.\n");

    add_item(({"cliff","cliffs"}), "The sheer vertical mass of rock besid"
        +"e you has been weathered away over time to an almost completely"
        +" smooth wall. Your keen eyes notice a rocky ledge just above he"
        +"ad height\n");

    add_item(({"shore", "beach"}), "You are standing on the southeastern"
        +"shore of Finback Island, and the Sea of Swords is to your"
        +" east.\n");

    add_item(({"wave", "waves"}), "Briney white foaming waves ebb and flo"
        +"w, hauling debris further inland.\n");

    add_room_tell("The stomach-churning aroma of rotting sea life drifts "
        +"past you. ");

    add_room_tell("Salty sea spray from a large wave hit's you square in "
        +"the face. Ouch!");

    add_room_tell("The soothing melody of lapping waves fills you with a "
        +"sense of calm.");

    set_no_exit_msg( ({"northwest", "west", "north"}), "There is a cl"
        +"iff in the way. You decided it is too risky to climb a horizontal"
        +" face of rock.\n");

    set_no_exit_msg( ({"west"}), "OUCH!! You walk "
        +"straight into a jagged cliff-face.\n");

    set_no_exit_msg( ({"east", "southeast", "south"}), "Break"
       +"ing waves deter you from moving in that direction.\n");

    add_exit(ROOM_DIR + "beach2.c", "northeast");
    add_exit(ROOM_DIR + "beach4.c", "southwest");

    reset_faerun_room();
}
void
reset_faerun_room()
{
    set_searched(0);
}

void
init()
{
    ::init();
    //adds action climb to the room
    add_action("do_climb", "climb");
}

//function which defines climbing functionality
int
do_climb(string str)
{
    //if function is triggered with phrase 'climb', but nothing else
    if(!str)
    {
        write("What did you want to climb? The cliff?\n");
        return 1;
    }
    //if function triggered but wrong climb syntax
    if(!parse_command(str, ({}), " [up] [the] [tall] [stone] [rugged] "
        +"[rocky] 'cliff' / 'cliffs'"))
    {
        write("Climb where?\n");
        return 1;
    }
    if (this_player()->resolve_task(TASK_CLIMBUP, ({SKILL_WEIGHT, XDEX,
        TS_DEX, SKILL_END, SKILL_1, SKILL_2})) > 0)
    {
        write("You climb up the rugged stone cliff.\n");
        tell_room(ROOM_DIR + "ledge", QCTNAME(this_player()) + " arrives climbing " +
            "up the side of the cliff.\n");
        this_player()->move_living("M", ROOM_DIR + "ledge", 1, 0);
        tell_room(this_object(), QCTNAME(this_player()) + " climbs up " +
            "the rugged stone cliff.\n");
        return 1;
    }
    set_alarm(1.0, 0.0, &write("You try to climb up the cliff, but " +
        "you lose your grip and tumble to the ground! OUCH!.\n"));
    set_alarm(1.0, 0.0, &tell_room(this_object(), QCTNAME(this_player()) +
        " tries to climb up the cliff but slips and falls!"));
    this_player()->heal_hp(-300);
        return 1;
}
