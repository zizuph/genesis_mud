/* Netyle, the General Store Shopkeeper, Gwyneth, June 1999 */

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/act/action.c";
inherit AM_FILE

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("netyle");
    set_living_name("netyle");
    set_race_name("kender");
    set_title("Bigpouch of Kendermore");
    set_long("This kender looks like he has boundless energy as he runs " + 
        "back and forth from the store room to the front room, carrying " + 
        "goods and parcels. He chatters about anything and everything as " + 
        "he works, enjoying the company of his customers.\n");
    add_name("shopkeeper");
    set_adj("energetic");
    add_adj("skinny");
    set_gender(G_MALE);
    set_introduce(1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and hands it " +
        "back, saying 'See, sometimes I do remember to return things!'\n");

    set_stats(({80,100,80,90,90,100}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_WEP_POLEARM, 50);

    set_alignment(350);
    set_knight_prestige(-40);

    start_patrol();
    set_patrol_time(2);
    set_patrol_path(({"yawn",180,"e","s","s","sw","w","sw","w","nw","n","ne",
        "e","sw",
        "emote jumps up high, waving his arms, and all the pigeons scatter.",
        "giggle mischievously","ne","w","sw","s","se","e","ne","e","ne","n",
        "n","w","bounce",600}));

    set_act_time(5);
    add_act("emote chatters: What can I do for you?");
    add_act("smile impishly");
    add_act("emote chatters about an adventure he had one time.");
    add_act("emote eyes your pockets.");

    set_default_answer("He seems to be busy talking, and doesn't hear " + 
        "your question.\n");
    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : Arm me
 * Description : Clones, wears and wields armours and weapons.
 * Returns : Null
*/

void
arm_me()
{
    setuid();
    seteuid(getuid(TO));
    clone_object(KOBJ + "std_knife")->move(TO);
    clone_object(KOBJ + "hoopak")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);
    clone_object(KOBJ + "cloak")->move(TO);
    clone_object(KOBJ + "shirt")->move(TO);

    command("wear all");
    command("wield all");
}

