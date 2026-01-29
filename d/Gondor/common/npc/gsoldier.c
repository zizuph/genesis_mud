/*
 * Modified - Gwyneth (Nov 4, 2000) replaced ~elessar/lib/goodkill.h
 *            with /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include "/d/Gondor/common/lib/logkill.c"

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
  set_name("soldier");
  set_race_name("human");
  set_short("soldier of Gondor");
  set_pshort("soldiers of Gondor");
  set_adj(({"tall","strong"}));
  set_long(BSN("This is one of the soldiers of Gondor, on war duty "
    + "protecting his land from the armies of the evil one, and "
    + "guarding it with his life if necessary. He looks quite "
    + "competent in fighting, as all guards get training with the "
    + "garrison once a week."));
  default_config_npc(random(10)+45);
  set_base_stat(SS_CON, random(10)+55);
  set_skill(SS_WEP_SWORD, random(10)+70);
  set_skill(SS_PARRY,85);
  set_skill(SS_DEFENCE,85);
  set_skill(SS_AWARENESS,70);
  set_alignment(150);
  set_chat_time(20);
  add_chat("Looks like the War is drawing nigh.");
  add_chat("What are you hanging around here for?");
  add_chat("The Enemy is mobilizing his armies.");
  add_chat("I fear the armies of the Evil One.");
  add_chat("I don't like the dark clouds gathering in the east.");
}

public void
arm_me()
{

    FIX_EUID
    clone_object(WEP_DIR + "rndsword")->move(TO);
    command("wield sword");
    clone_object(ARM_DIR + "rndarmour")->move(TO);
    clone_object(ARM_DIR + "rndhelmet")->move(TO);
    command("wear all");
}

public int
check_enemy(object tp)
{
    if ((query_friend_or_foe(tp) < 0) && F_DARE_ATTACK(TO, tp))
    {
        command("say Enemies! Attack!");
        command("kill "+tp->query_real_name());
        return 1;
    }
    return 0;
}

public void
init_living()
{
    ::init_living();
    check_enemy(TP);
}

/* For the Solemnian knights */
public int query_knight_prestige() { return -5; }

