#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("This is a dark and narrow street running north to " +
    "the city wall and south towards a large road, probably the great " +
    "Morgul Road. The street looks more deserted than further south. " +
    "To the west, you can see a large house, which unlike most other " +
    "houses in the city looks to be in good repair. To the east is a " +
    "post office.");
    set_road(3);
    set_side("north");

  add_item(({"wall","city wall"}), BSN(
    "All you can see from here is that some way to the north this " +
    "street seems to end at the foot of the northern city wall. "));
  add_item(({"morgul road"}), BSN(
    "To the south, you can see a broad road running crosswise to this " +
    "street. That is probably the Morgul Road. "));
  add_item(({"mansion","house","building"}), BSN(
    "To the west of the street is a large mansion. It was probably built " +
    "for a Dunadan nobleman living in this city centuries ago. Now it seems " +
    "still to be occupied by wealthy inhabitants, since unlike other houses " +
    "in the city it is in good repair. It has three stories, the facade is " +
    "covered with thin black stone slates. On the ground floor there " +
    "are no windows to the street, only a large black gate. The two upper " +
    "floors have two windows each overlooking the street. "));
  add_exit(MORGUL_DIR + "city/darkstr5","north","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/rooms/post","east","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/darkstr3","south","@@check_exit",1);

  clone_object(MORGUL_DIR+"city/doors/b4doorout")->move(TO);
}
