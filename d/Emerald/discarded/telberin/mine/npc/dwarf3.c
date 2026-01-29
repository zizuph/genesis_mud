 
/* mine/npc/dwarf3.c is cloned by mine/chasm10.c */
 
inherit "/std/monster";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
 
void
create_monster()
{
    set_name("dewar");
    set_adj("estranged");
    set_race_name("dwarf");
    set_short("estranged dewar");
    set_long( "This is a member of the exiled dwarven clan. "+
                "In their lust for metals of any type, they became perverted "+
                "by lust and greed. They are savage fighters but many are "+
                "mad.\n" );
 
    set_base_stat(SS_STR, 40);
    set_base_stat(SS_DEX, 26);
    set_base_stat(SS_CON, 35);
    set_base_stat(SS_INT, 13);
    set_base_stat(SS_WIS, 10);
    set_base_stat(SS_DIS, 20);
 
  set_skill(SS_WEP_POLEARM,40);
    set_skill(SS_DEFENCE, 31);
    set_skill(SS_PARRY, 30);
    set_skill(SS_FORM_DIVINATION, 25);
    set_skill(SS_ELEMENT_LIFE, 40);
    set_skill(SS_APPR_MON, 70);
    set_skill(SS_AWARENESS, 45);
 
    set_hp(600);
 
    add_prop(OBJ_I_WEIGHT, 19000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(LIVE_I_SEE_DARK, 1);
 
    set_chat_time(10);                             /* Set speaking interval */
    add_chat("Do you wear metal? Do you?"); /* A bit of random chat */
 
    set_cchat_time(4);                      /* Set combat speaking interval */
    add_cchat("You shall die for that stupidity!");            /* The usual combat talk */
    add_cchat("Don't even try it!");
 
    set_act_time(10);                    /* Set action interval           */
    add_act("grin evilly");              /* A few courteous actions       */
    add_act("growl");
 
 
    set_alarm( 1.0,0.0,"arm_me");
}
 
void
arm_me()
{
    object eq;
 
    eq = clone_object(MINE_DIR + "wep/halb");
    if (eq)
        eq->move(this_object());
    eq = clone_object(MINE_DIR + "arm/chain");
    if (eq)
        eq->move(this_object());
    command("wield all");
    command("wear all");
    MAKE_MONEY;
}
