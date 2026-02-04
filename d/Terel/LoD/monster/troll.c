#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <macros.h>
#include <money.h>

#include "/d/Terel/LoD/dungeon/quest.h"

public void
create_monster()
{
    ::create_monster();
    
    set_name("troll");
    set_race_name("troll");
    set_adj("enormous");
    set_long("An enormous troll.\n");

    default_config_npc(180);

    set_skill(SS_DEFENCE, 99);
    set_skill(SS_PARRY, 99);
    set_skill(SS_AWARENESS, 99);
    set_skill(SS_WEP_CLUB, 99);
    set_hp(9000);
    set_mana(9000);
    set_aggressive("@@my_aggressive");

    add_prop(CONT_I_WEIGHT, 153000);
    add_prop(CONT_I_VOLUME, 153000);
    add_prop(CONT_I_HEIGHT, 198);
    add_prop(CONT_I_MAX_WEIGHT, 283000);
    add_prop(CONT_I_MAX_VOLUME, 243000);

    set_all_attack_unarmed(35, 35);
    set_all_hitloc_unarmed(45);
    
    set_chat_time(34);
    add_chat("Gurk!");
    add_chat("Urgh.");
}

public int
my_aggressive()
{
    return 1;
}

public void
do_die(object killer)
{
    if (query_hp() > 0)
        return;
        
    command("say Huh?");
    
    ::do_die(killer);
}
