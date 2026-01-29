/*
 * Path in the Misty Mountains
 * By Finwe, September 2004
 */

#include "/d/Shire/sys/defs.h" 
#include "defs.h"
#include ORC_FILE

#include <macros.h>

inherit PATH_BASE;
//inherit ORCMAKER;

int alarmed;
object leader, warrior1, warrior2, warrior3, scout1, scout2;
object warg;

void add_stuff();
void mount_steed();

void
//create_room()
create_mt_room()
{
    set_vbfc_extra(path_desc1);

    add_exit(PATH_DIR + "npath27", "west",0,5);
    add_exit(PATH_DIR + "npath25", "southeast",0,5);
    reset_shire_room();
}

void
mount_steed()
{
    warg->move(ENV(TO), 1);

    TO->command("mount warg");
}

void
get_mount()
{
    setuid(); seteuid(getuid());
    warg = clone_object("/d/Shire/orcmaker/obj/warg");
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
        leader->set_power(200+random(51));
        leader->set_type(WARRIOR);
        leader->set_aggressive(1);
        leader->set_attack_chance(0);
        leader->move(TO);

        warg = clone_object("/d/Shire/orcmaker/obj/warg");
        warg->set_stats(({125, 125, 125, 80, 125, 125}));
        warg ->move(TO);
        leader->team_join(warg);
        leader->command("mount warg");
        warg->set_restrain_path(MM_DIR);
        warg->set_random_move(3);
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

        warg = clone_object("/d/Shire/orcmaker/obj/warg");
        warg->set_stats(({125, 125, 125, 80, 125, 125}));
        warg ->move(TO);
        leader->team_join(warg);
        warrior1->command("mount warg");
        warg->set_restrain_path(MM_DIR);
        warg->set_random_move(3);
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

        warg = clone_object("/d/Shire/orcmaker/obj/warg");
        warg->set_stats(({125, 125, 125, 80, 125, 125}));
        warg ->move(TO);
        leader->team_join(warg);
        warrior2->command("mount warg");
        warg->set_restrain_path(MM_DIR);
        warg->set_random_move(3);
	    leader->team_join(warrior2);
    }

    if (!warrior3)
    {
        setuid();
        seteuid(getuid());

        warrior3=clone_object(ORCMAKER_DIR+"orcmaker");
	    warrior3->set_power(190+random(51));
    	warrior3->set_type(SCOUT);
	    warrior3->set_aggressive(1);
    	warrior3->set_attack_chance(0);
	    warrior3->move(TO);
        warrior3->set_restrain_path(MM_DIR);
        warrior3->set_random_move(3);



	    leader->team_join(warrior3);
    }

}
