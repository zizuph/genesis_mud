/*
 * pedestal.c
 *
 * This is simply a 'container' that holds a sword. More explicitly,
 * it is a pedestal which stands in the depths of the ruins of Castle
 * Chimera, embedded within which is a sword. The sword can only be
 * released by weighting down 4 (of a possible 36) flagstones in the
 * floor of the chamber.
 *
 * Coded by Khail, December 23/96.
 */
#pragma strict_types

#include "defs.h"

inherit "/std/container";

object sword;
int sword_freed;

/*
 * Function name: reset_quest
 * Description  : Resets the pedestal 'locked' var, and clones
 *                a new sword.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_quest()
{
    seteuid(getuid());
    if (sword_freed)
        (SWORD_BRAIN)->reset_quest();
    sword_freed = 0;
    if (!sword || !present(sword, TO))
    {
        sword = clone_object(WEP + "ped_sword");
        sword->move(TO, 1);
    }
}

/*
 * Function name: check_remove
 * Description  : VBFC'd blocking function for CONT_M_NO_REM.
 *                Allows players to only get the sword once the
 *                pedestel has been 'unlocked', and sets the
 *                quest bit if they succeed.
 * Arguments    : n/a
 * Returns      : A string saying why they failed, or
 *                0 if they succeed.
 */
public mixed
check_remove()
{
  /* Can't get a sword that isn't there. */
    if (!sword || !present(sword, TO))
        return "There's nothing to get from the pedestal.\n";

  /* Can't take the sword if it hasn't been unlocked. */
    if (!sword_freed)
    {
        say(QCTNAME(TP) + " braces " + TP->query_objective() + "self " +
            "solidly, and begins to heave on the sword embedded in " +
            "the pedestal. After a few moments of futile pulling, " +
            TP->query_pronoun() + " gives up.\n");
        return "You brace yourself solidly, and grasp the sword " +
            "firmly. But try as you might, you just cannot free the " +
            "sword from the pedestal.\n";
    }
    write("Taking a firm grasp on the hilt of the longsword, " +
        "you swiftly draw the ancient blade from its stone " +
        "tomb!\n");
    say("Taking a firm grasp on the hilt of the longsword in " +
        "the stone pedestal, " + QTNAME(TP) + " swiftly " +
        "draws the ancient blade from its stone tomb!\n");   
    seteuid(getuid());
    BITMASTER->set_bit(ELDORAL_SWORD_QUEST_BIT, TP);
    return 0;
}

public void
create_container()
{
    set_name("pedestal");
    add_name("pillar");
    add_name("column");
    set_adj("short");
    add_adj("stone");
    set_long("The short stone pedestal appears to be little more " +
        "than a circular column cut off around waist-high to a " +
        "human. The top has been smoothed, with a flare at the top to " +
        "give the pedestal the appearance of a simple anvil.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_VOLUME, 15700);
    add_prop(CONT_I_WEIGHT, 250000);
    add_prop(CONT_M_NO_INS, "You cannot put anything in the pedestal.\n");
    add_prop(CONT_M_NO_REM, "@@check_remove");
    add_prop(OBJ_M_NO_GET, "The pedestal is firmly placed on the floor.\n");

    set_alarm(1.0, 0.0, reset_quest);
}

public void
release_sword()
{
    tell_room(environment(TO), "A clear, ringing sound suddenly emanates " +
        "from the pedestal.\n");
    sword_freed = 1;
}
   
