#define GUILD_NAME               "Holy Order of the Stars"
#define GUILD_SHORT_NAME         "oots"
#define GUILD_TYPE               "layman"
#define GUILD_STYLE              "cleric"
#define GUILD_TAX                16

#define OOTS_DIR             "/d/Krynn/guilds/OotS/"

#define OOTS_DATA            OOTS_DIR + "data/"
#define OOTS_HELP            OOTS_DIR + "help/"
#define OOTS_REVELATIONS     OOTS_DIR + "revelations/"
#define OOTS_OBJS            OOTS_DIR + "obj/"
#define OOTS_ROOM            OOTS_DIR + "room/"
#define OOTS_LIVING          OOTS_DIR + "living/"
#define OOTS_LOGS            OOTS_DIR + "logs/"
#define OOTS_LIBS            OOTS_DIR + "lib/"
#define OOTS_SHADOWS         OOTS_DIR + "shadow/"
#define OOTS_SPELLS          OOTS_DIR + "spells/"
#define OOTS_SPELL_OBJS      OOTS_SPELLS + "objs/"
#define OOTS_SOULS           OOTS_DIR + "soul/"
#define OOTS_BOARD_NOTES     OOTS_DIR + "board_notes/"
#define OOTS_SPELLS_HELP     OOTS_HELP + "spells/"

#define STD_SPELL_SYSTEM     "/d/Genesis/specials/new/magic/spells/"

// Guild Locations
#define OOTS_STARTROOM       ("/d/Krynn/solace/new_village/inn_room")
#define OOTS_JOINROOM        (OOTS_ROOM + "joinroom")

// Shadows and Souls
#define OOTS_SOUL        (OOTS_SOULS   + "oots_soul")
#define OOTS_SHADOW      (OOTS_SHADOWS + "oots_shadow")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define OOTS_GUILD_SKILL  108800
#define OOTS_GUILD_XP     108801

// Master Objects
#define OOTS_MANAGER     (OOTS_LIBS + "oots_manager")

// Guild NPCS
#define OOTS_GUILDMASTER (OOTS_LIVING + "elistan")

// Stat weighting influencing spell effectiveness
#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_WIS, SKILL_WEIGHT, 20, TS_INT, SKILL_WEIGHT, 20, TS_DIS })

// Useful Macros
#define IS_OOTS(x)                  ((x)->query_guild_name_lay() == GUILD_NAME)
#define IS_GUILDMASTER(x)           IN_ARRAY(x->query_real_name(), SECURITY->query_guild_masters(GUILD_SHORT_NAME))
#define IS_KRYNN_WIZ(x)             IN_ARRAY(x->query_real_name(), SECURITY->query_domain_members("krynn"))
#define IS_MEMBER(x)                OOTS_MANAGER->query_is_member(x)
#define OOTS_LEVEL(x)               (x->query_guild_level_lay() + 1)
#define OOTS_PROGRESSION_MOD         24
#define OOTS_GUILD_STAT_FORMULA(x)  (x)->exp_to_stat((x)->query_skill(OOTS_GUILD_XP))
#define OOTS_ADD_EXP(x, y)          (x->set_skill(OOTS_GUILD_XP, x->query_skill(OOTS_GUILD_XP) + y))
#define OOTS_REDUCE_EXP(x, y)       (x->set_skill(OOTS_GUILD_XP, x->query_skill(OOTS_GUILD_XP) - y))

#define DEBUG(x)	            find_player("arman")->catch_msg("[OotS] " + x + "\n")

//Revelations
#define OOTS_ADD_REV(p,r1,r2)       OOTS_MANAGER->add_oots_revelations(p, r1, r2)
#define OOTS_QUERY_REV(p, r)        (member_array(r, m_indexes(OOTS_MANAGER->query_oots_revelations(p))) > -1)
#define OOTS_REMOVE_REV(p, r)       OOTS_MANAGER->remove_oots_revelations(p, r)
#define OOTS_REMOVE_ALL_REV(p)      OOTS_MANAGER->remove_oots_all_revelations(p)

// Other Defines
#define OOTS_I_CONFIRM_JOIN         "_oots_i_confirm_join"
#define OOTS_I_CONFIRM_LEAVE        "_oots_i_confirm_leave"
#define OOTS_GUILD_OBJECT           (OOTS_OBJS + "medallion")
#define OOTS_INELIGIBLE_RACES       ({"goblin","hobgoblin","ogre","orc"})
