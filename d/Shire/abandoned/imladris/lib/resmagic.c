/*
 * /lib/resmagic.c
 *
 * This file is a suggestion on how resistance against magic could
 * be coded after the intensions written in the file
 *     /d/Shire/rogon/open/mudlib.ideas
 *
 */

/*
 * Function:	add_resistance_object
 * Arguments:	object res_obj		- The object which increases resistance.
 * Description:
 *	The resistance objects are put into a variable so that a fast
 *	search throught these objects can determine a livings resistance.
 */

void
add_resistance_object(object res_obj)
{
    if(!sizeof(gResistance_objects))
	gResistance_objects = ({ res_obj });
    else
	gResistance_objects += ({ res_obj });
}

int
remove_resistance_object(object res_obj)
{
    int pos;

    pos = member_array(res_obj, gResistance_objects);
    if(pos==-1)
	return 0;
    gResistance_objects = exclude_array(gResistance_objects, pos, pos);
    return 1;
}


query_pure_resistance(string prop)
{
    int no_objs, max, max_add, max_stat, i, *value;
    object *list;

    list = gResistance_objects;
    no_objs = sizeof(list);

    max_add = 100;

    for(i = 0; i < no_objs ; i++)
    {
	value = list[i]->query_prop(PRE_OBJ_MAGIC_RES + prop);
	if(pointerp(value))
	{
	    if(sizeof(value)>0 && !value[1])
		max_stat = MAX(max_stat, value[0]);
	    else
		max_add  = max_add * (100 - value[0]) / 100;
	}
    }

    if(max_add>0)
	max_add = 100 - max_add;

    max = MAX(max_stat, max_add);

    max += (int)this_object()->query_prop(PRE_OBJ_MAGIC_RES + prop)

    return MAX(100, max);
}

/*
 * Function:	query_magic_resistance
 * Arguments:	string element - The element of the attack.
 *		string dt      - The damage type of the attack.
 * Description:
 *  Calculates the magic resistance of a living according to these rules:
 *
 *  1. The resistance against MAGIC counts for all magical attacks.
 *     If element == 0 (ELEMENT_ARMS) then this will rule will not apply.
 *
 *  2. Element can be one of:
 *	  ELEMENT_FIRE	    - Uses RES_I_FIRE
 *	  ELEMENT_WATER     - Uses RES_I_WATER
 *	  ELEMENT_AIR	    - Uses RES_I_AIR
 *	  ELEMENT_EARTH     - Uses RES_I_EARTH
 *	  ELEMENT_LIFE	    - Uses RES_I_LIFE
 *	  ELEMENT_DEATH     - Uses RES_I_DEATH
 *	  ELEMENT_ARMS	    - Used when no magic element can be applied.
 *
 *  3. Damage type can be one of:
 *	  DT_IMPACT
 *	  DT_HEAT
 *	  DT_COLD
 *	  DT_ACID
 *	  DT_ELECTRICITY
 *	  DT_VIBRATION
 *	  DT_RADIATION
 *	  DT_VACUUM
 *
 *	  DT_SPECIAL
 *
 *  Weights:
 *	1: 40%
 *	2: 40%
 *	3: 20%
 */
int
query_magic_resistance(string element, int dt)
{
    int sum = 0, dividend = 0;

    if(element != ELEMENT_ARMS)
    {
	sum += query_pure_resistance(MAGIC_I_RES_MAGIC)*40;
	sum += query_pure_resistance("_magic_i_res_"+element)*40;
	dividend += 80;
    }

    if(element != DT_SPECIAL)
    {
	sum += query_pure_resistance("_magic_i_res_"+DT_PROP[dt])*20;
	dividend += 20;
    }

    if(dividend == 0)
	return 0;

    return sum/dividend;
}
