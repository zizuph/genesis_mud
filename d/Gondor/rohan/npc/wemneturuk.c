/* This file is /d/Gondor/rohan/npc/wfolduruk.c         */
/*                                                     */
/* This orc will attack anyone attacking a member      */
/* of his team                                         */
/* copied in parts from /doc/examples/mobiles/troll.c  */
/*
 * Altered by Eowul on Oktober 10th, 2008 - Replaced the 
 * custom corpse with a custom leftover.
 */

inherit "/d/Gondor/common/npc/std_orc";

#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object sword;

void
create_monster()
{
    set_adj("chief");
    ::create_monster();

    set_name("uruk");
    add_name("leader");
    add_name("captain");
    set_pname("uruks");
    set_short("uruk");
    set_pshort("uruks");
    set_race_name("uruk");
    set_long(BS("This is a large black orc. He is one of the uruk-hai, the large black orcs of Mordor."
        + " He seems to be the leader of this pack.\n"));
    default_config_npc(45+random(15));
    set_base_stat(SS_CON, 55+random(15));
    set_base_stat(SS_INT, 20+random(5));
    set_base_stat(SS_WIS, 20+random(5));
    set_base_stat(SS_DIS, 95+random(5));

    set_restrain_path(({ROH_DIR + "plains/l05",
                        ROH_DIR + "plains/l06",
                        ROH_DIR + "plains/l07",
                        ROH_DIR + "plains/l08",
                        ROH_DIR + "plains/l09",
                        ROH_DIR + "plains/l10",
                        ROH_DIR + "plains/k06",
                        ROH_DIR + "plains/k07",
                        ROH_DIR + "plains/k08",
                        ROH_DIR + "plains/k09",
                        ROH_DIR + "plains/k10"}));
    set_monster_home(({ROH_DIR + "plains/l10"}));
    set_alignment(-400-random(5)*50);
    set_skill(SS_WEP_SWORD,50+random(10));

    set_skill(SS_WEP_CLUB,50+random(10));
    set_skill(SS_PARRY,50+random(5));
    set_skill(SS_DEFENCE,50+random(10));

    add_prop(CONT_I_HEIGHT,195+random(20));
    add_prop(CONT_I_WEIGHT,140000+random(10000));
    add_prop(CONT_I_VOLUME,120000+random(20000));

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_cchat("Kill that spy!");
    add_act("shout To me! Everyone to me!");
    add_act("shout Hurry, you bastards! Keep running!");
    add_act("snarl");   
    add_cact("spit");   

    add_leftover(ROH_DIR + "npc/urukheart", "heart", 1, 0, 0, 1);
}

arm_me()
{
    object arm, roarm;

    seteuid(getuid(TO));

    sword = clone_object(WEP_DIR + "uruksword");
    sword->move(TO);
    command("wield all");

    if (random(2))
      {
        arm = clone_object(ARM_DIR + "orcstlarm");
        arm->move(TO);
      }

    if (random(2))
      {
	arm = clone_object(ARM_DIR + "orcshield");
	arm->move(TO);
      }

    if (random(2))
      {
	arm = clone_object(ARM_DIR + "orchelmet");
	arm ->move(TO);
      }
    command("wear all");
}

do_die(object killer)
{
  if(killer->query_prop("_elfhelm_uruk_quest"))
  {
    sword->add_prop("_elfhelm_uruk_quest_weapon",1);
  }
  else
  {
    sword->add_prop("_uruk_quest_weapon",killer->query_real_name());
  }
  ::do_die(killer);
}

query_knight_prestige() {return 800;}
