/* Master definitions file contains all necessary def procs. Mucalytic. */

#include "/d/Krynn/common/defs.h"

/* Directory definitions. */

#define DOMAIN		"/d/Krynn/"
#define ROOT		DOMAIN + "mucalytic/"

/* Area directories. */

#define HILLS		ROOT + "hills/"
#define SHAANGSEI	ROOT + "shaangsei/"
#define PUZZLE_QUEST	DOMAIN + "solace/puzzle/"

/* Other directories. */

#define STD		ROOT + "std/"
#define SYS		ROOT + "sys/"
#define LOG		ROOT + "log/"
#define WORK		ROOT + "work/"
#define OPEN		ROOT + "open/"
#define PRIVATE		ROOT + "private/"
#define CONTROL		ROOT + "control/"

/* Command definitions. */

#define TI		this_interactive()

#define I(ob)		all_inventory(ob)
#define D(ob)		deep_inventory(ob)

#define RNAME(ob)	ob->query_real_name()
#define RACEN(ob)	ob->query_race_name()

#define IS_NPC(ob)	ob->query_npc()
#define IS_ALIVE(ob)	ob->query_prop(LIVE_I_IS)

/* Short function definitions. */

#define LIVING(ob)	(IS_ALIVE(ob) & !IS_NPC(ob))

/* Miscellaneous. */

#define LINE "+--------------------------------------"+ \
             "---------------------------------------+\n"
