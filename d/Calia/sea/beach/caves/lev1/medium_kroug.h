/*  description: header file for cloning
 *               medium-sized water krougs
 *               for caves
 */

#pragma strict_types

object kroug1, kroug2, kroug3;


void
reset_room()
{
    if (!objectp(kroug1))
    {
	kroug1 = clone_object(SEA_CREATURES + "medium_wkroug");
	kroug1->arm_me();
	kroug1->command("wield all");
	kroug1->move(this_object(), 1);
	kroug1->command("emote charges in.");
    }
    if (!objectp(kroug2))
    {
	kroug2 = clone_object(SEA_CREATURES + "medium_wkroug");
	kroug2->arm_me();
	kroug2->command("wield all");
	kroug2->move(this_object(), 1);
	kroug2->command("emote leaps in with a shout!");
    }

    if (!objectp(kroug3))
    {
	kroug3 = clone_object(SEA_CREATURES + "medium_wkroug");
	kroug3->arm_me();
	kroug3->command("wield all");
	kroug3->move(this_object(), 1);
	kroug3->command("emote jumps you from behind.");
    }

    return;
}
