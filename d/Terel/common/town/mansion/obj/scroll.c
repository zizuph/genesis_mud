/* A readable scroll */
inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define MANSION "/d/Terel/common/town/mansion/"
#define HARD_TO_READ 31+random(2)
#define TP this_player()
#define TO this_object()
#define BSN(xx) break_string(xx + "\n", 70)
#define TXT "I had to kill the old king, since he was "+\
            "very reluctant to give me his daughter's hand. "+\
            "This foul act haunts me... I think I have seen "+\
            "his ghost... An old gypsy woman told me to write this "+\
            "scroll and put it where the deed was done... "+\
            "She said it would help to stop the haunting... "+\
            "Let's hope it will... "+\
            "She also told me to bury the body properly, the king "+\
            "now lies in a grave without name outside the chapel. "+\
            "      Marquis Rhieu Avenchir."

int has_key;
object find_q_ring(int q_no, object ob);

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
    has_key = 1;
}

read(string str)
{
    object ob, key, ring;

   notify_fail("Read what?\n");
   if (!str) return 0;
   if (!parse_command(str, environment(), "%o", ob)) return 0;
   if (ob != TO) return 0;

   write("You unfold the scroll and start to read it.\n");
   say(QCTNAME(TP) + " unfolds a scroll.\n");
   if (TP->query_skill(SS_LANGUAGE) >= HARD_TO_READ) {
        write("The scroll reads:\n" + BSN(TXT));
   } else {
       write("It's written in a language you don't understand.\n");
   }
    ring = find_q_ring(7, TP);
    if (has_key && ring && ring->query_prop("qstep") >= 1) {
        has_key = 0;
        seteuid(getuid(TO));
        key = clone_object(MANSION + "obj/coffin_key");
        key->add_prop("key_owner_7", TP->query_name());
        ring->change_prop("q_step", 2);
        write("As you unfold the scroll a key falls out of it.\n");
        if (key->move(TP)) {
            key->move(environment(TP));
        }
    }
   return 1;
}

object
find_q_ring(int q_no, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->query_prop("q_number") == q_no &&
            ob_arr[i]->query_prop("q_solver") == ob->query_name()) {
            r_ob = ob_arr[i];
        }
    }
    return r_ob;
}
