#ifndef VAMPIRE_DEFS
#define VAMPIRE_DEFS

#include "/d/Emerald/sys/macros.h"
#include "/d/Emerald/sys/paths.h"
#include "defs.h"
#include "lockout.h"
#include "/d/Emerald/sys/properties.h"
#include <std.h>

#define GUILD_NAME          "Vampires of Emerald"
#define GUILD_STYLE         "fighter"
#define GUILD_TAX           40

#undef VAMP_DIR
#define VAMP_DIR "/d/Emerald/vamp/"

#define VAMP_ROOM_DIR   VAMP_DIR + "room/"
#define VAMP_NPC_DIR    VAMP_DIR + "npc/"
#define VAMP_LOG_DIR    VAMP_DIR + "log/"
#define VAMP_OBJ_DIR    VAMP_DIR + "obj/"
#define VAMP_HELP_DIR   VAMP_DIR + "help/"
#define VAMP_SHADOW_DIR VAMP_DIR + "shadow/"
#define VAMP_SOUL_DIR   VAMP_DIR + "soul/"
#define VAMP_LIB_DIR    VAMP_DIR + "lib/"
#define VAMP_BOOK_DIR   VAMP_LOG_DIR + "books/"
#define VAMP_SPELL_DIR  VAMP_DIR + "spells/"

#define MEMBER_SAVE_DIR     (VAMP_LOG_DIR + "member_save/")
#define OLD_MEMBER_SAVE_DIR (MEMBER_SAVE_DIR + "old/")
#define MEMBER_FILE(who)     MEMBER_SAVE_DIR + who
#define OLD_MEMBER_FILE(who) OLD_MEMBER_SAVE_DIR + who
#define WEAPON_SAVE (VAMP_LOG_DIR + "weapon")



#define SUN                      (VAMP_DIR  + "sun")
#define THIRST_NOTIFIER          (VAMP_DIR  + "thirst_notifier")
#define COFFIN_MANAGER           (VAMP_LOG_DIR + "coffin_manager")
#define ADVERB_MANAGER           (VAMP_LOG_DIR + "adverbs")
#define LAIR_MANAGER             (VAMP_LOG_DIR + "lair_manager")
#define VAMP_STARTLOC            (VAMP_ROOM_DIR + "start")
#define VAMP_CMDSOUL             (VAMP_SOUL_DIR + "vamp_soul")
#define VAMP_COVENMASTER_CMDSOUL (VAMP_SOUL_DIR + "cm_soul")
#define VAMP_ABILITIES           (VAMP_SOUL_DIR + "abilities")
#undef VAMP_ABILITIES
#define VAMP_SPELLS              (VAMP_SPELL_DIR + "vamp_spells")
#define VAMP_CLOAK_CMDSOUL       (VAMP_SOUL_DIR + "cloak_soul")
#define VAMP_SHADOW              (VAMP_SHADOW_DIR + "vamp_sh")
#define MELD_CONT                (VAMP_ROOM_DIR    + "meld_cont")

#define GUILD_EMBLEM   VAMP_OBJ_DIR + "cloak"
#define GUILD_EMBLEM_AUTOLOADING

#define EMBRACE_SHADOW VAMP_SHADOW_DIR + "embrace_sh"
#define YES_NO_OBJECT  "/d/Emerald/std/yes_no"

#define IS_MEMBER(x)   (x->is_emerald_vampire())

#define SECURITY_LOG(x, y) \
    setuid(); seteuid(getuid()); \
    write_file(VAMP_LOG_DIR + "security", \
    sprintf("%-12s (%s):\n%s\n\n", capitalize(x->query_real_name()), \
    ctime(time()), y))    
    
#define SECURITY_CHECK(x) \
    ((file_size(MEMBER_FILE(x->query_real_name()) + ".o") > -1) || \
    EMRLD_WIZ(x) || \
    (SECURITY->query_wiz_rank(x->query_real_name()) >= WIZ_ARCH))

#define VAMPS(x)       (filter(x, &->is_emerald_vampire()))

#define EFF_OCCSTAT(x) x->query_effective_vamp_stat()

#define GUILD_EMBLEM_ID "_vamp_guild_cloak"

#define CLOAK_SUB                    "vamp_cloak_subloc"
#define VAMP_I_MOVING_TO_COFFIN      "_vamp_i_moving_to_coffin"
#define VAMP_O_CLING                 "_vamp_o_cling"
#define LIVE_I_ENTERED_VAMP_STARTLOC "_live_i_entered_vamp_startloc"
#define LIVE_O_VAMP_DRAINER          "_live_o_vamp_drainer"

#define SUNLIGHT_DAMAGE(light_lev) MAX(0, (10 * light_lev))
#define SUNLIGHT_DAMAGE_INTERVAL   2.0

#define MANAGER                (VAMP_LOG_DIR + "manager")
#define QUERY_PUNISH(who, pun) MANAGER->query_punished(who, pun)

#define DRAIN_STATUS_START_DRAIN 1
#define DRAIN_STATUS_DRAINING    2

#define EXPEL  1
#define BANISH 2

#define ROGUE_VAMPIRE "rogue"


#define UNSEEN_SUBLOC  "_vunseen_subloc"
#define VAURA_SUBLOC   "_vaura_subloc"

#endif
