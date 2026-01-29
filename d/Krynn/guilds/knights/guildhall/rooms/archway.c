/* The new Vingaard Keep by Morrigan, 11/11/96 */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

public void
create_vin_room()
{
    set_short("Archway");
    set_long("This is a small room adjoining a couple guard posts " +
      "to the west and east, a courtyard to the south, and " +
      "an inner gate to the north. Straw is scattered about " +
      "on the floor.\n");
    AI(({"inner gate","gate"}),"It lies to the north, and protects " +
      "the inner sanctum of Vingaard Keep.\n");
    AI(({"posts","guard posts"}),"To the east and west are guard " +
      "posts, that usually contain Knights or militia, unless " +
      "an attack has occurred.\n");
    AI("courtyard","It is an expansive courtyard that could hold " +
      "many a Solamnian. It is used most often for tournaments " +
      "and parades, though it has also seen the Knights of " +
      "Solamnia marshall their forces.\n");
    AI(({"wall","ceiling"}),"These are made of the same solid stone "+
      "as the rest of Vingaard Keep.\n");
    AI("walls","They are made of the same solid stone as the rest " +
      "of Vingaard Keep.\n");
    AI(({"wall","ceiling"}),"This is made of the same solid stone " +
      "as the rest of Vingaard Keep.\n");
    AI(({"solid stone","stone"}),"It symbolizes the stalwart " +
      "Knights of Solamnia.\n");
    AI("floor","The floor itself is made of solid stone, but " +
      "covering it is scattered straw.\n");
    AI(({"straw","scattered straw"}),"Presumably, this straw was " +
      "either blown in by the wind, or scattered into this " +
      "area by persons who had just walked in the stables. It " +
      "is all a fine golden colour.\n");

    add_search(({"floor","scattered straw"}),1,
      KROBJECT + "straw_blade", -5);

    AE(VROOM + "arch_guardw", "west", 0);
    AE(VROOM + "inner_gate", "north", 0);
    AE(VROOM + "arch_guarde", "east", 0);
    AE(VROOM + "courtyard", "south", "@@archway", 0);

    add_prop("_room_i_allow_steed", 1);
}
int
archway()
{
    write("The blast of fresh air refreshes you as you step from " +
          "the archway to the courtyard of Vingaard Keep.\n");
    return 0;
}
