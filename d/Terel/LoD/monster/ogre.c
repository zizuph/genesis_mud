#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <macros.h>
#include <money.h>

#define HEAD  LOD_DIR + "obj/ohead"

public void
create_monster()
{
    ::create_monster();
    
    set_name("ogre");
    set_race_name("ogre");
    set_adj("huge");
    set_long("A dark and dangerous looking ogre. He must have " +
             "been here since the last of the Avenchirs captured " +
             "him. Its head is unusually large and ugly looking.\n");

    default_config_npc(80);

    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 55);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_WEP_AXE, 50);
    set_hp(9000);
    set_mana(9000);
    set_aggressive("@@my_aggressive");

    set_all_attack_unarmed(35, 68);
    set_all_hitloc_unarmed(35);
    
    set_chat_time(34);
    add_chat("Nugyil almorf sadah!");
    add_chat("Seda u koyla.");
    add_chat("Hoyt!");
    add_chat("Koat u fot naya.");
}

public int
my_aggressive()
{
    string race = TP->query_race_name();
    
    if (race == "human" || race == "elf" || race == "hobbit")
        return 1;
    return 0;
}

public void
do_die(object killer)
{
    if (query_hp() > 0)
        return;
        
    command("say Huh?");
    command("emote looks confused as its head fall off.");
    
    seteuid(getuid());
    clone_object(HEAD)->move(ETO);
    
    ::do_die(killer);
}
