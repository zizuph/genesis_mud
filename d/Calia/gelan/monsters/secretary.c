/* 	this is a monster of the town Gelan

    coder(s):   Merlin

    history:    21. 9.94  created               Merlin

    purpose:    this is the secretary for the hospital

    weapon:     none
    armour:     none

    objects:    none

    quests:     none
    special:    log debts of players

    to do:      

    bug:        none known
*/

#include "monster.h"
inherit STD_GUARD;
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>


#define FILE "patients"

mapping patients;


/*
 * Function name: create_monster
 * Description:   creates the guard
 * Arguments:     none
 * Returns:       none
 */

create_monster()
{
    seteuid(getuid());

    /* descritpion */

    set_race_name("secretary");

    set_adj(({"clean","educated"}));

    set_long("This is the secretary of the Gelan hospital");

    set_gender(G_FEMALE);

    set_alignment(1000);

    /* stats and skills */

    default_config_npc(10);    			/* make it intelligent, but */
                                                /* not strong */

    set_base_stat(SS_INT, 10);
    set_base_stat(SS_WIS, 10);

    set_hp(this_object()->query_max_hp());	/* starts with full strength */
    set_mana(this_object()->query_max_mana());

    /* properties */

    add_prop(OBJ_I_WEIGHT, 55000);
    add_prop(OBJ_I_VOLUME, 25000);
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 0);
    add_prop(LIVE_I_SEE_INVIS, 0);

    /* armour */

    /* actions */
    set_act_time(50);
    add_act("smile");
    add_act("bow");
    add_act("twiddle");
  
    set_cchat_time(50);
    add_cchat("Hi there");
    seteuid(getuid());

    /* get the patient mapping */

    patients = restore_map(FILE);    
}

/*
 * Function name: help_other
 * Description:   react on help call from master guard (shadow original
                  function)
 * Arguments:     the nearest meeting room to the attacked guard,
                  the room the guard is attacked in,
                  the object pointer to the attacker
 * Returns:       none
 */

void
help_other(int meeting, string room, object attacker)
{

    command("say Well, someone just attacked one of our guards.");
    command("say You'd better be carefull in the town.");

}


/* shouldn't go anywhere when an enemy leaves */
void
notify_enemy_gone(object attacked)
{
}


int
special_attack(object enemy)
{
 
}

void
record(string name, int cost)
{
  patients += ([ name: cost ]);  
}

void
print_patients()
{
  write("Patients: ");
  dump_array(patients);
  write("\n");
}

void
remove_object()
{
/*  save_map(patients, FILE); */

  ::remove_object();
}


void
test()
{
  save_map(patients, FILE);
}
