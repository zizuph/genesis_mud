#pragma strict_types

inherit "/d/Gondor/morgul/vale/morgul2.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_short("At the gate at the Morgul Pass, outside Mordor.\n");

    set_extraline("You are outside the watchtower of Cirith Ungol and the gate into Mordor. " +
        "To the north you can see a small courtyard of the watchtower of Cirith Ungol " +
        "while the entrance to Mordor is eastwards through the gate. Here you can see a " +
        "great arch over the gate. Two stone watchers seem to guard the " +
        "gate at each side.\n");
 
        add_item(({"road"}), BSN(
        "This dusty road ends infront of the Mordor-gate."));
    add_item(({"field", "darkness", "field of darkness"}), BSN("When you try to look through " +
            "the arch, you cannot see " +
            "anything. You think this is because of an invisible field of " +
            "darkness. This field will prevent all mortal beings, perhaps " +
            "except orcs, from leaving or entering Mordor.")); 
    add_item(({"watcher", "watchers"}), BSN("The watchers are like great " +
        "figures seated upon thrones. Each has three joined bodies, and " +
        "three heads facing outward, inward and across the gateway. The " +
        "heads have vulture-faces, and on their great knees are laid " +
        "clawlike hands. They seem to be carved out of huge blocks of " +
        "stone, immovable, and yet they are aware: some dreadful spirit of " +
        "evil vigilance abode in them. They know an enemy. Visible or " +
        "invisible none can pass unheeded. They will forbid his entry, or " +
        "his escape."));
    add_item(({"gate", "arch"}), BSN("You are standing under a dark arch " +
        "and above you, you can see the dark tower of Cirith Ungol. Mighty " +
        "watchers have their obscure way of keeping the enemy out (OR IN!)" +
        "The stones of the arch are smooth and you don't think you can " +
        "climb your way into Mordor here."));
    add_item("tower", BSN("Standing here you see the tower of Cirith Ungol " +
        "in all its might. They rise all the way to the sky and you don't " +
        "look forward to climbing all the way to the top if yo udare. The " +
        "walls are so smooth that probably a spider wouldn't be able to " +
        "climb up to the top."));
    add_item(({"wall", "walls"}), BSN("The walls of the tower are so smooth " +
        "that a spider can't climb up to the top. You are amazed by the " +
        "skills the craftsman of the old had."));

    add_exit(UNGOL_DIR + "yard1", "northwest",0,3);
    add_exit(MORGUL_DIR + "vale/mrd15","west",0,3);
}





