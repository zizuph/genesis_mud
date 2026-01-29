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
#include "monsters.h"


create_monster()
{

    /* descritpion */

    set_race_name("human");

    set_adj("little");

    set_name("kid");

    set_short("little kid");

    add_name(({"kid", "brat"}));

    set_long(BS("A little kid that goes to this school.  She looks evil.\n"));

    set_gender(1);

    set_alignment(-250);
    set_aggressive(0);

    /* stats and skills */

    default_config_npc(10);
    set_base_stat(SS_INT, 10);
    set_base_stat(SS_WIS, 10);
    set_base_stat(SS_DIS, 5);
    set_base_stat(SS_STR, 5);
    set_base_stat(SS_DEX, 20);
    set_base_stat(SS_CON, 5);

    set_hp(200);

    /* actions */

    set_act_time(5);
    add_act("smirk");
    add_act("frown");
    add_act("sulk");
    add_act("grin");
    add_act("cackle");
    add_act("scream");
    add_act("spit");
    add_act("burp");

    set_chat_time(3);
    add_chat("You're a snotty little jerk!");
    add_chat("MY mother is prettier than YOUR mother!");
    add_chat("I hate you!");
    add_chat("I'm gonna telllllllllll!");
    add_chat("Kiss my butt!");
    add_chat("Wanna fight about it?");
    add_chat("I bet my dad could beat up your dad!");
    add_chat("School sucks!");

    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(5, 2);

}
/*
 * Function name:
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
