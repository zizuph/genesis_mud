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

/*
 * Warning - 30, 20, 20, 23, 25, 27
 * Wandering - 17, 25, 16, 18, 12, 20
 * Invading - weak
 */

#include <language.h>
#include "local.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#define TO this_object()
object *orcs = ({ });

public void clone_tent_orcs()
{
    int i;
    int num_of_orcs;
    int kind_of_orc;
    object orcleader;

    setuid();
    seteuid(getuid());
  
    num_of_orcs = random(3);
 
    if (!present("leader"))
    {
       orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
       orcleader->set_long("This is an monstrously large orc leader.\n");
       orcleader->add_name("leader");
       orcleader->set_power(35 + random(21));
       orcleader->set_type(GUARD);
       orcleader->move(TO);
    }
    if(!sizeof(orcs))
        orcs = allocate(num_of_orcs);
    for(i = 0; i < num_of_orcs; i++)
        if(!orcs[i])
    {
        kind_of_orc = random(ORC_TYPE);
        orcs[i] = clone_object(ORCMAKER_DIR + "orcmaker");
        orcs[i]->set_power(30 + random(16));
        orcs[i]->set_type(kind_of_orc);
        orcs[i]->move(TO);
        orcleader->team_join(orcs[i]);
 
    }
    else
        if(orcs[i]->query_leader() != orcleader)
        orcleader->team_join(orcs[i]);
}


public void clone_camp_orcs()
{
    int i;
    int num_of_orcs;
    int kind_of_orc;
    object orcleader;

    setuid();
    seteuid(getuid());
  
    num_of_orcs = random(3);
 
    if (!present("leader"))
    {
       orcleader = clone_object(ORCMAKER_DIR + "orcmaker");
       orcleader->set_long("This is an monstrously large orc leader.\n");
       orcleader->add_name("leader");
       orcleader->set_power(35 + random(20));
       orcleader->set_type(GUARD);
       orcleader->move(TO);
    }
    if(!sizeof(orcs))
        orcs = allocate(num_of_orcs);
    for(i = 0; i < num_of_orcs; i++)
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
    else
        if(orcs[i]->query_leader() != orcleader)
        orcleader->team_join(orcs[i]);
}

public void clone_warning_orcs()
{
    object orc, orc2, orc3;
    if(!present("orc"))
    {
        orc = clone_object(EVE_NPC + "warning_orc");
        orc->move(TO);
        orc2 = clone_object(EVE_NPC + "warning_orc");
        orc2->move(TO);
        orc3 = clone_object(EVE_NPC + "warning_orc");
        orc3->move(TO);
     }


}

public void clone_invading_orcs()
{
    object orc, orc2, orc3;
    if(!present("orc"))
    {
        orc = clone_object(EVE_NPC + "invading_orc");
        orc->move(TO);
        orc2 = clone_object(EVE_NPC + "invading_orc");
        orc2->move(TO);
        orc3 = clone_object(EVE_NPC + "invading_orc");
        orc3->move(TO);
    }
}

public void clone_wandering_orcs()
{
    object orc, orc2, orc3;
    if(!present("orc"))
    {
        orc = clone_object(EVE_NPC + "wandering_orc");
        orc->move(TO);
        orc2 = clone_object(EVE_NPC + "wandering_orc");
        orc2->move(TO);
        orc3 = clone_object(EVE_NPC + "wandering_orc");
        orc3->move(TO);
    }

}
