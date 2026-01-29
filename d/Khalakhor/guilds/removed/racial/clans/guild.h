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
#define NPC             (GUILD_DIR + "npc/")
#define HELP            (GUILD_DIR + "help/")
#define SCROLLS         (GUILD_DIR + "scrolls/")
#define GUILD_ROOM      (ROOM + "guild_room")
#define SCROLL          (GUILD_DIR + "scroll")
#define SHADOW          (GUILD_DIR + "shadow")
#define SERVER          (GUILD_DIR + "server")
#define SOUL            (GUILD_DIR + "soul")
#define OBJECT          (GUILD_DIR + "tartan")
#define OBJECT_ID       "_khal_clan_emblem"
#define GUILD_SUBLOC    "_khal_clan_subloc"
#define LEADER_EMBLEM_ID "_CLAN_leader_emblem"

#define GLOG            (GUILD_DIR + "log/")
#define GLOG_macvay     (GUILD_DIR + "log/macvay/")
#define GLOG_macdunn    (GUILD_DIR + "log/macdunn/")
#define GLOG_macfaolain (GUILD_DIR + "log/macfaolain/")
#define GLOG_lohrayn    (GUILD_DIR + "log/lohrayn/")
#define GLOG_macfadden  (GUILD_DIR + "log/macfadden/")
#define GLOG_mactabor   (GUILD_DIR + "log/mactabor/")
#define INFO_LOG        (GLOG + "info_log")

#define IS_MEMBER(x)    (x->query_guild_member(GUILD_NAME))
#define IS_CLANCHIEF(x) strlen(SERVER->query_clanchief(x->query_real_name()))
#define IS_KINSLAYER(x) (SERVER->query_kinslayer(x->query_real_name()))
#define MORE_OBJ "/std/board/board_more"

#define CLAN_DIR      (ROOM + "clans/")
#define MACFAOLAIN    (CLAN_DIR + "macfaolain/")
#define LOHRAYN       (CLAN_DIR + "lohrayn/")
#define MACDUNN       (CLAN_DIR + "macdunn/")
#define MACFADDEN     (CLAN_DIR + "macfadden/")
#define MACTABOR      (CLAN_DIR + "mactabor/")
#define MACVAY        (CLAN_DIR + "macvay/")



// #define IS_CLANCHIEF(x) (SERVER->query_council_member(SERVER->query_clan(x->query_real_name())) \
//                         == (x->query_real_name()))


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
        "Dochartaigh", "Domhnaill", "MacMeanmain", "Monaghan", \
        "Faolain", "Murnane","MacLochlainn","Cleburne","Aoileain", \
        "Hodhrain","MacEochagain","Seachnasaigh","Tighearnaigh", \
        "MacAmhlaoibh","Bellew","Ceallachain","Gailleang","Maoileanaigh", \
        "Cinnsealach","Caollaidhe","Thoirdealbach", \
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
        "MacVay"     : ([ CLAN_CLRS : ({ "green", "red" }), ]),     \
        "MacFaolain" : ([ CLAN_CLRS : ({ "crimson", "green" }), ]),      \
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
#define KSLYR   3       /* Kinslayer field */

/*
 * Indexes into the clans mapping
 */
#define HAGE    0       /* Time joined the clan */
#define HBY     1       /* Who interred us into the clan */


/*
 * Clan Badge/Crest Descriptions:
 */
#define MACDUNN_BADGE  "displays the crest of MacDunn. The " + \
                       "crest depicts a black swan " + \
                       "clutching a bone within its " + \
                       "twisted neck while standing " + \
                       "upon the hilt of a large claymore.\n"

#define LOHRAYN_BADGE  "displays the crest of Lohrayn. The " + \
                       "crest depicts a crow clutching " + \
                       "a bouquet of heather in one " + \
                       "claw and a dagger in the other.\n"

#define MACTABOR_BADGE "displays the crest of MacTabor. The " + \
                       "crest depicts a goshawk with " + \
                       "wings spread wide encircled by " + \
                       "a crown of laurel. Its talons " + \
                       "clutching a long-thin rapier.\n"

#define MACFADDEN_BADGE "displays the crest of MacFadden. The " + \
                        "crest depicts an eagle wearing " + \
                        "a crown while clutching swords " + \
                        "in either of its outstretched talons.\n"

#define MACVAY_BADGE    "displays the crest of MacVay. The " + \
                        "crest depicts a large double-edged " + \
                        "axe surrounded in a circlet of " + \
                        "trefoil.\n"

#define MACFAOLAIN_BADGE "displays the crest of MacFaolain. The " + \
                         "crest depicts a lion resting " + \
                         "upon two crossed axes within " + \
                         "a belted circle.\n"


#endif __GUILD_DEFS__
