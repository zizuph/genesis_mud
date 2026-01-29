/**********************************************************************
 * - guild.h                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/

#ifndef __GUILD_DEFS__
#define __GUILD_DEFS__

#define GUILD_MASTER    "damaris"

#define GUILD_NAME      "Thanar race guild"
#define GUILD_STYLE     "race"
#define GUILD_TYPE      "race"
#define GUILD_TAX       4


#define GUILD_DIR       "/d/Raumdor/guilds/thanar/"
#define ARM             (GUILD_DIR + "arm/")
#define MESSENGER_DIR   (GUILD_DIR + "messenger/")
#define HELP            (GUILD_DIR + "help/")
#define LOG             (GUILD_DIR + "log/")
//#define NPC             (GUILD_DIR + "npc/")
#define ROOM            (GUILD_DIR + "room/")
#define SCROLLS         (GUILD_DIR + "scrolls/")
#define SPELLS          (GUILD_DIR + "spells/")
#define WEP             (GUILD_DIR + "wep/")

#define GUILD_ROOM      (ROOM + "guild_room")

#define SCROLL          (GUILD_DIR + "scroll")
#define SHADOW          (GUILD_DIR + "shadow")
#define SERVER          (GUILD_DIR + "server")
#define SOUL            (GUILD_DIR + "soul")
#define OBJECT          (GUILD_DIR + "cloak")
#define OBJECT_ID       "_thanar_emblem"
#define GUILD_SUBLOC    "_thanar_subloc"
#define STARTLOC        (ROOM + "start")
#define GLOG            (LOG + "log")
#define INFO_LOG        (LOG + "info_log")

#define IS_MEMBER(x)    (x->query_guild_member(GUILD_NAME))

#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
   (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) :\
   (write_file(file, ctime(time()) + ": " + entry + "\n")))


#define VALID_SUBRACES ({"human", "wraith"})
/*
 * List of families to choose from when joining.
 */
#define SURNAMES ({ \
        "Achard", "Adeney", "Alevi", "Bachiler", "Bladin", "Bonel", \
        "Caillot", "Carnet", "Chandos", "Damours", "Deven", "Durerie", \
        "Duval", "Etri", "Elers", "Eveque", "Faintree", "Faucon", \
        "Gael", "Gouel", "Gothin", "Gueron", "Halacre", "Harcourt", \
        "Ilis", "Inel", "Iswal", "Jasin", "Jezlin", "Keth", "Kildian", \
        "Khohm", "Linesi", "Ligonier", "Lorz", "Lumion", "Machel", \
        "Magilis", "Mathan", "Nelond", "Neot", "Nesdin", "Nestle", \
        "Omand", "Ormond", "Osmont", "Painel", "Pasquier", "Picard", \
        "Pevrel", "Quesnel", "Quistle", "Rames", "Rennes", "Reviers", \
        "Saisset", "Senlis", "Simnel", "Talvace", "Tibon", "Tirel", \
        "Trelli", "Truan", "Ulin", "Ulnaris", "Urry", "Veci", \
        "Ventris", "Vesci", "Villon", "Warci", "Watteau", "Wissant", \
        "Wistin", "Xyin", "Yulin", "Zenar", "Zece", \
    })

/*
 * List of coven and the colours of the coven.
 */
#define COVEN_CLRS "CLRS"  /* Index pointing to the coven colours */
#define COVENS ([ \
          "Blade" : ([ COVEN_CLRS : ({ "onyx",     "silver" }), ]), \
         "Elemin" : ([ COVEN_CLRS : ({ "saphire",  "silver" }), ]), \
          "Flame" : ([ COVEN_CLRS : ({ "ruby",       "gold" }), ]), \
           "Goth" : ([ COVEN_CLRS : ({ "onyx",       "gold" }), ]), \
      "Hellstone" : ([ COVEN_CLRS : ({ "saphire",    "gold" }), ]), \
           "Magi" : ([ COVEN_CLRS : ({ "emerald",  "silver" }), ]), \
    ])

/*
 * List of Lower level titles.
 */
#define TITLE1 ({ \
   "Novice", "Trainee",  "Beginner", "Apprentice", "Learned", \
   "Enthusiast", "Fervent", "Unforgiving", "Callous", "Harsh", "Severe", \
   "Cruel", "Ruthless", "Merciless", "Heartless", "Passionate", "Adored", \
   "Dedicated", "Devoted", "Fanatical", "Obsessive", "Loyal", "Zealous", \
   })

/*
 * List of Ranking titles.
 */
   
#define RANK ({ "Follower", "Disciple", "Extremist", "Guardian" })

/*
 * List of Higher level titles.
 */

#define TITLES ({ \
               "Feared Assassin", \
               "Zealous Executioner", \
               "Celebrated Inquisitor", \
               "Legendary Grand Inquisitor" })
/*
 * Special Title.
 */

#define SPECIAL_TITLE  "The Omnipotent Avatar of Thanar"
#define LIBRARY_TITLE  "Learned Scholar of the Thanarian Order"

/*
 * The following are neccessary to the guild server.
 */
#define MLC(x)  (x = lower_case(x))
#define MCAP(x) (x = capitalize(x))
#define SAVE    file_name(this_object())

/*
 * Indexes into the members mapping
 */
#define MAGE    0       /* Time joined field */
#define FNAME   1       /* Family field */
#define SPEC    2       /* Race selector field */
#define CNAME   3       /* Coven field */

/*
 * Indexes into the covens mapping
 */
#define HAGE    0       /* Time joined the coven */
#define HBY     1       /* Who interred us into the coven */

#endif GUILD_DEFS
