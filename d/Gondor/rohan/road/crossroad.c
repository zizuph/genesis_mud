/*
 *      /d/Gondor/rohan/road/crossroad.c
 *
 *      Modification log:
 *      26-Jan-1997, Olorin: General revision.
 *      31-May-2020, Raymundo: Changed RHARD to 0. Players were having 
 *                          unreasonable difficulty crossing the ford.
 */
#pragma strict_types
inherit "/d/Gondor/common/lib/roads.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define RHARD   0

public int     bridge_msg();
public void    reset_room();

static object  Warden;

public void
create_roads() 
{
    set_street("broad, stonelaid road");
    set_where("southwest");
    set_county("Eastfold");
    set_land("Rohan");
    set_mountain("White Mountains");
    set_vegetation("long, green grass");
    set_river_name("Snowbourn");
    set_rwhere("north");
    set_rhard(RHARD);

    set_extraline("Far north, the great plains of Rohan spread out. "
        + "The sound of running water that can be heard from the "
        + "north probably is the river Snowbourn. It continues to " 
        + "the southwest, and the riverbed there can be seen from "
        + "here. To the south the peaks of the White Mountains touch "
        + "the sky. By the foot of the mountains lies Edoras, the "
        + "capital of Rohan. The crossroad here is the beginning of "
        + "the Western turnpike, which connects Edoras with Minas "
        + "Tirith. A long road is leading east from here. To the "
        + "west, the road crosses the river Snowbourn on an ancient "
        + "stone bridge and loses itself in the distance.");
   
    add_exit(ROH_DIR + "road/graves", "south", 0,          2);
    add_exit(ROH_DIR + "road/er1",    "east",  0,          2);
    add_exit(ROH_DIR + "road/wr1",    "west",  bridge_msg, 2);
    add_exit(ROH_DIR + "plains/h08",  "north", crossing,   RHARD, 1);

    add_item(({"bridge","stone bridge"}),
        "To the west, the road crosses the river Snowbourn on an ancient stone bridge.\n");
    add_item(({"grove","willow","willows"}), BSN(
        "This is a grove of willows. A willow is a kind of tree. This "
            + "kind of tree has very long and thin branches. It grows near "
            + "water..."));
    add_item(({"edoras","town"}), BSN(
        "Edoras, the capital of Rohan, lies on a hill south of here. A mighty wall "
            + "encircles it. Within there rise the roofs of houses; and in the midst, set upon a green "
            + "terrace, there stands aloft a great hall of Men. It seems to be thatched with gold; "
            + "golden, too, are the posts to its doors."));
    add_item(({"stream","river","snowbourn"}), BSN(
        "The Snowbourn runs down swiftly into the plain, and here at the foot of the hills turns "
            + "to the east to feed the Entwash far off in its reed-choked "
            + "beds. To the north there is a ford across the stream between "
            + "low banks much trampled by the passage of horses."));
    add_item(({"ford"}), BSN(
        "Over the stream there is a ford between low banks much trampled by the passage of horses. Across the "
            + "ford, you can see the plains of Rohan stretch as far as you can see."));
   
    reset_room();
   
    (ROH_DIR + "plains/e14")->load_me();
    (ROH_DIR + "plains/l10")->load_me();
}

public void
reset_room()
{
    Warden = clone_npc(Warden, ROH_DIR + "npc/roadguard");

    if (!objectp(present("glove",TO)))
        clone_object(ARM_DIR + "fsglove")->move(TO);
    if (!objectp(present("sign")))
        clone_object(ROH_DIR + "road/road_sign")->move(TO);
}

public int
bridge_msg()
{
    write("You cross the river Snowbourn on a stone bridge.\n");
    return 0;
}
