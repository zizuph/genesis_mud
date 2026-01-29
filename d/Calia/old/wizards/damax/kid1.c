/* 	this is a monster of the town Gelan

    coder(s):   Damax 

    history:    18.02.93       Created                Damax 

    purpose:    One of the smaller children in the school.  

    weapons:    none
    armours:    none

    objects:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "townmonsters.h"


create_monster()
{

    /* descritpion */

    set_name("child");
    set_race_name("human");

    set_adj("small");

    set_short("a small child");

    set_long(BS("One of many small children in the lower grades.\n"));

    set_gender("male");

    set_alignment(0); 
    set_aggressive(0);

    /* stats and skills */

    default_config_npc(%);
    set_base_stat(SS_INT, 10);
    set_base_stat(SS_WIS, 10);
    set_base_stat(SS_DIS, 5);
    set_base_stat(SS_STR, 5);
    set_base_stat(SS_DEX, 20);
    set_base_stat(SS_CON, 5);

    set_hp(200);


    /* actions */
    set_act_time(5);
    add_act("giggle");
    add_act("bounce");
    add_act("cry");
    add_act("sulk");
    add_act("pout");
    add_act("scream");
    add_act("sob");

    set_chat_time(10);
    add_chat("Ow!  She hit me!");
    add_chat("You got cooties, you got cooties!");
    add_chat("Turtle Power!!!");
    add_chat("Nyahh nyahh nyaaahhhhh!  You can't catch me!");
    add_chat("I like recess best!");

    set_all_hitloc_unarmed(%);
    set_all_attack_unarmed(%);

/*
 * Function name:
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
