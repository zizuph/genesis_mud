/* A readable scroll */
inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define HARD_TO_READ 29+random(2)
#define TP this_player()
#define TO this_object()
#define BSN(xx) break_string(xx + "\n", 70)

init()
{
   ::init();
   add_action("read", "read");
}

create_object()
{
   set_name("scroll");
   set_short("old scroll of parchment");
   set_pshort("old scrolls of parchment");
   set_long("It's an old scroll of parchment.\n");
   set_adj("old");
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 100);
}

read(string str)
{
   object ob;

   notify_fail("Read what?\n");
   if (!str) return 0;
   if (!parse_command(str, environment(), "%o", ob)) return 0;
   if (ob != TO) return 0;

   write("You unfold the scroll and start to read it.\n");
   say(QCTNAME(TP) + " unfolds a scroll.\n");
   if (TP->query_skill(SS_LANGUAGE) >= HARD_TO_READ) {
       write("The scroll reads:\n" + BSN(
	     "Among the enchanted trees, I buried my treasure. " +
	     "I left it there, only to be guarded by the strange " +
	     "creatures who adore the trees. I have marked out the " +
	     "place with my symbol."
       ));
   } else {
       write("It's written in a language you don't understand.\n");
   }
   return 1;
}
