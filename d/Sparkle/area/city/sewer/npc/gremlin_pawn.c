/*
 * /w/aeg/sparkle/sewer/npc/gremlin_pawn.c
 *
 * This is a weaker gremlin in the sewers.
 *
 * Created FEB 07 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types
#include "../defs.h" 
 
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
    add_name("pawn");

    set_long("The " + query_short() + " is a creature who dwells in dark, "
        + "wet places. This specific variety is the common sewer gremlin, "
        + "who lives beneath cities and wreaks havoc upon the surface-"
        + "dwellers. This gremlin appears to be a lessor warrior.\n");

    set_base_stat(0, 80, 10);
    set_base_stat(1, 105, 10);
    set_base_stat(2, 70, 10);
    set_base_stat(3, 110, 10);
    set_base_stat(4, 60, 10);
    set_base_stat(5, 60, 10);
    set_hp(20000); /* Heal it */
    
    arm_me();
 
}


void
arm_me() 
{
    seteuid(getuid());
    clone_object(SEWER_OBJ_DIR + "grem_suit")->move(this_object());
    clone_object(SEWER_OBJ_DIR + "owlrat_pelt")->move(this_object());
    clone_object(SEWER_OBJ_DIR + "grem_dagger")->move(this_object());
    command("wear all");
    command("wield all");

}