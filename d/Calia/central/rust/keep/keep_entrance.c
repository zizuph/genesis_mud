/* Created 29/9/98 by Bishop, of Calia. This is a room just
outside the keep protecting Rust. */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

create_room()
{
    set_short("Clearing outside the keep");

    set_long("You have arrived at a clearing in the great forest." +
        " To the east, partly concealed by tree branches and other" +
        " vegetation, stands a stone keep. It doesn't stand very" +
        " tall, but seems to be a pretty massive structure" +
        " nonetheless. A path trails into the dense underbrush to" +
        " the north, and going eest would take you to the gates of" +
        " the keep.\n");

    add_item(({"keep","stone keep"}), "The keep has been made out" +
        " of large stone blocks. It extends quite a bit back into" +
        " forest to the east, but seems to be only two stories" +
        " high. If anyone is standing at the barred" +
        " windows on the second floor, they would have a good view" +
        " of where you're standing.\n");
    add_item(({"great forest", "forest"}),"The great forest" +
        " extends in all directions beyond this clearing, but" +
        " seems particularly dense to the north.\n");
    add_item("clearing", "Someone must have cut down quite a few" +
        " trees to create this clearing.\n");
    add_item(({"branches", "tree branches", "vegetation"}), "It" +
        " seems likely that the branches and vegetation has been" +
        " used to camouflage the keep, so it wouldn't be obvious" +
        " from a distance.\n");
    add_item("underbrush","It's very dense, with many a sharp" + 
        " thorn.\n");
    add_item("gates","They appear to be made out of wood, but you" +
        " would need to move closer to get a good look.\n");

    add_prop(ROOM_I_HIDE, 40);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(KEEP+"keep_path2","north",0,1);
}
