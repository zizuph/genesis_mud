/* (c) Damian Horton, BKA Casimir, 2000.
   update for Raumdor, Feb. 2001.

#pragma strict_types
#pragma save_binary

/*
   Function name: pct_hurt
   Description  : Determines percentage of remaining hit points a given
                  amount of damage will deal to a living.
   Arguments    : int damage    - the number of hit points lost by the living
                  object living - the living who lost the hp
   Returns      : int           - Percentage of hit points lost, 100 if the
                                  victim took lethal damage.
*/ 
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
    
    return ftoi((itof(damage) / hp) * 100.0);
}

