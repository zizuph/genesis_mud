/*
 *  /d/Gondor/minas/houses/stable3.c
 *
 *  Stable for the King's Mount
 *
 *  Alto, 10 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_gondor()
{
    set_short("The stable for the King's mount");
    set_long("This is a relatively small stable with room enough for "
        + "a single horse to live comfortably, although there has not been a "
        + "horse stabled here for hundreds of years. It is therefore "
        + "somewhat surprising that the floor is covered "
        + "with fresh straw. A window lets in a fresh breeze. Near "
        + "the gate, there is a bin for food and a basin for water.\n");

    add_item(({"stable"}), "This is a place where horses used to live.\n");
    add_item(({"floor", "straw"}), "The floor is covered by a thick "
        + "layer of fragrant straw. No need to worry where you step, "
        + "though, because there have been no horses in this stable for "
        + "hundreds of years. Still the Stablemasters of Minas Tirith have "
        + "kept it ever ready for the return of the King.\n");
    add_item(({"window"}), "The large square window set into the north "
        + "wall lets in a cool breeze of fresh air.\n");
    add_item(({"insignia", "insignia of the house of elendil"}), "Seven white "
        + "stars over a white tree.\n");
    add_item(({"star", "stars"}), "The stars on the insignia of the House "
        + "of Elendil are white and many-rayed.\n");
    add_item(({"tree"}), "The tree on the insignia of the House of Elendil "
        + "is a symbol of the trees descended from Nimloth the Fair "
        + "which grew in Numenor of old.\n");
    add_item(({"bin"}), "A large bin from which a resident horse could "
        + "eat. It is kept filled with oats should the King return once "
        + "again.\n");
    add_item(({"oats"}), "Food for horses. It probably would not taste "
        + "very good to a person.\n");
    add_item(({"basin"}), "A rectangular basin made of stone. It is "
        + "presently completely filled with water. The water looks clean "
        + "and inviting.\n");
    add_item(({"horse hair", "hair"}), "To the sorrow of the Men of Gondor, there "
        + "has been none in this room for a very long time.\n");
    add_item(({"water"}), "The water is crystal-clear and cool. No doubt "
        + "it would satisfy the thirst of a weary traveller.\n");

    set_drink_from("basin");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_INSIDE, 1);

    clone_object(INNER_MINAS +"/doors/stablegate_n1")->move(TO);

    reset_room();

}

public void
init()
{
    ::init();
    init_drink();
}












