inherit "/d/Rhovanion/lib/room";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

#define G_HERB   "/d/Gondor/common/herbs/"
#define HERBS   ({ "attanar",\
                   "attanar",\
                   "attanar",\
                   "attanar",\
                   "attanar",\
                   "attanar",\
                   "blueberry",\
                   "blueberry",\
                   "blueberry",\
                   "blueberry",\
                   "blueberry",\
                   "blung",\
                   "blung",\
                   "blung",\
                   "blung",\
                   "blung",\
                   "bpotato",\
                   "caraway",\
                   "caraway",\
                   "caraway",\
                   "caraway",\
                   "caraway",\
                   "chervil",\
                   "chervil",\
                   "chervil",\
                   "chervil",\
                   "chervil",\
                   "foxglove",\
                   "foxglove",\
                   "foxglove",\
                   "foxglove",\
                   "foxglove",\
                   "gonion",\
                   "gonion",\
                   "gonion",\
                   "gonion",\
                   "gonion",\
                   "hemlock",\
                   "hemlock",\
                   "hemlock",\
                   "hemlock",\
                   "hemlock",\
                   "hemlock",\
                   "holly",\
                   "holly",\
                   "holly",\
                   "holly",\
                   "holly",\
                   "laurel",\
                   "laurel",\
                   "laurel",\
                   "laurel",\
                   "laurel",\
                   "laurel",\
                   "lissuin",\
                   "lissuin",\
                   "lissuin",\
                   "lissuin",\
                   "lothore",\
                   "lothore",\
                   "lothore",\
                   "lothore",\
                   "lothore",\
                   "mint",\
                   "mint",\
                   "mint",\
                   "mint",\
                   "mint",\
                   "myrtle",\
                   "myrtle",\
                   "myrtle",\
                   "myrtle",\
                   "myrtle",\
                   "myrtle",\
                   "oregano",\
                   "oregano",\
                   "oregano",\
                   "oregano",\
                   "oregano",\
                   "oregano",\
                   "redweed",\
                   "redweed",\
                   "redweed",\
                   "redweed",\
                   "rpotato",\
                   "rpotato",\
                   "rpotato",\
                   "rpotato",\
                   "rpotato",\
                   "seregon",\
                   "seregon",\
                   "seregon",\
                   "seregon",\
                   "suranie",\
                   "suranie",\
                   "suranie",\
                   "suranie",\
                   "suranie",\
                   "suranie",\
                   "suranie",\
                   "suranie",\
                   "tarragon",\
                   "tarragon",\
                   "tarragon",\
                   "tarragon",\
                   "tuo",\
                   "tuo",\
                   "tuo",\
                   "tuo",\
                   "ungolestel",\
                   "ungolestel",\
                   "ungolestel",\
                   "ungolestel",\
                   "ungolestel",\
                   "ungolestel",\
                })

void add_herbs()
{
  int i;

  add_prop(OBJ_I_SEARCH_TIME, 6);
  add_prop(OBJ_S_SEARCH_FUN, "herb_search");
  set_search_places(({"ground", "trees"}));
  for(i=0; i<5; i++)
    add_herb_file(G_HERB+ONE_OF_LIST(HERBS));
}
