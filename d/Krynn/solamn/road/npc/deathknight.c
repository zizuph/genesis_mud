/*
 * A Death Knight of Lord Soth
 * near Dargaard Keep.
 * ~Aridor 08/98
 *
 * originially:
 * A zombie, found in the crypts
 * 950421 by Rastlin
 *
 */

#include "../local.h"
#include <ss_types.h>
#include <wa_types.h>

inherit M_FILE

object gEnemy;

void
create_krynn_monster()
{
   int i;

   set_name("knight");
   set_pname("knights");
   set_race_name("human");
   set_short("hideous death knight");
   set_pshort("death knights");
   set_long("He is one of the former guards of Lord Soth. In the centuries " +
	    "since, however, an evil perversion has corrupted the guard, " +
	    "turning them into mindless zombies commanded to perform only one task: " +
	    "kill all trespassers.\n"); 
   
   set_adj(({"hideous", "death"}));
   set_gender(G_MALE);
   
   for (i = 0; i < 5; i++)
     set_base_stat(i, 80 + random(20));
   set_base_stat(SS_DIS, 150 + random(40));
   
   set_skill(SS_DEFENCE,      40);
   set_skill(SS_PARRY,        60);
   set_skill(SS_WEP_SWORD,    80);
   set_skill(SS_AWARENESS,   200);
   add_prop(LIVE_I_QUICKNESS, 10);
   add_prop(LIVE_I_SEE_DARK, 100);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(NPC_I_NO_LOOKS,    1);
   add_prop(LIVE_I_UNDEAD,    30);
   
   set_aggressive(1);

   set_alignment(-320);
   set_knight_prestige(230);

   set_all_hitloc_unarmed(45);

   seteuid(getuid());

   set_alarm(1.0, 0.0, "arm_me");
}

public void
arm_me()
{
    clone_object("/d/Krynn/pax/weapon/longsword")->move(TO);
    command("wield all");
    clone_object("/d/Krynn/pax/armour/leather_arm")->move(TO);
    command("wear all");
}

