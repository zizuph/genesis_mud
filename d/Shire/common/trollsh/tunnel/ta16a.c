/*
 * Tunnel beneath the Trollshaws
 * By Finwe, August 2001
 * 
 * Grothaur randomly blocks attackers from leaving while fighting him.
 * Finwe, January 2004
 *
 * The block now works all except the first time for bouncers.
 * Arandir, January 2004
 *
 * Grothaur and orcs are teamed so all attack when Grothaur's attacked.
 * Finwe, Nov 2004
 *
 */
 

#pragma strict_types

inherit "/d/Shire/std/room.c";

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define FALSE	0
#define TRUE	1

#define MAX_TROLLS 3

#define PLAYER_I_BOUNCE_WARNED	"_player_i_bounce_warned"

#define S_BOUNCE_LOG		"bounce_grothaur"


inherit TUNNEL_BASE;
static object grothaur, leader;
static object *trolls  = allocate(MAX_TROLLS);

void
make_trolls();

void
reset_room()
{
  make_trolls();
}


int check_exit() 
{
  string sWho = TP->query_real_name ();
  string sWhoCap = capitalize (sWho);
  object oGrothaur = present ("grothaur");
  
  if (!objectp (oGrothaur)) return (FALSE);

  if (oGrothaur->s_is_bouncer (TP))
  {
    if (TP->query_prop (PLAYER_I_BOUNCE_WARNED))
    {
      write ("The terrible menacing troll snarls: In a hurry?\n");
      say ("The terrible menacing troll blocks " + QCTNAME(TP) + " from leaving.\n");
      return (TRUE);
    }
    else
    {
      write ("The terrible menacing troll snarls: Return and die!\n");
      say (QCTNAME(TP)+" runs from the terrible menacing troll in shame.\n");
      TP->add_prop (PLAYER_I_BOUNCE_WARNED, TRUE);
      log_file (S_BOUNCE_LOG, ctime (time ()) + " " + sWhoCap + " given a bouncing warning.\n");
      return (FALSE);
    }
  }

  if (TP->query_skill(SS_SNEAK) > 18+random(10))
  {
    write("You manage to sneak past the terrible menacing troll.\n");
    say (QCTNAME(TP)+" managed to sneak past the terrible menacing troll.\n");
    return (FALSE);
  }
  if (TP->query_skill(SS_HIDE) > 18+random(10))
  {
    write ("You manage to hide from the terrible menacing troll and escape.\n");
    say (QCTNAME(TP)+" hides and escapes the terrible menacing troll's attention.\n");
    return (FALSE);
  }

  write ("The terrible menacing troll snarls: No one gets past me...\n");
  say ("The terrible menacing troll blocks " + QCTNAME(TP) + " from leaving.\n");
  return (TRUE);
}


void
create_tunnel_room()
{
    set_long("@@tunnel_desc6@@");
    add_my_desc("The tunnel becomes wider here. Many exits lead " +
        "off in various directions. The main ones lead north, " +
        "west, and southeast.\n");

    add_exit(TUN_DIR + "ta24", "north",check_exit);
    add_exit(TUN_DIR + "ta15", "west",check_exit);
    add_exit(TUN_DIR + "ta17", "southeast",check_exit);

    reset_room();
}


void
make_trolls()
{
    int index;

    setuid();
    seteuid(getuid());
   if(!objectp(grothaur))
    {
        grothaur = clone_object(NPC_DIR + "grothaur");
        grothaur->move(TO);
    }

    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_TROLLS; index++)
    {
        if (!objectp(trolls[index]))
        {
            trolls[index] = clone_object(NPC_DIR + "newtroll");
            trolls[index]->move(TO);
            grothaur->team_join(trolls[index]);
 
        }
    }

}
