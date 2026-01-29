#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

#define SHARK "/d/Calia/sea/creatures/shark"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("shape");
    add_adj("dark");
    add_adj("shadowy");
    set_short("dark shadowy shape beneath the water");
    set_long("Something lurks under the water here. You cannot " +
      "make out any details, apart from the fact that it looks " +
      "rather large.\n");
    set_gender(G_NEUTER);

    set_stats(({100, 100, 100, 100, 100, 100}));
    set_hp(query_max_hp());


    set_alignment(0);
    set_knight_prestige(0);
    set_skill(SS_SWIM, 100);
    set_skill(SS_AWARENESS, 100);
    add_prop(CONT_I_HEIGHT, 600);
    add_prop(CONT_I_WEIGHT, 490000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_BODY, 1); 
    add_prop(LIVE_I_NO_CORPSE, 1);  

    set_act_time(6);
    add_act("emote moves silently beneath you.\n");

    add_prop(OBJ_M_NO_ATTACK,"Whatever the creature is beneath you, " +
       "it is too deep for you to attack from here.\n");

    setuid();
    seteuid(getuid());
}

void
monster_attack(object enemy)
{
    object monster;
    int monster_type;

    if(!CAN_SEE(TO, enemy))
        return;

    if(present("turtle", environment(this_object())) ||
       present("serpent", environment(this_object()))||
       present("shark", environment(this_object())))
    {
	// Easy way to fix the problem of these npcs fighting
	// each other on occassions.
	return;
    }
    
    monster_type = random(4);

    if(monster_type == 0)
    {
    monster = clone_object(BNPC + "dragon_turtle");
    monster->move(E(TO));
    }
    else if(monster_type == 1)
    {
    monster = clone_object(BNPC + "serpent");
    monster->move(E(TO)); 
    } 
    else
    {
    monster = clone_object(SHARK);
    monster->move(E(TO));
    monster->set_alignment(0);
    }   

    tell_room(E(TO),
       "A creature from the depths of the Bloodsea of Istar rises out of the " +
       "water!\n");
    monster->command("kill " +enemy->query_real_name()); 

    TO->remove_object();

}


void
init_living()
{

    if(living(TP))
        set_alarm(4.0,0.0, "monster_attack",TP);
    ::init_living();
}


