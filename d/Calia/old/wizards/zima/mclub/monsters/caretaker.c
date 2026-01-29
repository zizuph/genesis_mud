/* Mclub - Caretaker of the Memorial of the Ancient Ones
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           7/29/95   Created - gives key to members; answers questions
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"grammateus","caretaker","human"}));
    set_adj(({"lean","elderly"}));
    set_race_name("human");
    set_short("lean elderly human");
    set_pshort("lean elderly humans");
    set_long(
        "He is a lean elderly human dressed in a dirty tunic. He "+
        "looks as if he might be the caretaker of the shrine.\n");
 
    set_restrain_path(ROOM_DIR);
    set_monster_home(ROOM_DIR+"shoak1");
    set_random_move(60);
 
    set_default_answer("The lean elderly human says: I don't know. I'm "+
                       "just the caretaker around here.\n");
    add_ask(({"shrine","about shrine"}),
            "say It was built in memory of an ancient order that "+
            "died out long ago.",1);
    add_ask(({"order","ancient order","about order","about ancient order"}),
            "say I believe it was called the Ancient Order of the "+
            "Mystics.",1);
    add_ask(({"mystics","about mystics"}),
            "say Yes, I remember them. They were a pretty secretive bunch. "+
            "Most of 'em didn't say much, but you didn't want to "+
            "cross one.",1);
    add_ask(({"club","about club"}),
            "say You'll have to talk to one of the members about that.",1);
    add_ask(({"oak","oaks","about oak","about oaks"}),
            "say The oaks have been here almost as long as this hill "+
            "I'd imagine. Not even drought seems to hurt 'em.",1);
    add_ask(({"key","about key","for key","keys","about keys","for keys"}),
              "@@ask_key",1);
 
    set_stats(({ 30, 30, 30, 30, 30, 30})); /* STR,DEX,CON,INT,WIS,DIS */
    set_hp(10000);
    set_alignment(0);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
string ask_key() {
   object TP=this_player();
   object TO=this_object();
   object key;
   if (InMClub(TP)) {
      key=clone_object(OBJ_DIR+"btkey");
      key->move(TO);
      TO->command("give key to "+(lower_case(TP->query_name())));
      return "say Here you go. Don't loose it.";
   }
   else return "say Sorry, I don't have any keys.";
}
