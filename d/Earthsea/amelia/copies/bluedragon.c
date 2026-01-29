#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";

#include "/d/Roke/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Cirath/common/quests/guru_axe.h"

mixed attackers;
trme(object tp);
snok(object tp);

default_config_npc(int i)
{
  int j;
  for(j=0;j<6;j++)
    set_base_stat(j,i);
}

notify_been_zapped(object ob)
{
  if(!ob->query_prop("refnas_e_en_riktig_man_banka_gurka_det_kan_han"))
    return;

  set_alarm(3.0, 0.0, &trme(this_player()));
}

trme(object tp)
{
  tell_room(E(TO),"The dragon looks like hot jelly. It obviously has great\n"+
	    "problems keeping it's shape.\n");
  set_alarm(3.0, 0.0, &snok(tp));
}

snok(object tp)
{
  object wiz;

  tell_room(E(TO),"Suddenly the dragon collapses, and transforms into a human.\n");
  seteuid(getuid(this_object()));
  wiz = clone_object(MOUNT+"monster/wizard");
  wiz->move(E(TO));
  wiz->reward(tp);

  remove_object();
}

create_creature()
{
  default_config_npc(150);

  set_name("dragon");
  set_race_name("dragon");
  set_living_name("bobban");

  set_short("black dragon");
  set_adj("black");
  
  set_long("This is the Black Dragon of Gont. Rumors say that it is an evil\n"+
	   "wizard that has been cursed by one of his enemies.\n");

  set_alignment(-1000);

  set_skill(SS_DEFENCE,75);
  set_skill(SS_UNARM_COMBAT,75);
  
  set_attack_unarmed(0,  50, 50, W_IMPALE, 50, "jaws");
  set_attack_unarmed(1, 50, 50, W_BLUDGEON, 50, "heavy tail");
  set_hitloc_unarmed(0, ({ 50 }), 10, "head");
  set_hitloc_unarmed(1, ({ 50 }), 80, "body");
  set_hitloc_unarmed(2, ({ 50 }), 10, "tail");

  set_fatigue(9000);
  set_hp(40000);
}

query_knight_prestige(){return 750;}

attacked_by(ob)
{
    ::attacked_by(ob);

    if (!pointerp(attackers)) attackers = ({});

    if (member_array(ob,attackers) == -1)
	attackers += ({ob});
}

do_die(killer)
{
    object cuir;

    if (query_hp() > 0) return;

    if (sizeof(attackers) <= 1)
	if (cuir = present(CUIR_ID,killer))
	{
	    cuir->report_kill(BLUE_DRAGON);
#ifdef GURUDEBUG
	    killer->catch_msg("Yes, a guru kill!\n");
#endif
	}
    ::do_die(killer);
}
