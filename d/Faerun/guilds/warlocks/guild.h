/*  /d/Faerun/guilds/warlocks/guild.h
 *
 *  Guildheader.
 *
 *  Nerull 2017.
 *
 */

//#ifndef __WARLOCKS_DEFINITIONS__
//#define __WARLOCKS_DEFINITIONS__

/* outdated, but kept for backwards compatibility */
#define WARLOCK_GUILDDIR         "/d/Faerun/guilds/warlocks/"

/* directory paths */
#define WARLOCK_GUILD_DIR       "/d/Faerun/guilds/warlocks/"

#define WARLOCK_BOARDS_DIR      (WARLOCK_GUILD_DIR + "boards/")
#define WARLOCK_DOC_DIR         (WARLOCK_GUILD_DIR + "doc/")
#define WARLOCK_HELP_DIR        (WARLOCK_GUILD_DIR + "help/")
#define WARLOCK_LIBRARY_DIR     (WARLOCK_GUILD_DIR + "library/")
#define WARLOCK_LOG_DIR         (WARLOCK_GUILD_DIR + "log/")
#define WARLOCK_MASTER_DIR      (WARLOCK_GUILD_DIR + "master/")
#define WARLOCK_NPC_DIR         (WARLOCK_GUILD_DIR + "npc/")
#define WARLOCK_OBJ_DIR         (WARLOCK_GUILD_DIR + "obj/")
#define WARLOCK_ROOMS_DIR       (WARLOCK_GUILD_DIR + "rooms/")
#define WARLOCK_SHADOWS_DIR     (WARLOCK_GUILD_DIR + "shadows/")
#define WARLOCK_SOULS_DIR       (WARLOCK_GUILD_DIR + "souls/")
#define WARLOCK_SPELLOB_DIR     (WARLOCK_SPELLS_DIR + "objs/")
#define WARLOCK_SPELLS_DIR      (WARLOCK_GUILD_DIR + "spells/")
#define STORE_ROOM              (WARLOCK_ROOMS_DIR + "store")

#define WARLOCK_SAVE_FILE       (WARLOCK_MASTER_DIR +"log/warlock_save")
#define DESECRATION             (WARLOCK_MASTER_DIR +"log/desecration")
#define DESECRATION_PRIMER      (WARLOCK_MASTER_DIR +"log//desecration_primer")

#define MROOM_DIR                "/d/Faerun/mere/rooms/"
#define TELEPORT_DIR             "/d/Faerun/mere/rooms/"

// Joiningroom properties and premises
#define SECOND_REQUEST           "_second_war_request"
#define I_TOUCHED_TAPESTRY       "_i_touched_tapestry"
#define REQ_AVG                  20    

#define WAR_SPELL_16            (WARLOCK_MASTER_DIR +"log/war_spell_16")
#define WAR_SPELL_17            (WARLOCK_MASTER_DIR +"log/war_spell_17")
#define WAR_SPELL_18            (WARLOCK_MASTER_DIR +"log/war_spell_18")
#define WAR_SPELL_19            (WARLOCK_MASTER_DIR +"log/war_spell_19")

/* Library files and shortcuts */
#define LIBRARY_BOOKS_DIR       (WARLOCK_LIBRARY_DIR + "books")
#define LIBRARY_CARD            "_warlock_library_card"
/* end library */

/* guild item */
#define GUILD_ITEM              (WARLOCK_OBJ_DIR + "guild_item")
#define GUILD_ITEM1             (WARLOCK_OBJ_DIR + "warlock_robe1")
#define GUILD_ITEM2             (WARLOCK_OBJ_DIR + "warlock_robe2")
#define GUILD_ITEM3             (WARLOCK_OBJ_DIR + "warlock_robe3")
#define GUILD_ITEM4             (WARLOCK_OBJ_DIR + "warlock_robe4")
#define GUILD_ITEM_NAME         "_warlock_guild_item"


/* files */
#define WARLOCK_TELEP_HOME_LOC  (WARLOCK_ROOMS_DIR + "start")
#define WARLOCK_STD_ROOM        (WARLOCK_ROOMS_DIR + "std/warlock_std_room")
#define WARLOCK_MASTER          (WARLOCK_MASTER_DIR + "lay_warlock_master")
#define WARLOCK_MAPPINGS        (WARLOCK_MASTER_DIR + "lay_warlock_mappings")


#define WARLOCK_MIN_RANK_MEMBER  0
#define WARLOCK_MAX_RANK_MEMBER  22

#define MEMBER_LIST_UTILITY      ("/d/Faerun/guilds/warlocks/souls/member_list_util")

#define WARLOCK_SPELL_OBJECT     "War_Spell_Object"

#define SPELL_MANAGER_SOUL       "/d/Genesis/specials/guilds/souls/spell_manager_soul"
#define MANA_SHADOW              "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define RIT1_LOG(x,y)       write_file(WARLOCK_MASTER_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define RIT2_LOG(x,y)       write_file(WARLOCK_MASTER_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define RIT3_LOG(x,y)       write_file(WARLOCK_MASTER_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define SW                       shadow_who

