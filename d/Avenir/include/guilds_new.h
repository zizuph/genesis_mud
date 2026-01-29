/*
 * This file contains the list for all (well, most) active guilds
 * in the game. To see if someone is a member of, say, the rangers,
 * just do GMEMBER(TP, ORANGER)
 *
 * Modification Log:
 *   Cirion, August 8th 1996     Created the file
 *
 *   Lilith Oct 2021: Comprehensive update of guilds.
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
#define OAOD          "Army of Darkness"
#define OANGMAR       "Angmar Army"
#define OARCHERS      "Ansalon Elvish Archers"
#define OCALIA        "Calian warrior's guild"
#define ODRAGARM      "Dragonarmy"
#define OELEMENTAL    "Elemental Clerics of Calia"
#define OFK           "Fire Knives"
#define OGLADIATOR    "Gladiator guild"
#define OKENDER       "Secret Society of Uncle Trapspringer"
#define OKNIGHT       "Solamnian Knights"
#define ORANGER       "Rangers of the Westlands"
#define OMONK         "Order of the Dragon"
#define OMAGE         "Morgul Mages"
#define OMERCS        "Free Mercenary Guild"
#define ONEIDAR       "Dwarven Warriors of the Neidar Clan"
#define OPATROL       "Patrol Guild of Silverdell"
#define OPOT          "Priests of Takhisis"
#define OSOHM         "School of High Magic"
#define OTHORN        "Thornlin Militia"
#define OUNION        "Union of the Warriors of Shadow"
#define OVAMP         "Vampires of Faerun"
#define OWARLOCK      "Warlocks of Faerun"
#define OWIZ          "Wizards of High Sorcery"

/* Layman guilds, L<guildname> */
#define LACAD         "Academy of Elemental Arts"
#define LANGMAR       "Angmar Army"
#define LARCHERS      "Ansalon Elvish Archers"
#define LBLADE        "Blademasters of Khalakhor"
#define LCADET        "Cadets of Gelan"
#define LGARDENER     "Gardeners of Gont"
#define LELEMCLER     "Elemental Clerics of Calia"
#define LHERALD       "Heralds of the Valar"
#define LKNIGHTS      "Knights of Solamnia"
#define LMINSTRIL     "The August Order of Minstrels"
#define LMINO         "Bloodsea Minotaurs"
#define LMONK         "Order of the Dragon"
#define LPIRATE       "Pirate of the Bloodsea"
#define LPOT          "Priests of Takhisis"
#define LRAIDERS      "Raiders of Throtyl"
#define LELEMSEEK     "Elemental Seekers of Calia"
#define LSHIELD       "Shieldbearers of Iron Delving"
#define LSMITH        "The Smiths Guild"
#define LSTARS        "Holy Order of the Stars"
#define LTEMPLAR      "Templars of Takhisis"
#define LTHIEF        "Cabal of Hiddukel"
#define LTHORN        "Thornlin Militia"
#define LTRICK        "Tricksters"
#define LVAMP         "Vampires of Faerun"
#define LWARLOCK      "Warlocks of Faerun"
#define LWIZ          "Wizards of High Sorcery"
#define LELEMWOR      "Elemental Worshippers of Calia"

/* Craft Guilds, C<guildname> */
#define CGARDENER     "Gardeners of Gont"
#define CHALFLINGS    "Halflings of Faerun"
#define CMARINERS     "Mariners of Genesis"
#define CPATROL       "Patrol Guild of Silverdell"
#define CSMITH        "The Smiths Guild"

/* Race guilds, R<guildname> */
#define RAMAZON       "Amazon racial guild"
#define RAOD          "Army of Darkness"
#defone RCLANS        "Clans of Khalakhor"
#define RDROW         "Drow of Underdark"
#define RDUN          "Dunedain"
#define REIL          "Eil-Galaith"
#define RFANG         "Red Fang Guild"
#define RGRUNTS       "Grunts guild"
#define RHALFLINGS    "Halflings of Faerun"
#define RHOBBIT       "Adventuresome Hobbits Guild"
#define RINVENTOR     "Gnomish Inventors"
#define RKRYNN        "Krynn race guild"
#define RNOLDOR       "Noldor of Imladris"
#define RORCS         "Orcs of Middle Earth"  
#define RROCK         "Rockfriend guild"
#define RTHANAR       "Thanar race guild"
#define RTRAVELLER    "Traveller guild"
#define RVAMP         "Vampires of Faerun"
#define RWILD         "Wild Elves Guild"

#define OGUILDS   ({ OAOD, OANGMAR, OARCHERS, OCALIA, ODRAGARM, OELEMENTAL, \
                     OFK, OGLADIATOR, OKENDER, OKNIGHT, ORANGER, OMONK, \
					 OMAGE, OMERCS, ONEIDAR, OPATROL, OPOT, OSOHM, OTHORN, \
                     OUNION, OVAMP, OWARLOCK, OWIZ })

#define LGUILDS   ({ LACAD, LANGMAR, LARCHERS, LBLADE, LCADET, LGARDENER, \
                     LELEMCLER, LHERALD, LKNIGHTS, LMINSTRIL, LMINO, LMONK, \
					 LPIRATE, LPOT, LRAIDERS, LELEMSEEK, LSHIELD, LSMITH, \
					 LSTARS, LTEMPLAR, LTHIEF, LTHORN, LTRICK, LVAMP, \
					 LWARLOCK, LWIZ, LELEMWOR })

#define CGUILDS  ({ CGARDENER, CHALFLINGS, CMARINERS, CPATROL, CSMITH }) 

#define RGUILDS  ({ RAMAZON, RAOD, RCLANS, RDROW, RDUN, REIL, RFANG, \
                    RGRUNTS, RHALFLINGS, RHOBBIT, RINVENTOR, RKRYNN, \
					RNOLDOR, RORCS, RROCK, RTHANAR, RTRAVELLER, RVAMP, \
					RWILD })

#define ALLGUILDS ({ OAOD, OANGMAR, OARCHERS, OCALIA, ODRAGARM, OELEMENTAL, \
                     OFK, OGLADIATOR, OKENDER, OKNIGHT, ORANGER, OMONK, \
					 OMAGE, OMERCS, ONEIDAR, OPATROL, OPOT, OSOHM, OTHORN, \
                     OUNION, OVAMP, OWARLOCK, OWIZ, \
					 LACAD, LANGMAR, LARCHERS, LBLADE, LCADET, LGARDENER, \
                     LELEMCLER, LHERALD, LKNIGHTS, LMINSTRIL, LMINO, LMONK, \
					 LPIRATE, LPOT, LRAIDERS, LELEMSEEK, LSHIELD, LSMITH, \
					 LSTARS, LTEMPLAR, LTHIEF, LTHORN, LTRICK, LVAMP, \
					 LWARLOCK, LWIZ, LELEMWOR \
					 CGARDENER, CHALFLINGS, CMARINERS, CPATROL, CSMITH, \
					 RAMAZON, RAOD, RCLANS, RDROW, RDUN, REIL, RFANG, \
                     RGRUNTS, RHALFLINGS, RHOBBIT, RINVENTOR, RKRYNN, \
				   	 RNOLDOR, RORCS, RROCK, RTHANAR, RTRAVELLER, RVAMP, \
                     RWILD })
					 
