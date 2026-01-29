// file name:        /d/Avenir/common/port/port_room_s.c
// creator(s):       Ilyian, taken from code in Gondor written be Mercade with
//                   permission from Elessar on 18 January, 1995
// revision history: Denis, Sep'96: Renamed to port_room_s.c from silent_r.c,
//			            moved the room_tell here from port.h, etc.
// purpose:          50% silence in the room
// note:             To be inherited.
// bug(s):
// to-do:

# pragma strict_types
# include "port.h"
inherit PORT_ROOM;

/*
 * Only with a 50 percent change, you are heard in the area. The write,
 * return 1; construct is used to block speech etc. 
 */
int
do_no_sound_in_area(string str)
{
    if (random(100) < 50 && !this_player()->query_wiz_level())
    {
        write("The roar of the water drowns out all the sound " +
              "you try to make.\n");
        return 1;
    }

    return 0;
}

/*
 * Only with a 50 percent change, you are seen in the area. The write,
 * return 1; construct is used to block ponder etc. 
 */
int
do_no_vision_in_area(string str)
{
    if (random(100) < 50 && !this_player()->query_wiz_level())
    {
        write("The noise is so loud you cannot collect you thoughs " +
              "into any coherent order.\n");
        return 1;
    }

    return 0;
}

public void
init()
{
    ::init();

    /*
     * The next add_actions are to make sure that no sound is heard in this
     * area.
     */
    add_action(do_no_sound_in_area, "ask");
    add_action(do_no_sound_in_area, "cry");
    add_action(do_no_sound_in_area, "'", 1);
    add_action(do_no_sound_in_area, "say");
    add_action(do_no_sound_in_area, "rsay");
    add_action(do_no_sound_in_area, "grsay");
    add_action(do_no_sound_in_area, "scream");
    add_action(do_no_sound_in_area, "swear");
    add_action(do_no_sound_in_area, "shout");
    add_action(do_no_sound_in_area, "whisper");

   /*
     * These add_actions are to make sure that other people see you think
     * or ponder something as a way of communication.
     */
    add_action(do_no_vision_in_area, "ponder");
    add_action(do_no_vision_in_area, "think");
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
