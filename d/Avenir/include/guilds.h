/*
 * This file contains the list for all (well, most) active guilds
 * in the game. To see if someone is a member of, say, the rangers,
 * just do GMEMBER(TP, ORANGER)
 *
 * Modification Log:
 *   Cirion, August 8th 1996     Created the file
 *
 */
/* Is 'who' a member of the guild named 'guild'? */
#define GMEMBER(who, guild) \
    (((who)->query_guild_name_occ() == (guild) ) || \
     ((who)->query_guild_name_lay() == (guild) ) || \
     ((who)->query_guild_name_race() == (guild) ))

/* Support for guilds that use hidden titles - is 'who' */
/* obviousley a member of the guild named 'guild'?      */
#define GMEMBER_APPARANT(who, guild) \
    ((((who)->query_guild_name_occ() == (guild)) \
                && (!(who->query_incognito_occ()))) || \
     (((who)->query_guild_name_lay() == (guild)) \
                && (!(who->query_incognito_occ()))) || \
     (((who)->query_guild_name_race() == (guild)) \
                && (!(who->query_incognito_occ()))) )

#define MGUILDS(who) ({ who->query_guild_name_occ(), \
                        who->query_guild_name_lay(), \
                        who->query_guild_name_race() }) - ({ 0 })

/* Occuptaional guilds, O<guildname> */
#define OGLADIATOR    "Gladiator guild"
#define OCALIA        "Calian warrior's guild"
#define ORANGER       "Gondorian Rangers Guild"
#define OMONK         "Ancient Kaheda Order"
#define OANGMAR       "Angmar Army"
#define OKNIGHT       "Solamnian Knights"
#define OMAGE         "Morgul Mages"
#define OMYSTIC       "The Ancient Mystic Order"
#define OUNION        "Union of the Warriors of Shadow"
#define OVAMP         "Vampires of Emerald"
#define OWIZ          "Wizards of High Sorcery"
// #define ODKHIRAA      "DK of Khiraa"
// #define OLKHIRAA      "LP of Khiraa"

/* Layman guilds, L<guildname> */
#define LTHIEF        "Cabal of Hiddukel"
#define LMYSTIC       "The Ancient Mystic Mages"
#define LSENTRY       "Sentries of Solamnia"
#define LCLERIC       "Solamnian Knight Clerics"
#define LHERALD       "Heralds of the Valar"
#define LTRICK        "Tricksters"
#define LMONK         "Ancient Kaheda Order"
#define LANGMAR       "Angmar Army"
#define LSMITH        "The Smiths Guild"
#define LMINSTRIL     "The August Order of Minstrels"
#define LELEMENTAL    "Elemental Worshippers of Calia"
#define LCADET        "Cadets of Gelan"
#define LDISCIPLE     "The Disciples of Dark Song"


/* Race guilds, R<guildname> */
#define RROCK         "Rockfriend guild"
#define RTRAVELLER    "Traveller guild"
#define RDUNEDAIN     "Dunedain"
#define RINVENTOR     "Inventors"
#define RFANG         "Red Fang Guild"
#define RDROW         "Drow race guild"
#define RWILD         "Wildrunner guild"
#define RHOBBIT       "Adventuresome Hobbits Guild"

#define ALLGUILDS ({ OGLADIATOR, OCALIA, ORANGER, OMONK, OANGMAR, OKNIGHT, OMAGE, \
                     OMYSTIC, OUNION, OVAMP, OWIZ, \
                     LTHIEF, LMYSTIC, LSENTRY, LCLERIC, LHERALD, LTRICK, LMONK, LANGMAR, \
                     LSMITH, LMINSTRIL, LELEMENTAL, LCADET, LDISCIPLE, \
                     RROCK, RTRAVELLER, RDUNEDAIN, RINVENTOR, RFANG, RDROW, RWILD, RHOBBIT })
