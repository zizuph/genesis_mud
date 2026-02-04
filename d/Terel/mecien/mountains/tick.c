inherit "/std/monster";

#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define TO this_object()

/* Prototypes */
void catch_disease(object target);

init_living(){
   add_action("crush", "crush");
   ::init_living();
}

create_monster(){
    
    set_name("tick");
    set_race_name("tick");
    set_adj("foul");
    set_gender(2);
    set_long("A puffy black tick, its eyes are red.\n");
   
    set_act_time(1);
    add_act("@@bite");
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_VOLUME, 2);
    add_prop(CONT_I_WEIGHT, 2);   
}

bite(object target){
    if (!living(target = environment(TO)))
        return;
    target->heal_hp(-1);
    target->catch_msg("You feel a slight itching pain.\n");
    if(random(100) > 90){
        set_alarm(10.0, 1.0, &catch_disease(target));
    }
}

crush(string str){
    if(!str) return "Crush what?\n";
    if(str == "tick"){
        TP->catch_msg("You crush the tick and it dies.\n");
        TO->remove_object();
        return 1;
    }
}

catch_disease(object target){
}
