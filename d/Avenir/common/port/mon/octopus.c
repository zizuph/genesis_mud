 // Octopus          (/d/Avenir/common/port/mon/giant_octopus.c)
 // creator(s):       Ibun Mars -04
 // last update:      This octopus is bigger and tougher than the old one
 //                   Zielia, Jan 2009 - combined octopi to use one file,
 //                       upped the darkness caused by the ink (ink should
 //                       not be so easily countered with light), changed
 //                       the entangle so you must slice off the holding
 //                       arm or defeat the monster to exit, slowness
 //                       is managed by an object now
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

int arms = 8;

public void
config_octo(int octo_type = 0)
{
    remove_adj(query_adjs());
	
    if (octo_type == 1)
    {
	set_short("enormous eight armed octopus");
	set_adj(({"enormous", "eight armed" }));
	set_long("This lethal creature has found a new home here in the " +
	    "storage room of the old shipwreck. The environment being " +
	    "ideal, providing shelter for its enormous body. Though " +
	    "vulnerable, it still looks frightening with its many " +
	    "arms and giant head. Dont make any mistake now. " +
	    "He is going to eat you soon if you dont leave.\n");
	
	set_stats(({ 140, 140, 140, 90, 90, 130}));
	heal_hp(TO->query_max_hp());
	return;
    }	    
    set_short("huge pale octopus");
    set_adj(({"pale", "huge" }));
    set_long("This large creature has found a new home here in the " +
             "storage room of the old shipwreck. The environment being " +
             "ideal, providing shelter for its soft body. Though " +
             "vulnerable, it still looks frightening with its many " +
             "arms and giant head.\n");

    set_stats(({ 130, 90, 60, 90, 90, 130}));
    heal_hp(TO->query_max_hp());
}    

create_creature()
{
    set_name("octopus");
    set_race_name("octopus");
    config_octo();

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
   add_action("do_search","search");
   ::init_living();
}

public nomask void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
 /*
    hid:   The hitloc id        ph:    The %hurt
    att:   Attacker            aid:   The attack id
     dt:    The damagetype     dam:   The damage in hit points   */

{
   object arm;

   if(arms && dam>20 && dt==W_SLASH)
   {
      arm= clone_object(PORT + "obj/tentacle");
      arm->move(environment(TO));
      set_alarm(0.1,0.0,"remove_stuff",arms);
      tell_room(ENV(TO), QCTNAME(att) + " cuts an arm off the octopus!\n", 
          att, TO);
      att->catch_msg("You cut an arm off the octopus!\n");
 
      ENV(TO)->let_go(att, arms); 
      arms=arms-1;   
   }
   ::cr_got_hit( hid, ph, att, aid, dt, dam);
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
   ENV(TO)->add_prop(ROOM_S_DARK_LONG,
	"The dark water around you covers your sight.\n");
   ENV(TO)->add_prop(ROOM_S_DARK_MSG,
	"The water is too dark to");
   environment(TO)->update_light();
   observers = filter( all_inventory(environment(TO)), interactive );
   observers->catch_msg("The ink dissolves.\n");
}

void
do_entangle(object player)
{
   object robe = player->query_armour(A_ROBE);
      
   if( !present( player, environment(TO)) )
   {
      return;
   }

   if (robe->id("_oilskin_cloak_"))
   {
	player->catch_msg("The octopus tries to grab you, " +
	    "but the tentacles slips on your cloak.\n");
	return;
   }
   
   environment(TO)->hold_me(player, arms);      
}

/* which enemies are in the room with me?*/
public mixed
query_p_enemies(void)
{
    return TO->query_enemy(-1) &
	filter(all_inventory(environment(TO)), living);
}

int
special_attack(object victim)
{
   int light;
   object *enemies = query_p_enemies();
   object enemy = one_of_list(enemies); 
   
   light = TO->query_prop(CONT_I_LIGHT);
   if(light)
      return 0;
      
   switch(random(4))
   {
   case 3:
      victim->catch_msg(QCTNAME(TO) + " squirts ink at you. It " +
         "spreads and covers the area like dark, impenetrable blanket.\n");
      tell_room(ENV(TO), QCTNAME(TO) + " squirts ink at " + QTNAME(victim) +
         ". It spreads and covers the area like a dark, impenetrable "+
         "blanket.\n", victim, TO);
      TO->add_prop( CONT_I_LIGHT, ALWAYS_DARK );
      ENV(TO)->add_prop(ROOM_S_DARK_LONG, "Black ink clouds the water and "+
         "obscures your vision.\n");
      ENV(TO)->add_prop(ROOM_S_DARK_MSG, "You cannot see through the ink "+
         "to");
      set_alarm(itof(4+random(12)), 0.0, &remove_dark(TO) );
   break;
   case 2:
      do_entangle(enemy); 
   break;
   default:
        /* do nothing*/
   break;
   }
   return 0;
}

public void
do_die(object killer)
{
    remove_dark(TO);
    environment(TO)->release_all();
   ::do_die(killer);
}

do_search()
{
   TP->catch_msg("The "+ short() +" stops you from doing that.\n");
   return 1;
}

void
attacked_by( object ob )
{
   ::attacked_by(ob);
   if (random(3))
        do_entangle(ob);
}

