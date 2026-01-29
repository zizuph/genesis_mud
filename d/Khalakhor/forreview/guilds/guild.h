#ifndef _KHALAKHOR_SPAWN_DEFS
#define _KHALAKHOR_SPAWN_DEFS

#define GUILD_NAME       "Order of the Sgath-Cladh"
#define GUILD_TAX        20
#define GUILD_STYLE      "fighter"
#define GUILD_TYPE       "occupational"

#define GUILD_DIR        "/d/Khalakhor/guilds/sgath-cladh/"
#define GUILD_DOCS_DIR   GUILD_DIR + "docs/"
#define GUILD_OBJ_DIR    GUILD_DIR + "obj/"
#define GUILD_ADMIN_DIR  GUILD_DIR + "admin/"
#define GUILD_ROOM_DIR   GUILD_DIR + "room/"

#define GUILD_SHADOW     GUILD_DIR + "shadow"
#define GUILD_SOUL       GUILD_DIR + "soul"
#define GUILD_TRAINER    GUILD_ROOM_DIR + "trainer"
#define GUILD_OBJECT     GUILD_OBJ_DIR + "crystal"
#define GUILD_MASTERS    ({"igneous"})

#define IS_MEMBER(o)     (o->query_guild_name_occ() == GUILD_NAME)

// No more defines after this line
#endif
