
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit M_FILE

void
create_krynn_monster()
{
   int i;
   
   set_name("rat");
   set_race_name("rat");
   set_long(BS(
         "The rats eyes seem to glow in the dim light. It sits up"
         + " on its hind legs and starts to clean itself."
         + "",75));
   
   set_adj("filthy");
   
   for (i = 0; i < 6; i++)
   set_base_stat(i, 2 + random(10));
   
   set_attack_unarmed(0, 10, 10, W_IMPALE, 50, "bite");
   set_attack_unarmed(0, 12, 10, W_SLASH, 50, "bite");
   
   
   set_alignment(-200);
   set_knight_prestige(5);
   seteuid(getuid());
   set_act_time(5);
   add_cact("sniff");
   add_cact("peer");
   add_cact("stare");
   
}

void do_die(object killer)
{
   object ob;
   
   ob = clone_object("/std/lefvtover");
   ob->leftover_init("bite","flea");
   ob->move(TO);
   
   ::do_die(killer);
}
