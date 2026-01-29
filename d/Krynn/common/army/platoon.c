#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include "/d/Krynn/common/defs.h";
#include "army.h";

inherit "/std/object";

#define CLONE_ATTACK(x,y) ob = clone_object(x); \
                          ob->move(E(TO)); \
                          ob->attack_object(y);

static string gId;
static mapping gPlatoon = ([]);
static int gTotal = 0;
static string gPtype, gType;
static string *gNames, *gPnames;
static int gPatch = 0;
static string gCommander;
static string *gOfficer = ({});
static object *gCloned_soldiers;
static int gTime = 10, gCombat = 0;
static mixed gRoute;
static int gPos = 0;          /* Used to keep track on the route array */

/*
 * Function name: query_platoon_size
 * Description:   Find the proper name of the army.
 * Returns:       The right name.
 */
static nomask string
query_platoon_size()
{
    switch(gTotal)
    {
        case 2..15:    return "unit";
        case 16..50:   return "platoon";
        case 51..150:  return "company";
        case 151..300: return "battalion";
        case 301..900: return "brigade";
        default:       return "division";
    }
}

/*
 * Function name: update_names
 * Description:   Update the names for the platoon.
 */
static nomask void
update_names()
{
    int i;
    string size;

    if (gNames && (i = sizeof(gNames)))
        while (i--)
	    remove_name(gNames[i]);

    if (gPnames && (i = sizeof(gPnames)))
        while (i--)
	    remove_pname(gPnames[i]);

    size = query_platoon_size();

    gNames = ({ gPtype, size });
    set_name(gNames);

    size = (size == "company" ? "companies" : size + "s");
    gPnames = ({ gPtype, size });
    set_pname(gPnames);
}

/*
 * Function name: update_items
 * Description:   Updates the items to look on.
 */
static nomask void
update_items()
{
    string *items = ({});
    mixed idx, idx2 = gOfficer + ({});
    int i;

    idx = (m_indexes(gPlatoon) - ({ gCommander })) + ({ gCommander });
    idx = (idx - (idx & idx2)) + (idx & idx2);

    for (i = 0; i < sizeof(idx); i++)
    {
        items += ({ ({ ARMYMASTER->query_soldier_items(idx[i]),
		       ARMYMASTER->query_soldier_long(idx[i]) }) });
    }

    set_add_item(items);  /* Never thought I would use that one :-) */
}

/*
 * Function name: remove_officer
 * Description:   Remove the named or the last officer from the
 *                list.
 * Arguments:     str - A filename for the officer to remove.
 * Returns:       The officer removed.
 */
public varargs string
remove_officer(string str = "")
{
    int i;

    if (!str || !strlen(str))
        str = gOfficer[sizeof(gOfficer) - 1];

    if ((i = member_array(str, gOfficer)) >= 0)
        gOfficer = exclude_array(gOfficer, i, i);
    else
        return 0;

    return str;
}

/*
 * Function name: setup_ranks
 * Description:   Get the officers and the commander from the
 *                soldiers.
 */
public nomask void
setup_ranks()
{
    string *idx;
    mixed *officer;
    int high, tmp, i, j, nr;
    mixed data;

    if (!gOfficer || !sizeof(gOfficer))
    {
        tmp = (gTotal / 5);           /* The number of officers needed */

	if (!gCommander)              /* We need a commander too */
            tmp += 1;

	tmp = (tmp < 2 ? 2 : tmp);    /* We need atleast two officers */

	officer = ARMYMASTER->get_officers(gPlatoon, tmp);
	
	gOfficer = officer[0];
	gPlatoon = officer[1];
    }

    if (!gCommander)
    {
      	gCommander = gOfficer[0];
	gOfficer = exclude_array(gOfficer, 0, 0);
    }
}

public void
create_platoon()
{
}

nomask public void
create_object()
{
    seteuid(getuid());

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GET, 1);

    if (IS_CLONE)
    {
        /* Register our platoon with the Army Master object */
        gId = ARMYMASTER->add_platoon(this_object());
        set_name("_krynn_" + gId);

	set_long("@@platoon_long@@");

	create_platoon();

	if (!gTotal)
	    return;

	update_names();

	setup_ranks();

	if (gRoute)
            set_alarm(itof(gTime), 0.0, "move_platoon");
    }
}

init()
{
    add_action("kill_platoon", "kill");
}

/*
 * Function name: short
 * Description:   Create the short description of the platoon.
 * Arguments:     NONE.
 * Returns:       The short description.
 */
public varargs string
short()
{
    string str = query_platoon_size() + " of " + LANG_WNUM(gTotal) + " ";

    if (gTotal > 1)
        str += gPtype;
    else
        str += gType;
	    
    return str;
}

/*
 * Function name: long
 * Description:   Hmm.. An ugly patch so that we don't get
 *                multiple descriptions of the items.
 * Arguments:     for_obj - Passed from the soul.
 * Returns:       The normal long.
 */
