/* Changed alignment to 100
 * 600 seemed rather extreme
 * removed the no_attack prop and gave him a few skills
 * Damaris 2/2002
 */
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("mardon");
    add_name("shopkeeper");
    add_name("owner");
    set_race_name("human");
    set_adj("grizzled");
    add_adj("scarred");
    set_long("A swarthy, grizzled old veteran of many battles. Or so it "+
      "seems when your first lay eyes upon him. Altough his outward demeanor "+
      "appears menacing and even hostile, somehow you know that this is a "+
      "kind and gentle man.\n");
    set_stats(({90,90,120,80,80,120}));
    set_alignment(100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_BLIND_COMBAT,50);
    set_skill(SS_DEFENCE,60);
    set_title("the Owner of the Tar Shop");
    set_act_time(3);
    add_act("emote smiles warily.");
    add_act("say Tar isn't as worthless as most people think.");
    add_act("say Without tar, you couldn't have ships!");
    add_act("emote polishes the desk.");
    add_act("smile friendly");
    set_cact_time(3);
    add_cact("say Have you no respect for the elderly!");
    add_cact("spit");
    add_cact("say You younger folk are all barbarians!");
    add_cact("scream");

    add_speak("I have the best tar in the entire town...probably because I'm the only "+
      "shopkeeper that sells it!\n");
    set_default_answer("The shopkeeper says: I don't understand what you "+
      "are talking about.\n");
    add_ask(({"tar"}),"The shopkeeper says: Tar is the lifeblood of a "+
      "thriving port city, in fact, it is the lifeblood of any sea-going "+
      "community.\n");
    set_knight_prestige(-100);

}
