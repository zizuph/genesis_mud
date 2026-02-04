/*
 *   A teacher. Mortricia 930304.
 *
 *   If the teacher is closed you can toggle this by doing,
 *   > Call teacher close_open
 *
 */

inherit "/std/monster";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Terel/common/teacher.h"

#define NF(str)            notify_fail(str)
#define TP                 this_player()
#define TO                 this_object()
#define BS(xxx)            break_string(xxx,70)
#define BSN(xxx)           break_string(xxx+"\n",70)
#define CLOSED             0      /* 1 = closed,   0 = open.  */
#define ALIGN              0

int closed;

create_monster() { 
   
   closed = CLOSED; 
   
   set_name("teacher");
   set_short("old human");
   set_adj("old");
   set_long(BSN(
       "It's an old human. He looks almost like a teacher. "+
       "Maybe he can share some of his skills with you."
   ));
   set_race_name("human");
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
    set_skill(SS_ELEMENT_DEATH, 90);
   
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
   create_skill_raise();
   set_up_skills();
}

init_living() {
   ::init_living();
   init_skill_raise();
}

wizinfo() {
   return ("If there should be due cause to close down the teacher, do so by\n"+
      "typing:  Call teacher close_open\n"+
      "This will temporarily prevent mortals from learning. After a\n"+
      "reboot, the teacher will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n  Mortricia.\n");
}

enter_inv(ob, from) {
   ::enter_inv(ob, from);
   
   if (!interactive(ob) || !closed)
      return;
   
   if (ob->query_wiz_level()) 
      write("\n\nWARNING!\nYou shouldn't be here. "+
      "I'm doing some work on the teacher.\n");
   else {
      write("The teacher is asleep. Come back later.\n");
      ob->move(environment(TO));
   }
}

close_open() {
   if (closed) {
      closed = 0;
      return "  **The teacher is now open**";
   }
   closed = 1;
   return "  **The teacher is now closed**";
}

query_closed() { return closed; }

void
set_up_skills()
{
    string me, ot;
   
    me = "use knives"; ot = me;
    sk_add_train(SS_WEP_KNIFE,      ({me, ot}),     0, 0, 20 );
    me = "use the elements of death"; ot = me;
    sk_add_train(SS_ELEMENT_DEATH,    ({me, ot}),     0, 0, 80 );
}
