/*
 * Strike Dragon Manager for the Dragonarmies
 *
 * This will keep track of all the strike dragons that are out there
 * for the dragonarmy members.
 *
 * Created by Petros, February 2009
 */
 
#pragma strict_types

#include "../guild.h"

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

// Defines
#define DATA          (DRAGONARMY_DATA + "da_strike_dragons")

public mapping da_strike_dragons = ([ ]);
public mapping da_steed_dragons = ([ ]);

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
    
    if (file_size(DATA + ".o"))
    {
        restore_object(DATA);
    }

    /* Prevent the mapping from being huge */
    foreach (string key, mixed value: da_strike_dragons) {
	if (!value)
	    m_delkey(da_strike_dragons, key);
    }
    foreach (string key, mixed value: da_steed_dragons) {
        if (!value)
            m_delkey(da_steed_dragons, key);
    }

}

public object
query_summoned_strike_dragon(object player)
{
    string name;
    
    if (!objectp(player))
    {
        return 0;
    }
    name = interactive(player) ? player->query_real_name() : OB_NAME(player);
    return da_strike_dragons[name];    
}

public object
query_summoned_dragonsteed(object player)
{
    string name;
    
    if (!objectp(player))
    {
        return 0;
    }
    name = interactive(player) ? player->query_real_name() : OB_NAME(player);
    return da_steed_dragons[name];    
}

public string
dragonfear_dragon_age(object player)
{
    string age;

    if (!objectp(player))
    {
        return 0;
    }
    switch(player->query_dragonarmy_promotions())
    {
    case 4:
	    age = "ancient";
	    break;
    case 3:
    	age = "aged"; 
    	break;
    case 2:
	    age = "adult";
    	break;
    case 1:
	    age = "young";
    	break;
    default:
        return 0;
    }
    
    return age;
}

public object
create_strike_dragon(object player)
{
    object dragon;
    string name;
    
    if (objectp(dragon = query_summoned_strike_dragon(player)))
    {
        return 0;
    }
        
    setuid();
    seteuid(getuid());

    dragon = clone_object(STRIKE_DRAGON);
    dragon->set_summoner(player);
    dragon->set_age(dragonfear_dragon_age(player));
    dragon->heal_hp(10000);
    
    // Add the dragon to the mapping
    name = interactive(player) ? player->query_real_name() : OB_NAME(player);
    da_strike_dragons[name] = dragon;
    save_object(DATA);
    
    return dragon;
}

public object
create_dragonsteed(object player)
{
    object dragon;
    string name;
    
    if (objectp(dragon = query_summoned_dragonsteed(player)))
    {
        return 0;
    }
    
    setuid();
    seteuid(getuid());

    dragon = clone_object(DRAGON_STEED);
    dragon->set_summoner(player);
    dragon->set_gender(!player->query_gender());
    
    // Add the dragon to the mapping
    name = interactive(player) ? player->query_real_name() : OB_NAME(player);
    da_steed_dragons[name] = dragon;
    save_object(DATA);
    
    return dragon;
}

public void
remove_strike_dragon(object player)
{
    string name;
    
    if (!objectp(player))
    {
        return;
    }

    name = interactive(player) ? player->query_real_name() : OB_NAME(player);    
    if (da_strike_dragons[name])
    {
        m_delkey(da_strike_dragons, name);
    }
    save_object(DATA);
}

public void
remove_dragon_steed(object player)
{
    string name;
    
    if (!objectp(player))
    {
        return;
    }

    name = interactive(player) ? player->query_real_name() : OB_NAME(player);    
    if (da_steed_dragons[name])
    {
        m_delkey(da_steed_dragons, name);
    }
    save_object(DATA);
}
