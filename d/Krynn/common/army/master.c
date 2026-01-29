#pragma strict_types;
#pragma save_binary;
#pragma no_clone;

#include "/d/Krynn/common/defs.h"
#include "army.h"
#include <macros.h>
#include <ss_types.h>

#define S_NAME 0
#define S_RACE 1
#define S_PRACE 2
#define S_ADJS 3
#define S_LONG 4
#define S_DIS  5
#define S_ITEMS 6
#define S_TYPE 7

private mapping gPlatoons = ([]);
private int gPlatoon_id = 1;

static mapping gSoldiers = ([]);

public nomask void
save_master()
{
    save_object(ARMYSAVE);
}


/*
 * Function name: add_platoon
 * Description:
 * Arguments:     ob - 
 * Returns:       The given id
 */
public nomask string
add_platoon(object ob)
{
    string id = "platoon#" + gPlatoon_id++;

    gPlatoons += ([ id : ({MASTER_OB(ob), 0, 0}) ]);
    return id;
}

/*
 * Function name: remove_platoon
 * Description:
 * Arguments:     id - 
 */
public nomask void
remove_platoon(string id)
{
    if (!gPlatoons[id])
        return;

    gPlatoons = m_delete(gPlatoons, id);

    save_master();
}

/*
 * Function name: register_soldier
 * Description:
 * Arguments:     soldier - Filename of the soldier
 * Returns:       True if register ok, otherwise false
 */
public nomask int
register_soldier(string soldier, string pname)
{
    object ob;
    mixed data = ({});
    string *items = ({}), *adjs, name, race, type = "";
    int size, i;

    if (member_array(soldier, m_indexes(gSoldiers)) >= 0)
        return 1;

    if (!(ob = clone_object(soldier)))
        return 0;

    name = lower_case(ob->query_name());
    race = QRACE(ob);
    adjs = ob->query_adjs();

    if (!pname)
        pname = LANG_PWORD(race);

    data += ({ name, race, pname, adjs });
    data += ({ ob->query_long() });
    data += ({ ob->query_stat(SS_DIS) });

    size = sizeof(adjs);
    for (i = 0; i < size; i++)
    {
        type += adjs[i] + " ";
	items += ({ adjs[i] + " " + race });
    }

    items += ({ type + race, race, name });

    data += ({ items, type });

    gSoldiers += ([ soldier : data ]);
}

/*
 * Function name: query_soldier_long 
 * Description:
 * Arguments: 
 * Returns:
 */
public nomask string
query_soldier_long(string soldier)
{
    if (member_array(soldier, m_indexes(gSoldiers)) >= 0)
        return gSoldiers[soldier][S_LONG];
    return 0;
}

/*
 * Function name: query_soldier_type 
 * Description:
 * Arguments: 
 * Returns:
 */
public nomask string
query_soldier_type(string soldier)
{
    if (member_array(soldier, m_indexes(gSoldiers)) >= 0)
        return gSoldiers[soldier][S_TYPE];
    return 0;
}

/*
 * Function name: query_soldier_race 
 * Description:
 * Arguments: 
 * Returns:
 */
public nomask string
query_soldier_race(string soldier)
{
    if (member_array(soldier, m_indexes(gSoldiers)) >= 0)
        return gSoldiers[soldier][S_RACE];
    return 0;
}

/*
 * Function name: query_soldier_prace 
 * Description:
 * Arguments: 
 * Returns:
 */
public nomask string
query_soldier_prace(string soldier)
{
    if (member_array(soldier, m_indexes(gSoldiers)) >= 0)
        return gSoldiers[soldier][S_PRACE];
    return 0;
}

/*
 * Function name: query_soldier_items
 * Description:
 * Arguments: 
 * Returns:
 */
public nomask string
query_soldier_items(string soldier)
{
    if (member_array(soldier, m_indexes(gSoldiers)) >= 0)
        return gSoldiers[soldier][S_ITEMS];
    return 0;
}

/*
 * Function name: get_officers
 * Description:
 * Arguments: 
 * Returns:       An array, containing two arrays, the first one
 *                holds the officers, and the second one holds the
 *                remaining soldiers.
 */
public nomask mixed
get_officers(mapping platoon, int number)
{
    string *idx = m_indexes(platoon), officer, *officers = ({});
    int i, j, dis, nr;
    mixed data;

    for (j = 0; j < number; j++)
    {
        dis = 0;
	officer = 0;

	for (i = 0; i < sizeof(idx); i++)
	{
	    data = gSoldiers[idx[i]];
	    if (data[S_DIS] > dis && !platoon[idx[i]][P_NO_RANK])
	    {
	        dis = data[S_DIS];
	        officer = idx[i];
	    }
	}

	if (officer)
	{
	    nr = number - j;
	    if (platoon[officer][P_NUMBER] >= nr)
	    {
	        platoon[officer][P_NUMBER] -= nr;
		j += nr - 1;
	    }
	    else
	    {
	        nr = platoon[officer][P_NUMBER];
		platoon[officer][P_NUMBER] = 0;
		j += nr - 1;
	    }

	    for (i = 0; i < nr; i++)
	        officers += ({ officer });

	    if (platoon[officer][P_NUMBER] == 0)
	    {
	        platoon = m_delete(platoon, officer);
		idx = m_indexes(platoon);
	    }
	}
    }

    return ({ officers, platoon });
}

/*
 * Function name: set_platoon_room
 * Description:
 * Arguments:     id - 
 *                room - 
 */
public nomask void
set_platoon_room(string id, object room)
{
    if (!gPlatoons[id])
        return;

    gPlatoons[id][LOCATION] = MASTER_OB(room);

    save_master();
}

/*
 * Function name: set_platoon_vars
 * Description:
 * Arguments:     id - 
 *                room - 
 */
public nomask void
set_platoon_vars(string id, mixed vars)
{
    if (!gPlatoons[id])
        return;

    gPlatoons[id][VARS] = vars;

    save_master();
}

/*
 * Function name: create_army
 * Description:
 */
nomask static void
create_army()
{
    string *index;
    int i;
    object ob;

    index = m_indexes(gPlatoons);
    i = sizeof(index);

    while (i--)
    {
        call_other(gPlatoons[index[i]][LOCATION], "??");
	ob = clone_object(gPlatoons[index[i]][FILEPATH]);
	ob->move(gPlatoons[index[i]][LOCATION]);
	remove_platoon(gPlatoons[index[i]]);
    }
}

/*
 * Function name: create
 * Description:
 */
nomask void
create()
{
    seteuid(getuid());

    restore_object(ARMYSAVE);

    create_army();

    /* Call reset every 15 min */
    set_alarm(900.0, 900.0, "reset");
}

/*
 * Function name: reset
 * Description:   This function is called every 15 minute.
 */
nomask void
reset()
{
    save_master();
}

/*
 * Function name: remove_object
 * Description:
 */
nomask public void
remove_object()
{
    save_master();
    destruct();
}

/*
 * Function name: 
 * Description:
 * Arguments: 
 * Returns:
 */








