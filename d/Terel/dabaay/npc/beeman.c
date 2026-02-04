/*  This is an NPC named Beeman. He is called by dshop.c as a
 *  shopkeeper.  If he is killed, the shop will not function.  
 *
 *  Goldberry, November 1999
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;


#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("Beeman");
    add_name("beeman");
    set_race_name("half-elf");
    set_long(
        "Beeman is a tall and lanky half-elf, with an air of laziness "+
        "about him. He manages the general store of Dabaay.\n");

    /* Average stat: 92
     */
    default_config_npc(92);

    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 85);
    set_skill(SS_UNARM_COMBAT, 99);
    set_hp(9999);

    set_all_hitloc_unarmed(50);
    set_all_attack_unarmed(60, 50);

    set_chat_time(15);

    add_chat("You here to do business or are you going to just stand there "+
        "all day?"); 

    add_chat("I hates loiterers, always just loitering around.");

    add_chat("Hey, you break it, you bought it.");

    add_chat("If you don't like my prices, then you got a long walk to "+
        "next closest store in these parts.");

    add_chat("I really ought to do something about all those cracks in the "+
        "wall. Anriel's smoke keeps giving me headaches.");

    add_chat("Inconceivable, those fools in Calathin don't know the sea "+
        "from a hole in the ground.");

    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK,"Beeman lazily smacks you a good one and says: "+
       "Hey, if you want a fight, go get some of those filthy dog-children "+
       "that keep wandering in here.\n");

}
