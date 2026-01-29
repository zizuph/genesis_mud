/*
 *  /d/Sparkle/area/orc_temple/obj/amulet_shadow.c
 *
 *  This is the effect shadow generated when a player wears the
 *  Amulet sold by Karkadelt to allow larger players to enter the
 *  orc dungeons. It reduces all stats and combat skills to 20.
 *
 *  Created December 2010, by Lavellan
 *      Minor revisions by Gorboth (January 2011)
 *      Revised by Mirandus to remove delay in stat loss/gain
 *
 *  The list of guild specials that are lowered by this shadow include:
 *     118200   brawling (rangers)
 *     151011   mercenary tactics (mercenaries)
 *     139051   slashing attack (union)
 *     139052   fling knife (union)
 *     139050   sway (union)
 *     112200   smash (aa)
 *     112201   shield (aa)
 *     112202   shield bash (aa)
 *     143015   gore (minotaurs)
 *      67531   kattack (knights)
 *     143008   slash (DA)
 *     130010   bok special
 *     108600   tattack (templar)
 *     108601   focus (templar)
 *     108602   sap (templar)
 *     147002   strike (monks)
 *     147003   plexus (monks)
 *     143002   axe chop (niedar)
 *     143003   battleraging (niedar)
 *     114021   spirit spells (scop)
 *     132010   crush (ogres)
 *     114007   swarm (calians)
 *     114009   riposte (calians)
 *     114001   move behind (calians)
 */

#pragma strict_types
#include <macros.h>

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "../defs.h"


/* Definitions */
#define     SKILLS      ({ 0, 1, 2, 3, 4, 5, 6, 20, 21, 22, 23, 24, \
                           139052, \
                           139051, \
                           139050, \
                           118200, \
                           151011, \
                           139051, \
                           139052, \
                           139050, \
                           112200, \
                           112201, \
                           112202, \
                           143015, \
                            67531, \
                           143008, \
                           130010, \
                           108600, \
                           108601, \
                           108602, \
                           147002, \
                           147003, \
                           143002, \
                           143003, \
                           114021, \
                           132010, \
                           114007, \
                           114009, \
                           114001, \
                         })

/*
 * Function:    has_sparkle_amulet_shadow
 * Description: If the player is shadowed by this shadow, then this
 *              should return 1.
 */
public int
has_sparkle_amulet_shadow()
{
    return 1;
}

/*
 * Function:    remove_sparkle_amulet_shadow
 * Description: Convenience function to allow removal of this shadow
 *              when there are multiple shadows shadowing a player.
 */
public void
remove_sparkle_amulet_shadow()
{
    remove_shadow();
}

/*
 * Function:    query_reduce_skills
 * Description: Check the amulet on the player to see if it has
 *              reduce stats.
 */
public int
query_reduce_skills()
{
    object amulet = present(AMULET, shadow_who);
    if (!objectp(amulet))
    {
        return 0;
    }
    return amulet->is_descaling_stats();
}

/*
 * Function name:        query_skill
 * Description  :        Here we mask the function to limit certain
 *                       skills to level 20.
 * Arguments    :        int skill - the skill number
 * Returns      :        int - the level
 */
public int
query_skill(int skill)
{
    if (member_array(skill, SKILLS) >= 0 && query_reduce_skills()) 
    {
        return min(30, shadow_who->query_skill(skill));
    }

    return shadow_who->query_skill(skill);
} /* query_skill */
