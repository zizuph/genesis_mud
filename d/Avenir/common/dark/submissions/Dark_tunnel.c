/*
 * File:          /d/Avenir/common/dark/submissions/Dark_tunnel.c
 * Creator:       Katrina
 * Date:          Tue Jul 13 08:20:02 1999
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#108131
 * Comments:      
 *                This is to be a small area when the strong
 *                and wise can try their luck at mining
 *                precious gems for themselves. The speed of
 *                ones mining should be dependent on strength
 *                of the individual and quality of tools used.
 *                The quality of gems should be based on ones
 *                wisdom of such topics, awareness to
 *                recognize the good veins of minerals, and
 *                maybe location sense to know which way to
 *                mine.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("Dark tunnel");
    set_long("You are stumbling along a roughly carven tunnel, "
        + "the sound of dripping water echoes back to you "
        + "from both directions.  Further along the passage "
        + "you notice a unwavering red-orange light that "
        + "seems to provide no heat to your current "
        + "surroundings.\n");

    add_item(({"tunnel","passage","wall","walls","floor","ceiling"}),
        "The jagged edges of rock along this tunnel lead "
        + "you to believe it was constructed rather hastily.\n");
    add_item(({"unwavering red-orange light","red-orange light","light"}),
        "You can not make out the source of this light from "
        + "here, the lack of a flicker in this light gives "
        + "you cause for suspicion.\n");
    add_item(({"water"," dripping water"}),
        "At seemingly random places along the tunnel, small "
        + "puddles of water collect from the constantly "
        + "leaking ceiling.\n");
    add_item(({"puddle","puddles"}),
        "Small puddles of chalky-looking water have "
        + "collected on the floor of this tunnel.\n");
    add_item(({"mud"," white mud"}),
        "A fine white mud that is cool to the touch.\n");
    add_item(({"rock"}),
        "The dark rock of these tunnels appears to be "
        + "flecked with precious stones.\n");
    add_item(({"precious stones"," flecks"}),
        "As you hold your light closer to walls of the "
        + "tunnel, you notice the distinguishing sparkle of "
        + "gems.\n");
    add_item(({"gem"," gems"}),
        "Small glimpses of gems can be seen still embedded "
        + "within the walls of these tunnels.\n");
    add_item(({"jagged edges of rock"," edges of rock"}),
        "Sharp chipped rock lines these tunnels, you can "
        + "even make out tool marks along the walls where "
        + "recent mining has taken place.\n");
    add_item(({"tool marks"," marks"}),
        "Deep scratches and grooves are apparent "
        + "everywhere, probably made with a pickaxe or rough "
        + "chisel.\n");
    add_cmd_item(({"puddle"," puddles"}),
        ({"step in"," jump in"," walk through"}),
        "Your feet get soaked by the water! A fine white "
        + "mud clings to the bottom of your feet.\n");
    add_cmd_item(({"gem"," gems"}),
        ({"mine"," mine for"}),
        "You scratch and claw at the walls of the tunnel "
        + "but do not manage to free up any precious stones.\n");


}
