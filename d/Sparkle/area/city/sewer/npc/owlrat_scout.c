/*
 * /d/Sparkle/area/sewer/npc/owlrat_scout.c
 *
 * This is a weakest owlrat.
 *
 * Created FEB 11 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types
#include "../defs.h"
 
inherit "/d/Sparkle/area/city/sewer/npc/owlrat_npc";

#include <macros.h>         /* General purpose */
#include <stdproperties.h>  /* References */
#include <ss_types.h>       /* Skills */
#include <wa_types.h>       /* Attack+Hitloc */
#include <cmdparse.h>       /* actions */
#include <money.h>          /* money */

public void     create_owlrat();

/* 
 * Function name:       create_owlrat
 * Description  :       creates NPC with owlrat settings 
 */
 
public void
create_owlrat()
{
    set_long("This " + query_short() + " is a creature that infests cities "
        + "and buildings, where food is left around. This mix, between an "
        + "owl and a rat, is a scavenger of foodstuffs and is often blamed "
        + "for the spread of disease. It can simpily be described as an owl "
        + "with a rat tail and sharp teeth sticking out of it's beak. This "
        + "owlrat is quite small and seems only interested in scavenging "
        + "for food.\n");

    set_base_stat(0, 15, 10);
    set_base_stat(1, 25, 10);
    set_base_stat(2, 25, 10);
    set_base_stat(3, 30, 10);
    set_base_stat(4, 40, 10);
    set_base_stat(5, 20, 10);
    set_hp(20000); /* Heal it */
    
}

