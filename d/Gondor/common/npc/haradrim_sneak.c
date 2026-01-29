/*
 * /d/Gondor/common/npc/haradrim_sneak.c
 *
 * A haradrim warriors.
 *
 * By someone.
 *
 * Revision:
 * Updated code: Boron May 30. 1996
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";
#include "/d/Gondor/common/lib/logkill.c"

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
  set_name("haradrim");
  set_pname(({"men", "warriors", "haradrim"}));
  add_name(({"man", "southron", "warrior" }));
  set_adj( ({"tall", "dark-skinned"}) );
  set_long(BSN("This is a tall and dark-skinned haradrim warrior, "
      + "clad in bright clothing and with golden earrings. He "
      + "looks hatefully at you, brandishing his sharp scimitar."));
  set_race_name("human");
  set_alignment(-200-random(24));
  set_aggressive(1);
  default_config_npc(random(10)+58);
  set_base_stat(SS_CON,random(10)+62);

  set_skill(SS_WEP_SWORD, random(10)+70);
  set_skill(SS_AWARENESS, 20 + random(40));
  set_skill(SS_PARRY,85);
  set_skill(SS_DEFENCE,85);
  set_chat_time(16);
  add_chat("I'll take the scalps of every dunedain that I kill!");
  add_chat("If only the signal for our attack would come.");
  add_chat("I'm tired of waiting in this filthy camp!");
  add_chat("Why do we have to camp with the dirty orcs?");
  add_chat("We will plunder the houses of Minas Tirith soon!");
  set_cchat_time(5);
  add_cchat("Bleed to death, dirty hyena!");
  add_cchat("Your neck won't stand a chance to my scimitar!");
  add_cchat("Die screaming, dog!");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Run while you can, filthy rat!"}));
}

public void
get_armed()
{
    FIX_EUID
    clone_object(WEP_DIR + "haradscim")->move(TO);
    command("wield scimitar");
    clone_object(ARM_DIR + "haradcloak")->move(TO);
    command("wear cloak");
    clone_object(ARM_DIR + "haradshield")->move(TO);
    command("wear shield");
}

init_attack()
{
  int delta;
  if(TP->query_npc() || TP->query_alignment() < -100) return;

  delta = TO->query_skill(SS_AWARENESS) - TP->query_skill(SS_SNEAK);
  if(delta > 45) delta = 45;
  if(delta < -30) delta = -30;
  if((delta > 0 && random(100) > 75 + delta/2) || (delta <= 0 && random(100) > 30 + delta))
  {
    set_alarm(2.0, 0.0, did_sneak(TP));
    return;
  }

  set_alarm(2.0, 0.0, aggressive_attack(TP));   
}

did_sneak()
{
  if(TO->query_attack()) return;
  write("Skillfully, you manage to sneak past the eyes of the Haradrim.\n");
  return;
}

/* Solemnian prestige */
query_knight_prestige() { return 500; }
