/*
 * This file randomly generates orcs for orc camps.
 * The most it will generate is based on MAX_ORCS in the 
 * header file. Also, it will generate one of 5 different 
 * orc types. They are:
 * 0-Slave, 1-Guard, 2-Warrior, 3-Scout, 4-Slave Driver
 * These types are based on the orcmaker types
 *
 * Tent differ from camp orcs; they don't wander about 
 * the camp or leave their tent and are stronger,
 * By Finwe, July 2000
 */

#include <language.h>
#include "local.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#define TO this_object()
object *orcs = ({ });

public void
clone_tent_orcs()
{
    int i;
    int num_of_orcs;
    int kind_of_orc;
    object orcleader;

    setuid();
    seteuid(getuid());

    orcs = filter(orcs, objectp);
    num_of_orcs=random(4);
 
    if (!present("leader"))
    {
       orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
       orcleader->set_long("This is an monstrously large orc leader.\n");
       orcleader->add_name("leader");
       orcleader->set_power(35 + random(21));
       orcleader->set_type(GUARD);
       orcleader->move(TO);
    }
    if (!num_of_orcs)
    {
        return;
    }
    if (sizeof(orcs) < num_of_orcs)
    {
        orcs = orcs + allocate(num_of_orcs - sizeof(orcs));
    }
    for(i = 0; i < num_of_orcs; i++)
    {
        if(!orcs[i])
        {
            kind_of_orc = random(ORC_TYPE);
            orcs[i] = clone_object(ORCMAKER_DIR + "orcmaker");
            orcs[i]->set_power(30 + random(16));
            orcs[i]->set_type(kind_of_orc);
            orcs[i]->move(TO);
            orcleader->team_join(orcs[i]);
        }
        else if(orcs[i]->query_leader() != orcleader)
        {
            orcleader->team_join(orcs[i]);
        }
    }
}


public void
clone_camp_orcs()
{
    int i;
    int num_of_orcs;
    int kind_of_orc;
    object orcleader;

    setuid();
    seteuid(getuid());
  
    num_of_orcs=random(3)+1;
    orcs = filter(orcs, objectp);

    if (!present("leader"))
    {
        orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
        orcleader->set_long("This is an monstrously large orc leader.\n");
        orcleader->add_name("leader");
        orcleader->set_power(35 + random(20));
        orcleader->set_type(GUARD);
        orcleader->move(TO);
    }
    if (!num_of_orcs)
    {
        return;
    }
    if (sizeof(orcs) < num_of_orcs)
    {
        orcs = orcs + allocate(num_of_orcs - sizeof(orcs));
    }
    for(i = 0; i < num_of_orcs; i++)
    {
        if(!orcs[i])
        {
            kind_of_orc = random(ORC_TYPE);
            orcs[i] = clone_object(ORCMAKER_DIR + "orcmaker");
            orcs[i]->set_power(20 + random(10));
            orcs[i]->set_type(kind_of_orc);
            orcs[i]->move(TO);
            orcleader->team_join(orcs[i]);
            orcs[i]->set_random_move(3);
         }
         else if(orcs[i]->query_leader() != orcleader)
         {
             orcleader->team_join(orcs[i]);
         }
    }
}
