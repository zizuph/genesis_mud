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
#define TO this_object()

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
