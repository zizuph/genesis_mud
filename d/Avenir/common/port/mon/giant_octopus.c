 // Octopus          (/d/Avenir/common/port/mon/giant_octopus.c)
 // creator(s):       Ibun Mars -04
 // last update:      This octopus is bigger and tougher than the old one
 // purpose:          Should live in the storeroom of the
 //                   shipwreck.
 // note:
 // bug(s):
 // to-do:

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#include "/d/Avenir/common/common.h"

#define A_ARM8  0
#define A_ARM1  1
#define A_ARM2  2
#define A_ARM3  3
#define A_ARM4  4
#define A_ARM5  5
#define A_ARM6  6
#define A_ARM7  7

#define H_HEAD 8

#define H_ARM1 1
#define H_ARM2 2
#define H_ARM3 3
#define H_ARM4 4
#define H_ARM5 5
#define H_ARM6 6
#define H_ARM7 7
#define H_ARM8 0
int n = 8;

create_creature()
{
    set_name("octopus");
    set_race_name("octopus");
    set_short("enormous eight armed octopus");
    set_adj(({"enormous", "eight armed" }));
    set_long("This lethal creature has found a new home here in the " +
             "storage room of the old shipwreck. The environment being " +
             "ideal, providing shelter for its enormous body. Though " +
             "vulnerable, it still looks frightening with its many " +
             "arms and giant head. Dont make any mistake now. " +
             "He is going to eat you soon if you dont leave.\n");

    set_stats(({ 140, 140, 140, 90, 90, 130}));

    heal_hp(10000);

    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_SWIM, 80);

    set_attack_unarmed(A_ARM1,  30, 15, W_BLUDGEON, 90, "tentacle");
    set_attack_unarmed(A_ARM2,  30, 15, W_BLUDGEON, 90, "tentacle");
    set_attack_unarmed(A_ARM3,  30, 15, W_BLUDGEON, 90, "tentacle");
    set_attack_unarmed(A_ARM4,  30, 15, W_BLUDGEON, 90, "tentacle");
    set_attack_unarmed(A_ARM5,  30, 15, W_BLUDGEON, 90, "tentacle");
    set_attack_unarmed(A_ARM6,  30, 15, W_BLUDGEON, 90, "tentacle");
    set_attack_unarmed(A_ARM7,  30, 15, W_BLUDGEON, 90, "tentacle");
    set_attack_unarmed(A_ARM8,  30, 15, W_BLUDGEON, 90, "tentacle");

    set_hitloc_unarmed(H_HEAD, ({ 30, 15, 40 }), 20, "head");
    set_hitloc_unarmed(H_ARM1,  ({ 30, 15, 40 }), 10, "tentacle");
    set_hitloc_unarmed(H_ARM2,  ({ 30, 15, 40 }), 10, "tentacle");
    set_hitloc_unarmed(H_ARM3,  ({ 30, 15, 40 }), 10, "tentacle");
    set_hitloc_unarmed(H_ARM4,  ({ 30, 15, 40 }), 10, "tentacle");
    set_hitloc_unarmed(H_ARM5,  ({ 30, 15, 40 }), 10, "tentacle");
    set_hitloc_unarmed(H_ARM6,  ({ 30, 15, 40 }), 10, "tentacle");
    set_hitloc_unarmed(H_ARM7,  ({ 30, 15, 40 }), 10, "tentacle");
    set_hitloc_unarmed(H_ARM8,  ({ 30, 15, 40 }), 10, "tentacle");

    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(MAGIC_I_BREATH_WATER, 1);
}

init_living()
{
   set_alarm(3.0, 0.0, "do_entangle", TP );
   add_action("do_search","search");
   ::init_living();
}
 /*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */

static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

public nomask void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
 /*
    hid:   The hitloc id        ph:    The %hurt
    att:   Attacker            aid:   The attack id
     dt:    The damagetype     dam:   The damage in hit points   */

{
   object arm;

   if(n && dam>20 && dt==W_SLASH)
   {
      n=n-1;
      arm= clone_object(PORT + "obj/tentacle");
       arm->move(environment(TO));
      set_alarm(0.1,0.0,"remove_stuff",n);
      tell_watcher(QCTNAME(att) + " cuts an arm off the octopus!\n", att);
      att->catch_msg("You cut an arm off the octopus!\n");
   }
   ::cr_got_hit( hid, ph, att, aid, dt, dam);
}

void
test_props()
{
// This function has been moved to the room instead. Call in do_die didnt work
     int i;
     object *all;
 
    all = all_inventory(environment(this_object()));
     for (i=0; i<sizeof(all); i++) 
     {
         if (all[i]->query_prop("_is_entangled"))
         {
            all[i]->remove_prop("_is_entangled");
            all[i]->change_prop(LIVE_I_QUICKNESS, 
            (all[i]->query_prop_setting(LIVE_I_QUICKNESS) + 50));
         }
     }
 
}
remove_stuff(int n)
{
   remove_hitloc(n);
   remove_attack(n);
}

void
remove_dark( object ob )
{
   object *observers;

   ob->remove_prop(CONT_I_LIGHT);
   environment(TO)->update_light();
   observers = filter( all_inventory(environment(TO)), interactive );
   observers->catch_msg("The ink dissolves.\n");
}

int
special_attack(object enemy)
{
   int light;

   light = TO->query_prop(CONT_I_LIGHT);
   if(light)
      return 0;
   if(!random(3))
   {
      enemy->catch_msg(QCTNAME(TO) + " squirts ink at you. It " +
         "spreads and covers the area like dark blanket.\n");
      tell_watcher(QCTNAME(TO) + " squirts ink at " + QTNAME(enemy) +
         ". It spreads and covers the area like a dark blanket.\n", enemy);
      TO->add_prop( CONT_I_LIGHT, -10 );
      set_alarm(12.0, 0.0, &remove_dark(TO) );
   }
   return 0;
}

public void
do_die(object killer)
{
   remove_dark(TO);
    environment(TO)->test_props();
   ::do_die(killer);
}

void
do_entangle(object player)
{
   object robe;
   if( !present( player, environment(TO)) )
   {
      return;
   }
    robe = player->query_armour(A_ROBE);
    if (robe->id("_oilskin_cloak_"))
   {
    player->catch_msg("The octopus tries to grab you, " +
                      "but the tentacles slips on your cloak.\n");
    return;
   }
   player->catch_msg("Too late you notice the octopus sliding a " +
                     "tentacle around your body with a good grip. You are stuck.\n");
   player->add_prop("_is_entangled", 1);
    player->change_prop(LIVE_I_QUICKNESS,  
        (player->query_prop_setting(LIVE_I_QUICKNESS) - 50));
}


do_search()
{
   TP->catch_msg("The huge pale octopus stops you from doing that.\n");
   return 1;
}

void
attacked_by( object ob )
{
   ::attacked_by(ob);
   if (ob->query_prop("_is_entangled"))
        ob->catch_msg("Being entangled like this makes your moves very slow.\n");
}

