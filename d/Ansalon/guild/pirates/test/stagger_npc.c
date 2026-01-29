/*
   statistic monster base file by Milan
 */

inherit "/w/milan/stat_npc";

#include <macros.h>
#include <ss_types.h>

void
special_command_enabled(string str)
{
    if (str == "dattack");
    {
	command("slash");
    }
}

void
kill_command()
{
    set_intoxicated(intoxicated_max());
    oponent->set_intoxicated(oponent->intoxicated_max());
    oponent->set_skill(110,90);
    command("kill "+OB_NAME(oponent));
}

void
create_monster()
{
    set_base_stat(6,100);
    set_base_stat(7,100);
    set_base_stat(8,100);
    ::create_monster();
    set_race_name("human");
    set_log_str("Pirates stagger results:\n");
    set_name("pirate");
//    set_adj("BDA");
}

void
arm_me()
{
    object gShadow = clone_object("/d/Ansalon/guild/pirates/shadow/pirate_shadow2");
    if(gShadow->shadow_me(this_object(), "layman", "fighter", "Pirate of the Bloodsea") != 1)
    {
	"secure/master"->do_debug("destroy",gShadow);
    }
    else
    {
	gShadow->set_promotion_level(1);
    }
//    set_skill(143008, 100);
//    add_cmdsoul("/d/Ansalon/guild/dragonarmy/soul/dragonarmy_blue_soul");
//    load_command_souls();
    ::arm_me();
}
