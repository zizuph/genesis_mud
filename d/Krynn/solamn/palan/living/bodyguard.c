/* created by Aridor, 09/14/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "sweater")->move(TO);
    clone_object(OBJ + "leggings")->move(TO);
    clone_object(OBJ + "boots")->move(TO);
    command("wear all");
    MONEY_MAKE_CC(random(5))->move(TO);
}

void
create_citizen()
{
    set_name("giorge");
    add_name("guard");
    add_name("bodyguard");
    set_race_name("human");
    set_introduce(", Bodyguard to Lady Malynda of the noble House of " +
		  "Branchala");
    set_gender(0);

    set_adj("strong");
    add_adj("fierce");
    set_long("@@my_long@@He is a bodyguard and you are sure he is good at " +
	     "it, too.\n");
    default_config_npc(random(10) + 110);
    add_prop("_live_m_attack_thief",1);
}

void
attacked_by(object ob)
{
    ::::attacked_by(ob);
      /* do this to avoid calling the city guard */
}
