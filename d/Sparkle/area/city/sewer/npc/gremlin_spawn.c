/*
 * /w/aeg/sparkle/sewer/npc/gremlin_spawn.c
 *
 * This is a weakest gremlin in the sewers.
 *
 * Created FEB 10 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types
#include "defs.h"
 
inherit GREM_NPC;

#include <macros.h>         /* General purpose */
#include <stdproperties.h>  /* References */
#include <ss_types.h>       /* Skills */
#include <wa_types.h>       /* Attack+Hitloc */
#include <cmdparse.h>       /* actions */
#include <money.h>          /* money */

public void     create_gremlin();
public void     arm_me();

/* 
 * Function name:       create_gremlin
 * Description  :       creates NPC with gremlin settings 
 */
 
public void
create_gremlin()
{
    add_name("spawn");
    seteuid(getuid());
    set_long("The " + query_short() + " is a creature who dwells in dark, "
        + "wet places. This specific variety is the common sewer gremlin, "
        + "who lives beneath cities and wreaks havoc upon the surface-"
        + "dwellers. This gremlin appears to be a newcomer to life.\n");

    set_base_stat(0, 30, 10);
    set_base_stat(1, 40, 10);
    set_base_stat(2, 40, 10);
    set_base_stat(3, 50, 10);
    set_base_stat(4, 20, 10);
    set_base_stat(5, 30, 10);
    set_hp(20000); /* Heal it */
    
    arm_me();
 
}


void
arm_me() 
{
    seteuid(getuid());
    clone_object(SEWER_OBJ_DIR + "spawn_armour")->move(this_object());
    clone_object(SEWER_OBJ_DIR + "grem_dagger")->move(this_object());
    command("wear all");
    command("wield all");

}