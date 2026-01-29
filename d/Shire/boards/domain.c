inherit "/std/board";

#include <std.h>
#include "/d/Shire/common/defs.h"

#define MIDDLE_EARTH ({"Shire","Gondor","Rhovanion","Mordor"})
#define IN_MIDDLE_EARTH(x) member_array(SECURITY->query_wiz_dom(x->query_real_name()), MIDDLE_EARTH)

#define IS_IMPORTANT(x)  (SECURITY->query_wiz_rank(x->query_real_name()) >= WIZ_LORD)

#define IS_SPECIAL   ({"olorin","elessar"})
#define IS_EXCEPTION(x) member_array(x->query_real_name(), IS_SPECIAL)

#define MEMBER(x) (IN_MIDDLE_EARTH(x)  || IS_IMPORTANT(x) || IS_EXCEPTION(x))

int initialized;

create_board() {
   set_board_name(SHIRE_DIR + "boards/domain");
   set_num_notes(30);                /* Number of notes             */
   set_silent(0);                    /* Make noise when reading     */
   set_remove_rank(WIZ_NORMAL); /* Full wizards or higher      */
   set_remove_str("You are not allowed to do that");
}

init() {
   ::init();
   add_action("do_read", "read");   /* Control all actions */
   add_action("do_read", "mread");
   add_action("do_remove", "remove");
   add_action("do_note", "note");
   add_action("do_note", "gnote");
   add_action("do_store", "store");
}

do_read(str){
   if (!MEMBER(this_player())) {
      write("The great Nob Nar prevents you from reading this.\n"
          + "Only the pure of heart will be allowed to do so.\n");
      return 1;
   }
   return ::read_msg(str);
}

do_remove(str) {
   if (!MEMBER(this_player())) {
      write("The shadow of ancient power emerges.\n"
          + "You are punished for your sabotage attempt.\n"
          + "Nob Nar's anger bears heavy on your shoulders.\n");
      return 1;
   }
   if (SECURITY->query_wiz_dom(this_player()->query_real_name()) == "Shire")
      return ::remove_msg(str);
   write("Nob Nar will only let his closest do this.\n");
   say("Nob Nar stops an illegal removal of a note from his board.\n");
   return 1;
}

do_note(str){
   if (!MEMBER(this_player())) {
      write("A loud voice booms: Do not touch this sacred board, infidel!\n"
          + "It seems that only the pure of heart are allowed to write here.\n");
      return 1;
   }
   return ::new_msg(str);
}

do_store(str){
   if (!MEMBER(this_player())) {
      write("The great Nob Nar lets you neither read nor save a message.\n"
          + "Only the pure of heart will be allowed to do so.\n");
      return 1;
   }
   return ::store_msg(str);
}
