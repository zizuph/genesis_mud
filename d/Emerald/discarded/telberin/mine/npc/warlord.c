 
/* mine/npc/warlord.c is cloned by mine/maze6.c */
 
inherit "/std/monster";
 
#include "/sys/stdproperties.h"
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
#include "/d/Emerald/lib/make_money.h"
 
string *directions = ({"east","north","up",});
 
int added = 0;
 
void
create_monster()
{
    set_name("warlord");
    add_name("dewar");
    set_adj("dewar");
    set_race_name("dwarf");
    set_short("dewar warlord");
    set_long( "This mighty dewar is kitted out for battle "+
                "in a big way, and looks very used to it as well.\n");
 
    set_base_stat(SS_STR, 110);
    set_base_stat(SS_DEX, 82);
    set_base_stat(SS_CON, 123);
    set_base_stat(SS_INT, 85);  /* changed from 45 by SN because */
                                /* sometimes warlord didn't wield axe */
    set_base_stat(SS_WIS, 46);
    set_base_stat(SS_DIS, 80);
 
    set_skill(SS_WEP_AXE, 100);
  set_skill(SS_BLIND_COMBAT,70);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_PARRY, 98);
  set_skill(SS_SPELLCRAFT,80);
  set_skill(SS_ELEMENT_AIR,50);
 
  set_alignment(-150-random(51));
    set_all_hitloc_unarmed(50); /* Inherent AC of 50 */
 
    MAKE_MONEY;
    add_prop(OBJ_I_WEIGHT, 19000);
  add_prop(LIVE_I_SEE_DARK,2);
 
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(CONT_I_MAX_VOLUME, 100000);
 
    set_chat_time(10);              /* Set speaking interval */
    add_chat("Get out of these mines! They belong to us.");
 
    set_cchat_time(4);       /* Set combat speaking interval */
    add_cchat("You pathetic fool! Think you can beat me?");
    add_cchat("Get out of here before I get angry!");
 
    set_act_time(10);     /* Set action interval           */
    add_act("grin");
    add_act("growl");
}
 
void
arm_me()
{
    object eq;
 
    eq = clone_object(MINE_DIR + "wep/r_axe");
    if (eq)
        eq->move(this_object());
    eq = clone_object(MINE_DIR + "arm/adam_gre");
    if (eq)
        eq->move(this_object());
    eq = clone_object(MINE_DIR + "arm/adam_sc");
    if (eq)
        eq->move(this_object());
    eq = clone_object(MINE_DIR + "arm/adam_hel");
    if (eq)
        eq->move(this_object());
    eq = clone_object(MINE_DIR + "arm/adam_bra");
    if(eq)
        eq->move(this_object());
    command("wield all");
    command("wear all");
}
 
void
attacked_by(object ob)
{
  set_alarm(30.0, 0.0, "do_start", TO );
}
 
void
do_commands( object wl )
{
  if(added < sizeof(directions))
  {
    wl->command(directions[added]);
    added++;
  }
 
  set_alarm(10.0, 0.0, "do_commands",wl);
}
 
 
void
get_assist(object wl)
{
  object chaoslord;
 
  chaoslord = present("chaoslord", ENV(wl));
 
  if(chaoslord)
  { chaoslord->command("assist warlord");
    chaoslord->command("assist warlord");
  }
}
 
 
void do_start(object who)
{
  command("hmm");
  command("say This is bad, I better go warn the Chaos Lord!");
  set_alarm(1.0,0.0,"do_commands",who);
  set_alarm(50.0,0.0,"get_assist",who);
}
