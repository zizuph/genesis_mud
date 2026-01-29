/* File         : /d/Khalakhor/std/armour.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : October 12, 1998         
 * Purpose      : Khalakhor standard armour, to be inherited by all weapons      
 * Related Files: /std/armour.c
 * Comments     :
 * Modifications: Teth, Feb 27, 1999
 *                - masked appraise_object(), added functionality for
 *                  Khalakhor lore skill
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

string lore_skill_desc();
string query_lore_skill_desc();

/*
 * Function name: create_khalakhor_armour
 * Description  : Constructor function for armours.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_armour()
{
}

/*
 * Function name: create_armour (MASK)
 * Description  : Constructor function.
 * Arguments    : n/a
 * Returns      : n/a
 */
nomask void
create_armour()
{
    create_khalakhor_armour();
}

/*
 * Function name: appraise_object (MASK)
 * Description  : Someone attempts to appraise the object. We also
 *                add information about the armour and extra desc
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
 * Description  : This function is masked in the armour to produce the 
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
