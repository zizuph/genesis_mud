/* A ghostly butler. Mortricia 921027 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define WEP_DIR         MORTRICIADIR + "weapons/"
#define ARM_DIR         MORTRICIADIR + "armours/"
#define ALIGN           -10

init_living()
{
    ::init_living();
   add_action("do_ask", "ask");
}

void
create_monster()
{
   if (!IS_CLONE) return;
   
   set_name("butler");
   set_short("ghostly butler");
   set_long(BSN(
         "It's an old butler. You aren't quite certain whether he " +
         "is a real living servant or whether he is a ghost. " +
         "Nevertheless, he can probably answer some of your questions."
         ));
   set_adj("ghostly");
   set_race_name("human");
   set_gender(0);
   
   set_stats(({25,25,25,40,40,25}));
   set_hp(9999);
   set_mana(9999);
   set_alignment(ALIGN);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   
   set_skill(SS_UNARM_COMBAT, 10);
   set_skill(SS_WEP_SWORD, 20);
   set_skill(SS_AWARENESS, 20);
   
   set_all_hitloc_unarmed(10);
   set_all_attack_unarmed(10, 10);
   
   set_chat_time(10);
   add_chat("Welcome!");
   
   set_act_time(10);
   add_act(({"bow", "smile"}));
   
   seq_new("do_first");
   seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
   object sword, cloak;
   
   seteuid(getuid(TO));
   cloak = clone_object(ARM_DIR + "cloak");
   cloak -> set_name("livery");
   cloak -> set_short("black livery");
   cloak -> set_long("A black livery. Normally used on state " +
      "occasions.\n");
   cloak -> set_adj("black");
   cloak -> move(TO);
   command("wear livery");
   
   sword = clone_object(WEP_DIR + "plain_sword");
   sword -> set_name("sabre");
   sword -> set_short("ceremonial sabre");
   sword -> set_adj("ceremonial");
   sword -> set_long(BSN(
         "It's a ceremonial sabre, not really suited for " +
         "combat."
    ));
   sword -> set_hit(20);
   sword -> set_pen(15);
   sword -> move(TO);
   command("wield sabre");
}

do_ask(string what)
{
   object ob;
   string race, name, dum, s;
   
   if (!what || !parse_command(lower_case(what), environment(),
            " %o %s ", ob, s)) {
      return 0;
   }
   if (ob != TO) return 0;
   if (sscanf(s, "about %s", dum) == 1) s = dum;
   if (sscanf(s, "for %s",   dum) == 1) s = dum;
   
   race = capitalize(TP -> query_race_name());
   name = lower_case(TP -> query_name());
   
   if (s=="mansion") {
      TO->command("smile");
      TO->command("say You have found it, my dear " + race + "!");
      return 1;
   }
   if (s=="garden") {
      TO->command("smile");
      TO->command("say The garden has many hidden treasures.");
      TO->command("say Maybe you are strong enough to solve the mystery?");
      TO->command("say Beware of the vines, " + race + "!");
      return 1;
   }
   if (s=="mystery" || s=="witch") {
      TO->command("ponder");
      TO->command("say No one knows where the remains of the witch is.");
      TO->command("say Maybe you should try to find them, " + race + "!");
      return 1;
   }
   if (s=="skull") {
      TO->command("gasp");
      TO->command("whisper "+name+" The skull? Have you found it?! "+
         "Where is the rest of the remains?");
      return 1;
   }
   if (s=="skeleton" || s=="remains") {
      TO->command("whisper "+name+" The "+s+"? Have you looked in "+
         "the walls of the chapel?");
      return 1;
   }
   if (s=="quest" || s=="quests") {
      TO->command("ponder");
      TO->command("whisper "+name+" Yes, we have that too here.");
      TO->command("point east");
      return 1;
   }
   if (s=="help") {
      TO->command("say My dear "+race+", just ask me something.");
      TO->command("smile");
      return 1;
   }
   if (s=="butler") {
      TO->command("say At your service, "+race+"!");
      TO->command("bow to " + name);
      return 1;
   }
   if (s=="monster" || s=="monsters") {
      TO->command("say Kill them when you find them, my dear "
         +race+"!");
      TO->command("grin");
      return 1;
   }
   if (s=="legion") {
      TO->command("say I don't like it either, my dear "+race+"!");
      TO->command("sigh");
      return 1;
   }
   TO->command("say I'm sorry. I can't help you with that, "+race+".");
   TO->command("shrug");
   return 1;
}
