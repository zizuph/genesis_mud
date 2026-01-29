#ifndef EMERALD_MACROS_HEADER
#define EMERALD_MACROS_HEADER

#include "/d/Emerald/sys/domain.h"
#include <std.h>

#define LOAD_CLONE_HANDLER(x) \
    if (interactive(this_player())) catch(call_other(x, "??"));
  
/* This is the most secure method of determining if someone is a
 * wizard, but it also the least efficient.  For general purposes,
 * use ob->query_wiz_level().  If you are very concerned about
 * security, though, use this macro.
 */
#define IS_WIZ(x) (interactive(x) && \
    SECURITY->query_wiz_rank(x->query_real_name()))

#define EMRLD_WIZ(x) DOMAIN_WIZ(x) 

/* Add this name to all creatures of Val-Shoreil which you create */
#define CREATURE_OF_VS_ID  "_creature_of_val-shoreil"

/* Use this macro to determine if a creature is a creature of VS.
 *
 * N.B.  For interaction with npcs, KNOWN_CREATURE_OF_VS is probably more
 * appropriate unless the npc has extensive knowledge of such creatures or
 * has magically detected the creature's origins.
 */
#define CREATURE_OF_VS(ob) \
    (ob->query_vampire() || \
     KNOWN_CREATURE_OF_VS(ob) || \
     ob->id(CREATURE_OF_VS_ID))

/* Use this macro to determine whether a creature is a known creature of
 * VS.  Known creatures of VS are those that are likely to be recognized
 * by most light dwellers.
 */
#define KNOWN_CREATURE_OF_VS(ob) \
    (member_array(ob->query_race_name(), \
    ({ "ogre", "orc", "uruk", "uruk-hai", "troll", "olog", "olog-hai", \
       "goblin", "darkling", })) >= 0)

/* Add this name to all creatures of Val-Shoreil which you create */
#define CREATURE_OF_TR_ID  "_creature_of_telan-ri"

/* Use this macro to determine if a creature is a creature of TR.
 *
 * N.B.  For interaction with npcs, KNOWN_CREATURE_OF_TR is probably more
 * appropriate unless the npc has extensive knowledge of such creatures or
 * has magically detected the creature's origins.
 */
#define CREATURE_OF_TR(ob) \
     (KNOWN_CREATURE_OF_TR(ob) || ob->id(CREATURE_OF_TR_ID))

/* Use this macro to determine whether a creature is a known creature of
 * TR.  Known creatures of VS are those that are likely to be recognized
 * by most dark dwellers.
 */
#define KNOWN_CREATURE_OF_TR(ob) \
    (member_array(ob->query_race_name(), \
    ({ "elf", "unicorn", "pegasus" })) >= 0)

/*
 * LOG_QUEST
 *
 * Developed by Mercade for the Gondor domain in 1994
 *
 * This define should be used to log something in the quest-log. The
 * quest log should never be written to directly. The following
 * parameters should always be added:
 *
 * p - objectpointer to the player solving the quest
 * x - experience gained
 * n - name of the quest (max 25 characters)
 */
#define QUESTLOG_FILE ("/d/Emerald/sys/questlog")
#define LOG_QUEST(p, x, n)  QUESTLOG_FILE->log_quest(p, x, n);


/* A lot of useless macros.  I keep them for legacy code.  I'd prefer
 * that they not be used in new code.  Note: that doesn't mean make
 * up your own.
 */
#define TP              this_player()
#define TO              this_object()
 
#define NF(x)           notify_fail(x)
 
#define QP(x, y)        (x->query_prop(y))
#define AP(x, y, z)     (x->add_prop(y, z))
#define CP(x, y, z)     (x->change_prop(y, x->query_prop(y) + z))
#define RP(x, y)        (x->remove_prop(y))
 
#define HE_SHE(x)       x->query_pronoun()
#define PRON(x)         HE_SHE(x)
#define HIM_HER(x)      x->query_objective()
#define OBJ(x)          x->query_objective()
#define HIS_HER(x)      x->query_possessive()
#define POS(x)          HIS_HER(x)
 
#define ENV(x)          environment(x)
#define E(x)            environment(x)

#define FIXEUID         { setuid(); seteuid(getuid()); }

#endif
