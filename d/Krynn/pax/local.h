/*
 * Definition file for Pax Tharkas
 *
 * 941105 by Rastlin
 */

#ifndef LOCAL_H
#define LOCAL_H

/* Defines for standard pax rooms             */
/* Using ifdef due to the nature of the names */
#ifndef CREATE
#define CREATE "create_pax_room"
#endif

#ifndef RESET
#define RESET  "reset_pax_room"
#endif

/* Connections to the outside world */
#define QUE             "/d/Krynn/que/newports/"
#define WAYRETH         "/d/Krynn/wayreth/"
/* Warfare path */
#ifndef WAR_AREA_NEWPORT
#define WAR_AREA_NEWPORT   "Newports Area"
#endif

#define PAX     "/d/Krynn/pax/"
#define PMONSTER    PAX + "monster/"
#define POBJ        PAX + "obj/"
#define PWEAPON         PAX + "weapon/"
#define PARMOUR         PAX + "armour/"
#define PSLA        PAX + "sla_mori/"
#define PTHARKAS    PAX + "tharkas/"
#define VALLEY          PAX + "valley/"
#define ROAD            PAX + "road/"
#define PLOG            PAX + "log/"

/* sub directories to tharkas .. added 95/01/04 by Jeremiah */

#define LOW_LEVEL       PTHARKAS + "low_level/"
#define GROUND_LEVEL    PTHARKAS + "ground_level/"
#define WALL_LEVEL      PTHARKAS + "wall_level/"
#define COURT_YARD      PTHARKAS + "court_yard/"

#define STDDOOR         "/d/Krynn/std/door"
#define PAXINROOM       "/d/Krynn/pax/std/in_room"
#define PAXOUTROOM      "/d/Krynn/pax/std/out_room"

#define MAP             "/d/Krynn/pax/map"

#define PAX_DRAC_BASE   "/d/Krynn/pax/std/draconian_base.c"

#define PAXMASTER       "/d/Krynn/pax/obj/master"
#define PLAYEROBJ       "/d/Krynn/pax/obj/player_object"
#define WIZARDOBJ       "/d/Krynn/pax/obj/wizard_object"
#define IS_PAXPLAYER(x) present("_pax_player_", x)

#define GONDORGEM       "/d/Gondor/common/obj/gems"
#define LIVE_I_KRYNN_GEM "_live_i_krynn_gem"

/* Key defines */

#define TOMB_KEY    "7107925"
#define FINAL_KEY   "7107926"
#define PRISON_KEY      "7107927"
#define CELL_KEY        "7107928"

#endif
