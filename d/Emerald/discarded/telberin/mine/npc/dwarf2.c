 
/* mine/npc/dwarf2.c is cloned by mine/mine3.c */
 
inherit "/std/monster";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
 
void
create_monster()
{
    set_name("dewar");
    set_adj("small");
    set_race_name("dwarf");
    set_short("small dewar");
    set_long( "This is a member of the exiled dwarven clan. "+
                "In their lust for metals of any type, they became perverted "+
                "by lust and greed. They are savage fighters but many are "+
                "mad.\n" );
 
    set_base_stat(SS_STR, 20);
    set_base_stat(SS_DEX, 13);
    set_base_stat(SS_CON, 15);
    set_base_stat(SS_INT, 9);
    set_base_stat(SS_WIS, 8);
    set_base_stat(SS_DIS, 14);
 
    set_skill(SS_DEFENCE, 10);
    set_skill(SS_PARRY, 10);
    set_skill(SS_WEP_AXE, 15);
    set_skill(SS_FORM_DIVINATION, 25);
    set_skill(SS_ELEMENT_LIFE, 40);
    set_skill(SS_APPR_MON, 70);
    set_skill(SS_AWARENESS, 45);
 
    set_hp(250);
 
    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(LIVE_I_SEE_DARK, 1);
 
    set_chat_time(10);                             /* Set speaking interval */
    add_chat("Does it wear metal?"); /* A bit of random chat */
    add_chat("I can smell something strange around here!");
 
    set_cchat_time(4);                      /* Set combat speaking interval */
    add_cchat("Get it, and kill it!");            /* The usual combat talk */
    add_cchat("Get out of these mines! They're ours!");
 
    set_act_time(10);                    /* Set action interval           */
    add_act("grin evilly");              /* A few courteous actions       */
    add_act("cackle");
 
 
    set_alarm( 1.0,0.0,"arm_me");
}
 
void
arm_me()
{
    object eq;
 
    eq = clone_object(MINE_DIR + "wep/axe");
    if (eq)
        eq->move(this_object());
    eq = clone_object(MINE_DIR + "arm/scale");
    if (eq)
        eq->move(this_object());
    command("wield all");
    command("wear all");
    MAKE_MONEY;
}
