#pragma strict_types

#include "../xdefs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/filter_funs.h"
#include <ss_types.h>
#include <money.h>
 
inherit "/std/monster";
inherit "/lib/trade";
 
int has_introduced=0;

void
create_monster()
{
    set_name("kroesus");
    set_living_name("kroesus");
    set_race_name("human");

    set_title("The Ultimate Big Shot of The Rich Men's Club");

    set_adj("greedy");
    add_adj("rich");
    set_stats(({ 350, 450, 450, 200, 200, 250 }));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    refresh_mobile();
    has_introduced = 0;
}
 
void
init_living()
{
    add_action("buy", "buy");
} 
 
void
add_introduced(string person)
{
    if (!has_introduced)
    {
	set_alarm(2.0, 0.0, "introduce_me");
	has_introduced=1;
	set_alarm(12.0, 0.0, "remove_int");
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

void
arm_me()
{
    FIXEUID;
    clone_object("/d/Immortal/rclub/richpurse_l")->move(TO);
    clone_object("/d/Immortal/gold/obj/ksword")->move(TO);
    clone_object("/d/Immortal/gold/obj/kplate")->move(TO);

    command("wield all");
    command("wear all");
}

void
logger(object killer)
{
    FIXEUID;
    
    write_file("/d/Immortal/log/kroesus.log", "- "+
	       capitalize(killer->query_real_name()) +
	       " killed me!\t"+extract(ctime(time()),4,15) + "\n");
}

void
do_die(object killer)
{
    if(query_hp()>0)
        return;
    
    logger(killer);

    command("emote screams in agony as he dies!");
    command("emote fetches his bankbook from his money-sack.");
    command("emote shouts: If I can't have it, NO ONE WILL!");
    command("emote throws the bankbook into the sea.");

    ::do_die(killer);
}
