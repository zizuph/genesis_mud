/**********************************************************************
 * - guild.h                                                        - *
 * - Defines for the minor guild - layman guild for females         - *
 * - Temptresses of Oenghus                                         - *
 * - Created by Damaris@Genesis 3/2006                              - *
 **********************************************************************/

#ifndef GUILD_DEFS
#define GUILD_DEFS

#define GUILD_NAME      "Temptresses of Oenghus"
#define GUILD_STYLE     "club"

#define GUILD_DIR       "/d/Khalakhor/guilds/tempt/"

#define ARM             (GUILD_DIR + "arm/")
#define HELP            (GUILD_DIR + "help/")
#define LOG             (GUILD_DIR + "log/")
#define NPC             (GUILD_DIR + "npc/")
#define ROOM            (GUILD_DIR + "room/")
#define WEP             (GUILD_DIR + "wep/")

#define SOUL	        (GUILD_DIR + "soul")
#define SHADOW          (GUILD_DIR + "shadow")
#define GUILD_OBJ	(GUILD_DIR + "bangles")
#define JOIN_SCROLL     (LOG + "scroll")
#define OBJECT_ID       ("_tempt_emblem")
#define GUILD_SUBLOC	("_tempt_subloc")

#define JOIN            (NPC + "join")
#define HISTORY         (NPC + "history")

#define ENTRANCE        (ROOM + "entrance")
#define GUILD_ROOM      (ROOM + "guild_room")     
#define FRUIT_PICK      (ROOM + "fruit_pick")

#define IS_MEMBER(x)    (present(OBJECT_ID, (x)))

#endif
