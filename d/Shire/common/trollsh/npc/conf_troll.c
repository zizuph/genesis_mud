#include "/d/Shire/common/defs.h"
inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"

object troll;

create_monster()
{
    seteuid(getuid());
       if(!IS_CLONE)
           return;
           
    set_name("wandering");
    set_race_name("troll");
    set_adj("sad");
    add_adj("confused");
    add_name("troll");
    set_long(
            "This troll looks like it is totally lost. It has no idea of where "
           +"to go, and can not seem to find his friends. He is quite small, only "
           +"about 7 feet, and has an ugly, disgusting face. Maybe that is why he "
           +"is left all alone out here... However, he looks strong and sturdy and "
           +"has thick arms. Might not be a good idea to start a fight with him.\n");
           
    set_alignment(-200 - random(100));
    
    add_prop(CONT_I_WEIGHT, 200*1000);
    add_prop(CONT_I_HEIGHT, 320);
    add_prop(LIVE_I_SEE_DARK, 2);
    set_appearance(100);
    set_scar(2300 + random(200));
    
    set_stats(({124,50,90,40,90,70}));
    
    set_act_time(2);
    add_act("emote sniffs unhappily.");
    add_act("giggle insa");
    add_act("sob");
    add_act("cry");
    add_act("confused");
    add_act("laugh all");
    
    set_cact_time(1);
    add_cact("cackle sad");
    add_cact("say Mefinks me likes YOU for dinnah today!");
    add_cact("fart");
    add_cact(({"say AAAAAAAAAAARGHH!!! Me hates sun!!","Sun gives me PAIN","scream"}));
    add_cact("snore");
    add_cact("say Me hates your guts, but makes good food!");
    add_cact(({"emote lifts you up with his huge arms!!","laugh all","emote drops you again!"}));
    add_cact("spit");
    
    set_skill(SS_WEP_SWORD, 50);    
    set_skill(SS_WEP_CLUB, 60);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 30);
    set_skill(SS_BLIND_COMBAT, 30);
    set_skill(SS_AWARENESS, 50);
    MAKE_MONEY;
    set_aggressive(1);
    set_attack_chance(50);
    set_pick_up(100);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alarm(2.0,0.0,"arm_me");

    troll->set_restrain_path(({"rivend3","rivend4","rivend2","rivend5"}));
    set_random_move(4);
    set_monster_home("/d/Shire/common/trollsh/rivend2");

}

arm_me()
{
    clone_object(TROLLSH_DIR + "weapon/lost_sword")->move(TO);
    clone_object(TROLLSH_DIR + "arm/rudeplate")->move(TO);
    command("wear all");
    command("wield all");    
}    
    
int
query_knight_prestige()
{
    return 200;
}
