#include <macros.h>
#include <options.h>
#include <language.h>

inherit "/std/weapon";

private int filter_see_blood(object person);
private int filter_gag_misses(object person);

mapping slay_map = ([]);
string slay_desc = 0;

nomask void
set_slay_desc(string s)
{
    slay_desc = s;
}

nomask string
query_slay_desc()
{
    return slay_desc;
}

/*
 * Function name: set_slay_map()
 * Description  : Sets a mapping with races that are affected by
 *                the slay magic in this weapon.
 *
 * Arguments    : mapping with race as key, and percent extra dam as value.
 */
nomask void
set_slay_map(mapping m)
{
    slay_map = m;
}

nomask mapping
query_slay_map()
{
    return slay_map;
}

public void 
tell_glow(object wielder, object traget, string message)
{
    object *bystanders = all_inventory(environment(wielder)) - ({ wielder });
    
    if (interactive(wielder))
    {
        tell_object(wielder, "Your " + message);
    }

    bystanders = filter(bystanders, &interactive());
    bystanders = filter(bystanders, &filter_see_blood());

    map(bystanders, &->catch_msg(QCTPNAME(wielder) + " " + message));
}

did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int dam_factor;

    if (phurt > 0 && random(2) && (dam_factor = slay_map[enemy->query_race_name()]))
    {
        dam_factor += 100;
        dam = dam * dam_factor / 100;
        phit  = phit * dam_factor / 100;
        phurt = phurt * dam_factor / 100;

	if (!slay_desc)
	{
            slay_desc = short() + " glows red!\n";
	}

	this_object()->tell_glow(query_wielded(), enemy, slay_desc);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

/*
 * Function name: filter_see_blood
 * Description  : Returns true if the person don't want to see the message.
 *                
 * Arguments    : person: Player to check for OPT_BLOOD.
 * Returns      : int:    True if the person don't want to see blood.
 */
private int 
filter_see_blood(object person)
{
    return !(person->query_option(OPT_BLOOD));
}

/*
 * Function name: filter_gag_misses
 * Description  : Returns true if player wants to see misses..
 *                
 * Arguments    : person: Player to check for OPT_GAG_MISSES.
 * Returns      : int:    True if player wants to see misses.
 */
private int 
filter_gag_misses(object person)
{
    return !(person->query_option(OPT_GAG_MISSES));
}

public string
stat_object()
{
    string msg;
    string *races;
    int i;

    if (m_sizeof(slay_map))
    {
        msg = "One time in three this weapon does:\n";
	races = m_indexes(slay_map);

	for (i = 0; i < sizeof(races); i++)
        {
	    msg += " " + slay_map[races[i]] + "%" + " extra dammage when it hits " + 
	      LANG_ADDART(capitalize(races[i])) + ".\n";
	}
	return ::stat_object() + msg;
    }
    
    return ::stat_object();
}
  
