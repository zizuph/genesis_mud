/*
 * File:          /d/Avenir/common/dark/submissions/Water_pillar.c
 * Creator:       Caw
 * Date:          Tue Mar  2 00:20:02 1999
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#86868
 * Comments:      
 *                This is a resubmission to fix some typos and
 *                other odds and ends in the room. See the
 *                "Inside the pillar." Room for information
 *                concerning entering it from this room.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("Water pillar");
    set_long("This massive chamber is dominated by a huge pillar "
        + "of water that falls from a hole in the center of "
        + "the domed ceiling and falls into a larger hole in "
        + "the floor. That cavern itself is perfectly round "
        + "with a high domed ceiling. The pillar of water "
        + "glows with an eerily perfect white light. The "
        + "wavering light cast by the pillar causes shadows "
        + "to move around the bas-relief carvings on the "
        + "wall that makes them seem almost alive.\n");

    add_item(({"pillar","water","waterfall"}),
        "The pillar of water falls from a large round hole "
        + "in the ceiling way above you. A eerie white light "
        + "shine forth from it. You notice that four chains "
        + "come out of the pillar and are attached to the "
        + "wall around the room.\n");
    add_item(({"wall","walls"}),
        "The walls are a dark gray marble that has been "
        + "carved all around with a bas-relief battle scene "
        + "depicting veiled warriors fighting against hordes "
        + "of ogres. Four chains are mounted high on the "
        + "wall and go into the pillar of water.\n");
    add_item(({"carvings","scene","battle"}),
        "The scene seems to show the battle between a band "
        + "of veiled warriors against a horde of ogres. "
        + "Although outnumbered the warriors seem to be "
        + "easily dispatching the ogres as a large number "
        + "are depicted with mortal wounds or already dead. "
        + "The warriors seem to be flowing with a beautiful "
        + "grace and confidence, their weapons flashing and "
        + "capes flowing out behind them. The wavering light "
        + "cast by the pillar makes the shadows among the "
        + "figures flicker causing them to seem alive with "
        + "movement.\n");
    add_item(({"warriors"}),
        "The veiled warriors are superbly crafted making "
        + "them seem to be almost alive when the shadows "
        + "move around them. They seem to be in the midst of "
        + "a beautiful flowing dance full of grace and "
        + "death.\n");
    add_item(({"chain","chains"}),
        "The chains a mounted high on the walls in four "
        + "places around the room. They slope downward "
        + "towards the pillar entering it a little above eye "
        + "level. The chains are crafted from a black metal "
        + "that seems to have just come from the forge. No "
        + "rust is evident despite what must have been years "
        + "exposed to the waters.\n");
    add_item(({"ogres"}),
        "The ogres are depicted as large fearful looking "
        + "creatures. But many are shown dead or dyeing at "
        + "the hands of the warriors.\n");
    add_item(({"floor"}),
        "The floor is slick from the dampness of the room "
        + "and the water the splashes from the pillar. It "
        + "slopes slightly towards the center to allow the "
        + "water to drain into the hole in floor.\n");
    add_item(({"hole"}),
        "Which hole? The one in the ceiling or the floor?\n");
    add_item(({"ceiling hole"}),
        "The water falls from this hole that is in the "
        + "center of the ceiling.\n");
    add_item(({"floor hole"}),
        "The hole in the floor is larger then the pillar of "
        + "water. The pillar is about ten feet from the edge "
        + "of the hole. Looking down you see nothing other "
        + "then the walls of the hole and the pillar of "
        + "water until the light grows too dim far below.\n");
    add_item(({"ceiling"}),
        "The ceiling is domed with a large hole in the "
        + "center from which the pillar of water flows.\n");
    add_cmd_item(({"wall","walls","carvings","warriors"}),
        ({"touch","feel"}),
        "The stone feels soft and warm despite the chill "
        + "air.\n");
    add_cmd_item(({"ogre","ogres"}),
        ({"touch","feel"}),
        "The stone feels rough and damp.\n");


}
/*
 * File:          /d/Avenir/common/dark/submissions/Water_pillar.c
 * Creator:       Caw
 * Date:          Tue Mar  2 01:17:23 1999
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#86868
 * Comments:      
 *                To enter this room the person would have to
 *                jump to the chain in the water pillar room,
 *                and then climb it. The climbing across
 *                should be an incremented thing with the
 *                climber receiving several messages along the
 *                way. Such as "The water buffets around you
 *                nearly making you loss your grip." And "The
 *                water pulls at you making it hard to hold
 *                onto the chain." Etc.  Once they reach the
 *                room. They should get a message that the
 *                bright light blinds them. At which point
 *                they cant see anything. Slowly vision
 *                returns as the acclimate to the light.
 *                Receiving messages like "As your eyes adjust
 *                you begin to make out some shapes." The
 *                pillar is an altar to Schlachlil, and can be
 *                worshiped like the altars of Hizarbin and
 *                Aclolthayr. The effect if any I will leave
 *                to you. Perhaps allowing the people to see
 *                in darkness for a short time. Or a piece of
 *                crystal come from the pillar and they can
 *                take it. And it will provide light for
 *                awhile. Should you decide to make this whole
 *                process dangerous, instead of death. Someone
 *                that falls could find themselves washed up
 *                near a river somewhere in Terel.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("Inside the pillar");
    set_long("The noise in this room is deafening and the light "
        + "so bright its hard to make out many details. The "
        + "floor and ceiling are crafted from two circular "
        + "slabs of stone. They are join together by a "
        + "pillar of crystal in the center of the room. The "
        + "pillar is the source of the light and is hard to "
        + "look at for long. You can see four chains "
        + "attached to the pillar about halfway up. Perhaps "
        + "the most interesting part of the room is the "
        + "outer wall which are curtains of falling water.\n");

    add_item(({"walls","wall"}),
        "The wall of water circling the room is caused by "
        + "the ceiling of the room parting the waterfall "
        + "creating a relatively safe room here in the "
        + "center. The flow of the water is dangerously "
        + "fast. You can see some faint images through the "
        + "waters.\n");
    add_item(({"floor"}),
        "The floor is a circular slab of gray marble "
        + "affixed to the pillar by some unknown means.\n");
    add_item(({"ceiling"}),
        "The ceiling is a circular slab of gray marble, "
        + "probably with a conical top to help part the "
        + "waters of this great underground waterfall.\n");
    add_item(({"pillar","crystal","altar"}),
        "The pillar is nearly 20 feet tall and is crafted "
        + "from a white crystal that glows with a painfully "
        + "bright white light. Your eyes begin to water from "
        + "looking at it. You do notice some carvings on its "
        + "surface that are a little less brilliant then the "
        + "rest of the crystal. You see four chains attached "
        + "to the pillar that lead out of the room through "
        + "the waters.\n");
    add_item(({"carvings","words"}),
        "They are hard to make out do to the brightness of "
        + "the light, but you notice a character that "
        + "represents Schlachlil.\n");
    add_item(({"chains"}),
        "You remember these chains well from having just "
        + "climbed across them to reach this room. They are "
        + "crafted from a black metal, they gave you a "
        + "surprisingly firm gripping surface despite the "
        + "waters.\n");
    add_item(({"character"}),
        "The character appears to be a stylized "
        + "representation of a crystal.\n");
    add_item(({"images"}),
        "After squinting for several minutes the images "
        + "start to become clearer. They are that of the "
        + "carvings that adorn the walls in the outer "
        + "chamber. But from in here they seem larger then "
        + "life, and are moving as if they where truly "
        + "alive. You watch in amazement at the battle "
        + "unfolds around you. The Warriors are engaged in "
        + "combat by a band of veiled warriors who attack "
        + "from out of the shadows. They begin killing "
        + "dispatching the ogres with lethal ease. Then they "
        + "disappear again as swiftly as they appeared and "
        + "the ogres are left dead and dying. The image "
        + "begins to fade again and the curtain is again "
        + "just falling water, obviously some magics are in "
        + "effect here.\n");
    add_item(({"ogres"}),
        "Staring though the water you can see the unearthly "
        + "creatures being killed by the veiled warriors.\n");
    add_item(({"warriors"}),
        "The images through the water shows the warriors "
        + "flowing among the ogres with a grace bordering on "
        + "the preternatural . The are dispatching the ogres "
        + "with ease.\n");
    add_cmd_item(({"wall","walls","water"}),
        ({"touch","feel"}),
        "Your hand is jerked down by the flow of the water "
        + "and you are nearly pulled from the room.\n");
    add_cmd_item(({"pillar","crystal","altar"}),
        ({"touch","feel"}),
        "The stone is cool to the touch and very smooth "
        + "except for where the carvings mar the surface.\n");


}
