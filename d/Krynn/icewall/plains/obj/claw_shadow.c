/*
 * Igneous' claw shadow
 *
 *  Used to alter a players attack description to that of the claw
 *  he/she has just worn.
 *
 *  Copyright (C) Chad Richardson   September 1997
 *
 * Modifaction log:
 *
 */
#pragma strict_types

inherit "/std/shadow";

#include <wa_types.h>

#define ERROR(s)  log_file("claw_error", ctime(time()) + " " + s + "\n")

// Global Variables
object gRight_claw, gLeft_claw;

/*
 * Function    : query_is_claw_shadowed
 * Description : Used to see if someone is shadowed with this shadow
 * Returns     : 1
 */
nomask public int
query_is_claw_shadowed()
{
    return 1;
}

/*
 * Function    : query_remove_claw_shadow
 * Description : Used to see if we should remove this shadow
 */
nomask public void
query_remove_claw_shadow()
{
    if (!objectp(gLeft_claw) && !objectp(gRight_claw))
	remove_shadow();
}

/*
 * Function    : add_claw
 * Description : Adds a claw to this shadow so it has a pointer 
 *               to the claw object.
 * Arguments   : claw: The claw object
 */
nomask public void
add_claw(object claw)
{
    if (claw->query_hand() == 1)
    {
	if (!objectp(gRight_claw))
	    gRight_claw = claw;
	else
	    ERROR("Shadow tried to add a claw that was already present.");
    }
    else 
    {
	if (!objectp(gLeft_claw))
	    gLeft_claw = claw;
	else
	    ERROR("Shadow tried to add a claw that was already present.");
    }
}

/*
 * Function    : remove_claw
 * Description : removes the pointer to the claw object
 * Arguments   : claw : the claw object
 */
public nomask void
remove_claw(object claw)
{
    if (claw->query_hand() == 1)
    {
	if (objectp(gRight_claw))
	    gRight_claw = 0;
	else
	    ERROR("Shadow tried to remove a non-existant claw.");
    }
    else
    {
	if (objectp(gLeft_claw))
	    gLeft_claw = 0;
	else
	    ERROR("Shadow tried to remove a non-existant claw.");
    }
}

/*
 * Function    : cr_attack_desc (MASKED)
 * Description : Used to atler a players attack description to that 
 *               of the claw he/she is wearing.
 * Arguments   : aid: the attack id.
 * Returns     : string: the description of the attack.
 */
public string
cr_attack_desc(int aid)
{
    if (aid == W_RIGHT && objectp(gRight_claw))
	return "right "+gRight_claw->short();
    if (aid == W_LEFT && objectp(gLeft_claw))
	return "left "+gLeft_claw->short();

    return shadow_who->cr_attack_desc(aid);
}
