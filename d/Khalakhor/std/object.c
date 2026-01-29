/* File         : /d/Khalakhor/std/object.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : October 12, 1998         
 * Purpose      : Khalakhor standard object, to be inherited by all objects      
 * Related Files: /std/object.c
 * Comments     :
 * Modifications: Teth, March 19, 1999
 *                - altered to use lore skill appraisal
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

string lore_skill_desc();
string query_lore_skill_desc();

/*
 * Function name: create_khalakhor_object
 * Description  : Constructor function for objects.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_object()
{
}

/*
 * Function name: create_object (MASK)
 * Description  : Constructor function.
 * Arguments    : n/a
 * Returns      : n/a
 */
nomask void
create_object()
{
    create_khalakhor_object();
}

/*
 * Function name: appraise_object (MASK)
 * Description  : Someone attempts to appraise the object. We also
 *                add information about the object and extra desc
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
