inherit "/std/monster";
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

/* daugher for quest for use in Genesis: Xeros of GondorMud 4 Dec 1993 */

alignlook() {
    string *alignlooks;
    alignlooks=({"alluring","slender","seductive","melancholy","sweet","pretty","bouncy",
        "haughty","voluptuous","auburn-haired","animated","energetic","young","willowy",
        "dark-eyed","lean","petite","light","elfin","thin","exciting",
        "friendly","talkative","tiny","light","leggy","light-skinned","olive-skinned",
        "brown-skinned","black-eyed","white","green-eyed","grey-eyed",
        "sexy","dimpled","provocative"});
    return alignlooks[random(sizeof(alignlooks))];
}
arm_me()
{
    object wep, arm, roarm;
    seteuid(getuid(this_object()));
   
    if (1==random(3)) wep=clone_object(LEB_DIR + "obj/cutlass");
    else {
        wep=clone_object(LEB_DIR + "obj/pin");
        arm=clone_object(LEB_DIR + "obj/corshirt");
        arm->move(TO); }
    wep->move(TO);
    arm=clone_object(LEB_DIR + "obj/corpants");
    arm->move(TO);
    if (1<random(4)) {
        wep=clone_object(LEB_DIR + "obj/cutlass");
        wep->move(TO); }
/*
    command("wield all");
    command("say Ha! No more mr nice guy, this time I'm usin me weapons");
    command("wear all");
    command("say Argh! Caught wit me pants down again");
*/
}

get_money() {       
    make_money(random(100)+50,"copper");
    make_money(random(10)+15,"silver");
    make_money(random(1),"gold");
}
 make_money(i,type) {
    object money;

    money=clone_object("/std/coins");
    money->set_heap_size(i);
    money->set_coin_type(type);
    money->move(TO,1);
}

query_knight_prestige() { return -10; }

create_monster() { 
    if(!IS_CLONE)
        return;
    set_name("veronica");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_adj(alignlook());
    add_adj(alignlook());
    set_long(BSN("A young, fresh face is all that makes this woman memorable."));
    default_config_npc(65+random(15));
    set_hp(query_max_hp());
    set_skill(SS_WEP_KNIFE,55+random(35));
    set_skill(SS_WEP_CLUB,55+random(29));
    set_skill(SS_DEFENCE,80+random(35));
    set_skill(SS_PARRY,70 +random(28));
    set_skill(SS_2H_COMBAT,30+random(15));
    set_skill(SS_BLIND_COMBAT,15+random(10));
    set_skill(SS_UNARM_COMBAT,15+random(20));
    add_prop(CONT_I_HEIGHT,175+random(15));
    add_prop(CONT_I_WEIGHT,60000+random(4000));
    add_prop(CONT_I_VOLUME,1200);
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_chat_time(25+random(25));
    set_cchat_time(5+random(14));
    set_act_time(15+random(10));
    add_act("spank all");
    add_act("stretch erotically");
    add_act("get coins");
    add_act("cackle sed");

    set_alarm(1.0, 0.0, get_money);
    seq_new("do_things");
    seq_addfirst("do_things","@@arm_me");
}

