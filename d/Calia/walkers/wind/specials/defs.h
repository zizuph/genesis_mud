
#include "../defs.h"
#define WORSHIPPER_GUILD "Elemental Worshippers of Calia"
#define WOR_LANGUAGE "/d/Calia/walkers/specials/wlang.h"
#define CAP(x) capitalize(x)
#define ENV(x) environment(x)
#define IS_WORSHIP(x) ((x)->query_guild_name_lay() == WORSHIPPER_GUILD)
#define IS_WALKER(x) ((x)->query_skill(SS_WALKER_CHOSEN))

