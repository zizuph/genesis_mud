/* created by Aridor, 03/10/94 */

#include "../local.h"
inherit THEIWAR_BASE
#include <macros.h>
#include <money.h>
#include <ss_types.h>

void
create_theiwar()
{
    set_adj("impressive");
    default_config_mobile(120);
    set_all_attack_unarmed(20, 60);
    set_all_hitloc_unarmed(60);
    set_skill(SS_WEP_AXE, 90);
    add_prop(LIVE_I_SEE_DARK, 2);
    set_alignment(-random(20) - 40);
    set_knight_prestige(1440);
}


void
arm_me()
{
  seteuid(getuid(TO));
  MONEY_MAKE(random(10),"gold")->move(TO);
  MONEY_MAKE(random(20),"silver")->move(TO);
  clone_object(OBJ + "hammer2")->move(TO);
  clone_object(OBJ + "smail2")->move(TO);
  if (!random(5))
    clone_object(OBJ + "sh_stone")->move(TO);
  command("wear all");
  command("wield all");
}

void
make_good()
{
    if (good)
      return;
    good = 1;
    remove_adj("dark");
    add_adj("friendly");
    set_long("This is a @@query_adjects@@ dwarf. From the expression on his face " +
	     "you wouldn't think this guy has been here under this " +
	     "mountain all his life. He looks friendly and has a merry twinkle in " +
	     "his eyes, blinking at you from above his beard.\n");
    set_alignment(random(20) + 40);
    set_knight_prestige(-1);
    command("emote cheers up visibly as his aura shifts from dark to light.");
    command("smile");
}

void
make_evil()
{
    if (!good)
      return;
    good = 0;
    remove_adj("friendly");
    add_adj("dark");
    set_long("This is a @@query_adjects@@ dwarf. The expression on his face " +
	     "lets you think this guy must have been here under this " +
	     "mountain all his life. He looks just as hard as the rock " +
	     "around him, probably even harder!\n");
    set_alignment(-random(20) - 40);
    set_knight_prestige(1440);
    command("emote moans and chokes back a scream as his aura shifts from light to dark.");
    command("grin");
}
