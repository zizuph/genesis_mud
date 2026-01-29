/*
 * Warhorse Manager for the Knights of Solamnia
 *
 * This will keep track of all the warhorses that are currently out there
 * for Solamnian Knights.
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
#define DATA          (KDATA + "knight_mounts")

public mapping solamnian_mounts = ([ ]);

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
}

public object
query_solamnian_steed(object player)
{
    string name;
    
    if (!living(player))
    {
        return 0;
    }
    
    name = player->query_name();
    if (!IN_ARRAY(name, m_indices(solamnian_mounts)))
    {
        return 0;
    }
    
    return solamnian_mounts[name];
}

public object
retrieve_solamnian_steed(object player)
{
    object steed;
    string name;
    mapping mounts;
    
    if (objectp(steed = query_solamnian_steed(player)))
    {
        NF("You have already retrieved a solamnian steed!\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    
    name = player->query_name();
    mounts = restore_map(MOUNT_FILE);

    if (member_array(name, m_indexes(mounts)) == -1)
    {
        NF("You have no chosen mount yet, you must have a mount to "+
          "retrieve, before you may retrieve it.\n");
        return 0;
    }

    steed = clone_object(VNPC + "steed");
    steed->set_short(mounts[name][0]+" "+mounts[name][1]+" warhorse");
    steed->set_gender((mounts[name][2] == "male" ? 0 : 1 ));
    steed->add_adj(mounts[name][0]);
    steed->add_adj(mounts[name][1]);
    steed->set_owner(player);
    steed->move(environment(player));
        
    solamnian_mounts[name] = steed;
    save_object(DATA);
    
    return steed;
}
