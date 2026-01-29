/* /d/Faerun/guilds/fire_knives/rooms/h5.c
 *
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Before a thick marble column");

    set_long("The hallway widens around a thick "
    +"marble column to your north, "
    +"as if embracing its commanding structure. "
    +"As it does so, it splits into "
    +"the northeast and northwest in equal "
    +"passageways. Narrowing to the south, "
    +"the hall comes to a halt at the top of "
    +"a stairway partially covered in "
    +"flickering shadows cast by the light of "
    +"the torches hanging on every wall. "
    +"Soft carpets begin at the base of the "
    +"stairs, covering the otherwise cold, "
    +"stone floor.\n");

    add_item(({"column","thick column","marble column",
    "thick marble column"}),
    "Before you directly to the north rises from "
    +"the bottom of the floor a tall "
    +"and wide marble column that claims all "
    +"around it to itself. It seems to "
    +"protrude from the very stone as if it had grown "
    +"from it or the halls in "
    +"which you walk around in were carved out "
    +"of it with absolute precision. "
    +"Its smooth surface bears no markings "
    +"whatsoever, appearing instead to be "
    +"waxed and polished by hard-working hands. "
    +"The width makes it impossible "
    +"to see what lies on the various sides around "
    +"it, reflecting instead "
    +"the light of the flickering torches, "
    +"illuminating the area. Following its "
    +"surface reaching upwards is impossible, "
    +"its top reach obscured by the "
    +"enveloping shadows in the ceiling. \n");

    add_item(({"passageways","passageway","passage","hallway"}),
    "The passageways are formed by the split around the marble column.\n "
    +"They extend from this point to the northwest and northeast.\n");

    add_item(({"hall","stairway","stairs","steps"}),
    "Narrowing to the south, the hall comes to a full stop at the top of "
    +"a stairway partially covered in flickering shadows.\n");

    add_item(({"sconces","sconce"}),
    "The sconces are placed at an equal distant to "
    +"each other along the walls that "
    +"extend from the bottom of the stairs southwards. "
    +"Inside each one of them are "
    +"torches.\n");

    add_item(({"torch","torches"}),
    "Inside each one of the sconces along the wall "
    +"is a torch, currently lit.\n");

    add_item(({"floor","carpet", "carpets"}),
    "The floor is covered in soft carpets "
    +"beginning at the base of the stairs, "
    +"muffling the sound of steps and isolating the cold, stone floor.\n");

    add_item(({"wall","walls"}),
    "The stone cold walls seem smooth and clean, "
    +"the distances between its parts "
    +"marked only by equidistant sconces in which "
    +"torches are placed. In between "
    +"them is a thickly framed high portrait.\n");

    add_item(({"portrait","portaits"}),
    "In between each space inside two sconces is a "
    +"thickly framed high portrait. "
    +"A total of two portraits can be seen here: one "
    +"to the left, and another to "
    +"the right.\n");

    add_item(({"left portrait"}),
    "The portrait to the left depicts a round-faced, black-skinned human "
    +"with a thick brown goatee on a face frozen in an eternal scowl.\n"
    +"Below the portrait is a golden plaque.\n");

    add_item(({"right portrait"}),
    "The portrait to the right depicts a thin-faced woman of blue skin "
    +"and long auburn hair dangling in tattered ropes over an imperial "
    +"cape.\n"
    +"Below the portrait is a silver plaque.\n");

    add_item(({"golden plaque"}),
    "The golden plaque reads: Kalam.\n");

    add_item(({"silver plaque"}),
    "The silver plaque reads: Lorn.\n");

    add_item(({"plaque","plaques"}),
    "There are two of them underneath each one of "
    +"the portraits: the one to the left "
    +"is golden while the one to the right is silver.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "h8.c", "south");
    add_exit(FIREKNIVES_ROOMS_DIR + "h6.c", "northwest");
    add_exit(FIREKNIVES_ROOMS_DIR + "h4.c", "northeast");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
