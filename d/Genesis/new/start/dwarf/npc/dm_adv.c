/*
 * Written by Nuf
 * /d/Genesis/new/start/dwarf/npc/dm_adv.c
 * Adventurer in the depths of the dwarven mountain(L0), 
 * looking for valuable stuff.
 */

#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include "../dwarf.h"

/* Prototypes */
public void create_monster();

/* Defines */

public void 
create_monster()
{
    int age;
    age = random(10)+15;
    set_name("adventurer");
    set_race_name("adventurer");
    set_living_name("_adventurer_in_dwarven_mountain");
    set_adj("nervous");
    add_adj("eager"); 
    set_long("He's quite young, simply venturing the tunnels "+
             "of the mountain.\n");
    set_stats( ({10+random(age), 10+random(age), 10+random(age), 
               5, 10,10}) );
    
    /* Properties */
    add_prop(OBJ_I_WEIGHT, 40000 + random(20)*1000);
    
    /* Movements */
    set_random_move(10);
    set_restrain_path(DWARF_START + "dm/L0");
    set_monster_home(DWARF_START + "dm/npc_ctrl.c");
}