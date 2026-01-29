#ifndef __GUILD_DEFS__
#define __GUILD_DEFS__

#include "/d/Khalakhor/sys/basic.h"

#define GUILD_MASTER    "damaris"

#define GUILD_NAME      "Clans of Khalakhor"
#define GUILD_STYLE     "race"
#define GUILD_TAX       0

#define GUILD_DIR       "/d/Khalakhor/guilds/clans/"

#define ARM             (GUILD_DIR + "arm/")
#define HELP            (GUILD_DIR + "help/")
#define LOG             (GUILD_DIR + "log/")
#define NPC             (GUILD_DIR + "npc/")
#define GOBJ            (GUILD_DIR + "obj/")
#define ROOM            (GUILD_DIR + "room/")
#define WEP             (GUILD_DIR + "wep/")

#define GUILD_ROOM      (ROOM + "guild_room")

#define SHADOW          (GUILD_DIR + "shadow")
#define SERVER          (GUILD_DIR + "server")
#define SOUL            (GUILD_DIR + "soul")
#define OBJECT          (GUILD_DIR + "tunic")
#define SCROLL          (GUILD_DIR + "scroll")
#define STARTLOC        (ROOM + "start")

#define OBJECT_ID       "_khal_clan_emblem"
#define GUILD_SUBLOC    "_khal_clan_subloc"

#define IS_MEMBER(x)    (x->query_guild_member(GUILD_NAME))
#define BANNER_PATH   (GOBJ + "banner")
#define BANNER_LIMIT  ({ 2, 150, "You have taken enough banner, "+ \
"leave some for others.\n", "Sorry, there are no banners available "+ \
"at this.\n" })
#define KILT_PATH   (GOBJ + "banner")
#define KILT_LIMIT  ({ 7, 150, "You have taken enough kilts, "+ \
"leave some for others.\n", "Sorry, there are no kilts available "+ \
"at this.\n" })

#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
   (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) :\
   (write_file(file, ctime(time()) + ": " + entry + "\n")))

/*
 * List of surnames to choose from when joining.
 */
#define SURNAMES ({"","Alasdair", "Amhlaigh", "a' Mhaoilein", \
        "an Aba", "an Toisich", "an t-Sagairt", "an t-Saoir", \
        "an t-Sealgair", "Aoidh", "Aonghais", "a' Phearsain", \
        "a' Phi", "Asgail", "Arnwulf", "Artair", "Caoig", "Coinnich", \
        "Cruimein", "Dhomhnaill", "Dhonnchaidh", "Dhughaill", \
        "Eacharna", "Fhearghais", "Fhionghain", "Fhionnlaigh", \
        "Griogair", "Guaire", "Gumaraid", "Iain", "IllEathain", \
        "IlleMhaoil", "IllFhaolain", "IllFhinnein", "IllIosa", \
        "Iomhair", "Leoid", "Mhuirich", "Neacail", "Neill", "Phail", \
        "Pharlain", "Rath", "Risnidh", "Suain", "Thearlaich", \
        "Thomais", "Ualraig", "a' Ghobhainn", "Deas", \
    })

/*
 * List of Clans and the colours of the Clan.
 */
#define CLAN_CLRS "CLRS"  /* Index pointing to the Clan colours */

#define CLANS ([ \
      "Clan 'IcAlasdair" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
        "Clan 'IcArtair" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
       "Clan 'IcAsgaill" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
      "Clan 'IcAmhlaigh" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Clan 'IcCaoig" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
    "Clan 'IcDhomhnaill" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
        "Na Domhnallaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Clan Griogair" : ([ CLAN_CLRS : ({ "black",     "gold" }), ]), \
       "Clan 'IGriogair" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
      "Clan 'IcAonghais" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
       "Clan an Toisich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
       "Clan an t-Saoir" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
       "Clan 'IcIomhair" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Clan 'IcAoidh" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
      "Clan 'IcCoinnich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
    "Clan 'IcFhionghain" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
    "Clan 'IcIllEathain" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Na Leathanaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
   "Clan 'IcIllFhaolain" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
   "Clan 'IcIllFhinnein" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Clan 'IcLeoid" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
            "Na Leodaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
    "Clan 'IcIlleMhaoil" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
           "Clan an Aba" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Clan 'IcNeill" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
 "Clan 'Ic a' Phearsain" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
        "Clan 'IcGuaire" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
          "Clan 'IcRath" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Clan 'IcSuain" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
 "Clan 'Ic an t-Sagairt" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
          "Na Peutanaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
            "Na Brusaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
        "Na Caimbeulaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
        "Na Camshronaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
          "Na Siosalaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Na Dughlasaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
     "Na Fearghasdanaich" : ([ CLAN_CLRS : ({ "purple",    "black" }), ]), \
    "Clan 'IcFhearghais" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
     "Na Fionnlasdanaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
   "Clan 'IcFhionnlaigh" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
         "Na Frisealaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
       "Clan 'IcIllIosa" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
           "Na Greumaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
          "Na Granndaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
    "Clan an t-Sealgair" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
          "Na Ceanadaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
       "Clan 'IcUalraig" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
      "Clan 'IcGumaraid" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
      "Na Moireasdanaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
            "Na Rothaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
             "Na Moirich" : ([ CLAN_CLRS : ({ "silver",   "blue"  }), ]), \
       "Clan 'IcNeacail" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
        "Na Robasdanaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
   "Clan 'IcDhonnchaidh" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
       "Clan Donnchaidh" : ([ CLAN_CLRS : ({ "red",      "black" }), ]), \
             "Na Rosaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
     "Clan a' Ghobhainn" : ([ CLAN_CLRS : ({ "red",    "black" }), ]), \
       "Na Stiubhartaich" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
       "Clan 'IcThomais" : ([ CLAN_CLRS : ({ "green",    "black" }), ]), \
            "Clan Aesir" : ([ CLAN_CLRS : ({ "silver", "midnight-blue" }), ]), \
            ])
            
// link to blademaster list
#define BMASTER_MAP	"/d/Khalakhor/guilds/blademasters/special/master_map"


/**********************************************************************
 * - The following are neccessary to the guild server.              - *
 **********************************************************************/
#define MLC(x)  (x = lower_case(x))
#define SAVE    file_name(this_object())

/**********************************************************************
 * - Indexes into the members mapping.                              - *
 **********************************************************************/
#define MAGE    0       /* Time joined field */
#define SNAME   1       /* Surname field */
#define CNAME   3       /* Clan field */

/**********************************************************************
 * - Indexes into the clan mapping.                            - *
 **********************************************************************/
#define CAGE    0       /* Time joined the clan */
#define CBY     1       /* Who entered us into the clan */

#endif __GUILD_DEFS__