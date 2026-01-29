/*
 * File:          /d/Avenir/common/dark/submissions/water_room.c
 * Creator:       Caw
 * Date:          Tue Mar  2 01:17:23 1999
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#86868
 *                Added by Cirion on 1999.03.01
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
inherit "/d/Avenir/inherit/room";


#include "/d/Avenir/common/dark/dark.h"  

void
create_domain_room ()
{
    set_short("Inside the pillar");
    set_long("The noise in this room is deafening and the light "
        + "is so bright its hard to make out many details. The "
        + "floor and ceiling are crafted from two circular "
        + "slabs of stone. They are joined together by a "
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
    add_item(({"slab","stone","marble","gray marble","circular slab"}),
        "The floor and ceiling are circular slabs of gray marble.\n");
    add_item(({"floor"}),
        "The floor is a circular slab of gray marble "
        + "affixed to the pillar by some unknown means.\n");
    add_item(({"ceiling"}),
        "The ceiling is a circular slab of gray marble, "
        + "probably with a conical top to help part the "
        + "waters of this great underground waterfall.\n");
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
        + "chamber. But from in here they seem larger than "
        + "life, and are moving as if they were truly "
        + "alive. You watch in amazement at the battle "
        + "unfolds around you. The ogres are engaged in "
        + "combat by a band of veiled warriors who attack "
        + "from out of the shadows. They begin "
        + "dispatching the ogres with lethal ease. Then they "
        + "disappear again as swiftly as they appeared and "
        + "the ogres are left dead and dying. The image "
        + "begins to fade again and the curtain is again "
        + "just falling water.\n");
    add_item(({"ogres"}),
        "Staring though the water you can see the unearthly "
        + "creatures being killed by the veiled warriors.\n");
    add_item(({"warriors"}),
        "The images through the water shows the warriors "
        + "flowing among the ogres with a grace bordering on "
        + "the preternatural. The are dispatching the ogres "
        + "with ease.\n");
    add_cmd_item(({"wall","walls","water"}),
        ({"touch","feel"}),
        "Your hand is jerked down by the flow of the water "
        + "and you are nearly pulled from the room.\n");
    add_cmd_item(({"pillar","crystal","altar"}),
        ({"touch","feel"}),
        "The stone is cool to the touch and very smooth "
        + "except for where the carvings mar the surface.\n");


    clone_object(OBJ + "schlachlil_altar")->move(this_object(), 1);
}

void
remove_blind(object who)
{
    who->add_prop(LIVE_I_BLIND,
	who->query_prop(LIVE_I_BLIND) - 1);
    who->catch_tell("Your vision slowly returns...\n");
    who->command("look"); // tell them to take a look at the room
}

void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    // blind livings who enter, for a short time
    if(living(to))
    {
        to->catch_tell("You are suddenly engulfed in blindingly "
            + "bright white light.\n");
	to->add_prop(LIVE_I_BLIND,
	    to->query_prop(LIVE_I_BLIND) + 1);
        set_alarm(20.0 + itof(random(20)), 0.0, &remove_blind(to));
    }

}

int
do_jump(string str)
{
    write("You jump down off the platform, through the water, and "
        + "fall a short distance to the ground.\n");
    say(QCTNAME(this_player()) + " jumps down off the platform and "
        + "through the sheet of water.\n");
    this_player()->move_living("M", L2 + "water_pillar", 1, 1);
    say(QCTNAME(this_player()) + " falls onto the floor from within "
        + "the water pillar above.\n");
    return 1;
}

int
do_climb(string str)
{
    notify_fail("Climb what?\n");
    if(!strlen(str))
        return 0;

    if((str != "down") && (str != "chain") && (str != "chains"))
        return 0;

    write("You manage to climb down the wet chain, through the sheet of falling "
        + "water, and drop down to the floor.\n");
    say(QCTNAME(this_player()) + " climbs along the chain through the "
        + "sheet of falling water.\n");
    this_player()->move_living("M", L2 + "water_pillar", 1, 1);
    say(QCNAME(this_player()) + " climbs out of the water pillar along "
        + "one of the chains, and drops down to the floor.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_climb, "climb");
    add_action(do_jump, "jump");
}
