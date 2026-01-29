/*  /d/Faerun/sea/whalebones/rooms/cliff.c
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
#define CLIFF ROOM_DIR + "cliff"

//calls do_climb to check if climb syntax has been entered
int do_climb(string str);

void
create_whaleb_outdoor()
{
    extraline = "Seaside wind tears at the clothes on your back as you clin"
        +"g on with fingertips and toes. Muscles scream in pain with the ef"
        +"fort to remain in place.";
    set_short("Dangling for life halfway up a cliff");

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
    if(parse_command(str, ({}), "'down'")){
        if (this_player()->resolve_task(TASK_CLIMBUP, ({SKILL_WEIGHT,
            XDEX, TS_DEX, SKILL_END, SKILL_1, SKILL_2})) > 0)
        {
            write("You climb down the rugged stone cliff.\n");
            tell_room(ROOM_DIR + "cliff", QCTNAME(this_player()) + " clim"
                +"bs down the rugged stone cliff.\n");
            this_player()->move_living("M", ROOM_DIR + "beach3", 1, 0);
            tell_room(ROOM_DIR + "beach3", QCTNAME(this_player()) + " arr"
                +"ives climbing down the side of the cliff.\n");
        }else{

            write("You try to climb down, but you slip and tumble down in"
                +"stead. OUCH!\n");
            tell_room(ROOM_DIR + "cliff", QCTNAME(this_player()) + " lose"
                +"s their grip and tumbles down the rugged stone cliff.\n");
            this_player()->move_living("M", ROOM_DIR + "beach3", 1, 0);
            set_alarm(1.0, 0.0, &tell_room(ROOM_DIR + "beach3",
                QCTNAME(this_player()) + " arrives tumbling down the side"
                +" of the cliff. OUCH!\n"));
            this_player()->heal_hp(-300);
        }
        return 1;
    }


    else if(!parse_command(str, ({}), " [up] [the] [tall] [stone] [rugged] "
        +"[rocky] 'cliff' / 'cliffs'"))
    {
        write("Climb where?\n");
        return 1;
    }

    else{

    if (this_player()->resolve_task(TASK_CLIMBUP, ({SKILL_WEIGHT, XDEX,
        TS_DEX, SKILL_END, SKILL_1, SKILL_2})) > 0)
    {
        write("You climb up the rugged stone cliff.\n");
        tell_room(ROOM_DIR + "cliff", QCTNAME(this_player()) + " climbs u"
            +"p the rugged stone cliff.\n");
        this_player()->move_living("M", ROOM_DIR + "ledge", 1, 0);
            tell_room(ROOM_DIR + "ledge", QCTNAME(this_player()) + " arri"
            +"ves climbing up the side of the cliff.\n");
        return 1;
    }
        set_alarm(1.0, 0.0, &write("You try to climb up the cliff, but "
            +"you lose your grip and tumble to the ground! OUCH!.\n"));
        this_player()->move_living("M", ROOM_DIR + "beach3", 1, 0);
        set_alarm(1.0, 0.0, &tell_room(ROOM_DIR + "beach3",
            QCTNAME(this_player()) + " arrives tumbling down the side of "
            +"the cliff. OUCH!\n"));
        this_player()->heal_hp(-300);
        return 1;
  }
}
