/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 *  ~mecien/valley/guild/spells/spells.h
 *  Constants to define spell costs for each spell in this directory.
 */

#ifndef MYSTIC_SPELLS
#define MYSTIC_SPELLS

#ifndef SPELL_DIR
#define SPELL_DIR "/d/Terel/mecien/valley/guild/spells/"
#endif

#define DURATION(intel, spellcraft, min)\
    (random((intel)/5) + random((spellcraft)/3) + (min))
    

#define ANGELICUS_MIN_WIS       80
#define ANGELICUS_MANA_COST    100
#define ANGELICUS_CAST_LIMIT   100
#define ANGELICUS_MIN_DURATION  45

#define BEATUS_MIN_WIS          80 /* Not used! */
#define BEATUS_SELF_MANA         2
#define BEATUS_OTHER_MANA        1
#define BEATUS_CAST_LIMIT       20

#define FLAMMIS_MIN_WIS          80 /* Not used! */
#define FLAMMIS_MANA_COST        40
#define FLAMMIS_CAST_LIMIT       40
#define FLAMMIS_PEN              70

#define FULMEN_MIN_WIS          80 /* Not used! */
#define FULMEN_MANA_COST        50
#define FULMEN_CAST_LIMIT       75
#define FULMEN_PEN              150 

#define IMAGO_MIN_WIS          80 /* Not used! */
#define IMAGO_SELF_MANA        10
#define IMAGO_OTHER_MANA       20
#define IMAGO_CAST_LIMIT       80

#define LUMEN_MANA_COST        10
#define LUMEN_CAST_LIMIT       10
#define LUMEN_MIN_DURATION     90
#define ARDERE_MANA_COST       25
#define ARDERE_CAST_LIMIT      60

#define NUBES_MANA_COST	40
#define NUBES_CAST_LIMIT 	40
#define NUBES_MIN_DURATION   50

#define PERDITUS_CAST_LIMIT   150
#define PERDITUS_MANA_COST    200

#define MITTERE_CAST_LIMIT   50
#define MITTERE_MANA_COST    40

#define STELLA_MANA_COST	15
#define STELLA_CAST_LIMIT	30
#define STELLA_PEN		30

#endif
