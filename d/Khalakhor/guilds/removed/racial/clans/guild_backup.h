#ifndef __GUILD_DEFS__
#define __GUILD_DEFS__

#include "/d/Khalakhor/sys/defs.h"

#define GUILD_NAME      "Clans of Khalakhor"
#define GUILD_STYLE     "race"
#define GUILD_TAX       1 or 3 depending on if they choose a clan or not.
#define GUILD_MIN_ALIGN -1200


#define GUILD_DIR       "/d/Khalakhor/guilds/racial/clans/"
#define ARM             (GUILD_DIR + "arm/")
#define ROOM            (GUILD_DIR + "room/")
#define OBJ             (GUILD_DIR + "obj/")
#define LOG             (GUILD_DIR + "log/")
#define NPC             (GUILD_DIR + "npc/")
#define HELP            (GUILD_DIR + "help/")
#define SCROLLS     (GUILD_DIR + "scrolls/")
#define GUILD_ROOM      (ROOM + "guild_room")
#define SCROLL          (GUILD_DIR + "scroll")
#define SHADOW          (GUILD_DIR + "shadow")
#define SERVER          (GUILD_DIR + "server")
#define SOUL            (GUILD_DIR + "soul")
#define OBJECT          (GUILD_DIR + "tartan")
#define OBJECT_ID       "_khal_clan_emblem"
#define GUILD_SUBLOC    "_khal_clan_subloc"
#define LEADER_EMBLEM_ID "_CLAN_leader_emblem"
#define STARTLOC        (ROOM + "start")
#define GLOG            (LOG + "log")
#define INFO_LOG        (LOG + "info_log")
#define IS_MEMBER(x)    (x->query_guild_member(GUILD_NAME))
#define IS_LEADER(x)    (SERVER->query_council_member(x))


#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
   (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) :\
   (write_file(file, ctime(time()) + ": " + entry + "\n")))

/*
 * List of surnames to choose from when joining.
 */
#define SURNAMES ({ \
        "Stewart", "Maclaine", "McClain", "McLain", "MacLayne", \
        "MacLean", "Lane", "Laine", "Lain", "Layne", \
        "Lean", "McFadyen", "MacFadden", "McPhadon", \
        "McPhadzean", "Fadden", "MacCormack", "McCormick", \
        "Cormack", "Cormick", "MacGillivray", "MacIlvora", \
        "MacBay", "MacVay", "MacAvoy", "Avoy", "MacEvoy", \
        "Evoy", "MacFetridge", "Patton", "Patten", "Paton", \
        "Peden", "Douie", "Huie", "Beaton", "Black", "Clanachan", \
                  })

/*
 * List of clans and their colours.
 */
#define CLAN_CLRS "CLRS"  /* Index pointing to the clan colours */
#define CLANS ([ \
        "MacDunn"    : ([ CLAN_CLRS : ({ "black", "white"   }), ]),  \
        "Lohrayn"    : ([ CLAN_CLRS : ({ "purple", "white" }), ]), \
        "MacTabor"   : ([ CLAN_CLRS : ({ "blue", "white" }), ]),     \
        "MacFadden"  : ([ CLAN_CLRS : ({ "green", "purple" }), ]),  \
        "MacVay"     : ([ CLAN_CLRS : ({ "white", "red" }), ]),     \
        "Clanachan"  : ([ CLAN_CLRS : ({ "grey", "red" }), ]),      \
    ])

/*
 * The following are neccessary to the guild server.
 */
#define MLC(x)  (x = lower_case(x))
#define CAP(x)  (x = capitalize(x))
#define SAVE    file_name(this_object())

/*
 * Indexes into the members mapping
 */
#define MAGE    0       /* Time joined field */
#define SNAME   1       /* Surname field */
#define CNAME   2       /* Clan field */

/*
 * Indexes into the clans mapping
 */
#define HAGE    0       /* Time joined the clan */
#define HBY     1       /* Who interred us into the clan */

#endif __GUILD_DEFS__
