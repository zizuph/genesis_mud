/* File         : /d/Khalakhor/std/weapon.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : October 12, 1998         
 * Purpose      : Khalakhor standard weapon, to be inherited by all weapons      
 * Related Files: /std/weapon.c
 * Comments     :
 * Modifications: Teth, Feb 27, 1999
 *                - masked appraise_object(), added functionality for
 *                  Khalakhor lore skill
 *              : Teth - Feb 09 2002
 *                Added default likely_break and likely_dull functions
 *              : Teth - Feb 15 2002
 *                Added functionality to alter the likely_break and likely_dull
 *                of the weapon based on the differential of the wielder's STR
 *                and INT.
 *              : Cotillion - Jun 05 2005
 *                Removed silly likely break stuff. Not our job to enforce
 *                stat balance.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <stdproperties.h>

/*
 * Initialize some functions
 */
string lore_skill_desc();
string query_lore_skill_desc();

/*
 * Function name: create_khalakhor_weapon
 * Description  : Constructor function for weapons. This should
 *                be used in all Khalakhor weapons, as the 
 *                create_weapon() function is set as nomask and
 *                can't be altered.
 */
public void
create_khalakhor_weapon()
{
}

/*
 * Function name: create_weapon (MASK)
 * Description  : Constructor function.
 * Arguments    : n/a
 * Returns      : n/a
 */
public nomask void
create_weapon()
{
    create_khalakhor_weapon();
}

/*
 * Function name: appraise_object (MASK)
 * Description  : Someone attempts to appraise the object. We also
 *                add information about the weapon and extra desc
 *                based on the Khalakhor lore skill.
 * Argument     : int num - A random seed number for appraisal variables.
 * Returns      : The description of the object when appraised.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);

    write(query_lore_skill_desc());
}

/*
 * Function name: lore_skill_desc
 * Description  : This function is masked in the object to produce the 
 *                variable description in via appraisal.
 * Arguments    : n/a
 * Returns      : A string to write. 
 */
public string
lore_skill_desc()
{
    return "";
}

/*
 * Function name: query_lore_skill_desc
 * Description  : The descriptor function for lore skill via appraisal.
 * Arguments    : n/a
 * Returns      : The string to write when the item is appraised.
 */
public string
query_lore_skill_desc()
{
    if (!(strlen(this_object()->lore_skill_desc())))
    {
        return "";
    }

    return ("\n" + lore_skill_desc() + "\n");
}

/*
 * Function name: query_khalakhor_weapon
 * Description  : Check to see if this is a Khalakhor weapon.
 * Returns      : 1 - if a weapon
 */
public int
query_khalakhor_weapon()
{
    return 1;
}



