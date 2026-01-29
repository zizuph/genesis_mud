/* Simple routine to determine what proportion of hit points a
   living lost as a result of taking some damage.

   Args: int damage - the number of hit points lost by the living
         object living - the living who lost the hp
	 
   Returns: int - Percentage of hit points lost.
 */

#pragma strict_types
#pragma save_binary
 
int
pct_hurt(int damage, object living)
{
    float hp;
    
    hp = itof(living->query_hp());
    
    if (hp < 1.0)
    {
	//prevents possible division by zero errors,
	//or the return of negative percentages
	return 100;
    }

    return ftoi(itof(damage) / (hp * 100.0));
}

