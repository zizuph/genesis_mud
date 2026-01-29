/*
   Catchable rat used in Rhun, Rhovanion created by Milan, Oct. 1995.
   Based on:
   A minor rat. Used in human starting location.
   Styles, 920317.
*/

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/attack";      /* aggressive attacks     */
inherit "/std/act/domove";      /* random move and follow */

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include "/d/Rhovanion/defs.h"

#define TMP_CATCH_RAT "_tmp_catch_rat"
#define HOW_MANY_RATS "_how_many_rats"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

void create_creature()
{
    set_name("rat");
    set_pname("rats");
    set_race_name("rat");
    set_adj(({"black","dirty"}));
    set_short("black dirty rat");
    set_pshort("black dirty rats");

    set_long("This is a black dirty rat with a long tail.\n");

    set_gender(G_NEUTER);
    set_random_move(40);
    set_stats(({ 2, 4, 3, 1, 6, 20})); /* str, dex, con, int, wis, dis */
    set_alignment(-11);

    set_skill(SS_SWIM, 95);

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 1500);

    add_prop(LIVE_I_SEE_DARK,4);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_NO_GET, "You have to catch the rat.\n");
    add_prop("_is_rhun_rat", 1);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   8, 10, W_IMPALE, 80, "jaws");
    set_attack_unarmed(A_LCLAW, 15,  6, W_SLASH,  10, "left paw");
    set_attack_unarmed(A_RCLAW, 15,  6, W_SLASH,  10, "right paw");

    /* Hit_loc,   *Ac (im/sl/bl/ma),   %hit,   hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 10, 14,  6,   5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  5,  8, 16,   0 }), 80, "body");

    set_whimpy(40);
}

int query_knight_prestige(){return 1;}

void init_living()
{
  ::init_living();
  add_action("catch_rat", "catch");
}

void
remove_tmp_prop(object tp)
{
  tp->remove_prop(TMP_CATCH_RAT);
}

int catch_access(object ob)
{
  if((!living(ob)) || (ob->query_ghost()) || (ob == TP) ||
     (!ob->check_seen(TP)) || (ENV(ob) != ENV(TP)))
    return 0;
  return 1;
}

int catch_rat(string arg)
{
  object *target;

  if(TP->query_prop(TMP_CATCH_RAT)) return 0;
  TP->add_prop(TMP_CATCH_RAT, 1);
  set_alarm(0.5, 0.0, "remove_tmp_prop", TP);

  target = CMDPARSE_ONE_ITEM(arg, "catch_access", "catch_access");
  if(sizeof(target) > 1)
  {
    NF("Be specific, you can't "+query_verb()+" "+COMPOSITE_LIVE(target)+
       " at the same time.\n");
    return 0;
  }
  else if(!sizeof(target))
  {
    NF("You find no such living creature.\n");
    return 0;
  }
  NF(target[0]->query_The_name(TP)+" can't be caught.\n");
  return target[0]->do_catch_rat();
}

int
do_catch_rat()
{
  int a,i,j,k;
  string *exits = ENV(TO)->query_exit_cmds();

  i = TP->query_stat(SS_DEX) / 10;
  a = TP->query_skill(SS_ANI_HANDL);
  j = TP->query_prop("_know_catch_rat");
  k = TP->query_stat(SS_WIS) / 10;
  i = random(i+j+a);

  if(i<10)
  {
    write("You move closer to the "+short()+".\n"+
          "The rat notices your approach and moves away.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" moves closer to the "+short()+".\n"+
          "The rat notices "+HIS(TP)+" approach and moves away.\n", TP);
    TP->add_prop("_know_catch_rat", k+j+1);
  }
  else if(i<20)
  {
    write("You jump after the "+short()+
          " and land emptyhanded on the floor.\n"+
          "The rat easily escaped from your range.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" jumps after the "+short()+
          " and lands emptyhanded on the floor.\n"+
          "The rat easily escaped from "+HIS(TP)+" range.\n", TP);
    TP->add_prop("_know_catch_rat", k+j+1);
  }
  else if(i<30)
  {
    write("You quickly jump after the "+short()+
          " but it slips between your hands.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" jumps after the "+short()+
          " but it slips between "+HIS(TP)+" hands.\n", TP);
    TP->add_prop("_know_catch_rat", k+j+1);
  }
  else
  {
    write("You quickly jump after the "+short()+
          " and firmly grab its tail.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" quickly jumps after the "+short()+
          " and firmly grabs its tail.\n", TP);
    TP->add_prop("_know_catch_rat", j-k);
  }

  if(i<30)
  {
    if(sizeof(exits)) TO->command(ONE_OF_LIST(exits));
    if((!a) && (!random(3)))
    {
      TP->set_skill(SS_ANI_HANDL, 1);
      write("You have learned a little how to handle animals.\n");
    }
    return 1;
  }
  TO->remove_prop(OBJ_M_NO_GET);
  if((!random(5)) || TO->move(TP))
  {
    TO->add_prop(OBJ_M_NO_GET, "You have to catch the rat.\n");
    write("The "+short()+" bites your finger causing you to drop it.\n");
    tell_room(ENV(TP), "The "+short()+" bites "+QTNAME(TP)+
                       "'s finger causing "+HIM(TP)+" to drop it.\n", TP);
  }
  i = TP->query_prop(HOW_MANY_RATS) + 1;
  TP->add_prop(HOW_MANY_RATS, i);
  if(i==1)      { j = 7; }
  else if(i<5)  { j = (2 * i) + 6; }
  else if(i<8)  { j = i + 10; }
  else if(i<14) { j = ((i + 1) / 2) + 13; }
  else if(i<20) { j = ((i + 2) / 3) + 15; }
  else if(i<24) { j = ((i + 1) / 4) + 17; } 

  if(a < j)
  {
    TP->set_skill(SS_ANI_HANDL, j);
    write("You have learned a bit more how to handle animals.\n");
  }
  return 1;
}

void enter_env(object dest, object old)
{
  ::enter_env(dest, old);
  if(living(old) && (dest == ENV(old)))
    TO->add_prop(OBJ_M_NO_GET,
                 "The rat runs away as you try to catch it.\n");
}

