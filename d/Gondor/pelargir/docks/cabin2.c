inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in the captain's cabin");
    set_long(BSN("You are in the Captain's cabin. The room looks more "
      + "like a trophy storeroom though as you notice the myriad "
      + "objects hung on the wall. On two walls there are pirate flags "
      + "evidently taken from various scuffles at sea. Propped in "
      + "another corner is a long object that reminds you vaguely of "
      + "ivory, no doubt some horrible sea creature's tooth. The "
      + "captain's desk and bed are impeccably clean however, as he "
      + "rarely actually does any work."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"flags","flag","pirate flags"}), BSN(
        "The skull and crossbones pirate symbol is boldly printed on "
      + "these flags. The edges are torn and frayed now and a little "
      + "burnt around the edges. The fight to capture these flags "
      + "certainly was not easy."));
    add_item(({"tooth", "ivory"}), BSN(
        "This huge tooth must have come from quite a mouth. You guess "
      + "that it is at least 3 feet long."));
    add_item(({"trophies", "myriad objects"}), BSN(
        "Besides the tooth and the flags, there is a golden cutlass "
      + "mounted firmly on the wall. Engraved in it are the words:"
      + "\tDrasmere Lord of Pirates."));
    add_item("deck",BSN("The deck is spotless, you could not have "
      + "done a better job yourself."));
    add_exit(PELAR_DIR + "docks/ship2.c","deck",0);
}
