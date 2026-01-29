#include <tasks.h>
#include "defs.h"
#include "/d/Shire/bits.h"

#define QUEST_NAME "moria_exit"
#define HOLLIN_EXIT "/d/Shire/common/hollin/crevice"
#define TEST_EXIT "/d/Shire/moria/chute"

void press_notch(object player);
void reset_notch();

int pressed = 0;

CONSTRUCT_ROOM 
{
    set_short("End of the dark tunnel");
    set_long("You have been abrupted by a sudden stop in the dark tunnel. " +
        "This place is even wider and higher than in the south, where " +
        "the tunnel leads back to the guard room. There's a sign on " +
        "laying on the ground.\n");
    add_item(({"sign", "wall", "runes"}), 
      "It looks like strange signs written with runes. Perhaps read them?\n");
    add_call("read", "[the] 'sign' / 'runes' / 'wall'", "read_sign");
    add_call(({"search", "exa", "examine", "look", "l"}),
      "[at] [the] 'trap-door' / 'floor' / 'chute' / 'exit / 'notch'",
      "search_exit");
    add_call(({"press", "push"}), "[the] 'notch' [on] [the] [floor]",
      "wait_press_notch");
    SOUTH("exit2");
}

int
read_sign(string str)
{
    int diff, res;

    if (TP->query_race_name() == "dwarf") 
	diff = DIFF_EASY;
    else
	diff = DIFF_HARD;

    res = TP->resolve_task(diff, ({ TS_WIS, SS_LANGUAGE, SS_OPEN_LOCK }));

    if (res < -20) 
	write("You try to understand what the runes says, but you fail.\n");
    else if (res < 0) 
	write("You try to understand the runes, but guess only that it " +
	  "is probably some kind of magic here.\n");
    else if (res < 20) 
	write("You read the runes. They say nothing but rubbish: \"MXPLW\".\n");
    else
	write("You read the runes. They say nothing but rubbish: \"MXPLW\". " +
	  "Aha! You get it now. It is a rune key combination! You must " +
	  "get a rune key, and place it on the runes!\n");

    say(QCTNAME(TP) + " tries to understand the runes on the wall.\n");
    return 1;
}

int
search_exit(string arg)
{
    if (!TP->test_bit("Shire", EASTERN_GROUP, MORIA_EXIT_BIT))
	return 0;

    write("Hmm, yes, you've already fallen down here, no wonder...\n");
    write("Perhaps it is possible to trigger it by using some other method?\n");
    write("Let's see.. Rune on the wall triggers, yes, hmm..\n");
    write("Yes!! Perhaps just press that notch on the floor?\n");
    say(QCTNAME(TP) + " strolls around the room trying to figure out something.\n");
    return 1;
}

int
wait_press_notch(object player)
{
    if (!TP->test_bit("Shire", EASTERN_GROUP, MORIA_EXIT_BIT))
	return 0;
    if (pressed)
    {
	NF("You press the button, but find it already depressed.\n");
	return 0;
    }

    write("You press the notch in the floor, and wait a moment for "+
      "the escape hatch to open.\n");
    say(QCTNAME(TP) + " bends down and does something peculiar.\n");
    pressed = 1;
    set_alarm(itof(4 + random(5)), 0.0, &press_notch(TP));
    set_alarm(itof(300 + random(200)), 0.0, reset_notch);
    return 1;
}

void
reset_notch()
{
    tell_room(TO, "The notch in the floor rises back into "+
      "position.\n");
    pressed = 0;
}

void
press_notch(object player)
{
    int i;
    object *objs;

    objs = all_inventory(TO);

    if (!sizeof(objs))
	return;
    tell_room(TO, "The floor suddenly drops away beneath you!\n");

    for (i=0; i<sizeof(objs); i++)
    {
	if (living(objs[i])) {
	    if (!objs[i]->query_npc())
		objs[i]->move_living("M", TEST_EXIT);
	}
	else
	    objs[i]->move(HOLLIN_EXIT);
    }
    return;
}
