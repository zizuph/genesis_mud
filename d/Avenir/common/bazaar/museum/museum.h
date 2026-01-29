/* Definitions for the museum in the bazaar
 *  Cirion 040296
 */

#include "../bazaar.h"

#define MUS         BAZAAR+"museum/"
#define MUS_OBJ     MUS + "obj/"

#define MUSLOG(x)   write_file("/d/Avenir/log/bazaar/statues", \
    ctime(time()) + ": "+ x +"\n")

#define STATUES     MUS+"statues"

#define CENTER     (MUS+"center")
#define STUDIO     (MUS+"studio")
#define STAT1      (MUS+"gallery1")
#define STAT2      (MUS+"gallery2")
#define STAT3      (MUS+"gallery3")
#define STAT4      (MUS+"gallery4")
#define STAT5      (MUS+"gallery5")
#define STAT6      (MUS+"gallery6")
#define STAT7      (MUS+"gallery7")
#define STAT8      (MUS+"gallery8")
#define STAT9      (MUS+"gallery9")
#define STAT10     (MUS+"gallery10")
#define STAT11     (MUS+"gallery11")
#define STAT12     (MUS+"gallery12")
#define STAT13     (MUS+"gallery13")
#define STAT14     (MUS+"gallery14")
#define STAT15     (MUS+"gallery15")

#define GET_STATUES(x)  ((STUDIO)->query_statues(x))

#define SGT         seteuid(getuid(this_object()))

/* Statues cost 150 plats, for now */
#define STAT_COST   (150 * 12 * 12 * 12)

/* Guild names, to add to statue material */
/* Occ */
#define RANGER     "Gondorian Rangers Guild"
#define KNIGHT     "Solamnian Knights"
#define ANGMAR     "Angmar Army"
#define VAMP       "Vampires of Emerald"
#define MONK       "Ancient Kaheda Order"
#define GLAD       "Gladiator guild"
#define MYSTIC     "Ancient Mystic Order"
#define MAGE       "Morgul Mages"
#define SHAD       "Union of the Warriors of Shadow"

/* Lay */
#define MINSTRIL   "The August Order of Minstrels"
#define L_MONK     "Ancient Kaheda Order"
#define L_ANGMAR   "Angmar Army"
#define SQUIRE     "Solamnian Knights"
#define HERALD     "Heralds of the Valar"
#define TRICK      "-Tricksters-"

/* Race */
#define DROW       "Drow race guild"
#define DUNE       "Dunedain"
#define TRAVEL     "Traveller guild"
#define THANAR     "Thanarian human race guild"
#define ROCK       "Rockfriend guild"
#define GRUNT      "Grunts guild"
#define WILD       "Wildrunner guild"
#define INVENT     "Inventors"
#define ADV_HOB    "Adventuresome Hobbits Guild"


