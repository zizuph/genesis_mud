#include "../guild.h"

#define DAMAGE_LIB      "/d/Genesis/specials/std/damage"
#define DEBUGGER_LIB    "/d/Genesis/specials/debugger/debugger_tell.h"

#define BATTACK_COMBAT_AID     50
#define BATTACK_PREP_TIME      6
#define BATTACK_COOLDOWN_TIME  9


#define FAIL_NO_SWORD         1
#define FAIL_NO_SKILL_DEX_2H  2
#define FAIL_NO_STR_BOTH      3
#define FAIL_NO_DEX           4
#define FAIL_NO_SKILL         5

#define BATTACK_ABILITY (SPECIAL + "blade_attack")

#ifndef TP
#define TP     this_player()
#define TO     this_object()
#define NF(x)  notify_fail(x)
#endif
#ifndef TPQN
#define TPQN         this_player()->query_name()
#endif
#ifndef NF0(x)
#define NF0(x) { notify_fail(x + "\n"); return 0; }
#endif
#ifndef ENV
#define ENV    environment(TP)
#endif

#define KLOGGER      "/d/Khalakhor/lib/logger"
