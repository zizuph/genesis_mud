#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE

#define SHARK   "/d/Calia/sea/creatures/shark"
#define SQUID   (LIVING + "squid_giant")
#define SEALION (LIVING + "sealion")
#define NAGA    (LIVING + "sealion")
#define TURTLE  (LIVING + "ancient_dragon_turtle")

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("shape");
    add_adj("dark");
    add_adj("ominous");
    set_short("dark ominous shape beneath the water");
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
    string message = "A creature from the depths of the " +
        "sea rises out of the water!\n";

    if(!CAN_SEE(TO, enemy))
        return;

    if(present("lion", environment(this_object())) ||
       present("squid", environment(this_object())) ||
       present("turtle", environment(this_object())) ||
       present("naga", environment(this_object())) ||
       present("shark", environment(this_object())))
    {
	// Easy way to fix the problem of these npcs fighting
	// each other on occassions.
	return;
    }
    
    monster_type = random(10);

    switch(monster_type)
    {
        case 0:
            monster = clone_object(TURTLE);
            message = "The water erupts as a creature " +
                "of awe-inspiring gigantic proportions " +
                "rises out of the sea!\n";
            monster->move(E(TO));
        break;
        case 1..2:
            monster = clone_object(NAGA);
            monster->move(E(TO));
        break;
        case 3..5:
            monster = clone_object(SEALION);
            monster->move(E(TO));
        break;
        case 6..8:
            monster = clone_object(SQUID);
            monster->move(E(TO));
        break;
        default:
            monster = clone_object(SHARK);
            monster->move(E(TO));
            monster->set_alignment(0);
        break;
    } 

    tell_room(E(TO), message);
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


