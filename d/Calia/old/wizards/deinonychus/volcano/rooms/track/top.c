
/*  part of the track leading up to the volcano in the land of the dinosaurs
 
    coder(s):	Deinonychus
 
    history:	DD.MM.YY	what done			who did
		27.02.93	created				Deinonychus
 
    purpose:	none
    exits:	none
 
    objects:	none
    npcs:	none
 
    quests:	none
    special:	none
 
    to do:	none
    bug:	none known
*/
 
 
inherit "/std/room";
#include "track.h"
#include <stdproperties.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
create_room()
{
    set_short("Top of the volcano");
    set_long(BS("You're on the top of the volcano. " + 
        "You have a wonderful sight to the land below. " +
        "Southwards you see the mountains, westwards is a marvelous " +
        "flatland, to your north and to your east is a dark forest.\n" +
        "There's a huge hole leading down into the volcano.\n"));

    add_item("volcano", "Wow, you really made it! You're on the top.\n");
    add_item("track", DESC("track"));
    add_item("forest", DESC("forest"));
    add_item("flatland", DESC("flatland"));
    add_item("trees", DESC("trees"));
    add_item("bushes", DESC("bushes"));
    add_item("animal", DESC("animal"));
    add_item("mountains", DESC("mountains"));
    add_item("hole", BS("It's a large hole, what else did you expect to find "
        + "on the top of the volcano? Looking down into the darkness of the "
        + "hole gives you a bad feeling. It'll be quite easy to enter the "
        + "hole but you wonder if you could climb up again.\n"));

    add_exit(ROOM("track_40"), "north", 0);

    call_out("reset_room",1); 
}

/*****************************************************************************/

/*
 * Function name: init
 * Description:   adds some commands to the player
 * Arguments:     none
 * Returns:       nothing
 */

void
init()
{
    add_action("enter_hole","enter");
    ::init();
}

/*****************************************************************************/

/*
 * Function name: enter_hole
 * Description:   blocks players who have not enough courage
                  other players can enter the hole in the volcano
 * Arguments:     none
 * Returns:       1/0
 */

int 
enter_hole(string what)
{
    object player;

    if (what == "hole"){
        player = TP;
        if (player->resolve_task(TASK_ROUTINE,TS_DIS) > 0){
            write("With your heart in your pants you enter the hole.\n");
            player->move_living("into the hole in the volcano.\n", ROOM("hole"));
            return 1;
        }
        else{
            write("Maybe you shouldn't enter this hole.\n");
            return 1;
        }
    }
    else{
    	notify_fail("Enter what?");
    	return 0;
    }
}

/*****************************************************************************/

void
reset_room()
{
    object dinosaur;    /* object pointer of pteranodon (named Egghead)*/
    object egg;         /* object pointer of pteranodon egg */
    object sky;         /* object pointer of the room "sky" */
    object top;         /* object pointer of this room */
    
    top = TO;
    sky = find_object(ROOM("sky"));
    if(sky) 
        dinosaur = present("egghead",({top,sky}));
    else
        dinosaur = present("egghead",top);
    
    if (dinosaur) {
        if (present("egg",dinosaur) || dinosaur->query_name() == "corpse")
            ;
        else {
            egg = clone_object(OBJECTS + "ptegg");
            egg->move(dinosaur);
    	    return;
    	}
    }
    else {
        dinosaur = clone_object(MONSTERS + "pteranodon");
        egg = clone_object(OBJECTS + "ptegg");
        egg->move(dinosaur);
        dinosaur->move(TO);
        tell_room(TO, QCNAME(dinosaur) + " flies in.\n");
        return;
    }
}

