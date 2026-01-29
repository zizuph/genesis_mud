/*
 *
 *    local.h - For the city of Neraka and the surrounding areas.
 *
 */

#ifndef NERAKA_DEF
#define NERAKA_DEF

#define NERAKA            "/d/Ansalon/taman_busuk/neraka/"
#define NSTD                NERAKA + "std/"
#define NNPC                NERAKA + "npc/"
#define NOBJ                NERAKA + "obj/"
#define NWEP                NERAKA + "wep/"
#define NARM                NERAKA + "arm/"
#define NINNER              NERAKA + "inner/"
#define NOUTER              NERAKA + "outer/"
#define NTEMPLE             NERAKA + "temple/"
#define NLOG                NERAKA + "log/"
#define NSEWER              NERAKA + "sewers/"

#define KNPC                "/d/Krynn/solamn/splains/living/"

#define NERAKA_ADMIN        (NERAKA + "admin/admin")
#define WAGONS_ADMIN        (NERAKA + "admin/wagons")
#define PARROT_ADMIN        (NERAKA + "admin/parrot")
#define ATTACKERS_ADMIN     (NERAKA + "admin/attackers")
#define CITY_ADMIN          (NERAKA + "admin/city")

#define INNER_BOARD         NLOG + "boards/inner"
#define GUILD_BOARD         NLOG + "boards/guild"

#define NERAKA_REPORT       "/d/Ansalon/taman_busuk/neraka/std/report.c"

/* Base files */

#define NINROOM         NSTD + "i_room_base"

#define NIOUTROOM       NSTD + "i_outer_city_base"
#define NOUTROOM        NSTD + "o_outer_city_base"

#define NIINNERROOM     NIOUTROOM
#define NINNERROOM      NSTD + "o_inner_city_base"

#define OUTER_OUT       NSTD + "o_outer_city_base"
#define OUTER_IN        NSTD + "i_outer_city_base"
#define INNER_OUT       NSTD + "o_inner_city_base"
#define INNER_IN        OUTER_IN
#define SEWER_BASE      NSTD + "sewer_base"
#define TEMPLE_BASE     NSTD + "temple_base"

#define RANTEAM         NSTD + "ranteam"

// #define KNPC(x)   "/d/Krynn/solamn/splains/living/x"

#define BAAZ    "/d/Krynn/std/baaz"
#define BOZAK   "/d/Krynn/std/bozak"
#define KAPAK   "/d/Krynn/std/kapak"
#define SIVAK   "/d/Krynn/std/sivak"
#define AURAK   "/d/Krynn/std/aurak"
#define M_FILE  "/d/Krynn/std/monster"

/* Quarters (colours) */
#define WHITE "white"
#define RED "red"
#define BLUE "blue"
#define BLACK "black"
#define GREEN "green"

/* Random tables */
#define NT_OUTER        "/d/Ansalon/taman_busuk/neraka/tables/outer"
#define NT_OUTERDRAC    "/d/Ansalon/taman_busuk/neraka/tables/outerdrac"
#define NT_OUTERGOBLIN  "/d/Ansalon/taman_busuk/neraka/tables/outergoblin"
#define NT_OUTERMERC    "/d/Ansalon/taman_busuk/neraka/tables/outermerc"
#define NT_OUTERSOLDIER "/d/Ansalon/taman_busuk/neraka/tables/outersoldier"
#define NT_OUTERMASTER  "/d/Ansalon/taman_busuk/neraka/tables/outermaster"

/* Keys */
#define SLAVE_KEY   "7999999"

/* special properties */
#define NERAKA_I_KILLED_PARROT      "_neraka_i_killed_parrot"

#define NERAKA_I_KILLED_KORDHEK       "_neraka_i_killed_kordhek"
#define NERAKA_I_FOUND_THE_SLAVE_KEY  "_neraka_i_found_the_slave_key"
/* a torch stand where npc's can get torches */
#define NERAKA_I_ROOM_HAS_TORCHES     "_neraka_i_room_has_torches"

#define NERAKA_I_ATTACKED_TEMPLE        "_neraka_i_attacked_temple"

#define NERAKA_LIVE_O_WAGON_STEED   "_neraka_live_o_wagon_steed"

#define NERAKA_I_IS_TEMPLE_ROOF     "_neraka_i_is_temple_roof"
#define NERAKA_MI_DRAGONBREW        "_neraka_mi_dragonbrew"

/* Other things */
#define VALID_PASS_ID   "_neraka_pass"
#define FAKE_PASS_ID    "_neraka_fake_pass"

/* crimes against the guards of neraka */
#define CRIME_SUSPECT   10000
#define CRIME_THEFT     15000
#define CRIME_ATTACK    15000
#define CRIME_MURDER    150000

#endif NERAKA_DEF
