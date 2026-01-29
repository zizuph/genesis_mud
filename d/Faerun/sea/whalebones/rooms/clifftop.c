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
//#define CLIFF ROOM_DIR + "cliff"

//calls do_climb to check if climb syntax has been entered
int do_climb(string str);

void
create_whaleb_outdoor()
{
    extraline = "Your feet are swallowed up by coarse brush and gras"
        +"s, so unlik"
        +"e the beach beneath you that for a moment you forget where you "
        +"are. The wind softly tickles your ear as you take in the view b"
        +"efore you. You clearly stand at the tallest point for miles and"
        +" your breath slows a fraction as you absorb your surroundings. "
        +"The crystalline blue water is broken by the odd streak of green"
        +" or brown, blending so subtly into the skyline that your entire"
        +" field of vision is the sea. The plateau extends further in a "
        +"westwardly direction. A Large hole lies to your west, which "
        +"exudes the distintive scent of ocean.";

    set_short("At the lip of a plateau overlooking a beach");

    add_item(({"sea", "ocean", "water"}),
        "Looking over the water, the view from here is breathtaking."
        +" Looking out over an endless canvas of blue you just see a "
        +"glimmer on the horizon which must be Sword coast.\n");

    add_item(({"plateau"}),"You stand on a rocky platau on Finback "
        +"Island.\n");

    add_item(({"mountain", "cliff"}), "A large craggy clifface pierces th"
        +"rough clouds to your southwest. Something feels off about it.\n");

    add_item(({"brush", "grass"}), "Dry scragly brush grabs at you"
        +"as you wade though it.\n");

    add_item(({"smell", "aroma", "air", "breeze"}), "The air here is clea"
         +"n and fresh, soothing a smile onto your face.\n");

    add_item(({"bones", "litter", "fragment", "fragments"}), "Fragments of"
         +" bones, shells and other various reffuse litter the beach far "
         +"below.\n");

    add_item(({"shore", "beach", "below"}), "You are standing on a platae"
        +"u on Finback Island, relieved to be away from the debris ridden"
        +"beach below you.\n");

    add_item(({"wave", "waves"}), "Briney white foaming waves ebb and flo"
        +"w, hauling debris further inland.\n");

    add_item(({"hole","rocks"}), "There is nothing too interesting about"
        +" this. You feel you should check back later.\n");

    add_room_tell("A sudden gust of wind nearly propells you off the cliffs ed"
        +"ge");

    add_room_tell("A soothing melody of lapping waves fills you with a "
        +"sense of calm.");

    add_room_tell("You percieve a slight shift in the direction of the wi"
        +"nd, pushing you closer towards the cliffs edge.");

    add_room_tell("A dark cloud gathers around the mountain... you look "
        +"again and it's gone, a trick of wind perhaps?");

    set_no_exit_msg( ({"east", "southeast", "south", "west", "northeast",
        "northwest"}), "There's nothing in that directi"
        +"ction except thin air. You decide against it.\n");

    set_no_exit_msg( ({"north"}),
        "The terrain appears quite rocky and hazardous in that"
        +" direction. You choose to save your ankles the trouble.\n");

    add_exit(ROOM_DIR + "15o.c", "northwest");
    add_exit(ROOM_DIR + "1o.c", "southwest");
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
            tell_room(ROOM_DIR + "ledge", QCTNAME(this_player()) + " arr"
                +"ives climbing down the side of the cliff.\n");
            this_player()->move_living("M", ROOM_DIR + "ledge", 1, 0);
            tell_room(ROOM_DIR + "clifftop", QCTNAME(this_player()) + " clim"
                +"bs down the rugged stone cliff.\n");
        }else{

            write("You try to climb down, but you slip and tumble down in"
                +"stead. OUCH!\n");
            set_alarm(1.0, 0.0, &tell_room(ROOM_DIR + "beach3",
                QCTNAME(this_player()) + " arrives tumbling down the side"
                +" of the cliff. OUCH!\n"));
            this_player()->move_living("M", ROOM_DIR + "beach3", 1, 0);
        tell_room(ROOM_DIR + "ledge", QCTNAME(this_player()) + " lose"
            +"s their grip and tumbles down the rugged stone cliff.\n");
            this_player()->heal_hp(-300);
        }
        return 1;
    }
}
