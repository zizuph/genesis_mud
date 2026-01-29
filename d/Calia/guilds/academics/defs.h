#include "/d/Calia/domain.h"

#define GUILD_NAME               "Academy of Elemental Arts"
#define GUILD_SHORT_NAME         "academic"
#define GUILD_TYPE               "layman"
#define GUILD_STYLE              "magic"
#define GUILD_TAX                10

#define ACADEMIC_DIR             "/d/Calia/guilds/academics/"

#define ACADEMIC_DATA            ACADEMIC_DIR + "data/"
#define ACADEMIC_HELP            ACADEMIC_DIR + "help/"
#define ACADEMIC_OBJS            ACADEMIC_DIR + "objs/"
#define ACADEMIC_NPCS            ACADEMIC_DIR + "npcs/"
#define ACADEMIC_LOGS            ACADEMIC_DIR + "logs/"
#define ACADEMIC_LIBS            ACADEMIC_DIR + "lib/"
#define ACADEMIC_SHADOWS         ACADEMIC_DIR + "shadows/"
#define ACADEMIC_SPELLS          ACADEMIC_DIR + "spells/"
#define ACADEMIC_SPELL_OBJS      ACADEMIC_SPELLS + "objs/"
#define ACADEMIC_SOULS           ACADEMIC_DIR + "souls/"
#define ACADEMIC_BOARD_NOTES     ACADEMIC_DIR + "board_notes/"

// Guild Locations
#define ACADEMIC_SCHOOL          ACADEMIC_DIR + "school/"
#define ACADEMIC_STARTROOM       (ACADEMIC_SCHOOL + "joinroom")

// Shadows and Souls
#define ACADEMIC_SOUL        (ACADEMIC_SOULS   + "academy_soul")
#define ACADEMIC_SHADOW      (ACADEMIC_SHADOWS + "academy_shadow")
#define SPELL_MANAGER_SOUL   ("/d/Genesis/specials/guilds/souls/spell_manager_soul")

// Master Objects
#define ACADEMIC_MANAGER     (ACADEMIC_LIBS + "academy_manager")

// Guild NPCS
#define ACADEMIC_GUILDMASTER (ACADEMIC_NPCS + "guildmaster")
#define ACADEMIC_TASKMASTER  (ACADEMIC_NPCS + "taskmaster")
#define ACADEMIC_TEACHER     (ACADEMIC_NPCS + "teacher")

// Useful Macros
#define IS_GUILDMASTER(x)    IN_ARRAY(x->query_real_name(), SECURITY->query_guild_masters(GUILD_SHORT_NAME))
#define IS_CALIA_WIZ(x)      IN_ARRAY(x->query_real_name(), SECURITY->query_domain_members("calia"))
#define IS_MEMBER(x)         ACADEMIC_MANAGER->query_is_member(x)
#define IS_GELAN_NPC(x)      x->query_calia_gelan_npc()
#define IS_CADET(x)          (x->query_guild_name_lay() == "Cadets of Gelan")

// Other Defines
// Can go up to veteran (inclusive)
#define ACADEMIC_MAX_AVG_STAT   98
#define ACADEMIC_I_CONFIRM_JOIN     "_academic_i_confirm_join"
#define ACADEMIC_I_CONFIRM_LEAVE    "_academic_i_confirm_leave"
#define ACADEMIC_CHANNEL_OBJECT     (ACADEMIC_OBJS + "channel_paralyze_object")
#define ACADEMIC_FOCUS_OBJECT       (ACADEMIC_OBJS + "focus_obj")
#define ACADEMIC_FOCUS_PARALYZE     (ACADEMIC_OBJS + "focus_paralyze_object")
#define ACADEMIC_GUILD_OBJECT       (ACADEMIC_OBJS + "scrollcase")
#define TASK_ONE_GIVEN      "_academic_task_one_given"
#define TASK_TWO_GIVEN      "_academic_task_two_given"
#define TASK_THREE_GIVEN    "_academic_task_three_given"
#define TASK_FOUR_GIVEN     "_academic_task_four_given"
#define TASK_TWO_NOTE       (ACADEMIC_OBJS + "task_2_note")