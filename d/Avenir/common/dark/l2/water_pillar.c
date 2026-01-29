/*
 * File:          /d/Avenir/common/dark/submissions/water_pillar.c
 * Creator:       Caw
 * Date:          Thu Feb 25 01:54:01 1999
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#611091
 *                Added by Cirion on 1999.02.25
 * Comments:      
 *                The chains are suspending a platform in the
 *                center of the pillar that has a glowwing
 *                crystal pillar (the source of the light)
 *                going up from it a short distance to support
 *                a roof that parts the water and gives a
 *                place to stand, basically creating a room
 *                within the pillar that has a stone ceiling
 *                and floor and water walls. This room could
 *                be an altar to one of the gods, perhaps
 *                Hizarbin or Schlachlil. Or perhaps the
 *                resting place of a quest item or just about
 *                anything else. To reach the room a person
 *                would have to jump to the chain and move
 *                along it. Obviously rather dangerous ;) So
 *                it sould be something worthwild inside. Let
 *                me just say that allowing people to submit
 *                ideals like this is very cool. Thanks, Caw.
 */
inherit "/std/room";
#include "../dark.h"
#include <tasks.h>

void
create_room ()
{
    set_short("water pillar");
    set_long("This massive chamber is dominated by a huge pillar "
        + "of water that falls from a hole in the center of "
        + "the domed ceiling and falls into a larger hole in "
        + "the floor. That cavern itself is perfectly round "
        + "with a high domed ceiling. The pillar of water "
        + "glows with an eerily perfect white light. The "
        + "wavering light cast by the pillar causes shadows "
        + "to move around the bas-relief carvings on the "
        + "wall that makes them seem almost alive. An opening in "
        + "the northwest wall leads into the dark tunnels.\n");

    add_exit("s5", "northwest");

    add_item(({"pillar","water","waterfall"}),
        "The pillar of water falls from a large round hole "
        + "in the ceiling way above you. An eerie white light "
        + "shines forth from it. You notice that four chains "
        + "come out of the pillar and are attached to the "
        + "wall around the room.\n");
    add_item(({"wall","walls"}),
        "The walls are a dark gray marble that have been "
        + "carved all around with a bas-relief battle scene "
        + "depicting veiled warriors fighting against "
        + "hordes of ogres.\n");
    add_item(({"carvings","scene","battle"}),
        "The scene seems to show the battle between a band "
        + "of veiled warriors against a horde of ogres. "
        + "Although outnumbered the warriors seem to be "
        + "easily dispatching the ogres as a large number "
        + "are depicted with mortal wounds or already dead. "
        + "While the warriors seem to be moving with a "
        + "beautiful grace and confidence, their weapons "
        + "flashing and capes billowing out behind them. The "
        + "wavering light cast by the pillar makes the "
        + "shadows among the figures flicker causing them to "
        + "seem alive with movement.\n");
    add_item(({"warriors"}),
        "The veiled warriors are superbly crafted making "
        + "them seem to be almost alive when the shadows "
        + "move around them. They seem to be in the midst of "
        + "a beautiful swaying dance of grace and death.\n");
    add_item(({"chain","chains"}),
        "The chains are mounted high on the walls in four "
        + "places around the room. They slope downward "
        + "towards the pillar entering it a little above eye "
        + "level. The chains are crafted from a black metal "
        + "that seems to have just come from the forge. No "
        + "rust is evident despite what must have been years "
        + "of exposure to the water.\n");
    add_item(({"floor"}),
        "The floor is slick from the dampness of the room "
        + "and the water the splashes from the pillar. It "
        + "slopes slightly towards the center to allow the "
        + "water to drain into the hole in floor.\n");
    add_item(({"hole"}),
        "which hole?\n");
    add_item(({"ceiling hole"}),
        "The water falls from this hole that is in the "
        + "center of the ceiling.\n");
    add_item(({"floor hole"}),
        "The hole in the floor is larger then the pillar of "
        + "water. The pillar is about ten feet from the edge "
        + "of the hole. Looking down you see nothing other "
        + "than the walls of the hole and the pillar of "
        + "water until the light grows too dim far below.\n");
    add_item(({"ceiling"}),
        "The ceiling is domed with a large hole in the "
        + "center from which the pillar of water flows.\n");
    add_cmd_item(({"wall","walls","carvings","warriors"}),
        ({"touch","feel"}),
        "The stone feels soft and warm dispite the chill "
        + "air.\n");
    add_cmd_item(({"ogre","ogres"}),
        ({"touch","feel"}),
        "The stone feels rough and damp.\n");



}

int
do_climb(string str)
{
    notify_fail("Climb what?\n");
    if(!strlen(str))
        return 0;

    sscanf(str, "up %s", str); // parse out "up"
    sscanf(str, "the %s", str); // parse out "the"

    if((str != "up") && (str != "chain") && (str != "chains"))
        return 0;

    if ((this_player()->resolve_task(TASK_DIFFICULT, ({TS_STR, SS_CLIMB})) <= 0) ||
        (this_player()->query_fatigue() < 50)) // failed
        {
        write("You start to climb up the wet chain, but your hands slip "
            + "off and you fall back to the ground.\n");
        say(QCTNAME(this_player()) + " tries to climb up the chain, "
            + "but falls to the gound.\n");

        this_player()->add_fatigue(-50);
        return 1;
        }

    write("You manage to climb up the wet chain, through the sheet of falling "
        + "water, and into an area in the center of the water pillar.\n");
    say(QCTNAME(this_player()) + " climbs up along the chain through the "
        + "sheet of falling water.\n");
    this_player()->move_living("M", L2 + "water_room", 1, 1);
    say(QCNAME(this_player()) + " climbs along one of the chains and into "
        + "the room.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_climb, "climb");
}

