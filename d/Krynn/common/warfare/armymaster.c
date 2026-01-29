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

#define DA_BOARD "/d/Ansalon/taman_busuk/sanction/room/city/yard"
#define POT_BOARD "/d/Ansalon/taman_busuk/neraka/inner/board"
#define KNI_BOARD "/d/Krynn/guilds/knights/guildhall/rooms/war_room"
#define NEI_BOARD "/d/Ansalon/guild/neidar/rooms/board"
#define NP_BOARD "/d/Krynn/que/newports/newport_recruitment"


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
    if (!peace)
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
    if (!peace)
    {
        WAR_LOG("War start attempted during peace.");
        return;
    }

    WAR_LOG("Restarting the war.");
    WARFARE_DEBUG("Restarting the war. [armymaster]");
    
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
    object *obs;
    object inf1, inf2, inf3, inf4, inf5, inf6;
    
    WAR_LOG("Ending the war");
    WARFARE_DEBUG("Ending the war [armymaster]");
    peace = 1;

    // Record outcome of war
    WAR_CLUB_ADMIN->record_krynn_war_outcome();

    // Reset war stats
    WAR_CLUB_ADMIN->reset_krynn_war_stats();

    // Clone board reporter
    // For some reason Krynn-based informers can't post
    // notes on Ansalon boards, so clone the Ansalon
    // informer if adding to any new Ansalon board.
    inf1 = clone_object("/d/Krynn/clubs/warfare/informer"); 
    inf1->set_board_room(NP_BOARD);
    inf1->activate();

    inf2 = clone_object("/d/Ansalon/estwilde/living/clan_informer"); 
    inf2->set_board_room(DA_BOARD);
    inf2->activate();

    inf3 = clone_object("/d/Ansalon/estwilde/living/clan_informer"); 
    inf3->set_board_room(POT_BOARD);
    inf3->activate();

    inf4 = clone_object("/d/Krynn/clubs/warfare/informer"); 
    inf4->set_board_room(KNI_BOARD);
    inf4->activate();

    inf5 = clone_object("/d/Ansalon/estwilde/living/clan_informer"); 
    inf5->set_board_room(NEI_BOARD);
    inf5->activate();

    inf6 = clone_object("/d/Krynn/clubs/warfare/informer"); 
    inf6->set_board_room("/d/Krynn/clubs/warfare/warfare_board");
    inf6->activate();
    
    obs = (map(m_values(areas) + m_values(armies), find_object)) - ({ 0 });
    obs->stop_war();

    if (get_alarm(event_alarm))
        remove_alarm(event_alarm);

    save();
}

/* Function called in the Krynn clock flow when the calendar year
 * ends to reset the warfare system.
 * Calendar runs from 347 until March 26th year 352
 */

public void
reset_warfare_state()
{
    stop_war();
    set_alarm(10.0,0.0, &start_war());
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
    
    //Also, we're not doing recruits or funds anymore
    //Just clone what they need

    if (query_peace())
    {
        remove_alarm(event_alarm);
        return;
    }
    
    arm = m_indexes(armies);
    k = sizeof(arm);

    /*
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

    // Conquer spam check
    if (player->query_prop(PLAYER_LAST_CONQUER))
    {
        int last_conquer_time = player->query_prop(PLAYER_LAST_CONQUER);

        // 4 second cooldown on conquer command
        if(time() < (last_conquer_time + 4))
        {
            notify_fail("You just recently tried to conquer this area! " +
                "You will need to wait a moment before you can attempt " +
                "to conquer again.\n");
            return 0;
        }
    }

    player->add_prop(PLAYER_LAST_CONQUER, time());

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
    if (peace)
        return 0;
    
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
