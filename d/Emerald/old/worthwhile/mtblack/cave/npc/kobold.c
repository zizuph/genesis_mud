/* An Evil Kobold (humanoid) - Recoded 18/07/95, Tulix III */
/* Cloned by caves: levela/cave13a.c levelb/cave2b.c levelb/cave6b.c */

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"

void
create_monster()
{
    set_name("kobold");
    set_pname("kobolds");
    set_race_name("kobold");
    set_short("evil kobold");
    set_pshort("evil kobolds");
    set_adj("evil");
    set_long("It is a horrible little creature, that scavenges food "
	+"off long dead corpses.\n");

    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_gender(0);  /* male=0, female=1, other=2 */

    set_default_answer("The kobold merely snorts.\n");
    /* stats -   STR DEX CON INT WIS DIS  */
    set_stats(({ 25, 25, 25, 10, 10, 25}));
    set_hp(20400);
    set_alignment(-20);

    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10,15);

    set_attack_chance(60);

    /* Set the all important skills. */
    set_skill(SS_WEP_KNIFE,20);
    set_skill(SS_UNARM_COMBAT,10);
    set_skill(SS_BLIND_COMBAT,40);
    set_skill(SS_DEFENCE,30);

    set_chat_time(5);                /* Set speaking interval         */
    add_chat("Get lost, scum.");
    add_chat("What are you looking at, scum?");
    add_chat("Get out before I kill you!"); 
    add_cchat("Prepare to die!");  

    set_act_time(5);               /* Set action interval           */
    add_act("scream");            
    add_act("spit at lichen");
    add_act("grin");

}

void
arm_me()
{
    object wep;

    wep = clone_object(CAVE_DIR + "wep/ord_knife");
    wep -> move( TO );
    command("wield all");
    return;
}
