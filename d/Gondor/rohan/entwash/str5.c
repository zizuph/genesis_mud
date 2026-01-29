inherit "/d/Gondor/rohan/entwash/stream";

#include "/d/Gondor/defs.h"

void
create_stream()
{
    set_extra_long("A wide and muddy bank extends out from the river"
      + " here which has almost fully assumed its eastward flow. The"
      + " area has grown somewhat less dry, and southeast the ground"
      + " grows more moist. The marshes are clearly visible beginning"
      + " in that direction.");

    set_flow("southeast");

    add_item(({"bank","banks","muddy bank"}), BSN(
        "The bank of the Entwash is wide and quite muddy here. Some"
      + "thing has disturbed the mud, as there are prints and holes"
      + " near to the water."));
    add_item(({"print","prints","footprint","footprints"}), BSN(
        "Upon closer inspection, these appear to be human footprints."
      + " Though small, and somewhat queer looking, distinct bare-"
      + "footed depressions are made in this bank. They seem to lead"
      + " away from the water off to the southeast."));
    add_item(({"hole","holes","mud"}), BSN(
        "Whoever or whatever made these holes was perhaps digging for"
      + " snails, as there are some empty shells strewn about."));
    add_item(({"snails","shail","shell","shells","snail shells",
        "snail shell"}), BSN("These small and grey shells have been"
      + " cracked open and drained of their meat."));

    add_exit(ENTWASH_DIR + "str4", "northwest");
    add_exit(ENTWASH_DIR + "str6", "southeast");
}
