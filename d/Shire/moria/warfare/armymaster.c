/*
 * /d/Krynn/common/warfare/armymaster.c
 *
 * This is the Armymaster of Krynn
 * It was originally coded by Aridor.
 *
 */
#pragma no_clone
#pragma strict_types

#include <macros.h>
#include "warfare.h"

static mapping areas, armies;
static int event_alarm;
static string *conquer_rewards;

int peace;           /* War/Peace State */
mapping quests;      /* Who solved what quests? */

/* Prototypes */
public void load_armies();
public void load_areas();
public void start_war();
public string *query_areas_of_army(string army);
int query_peace();
static void war_events();
string army_of_player(object player);

public void
create()
{
    object *obs;
    string *idx;
    int k;

    /* Initalize */
    areas = ([ ]);
    armies = ([ ]);
    quests = ([ ]);
    
    peace = 1;        /* Default is peace */

    setuid();
    seteuid(getuid());
    
    /* Load */
    if (file_size(MASTER + ".o") > 0)
	restore_object(MASTER);
    
    load_armies();
    load_areas();

    /* If it's not peace then we fire up the alarms */
    //Due to long uptimes, it's always war!
    //if (!peace)
	event_alarm = set_alarm(0.0, 600.0, &war_events());
    //populate some
    war_events();

    /* Apply Quest Effects */
    
    obs = map(m_values(areas) + m_values(armies), find_object);

    idx = m_indexes(quests);
    k = sizeof(idx);

    while (k--)
    {
	obs->quest_effect(idx[k], quests[idx[k]]);
    }

}

public void
save()
{
    object *obs;
    
    WAR_LOG("Saving war state."); 

    save_object(MASTER);
    
    obs = map(m_values(areas) + m_values(armies), find_object);
    obs -= ({ 0 });
    
    obs->save();
}

public int
remove_object()
{
    save();
    destruct();
    return 1;
}

/*
 * Wander through the armies dir and load all armies specified
 * there.
 */
public void
load_armies()
{
    object army;
    string *files, file;
    int k;
    
    files = get_dir(ARMY_PATH + "*.c");
    k = sizeof(files);

    while (k--)
    {
	file = ARMY_PATH + files[k];
	WAR_LOG("Loading army: " + file);
	if (LOAD_ERR(file) || !(army = find_object(file)))
	    continue;
	
	armies[army->query_army_name()] = file;
    }
}

/*
 * Wander through the area dir and load all areas found there.
 */
public void
load_areas()
{
    object area;
    string *files, file;
    int k;
    
    files = get_dir(AREA_PATH + "*.c");
    k = sizeof(files);

    while (k--)
    {
	file = AREA_PATH + files[k];
	WAR_LOG("Loading area: " + file);
	if (LOAD_ERR(file) || !(area = find_object(file)))
	    continue;
	
	areas[area->query_area_name()] = file;
    }
}

/*
 * start_war
 *
 * Sets up a starting state for the war.
 * Clears all variables. 
 */
public void
start_war()
{
    object *obs;
    
    //It's always war until we plan for the long uptimes, which I'm
    //too lazy to do.  The players like killing all the time anyway
    /*
    if (!peace)
    {
        WAR_LOG("War start attempted during peace.");
        return;
    }
    */

    WAR_LOG("Restarting the war.");
    
    peace = 0;
    quests = ([ ]);
    
    obs = map(m_values(areas) + m_values(armies), find_object);
    obs -= ({ 0 });
    obs->start_war();

    if (!get_alarm(event_alarm))
	event_alarm = set_alarm(0.0, 600.0, &war_events());
    war_events();
}

/*
 * Ends the war
 */
public void
stop_war()
{
//No more stopping wars
    return;
    object *obs;
    
    WAR_LOG("Ending the war");
    peace = 1;
    
    obs = (map(m_values(areas) + m_values(armies), find_object)) - ({ 0 });
    obs->stop_war();
    
    if (get_alarm(event_alarm))
	remove_alarm(event_alarm);

    save();
}

/*
 * War actions
 *
 * Loops through the areas and credits the owners with funds and recruits.
 */
static void
war_events()
{
    string *arm, *are;
    int k, y;
    float recruits;
    object *obs;
    
    //It's always war due to long uptimes
    //Also, we're not doing recruits or funds anymore
    //Just clone what they need

    /*
    if (query_peace())
    {
	remove_alarm(event_alarm);
	return;
    }

    arm = m_indexes(armies);
    k = sizeof(arm);

    while (k--)
    {
	recruits = 0.0;
	
	are = query_areas_of_army(arm[k]);
	y = sizeof(are);

	while (y--)
	{
	    // How many recruits we get depends on how many we have 
	    recruits += RECRUIT_RATE(itof(areas[are[y]]->
		query_recruit_base()),
		itof(armies[arm[k]]->query_recruits())) *
		armies[arm[k]]->query_recruit_modifier();
	    
	    // Different armies have different tax pressure 
	    armies[arm[k]]->add_funds(areas[are[y]]->query_tax_base() *
		armies[arm[k]]->query_tax(are[y]) / 100);
	}


	armies[arm[k]]->add_recruits(ftoi(recruits));
	WAR_LOG(arm[k] + " got " + ftoi(recruits));
    }
*/    
    //Area and Army effect will take care of what the areas need to
    //do every interval
    obs = map(m_values(areas), find_object) - ({ 0 });
    obs->area_effect();

    obs = map(m_values(armies), find_object) - ({ 0 });
    obs->army_effect();
    
}

