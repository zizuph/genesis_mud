inherit "/d/Gondor/rohan/edoras/npc/edoras_npc";
inherit "/d/Gondor/common/lib/logkill";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void    arm_me();

void
create_child()
{
    set_chat_time(30);
    add_chat("My mommy won't let me have a real sword yet.");
    add_chat("I heard that Harding saw a real true Orc yesterday!");
    add_chat("I bet I could kill an Orc too if I had a sword.");
    add_chat("I can ride horses faster than you can.");
    add_chat("My dad is a Rider of the First Eored.");
    set_act_time(20);
    add_act("emote makes a teasing face at some other kid nearby.");
    add_act("emote runs and skips, kicking a rock.");
    add_act("emote hums an annoying little tune.");
    add_act("emote peers curiously at you.");
    add_act("giggle");
    add_cact("shout Help! Help me! They're trying to get me!");
    add_cact("scream");
    add_cact("shout Daddy!");
}

nomask void
create_edoras_npc()
{
    int     rnd = random(15);

    set_name(({"child", "kid", "rohirrim"}));
    set_race_name("human"); 
    set_short("rohirrim child");
    set_adj(({"young", "rohirrim"}));
    set_long("This is a rohirrim " + (query_gender() ? "girl" : "boy") 
      +", blond-haired, mischievious and full of energy.\n");
    default_config_npc(10 + rnd);
    set_alignment(800);
    set_skill(SS_WEP_KNIFE,5 + rnd);
    set_whimpy(40);
    add_prop(CONT_I_WEIGHT, 20000 + (rnd * 1000));
    add_prop(CONT_I_HEIGHT, 125 + rnd);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    create_child();
}

void
arm_me()
{
    FIX_EUID

    clone_object(EDORAS_DIR + "obj/fknife")->move(TO);
    command("wield knife");
}

/* solemnian prestige */
int     query_knight_prestige() {return (-5);}