// 1 of we are testing all spells. Should be 0 when live.
#define SPELLTESTING             0

// 1 for no components. For testing. Should be 0 when live.
#define SPELLTESTING_NOCOMPS     0

// Number of spellcharges per charm used
#define CHARM_CHARGES            12

// Guildname, type & tax --- ---------------
#define GUILD_NAME               "Warlocks of Faerun"
#define WARLOCK_NAME             "Warlocks of Faerun"
#define TYPE_LAY                 "magic"
#define TAX_LAY                  18

#define IS_MEMBER(p) ((p)->query_guild_name_lay() == WARLOCK_NAME)
//-----------------------------------------

// Support strings
#define WARLOCK_NAME_SINGULAR    "Warlock"
#define GUILDNAME_STRING         "Warlocks"

//Guildtitles - nonpatron 
#define NONPATR_TITLE0       "Fresh Servant of the Whispess"
#define NONPATR_TITLE1       "Fresh Servant of the Whispess"
#define NONPATR_TITLE2       "Curious Servant of the Whispess"
#define NONPATR_TITLE3       "Convinced Servant of the Whispess"
#define NONPATR_TITLE4       "Crazed Servant of the Whispess"
#define NONPATR_TITLE5       "Mad Servant of the Whispess"
#define NONPATR_TITLE6       "Frenzied Servant of the Whispess"
#define NONPATR_TITLE7       "Fanatic Servant of the Whispess"

#define NONPATR_TITLE8       "Fanatic Servant of the Whispess"
#define NONPATR_TITLE9       "Fanatic Servant of the Whispess"
#define NONPATR_TITLE10      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE11      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE12      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE13      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE14      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE15      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE16      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE17      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE18      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE19      "Fanatic Servant of the Whispess"
#define NONPATR_TITLE20      "Fanatic Servant of the Whispess"


// Guildtitles - patron 1 (Archfiend) / Asmodeus
#define PATR1_TITLE0             ""
#define PATR1_TITLE1             ""
#define PATR1_TITLE2             ""
#define PATR1_TITLE3             ""
#define PATR1_TITLE4             ""
#define PATR1_TITLE5             ""
#define PATR1_TITLE6             ""

#define PATR1_TITLE7         "Minion of the Inverted Crimson Pentagram"
#define PATR1_TITLE8         "Experienced Minion of the Inverted Crimson Pentagram"
#define PATR1_TITLE9         "Dedicated Minion of the Inverted Crimson Pentagram"
#define PATR1_TITLE10        "Foul Marionette of the Flame Sea"
#define PATR1_TITLE11        "Dangerous Marionette of the Flame Sea"
#define PATR1_TITLE12        "Stout Marionette of the Flame Sea"
#define PATR1_TITLE13        "Fierce Follower of Nessus"
#define PATR1_TITLE14        "Brutal Follower of Nessus"
#define PATR1_TITLE15        "Deadly Follower Of Nessus"
#define PATR1_TITLE16        "Ruthless Acolyte of the Nine Hells"
#define PATR1_TITLE17        "Devilish Acolyte of the Nine Hells"
#define PATR1_TITLE18        "Fiendish Acolyte of the Nine Hells"
#define PATR1_TITLE19        "Chosen Candidate of Asmodeus, the Lord of the Nine Hells"
#define PATR1_TITLE20        "Chosen of Asmodeus, the Lord of the Nine Hells"

// Guildtitles - patron 2 (Great Old One) / Hastur
#define PATR2_TITLE0             ""
#define PATR2_TITLE1             ""
#define PATR2_TITLE2             ""
#define PATR2_TITLE3             ""
#define PATR2_TITLE4             ""
#define PATR2_TITLE5             ""
#define PATR2_TITLE6             ""

#define PATR2_TITLE7         "Initiate of the Yellow Sign"
#define PATR2_TITLE8         "Acolyte of the Yellow Sign"
#define PATR2_TITLE9         "Mad Acolyte of the Yellow Sign"
#define PATR2_TITLE10        "Frenzied Acolyte of Lost Carcosa"
#define PATR2_TITLE11        "Vile Acolyte of Lost Carcosa"
#define PATR2_TITLE12        "Fanatic Acolyte of Lost Carcosa"
#define PATR2_TITLE13        "Frenzied Cultist of the Black Stars"
#define PATR2_TITLE14        "Cruel Cultist of the Black Stars"
#define PATR2_TITLE15        "Eerie Cultist of the King in Yellow"
#define PATR2_TITLE16        "Dreaded High Cultist of the King in Yellow"
#define PATR2_TITLE17        "Malevolent High Cultist of the King in Yellow"
#define PATR2_TITLE18        "Morbid High Cultist of the King in Yellow"
#define PATR2_TITLE19        "Terrifying Inquisitor of the King in Yellow"
#define PATR2_TITLE20        "Emissary of the King in Yellow, Bringer of Madness and Despair"

