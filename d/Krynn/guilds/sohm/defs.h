#define GUILD_NAME               "School of High Magic"
#define GUILD_SHORT_NAME         "sohm"
#define GUILD_TYPE               "occupational"
#define GUILD_STYLE              "magic"
#define GUILD_TAX_INITIATE       17
#define GUILD_TAX_NOVITIATE      22
#define GUILD_TAX_ASPIRANT       25

#define SOHM_DIR             "/d/Krynn/guilds/sohm/"

#define SOHM_DATA            SOHM_DIR + "data/"
#define SOHM_HELP            SOHM_DIR + "help/"
#define SOHM_OBJS            SOHM_DIR + "objs/"
#define SOHM_ROOM            SOHM_DIR + "room/"
#define SOHM_NPCS            SOHM_DIR + "npcs/"
#define SOHM_LOGS            SOHM_DIR + "logs/"
#define SOHM_LIBS            SOHM_DIR + "lib/"
#define SOHM_SHADOWS         SOHM_DIR + "shadows/"
#define SOHM_SPELLS          SOHM_DIR + "spells/"
#define SOHM_SPELL_OBJS      SOHM_SPELLS + "objs/"
#define SOHM_SOULS           SOHM_DIR + "souls/"
#define SOHM_BOARD_NOTES     SOHM_DIR + "board_notes/"

// Combat aid guild opening penalty of 10% across all spells.
// Decided to keep the combat aid reduction post opening.
// Do not change this value! - Arman Kharas
#define CAID_OPENING_MOD     1

// Guild Locations
#define SOHM_STARTROOM       ("/d/Krynn/solace/poolbottom/room/start")
#define SOHM_JOINROOM        (SOHM_ROOM + "joinroom")

// Shadows and Souls
#define SOHM_SOUL        (SOHM_SOULS   + "sohm_soul")
#define SOHM_SHADOW      (SOHM_SHADOWS + "sohm_shadow")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define SOHM_GUILD_SKILL  108700

// Master Objects
#define SOHM_MANAGER     (SOHM_LIBS + "sohm_manager")

// Guild NPCS
#define SOHM_GUILDMASTER (SOHM_NPCS + "theobald")
#define SOHM_TASKMASTER  (SOHM_NPCS + "taskmaster")
#define SOHM_TEACHER     (SOHM_NPCS + "teacher")

// Useful Macros
#define IS_GUILDMASTER(x)    IN_ARRAY(x->query_real_name(), SECURITY->query_guild_masters(GUILD_SHORT_NAME))
#define IS_KRYNN_WIZ(x)      IN_ARRAY(x->query_real_name(), SECURITY->query_domain_members("krynn"))
#define IS_MEMBER(x)         SOHM_MANAGER->query_is_member(x)

#define DEBUG(x)	     find_player("arman")->catch_msg("[SoHM] " + x + "\n")


// Other Defines
#define SOHM_I_CONFIRM_JOIN     "_sohm_i_confirm_join"
#define SOHM_I_CONFIRM_LEAVE    "_sohm_i_confirm_leave"
#define SOHM_CHANNEL_OBJECT     (SOHM_OBJS + "channel_paralyze_object")
#define SOHM_FOCUS_OBJECT       (SOHM_OBJS + "focus_obj")
#define SOHM_FOCUS_PARALYZE     (SOHM_OBJS + "focus_paralyze_object")
#define SOHM_GUILD_OBJECT       (SOHM_OBJS + "spellbook")
#define SOHM_INELIGIBLE_RACES        ({"dwarf","orc","goblin","kender","minotaur","hobgoblin","ogre"})

#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_INT, SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 20, TS_DIS })

#define SOHM_CANTRIP_SPELL      1
#define SOHM_MINOR_SPELL        2
#define SOHM_LESSER_SPELL       3
#define SOHM_GREATER_SPELL      4
#define SOHM_ADVANCED_SPELL     5

#define ELIGIBLE_RACIAL_TITLES ({ "Drow of Underdark", \
                                  "Gnomish Inventors", \
                                  "Traveller guild", \
                                  "Krynn race guild", \
                                  "Thanar race guild", \
                                  "Dunedain", \
                                  "Eil-Galaith", \
                                  "Halflings of Faerun" })

#define ELIGIBLE_CRAFT_TITLES  ({ "Gardeners of Gont", \
                                  "Mariners of Genesis" })

#define ELIGIBLE_LAYMAN_TITLES ({ "Pirate of the Bloodsea", \
                                  "Angmar Army", \
                                  "Necromancers Of Vile Darkness", \
                                  "Shieldbearers of Iron Delving", \
                                  "Heralds of the Valar", \
                                  "Thornlin Militia", \
                                  "Gardeners of Gont", \
                                  "Elemental Worshippers of Calia", \
                                  "Templars of Takhisis", \
                                  "Ansalon Elvish Archers", \
                                  "The August Order of Minstrels", \
                                  "Holy Order of the Stars", \
                                  "Warlocks of Faerun", \
                                  "Raiders of Throtyl", \
                                  "Blademasters of Khalakhor" })