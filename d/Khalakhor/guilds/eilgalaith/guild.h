#ifndef __GUILD_DEFS__
#define __GUILD_DEFS__

#include "/d/Khalakhor/sys/basic.h"

#define GUILD_MASTER    "damaris"

#define GUILD_NAME      "Eil-Galaith"
#define GUILD_STYLE     "race"
#define GUILD_TAX       4
#define GUILD_MIN_ALIGN 189


#define GUILD_DIR       "/d/Khalakhor/guilds/eilgalaith/"
#define ARM             (GUILD_DIR + "arm/")
#define MESSENGER_DIR   (GUILD_DIR + "messenger/")
#define HELP            (GUILD_DIR + "help/")
#define LOG            (GUILD_DIR + "log/")
#define NPC             (GUILD_DIR + "npc/")
#define ROOM            (GUILD_DIR + "room/")
#define SCROLLS         (GUILD_DIR + "scrolls/")
#define SPELLS          (GUILD_DIR + "spells/")
#define WEP             (GUILD_DIR + "wep/")

#define MESSENGER_BASE  (MESSENGER_DIR + "messenger_base")
#define GUILD_ROOM      (ROOM + "guild_room")

#define SCROLL          (GUILD_DIR + "scroll")
#define SHADOW          (GUILD_DIR + "shadow")
#define SERVER          (GUILD_DIR + "server")
#define SOUL            (GUILD_DIR + "soul")
#define OBJECT          (GUILD_DIR + "mantle")
#define OBJECT_ID       "_eil_elves_emblem"
#define GLOBE_ID        "_eil-galaith_globe_"
#define GUILD_SUBLOC    "_eil_elves_subloc"
#define STARTLOC        (ROOM + "start")
#define GLOG            (LOG + "log")
#define INFO_LOG        (LOG + "info_log")
#define FRUIT_PICK      (ROOM + "fruit_pick")
#define IS_MEMBER(x)    (x->query_guild_member(GUILD_NAME))

#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
   (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) :\
   (write_file(file, ctime(time()) + ": " + entry + "\n")))

/*
 * List of surnames to choose from when joining.
 */
#define SURNAMES ({ \
        "Alinau", "Ailia", \
        "Caehorn", "Cailith", "Calaith", "Carthos", \
        "Driliau","Drilqu", "Drilaith", \
        "Eilaith", "Ellilith", "Elith", \
        "Furith", "Filian", \
        "Gilaoth", "Gili", \
        "Ililao", "Ilidra", "Illith", \
        "Jilaith", "Juju", "Jilio", "Jilouro", "Jilktuo", \
        "Khilaith", "Khalith", "Khilarith", \
        "Lalaith", "Liliam", "Lilyl", "Lief", \
        "Milio", "Miltuo", "Meljo", \
        "Nylo", "Nyldro", "Nyldrea", \
        "Quillith", "Quilia",\
        "Rylo", "Rizo", "Rilio", \
        "Sillaith", "Silith", \
        "Tranou", "Trilio", "Trilia", \
        "Uluith", "Utilou", "Ulaith", \
        "Vilio", "Vonou", "Vedri", \
        "Welis", "Wilan", "Wylith", \
        "Xelith", "Xenil", "Xilio", \
        "Zenul", "Zilith", "Zylil", \
    })

/*
 * List of houses and the colours of the house.
 */
#define HOUSE_CLRS "CLRS"  /* Index pointing to the house colours */
#define HOUSES ([ \
           "Ailia" : ([ HOUSE_CLRS : ({ "turquoise", "copper" }), ]), \
         "Driliau" : ([ HOUSE_CLRS : ({ "sapphire",    "gold" }), ]), \
         "Eilaith" : ([ HOUSE_CLRS : ({ "saffron", "cerulean" }), ]), \
        "Ellilith" : ([ HOUSE_CLRS : ({ "emerald",   "silver" }), ]), \
         "Jilaith" : ([ HOUSE_CLRS : ({ "emerald",     "gold" }), ]), \
       "Khilarith" : ([ HOUSE_CLRS : ({ "sapphire",  "silver" }), ]), \
        "Quillith" : ([ HOUSE_CLRS : ({ "jade",      "silver" }), ]), \
          "Silith" : ([ HOUSE_CLRS : ({ "pearl",   "hyacinth" }), ]), \
        "Sillaith" : ([ HOUSE_CLRS : ({ "sable",     "silver" }), ]), \
          "Uluith" : ([ HOUSE_CLRS : ({ "ruby",       "ebony" }), ]), \
          "Wylith" : ([ HOUSE_CLRS : ({ "jade",        "gold" }), ]), \
          "Xelith" : ([ HOUSE_CLRS : ({ "crimson",     "gold" }), ]), \
    ])

/*
 * The following are neccessary to the guild server.
 */
#define MLC(x)  (x = lower_case(x))
#define SAVE    file_name(this_object())

/*
 * Indexes into the members mapping
 */
#define MAGE    0       /* Time joined field */
#define SNAME   1       /* Surname field */
#define MRACE   2       /* Race selector field */
#define HNAME   3       /* House field */

/*
 * Indexes into the houses mapping
 */
#define HAGE    0       /* Time joined the house */
#define HBY     1       /* Who interred us into the house */

#endif __GUILD_DEFS__
