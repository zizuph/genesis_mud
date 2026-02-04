/* Modified by: 
 *  Lilith, 23 Oct 2008
 *   -attack aid to 80 from 70
 *  Lilith, 16 Nov 2008
 *   -attack aid moved from drain (removed haste) to bite: 80 to 101
 */
#include "defs.h"

#define OCC_GUILD_NAME          "Vampyr of Terel"
#define OCC_GUILD_STYLE         "ranger"
// Changed February 2009. Removed constrict, so remove 1% of tax.
#define OCC_GUILD_TAX           33
#define OCC_GUILD_TAX_2         9
// Changed February 2009. Added back the tax breaks that
// vampires were receiving:
// 1. Sunlight - emotive effect since Vampires with 1 darkness item
//               suffers no effect.
// 2. Blood use
// 3. Being undead
#define OCC_GUILD_TAX_3         13


#define LAY_GUILD_NAME          "Bloodguards of Terel"
#define LAY_GUILD_STYLE         "fighter"
#define LAY_GUILD_TAX           13

#define VAMP_SKILL_BITE         130010
#define VAMP_SKILL_FLURRY       130011
#define VAMP_BLOOD              130012
#define VAMP_FAVOR              130013

#define ROOM_I_SUNLIGHT  "_room_i_sunlight"

#define ROOM_I_NO_THIRST "_room_i_no_thirst"

#define VAMP_O_CLING      "_vamp_o_cling"

/* Aid changed to 80% to be in line with Balance design
 * February 2009 */
#define ATTACK_COMBAT_AID         80

#define VAMPS(x)       ((filter(filter(x, &interactive()), \
                            &->query_vampire())) - \
                       (filter(x, &->is_emerald_vampire())))

#define IS_VAMP(x)   (x)->query_vampire()

#define IS_BG(x)     (x)->query_bloodguard()

#define LIVE_O_VAMP_DRAINER "_live_o_vamp_drainer"
#define LIVE_O_OFFERED_BLOOD "_live_o_offered_blood"

#define YES_NO_OBJECT  (OBJ_DIR+"yes_no")

#define VAMP_FREE_SEE_DARKNESS  "_vamp_free_see_darkness"
#define VAMP_CAN_START_HERE     "_vamp_can_start_here"

#define WATCHERS(obj)   (filter(filter(all_inventory(environment((obj))), \
                            &->can_see_in_room()), &(obj)->check_seen()) \
                            - ({ (obj) }))

#define BG_JOIN_LOG (LOG_DIR+"bg_join_log")

#define VAMP_JOIN_LOG (LOG_DIR+"vamp_join_log")

#define CP(x, y, z)     (x->change_prop(y, x->query_prop(y) + z))

#define SECURITY_LOG(x, y) \
    setuid(); seteuid(getuid()); \
    write_file(LOG_DIR + "security", \
    sprintf("%-12s (%s):\n%s\n\n", capitalize(x->query_real_name()), \
    ctime(time()), y))    
    
#define SECURITY_CHECK(x) \
    (query_manager()->load_data(x->query_real_name()) || \
    (SECURITY->query_wiz_rank(x->query_real_name()) >= WIZ_ARCH))

#define ALLOWED_SKILLS  ([ \
        "martial" : \
        ({ SS_2H_COMBAT, SS_UNARM_COMBAT, SS_BLIND_COMBAT, \
            SS_PARRY, SS_DEFENCE, SS_WEP_SWORD, SS_WEP_CLUB, \
            SS_WEP_AXE, SS_WEP_POLEARM, SS_WEP_KNIFE, \
            }) , \
        "mental" : \
        ({ SS_HERBALISM, SS_SPELLCRAFT, SS_ALCHEMY, \
            SS_FORM_TRANSMUTATION, SS_FORM_ILLUSION, \
            SS_FORM_DIVINATION, SS_FORM_ENCHANTMENT, \
            SS_FORM_CONJURATION, SS_FORM_ABJURATION, \
            SS_ELEMENT_FIRE, SS_ELEMENT_AIR, SS_ELEMENT_EARTH, \
            SS_ELEMENT_WATER, SS_ELEMENT_LIFE, SS_ELEMENT_DEATH }) , \
        "rogue" : \
        ({ SS_OPEN_LOCK, SS_PICK_POCKET, SS_ACROBAT, SS_FR_TRAP, \
            SS_SNEAK, SS_HIDE, SS_BACKSTAB }), \
        "general" : \
        ({ SS_LANGUAGE, SS_APPR_MON, SS_APPR_OBJ, \
            SS_APPR_VAL, SS_SWIM, SS_CLIMB, SS_ANI_HANDL, \
            SS_LOC_SENSE, SS_TRACKING, SS_HUNTING, SS_AWARENESS, \
            SS_TRADING, SS_RIDING}) ])


//The vampire must have at least 20 game days to vote.
#define MINIMUM_VOTE_AGE 86400*20
