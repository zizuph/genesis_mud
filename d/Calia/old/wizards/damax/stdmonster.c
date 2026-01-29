/* 	this is a monster of the town Gelan

    coder(s):   standard

    history:    DD.MM.YY    what done                       who did

    purpose:    none

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

arm_me()
{
    object %;

    % = clone_object(TOWN_OBJECTS + "%");
    %->move(this_object());
}

create_monster()
{

    /* descritpion */

    set_name("%");
    set_race_name("%");

    set_adj("%");

    set_short("%");

    set_long(BS("%\n"));

    set_gender("%");

    set_alignment(%);
    set_aggressive(%);

    /* stats and skills */

    default_config_npc(%);
    set_base_stat(SS_INT, 100);
    set_base_stat(SS_WIS, 100);
    set_base_stat(SS_DIS, 100);
    set_base_stat(SS_STR, 100);
    set_base_stat(SS_DEX, 100);
    set_base_stat(SS_CON, 100);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);

    set_hp(%);

    /* properties */

    add_prop(%, %);

    /* armour */

    call_out("arm_me", 1);

    /* actions */
    set_act_time(%);
    add_act("%");

    set_chat_time(%);
    add_chat("%");

    set_cchat_time(%);
    add_cchat("%");

    set_all_hitloc_unarmed(%);
    set_all_attack_unarmed(%);

    set_random_move(%);

}

/*
 * Function name:
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
