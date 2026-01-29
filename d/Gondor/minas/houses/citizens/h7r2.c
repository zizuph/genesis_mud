inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("dirty bedroom");
    set_long(BSN(
        "This bedroom further reflects the mess of the first room you " +
        "entered in this house. The single bed which sits here is " +
        "unmade. There are clothes strewn all about and a flask of " +
        "oil rests in the corner."));
    add_item(({"bed"}), BSN(
        "This bed looks large and comfortable. The sheets and blankets " +
        "are still rumpled and wrinkled from their last use, and it " +
        "seems that they are rarely, if ever, tidy. There are two " +
        "comfortable pillows resting haphazardly upon the bed."));
    add_item(({"sheets","blankets"}), BSN(
        "These sheets and blankets seem not to have been washed for some " +
        "time. How unclean!"));
    add_item(({"pillow","pillows"}), BSN(
        "These soft feather pillows appear most comfortable, but they, " +
        "like most everything in this dwelling, could use a thorough " +
        "washing."));
    add_item(({"clothes","clothing"}), BSN(
        "The clothing has been cast about with seeming abandon. It " +
        "looks as if the owner is merely very lazy, as there is a " +
        "great volume of clothing strewn across the room, enough " +
        "for many days of clean clothes."));
    add_item(({"flask","oil flask"}), BSN(
        "This flask seems to have been spilled and quickly righted, " +
        "as it rests amid oil-stained clothing. It appears that " +
        "the flask was overturned and the ensuing mess was hastily " +
        "cleaned using some of the clothing which was conveniently " +
        "resting on the nearby floor."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(1);
    set_side("south");
    set_circle("Third Circle");

    add_walls("There are unsightly marks upon the wall.");
    add_ceiling("The ceiling is peaked in this house.");
    add_floor("There are clothes strewn all over the floor.");

    add_lamp();

    add_exit(MINAS_DIR + "houses/citizens/h7r1ss3crc3","north",0,0);
}
