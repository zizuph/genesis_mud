#define WOHS_GUILD_NAME          "Wizards of High Sorcery"
#define WOHS_GUILD_SHORT_NAME    "wohs"
#define WOHS_GUILD_TYPE          "occupational"
#define WOHS_GUILD_STYLE         "magic"
#define GUILD_TAX_WOHS	         38

#define SOHM_DIR             "/d/Krynn/guilds/sohm/"
#define WOHS_DIR	     "/d/Krynn/guilds/wohs/"

// data for WoHS stored in SoHM data file
#define WOHS_DATA            SOHM_DIR + "data/"
#define WOHS_LIBS            SOHM_DIR + "lib/"

#define WOHS_HELP            WOHS_DIR + "help/"
#define WOHS_OBJS            WOHS_DIR + "objs/"
#define WOHS_ROOM            WOHS_DIR + "room/"
#define WOHS_LOGS            WOHS_DIR + "logs/"
#define WOHS_SHADOWS         WOHS_DIR + "shadows/"
#define WOHS_SOULS           WOHS_DIR + "souls/"
#define WOHS_TEST            WOHS_DIR + "test/"
#define WOHS_NPCS            WOHS_DIR + "npcs/"

#define WOHS_SPELLS_HELP     (SOHM_DIR + "help/spells/")

// spells for WoHS are in the SoHM spell directory
#define WOHS_SPELLS          SOHM_DIR + "spells/"
#define WOHS_SPELL_OBJS      SOHM_SPELLS + "objs/"

#define WOHS_BOARD_NOTES     WOHS_DIR + "board_notes/"

#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_INT, SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 20, TS_DIS })

// Guild Locations
#define WOHS_STARTROOM       ("/d/Krynn/wayreth/tower/sleeproom")
#define WOHS_JOINROOM        (WOHS_ROOM + "joinroom")
#define WOHS_TEST_BASE       WOHS_TEST + "test_base"
#define WOHS_TEST_OUT        WOHS_TEST + "test_base_out"


// Shadows and Souls
#define WOHS_SOUL        (WOHS_SOULS   + "wohs_soul")
#define WOHS_SHADOW      (WOHS_SHADOWS + "wohs_shadow")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")

// To avoid being able to cast SoHM and WoHS spells in parallel, they share the
// same spell ability group.
#define WOHS_SPELL_ABILITY_GROUP "School of High Magic"

#define WOHS_GUILD_SKILL  108700
#define WOHS_GUILD_STAT   108701

// 37 million guild exp or 240 guild stat for top level worked out through the formula
// MIN(MAX_GUILD_LEVEL, WOHS_GUILD_STAT_FORMULA / WOHS_GUILD_LEVEL_MODIFIER);

#define WOHS_GUILD_STAT_FORMULA(x)  (x)->exp_to_stat((x)->query_skill(WOHS_GUILD_STAT))
#define MAX_GUILD_LEVEL             12
#define WOHS_GUILD_LEVEL_MODIFIER   20
#define WOHS_GUILD_LEVEL(x)         MIN(MAX_GUILD_LEVEL, WOHS_GUILD_STAT_FORMULA(x) / WOHS_GUILD_LEVEL_MODIFIER)
#define WOHS_BASE_GUILD_LEVEL(x)    (x)->stat_to_exp((WOHS_GUILD_LEVEL(x) * WOHS_GUILD_LEVEL_MODIFIER));
#define WOHS_NEXT_GUILD_LEVEL(x)    (x)->stat_to_exp(((WOHS_GUILD_LEVEL(x) + 1) * WOHS_GUILD_LEVEL_MODIFIER))

#define QUERY_WHITE_COUNCIL(x)  (WOHS_MANAGER->query_is_council_white() == (x)->query_real_name())
#define QUERY_RED_COUNCIL(x)    (WOHS_MANAGER->query_is_council_red() == (x)->query_real_name()) 
#define QUERY_BLACK_COUNCIL(x)  (WOHS_MANAGER->query_is_council_black() == (x)->query_real_name())
#define QUERY_IS_RENEGADE(x)    (WOHS_MANAGER->query_renegade_wohs((x)->query_real_name()))
#define QUERY_IS_COUNCIL(x)     (WOHS_MANAGER->query_is_council_white() == (x)->query_real_name() || \
                                 WOHS_MANAGER->query_is_council_red() == (x)->query_real_name() || \
                                 WOHS_MANAGER->query_is_council_black() == (x)->query_real_name())

// Archmage is a level within the guild above 1st Circle, so levels 11 (10) to 13 (12)
#define QUERY_IS_ARCHMAGE(x)    (((x)->query_guild_level_occ()) > 9)

#define WOHS_COUNCIL  ({ WOHS_MANAGER->query_is_council_black(), \
                         WOHS_MANAGER->query_is_council_red(), \
                         WOHS_MANAGER->query_is_council_white() })

// Master Objects stored in SoHM data file
#define WOHS_MANAGER     (WOHS_LIBS + "sohm_manager")

// Guild NPCS
#define WOHS_GUILDMASTER (WOHS_NPCS + "parsalian")
#define WIZ_GUILDMASTER   ({ "arman" })

// Useful Macros
#define IS_GUILDMASTER(x)    IN_ARRAY(x->query_real_name(), SECURITY->query_guild_masters(GUILD_SHORT_NAME))
#define IS_KRYNN_WIZ(x)      IN_ARRAY(x->query_real_name(), SECURITY->query_domain_members("krynn"))
#define WOHS_IS_MEMBER(x)    (x)->query_guild_member(WOHS_GUILD_NAME)
#define QUERY_WOHS_ROBE(x)   (WOHS_MANAGER->query_wohs_order_colour(x))

#define DEBUG(x)	     find_player("arman")->catch_msg("[WoHS] " + x + "\n")

// Other Defines
#define WOHS_I_CONFIRM_JOIN     "_wohs_i_confirm_join"
#define WOHS_I_CONFIRM_LEAVE    "_wohs_i_confirm_leave"
#define WOHS_GUILD_OBJECT       (WOHS_OBJS + "spellbook")
#define WOHS_ROBE               (WOHS_OBJS + "mage_robe")
#define WOHS_INELIGIBLE_RACES   ({"dwarf","orc","goblin","kender","minotaur","hobgoblin","ogre"})


#define WOHS_CANTRIP_SPELL      1
#define WOHS_MINOR_SPELL        2
#define WOHS_LESSER_SPELL       3
#define WOHS_GREATER_SPELL      4
#define WOHS_ADVANCED_SPELL     5
