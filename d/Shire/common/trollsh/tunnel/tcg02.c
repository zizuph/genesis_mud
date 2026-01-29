/*
 * Guard room in the Trollshaws
 * By Finwe, October 2001
 * Updated room so Grouthar is here instead of out in the open
 * tunnel. Moved from ta16.c
 * Finwe, January 2018
 */

#pragma strict_types

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
            say ("The terrible menacing troll blocks " + QCTNAME(TP) +
                " from leaving.\n");
            return (TRUE);
        }
        else
        {
            write ("The terrible menacing troll snarls: Return and die!\n");
            say (QCTNAME(TP)+" runs from the terrible menacing troll in shame.\n");
            TP->add_prop (PLAYER_I_BOUNCE_WARNED, TRUE);
            log_file (S_BOUNCE_LOG, ctime (time ()) + " " + sWhoCap + 
                " given a bouncing warning.\n");
             return (FALSE);
        }
    }

    if (TP->query_skill(SS_SNEAK) > 18+random(10))
    {
        write("You manage to sneak past the terrible menacing troll.\n");
        say (QCTNAME(TP)+" managed to sneak past the terrible menacing troll.\n");
        return (FALSE);
    }

    if (TP->query_skill(SS_HIDE) > 25+random(10))
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
    set_short("A messy room in the Trollshaws");
    add_my_desc("This is a messy guard room. It is used by the troll that rules over the Trollshaws. Piles of garbage fill the room, showing the trolls come here often and pay tribute to the Troll.\n");

    add_exit(TUN_DIR + "tc05", "south",check_exit);

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
