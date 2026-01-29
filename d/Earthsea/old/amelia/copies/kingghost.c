#pragma save_binary

inherit "/d/Roke/common/monster";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/qbits.h"
#include <ss_types.h>
#include "/d/Cirath/common/quests/guru_axe.h"

object axe;
mixed attackers;

create_monster()
{
  default_config_npc(100);

  set_race_name("ghost");
  set_name("ghost");
  add_name("king");

  add_prop(LIVE_I_UNDEAD,75);

  set_short("ghost of dwarf king");

set_long("This is the ghost of the former dwarf king, haunting the mountain\n"+
	 "to protect his treasury.\n");
  set_alignment(30);

  call_out("equip_me",1);

  set_skill(SS_UNARM_COMBAT,25);
  set_skill(SS_DEFENCE,50);
  set_skill(SS_PARRY,75);

  set_skill(SS_WEP_AXE,100);
}
query_knight_prestige(){return -1;}

attacked_by(ob)
{
    ::attacked_by(ob);

    if (!pointerp(attackers)) attackers = ({});

    if (member_array(ob,attackers) == -1)
	attackers += ({ob});
}

do_die(object killer)
{
    object cuir;

    if(query_hp()>0)
	return;

    if (sizeof(attackers) <= 1)
	if (cuir = present(CUIR_ID,killer))
	{
	    cuir->report_kill(GHOST_KING);
#ifdef GURUDEBUG
	    killer->catch_msg("Yes, a guru kill!\n");
#endif
	}

    query_combat_object()->cb_death_occured(killer);

    killer->notify_you_killed_me(this_object());
    axe->add_prop(GHOSTKINGKILLER,killer->query_real_name());
    command("drop all");
    tell_room(E(TO),"The ghost dissolves in a strange mist.\n");
    remove_object();
}

equip_me()
{
  axe = clone_object(CARISCA+"obj/kingaxe");
  axe->add_prop(GHOSTKINGSAXE,1);
  axe->move(TO);
  clone_object(CARISCA+"obj/kingmail")->move(TO);
  clone_object(CARISCA+"obj/kinghelm")->move(TO);
  clone_object(CARISCA+"obj/kinggaunt")->move(TO);

  command("wear all");
  command("wield all");
}
