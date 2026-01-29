//-*-C++-*-
// file name:    /d/Avenir/common/holm/mon/seamonster
// creator(s):   Lilith May 1997
// revised:
// purpose:      A monster for the shore area
// note:         
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Avenir/inherit/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <cmdparse.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../holm.h"
#include "/d/Genesis/gems/gem.h"

// rename hitlocs
#define A_BITE   TS_HEAD 
#define A_LCLAW  TS_LHAND
#define A_RCLAW  TS_RHAND
#define A_RFOOT  TS_RFOOT
#define A_LFOOT  TS_LFOOT
#define H_HEAD   TS_HEAD
#define H_BODY   TS_TORSO
#define H_LFQ    TS_LFOOT
#define H_RHQ    TS_RFOOT

#define MON_PARA HOLM_OBJ +"mon_para"
#define ETO      environment(this_object())

int imon = 0;
int query_imon() {    return imon;    }
void set_imon(int val)  {    imon = val;    }

void create_creature()
{
    set_name("quillist");
    add_name(({"monster", "seamonster", "being", "creature" }));
    set_race_name("seamonster");
    set_adj(({"misshapen", "green"}));
    set_short("seamonster");
    set_long("This is a misshapen, green pile of vines and tendrils, "+
       "with oddly humanoid webbed feet.\n");
   
    set_m_in("slides in.");
    set_m_out("slides");
    set_mm_in("rises from the beneath the surface of the pool.");

             /*  str, con, dex, int, wis, dis  */
    set_stats(({ 100, 110, 200, 75, 75, 100 }));
   
    set_skill(SS_BLIND_COMBAT, 95);
    set_skill(SS_UNARM_COMBAT, 95);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_AWARENESS, 95);
    set_gender(3);
    set_alignment(0);
    set_knight_prestige(500);                                                                                                 
               
    set_cact_time(3);
      add_cact("cry");
      add_cact("scream");
      add_cact("moan"); 
      add_cact("cringe");
      add_cact("tremble");        
      add_cact("emote flails a vine-like tendril in your direction."); 
      add_cact("emote trails a tendril over the surface of the pool.\n"+
          "An image flickers there, then is gone.");
      add_cact("emote rustles a tangle of vine-like appendages.");
      add_cact("emote makes an inarticulate sound.");

    set_attack_unarmed(A_BITE,  35, 35, W_IMPALE,   15, "gaping jaws");
    set_attack_unarmed(A_LCLAW, 20, 25, W_SLASH,    30, "left tendril");
    set_attack_unarmed(A_RCLAW, 20, 25, W_SLASH,    30, "right tendril");
    set_attack_unarmed(A_LFOOT, 50, 60, W_BLUDGEON, 10, "webbed left foot");
    set_attack_unarmed(A_RFOOT, 50, 60, W_BLUDGEON, 10, "webbed right foot");
   
    set_hitloc_unarmed(H_HEAD, ({ 35 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 25 }), 40, "upper-body");
    set_hitloc_unarmed(H_LFQ,  ({ 10 }), 20, "tendril");
    set_hitloc_unarmed(H_RHQ,  ({ 10 }), 20, "vine");
   
    add_prop(LIVE_I_SEE_DARK, 1 + random(10));
    add_prop(OBJ_I_RES_WATER, 40 + (random(35)));
    add_prop(OBJ_I_RES_POISON, 15 + (random(15)));
    add_prop(LIVE_I_SEE_INVIS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_I_HIDE, 90);
    seteuid(getuid(TO));
}

void equip_me()
{
    object gem;

    gem = clone_object(GEM_OBJ_DIR + "sea_agate");
    gem->set_heap_size(1 + random(3));
    gem->move(this_object());    
}

/*
 * Function name: stop_enter
 * Description:   Do we keep people from entering the pool?
 * Returns:       0 - no; 1 - yes.
 */
int stop_enter(string str)
{
    object tp = this_player();
    object para;

    notify_fail(capitalize(query_verb()) +" where?\n");
    if (!str)
        return 0;

    if (str == "water" || str == "in water" || str == "into water" ||
        str == "pool" ||  str == "in pool" || str == "into pool" ||
        str == "intertidal pool" || str == "in intertidal pool" || 
        str == "into intertidal pool")
    {
        if (query_imon() > 0)  
        {
            write("The seamonster prevents you from doing that.\n");
            say(QCTNAME(tp) +" tries to enter the pool, but the "+
                "seamonster stops "+ OBJECTIVE(tp) +".\n");
            return 1;
        }
        write("You jump into the pool.\nSomething grabs you by "+
            "the leg and begins to pull you down!\n");
        say(QCTNAME(tp) +" jumps into the pool.\n"+ QCTNAME(tp) +
            " suddenly begins to flail about, as though "+ POSSESS(tp) +
            " struggling against something that is pulling "+ 
        OBJECTIVE(tp) +" down!\n");
        set_imon(1);
        remove_prop(OBJ_I_HIDE);
        command("emote rises from the beneath the surface of the pool.");
        command("kill "+ tp->query_real_name());
        para = clone_object(HOLM_OBJ +"mon_para")->move(tp, 1);
        return 1;
    }
    return 0;
}

void init_living()
{
    ::init_living();
    add_action(stop_enter,   "enter");
    add_action(stop_enter,   "dive");    
    add_action(stop_enter,   "jump");        
}

void trap_em(object victim)
{
    int i, time;
    object *all, para;

    all = all_inventory(victim);
    for (i=0; i<sizeof(all); i++) 
    {
        if (MASTER_OB(all[i]) == MON_PARA) 
            return;
    }
    seteuid(getuid(TO));

    time = (3 * (random(6) + 1));
   
    para = clone_object(MON_PARA);
    para->set_remove_time(time);
    para->move(victim);
    tell_room(ETO, QCTNAME(TO) +" snakes a tendril out toward "+ 
        QNAME(victim) + " and wraps it around " + OBJECTIVE(victim) +
        "!\n", victim);
    victim->catch_msg(QCTNAME(TO) +" snakes a tendril out toward you "+ 
        "and wraps it tightly around you!\n");
    victim->add_attack_delay(time);
   return;
} 

int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
            return 1;
    }

    switch (random(8))
    {
        case 4: trap_em(victim);
            return 1;
        default: 
    }
    return 0;
}


int
query_knight_prestige() { return 500; }
