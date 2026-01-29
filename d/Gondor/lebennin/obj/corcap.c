/*
 * /d/Gondor/lebennin/obj/corcap.c
 *
 *
 * Revision history:
 * Update code - 05/06/96 - Boron
 */
inherit "/std/monster";
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

/* standard corsair for use in Genesis: Xeros of GondorMud 26 Nov 1993 */

alignlook() {
    string *alignlooks;
    alignlooks=({"dirty","wrinkled","jovial","melancholy","evil","angry","dour",
        "haughty","weathered","furtive","animated","energetic","young","ancient",
        "middled-aged","flabby","small","stout","large","thin","barrel-chested",
        "massive","big","tiny","light","squinty-eyed","swarthy","olive-skinned",
        "brown-skinned","black-eyed","one-eyed","dark-eyed","grey-eyed",
        "pug-nosed","red-nosed","hook-nosed"});
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
    command("wield all");
    command("say Ha! No more mr nice guy, this time I'm usin me weapons");
    command("wear all");
    command("say Argh! Caught wit me pants down again");
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
 
query_knight_prestige() { return 500+random(250); }

create_monster() { 
    if(!IS_CLONE)
        return;
    set_name("corsair");
    set_pname("corsairs");
    set_pshort("men");
    set_race_name("man");
    set_adj(alignlook());
    add_adj(alignlook());
    set_long(BSN("A filthy, muscular corsair, raider of the sea-lanes."));
    default_config_npc(65+random(15));
    set_hp(query_max_hp());
    set_skill(SS_WEP_SWORD,55+random(35));
    set_skill(SS_WEP_CLUB,55+random(29));
    set_skill(SS_DEFENCE,60+random(35));
    set_skill(SS_PARRY,40+random(28));
    set_skill(SS_2H_COMBAT,30+random(15));
    set_skill(SS_BLIND_COMBAT,15+random(10));
    set_skill(SS_UNARM_COMBAT,15+random(20));
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_HEIGHT,185+random(15));
    add_prop(CONT_I_WEIGHT,70000+random(4000));
    add_prop(CONT_I_VOLUME,1200);
    set_chat_time(25+random(25));
    add_chat("Aye me hearties, I can't wait ta be gettin home ta a good meal.");
    add_chat("What's this? Stow-aways? Ta the plank wit ya!");
    set_cchat_time(5+random(14));
    add_cchat("Shiver me timbers, I bets you be tryin ta kill me!");
    add_cchat("Aye bucko, keep this up and you'll be pissin me off you will!");
    add_cchat("Damnit Cap'n, I'm given it all she's got already!");
    set_act_time(15+random(10));
    add_act("fart");
    add_act("stretch");
    add_act("get coins");
    add_act("cackle mad");

    set_alarm(1.0, 0.0, get_money);
    seq_new("do_things");
    seq_addfirst("do_things","@@arm_me");
}

