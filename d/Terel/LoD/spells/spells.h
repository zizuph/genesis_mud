/*
 *  Constants to define spell costs for each spell in this directory.
 */

#ifndef LOD_SPELLS
#define LOD_SPELLS

#ifndef SPELL_DIR
#define SPELL_DIR "/d/Terel/LoD/spells/"
#endif

#define DURATION(intel, spellcraft, min)\
                  (random((intel)/4) + random((spellcraft)/2) + (min))

#define EVIL_LIM               -133 /* Align. limit for usage of necklace */

#define ZARPHUS_MANA_COST        30
#define ZARPHUS_CAST_LIMIT       30
#define ZARPHUS_PEN(att, tar)    25 + ((tar)->query_alignment() -\
                                       (att)->query_alignment())/100
#define ZARPHUS_ZERO_SKILL       10


#define ZARGMON_MANA_COST        55
#define ZARGMON_CAST_LIMIT       40
#define ZARGMON_PEN(att, tar)    50 + ((tar)->query_alignment() -\
                                       (att)->query_alignment())/50
#define ZARGMON_ZERO_SKILL       20


#define ZARSUZ_MANA_COST         50
#define ZARSUZ_CAST_LIMIT        25

#endif
