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

    set_name("vryl");
    set_title("Bloodstone, Young Clanmember");
    set_introduce(1);
    add_name("sorter");
    set_adj("young");
    add_adj("beardless");
    set_short("young beardless dwarf");
    set_race_name("dwarf");
    set_long("This young beardless dwarf is being " +
      "prepared for a life as a warrior of the clan, " +
      "being given the responsibility of sorting out the " +
      "warriors equipment and keeping the storeroom " +
      "clean.\n");

    set_stats(({140, 30, 90, 40, 40, 50}));
    set_hp(10000);

    set_alignment(100);
    set_knight_prestige(-1);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_AXE, 40);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(30);
    add_act("emote polishes the wooden cabinet.");
    add_act("emote examines the weapons on the " +
      "weapon rack carefully.");
    add_act("say One day, I'll slay me a giant!");
    add_act("smile dwarvish");

    set_default_answer("The dwarf is busy sorting " +
      "out the storeroom. If you want, you can give " +
      "him your equipment, and he'll put them in their " +
      "proper spot.\n");
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

