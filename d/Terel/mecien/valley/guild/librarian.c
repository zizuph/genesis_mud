/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define    TO     this_object()
#define    ETO    environment(TO)
#define    TP     this_player()

object key;

public void
create_monster()
{
   ::create_monster();
   
   set_name("herilnas");
   add_name("librarian");
   set_race_name("half-elf");
   set_living_name("herilnas");
   
   set_short("Herilnas the Librarian");
   set_title("the Librarian");
   set_long("A solemn half-elf, austere and gracious. He has taken the "
          + "vow of silence many years ago and kept it as part "
          + "of his rigorous discipline. He has hazel eyes and long "
          + "blonde hair. Garbed in a simple white robe and draped "
          + "with a gray mantle he attends the library.\n");
   set_stats(({ 23, 35, 30, 112, 102, 95}));
   set_hp(9000);
   set_mana(9000);
   set_appearance(86);
   set_alignment(345);
   add_prop(LIVE_I_ALWAYSKNOWN, "@@check");
   
   set_rank(MYSTIC_EXARCH);
   set_skill(SS_LANGUAGE, 90);

   set_all_attack_unarmed(20, 20);
   set_all_hitloc_unarmed(35);

   add_ask(({"for key", "for orator key", "for silver key"}), "@@key", 1);
   
   set_act_time(3);
   add_act("@@put_back");
   add_act("smile");
   add_act("@@wander");
   add_act("@@writes");

   set_cact_time(1);
   add_cact("@@mist_out");
   
   key = clone_object(GUILD_DIR + "office/ok");
   key->move(TO);
}

public int
check()
{
   if (MEMBER(TP)) return 1;
   return 0;
}

public string
key()
{
   if (TP->query_mystic_office() != OFFICE_ORATOR) return "confused";

   if (!key) return "shrug";
   
   if (environment(key) == TO) {
       command("nod " + TP->query_real_name());
       command("give " + key->short() + " to " + TP->query_real_name());
       return "msmile";
   }
   
   return "sigh";
}

public string
mist_out()
{
   tell_room(ETO, "A mist appears and " + QTNAME(TO) +
             " disappears within it.\n", TO);
   remove_object();
   return "";
}


public string
put_back()
{
   tell_room(ETO, QCTNAME(TO) + " returns some books to their place.\n", TO);
   return "";
}

public string
writes()
{
   tell_room(ETO, QCTNAME(TO) + " writes some notes in his journal.\n", TO);
   return "";
}

public string
wander()
{
   tell_room(ETO, QCTNAME(TO) + " wanders about the library.\n", TO);
   return "";
}
