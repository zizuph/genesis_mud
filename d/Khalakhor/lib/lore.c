/* File         : /d/Khalakhor/lib/lore.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : October 26th 1998
 * Purpose      : An inheritable file to be used for the Khalakhor lore
 * Related Files: ~Khalakhor/coding/skills/khalakhor_lore
 *                ~Khalakhor/coding/examples/lore_obj.c
 * Comments     :
 * Modifications:
 */
#include "/d/Khalakhor/sys/skills.h"

// Global Vars
static int *gLore_bits, gLore_skill;

/* Function name:  set_lore_bits
 * Description:    Sets the skill bits that are to be used
 * Arguments:      mixed bits: a bit or an array of bits to be used.
 */
public void
set_lore_bits(mixed bits)
{
    if (pointerp(bits))
	gLore_bits = bits;
    else
	gLore_bits = ({bits});
}

/* Function name: query_lore_bits
 * Description:   A simple query for the lore bits used here
 * Returns:       an integer array of bits used 
 */
public int *
query_lore_bits()
{
    return gLore_bits;
}

/* Function name: set_lore_skill
 * Description:   sets the skill we use to keep track of the bits
 * Arguments:     int skill:   The skill used.
 */
public void
set_lore_skill(int skill)
{
    gLore_skill = skill;
}

/* Function name: query_lore_skill
 * Description:   A simply query for the skill the bits use
 * Returns:       integer skill number used.
 */
public int
query_lore_skill()
{
    return gLore_skill;
}

/* Function name:  test_lore
 * Description:    Does all the upkeep and tests to see if a player
 *                 recieves any lore skill for doing a task.
 * Arguments:      object ob:  The player we are checking.
 */
public void
test_lore(object ob)
{
    int i, num = ob->query_skill(gLore_skill);

    //  Only add the skill to interactive players
    if (!interactive(ob))
	return;
    //  Hmmm this isn't set up correctly.
    if (!sizeof(gLore_bits) || !gLore_skill)
	return;
    i = -1;
    while(++i < sizeof(gLore_bits))
    {
	//  Seems the player already has this skill bit set in him.
	if (num & gLore_bits[i])
	    continue;
	// Okay now we add the bit to the bit skill and increment the lore skill
	ob->set_skill(gLore_skill, num | gLore_bits[i]);
	ob->set_skill(SS_KHALAKHOR_LORE,ob->query_skill(SS_KHALAKHOR_LORE)+1);
    }
}
