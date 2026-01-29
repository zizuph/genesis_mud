inherit "/std/monster";
inherit "/std/act/action";

#include </d/Roke/common/defs.h>
#include <ss_types.h>
#include "/sys/wa_types.h"
#include <macros.h>
#include "/d/Roke/Cirath/defs.h"

int has_introduced=0;

void
create_monster ()
{
  set_name("gorgat");
  add_name("guard");
  set_race_name("human");
  set_gender(0);

  add_adj("muscular");
  add_adj("big");
  set_short("big muscular human");
  set_long("This human guards the bridge. He won't let anybody pass.\n");

  call_out("arm_me",1);

  set_stats(({ 75, 110, 110, 50, 50, 100}));
  set_skill(SS_WEP_CLUB, 80);
  set_skill(SS_BLIND_COMBAT, 50);
  set_skill(SS_DEFENCE, 75);
  set_skill(SS_PARRY, 70);

  set_alignment(100);

  set_all_hitloc_unarmed(50); 

  set_act_time(5);
  add_act("emote snortles loudly,");

  set_cchat_time(6);
  add_cchat("Ha-HA!! I love fighting.");
  trig_new("%w 'introduces' %s", "react_introduce");
}

query_knight_prestige(){return -100;}

void
arm_me()
{
  seteuid(getuid(TO));
  clone_object(ARM+"guardhelm")->move(TO);
  clone_object(ARM+"guardmail")->move(TO);
  clone_object(WEP+"guardclub")->move(TO);

  command("wear all");
  command("wield all");
}

void
react_introduce()
{
  if (!has_introduced)
  {
    call_out("introduce_me", 4);
    has_introduced=1;
    call_out("remove_int",15);
  }
}

void
introduce_me()
{
  command("introduce myself");
}

void
remove_int()
{
  has_introduced=0;
}

string
query_title()
{
  return "Guardian of the Bridge";
}