public varargs string
long(string for_obj)
{
    if (gPatch)
      all_inventory(environment(this_object()))->krynn_item_patch(0);

    return ::long(for_obj);
}

/*
 * Function name: platoon_long
 * Description:   Create the long description of the platoon.
 * Returns:       The long description.
 */
public string
platoon_long()
{
    int size, i, number;
    string str;
    string *index = m_indexes(gPlatoon);

    str = "It is a ";

    str += query_platoon_size();
    str += " of";

    size = sizeof(index);

    for (i = 0; i < size; i++)
    {
        number = gPlatoon[index[i]][P_NUMBER];

        if (number < 20)
        {
            str += " " + LANG_WNUM(number) + " " + 
	           ARMYMASTER->query_soldier_type(index[i]) +
	           (number == 1 ? ARMYMASTER->query_soldier_race(index[i]) 
		    : ARMYMASTER->query_soldier_prace(index[i]));
	    
	}
	else
	    str += " countless number of " +
		ARMYMASTER->query_soldier_prace(index[i]);

	if (size > 1)
	    if (i < (size - 2))
	        str += ",";
            else
                if (i == size - 2)
		    str += " and";
    }

    str += ".";

    if (gCommander)
    {
	str += " The commander of the " + query_platoon_size() +
	    " is " + LANG_ADDART(ARMYMASTER->query_soldier_type(gCommander)) +
	       ARMYMASTER->query_soldier_race(gCommander) + ".";

	if ((size = sizeof(gOfficer)))
	{
	    str += " You also spot " + LANG_WNUM(size) + " other " +
	      "officer";
	    if (size > 1)
	        str += "s.";
	    else
	        str += ".";
	}
    }

    return str + "\n";
}

/*
 * Function name: set_soldier
 * Description:   Sets the soldiers of the platoon.
 * Arguments:     file - The file name to the soldier
 *                number - The number of soldiers of this kind.
 *                pname - The plural form of the race name.
 *                        Not needed if the normal race name could
 *                        be extended with a 's'.
 */
public varargs void
set_soldier(string file, int number, string pname = 0)
{
    object ob;
    string name, race, *adjs;
    string long, tmp = "";
    string *item = ({});
    int i, size, avg;

    if (!file || !strlen(file) || !number)
        return;

    if (!ARMYMASTER->register_soldier(file, pname))
        return;

    add_item(ARMYMASTER->query_soldier_items(file),
	     ARMYMASTER->query_soldier_long(file));

    gTotal += number;

    gPlatoon += ([file : ({ number, 0 }) ]);

    ob->remove_object();
}

/*
 * Function name: set_platoon_type
 * Description:   Sets the singular form of the platoon soldier.
 * Arguments:     str - The singular name.
 */
public void
set_platoon_type(string str)
{
    gType = str;
    gPtype = LANG_PWORD(str);
}

/*
 * Function name: set_platoon_ptype
 * Description:   Sets the plural form of the platoon soldiers.
 * Arguments:     str - The plural name.
 */
public void
set_platoon_ptype(string str)
{
    if (!str || !strlen(str))
        return;

    gPtype = str;
}

/*
 * Function name: move_platoon
 * Description:   Perform some platoon action, ie move.
 *                If someone attacked us during our delay.
 *                Make it longer.
 */
public void
move_platoon()
{
    int p, tmp_time = 0;
    string str;
    function f;

    if (gCombat)
    {
        gCombat = 0;
	set_alarm(itof(random(60) + 60), 0.0, "move_platoon");
        return;
    }

    if (gPos >= sizeof(gRoute))
        return;

    if (stringp(gRoute[gPos]))
    {
        str = gRoute[gPos];

        if ((p = member_array(str, E(TO)->query_exit_cmds())) >= 0)
	{
	    tell_room(E(TO), "The " + query_platoon_size() + " marches " + 
		      str + ".\n");
	    move(E(TO)->query_exit_rooms()[p]);
	    tell_room(E(TO), capitalize(LANG_ADDART(query_platoon_size())) + 
		      " of " + gPtype + " marches in.\n");
	}
    }
    else
    {
        if (intp(gRoute[gPos]))
	    tmp_time += gRoute[gPos];
	else
	    if (functionp(gRoute))
	    {
	        f = gRoute[gPos];
		f();
	    }
    }
    gPos++;
    set_alarm(itof(gTime + tmp_time), 0.0, "move_platoon");
}

/*
 * Function name: set_platoon_route
 * Description:   Set the route of the platoon.
 * Arguments:     arr - An array containing strings,
 *                      integers and function pointers.
 *                      The strings are used to determine
 *                      which exit to use. So you _MUST_ use
 *                      the whole word, ie north, NOT 'n'.
 *                      The integers are used as a temporary
 *                      value added to the default move time.
 *                      The function pointers are used to call
 *                      functions within the object.
 */
public void
set_platoon_route(mixed arr)
{
    if (pointerp(arr))
        gRoute = arr;
}

