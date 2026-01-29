/* An Imp (humanoid) - Tulix III, recoded 13/07/95 */
/* Cloned by caves: levela/cave6a.c & levela/cave10a.c */ 

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"

void
create_monster()
{
    set_name("imp");
    set_pname("imps");
    set_race_name("imp");
    set_short("short imp");
    set_pshort("short imps");
    set_adj("short");
    set_long("Its a nasty little Imp. It has an evil grin on its face.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1 );

    set_gender(2);  /* male=0, female=1, other=2 */

    set_default_answer("The imp thinks for a while.\n" +
        "The imp then gestures to you with two fingers!\n");
    /* stats -   STR DEX CON INT WIS DIS  */
    set_stats(({  10, 10, 10, 2, 3, 10}));
    set_hp(20400);
    set_alignment(-30);

    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(5,5);

    set_attack_chance(30);

    /* Set the all important skills. */
    set_skill(SS_UNARM_COMBAT,3);
    set_skill(SS_BLIND_COMBAT,40);
    set_skill(SS_PARRY,3);
    set_skill(SS_DEFENCE,2);

    set_cchat_time(2);               /* Set combat speaking interval  */
    add_cchat("Help!");

    set_act_time(2);
    add_act("grin");
    add_act("kick all");
    add_act("smirk");
    add_act("spit at lichen");
    add_act("poke all");
}

void
arm_me()
{
    return;
}
