/*
    A mansion wing room. Mortricia 920906.
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

void
create_room()
{
    set_short("triangle room");
    set_long(BS(
        "You are standing in a very strange looking triangle room. " +
	    "Unlike all other rooms, this room has only three walls. The " +
	    "strangest feature is that the three walls have different " +
	    "colors... one is red, one is violet and the third is orange. " +
	    "The floor however is covered by a black carpet, whereas the " +
        "ceiling is painted in white. The colors confuse you so much " +
        "that you lose your orientation. The wooden floor creaks under " +
        "your weight, and the walls are draped with dust. Cobwebs are " +
        "everywhere.\n"
        ));

    add_item(({"carpet"}), BS(
        "It is a black carpet made out of fine wool. Once it was beatiful " +
        "but now not much is left of it.\n"
        ));

    add_item(({"floor"}), BS(
        "The floor is made of wooden boards which have shrunk in this " +
        "dry climate, hence leaving quite large gaps between the boards. " +
        "An old carpet lies on the floor.\n"
        ));

    add_item(({"wall", "walls"}), BS(
        "The dusty wooden walls have not been touched by human hands " +
        "for many years. There's nothing unusual about them except " +
	"for their colors.\n"
        ));

   add_item(({"web", "webs", "cobwebs", "cobweb"}), BS(
        "From the size of the cobwebs you realise that the creatures " +
        "who made them must be quite big.\n"
        ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(MANSION + "tri3", "red", 0);
    add_exit(MANSION + "tri5", "violet", 0);
    add_exit(DUSTDIR + "door_room", "orange", 0);
}

public int
check()
{
    if (this_player()->query_wiz_level()) return 0;
    write("This room has been closed temporarily.\n");
    return 1;
}
