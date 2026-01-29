#pragma strict_types

#include "defs.h"
#include <ss_types.h>
inherit "/std/room";
#include "/d/Krynn/common/herbsearch.h"

#define LIVE_I_WARNED_JUMP "_live_i_warned_jump"
#define FALL_DAMAGE(x) (-3000 + (x->query_base_stat(SS_DEX) * 3) + \
            (x->query_skill(SS_ACROBAT) * 4))

public void reset_herb_room();
public void reset_room();
public string check_timber();
public string exa_timber();
public void create_room();
public void init();
public int do_jump(string str);
public int do_climb(string str);

public void
reset_herb_room()
{
    set_searched(1);
}

public void
reset_room()
{
    reset_herb_room();
}

public string
check_timber()
{
    if ((RUIN + "timber")->query_broken())
        return "Projecting slightly from the rubble of " +
            "the tower, you can see a broken timber reaching " +
            "out towards you, but it's far too short to " +
            "be of any use in getting out of this " +
            "treetop.";
    return "Projecting a fair distance from the rubble of " +
        "the tower, you can see a long timber reaching " +
        "out horizontally, ending fairly close to the " +
        "treetop you're in.";
}

public string
exa_timber()
{
    string str;

    str = "Jutting out from the end of the tower that " +
        "hangs over the wall of the ravine, the timber " +
        "is nothing more than the dried-out remains of " +
        "what was probably support for the tower roof. ";
    if ((RUIN + "timber")->query_broken())
        str += "It, however, has broken fairly close to " +
            "the rubble, and is much to far away to " +
            "safely jump to.\n";
    else if (stringp((RUIN + "timber")->check_break(TP)))
        str += (string)(RUIN + "timber")->check_break(TP);
    else
        str += "It's not in the best of condition, but " +
            "you think you might be safely able to jump " +
            "across to it.\n";

    return str;
}

public void
create_room()
{
    set_short("among the branches of an ancient tree");
    set_long("You are amidst the branches of an ancient " +
        "tree, decrepit, dried and withered in its age. " +
        "It's very tall, in fact looking down makes you " +
        "a bit dizzy, and appears to have once been an " +
        "evergreen of some sort. Now, however, its " +
        "skeletal branches are devoid of any greenery, " +
        "and are garbed only in thick beards of greenish " +
        "grey moss. @@check_timber@@\n\n");
    add_item(({"forest", "trees"}),
        "A fair-sized forest of similar " +
        "trees spreads out around you to the north, " +
        "filling the void of a vast ravine here.\n");
    add_item(({"ravine"}), "The " +
        "southern edge of the ravine, a steep-sided " +
        "cliff, rises just to the south, it's uppermost " +
        "edge approximately level with your position. " +
        "Reaching out from the edge of the cliff, the ruins " +
        "of a tower sprawl over the edge.\n");
    add_item(({"timber"}), "@@exa_timber");
    add_item(({"branch", "branches"}),
        "The branches of the tree are dead, and look " +
        "too much like bones for comfort, clad now only " +
        "in scaley grey bark, and thick beards of moss.\n");
    add_item(({"bark", "grey bark", "scaley grey bark"}),
        "The bark once must have been quite healthy for " +
        "the tree to grow this tall, but now it looks like " +
        "a massive scab covering the tree.\n");
    add_item(({"moss", "beard", "beards of moss", "beards"}),
        "Thick greenish-grey moss covers almost everything " +
        "in sight here.\n");

    add_prop(OBJ_I_SEARCH_TIME, 10);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_herb_file(OBJ + "vamp_moss");

    reset_room();
}

public void
init()
{
    ::init();
    add_action(do_jump, "jump");
    add_action(do_climb, "climb");
}

public int
do_jump(string str)
{
  /* Note: No default notify_fail to keep players from */
  /* realizing there's a special jump here unless they */
  /* are actually trying to jump to a specific place. */
    if (!str || !strlen(str))
        return 0;

    if (member_array(str, ({"to timber", "timber",
        "on timber", "onto timber", "over to timber"}))
         < 0)
    {
        notify_fail("Jump where?\n");
        return 0;
    }

    if ((RUIN + "timber")->query_broken())
    {
        if (!TP->query_prop(LIVE_I_WARNED_JUMP))
        {
            write("The timber has broken off awfully short, " +
                "are you sure you want to try it?\n");
            TP->add_prop(LIVE_I_WARNED_JUMP, 1);
            return 1;
        }
        else
        {
            write("Despite your better judgement, you " +
                "decide to attempt the jump anyway. You " +
                "concentrate on the distance between you " +
                "and the timber for a moment, then jump " +
                "as far as you can. Unfortunately, " +
                "your best wasn't enough! You undershoot " +
                "the timber and sail beneath it, crashing " +
                "into the cliff face and dropping downwards " +
                "helplessly onto a jagged ledge.\n");
            say(QCTNAME(TP) + " narrows " + 
                TP->query_possessive() + " eyes, judging " +
                "the distance between here and the timber. " +
                "Suddenly " + TP->query_pronoun() + " " +
                "leaps far out across the gap between " +
                "here and the timber, but doesn't quite " +
                "make it. You watch in shock as " + 
                TP->query_pronoun() + " sails under the " +
                "end of the timber, crashes against the " +
                "cliff face, and plummets around twenty " +
                "or twenty-five feet down onto a jagged " +
                "ledge on the cliff face, about halfway " +
                "down to the ravine floor.\n");
            TP->move_living("M", RAVINE + "ledge");
            say("You hear a scream from above growing " +
                "louder, and suddenly " + QNAME(TP) + " " +
                "comes crashing down through the trees, " +
                "hitting the ground with a sickening thud.\n");
            TP->heal_hp(FALL_DAMAGE(TP));
            if (TP->query_hp() <= 0)
            {
                write("You hear a thunderous CRACK! from the " +
                    "vicinity of your neck as you hit the " +
                    "ground.\n");
                TP->do_die(TO);
            }
            TP->remove_prop(LIVE_I_WARNED_JUMP);
            return 1;
        }
    }            
    else
    {
        write("You concentrate on the distance between you " +
            "and the timber for a moment, then jump " +
            "as far as you can. Your heart leaps into your " +
            "throat, as for a moment, it looks like you won't " +
            "make it, but at the last moment you manage to " +
            "catch hold of the timber and climb on.\n");
        say(QCTNAME(TP) + " narrows " + 
            TP->query_possessive() + " eyes, judging " +
            "the distance between here and the timber. " +
            "Suddenly " + TP->query_pronoun() + " " +
            "leaps far out across the gap between " +
            "here and the timber, narrowly managing to " +
            "catch hold of it and climb on.\n");
        TP->move_living("M", RUIN + "timber", 1, 0);
        say(QCNAME(TP) + " suddenly comes flying through " +
            "the air from a nearby tree, and lands awkwardly " +
            "on the edge of the timber.\n");
        return 1;
    }
    return 0;
}

public int
do_climb(string str)
{
    notify_fail("Climb where?\n");

    if (!str || !strlen(str))
        return 0;

    if (str == "down" || str == "down tree")
    {
        write("You start to look for a safe handhold " +
            "to climb down, then realize it's a miracle " +
            "you haven't fallen down, as the branches of " +
            "this tree seem barely able to support their " +
            "own weight, let alone yours. You decide " +
            "against pushing your luck and change your mind " +
            "about climbing.\n");
        return 1;
    }

    return 0;
}
