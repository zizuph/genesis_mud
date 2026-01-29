/*
 * Modified - Gwyneth (Nov 4, 2000) replaced ~elessar/lib/goodkill.h
 *            with /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

public void
create_monster() 
{
  set_living_name("isildil");
  set_name("Isildil");
  add_name(({"shopkeeper","ranger","shopranger","isildil"}));
  set_race_name("human");
  set_adj(({"stocky","dark-haired"}));
  set_long("This is Isildil, the Ranger who takes care of the Equipment store.\n"+
    "He is probably quite competent with numbers - trade is his speciality.\n");
  default_config_npc(64);
  set_base_stat(SS_CON,95);
  set_base_stat(SS_STR,95);
  set_skill(SS_WEP_SWORD, random(10)+90);
  set_skill(SS_DEFENCE, random(10)+90);
  set_skill(SS_PARRY, random(10)+90);
  set_alignment(800+random(200));
  set_chat_time(12);
  add_chat("Can I help you?");
  add_chat("This is the Rangers equipment store.");
  add_chat("I am Isildil, son of Anordil, Ranger of Ithilien.");
  add_chat("Have you got anything nice to sell?");
  add_chat("Perhaps you want to buy some nice equipment?");
  add_cchat("Get out of here, you thieving scoundrel!");
  add_cchat("You won't get away with this, you know!");
  add_cchat("Guards! Help!");
}

public void
arm_me()
{
    FIX_EUID

    clone_object(WEP_DIR + "r_brsword")->move(TO);
    clone_object(ARM_DIR + "studlarm")->move(TO);
    command("wield all");
    command("wear all");
}

/* solemnian prestige */
public int query_knight_prestige() {return -10;}

void
do_introduce(object pl, string name)
{
    if (!present(pl, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("say Pleased to meet you, "+CAP(name)+".");
    command("introduce me to "+name);
    command("say What can I do for you?");
}

public void
add_introduced(string who)
{
    object  pl;

    if (!objectp(pl = find_player(who)) ||
        pl->query_met(query_real_name()))
        return;
    set_alarm(5.0, 0.0, &do_introduce(pl, who));
}