// Guildtitles - patron 3 (Archfey) / Baba Zirana
#define PATR3_TITLE0             ""
#define PATR3_TITLE1             ""
#define PATR3_TITLE2             ""
#define PATR3_TITLE3             ""
#define PATR3_TITLE4             ""
#define PATR3_TITLE5             ""
#define PATR3_TITLE6             ""

#define PATR3_TITLE7         "Discreet Bone Collector of the Wild"
#define PATR3_TITLE8         "Bone Collector of the Wild"
#define PATR3_TITLE9         "Experienced Bone Collector of the Wild"
#define PATR3_TITLE10        "Novice Dissecter of the Old"
#define PATR3_TITLE11        "Dissecter of the Old"
#define PATR3_TITLE12        "Precise Dissecter of the Old"
#define PATR3_TITLE13        "Careful Kidnapper of the Dark Woods"
#define PATR3_TITLE14        "Efficient Kidnapper of the Dark Woods"
#define PATR3_TITLE15        "Brutal Kidnapper of the Dark Woods"
#define PATR3_TITLE16        "Dangerous Devourer of the Young"
#define PATR3_TITLE17        "Wicked Devourer of the Young"
#define PATR3_TITLE18        "Crazed Devourer of the Young"
#define PATR3_TITLE19        "Consumer of Infant Flesh, Underling of Baba Zirana"
#define PATR3_TITLE20        "Grand Consumer of Infant Flesh, Emissary of Baba Zirana"

// MINIMUM PATRON SELECTION RANK + PATRON NAMES
#define MIN_PATRON_LEVEL     6
#define PATRON1_NAME         "Asmodeus, Archfiend, Lord of the Nine Hells"
#define PATRON2_NAME         "Hastur, the Yellow King, Great Old One, Bringer of Madness and Despair"
#define PATRON3_NAME         "Baba Zirana, Archfey of the Feywild, Devourer of the Young"
#define PATRON1_NAME2        ", the Supreme Master of the Nine Hells"
#define PATRON2_NAME2        ", the Yellow King, Great Old One, Bringer of Madness and Despair"
#define PATRON3_NAME2        ", Archfey of the Feywild, Devourer of the Young"



// BASE SPELL UNLOCKS
// Follower spells
#define ASCENDSTEP_UNLOCK          2
#define COLDLIGHT_UNLOCK           3
#define WITCHSTEP_UNLOCK           4
#define SCULPTOROFFLESH_UNLOCK     5
// Patron spells
#define FULL_WARLOCK_UNLOCK        6
#define MASK_UNLOCK                7
#define ELDRITCH_SIGHT_UNLOCK      10
#define FALSELIFE_UNLOCK           13
#define REJUVENATION_UNLOCK        16
#define SCRY_UNLOCK                20
#define WARP_REALITY_UNLOCK        30
#define DEPTH_UNLOCK               40
#define INFUSION_UNLOCK            50
// --- Specialization unlocks ---
#define SHIELD_UNLOCK              60
#define FEAR_UNLOCK                70
#define MAGICSHIELD_UNLOCK         80
#define NUKE_UNLOCK                90

#define SPELL_END                  90

// Spell standard charges
#define SPELL_STD_CHARGE           15

// Ritual expiration timer        
#define COOLDOWN_EXPIRATION_TIME  20000

// Rejoin guild cooldowntime
#define COOLDOWN_REJOIN_TIME      260000

// How often the patrons will put demands on their warlocks
#define CHECK_DEMAND_ALARM        270.0


// --- Spellprops % Defs --------------
#define RESIST_LIBRARY          "/d/Genesis/specials/resist"
#define REFLECT_SUBLOC          "_reflect_spell_effect_subloc"
#define FEAR_SHADOW             WARLOCK_GUILD_DIR +"spells/objs/fear_shadow"
#define FEARED_SHADOW           WARLOCK_GUILD_DIR +"spells/objs/feared_shadow"

#define SPIKES_EFFECT           "_spikes_effect"
#define WITCHSTEP_EFFECT        "_witchstep_effect"
#define I_HAVE_BEEN_AVERSIONED  "_i_have_been_aversioned"
#define I_HAVE_BEEN_SPOOKED     "_i_have_been_spooked"
#define I_HAVE_BEEN_DREADED     "_i_have_been_dreaded"

// Limitation props
#define SHIELD_ON               "_war_shieldspell_on"
#define MR_SHIELD_ON            "_war_mrshieldspell_on"
#define HASTE_ON                "_haste_on"
#define STATBUFF_ON             "_statbuff_on"
#define ELDRITCH_SIGHT_ON       "_eldritch_sight_on"
#define SPELL_O_FAMILIAR        "_spell_o_familiar"

//#endif

