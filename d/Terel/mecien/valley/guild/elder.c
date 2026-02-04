/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO  this_object()
#define TP  this_player()
#define OBJ (GUILD_DIR + "obj/")

public void
do_stuff()
{
    object staff;
    
    seteuid(getuid());
    staff = clone_object(OBJ + "staff");
    staff->add_prop(OBJ_M_NO_STEAL, 1);
    staff->move(TO);
    command("hold staff");
}

public void
create_monster()
{
   ::create_monster();
   
   set_name("avirigh");
   add_name("keeper");
   add_name("elder");
   set_adj("old");
   set_race_name("human");
   set_title("the Elder Keeper");
   set_short("Avirigh the Elder Keeper");
   set_long("He has a white beard, pale grey eyes and speaks very " +
            "softly. He wears the simple white mystics clothing.\n");

   set_stats(({15, 25, 60, 277, 265, 110}));
   set_alignment(999);
   set_appearance(64);
   set_hp(9000);
   set_mana(9000);

   add_prop("no_show_title", 1);
   set_all_hitloc_unarmed(50);
   add_prop(OBJ_M_NO_ATTACK, 1);
   add_prop(LIVE_I_ALWAYSKNOWN, "@@check");

   set_rank(MYSTIC_ARCHON);
   set_skill(SS_DEFENCE, MYSTIC_MAX_DEFENCE);
   set_skill(SS_SPELLCRAFT, MYSTIC_MAX_SPELLCRAFT);
   set_skill(SS_LANGUAGE, MYSTIC_MAX_LANGUAGE);
   set_piety(1000);
   set_blessed(1);
   enable_intro();
   enable_auto_reverence();
   
   set_chat_time(5);
   add_chat("The Ancient Ones are here with us...");
   add_chat("Pray here for a time");
   add_chat("Peace comes to those that pray");

   set_act_time(8);
   add_act("pray");
   add_act("tap staff");
   add_act("msmile");
   
   set_alarm(3.0, -1.0, do_stuff);
}

public int
check()
{
   if (MEMBER(TP)) return 1;
   return 0;
}

void
init_living()
{
   ::init_living();
   add_action("do_pray", "pray");
}

public int
do_pray(string str)
{
   int rank;
   object obj;

   if (!str) return 0;

   seteuid(getuid());

   if (!MEMBER(TP)) {
      if (str != "for guidance") return 0;
      if (TP->query_guild_member("occupational")) return 0;
      if (TP->query_guild_member("layman")) return 0;
      if (TP->query_alignment() < JOIN_LIM) {
          command("say Seek holiness!");
          return 1;
      }
      if (present(MYSTIC_BEADS, TP)) {
          command("say You have already received guidance.");
      } else {
         obj = clone_object(OBJ + "beads");
         obj->move(TP);
         write("A pale light shines upon you.\n");
         write("Something is given to you.\n");
      }
      return 1;
   }

   rank = TP->query_mystic_rank();
   if (str == "for glory") {
      if (rank < MYSTIC_NOVITIATE) {
         command("say Thou art not yet prepared to receive " +
                 "glory from Antiquity.");
         return 1;
      }
      if (present(MYSTIC_AMULET, TP)) {
         command("say Mystic! You already possess the token of glory.");
         return 1;
      }
      command("say I shall give thee the glory of Antiquity");
      command("msmile");
      obj = clone_object(OBJ + "amulet");
      obj->move(TP);
      write("A mysterious power descends upon you.\n");
      write("Something has been given to you.\n");
      return 1;
   }
   if (str == "for wisdom") {
      if (rank < MYSTIC_CIRCLE) {
         command("ms Thou art not yet prepared to receive " +
                 "wisdom from Antiquity.");
         return 1;
      }
      if (present(MYSTIC_STAFF, TP)) {
         command("ms Mystic! You already possess the token of wisdom.");
         return 1;
      }
      command("ms Receive the wisdom of Antiquity.");
      write("A strange and pale light shines down upon you.\n");
      obj = clone_object(OBJ + "staff");
      obj->move(TP);
      write("Something has been given to you.\n");
      return 1;
   }
   if (str == "for truth") {
      if (rank < MYSTIC_CANTOR) {
         command("ms Thou art not yet prepared to receive " +
                 "truth from Antiquity.");
         return 1;
      }
      if (present(MYSTIC_ICON, TP)) {
         command("ms Mystic, you already recognize the truth.");
         return 1;
      }
      command("ms Let Truth be known forever.");
      obj = clone_object(OBJ + "icon");
      obj->move(TP);
      write("An unbearable brightness shines from above.\n");
      write("A mysterious sensation overshadows you.\n");
      return 1;
   }
   if (str == "for mystery") {
      if (rank < MYSTIC_PATRIARCH) return 0;
      if (present(MYSTIC_CROWN, TP)) {
         command("ms Majesty, your mystery is already with you.");
         return 1;
      }
      obj = clone_object(OBJ + "crown");
      obj->move(TP);
      command("reverence " + TP->query_real_name());
      command("ms Hail, Ancient Patriarch!");
      write("The Ancients bless you.\n");
      write("Something has been given to you.\n");
      return 1;
   }
   return 0;
}
