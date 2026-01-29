/*  description: header file for cloning
 *               large-sized water krougs
 *               for caves
 */

#pragma strict_types

object kroug1, larva;


void
reset_room()
{
    if (!objectp(kroug1))
    {
	kroug1 = clone_object(SEA_CREATURES + "large_wkroug");
	kroug1->arm_me();
	kroug1->command("wield all");
	kroug1->move(this_object(), 1);
	kroug1->command("emote charges in.");
    }

    if (!objectp(larva))
    {
	larva = clone_object(SEA_CREATURES + "larva");
	larva->move(this_object(), 1);
	larva->command("emote wriggles in.");
    }

    return;
}
