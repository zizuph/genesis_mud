#include "kdefend.h"
#include <macros.h>

void kdefend_player_halt(object p) {
   tell_object(p, "You are no longer defending yourself.\n");
   p->blademaster_set_defense_inactive();
}

void kdefend_player(object p) {
   p->remove_prop(BM_PREPARE_DEFEND);
   if(!interactive(p)) {
      return;
   }

   p->blademaster_set_defense_active();
   tell_object(p, "You leap into a defensive stance.\n");
   tell_room(environment(p), QCTNAME(p) + " leaps into a defensive stance.\n", ({ p }));
   set_alarm(35.0, 0.0, &kdefend_player_halt(p));
}

int kdefend(string str) {
   if(this_player()->query_prop(BM_PREPARE_DEFEND)) {
      notify_fail("You are already preparing to defend yourself.\n");
      return 0;
   }

   if(this_player()->query_blademaster_defense_active()) {
      notify_fail("You are already defending yourself.\n");
      return 0;
   }

   this_player()->add_prop(BM_PREPARE_DEFEND, 1);
   set_alarm(3.0, 0.0, &kdefend_player(this_player()));
   write("You prepare to defend yourself.\n");
   return 1;
}
