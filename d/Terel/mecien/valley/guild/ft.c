/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";
inherit "/d/Terel/std/teacher";

#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <language.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"
#include "/d/Terel/common/teacher.h"

#define NF(str)        notify_fail(str)
#define TO             this_object()
#define TP             this_player()
#define ETO            environment(TO)
#define ETP            environment(TP)

public void set_up_skills();

public void
create_monster()
{
   ::create_monster();
   
   set_name("arhalan");
   add_name("teacher");
   set_adj("ominous");
   add_adj("wizened");
   set_race_name("human");

   set_title("Guardian of the Ancient Fire");
   set_long("Standing seven feet tall, this aged man holds in him some " +
            "ominous power that emataes forth, providing him with an " +
            "aura of dark and noble greatness. He wear a robe and gown " +
            "of deep purple, a black cope, letterd with silver runes " +
            "about the edges. His eyes sparkle a deep colour and his " +
            "hair is long and silvery black.\n");

   set_stats(({ 56, 88, 89, 115, 120, 100 }));
   set_skill(SS_FORM_DIVINATION, 100);
   set_skill(SS_ELEMENT_FIRE, 100);
   set_skill(SS_DEFENCE, 100);

   set_hp(9999);
   set_mana(9999);
   set_all_hitloc_unarmed(80);
   
   set_rank(MYSTIC_EXARCH);
   set_alignment(588);
   set_blessed(1);
   set_piety(567);
   
   enable_intro();
   enable_auto_hail();

   create_skill_raise();
   set_up_skills();
}

public int
do_present(string str)
{
    object lamp;

    if (str != "lamp") return 0;

    lamp = present(MYSTIC_LAMP, TP);
    if (lamp) {
        if (lamp->add_ember()) {
            TP->catch_msg(QCTNAME(TO) + " places your lamp within the urn.\n");
            tell_room(ETO, "A glowing light errupts from the urn.\n");
            command("say I have given thee the sacred ember");
            return 1;
        } else {
            command("say Thy lamp contains the sacred ember already");
            return 1;
        }
    }
    command("say Where is thy lamp?\n");
    return 1;
}

public void
init_living()
{
   ::init_living();
   add_action(do_present, "present");
   init_skill_raise();
}

public void
set_up_skills()
{
   string me, ot;

   me = "use the mystic fire"; ot = me;
   sk_add_train(SS_ELEMENT_FIRE,  ({me, ot}), 0, 0, MYSTIC_MAX_FIRE);
}

int
sk_improve(string str)
{
   string name;

   name = lower_case(TP->query_name());
   if (!MEMBER(TP)) {
      command("point at " + name);
      command("say You are not worthy to be teached.");
      return 1;
   }
   return ::sk_improve(str);
}
