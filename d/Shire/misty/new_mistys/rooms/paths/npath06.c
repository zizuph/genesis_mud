/*
 * Path in the Misty Mountains
 * By Finwe, September 2004
 */

#include "/d/Shire/sys/defs.h" 
#include "defs.h"
#include ORC_FILE
#include <macros.h>

inherit PATH_BASE;

int alarmed;
object leader, warrior1, warrior2, scout1;

void add_stuff();

void
//create_room()
create_mt_room()
{
    set_vbfc_extra(path_desc1);

    add_exit(PATH_DIR + "npath07", "north",0,5);
    add_exit(PATH_DIR + "npath05", "south",0,5);
    reset_shire_room();

}

void reset_shire_room()
{
    add_stuff();
}

void
add_stuff()
{
    int index;

    if (!leader)
    {
        setuid();
        seteuid(getuid());

        leader=clone_object(ORCMAKER_DIR+"orcmaker");
        leader->set_power(225+random(51));
        leader->set_type(WARRIOR);
        leader->set_aggressive(1);
        leader->set_attack_chance(0);
        leader->move(TO);
        leader->set_restrain_path(MM_DIR);
        leader->set_random_move(3);
    }

    if (!warrior1)
    {
        setuid();
        seteuid(getuid());

      	warrior1=clone_object(ORCMAKER_DIR+"orcmaker");
	    warrior1->set_power(200+random(51));
    	warrior1->set_type(WARRIOR);
	    warrior1->set_aggressive(1);
    	warrior1->set_attack_chance(0);
	    warrior1->move(TO);
        warrior1->set_restrain_path(MM_DIR);
        warrior1->set_random_move(3);
        leader->team_join(warrior1);
    }

    if (!warrior2)
    {
        setuid();
        seteuid(getuid());

        warrior2=clone_object(ORCMAKER_DIR+"orcmaker");
    	warrior2->set_power(200+random(51));
	    warrior2->set_type(WARRIOR);
    	warrior2->set_aggressive(1);
	    warrior2->set_attack_chance(0);
    	warrior2->move(TO);
        warrior2->set_restrain_path(MM_DIR);
        warrior2->set_random_move(3);
    	leader->team_join(warrior2);
    }

    if (!scout1)
    {
        setuid();
        seteuid(getuid());

        scout1=clone_object(ORCMAKER_DIR+"orcmaker");
	    scout1->set_power(190+random(51));
    	scout1->set_type(SCOUT);
	    scout1->set_aggressive(1);
    	scout1->set_attack_chance(0);
	    scout1->move(TO);
        scout1->set_restrain_path(MM_DIR);
        scout1->set_random_move(3);
    	leader->team_join(scout1);
    }
}
