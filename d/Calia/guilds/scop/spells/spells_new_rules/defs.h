
#include "/d/Calia/domain.h"

#define SPIRIT_HEADER          "/d/Calia/guilds/scop/specials/scop.h"

#define SPIRIT_DIR             "/d/Calia/guilds/scop/"
#define WORSHIP_DIR            "/d/Calia/worshippers/"
#define WORSHIP_GUILD          "Elemental Worshippers of Calia"

#define SPIRIT_TEXTS           SPIRIT_DIR+"texts/"
#define SPIRIT_OBJECTS         SPIRIT_DIR+"objects/"
#define SPIRIT_SPECIALS        SPIRIT_DIR+"specials/"
#define SPIRIT_TEMPLE          SPIRIT_DIR+"temple/"
#define SPIRIT_NPCS            SPIRIT_DIR+"npcs/"
#define SPIRIT_LOGS            SPIRIT_DIR+"logs/"
#define SPIRIT_SOUL            SPIRIT_SPECIALS+"spiritsoul"
#define SPIRIT_SHADOW          SPIRIT_SPECIALS+"spiritshadow"
#define SPIRIT_LAY_SOUL        SPIRIT_SPECIALS+"spiritlaysoul"
#define SPIRIT_LAY_SHADOW      SPIRIT_SPECIALS+"spiritlayshadow"
#define SCOP_SPELL_DELAY "_scop_spell_delay"
#define SCOP_CAST_TIME "_scop_cast_time"



#ifndef SPIRIT_SPELLS
#define SPIRIT_SPELLS          SPIRIT_DIR+"spells/"
#endif

#ifndef COUNCIL_HEADER
#define COUNCIL_HEADER         "/d/Calia/guilds/scop/specials/council.h"
#endif

#define HE(x)         ((x)->query_pronoun())
#define HIM(x)        ((x)->query_objective())
#define HIS(x)        ((x)->query_possessive())
#define ONE_OF(x)     ((x)[random(sizeof(x))])
