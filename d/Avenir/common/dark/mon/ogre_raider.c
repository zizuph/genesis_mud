// file name:        /d/Avenir/common/dark/mon/ogre_raider.c
// creator(s):       Denis, Feb'03 from the Cirion's and Lilith's work.
// revision history: 
//   Lilith, Jan'98 - Added gem to inventory.
//   Lilith, Mar'02 - Added leadership qualities for raiding.
//   Denis,  Feb'03 - Made one base file for the ogre base and two ogres
//                    (ogre.c and ogre_raider.c) inheriting it, as the two
//                    had 95% of the code the same.
// purpose:          
//   Ogre leader. Will add other ogres to a tem enroute to Shadow union halls.
// note:
// bug(s):
// to-do: 
#pragma strict_types

inherit "/d/Avenir/common/dark/mon/ogre_base";

#include "/d/Avenir/common/dark/dark.h"
#define TSIZE 3

/*
 * Function name: create_monster
 * Description:   Creates a new ogre leader (raider) 
 */
public void
create_monster(void)
{
    setuid();
    seteuid(getuid());

    config_ogre();
    add_name(({"raider", "leader"}));
	
}

/*
 * Function name: init_living
 * Description:   Upon meeting an ogre tries to add him to the team.
 */
public void
init_living(void)
{
    ::init_living();

    // probably at the Gate, bang on it. 
	if (TP->query_prop("_live_i_am_sybarite"))
	    command("bash gate with weapon");
 
    if (query_interactive(TP))
	return;

    if (TP->query_race_name() != "ogre")
	return;

    if (TP->query_prop("_i_am_raiding_ogre"))
    {	
    if (sizeof(query_team_others()) < TSIZE)
    {
	team_join(TP);
	TP->set_leader(TO);
    }
	}
}  
