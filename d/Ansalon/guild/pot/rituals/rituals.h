/*
 * Changed dark touch to require 1 priest instead of 2
 * Due to inactivity of the priests.
 */

#ifndef POT_RITUALS
#define POT_RITUALS

#include "../guild.h"
#include <tasks.h>

#define R_OBJ2OBJ   (1)
#define R_OBJ2SH    (1 << 1)
#define R_PL2SH     (1 << 2)

/* "filename" : ({ DEFINE, num_of_priests, diff, "sh/obj", ({ ingr }) })
 *
 * First obj in ingr is affected if not R_PL2SH in which case
 * query_chantee() is affected
 *
 * ingr: "name"
 *       "filename" (begins with /)
 *       "property" (begins with _)
 */
#define FORMULAES ([ \
    "holy_water" : ({ R_OBJ2SH, 1, TASK_SIMPLE, (GUILDDIR + "rituals/shadows/holy_water"), \
                      ({ (GUILDDIR + "rituals/obj/phial"), "water" }) }), \
    "dark_touch" : ({ R_OBJ2SH, 1, TASK_ROUTINE, (GUILDDIR + "rituals/shadows/dark_touch"), \
                      ({ "Wclub", "fireweed", "heart", "diamond" }) }), \
    "magical_vestment" : ({ R_OBJ2SH, 1, TASK_ROUTINE, (GUILDDIR + "rituals/shadows/vestment"), \
                            ({ "robe", (GUILDDIR + "rituals/obj/xxx") }) }), \
    "summoning" : ({ R_OBJ2OBJ, 3, TASK_DIFFICULT, (GUILDDIR + "rituals/obj/sceptre"), \
                     ({ (GUILDDIR + "rituals/obj/xxx") }) }), \
])

#endif /* POT_RITUALS */
