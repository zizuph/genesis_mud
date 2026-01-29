inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("bedroom");
    set_long(BSN(
        "This small room is the bedroom of this house. It is not very " +
        "comfortable looking. You see a bucket against the wall and a " +
        "mattress on the floor. There is also a chest at the foot " +
        "of the bed."));

    add_item(({"bucket","wooden bucket"}), BSN(
        "This is a wooden bucket. It is empty, but it smells " +
        "horrible. You don't spend too long imagining what " +
        "goes into the bucket."));
    add_item(({"mattress","bed"}), BSN(
        "This mattress serves as the bed. It is not thick and " +
        "looks fairly uncomfortable. The cloth is rough and " +
        "worn and frayed at the edges."));
    add_item(({"chest","small chest","banded chest"}), BSN(
        "This small chest is banded with strips of leather " +
        "to keep it sturdy. It is battered but serviceable, " +
        "and it is the nicest furnishing in the room."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(0);
    set_side("south");
    set_circle("Second Circle");

    add_walls();
    add_ceiling("The ceiling slopes downward toward the west in " +
        "this room.");
    add_floor("There is an innocuous looking bucket on the floor.");

    add_exit(MINAS_DIR + "houses/citizens/h4r1salleycrc2","east",0,0);
}
