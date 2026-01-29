// file name:        /d/Avenir/common/dark/mon/ogre.c
// creator(s):       Denis, Feb'03, based on Cirion's and Lilith's work
// revision history: 
//   Lilith, Jan'98 - Added gem to inventory.
//   Lilith, Mar'02 - Added leadership qualities for raiding.
//   Denis,  Feb'03 - Made one base file for the ogre base and two ogres
//                    (ogre.c and ogre_raider.c) inheriting it, as the two
//                    had 95% of the code the same.
//   Lilith, Oct '14  added death logging
//   Lilith, Oct '15  modified config_ogre call
//
// purpose:          
//   Random Ogre for the L5 Utterdark Tunnels. They are pretty clever, they
//   follow, wimpy, try to use the best weapon, search for hidden players, etc.
// note:
// bug(s):
// to-do: 

#pragma strict_types

inherit "/d/Avenir/common/dark/mon/ogre_base";

/* Log deaths to weekly statserv */
#include "/d/Avenir/smis/sys/statserv.h"
#include "../dark.h"

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 90000) ? \
(rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
(write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define DEATH_LOG   "/d/Avenir/log/deaths/ogre"

/*
 * Function name: create_monster
 * Description:   Randomly configures ogre non-leader.
 */
void
create_monster()
{
    config_ogre();

    if (random(3))
	set_random_move(5 + random(50));
}



/* Logging death info. */
void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;
	
    if (query_hp() > 0)
        return 0;
	
    if (!killer)
        killer = previous_object();
	
    foos -= ({ killer });
    killers = (foos)->query_name();
	
    /* Logging death for various reasons */
    SCROLLING_LOG(DEATH_LOG, "Ogre ("+ this_object()->query_average_stat() +") by "+ 
				  killer->query_name() +"("+ killer->query_average_stat() +") "+ 
				  (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));
    STATSERV_LOG_EVENT("Utterdark", "Ogre died");
	
    ::do_die(killer);
}