/* API */

/*
 * Peace ?
 */
int
query_peace()
{
//always war
     return 0;
    return peace;
}

/*
 * 
 */
public string *
query_areas_of_army(string army)
{
    return map(filter(m_values(areas), &operator(==)(army) @
        &->query_controller()), &->query_area_name());
}

/*
 * Returns the controller of an area.
 */ 
public string
army_in_area(string area)
{
    if (!areas[area])
	return 0;

    return areas[area]->query_controller();
}

public int
army_alignment(string army)
{
    if (!armies[army])
	return 0;
    
    return armies[army]->query_alignment();
}

/*
 * Function Name: register_room
 * Description  : Register a room as belonging to an area
 */
public void
register_room(string area)
{
    string room;

    room = file_name(previous_object());

    //Only domain rooms please
    if (!wildmatch("/d/*", room))
    {
        areas[area]->remove_room(room);
        return;
    }

    if (!areas[area])
    {
	WAR_LOG("Register failed - '" + area + "' " + room);
	return;
    }
    
    areas[area]->add_room(room);
}

/*
 * Function Name: rooms_in_area
 * Description  : Counts how many rooms we have in an area
 */
public int
rooms_in_area(string area)
{
    if (!areas[area])
    {
	WAR_LOG("Room count failed - '" + area);
	return 0;
    }

    return areas[area]->count_rooms();
}

/*
 * What armies are there? 
 */
string *
query_armies()
{
    return m_indexes(armies);
}

/*
 * What areas are there?
 */
string *
query_areas()
{
    return m_indexes(areas);
}

/*
 * Is this an area?
 */
string
query_area(string str)
{
    return areas[str];
}

/*
 * Is this an army?
 */
string
query_army(string str)
{
    return armies[str];
}

/*
 * Conquer an area!
 */
public int
conquer(object player, string area)
{
    string army;

    if (query_peace())
    {
	notify_fail("\nConquer? - But you are not at war!\n\n");
	return 0;
    }

#ifdef TESTING
    if (!player->query_wiz_level())
    {
        notify_fail("You can't do that right now.\n");
        return 0;
    }
#endif
    
    if (!areas[area])
    {
	notify_fail("Something very strange happened.\n");
	return 0;
    }

    army = army_of_player(player);
    if (!army)
    {
	notify_fail("You can't conquer areas.\n");
	return 0;
    }
    
    return areas[area]->conquer(army, player);    
}

/*
 * Reports an npc kill
 */
public void
npc_killed(string area, string npc)
{
    if (!areas[area])
    {
	WAR_LOG("npc killed in non_area: " + area + "/" + npc);
	return;
    }

    areas[area]->remove_unit(npc);
}

object
clone_new_npc(string area)
{
    return areas[area]->clone_unit();
}

/*
 * Quest Stuff
 */

/*
 * Function Name: done_quest
 * Description  : Called when a quest has been solved.
 *                If this is the first time it has been
 *                solved since the start of the war the quest
 *                effects will be applied.
 */
public varargs void
done_quest(string quest_name, mixed solver)
{
    string army;
    object *obs;
    
    if (quests[quest_name])
	return;

    if (objectp(solver))
    {
	if (!(army = army_of_player(solver)))
	    army = "Undefined Army";
    }
    else if (stringp(solver))
    {
	if (armies[solver])
	    army = solver;
	else
	    army = "Undefined Army";
    }
    
    quests[quest_name] = army;
    
    obs = map(m_values(areas) + m_values(armies), find_object) - ({ 0 });
    obs->quest_effect(quest_name, army);
}

string
army_of_player(object player)
{
    object *obs;

    obs = map(m_values(armies), find_object) - ({ 0 });
    obs = filter(obs, &->query_member(player));
    if (!sizeof(obs))
	return 0;
    return obs[0]->query_army_name();
}

public void
load_reward_items()
{
    conquer_rewards = ({});

    object reward;
    string *files, file;
    int k;
    
    files = get_dir(REWARDS_PATH + "*.c");
    k = sizeof(files);

    while (k--)
    {
	    file = REWARDS_PATH + files[k];
	    WAR_LOG("Loading reward: " + file);

	    if (LOAD_ERR(file) || !(reward = find_object(file)))
	        continue;
    	
        conquer_rewards += ({ file });
    }
}

//Create a reward item
public object
reward_item(object player)
{
    string file;
    object reward;

    if (!conquer_rewards || !sizeof(conquer_rewards))
    {
        load_reward_items();
    }

    int k = random(sizeof(conquer_rewards));

    file = conquer_rewards[k];

    WAR_LOG("Rewarding "+file+" for "+player->query_real_name());

    reward = clone_object(file);
    if (!objectp(reward))
    {
	    WAR_LOG("Error cloning " + file );
        player->catch_msg("Failed to create a reward.  Please bug.\n");
    }

    return reward;
}

public string
stat_object()
{
    string str;
    object *obs;
    
    obs = map(m_values(armies), find_object) - ({ 0 });
    str = implode(obs->stat_object(), "\n");
    
    obs = map(m_values(areas), find_object) - ({ 0 });
    str += implode(obs->stat_object(), "\n");

    return str;
}
