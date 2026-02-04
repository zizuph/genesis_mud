/*
 * Lilith Dec 2021/Jan 2022: added more "sound" actions 
 *   to trigger opening to secret exit.
 *   Updated room desc to indicate there are good accoustics.
 */ 
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#define TP     this_player()
#define TO     this_object()

static int open = 0;

public void
create_room()
{
    set_short("Cave");
    set_long("Dirty and barren, this shaky rock cave seems to " +
             "have no importance. It does, however, seem to have "+
             "great accoustics.\n");

    add_prop(ROOM_I_LIGHT, -5);
    add_exit("cliff", "out", 0);
}

init()
{
    ::init();
    add_action("do_clap", "clap");
	add_action("do_clap", "shout");
	add_action("do_clap", "scream");
	add_action("do_clap", "stomp");
	add_action("do_clap", "whistle");
	add_action("do_clap", "yell");	
}

public int
do_clap(string str)
{
    tell_room(TO, "Sounds seem amplified in this space.\n");	
    set_alarm(1.5, -1.0, "secret");
}

public void
secret()
{
    if (open > 0) {
        tell_room(TO, "A secret passage closes.\n");
        remove_exit("north");
        open = 0;
        return;
    }
    tell_room(TO, "The vibration of the loud sound causes a "+
      "portion of the cave wall to crumble away.\nA secret "+
      "passage opens to the north.\n");
    add_exit("inner_cave", "north", 0);
    open = 1;
}


