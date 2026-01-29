// file name:        /d/Avenir/common/undraeth/shops/guard_post
// creator(s):       Nikklaus, July '97
// revision history:
// purpose:          Keep a ledger of foreign traders while they are in the
//                   city, and a few guards within the gates.
// note:
// bug(s):
// to-do:
/*
 * Re-patriated code back to the Kalad domain.
 * 	- Lucius, June 2017
 */
# pragma strict_types

#include "/d/Kalad/defs.h"
inherit "/d/Kalad/room_std";

void
create_room()
{
    enable_reset();
    setuid(); seteuid(getuid());

    INSIDE;
    add_prop(ROOM_M_NO_TELEPORT,1);

    set_short("Inside a small stone compound");
    set_long("The limestone walls shaped of this conical chamber are "+
      "planed smooth, shaped from the inside of this stalagmite, but the "+
      "granite floor is marred and gouged with abuse.  A long marble "+
      "counter stretches from beside the archway leading out to the "+
      "center of the room.  A bas-relief sculpture of a spider has been "+
      "chiselled high up the far wall, overlooking the room.\n");
    add_item(({"walls", "wall", "limestone", "limestone wall", 
	"limestone walls"}),
      "The walls of this chamber are made of limestone, planed smooth and "+
      "slightly chalky to the touch.\n");
    add_item(({"granite floor", "granite", "floor"}),
      "Streaks and grooves have been gouged out and scraped into the "+
      "granite floor.\n");
    add_item(({"marble counter", "marble", "counter"}),
      "A rectangular block of marble radiates from the center of "+
      "the circular floor and abuts against the wall next to the "+
      "archway.\n");
    add_item(({"archway", "exit"}),
      "The compound's archway leading back out to the streets of the "+
      "city is framed with a rounded lip, shaped as smooth as the rest "+
      "of the inside.\n");
    add_item(({"sculpture", "bas-relief", "spider"}),
      "The figure of a spider stands out from the stone, carved with "+
      "such detail you can make out the sections of its carapace, the "+
      "joints of its long legs, the hourglass shape on its back, and "+
      "the shape of its fangs and eyes.  Behind it, a network of "+
      "delicate lines, depicting a web, extend from the figure, "+
      "diminishing in clarity until they meld into the smooth "+
      "walls.\n");

    add_exit(CPASS(drow/d11), "south");

    add_npc(CPASS(drow/npc/post_guard));
    add_npc(CPASS(drow/npc/assessor));

    clone_object("/d/Genesis/obj/board")->move(this_object(), 1);
}
