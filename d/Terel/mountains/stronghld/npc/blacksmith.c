/*  
 *  Blacksmith
 *
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/action";

#include "/sys/macros.h"
#include <ss_types.h>


void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("narmar");
    add_name("Narmar");
    add_name("keeper");
    set_race_name("dwarf");
    set_title("Master Blacksmith");
    set_adj(({"musclebound","tall"}));
    set_long("The dwarf looks quite serious about his work " +
       "at the forge.\n");

    default_config_npc(88);


    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_UNARM_COMBAT, 80);
    SET_MAX_HP;

    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(50, 40);
    
    enable_intro();
    add_act("muscles flex as he hammers out a piece of stock over an anvil.");
    add_act("wipes his sweaty brow with a hankerchief.");
    add_act("pumps the bellows heating up the furnace.");
    set_chat_time(15);
    add_chat("I can fix your dull weapons.");
    add_chat("Don't throw dull weapons out, I'll make them good as new!");

}
