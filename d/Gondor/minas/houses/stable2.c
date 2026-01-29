/*
 *  /d/Gondor/minas/houses/stable2.c
 *
 *  Stable for the Steward's Mount
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
    set_short("The stable for the Steward's mount");
    set_long("This is a relatively small stable with room enough for "
        + "a single horse to live comfortably. The only horse stabled "
        + "here is that of the Lord Steward. The floor is covered "
        + "with deep straw and a window lets in a fresh breeze. Near "
        + "the gate, there is a bin for food and a basin for water.\n");

    add_item(({"stable"}), "This is a place where horses live.\n");
    add_item(({"floor", "straw"}), "The floor is covered by a thick "
        + "layer of fragrant straw. Be careful where you step, though, "
        + "as from the look of things the grooms have yet to clean the "
        + "stable today.\n");
    add_item(({"window"}), "The large square window set into the west "
        + "wall lets in a cool breeze of fresh air. This is not only "
        + "pleasant for the horse that lives here, but also for the "
        + "groomsmen who must work here.\n");
    add_item(({"insignia", "insignia of the house of stewards"}), "This is "
        + "also the insignia of the House of Hurin, who founded the House "
        + "of Stewards. All the Stewards, including Lord Denethor II "
        + "are descended in direct line from Hurin.\n");
    add_item(({"bin"}), "A large bin from which the resident horse may "
        + "eat. It is presently filled with oats.\n");
    add_item(({"oats"}), "Food for horses. It probably would not taste "
        + "very good to a person.\n");
    add_item(({"basin"}), "A rectangular basin made of stone. It is "
        + "presently half-filled with water. You may drink out of it if "
        + "the horse hair floating on the surface does not quench your "
        + "desire to do so.\n");
    add_item(({"horse hair", "hair"}), "It seems to be everywhere. There is "
        + "a particularly revolting film of it floating in the basin.\n");
    add_item(({"water"}), "The water in the basin does not look especially "
        + "inviting, but you may drink some if you wish.\n");

    set_drink_from("basin");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_INSIDE, 1);

    clone_object(INNER_MINAS + "/doors/stablegate_w1")->move(TO);
    clone_object(INNER_MINAS + "/npc/steward_horse")->move(TO);

    reset_room();

}

public void
init()
{
    ::init();
    init_drink();
}












