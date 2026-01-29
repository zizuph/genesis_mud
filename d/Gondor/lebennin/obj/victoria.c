/*
 * /d/Gondor/lebennin/obj/victoria.c
 *
 *
 *
 * Revision history:
 * Code update - 05/06/96 - By Boron
 */
inherit "/d/Gondor/lebennin/obj/team.c";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>

void get_money();

void create_monster() {
    set_name("victoria");
    add_name(({"captain","woman","corsair"}));
    set_race_name("human");
    set_adj(({"short","voluptuous"}));
    set_gender(G_FEMALE);
    set_title("the Captain of the Wave-cutter");
    set_long(BSN("Obviously an experienced campaigner, she looks as ruthless "+
        "and deadly as she is beautiful."));
    default_config_npc(140 +random(31));
    set_base_stat(SS_DEX, 160+random(21));
    set_base_stat(SS_CON, 150+random(21));
    set_base_stat(SS_INT, 140+random(41));
    refresh_mobile();
    set_alignment(-500-random(151));
    set_skill(SS_WEP_SWORD,90+random(11));
    set_skill(SS_WEP_KNIFE,80+random(21));
    set_skill(SS_2H_COMBAT,80+random(21));
    set_skill(SS_PARRY,90+random(11));
    set_skill(SS_DEFENCE,85+random(16));
    add_prop(CONT_I_HEIGHT,110);
    add_prop(CONT_I_WEIGHT,50000);
    add_prop(CONT_I_VOLUME,900);
    add_prop(LIVE_I_SEE_DARK,1);
    add_prop(LIVE_I_QUICKNESS,20);

    set_chat_time(10+random(11));
    set_cchat_time(10+random(6));
    set_act_time(10+random(11));
    add_act("laugh sedu");
    add_act("emote studies a chart.");
    add_act("moan sed");
    add_act("emote frowns prettily");

    set_alarm(1.0, 0.0, &get_money());
    seq_new("do_things");
    seq_addfirst("do_things","@@arm_me");
}

make_money(i,type) {
    object money;

    money=clone_object("/std/coins");
    money->set_heap_size(i);
    money->set_coin_type(type);
    money->move(TO,1);
}


void
get_money() {
    make_money(random(46)+15, "silver"); 
    make_money(random(11)+10, "gold");
    make_money(random(3)+2, "platinum");
}

query_knight_prestige() { return 1000; }

arm_me() {
    object wep, arm, roarm;

    seteuid(getuid(TO));

    wep=clone_object(LEB_DIR + "obj/cutlass");
    wep->move(TO);
    wep=clone_object(LEB_DIR + "obj/cutlass");
    wep->move(TO);
    command("wield all");

    arm=clone_object(LEB_DIR + "obj/chainshirt");
    arm->move(TO);
    arm=clone_object(LEB_DIR + "obj/vishelm");
    arm->move(TO);
    arm=clone_object(LEB_DIR + "obj/corpants");
    arm->move(TO);
    command("wear all");
}
