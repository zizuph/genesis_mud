/*
 * sivak_leader.c
 *
 * The leader of the teams in Kurinost.
 *
 * Copyright (C): created by Aridor 04/19/94
 *     Copied by:  Kellon, November 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <ss_types.h>

// I N H E R I T E D   F I L E S
inherit SIVAK;
inherit AUTO_TEAM

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_sivak
 *  Arguments:
 *  Returns  :
 * 
 *  Create the sivak leader.
 *
 */
public void
create_sivak()
{
    int j = random(6) + 3;
   /* j is the level of the draconian */
   
   set_pick_up_team(({ "aurak", "sivak", "bozak", "hobgoblin" }));
   set_max_team_size_auto_join(4);

   for (int i = 0; i < 6; i++)
   {
       set_base_stat(i, j * 10 + random(10) + 30);
   }

   set_skill(SS_DEFENCE,     j * 5 + random(4) + 65);
   set_skill(SS_PARRY,       j * 4 + random(4) + 65);
   set_skill(SS_WEP_SWORD,   j * 4 + random(4) + 65);
   set_skill(SS_2H_COMBAT,   j * 4 + random(4) + 65);
   set_skill(SS_WEP_KNIFE,   j * 4 + random(4) + 65);
   set_skill(SS_WEP_CLUB,    j * 4 + random(4) + 65);
   set_skill(SS_WEP_POLEARM, j * 4 + random(4) + 65);
   set_skill(SS_WEP_JAVELIN, j * 4 + random(4) + 65);
   set_skill(SS_WEP_AXE,     j * 4 + random(4) + 65);
   
   set_act_time(3);
   add_act("scream");
   add_act("stare");
   add_act("emote shows you his claws.");
   add_act("say What are you doing here?");
   add_act(({"say Get lost!", "laugh"}));
   add_act("emote shows you the finger, or rather, his middle claw.");
   add_act("frown");
   add_act("grin");
   add_act("giggle");
   add_act("twiddle");

   set_cact_time(10);
   add_cact("say You really think you can defeat me?\n");
   add_cact("say Ahhh, now I can test my battle skill.\n");
   add_cact("say I didn't even feel that!\n");
   add_cact("say Is that all you can do?\n");
   add_cact("say Don't take it personally but I'll kill you.\n");
   add_cact("grin");
   
   set_color("green");
}


/*
 *  FUNCTION : init_living
 *  Arguments:
 *  Returns  :
 * 
 *  Initiate the team pickup for the sivak leader.
 *
 */
public void
init_living()
{
    init_team_pickup();

    ::init_living();
}

