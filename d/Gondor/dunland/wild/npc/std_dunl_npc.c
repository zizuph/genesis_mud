/*
 *  The standard npc file for all ncs in 
 *  the camp of Dunlendings.
 *  
 *
 *  Created Sep 2012, by Martin Stromberg (Hordak)
 *
 * This has been created with help from temple_npc.c
 * in Sparkle. Credit goes to Gorboth.
 *
 */
#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include "/d/Gondor/dunland/wild/dunlendings.h"


/* Prototypes */
public string         create_dunl_npc();
nomask string         create_monster();
public void           assist_npc(object enemy);
public void           get_assistance(object enemy);

/* These routines are redefined in inheriting files to give personality
 * to the way in which the npcs do or do not help one another in fights.
 */
public void           ask_for_assistance()     { } 
public void           assist()                 { }          
public void           not_assist()             { } 
public void           not_ask_for_assistance() { }


/*
 * Function name:        dunl_npc
 * Description  :        dummy function to be replaced in inheriting files
 */
public string
create_dunl_npc()
{
} /* create_dunl_npc */


/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
nomask string
create_monster()
{
    setuid();
    seteuid(getuid());

    set_not_here_func("not_here_func");

    create_dunl_npc();
} 

/*
 * Function name:        assist_npc
 * Description  :        Have npcs help one another ... sometimes
 * Arguments    :        object enemy - who attacked us
 */
public void 
assist_npc(object enemy)
{
    if (member_array(enemy, this_object()->query_enemy(-1)) >= 0) 
    {
	return;
    }

    if (!random(3))
    {
	assist();   
	this_object()->attack_object(enemy);
    }
    else
    {
	not_assist();
    }
}


/*
 * Function name:        get_assistance
 * Description  :        Have npcs ask for assistance ... sometimes
 * Arguments    :        object enemy - the one who attacked us
 */
public void
get_assistance(object enemy)
{
    if (!random(2))
    {
	ask_for_assistance();

	filter(all_inventory(environment()), 
	  &->id(GONDOR_DUNL_NPC))->assist_npc(enemy);
    }
    else
    {
	not_ask_for_assistance();
    }
} /* get_assistance */
