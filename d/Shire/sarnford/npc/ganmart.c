/* Change Log:
 * Fixed a typo in the long description.
 * Raymundo, July 2020
 */

inherit "/std/monster.c";
inherit "/lib/shop.c";
inherit "/d/Emerald/lib/shop_list";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"

void introduce_me();
int intro_id;

void
create_monster()
{
   
   set_name("ganmart");
   set_title("Tallwater, the wandering merchant");
   add_adj(({"jolly","well-dressed"}));
   set_long("This man seems to have a perpetual smile on his " +
      "face, in addition to being very nicely dressed. Perhaps " +
      "you should introduce yourself to him?\n");
   set_race_name("human");
   set_gender(0);
   add_act("chuckle");
   add_act("emote makes checks his wagon to make certain everything is in place.");
   add_act("stretch");
   add_act("drinks a mug of beer.");
   add_act("smile");
   add_act("wanders into the Sleeping Fisherman, coming back with a mug of beer in his hand.");
   add_act("emote sits down on his wagon to eat a bowl of fish stew.");
   add_act("emote carefully inspects the wheels of his wagon, ensuring everything is ok.");
   add_act("runs into the building to grab something to eat.");
   add_act("scratch nose");
   add_act("emote goes into his wagon to rearrange some of his stores.");
   add_act("whistle");
   add_act("emote secures the tarp covering his wagon.");
   add_act("emote straightens his clothes.");

   add_chat ("As a merchant, my travels can take me to many different " +
      "lands, but for some reason I always seem to find myself back " +
      "here at the Fisherman.");
   add_chat ("Do you have anything to sell? Are you looking to make " +
      "a purchase? I am just enjoying some leisure time here, but a " +
      "successful merchant is never closed!");
   add_chat ("It is not an easy life being a travelling merchant, " +
      "but it can be profitable!");
   add_chat ("Would you like to buy anything?");
   add_chat ("Do you have anything you would like to sell?");
   add_chat ("Let me tell you, there is no better food than what you " +
      "can find here at the Fisherman!");
   add_chat ("There are strange things happening in the world today, " +
      "why I heard tell there are orcs migrating about. Orcs!");
   add_chat ("It is a dangerous world out there, if you don't have a " +
      "weapon to protect yourself, perhaps I can sell you one?");
   add_chat ("I am starting to feel hungry again already, I might " +
      "have to buy some more stew from Haestur.");
   
   set_act_time(10);
   set_chat_time(5);

   set_stats(({ 80, 80, 80, 100, 100, 80}), 10);
   
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE, 100);
   
   set_alignment(200);
   
   
  MAKE_MONEY;
   intro_id = 0;

   config_default_trade();
   set_money_give_max(1000);
   set_store_room(SARNFORD_DIR + "npc/ganmart_storeroom");
}

void
init_living()
{
    ::init_living();
    init_shop();
}


void
add_introduced(string person)
{
   if (intro_id == 0) {
      intro_id = set_alarm(4.0,0.0, introduce_me);
   }
}

void
allow_introductions() 
{
   intro_id = 0;
}

void
introduce_me()
{
   command("introduce me");

   set_alarm(15.0, 0.0, allow_introductions);
}


void
shop_hook_list_object(object ob, int price)
{
    string str, mess, categ;

    str = sprintf("%-41s", capitalize(LANG_ASHORT(ob)));
    categ = figure_category(ob);
    if (mess = text(split_values(price)))
    {
        mess = sprintf(" %-8s | %2d %2d %2d %2d", categ, price / 1728, (price 
            % 1728) / 144, (price % 144) / 12, price % 12);
        write("| " +str + "|" + mess + " |\n");
    }
    else
    {
        write(str + "That item wouldn't cost you much.\n");
    }

}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (!str || !stringp(str)) return 0;

    if (str == "notice")
    {
        return ::do_read("sign");
    }

    return 0;
}