/*
 * Function name: set_platoon_time
 * Description:   Set the time between each move.
 * Arguments:     i - The time in seconds.
 */
public void
set_platoon_time(int i)
{
    gTime = i;
}

/*
 * Function name: kill_platoon
 * Description:   Initialize a combat with the platoon.
 * Arguments:     str - The string given after the verb.
 */
public nomask int
kill_platoon(string str)
{
    object *platoons;
    mixed test;
    
    if (!str || !strlen(str))
        return 0;

    platoons = FIND_STR_IN_OBJECT(str, E(TO));

    if (!sizeof(platoons))
        return 0;

    if (TP->query_attack())
    {
        write("You are already engaged in combat and cant make such an " +
	      "attack.\n");
	return 1;
    }

    test = all_inventory(E(TO))->query_attack();
    test -= ({ 0 });
    if (sizeof(test))
    {
        write("You can't get past the current battle and are not able to " +
	      "make an attack.\n");
	return 1;
    }

    write("You bravely challenge the " + platoons[0]->short() + "\n");
    say(QCTNAME(TP) + " bravely challenge the " + platoons[0]->short() + "\n");

    platoons[0]->setup_attack(TP);

    return 1;
}

public nomask void
setup_attack(object attacker)
{
    object ob;
    string *idx, size;
    int i, r, nr = 5;

    size = query_platoon_size();

    gCombat = 1;

    say("The commander of the " + size + " barks " +
	"a few short orders and points at " + QTNAME(attacker) + "\n");
    write("The commander of the " + size + " barks " +
	"a few short orders and points at you.\n");

    if (gTotal / 5 > 1)
    {
        CLONE_ATTACK(remove_officer(), attacker);

	for (i = 0; i < 4; i++)
	{  
	    idx = m_indexes(gPlatoon);
	    r = random(sizeof(idx));
	    CLONE_ATTACK(idx[r], attacker);
	    if (gPlatoon[idx[r]][P_NUMBER] > 1)
	        gPlatoon[idx[r]][P_NUMBER] -= 1;
	    else
	        gPlatoon = m_delete(gPlatoon, idx[r]);
	}

	gTotal -= 5;
    }
    else
    {
        if (gTotal > 5)
	{
	    nr = gTotal - 5;

	    for (i = 0; i < (gTotal - 5); i++)
	    {  
	        idx = m_indexes(gPlatoon);
		r = random(sizeof(idx));
		CLONE_ATTACK(idx[r], attacker);
		if (gPlatoon[idx[r]][P_NUMBER] > 1)
		    gPlatoon[idx[r]][P_NUMBER] -= 1;
		else
		    gPlatoon = m_delete(gPlatoon, idx[r]);
	    }  
	    gTotal = 5;
	}
	else
	{
	    CLONE_ATTACK(gCommander, attacker);
	    CLONE_ATTACK(remove_officer(), attacker);

	    for (i = 0; i < 3; i++)
	    {
	        idx = m_indexes(gPlatoon);
		CLONE_ATTACK(idx[0], attacker);
		if (gPlatoon[idx[0]][P_NUMBER] > 1)
		    gPlatoon[idx[0]][P_NUMBER] -= 1;
		else
		    gPlatoon = m_delete(gPlatoon, idx[0]);	        
	    }

	    write("The five last members of the former unit " +
		  "snarls at you and then attacks.\n");

	    say("The five last members of the former unit attacks " +
		QTNAME(attacker) + ".\n");

	    remove_object();
	    return;
	}
    }

    say(capitalize(LANG_WNUM(nr)) + " " + (nr == 1 ? "soldier" : "soldiers") +
	" breaks out from the " + size + " and attacks " + 
	QTNAME(attacker) + ".\n");

    write(capitalize(LANG_WNUM(nr)) + " " + (nr == 1 ? "soldier" : 
	"soldiers") + " breaks out from the " + size + " and attacks you.\n");

    update_items();
}

/*
 * Function name: remove_object
 * Description:   The platoon is removed from the face of the earth.
 *                Make the Master object aware of it.
 */
public void
remove_object()
{
    ARMYMASTER->remove_platoon(gId);

    ::remove_object();
}

/*
 * Function name: enter_env
 * Description:   The platoon moves, make the Master object
 *                aware of it.
 */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    ARMYMASTER->set_platoon_room(gId, to);
}

/*
 * Function name: item_id
 * Description:   This is a part of the item patch.
 *                Called from the soul
 */
public int
item_id(string str)
{
   int result;

   if (gPatch)
       return 0;

   result = ::item_id(str);

   if (result)
       all_inventory(environment(this_object()))->krynn_item_patch(1);

   return result;   
}

/*
 * Function name: krynn_item_patch
 * Description:   This is a part of the item patch.
 * Arguments:     i - 0/1 depending on the status.
 */
public void
krynn_item_patch(int i)
{
    gPatch = i;
}

/*
 * Function name:
 * Description:
 * Arguments:  
 * Returns:
 */







