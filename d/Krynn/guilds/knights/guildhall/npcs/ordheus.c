/* Ordheus Ochre of Solanthus, Archknight */
/* modified by Teth and Morrigan 01/97 */
/* modified so he only have 1 sets of armours by Vencar 21-09-2003 */

#include "../../guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
inherit "/std/act/action";
inherit NPCSTD + "knight_base";

#include "./std/killer.h"

int sublevel, level;
string subtitle, title;
object attacker;

string
query_race_name()
{
    return(calling_function() == "query_presentation" ? "Solamnian" :
      "human");
}

string
set_my_title()
{
    level = 5;
    sublevel = 7;
    subtitle = ROSE_TITLES[sublevel];
    return "Knight of the Rose";
}


public void
create_knight_npc()
{
    int i;

    set_name("ordheus");
    set_living_name("ordheus");
    set_adj("towering");
    set_title("Ochre of Solanthus, the Archknight");
    add_name("gOrdheus");
    set_gender(0);
    set_introduce(1);
    set_long("This towering Knight of Solamnia takes his duties very " +
      "seriously, by the looks of it. He has a lengthy flowing " +
      "moustache, and it is a source of pride. Every move he makes " +
      "is conservatively measured, so that all his energies are " +
      "saved for a dangerous situation. He is an "+subtitle+".\n");
    set_race_name("human");
    for (i = 0; i < 6; i++)
        set_base_stat(i, 150 + random(30));
    set_all_hitloc_unarmed(90);

    set_knight_prestige(-8);
    set_alignment(1200);

    set_skill(SS_KATTACK, 150);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 90);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_GC(random(15) + 5)->move(TO);

    set_act_time(5);
    add_act("emote smooths his grand moustache with care.");
    add_act("say Ah, to be home in Solanthus, during spring dawning.");
    add_act("say The Knights of Solamnia are a noble organization!");
    add_act("emote gazes deep into your eyes.");
    add_act("emote unruffles his tunic.");
    add_act("emote solemnly declares: Est Sularus oth Mithas!");
    add_act("say The Knights of Solamnia are the finest body of justice and " +
      "honour throughout the land.");
    add_act("emote sighs and wistfully utters: How I wish I could go back " +
      "to Solanthus and visit my family. Alas, it's not to " +
      "be.");
    add_act("emote shuffles his body slightly.");
    add_act("emote steadies his body, and stands tall.");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'crown'", "say This Order represents " +
      "the virtues of loyalty and obedience. Habbakuk is the " +
      "patron god.",1);
    add_ask(" [about] 'sword'", "say Kiri-Jolith is the patron " +
      "god of this Order that represents courage and heroism.",1);
    add_ask(" [about] 'rose'", "say Paladine is the patron " +
      "god of this Order that values honour and justice.",1);
    add_ask(" [about] 'vingaard'", "say Vingaard Keep " +
      "shall never fall while I stand guard!",1);
    add_ask(" [about] 'task' / 'quest'", "say I have no tasks " +
      "for you, seek Gunthar.",1);
    add_ask(" [about] 'oath'", "say My Honour is My Life.",1);
    add_ask(" [about] 'order' / 'orders'", "say The " +
      "three Orders of the Knights " +
      "of Solamnia are Crown, Sword, and Rose.",1);
    add_ask(" [about] 'knight' / 'knights'", "say The " +
      "Knights of Solamnia are a body of warriors, bound " +
      "together in holy unity with the purpose of defending " +
      "the weak and impoverished and those in need, fighting " +
      "injustice and stemming the tide of evil. Several times "+
      "in our history, members of the Knights have been " +
      "called on to defend the world.", 1);
    add_ask(" [about] [vinas] 'solamnus'","say " +
      "A great man. He led an uprising against a cruel king, " +
      "after seeing the pain the Ergothian inflicted, even though " +
      "he was previously in the service of that king.",1);
    add_ask(" [about] 'paladine' / 'habbakuk' / 'kiri-jolith'", "say One " +
      "of the three patron gods of the Knights " +
      "of Solamnia. Another is better able to answer your questions " +
      "on this matter, or perhaps you could visit our library.",1);
    add_ask(" [about] 'joining'", "say Please read the book " +
      "about our holy order of Knights.",1);

}

