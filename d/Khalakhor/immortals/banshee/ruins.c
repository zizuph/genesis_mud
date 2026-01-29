#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <ss_types.h>
#include "banshee.h"
#include "/d/Khalakhor/sys/defs.h"

#define CLIMB_REQ   100
#define ENTRANCE    "/d/Khalakhor/khail/battlefield"

inherit "/d/Khalakhor/std/room";

public void
create_khalakhor_room()
{
    set_short("subterranean ruins");
    set_long("You are in a large, subterranean cavern littered with " +
        "the broken remains of ancient buildings whose architecture " +
        "predates what you have seen in other places nearby. Judging " +
        "by the rubble, they appear to have been large buildings of "+
        "intricately carved white stone. The ground swells upwards "+
        "towards the center of the cavern, where a lone structure " +
        "still stands amidst this field of destruction. A thin " +
        "shaft of light slices through the stale air of the "+
        "chamber from a hole in the roof far above.\n");

    add_item(({"cavern"}), "The cavern is enormous, but appears to "+
        "be natural, as if the earth itself opened up and swallowed " +
        "whatever these ruins once were when they stood upon the " +
        "surface.\n");
    add_item(({"buildings"}), "Nothing but rubble remains of all but " +
        "the lone building atop the hill at the centre of the " +
        "cavern.\n");
    add_item(({"hole","light","shaft"}),
        "A small hole in the ceiling of the chamber, far above you, " +
        "serves as the only source of light in this dark room. Dust " +
        "that has lain still for hundreds of years swirls through " +
        "the shaft of light beaming down from the opening in the " +
        "occasional gust of wind that blows down fresh air. A steep " +
        "pile of rubble and earth lead up to the hole, and might " +
        "be possible to climb up.\n");
    add_item(({"pile","steep pile","pile of rubble and earth"}),
        "A steep pile of rubble and earth ascends from the floor of "+
        "the cavern upwards to a small hole in the ceiling. It " +
        "is very steep, and looks none too stable. Possible to climb, " +
        "yes, easy to climb, definately not, but it's the only " +
        "apparent way out of here.\n");
    add_item(({"ruins","rubble"}),
        "The floor of the cavern is littered with countless pieces of " +
        "rubble that once formed intricate buildings. The remains of " +
        "columns, statues and reliefs are present in abundance, among " +
        "the larger slabs that were possible walls and ceilings.\n");
    add_item(({"columns","remains of columns"}),
        "They range in size from pieces as slender as saplings to as "+
        "thick as the mighty oaks of the Druid groves.\n");
    add_item(({"statues","remains of statues"}),
        "The statues are so badly destroyed they are impossible to "+
        "recognize as anything but monsters of fantasy and ancient " +
        "times spoken of only by the great bards of the land.\n");
    add_item(({"reliefs","remains of reliefs"}),
        "At one time these fragments were part of intricate carvings " +
        "of some sort, but they are so badly destroyed it's impossible " +
        "to even hazard a guess at what they may have once depicted.\n");
    add_item(({"structure","lone structure"}),
        "In the center of the cavern rises the only surviving " +
        "structure of these ruins. Though you can see little from " +
        "here, it appears to be constructed entirely of thick " +
        "white columns supporting a peaked roof of heavy white stone. " +
        "No doorway is evident, as the open columns are all it has " +
        "for walls. Oddly enough, a sickly green light seems to " +
        "emanate from within.\n");

    add_prop(ROOM_I_INSIDE, 1);
}

public int
do_enter(string str)
{
    if (!str)
        return 0;

    if (!parse_command(str, TP, "[the] 'structure' / 'building'"))
        return 0;

    if (TP->query_stunned())
    {
        notify_fail("You attempt to enter the ancient structure, " +
            "but you are too stunned to move.\n");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(TP))
    {
        notify_fail("You can't see a damned thing, let alone move " +
            "around.\n");
        return 0;
    }

    write("Climbing over the various pieces of rubble standing between " +
        "you and the structure at the heart of the chamber, you ascend " +
        "the few steps from the ground and slip between the columns " +
        "into it's depths.\n");
    say("Climbing over the various pieces of rubble standing between " +
        HIM_HER(TP) + " and the structure at the heart of the chamber, " +
        QTNAME(TP) + " ascends the few steps from the ground and " +
        "slips between the columns into the building's depths.\n");
    TP->move_living("M", PATH + "structure");
    say(QCTNAME(TP) + " slips into the room between two columns.\n");
    return 1;
}

