static int special_attack_pcnt;
static mixed *specials = ({ });

/* This is called from the combat object on each combat round to
 * see if this npc will do a special attack this round.  We do
 * some tests to see if we wish to attempt a special this round,
 * and if so, the appropriate function (as given by the first
 * argument to add_special_attack) is called.  That function
 * should return 0 if regular attacks should or 1 if they should
 * not (successful special attack).
 */
public int 
special_attack(object enemy)
{
    int i, j, ran;
    function attack_func;
  
    if (!sizeof(specials) || random(100) >= special_attack_pcnt)
    {
        return 0;
    }
  
    // decide which special to use
    ran = random(100);
    for (i = sizeof(specials); i--;)
    {
    	if ((j += specials[i][1]) >= ran)
    	{
	    break;
    	}
    }
  
    // call the appropriate function for the chosen attack
    i = max(0, min(sizeof(specials), i));
    attack_func = specials[i][0];
    return attack_func(enemy);
}

/* Function name: add_special_attack
 * Description:   add a special attack to those that will be performed by
 *                this npc 
 * Arguments:     function attack_func - the function to be called to execute
 *                                       the special attack.  This function
 *                                       should return 1 if regular attacks
 *                                       should be suspended this round, 0
 *                                       if they should not.
 *                int pcnt - the percentage that this attack should be used.
 *                           The sum of the percent usages of all the special
 *                           attacks should be 0
 *                mixed id - a unique id for this special attack for use
 *                           with remove_special_attack
 */
public void
add_special_attack(function attack_func, int pcnt, mixed id)
{
    specials += ({ ({ attack_func, pcnt, id }) });
}

/* Function name: remove_special_attack
 * Description:   remove a special attack from those that will be performed
 *                by this npc
 * Arguments:     mixed id - the attack's id.  It would seemingly make more
 *                           sense to use the function as an id, but it seems
 *                           that function-type variables can't be compared
 *                           reliably.
 * Returns:       1 - attack removed; 0 - attack not removed
 */
public int
remove_special_attack(mixed id)
{
    return (sizeof(specials) != sizeof(specials =
       filter(specials, &operator(!=)(id) @ &operator([])(,2))));
}

/* Function name: remove_all_special_attacks
 * Description:   removes all special attacks performed by this npc
 * Returns:       1
 */
public int
remove_all_special_attacks() 
{ 
    specials = ({ }); 
    return 1;
}

/* Function name: query_special_attacks
 * Description:   get a listing of special attacks performed by this npc
 * Returns:       an array of three-element arrays, where the first element
 *                is a function corresponding to a special attack, the 
 *                second element is an integer which is that attack's
 *                percent usage, and the third element is the attack's id.
 */
public mixed *
query_special_attacks() { return specials; }

/* Function name: set_special_attack_percent
 * Description:   set the percent of attack rounds that this npc should
 *                attempt a special attack.
 * Arguments:     int pcnt - the percentage of rounds
 * Returns:       1
 */
public int
set_special_attack_percent(int pcnt)
{
    special_attack_pcnt = pcnt;
    return 1;
}

/* Function name: query_special_attack_percent
 * Description:   get the percentage of attack rounds that this npc
 *                attempts a special attack.
 * Returns:       the percentage (integer)
 */
public int
query_special_attack_percent() { return special_attack_pcnt; }
