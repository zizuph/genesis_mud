/*
 * - /d/Avenir/union/room/shadow.c
 *
 * A Chambre of Shadows where members may practice emotes and
 * see their effects firsthand.
 *
 * Revisions:
 *   Lucius, Oct  6, 2005: Created.
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>

#define AMLIS  (NPC + "amlis")

private static int alarm;
private static object amlis, simul;


/*
 * In the Sway, these shadows are solid.
 */
private int
exit_block(void)
{
    if (present(SWAY_ID_ALL, TP))
    {
	write("You try to move, but the shadows seem to have acquired "+
	  "mass and density and you find your passage blocked.\n");
	return 1;
    }
    write("You ascend through the shadows...\n");
    return 0;
}

public void 
union_room(void)
{
    set_short("shadowy chambre");
    set_long("Shadows drape and cling to every inch of this room, "+
      "obscuring all save the obsidian staircase which you descended. "+
      "They move and writhe in random patterns with chaotic motion, "+
      "their cold dewy tendrils brushing exposed skin as they flitter "+
      "all around you. They seem anxious, almost eager, as though they "+
      "hold here awaiting some further purpose.\n");

    add_item(({"shadow","shadows","tendrils","shadowy tendrils"}),
      "They are Shadow, grey-black phantasms of something that once "+
      "was more.\n");

    add_item(({"steps","stair","stairs","staircase","obsidian staircase"}),
      "Your ingress and egress from this chambre. The shadows seem "+
      "to steer clear of the steps, leaving the passage clear while "+
      "obscuring the rest from thine seeking eyes.\n");

    add_item(({"walls","floor","ceiling"}), "Shadows cover all, save those "+
      "steps you descended to arrive here.\n");

    add_exit("novlib0", "up", exit_block, 0, 1);
}

private void
clear_alarm(void)	{ alarm = 0; }

/*
 * Embrace the shadows, and learn.
 */
public int
f_embrace(string str)
{
    if (str != "shadows" && str != "the shadows")
	return NF("What do you wish to embrace?\n");

    if (alarm || objectp(amlis))
    {
	if (alarm || present(amlis->query_embraced(), TO))
	{
	    write("You attempt to embrace the shadows, but they slip "+
	      "from your grasp leaving nothing but dewy tendrils upon "+
	      "your fingertips.\n");
	    return 1;
	}

	amlis->remove_object();
	simul->remove_object();
    }

    if (present(SWAY_ID, TP))
    {
	write("You find that the shadows have taken on an usual "+
	  "solidity and though you struggle, you are unable to "+
	  "complete the motions.\n");

	return 1;
    }

    write("You reach for the shadows, struggling to embrace the "+
      "intangible until one of them detaches itself from the "+
      "rest and embraces you back.\n");
    say(QCTNAME(TP) + " reaches for the shadows in an attempt to "+
      "embrace them, suddenly, one of them detaches from the rest "+
      "to return it.\n");

    if (!objectp(amlis = clone_object(AMLIS)))
    {
	write("The shadow seems to dissipitate upon contact, however, "+
	  "and you should inform the Immortals.\n");

	amlis = 0;
	return 1;
    }

    simul = clone_object(AMLIS);
    set_alarm(2.0, 0.0, &amlis->set_embraced(TP, 0));
    set_alarm(2.0, 0.0, &simul->set_embraced(TP, 1));
    amlis->move_living("M", TO, 1, 1);
    simul->move_living("M", TO, 1, 1);

    alarm = set_alarm(2.0, 0.0, clear_alarm);
    return 1;
}

public void
init(void)
{
    ::init();

    if (!IS_MEMBER(TP))
	return;

    add_action(f_embrace, "embrace");
}

/*
 * Reset shadow trainer when leaving.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (objectp(amlis) && (amlis->query_embraced() == ob))
    {
	amlis->remove_object();
	simul->remove_object();
    }
}

/*
 * This room has special sway messages.
 */
public string 
union_hook_sway_msg(int phase, object ob)
{
    switch (phase)
    {
    case 1:
	return "The shadows grow still, their movements suddenly ceasing, "+
	    "your heightened senses picking out a previous unfelt sense "+
	    "of agitation.";
    case 2:
	return "The air vibrates, and you are surrounded by a multitude "+
	    "of sibilant whispers caressing you from head to toe.";
    case 3:
	return "As you plummet further into the Sway, you hear voices.. "+
	    "many voices.. all of them whispering, \""+
	    "Embraaaaccceee Usssssss\"";
    case 4:
	return "The shadows draw closer, they wrap around you like a tight "+
	    "cloak, snaking their way over you every which way with "+
	    "increasing tenacity.";
    case 5:
	return "Suddenly, the shadows withdraw and hover, waiting...";
    case -1:
	return "As the Sway ends, so do the voices, returned again to "+
	    "a hushed drone as the shadows take up their wanderings "+
	    "once more.";
    default:
	return "";
    }
}

public string 
union_hook_sway_msg_other(int phase, object ob)
{
    switch (phase)
    {
    case 1:
	return "The shadows seem somehow more agitated.";
    case 3:
	return "Your ears buzz at some sound, but you can't determine "+
	    "the source.";
    case -1:
	return "The shadows seem to return to their lazy meanderings.";
    default:
	return "";
    }
}
