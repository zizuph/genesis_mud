#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("untunomourn");
    set_title("Stoneshield, Clan Trader");
    set_introduce(1);
    add_name("trader");
    set_adj("grey-bearded");
    add_adj("gnarled");
    set_short("grey-bearded cunning dwarf");
    set_race_name("dwarf");
    set_long("The rotund grey-bearded dwarf is the local " +
      "dwarven trader for Iron Delving. He gathers together " +
      "weapons the clan does not use, and trades them for axes to " +
      "outsiders.\n");

    set_stats(({140, 30, 90, 40, 40, 50}));
    set_hp(10000);

    set_alignment(100);
    set_knight_prestige(-1);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_AXE, 40);

    set_act_time(30);
    add_act("emote smiles wealthfully.");
    add_act("grin dwarv");
    add_act("say I'll trade weapons for axes!");
    add_ask(({"drop","drop all","drop equipment",
	"drop stuff"}),VBFC_ME("drop_stuff"));

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

}

string
drop_stuff()
{
    command("drop all");
    return "";
}

void
arm_me()
{
    seteuid(getuid(TO));
    command("wield all");
}

void
put_in_rack(object ob, object from)
{
    string what;

    what = L(ob->query_name());
    command("put " +what+ " in rack");
}

void
put_in_chest(object ob, object from)
{
    string what;

    what = L(ob->query_name());
    command("open chest");
    command("put " +what+ " in chest");
}

void
put_in_cabinet(object ob, object from)
{
    string what;

    what = L(ob->query_name());

    command("open cabinet");
    command("put " +what+ " in cabinet");
    command("eat all");
    command("drink all");
}

void
drop_living(object ob, object from)
{
    string what;

    what = L(ob->query_short());
    command("say Hmm, dunno what to do with " +
      "this thing.");
    command("drop " +what);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->query_wt())
    {
	set_alarm(1.0, 0.0, &put_in_rack(ob, from));
	return;
    }

    if(ob->query_at())
    {
	set_alarm(1.0, 0.0, &put_in_chest(ob, from));
	return;
    }

    if(living(ob))
    {
	set_alarm(1.0, 0.0, &drop_living(ob, from));
	return;
    }

    set_alarm(1.0, 0.0, &put_in_cabinet(ob, from));

    return;
}