public int
do_climb(string str)
{
    int climb_chance,
        reducer;
    object *temp;

    NF("Climb where?\n");

    if (!str || !strlen(str))
        return 0;

    if (member_array(str, ({"up","out","up to hole","up pile","up the pile"})) < 0)
        return 0;

  /* Can't climb out if stunned. */
    if (TP->query_prop(LIVE_I_STUNNED))
    {
        write("You are too stunned to attempt the climb out!\n");
        return 1;
    }

  /* Can't climb out if can't see. */
    if (!CAN_SEE_IN_ROOM(TP))
    {
        write("You can't see a damned thing! How do you expect to "+
            "climb anywhere?\n");
        return 1;
    }

  /* Can't climb unless both hands are free. */
    if (sizeof(temp = TP->query_weapon(-1)))
    {
        TP->catch_msg("It's far too steep to climb without both " +
            "hands free, get rid of your " +
            COMPOSITE_WORDS(map(temp, &->short())) + "!\n");
        return 1;
    }

  /* Can't hide and climb at the same time. */
    if (TP->query_prop(OBJ_I_HIDE))
    {
        write("Unable to conceal yourself and climb at the same " +
            "time, you come out of hiding.\n");
        TP->reveal_me(1);
    }
       
  /* Always fail if fatigued. */
    if (TP->query_fatigue() <= (TP->query_max_fatigue()/10))
    {
        write("You struggle weakly to climb the pile of rubble, " +
            "but are far too exhausted, and fall back helplessly " +
            "to the cavern floor.\n");
        say(QCTNAME(TP) + " struggles weakly to climb the pile " +
            "of rubble, but appears to be completely exhausted, " +
            "and falls back helplessly to the cavern floor.\n");
        return 1;
    }

  /* Chance to fail if climb is too low. Always fail if skill < 20 */
    if (TP->query_skill(SS_CLIMB) < MIN(20,random(CLIMB_REQ)))
    {
        write("You try scrambling up the pile towards the hole in the " +
            "ceiling, but your climbing skill fails you and you slide " +
            "to the bottom in a heap after only a few feet.\n");
        say(QCTNAME(TP) + " tries scrambling up the pile towards the " +
            "hole in the ceiling, but " + HIS_HER(TP) + " climbing " +
            "skill fails " + HIM_HER(TP) + " and " + HE_SHE(TP) +
            " slides to the bottom in a heap after only a few feet.\n");
        TP->add_fatigue(-random(80));
        return 1;
    }

  /* Probably will fail if player is carrying too much weight. */
  /* Always fail if player has greater than 50% encumberance. */
    if (TP->query_encumberance_weight() > MIN(50,random(100)))
    {
        write("You try to haul yourself up the pile of rubble "+
            "towards the hole in the ceiling, but your strength " +
            "fails you and you lose your grip, sliding back to " +
            "the cavern floor!\n");
        say(QCTNAME(TP) + " hauls " + HIM_HER(TP) + "self up " +
            "the pile of rubble towards the hole in the ceiling " +
            "a few feet, then " + HIS_HER(TP) + " strength appears "+
            "to fail " + HIM_HER(TP) + " and " + HE_SHE(TP) +
            " falls to the cavern floor huffing and puffing.\n");
        TP->add_fatigue(-random(80));
        return 1;
    }

  /* If the player's drunk they'll never make it up. */
    if (TP->query_intoxicated()*100/TP->intoxicated_max() > (random(99)+1))
    {
        write("You start climbing up the pile of rubble towards the " +
            "hole in the ceiling, but suddenly everything lurches " +
            "to one side, the room starts spinning, and you find " +
            "yourself flat on your ass on the cavern floor. Amazing " +
            "what being drunk does to your climbing ability, isn't it?\n");
        say(QCTNAME(TP) + " starts climbing up the pile of rubble " +
            "towards the hole in the ceiling, but suddenly " +
            "gets a blank look on " + HIS_HER(TP) + " face and " +
            "drops backwards to the floor with a thud.\n");
        TP->add_fatigue(-random(80));
        return 1;
    }

    write("You slip a few times on loose rubble, but manage to drag " +
        "yourself up the pile and pull yourself up through the hole " +
        "in the ceiling of the cavern out into fresh air and daylight!\n");
    say(QCTNAME(TP) + " slips a few times on loose rubble, but " +
        "ultimately manages to drag " + HIM_HER(TP) + "self up the pile " +
        "and out the hole in the ceiling of the cavern!\n");
    set_dircmd("up");
    TP->move_living("M", ENTRANCE, 0, 0);
    say(QCTNAME(TP) + " pulls " + HIM_HER(TP) + "self out of the " +
        "dark hole at the base of the pillar with a grunt.\n");
    add_prop(ROOM_S_DIR, ({"up the pile of rubble",TP->query_race_name()}));
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_enter, "enter");
    add_action(do_climb, "climb");
}
