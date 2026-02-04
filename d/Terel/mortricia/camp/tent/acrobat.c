/*
 *   A teacher. Mortricia 930304.
 *
 *   If the teacher is closed you can toggle this by doing,
 *   > Call teacher close_open
 *
 */
inherit "/d/Terel/std/monster";
inherit "/d/Terel/std/teacher";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define NF(str)            notify_fail(str)
#define TP                 this_player()
#define TO                 this_object()
#define CLOSED             0      /* 1 = closed,   0 = open.  */
#define ALIGN              0

public void set_up_skills();

int closed = CLOSED;

public void
create_monster()
{
   ::create_monster();
   
   set_name("treskar");
   add_name("acrobat");
   add_name("teacher");
   set_adj("springy");
   set_race_name("human");
   set_long("It's a springy human. He looks almost like an acrobat. " +
            "Maybe he can share some of his skills with you.\n");
   set_stats(({40,40,40,30,30,40}));
   set_hp(9999);
   set_mana(9999);
   set_gender(0);
   set_alignment(ALIGN);
   set_all_hitloc_unarmed(30);
   set_all_attack_unarmed(10, 10);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_ACROBAT, 40);
   set_skill(SS_CLIMB, 40);
   set_skill(SS_AWARENESS, 40);
   set_skill(SS_UNARM_COMBAT, 40);
   
   enable_intro();

   add_prop(OBJ_S_WIZINFO, "@@wizinfo");

   create_skill_raise();
   set_up_skills();
}

public void
init_living()
{
   ::init_living();
   init_skill_raise();
}

public string
wizinfo() {
   return "If there should be due cause to close down the teacher, do so\n"+
      "by typing:  Call teacher close_open\n"+
      "This will temporarily prevent mortals from learning. After a\n"+
      "reboot, the teacher will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n  Mortricia.\n";
}

public string
close_open()
{
   if (closed) {
      closed = 0;
      return "  **The teacher is now open**";
   }
   closed = 1;
   return "  **The teacher is now closed**";
}

public int
query_closed()
{
    return closed;
}

public void
set_up_skills()
{
    string me, ot;

    me = "climb"; ot = me;
    sk_add_train(SS_CLIMB,      ({me, ot}),     0, 0, 30 );
    me = "use acrobatics"; ot = me;
    sk_add_train(SS_ACROBAT,    ({me, ot}),     0, 0, 20 );
}

public int
sk_improve(string str)
{
   if (closed) {
       command("say Sorry, I don't have time for that now.");
       return 1;
   }
   return ::sk_improve(str);
}

