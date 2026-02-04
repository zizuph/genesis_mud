/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#include <language.h>
#include <ss_types.h>

#define TO     this_object()
#define TP     this_player()
#define ETP    environment(TP)
#define SUBLOC "horn_subloc"

int worn=0;

public void
create_object()
{
   set_name("horn");
   set_adj("ancient");
   set_long("Carved and fashioned from the horn of some mysterious " +
      "mountain ram, it shimmers with silver inlay and sparkling " +
      "beryls.\n");
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VALUE, 100);
}

do_return(string str){
  if(str!="horn") return 0;
  if(worn) remove_horn(TP);
   write("The horn flashes with blue fire and is gone, as you send it back to its mysterious keeper.\n");
   this_object()->remove_object();
   return 1;
}
hear_herald(object who){
   if(MEMBER(who)) who->catch_msg("You hear the sound of an ancient horn, triumphant and mesmerising, echoing through the winds, heralding the arrival of someone.\n");
}

mystic(object who){
   if(MEMBER(who)) who->catch_msg("You hear an ancient and mysterious horn calling the ancient followers to battle!\n");
   if(present("protector_ring", who)) who->catch_msg("A horn is heard, echoing through the world, calling upon you to defend the ancient ways!\n");
   
}

do_herald(){
   if(TP->query_mana() < 5){
      write("You do not have the strength to sound the horn to herland anyone.\n");
      say(QCTNAME(TP) + " tries to sound a horn.\n");
      return 1;
   }
   write("You sound the horn, triumphantly, as a herald.\n");
   say(QCTNAME(TP) + " sounds an ancient horn, triumphant and mesmerising, heralding the arrival of someone.\n");
   map(users(), hear_herald);
   TP->add_mana(-5);
   return 1;
}


public void
hear(object who)
{
   if (who->query_wiz_level())
      return;
   if (who->query_met(TP)) {
      who->catch_msg("You hear the sound of a mysterious horn " +
         "echoing through the winds!\n");
   }
}

public int
do_sound(string str)
{
   notify_fail("Sound what?\n");
   if (!str || !id(str))
      return 0;
   
   if (TP->query_mana() <= 5 || random(TP->query_stat(SS_WIS)) < 10) {
      write("You sound the " + short() + " but you cannot gather the " +
         "strength needed to make it heard all over the realms.\n");
      say(QCTNAME(TP) + " sounds " + LANG_ADDART(short()) + ".\n");
      return 1;
   }
   TP->heal_mana(-5);
   write("You forcefully sound the " + short() + ".\n");
   say(QCTNAME(TP) + " sounds " + LANG_ADDART(short()) + ", it " +
      "rings loud and clear! A haunting melody of the ancient days!\n");
   map(users(), hear);
   return 1;
}

public int
do_battle(string str)
{
   notify_fail("Sound what?\n");
   if (!str || !id(str))
      return 0;
   
   if (TP->query_mana() <= 5 || random(TP->query_stat(SS_WIS)) < 10) {
      write("You sound the " + short() + " but you cannot gather the " +
         "strength to call those to battle.\n");
      say(QCTNAME(TP) + " attempts to sound a horn.\n");
      return 1;
   }
   write("You blast the horn, calling the followers of the ancients to battle!\n");
   say(QCTNAME(TP) + " sounds " + LANG_ADDART(short()) +
      " with a ferocious and dreadful sound, as if summoning ancient powers to battle!\n");
   TP->heal_mana(-5);
   map(users(), mystic);
   return 1;
}

public void
add_horn(object who)
{
   who->add_subloc(SUBLOC, TO);
   add_prop(OBJ_M_NO_SELL, "The " + short() +
      " cannot be sold while worn.\n");
   add_prop(OBJ_M_NO_DROP, "The " + short() +
      " cannot be dropped while worn.\n");
   worn = 1;
}

public void
remove_horn(object who)
{
   remove_prop(OBJ_M_NO_SELL);
   remove_prop(OBJ_M_NO_DROP);
   who->remove_subloc(SUBLOC);
   worn = 0;
}

public int
do_wear(string str)
{
   
   if (!str || !id(str)) return 0;
   
   if (worn) {
      write("You already wear the " + short() + ".\n");
   } else {
      write("You wear the " + short() + " at your side.\n");
      say(QCTNAME(TP) + " wears " + LANG_ADDART(short()) + " at " +
         TP->query_possessive() + " side.\n");
      add_horn(TP);
   }
   return 1;
}

public int
do_remove(string str)
{
   if (!str || !id(str)) return 0;
   
   if (!worn) {
      write("You are not wearing the " + short() + ".\n");
   } else {
      write("You remove the " + short() + ".\n");
      say(QCTNAME(TP) + " takes " + LANG_ADDART(short()) + " from " +
         TP->query_possessive() + " side.\n");
      remove_horn(TP);
   }
   return 1;
}

public void
leave_env(object from, object to)
{
   ::leave_env(from, to);
   
   if (from && living(from) && worn)
      remove_horn(from);
}

public void
init()
{
   ::init();
   add_action(do_wear,   "wear");
   add_action(do_remove, "remove");
   add_action(do_battle, "battlesound");
   add_action(do_herald, "herald");
   add_action(do_sound,  "sound");
   add_action(do_return, "return");
   
}


public string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;
   
   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "You are wearing " + LANG_ADDART(short()) +
   " at your side.\n";
   else
      str = capitalize(carrier->query_pronoun()) +
   " is wearing " + LANG_ADDART(short()) + " at " +
   carrier->query_possessive() + " side.\n";
   return str;
}
