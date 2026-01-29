/* Guild.h */
#include "/d/Ansalon/common/defs.h"

#define GUILD_NAME_RACE     "Draconians of Krynn"
#define GUILD_NAME_LAYMAN   "Draconians of Krynn Layman"
#define GUILD_STYLE         "magic"
#define LAY_GUILD_TAX       10
#define RACE_GUILD_TAX      0

#define GUILD_DIR           "/d/Ansalon/guild/draconian/"
#define GUILD_SHADOW_RACE   GUILD_DIR  + "shadow/race_shadow"
#define GUILD_SHADOW_LAYMAN GUILD_DIR  + "shadow/layman_shadow"
#define GUILD_CMDSOUL       GUILD_DIR  + "soul/cmdsoul"
#define GUILD_ROOM          GUILD_DIR  + "room/"
#define GUILD_OBJ           GUILD_DIR  + "obj/"
#define GUILD_NPC           GUILD_DIR  + "npc/"
#define GUILD_SPELLS        GUILD_DIR  + "spells/"
#define GUILD_CLOAK         GUILD_OBJ  + "cloak"
#define GUILD_SUBLOC        GUILD_NAME_RACE + " subloc"
#define GUILD_STARTLOC      GUILD_DIR  + "joinroom"

/* A unique id for the guild's cloak */
#define GUILD_CLOAK_ID      GUILD_NAME_RACE + " cloak"
#define SW query_shadow_who()
/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 */
#define SS_GUILD_SPECIAL_SKILL 102031


