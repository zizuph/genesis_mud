/* A small hobbit */

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"

void
create_monster()
{
    set_name("teryth");
    set_pname("teryths");
    set_living_name("_teryth_");
    add_name("teryth");
    set_race_name("hobbit");
    add_adj(({"small","happy"}));
    set_long(break_string(
          "This hobbit is very small, but he has a pretty "
        + "good sized stomach on him nonetheless.  You "
        + "wonder how many meals he's had today. \n",70));
  
    set_alignment(100 + random(40));
    
    set_stats(({
                12 + random(5), /* STR */
                30 + random(30),/* DEX */
                20 + random(10),/* CON */
                15 + random(5), /* INT */
                15 + random(5), /* WIS */
                13 + random(3)  /* DIS */
             }));
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_HERBALISM, 50);
    set_skill(SS_HIDE, 50);
    set_skill(SS_SNEAK, 63);
    set_skill(SS_WEP_KNIFE, 20);

    MAKE_MONEY;
    
    set_act_time(6);
    add_act("emote smiles like he just finished supper.");
    add_act("search here for herbs");
    add_act("emote pats his stomach fondly.");

    set_chat_time(12);
    add_chat("As long as there's good food around, I'm happy!");
    add_chat("I'm looking for a mushroom, have you seen any?");
    add_chat("I hope Farmer Maggot doesn't catch me in his fields!");
    add_chat("If Old Farmer Maggot sees me, I'm in a LOT of trouble!");

    set_cact_time(4);
    add_cact("shout HELP! I'm being attacked!");
    add_cact("cry");
    add_cact("emote asks you to leave him alone");

    set_cchat_time(5);
    add_cchat("Why are you attacking me?");
    add_cchat("You are very mean.");
    add_cchat("I only wanted some mushrooms!!");


    set_alarm(1.0,0.0,"arm");    



  }

void
arm()
{
    object knife, shirt, food;

    FIXEUID;
    knife = clone_object("/d/Shire/narm/weapon/sm_knife");
    knife->move(TO);
    command("wield all");
    shirt = clone_object("/d/Shire/narm/armour/y_shirt");
    shirt->move(TO);
    command("wear all");
    food = clone_object("/d/Shire/narm/food/mushroom");
    food->move(TO);
  }
