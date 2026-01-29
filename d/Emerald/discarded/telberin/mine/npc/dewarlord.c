 
/* mine/npc/dewarlord.c is cloned by mine/corridor9.c */
 
inherit "/std/monster";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
#include "/d/Emerald/lib/make_money.h"

void arm_me();

void
create_monster()
{
    set_name("lord");
    add_name("dewar");
    set_adj("small");
    add_adj("dewar");
    set_race_name("dwarf");
    set_short("small dewar lord");
    set_long("This is a member of the exiled dwarven clan. "+
             "In their lust for metals of any type, they became perverted "+
             "by lust and greed. They are savage fighters but many are "+
             "mad. This one looks like a noble amongst them.\n");
     
    set_base_stat(SS_STR, 100);
    set_base_stat(SS_DEX, 75);
    set_base_stat(SS_CON, 80);
    set_base_stat(SS_INT, 45);
    set_base_stat(SS_WIS, 46);
    set_base_stat(SS_DIS, 80);

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 75);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_FORM_DIVINATION, 25);
    set_skill(SS_ELEMENT_LIFE, 40);
    set_skill(SS_AWARENESS, 45);
        set_aggressive(1);
 
    set_all_hitloc_unarmed(25);  /* Inherent AC of 25 without equip */
 
    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(LIVE_I_SEE_DARK, 1);
 
    set_chat_time(10);                             /* Set speaking interval */
    add_chat("Who do you think you are?"); /* A bit of random chat */
    add_chat("Kill all foreigners to our mines!");
    add_chat("Leave before i kill you!");
 
    set_cchat_time(4);                      /* Set combat speaking interval */
    add_cchat("You puny fool!");            /* The usual combat talk */
    add_cchat("Is that the best you can do?");
 
    set_act_time(10);                    /* Set action interval           */
    add_act("grin madly");              /* A few courteous actions       */
    add_act("swear");
 
 
    set_alarm(1.0, 0.0, arm_me);
}
 
void
arm_me()
{
    object eq;
 
    eq = clone_object( MINE_DIR + "wep/nblade");
    if (eq)
        eq->move(this_object());
    eq = clone_object( MINE_DIR + "arm/plate");
    if (eq)
        eq->move(this_object());
    command("wield all");
    command("wear all");
    MAKE_MONEY;
}
