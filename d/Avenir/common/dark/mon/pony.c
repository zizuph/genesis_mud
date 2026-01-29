// file name:   ~Avenir/common/dark/mon/pony.c
// creator(s):   Boriska
// last update:  Jan 18, 1995
//               Cirion 051396 - Fixed some typos
// purpose:      Merchant's pet from Avenir's tunnels, works 
//               together with him.
// bug(s):
// to-do:     

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <filter_funs.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/merchant.h"

object store, merchant;

void create_creature()
{
  if( !IS_CLONE )
    return;
  
  set_name("hiccu");
  set_short("cute pony");
  set_short("pony");
  set_adj("cute");
  set_long("This cute pony is working hard carrying loads of goods " +
	   "for his master.\n");
  set_race_name("pony");

  set_stats (({ 80, 80, 100, 80, 80, 80 }));

  set_skill(SS_DEFENCE, 50);
  set_skill (SS_UNARM_COMBAT, 70);

  add_prop(LIVE_I_SEE_DARK, 1);
  add_prop(LIVE_I_NEVERKNOWN, 1);
  add_prop(OBJ_I_WEIGHT, 90718);
  add_prop(OBJ_I_VOLUME, 378500);

  set_attack_unarmed ( 0, 20, 20, W_IMPALE,   30, "teeth");
  set_attack_unarmed ( 2, 30, 30, W_BLUDGEON, 35, "hoove");
  set_attack_unarmed ( 4, 20, 20, W_BLUDGEON, 35, "leg");

  set_hitloc_unarmed ( 0,  10, 20, "head"  );
  set_hitloc_unarmed ( 2,  20, 60, "body"  );
  set_hitloc_unarmed ( 4,  10, 20, "legs"  );

  add_prop(NPC_I_NO_RUN_AWAY, 1);
  set_whimpy(40);
  
  call_other(STORE, "???");
  store = find_object(STORE);
  set_alarm(SELL_PERIOD, SELL_PERIOD, "empty_store");
  set_alarm(0.1, 0.0, &set_m_in("arrives trotting."));
  set_alarm(0.1, 0.0, &set_m_out("trots"));
}
     
private void empty_store()
{
  object *inv = all_inventory(store);
  
  if(sizeof(inv) > 0 && !query_attack() && !query_no_show())
  {
    set_alarm(PONY_ABSENCE, 0.0, "return_pony");
      tell_room(environment(this_object()), QCTNAME(merchant)+
      " whispers something to "+QTNAME(TO)+".\n"
      +QCTNAME(TO)+" goes trotting along the tunnels.\n");
    call_other(FILTER_DEAD(inv), "remove_object");
    set_no_show();
   }
}    

private void return_pony()
{
  unset_no_show();
  set_no_show_composite(0);
  say(QCTNAME(TO) + " arrives trotting.\n");
}

public void set_merchant(object mer) 
{ 
  merchant = mer; 
}
     
void do_die(object killer )
{
  tell_room(environment(this_object()), "As "+QTNAME(TO)+
      " falls dead, all its packs suddenly disappear!\n");
  merchant->pony_died();
  call_other(all_inventory(store), "remove_object");
  ::do_die(killer);
}

private void run_away()
{
  command("scream");
  tell_room(environment(this_object()), "Exhausted by the "+
     "fight and frightened to death, "+QTNAME(TO)+
     " runs away down the tunnels.\n");
  merchant->pony_died(); // do the same as if pony were dead.
  call_other (FILTER_DEAD(all_inventory(store)), "remove_object");
  remove_object();
}
