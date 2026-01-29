/*
 * Cloned by ~Shire/common/bree/inn
 */
#include "/d/Shire/common/defs.h"

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

//    Prototypes
void return_introduce(string who);

void
create_monster()
{
    set_race_name("hobbit");
    default_config_npc(20);
    set_monster_home("/d/Shire/common/bree/inn");
    set_restrain_path("/d/Shire/common/bree/");
    set_random_move(1);

   set_act_time(3);
   add_act("bow");
   add_act("emote hustles quickly around, neatening up.");
   add_act("smile tir");
   add_act("emote fumbles with a tray.");
}

add_introduced(string who)
{
    object ob;

    if (!who)
	return 0;

    who = lower_case(who);
    ob = present(who, environment());

    if (!ob)
	return 0;

    if (!notmet_me(ob))
	return 0;

    if (!random(20))
	return 0;

    set_alarm(itof(random(10)),0.0,&return_introduce(who));
    return 1;
}

void
return_introduce(string who)
{
    if (random(4) && present(who, environment()))
	command("introduce myself to " + who);
    else
	command("introduce myself");
}

monster_is_bob()
{
    set_name("bob");
    set_living_name("bob");
    set_adj(({"small", "plump", "hairy"}));
    set_long("@@our_long");
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 50000);

/* He's plump, so I guess he tries to enjoy himself. Give him 2 tobaccos */
}

monster_is_nob()
{
    set_name("nob");
    set_living_name("nob");
    set_adj(({"large", "slim", "bold"}));
    set_long("@@our_long");
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 70000);
}

our_long()
{
    string str;

    str = "He looks quite strange for a hobbit.\n";
    if (notmet_me(this_player()))
	return str;
    return "He is one of Barliman Butterbur's servants.\n" + str;
}
