/*
 * /w/aeg/sparkle/sewer/npc/gremlin_warrior.c
 *
 * This is a strong gremlin in the sewers.
 *
 * Created FEB 07 2009, by Aeg (Matthew Morin)
 */
 

#pragma strict_types
#include "../defs.h"
#include <ss_types.h>           /* for SS_DEFENCE, etc          */

inherit GREM_NPC;

public void     create_gremlin();
public void     arm_me();

/* 
 * Function name:       create_gremlin
 * Description  :       creates NPC with gremlin settings 
 */
 
public void
create_gremlin()
{

    add_name("warrior");
    set_long("The " + query_short() + " is a creature who dwells in dark, "
        + "wet places. This specific variety is the common sewer gremlin, "
        + "who lives beneath cities and wreaks havoc upon the surface-"
        + "dwellers. This gremlin appears to be a greater warrior.\n");

    /* skills */
    set_skill(SS_DEFENCE,       40+random(30));
    set_skill(SS_UNARM_COMBAT,  30+random(10));
    set_skill(SS_WEP_KNIFE,     40+random(20));
    set_skill(SS_WEP_AXE,       20+random(20));
    set_skill(SS_WEP_POLEARM,   20+random(20));
    set_skill(SS_WEP_SWORD,     50+random(10));
    set_skill(SS_WEP_CLUB,      60+random(10));
    set_skill(SS_AWARENESS,     60+random(12));
    set_skill(SS_PARRY,         60+random(10));


    set_base_stat(0, 110, 10);
    set_base_stat(1, 155, 10);
    set_base_stat(2, 100, 10);
    set_base_stat(3, 180, 10);
    set_base_stat(4, 100, 10);
    set_base_stat(5, 100, 10);
    set_hp(20000); /* Heal it */
    
    arm_me();
 
}


void
arm_me() 
{
    seteuid(getuid());
    clone_object(SEWER_OBJ_DIR + "grem_suit")->move(this_object());
    clone_object(SEWER_OBJ_DIR + "owlrat_pelt")->move(this_object());
    clone_object(SEWER_OBJ_DIR + "grem_shield")->move(this_object());
    clone_object(SEWER_OBJ_DIR + "grem_scimitar")->move(this_object());
    command("wear all");
    command("wield all");

}