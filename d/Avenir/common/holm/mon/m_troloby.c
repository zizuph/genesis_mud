//              ~Avenir/common/holm/mon/m_troloby.c taken from:
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
#include <ss_types.h>
#include <wa_types.h>
#include "../holm.h"

#define STRRM      "/d/Avenir/common/holm/jungle/m_store.c"
#define TROBY      HOLM_MON + "m_troloby"
#define MERCHANT   HOLM_MON + "merchant"
#define MAX_STORE 40
#define SELL_PERIOD 1000.0
#define PONY_ABSENCE 120.0

object store, merchant;

void create_creature()
{
    if (!IS_CLONE )
        return;
  
    set_name("ymrmph");
    add_name(({"pony", "troloby"}));
    set_short("towering troloby");
    set_adj("towering");
    set_long("A huge troloby, half again as tall as the tallest of "+
        "elves, and thrice as wide. He towers over his gnomish "+
        "master, who holds a flimsy leash attached to a collar "+
        "that circles this fellow's neck. There is an exception"+
        "ally large pack on his back.\n");
    set_race_name("troloby");

    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_stats (({ 180, 80, 120, 90, 50, 100 }));
    set_skill(SS_DEFENCE, 50);
    set_skill (SS_UNARM_COMBAT, 70);
    set_attack_unarmed ( 0, 20, 20, W_IMPALE,   30, "teeth");
    set_attack_unarmed ( 2, 30, 30, W_BLUDGEON, 35, "hoof");
    set_attack_unarmed ( 4, 20, 20, W_BLUDGEON, 35, "fist");
    set_hitloc_unarmed ( 0,  10, 20, "head"  );
    set_hitloc_unarmed ( 2,  20, 60, "body"  );
    set_hitloc_unarmed ( 4,  10, 20, "legs"  );
  
    call_other(STRRM, "???");
    store = find_object(STRRM);
    set_alarm(SELL_PERIOD, SELL_PERIOD, "empty_store");
    set_alarm(0.1, 0.0, &set_m_in("arrives at a trot"));
    set_alarm(0.1, 0.0, &set_m_out("trots"));
}
     
private void empty_store()
{
    object *inv = all_inventory(store);
  
    if(sizeof(inv) > 0 && !query_attack() && !query_no_show())
    {
        set_alarm(PONY_ABSENCE, 0.0, "return_pony");
        tell_room(ENV(TO), QCTNAME(merchant)+" whispers something to "+
           QTNAME(TO)+".\n" +QCTNAME(TO)+" disappears into the "+
           "greenery at a trot.\n");
        call_other(FILTER_DEAD(inv), "remove_object");
        set_no_show();
    }
}    

private void return_pony()
{
    unset_no_show();
    set_no_show_composite(0);
    tell_room(ENV(TO), QCTNAME(TO) +" arrives trotting briskly.\n");
}

public void set_merchant(object mer) 
{ 
    merchant = mer; 
}
     
void do_die(object killer )
{
    tell_room(ENV(TO), "In a final, desperate act, "+ QTNAME(TO)+ 
        " tosses its pack into the bushes and then falls dead "+
        "at your feet!\n");
    merchant->pony_died();
    call_other(all_inventory(store), "remove_object");
    ::do_die(killer);
}

private void run_away()
{
    command("smile joy");
    tell_room(ENV(TO), QTNAME(TO) +" senses his freedom and trots "+
        "off into the green darkness of the foliage.\n");
    merchant->pony_died(); // do the same as if pony were dead.
    call_other (FILTER_DEAD(all_inventory(store)), "remove_object");
    remove_object();
}
