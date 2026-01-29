// Bazaar Center (/d/Avenir/common/bazaar/centr.c)
// creator(s):   Triana 1994
// purpose:      This where the crowd amasses to watch the public pillory
// last update:  Tepisch Aug 94
// 	             Lucius, 7/7/2006: Added some bounce prevention code; 
//                 cleanups.
//               Lilith, Sep 2021: Removed code blocking people from returning
//                 to the hill to fight Jadestone. This was desgiend to 
//                 prevent "bouncing" and is obsolete.
// note:
// bug(s):
// to-do:       
#pragma strict_types

#include <language.h>

inherit "/d/Avenir/common/bazaar/extr/std_center";
#include "/d/Avenir/common/bazaar/bazaar.h"

#define ALARMV     (1800.0)
#define HILL_EXIT  (EXTR + "hill")

private void check_cowards(void);

private static mapping cowards = ([]);
private static object guard1, guard2, slave1, slave2, troloby, peddler;

public void
reset_room(void)
{
    if (!guard1)
    {
	guard1 = clone_object(NPC + "grd");
	guard1->arm_me();
	guard1->move_living(0, this_object());
    }

    if (!guard2)
    {
	guard2 = clone_object(NPC + "grd");
	guard2->arm_me();
	guard2->move_living(0,this_object());
    }

    guard2->set_leader(guard1);
    guard1->team_join(guard2);

    if (!slave1)
    {
	slave1 = clone_object(NPC + "wom1");
	slave1->arm_me();
	slave1->move_living(0,this_object());
    }

    if (!slave2)
    {
	slave2 = clone_object(NPC + "man1");
	slave2->arm_me();
	slave2->move_living(0,this_object());
    }

    if (!troloby)
    {
	troloby = clone_object(NPC + "p_punisher");
	troloby->equip_me();
	troloby->move_living(0,this_object());
    }

    if(!peddler)
    {
	peddler = clone_object(NPC + "torch_peddler");
	peddler->arm_me();
	peddler->move_living(0,this_object());
    }
}

static void
create_room(void)
{
    setuid();
    seteuid(getuid());

    SHORT("Base of the hill in the center of the Bazaar hill");
    make_the_room(" An aura of excitement clings to the people "
      +"pressing in around you.\n");

    AE(EXTR + "str6", "north", 0);
    AE(EXTR + "str13", "east", 0);
    AE(EXTR + "str12", "west", 0);
    AE(EXTR + "str19", "south", 0);
    AE(HILL_EXIT, "up", "@@exit_check", 5, 0);

    add_prop(OBJ_S_WIZINFO, "To see what cowards have fleed "+
	"from the hilltop:\n\tCall here query_cowards\n\n");

    reset_room();

    set_alarm(ALARMV, ALARMV, &check_cowards());
}

public object *
query_cowards(void)
{
    return m_indexes(cowards);
}

private void
check_cowards(void)
{
    int now = time();

    /* We reset the time instead of deleting the entry
     * so we can see what cowards people have been. */
    foreach(string who, int when : cowards)
    {
	if ((when + 3000) <= now)
	    cowards[who] = 0;
    }
}

public void
am_cowardly(object who)
{
    string whom;

    if (!query_interactive(who))
	return;

    whom = this_player()->query_cap_name();

    if (cowards[whom] && ((time() - cowards[whom]) < 10))
	cowards[whom] = (time() - 60);
    else
	cowards[whom] = time();
}

public int
exit_check(void)
{

// This "anti-bounce" code is not necessary with the guilds being 
// updated to the standard guild library.
// Will continue to keep track of "cowards" running from Jadestone
// but will not longer preventing players returning to fight her.
//  -- Lilith, Sept 2021
/*
    object block;
    string whom;

    if (!query_interactive(this_player()))
	return 0;

    whom = this_player()->query_cap_name();

    if (!cowards[whom])
	return 0;

    if ((time() - cowards[whom]) <= 5)
	return 0;

    if (!objectp(block = HILL_EXIT->coward_blocker()))
	return 0;

    whom = CAP(LANG_ADDART(block->query_nonmet_name()));
    write(whom +" blocks your attempt to climb the hill.\n");
    say(whom +" blocks "+ QTPNAME(this_player()) +" attempt "+
	"to climb the hill.\n");

    return 1;
*/
    return 0;
}
