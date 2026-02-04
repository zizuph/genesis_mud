/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include "/d/Terel/include/Terel.h"
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define MANA_SPEECH 5
#define EN environment

mapping office_map;

int silver;
query_recover(){ return 0; }
query_value(){ return 0; }

string
query_auto_load()
{
   add_prop(OBJ_M_NO_DROP, 1);
   return MASTER;
}

void
create_armour()
{
   set_name("crown");
   add_name(MYSTIC_CROWN);
   set_adj("ancient");
   add_adj("silver");
   set_long(
      "It is an ancient silver crown, set with jade and encrusted "
      +"with chalcedony and amethysts.\n");
   set_at(A_HEAD);
   set_ac(10);
   add_prop(MYSTIC_ARMOUR, 1);
   add_prop(OBJ_M_NO_SELL, 1);
   
   office_map = ([ ]);
   FIX_EUID;
   restore_object(OFFICE_DATA);
}

void
enter_env(object dest, object old)
{
   ::enter_env(dest, old);
   if (!living(dest)) return;
   if (dest->query_mystic_rank() == MYSTIC_PATRIARCH) return;
   if (T_WIZ(dest)) return;
   dest->catch_msg("The crown disappears in a flash of light!\n");
   TO->remove_object();
   return;
}

void
init()
{
   ::init();
   if (TP == ETO) {
    add_action("treasury", "treasury");
      add_action("elect",  "elect");
      add_action("speech",  "speech");
      add_action("gaze",    "gaze");
      add_action("appoint", "appoint");
      add_action("sack",    "sack");
      add_action("resign",  "resign");
   }
}

treasury(){
   write("You gaze upon the hidden treasury of the shrine.\n");
  restore_object("/d/Terel/mecien/valley/guild/treasury");
   write("Its count is: " + silver + "\n");
 return 1;
}


elect(string str){
  object who;

   notify_fail("Elect who?\n");
   if(!str) return 0;
   
   who = find_living(str);
   
   notify_fail("The spirits can find no such person.\n");
   if(!who) return 0;
   
   notify_fail("This person is not of the Order.\n");
   if(!MEMBER(who)) return 0;
   
   notify_fail("This person is unworthy.\n");
   if(who->query_mystic_rank() != 5) return 0;
   
   TP->catch_msg("You call upon the great and holy spirits of Mystery down upon " + QCTNAME(who) + ".\n");
   who->catch_msg("A holy power enters you and you sense you have been chosen for some greatness.\n");
   tell_room(EN(TP), QCTNAME(TP) + " whispers a sacred prayer.\n", TP);
   who->set_skill(EXALT, 1);
   return 1;
}


int
gaze(string str)
{
   object ob, *obs;
   
   if (TP->query_mystic_rank() < MYSTIC_PATRIARCH) return 0;
   
   notify_fail("Gaze at whom?\n");
   if (!str) return 0;
   
   if (!parse_command(str, ETP, " [at] %l ", obs)) return 0;
   if (sizeof(obs) <= 1) return 0;
   ob = obs[1];
   if (ob == TP || !CAN_SEE(TP, ob)) return 0;
   
   TP->catch_msg("You gaze judgingly at " + QTNAME(ob) + ".\n");
   ob->catch_msg(QCTNAME(TP) + " gazes judgingly at you.\n");
   say(QCTNAME(TP) + " gazes judgingly at " + QTNAME(ob) + ".\n",
      ({ob, TP}));
   if (MEMBER(ob)) {
      if (ob->query_present_rank()) {
         TP->catch_msg(QCTNAME(ob) + " is worthy of " +
            ob->query_possessive() +
            " present mystic rank.\n");
       } else {
         TP->catch_msg(QCTNAME(ob) + " is not worthy of " +
            ob->query_possessive() +
            " present mystic rank.\n");
       }
      if (ob->query_mystic_rank() < MYSTIC_ARCHON) {
         if (ob->query_advance_rank()) {
            TP->catch_msg(QCTNAME(ob) +
               " is worthy enough to be consecrated.\n");
          } else {
            TP->catch_msg(QCTNAME(ob) +
               " is not worthy enough to be consecrated.\n");
          }
       } else {
         if (ob->query_advance_rank()) {
            TP->catch_msg(QCTNAME(ob) +
               " is worthy enough to be the new Patriarch.\n");
            } else {
            TP->catch_msg(QCTNAME(ob) +
               " is not worthy enough to be the new Patriarch.\n");
            }
       }
   }
   return 1;
}

public int
sack(string str)
{
   string what;
   object who, *obs;
   
   if (TP->query_mystic_rank() < MYSTIC_PATRIARCH) return 0;
   
   NF(capitalize(query_verb()) + " whom from what Office?\n");
   if (!str) return 0;
   
   if (!parse_command(str, ETP, " %l [from] %s ", obs, what))
      return 0;
   
   if (sizeof(obs) <= 1) return 0;
   
   who = obs[1];
   
   if (!CAN_SEE(TP, who)) return 0;
   
   if (!MEMBER(who)) {
      write("That person is not of the Order.\n");
      return 1;
   }
   
   if (member_array(what, OFFICES) == -1) {
      write("That is not a valid Office.\n");
      return 1;
   }
   
   if (office_map[what] == 0) {
      write("No one holds that Office.\n");
      return 1;
   }
   
   if (office_map[what] != who->query_real_name()) {
      write("That Mystic does not hold that Office.\n");
      return 1;
   }
   
   office_map[what] = 0;
   FIX_EUID;
   save_object(OFFICE_DATA);
   
   who->remove_skill(OFFICE);
   
   tell_room(ENV(ETO), QCTNAME(TP) + " removes " + QTNAME(who) +
      " from the Office of " + capitalize(what) + ".\n",
      ({TP, who}));
   
   TP->catch_msg("You remove " + QTNAME(who) + " from the Office of " +
      capitalize(what) + ".\n");
   
   who->catch_msg(QCTNAME(TP) + " removes you from the Office of " +
      capitalize(what) + ".\n");
   return 1;
}

public int
appoint(string str)
{
   int i;
   object who, *obs;
   string what, *office_holders;
   
   if (TP->query_mystic_rank() < MYSTIC_PATRIARCH) return 0;
   
   NF("Appoint whom to what Office?\n");
   
   if (!str) return 0;
   
   if (!parse_command(str, ETP, " %l [to] %s ", obs, what))
      return 0;
   
   if (sizeof(obs) <= 1) return 0;
   
   who = obs[1];
   
   if (!CAN_SEE(TP, who)) return 0;
   
   if (!MEMBER(who)) {
      write("That person is not of the Order.\n");
      return 1;
   }
   
   if (who == TP) {
      write("You cannot appoint yourself to any Office.\n");
      return 1;
   }
   
   i = member_array(what, OFFICES);
   if (i == -1) {
      write("That is not a valid Office.\n");
      return 1;
   }
   
   if (office_map[what] != 0) {
      if (office_map[what] == who->query_real_name())
         TP->catch_msg(QCTNAME(who) + " already holds that Office.\n");
      else
         write("That Office is currently filled by " +
         capitalize(office_map[what]) + ".\n");
      return 1;
   }
   
   office_holders = m_values(office_map);
   
   if (member_array(who->query_real_name(), office_holders) != -1) {
      TP->catch_msg(QCTNAME(who) + " presently holds an Office.\n");
      return 1;
   }
   
   office_map[what] = who->query_real_name();
   FIX_EUID;
   save_object(OFFICE_DATA);
   who->set_skill(OFFICE, i+1);
   
   tell_room(ENV(ETO), QCTNAME(TP) + " appoints " + QTNAME(who) +
      " to the Office of " + capitalize(what) + ".\n",
      ({TP, who}));
   
   TP->catch_msg("You appoint " + QTNAME(who) + " to the Office of " +
      capitalize(what) + ".\n");
   
   who->catch_msg(QCTNAME(TP) + " appoints you to the Office of " +
      capitalize(what) + ".\n");
   return 1;
}

int
speech(string msg)
{
   int i;
   object *ul;
   
   if (TP->query_mystic_rank() < MYSTIC_PATRIARCH) return 0;
   
   notify_fail("Speech what?\n");
   if (!msg) return 0;
   
   if (TP->query_mana() <= MANA_SPEECH) {
      write("You are too tired to speak to the Order.\n");
      return 1;
   }
   TP->add_mana(-MANA_SPEECH);
   
   if (TP->query_get_echo())
      write("You speak " + msg + ", to the Order.\n");
   else
      write("Ok.\n");
   
   ul = users();
   for (i=0; i<sizeof(ul); i++)
   if (MEMBER(ul[i]) && present(MYSTIC_RING, ul[i]) && ul[i] != TP)
      ul[i]->catch_msg("Your hear " + QTNAME(TP) + 
      " mystically: " + msg + "\n");
   
   return 1;
}

public int
resign(string str)
{
   object ob, *obs;
   
   if (TP->query_mystic_rank() < MYSTIC_PATRIARCH) return 0;
   
   notify_fail("Resign to whom?\n");
   if (!str) return 0;
   if (!parse_command(str, ETP, " 'to' %l ", obs)) return 0;
   if (sizeof(obs) <= 1) return 0;
   ob = obs[1];
   if (!CAN_SEE(TP, ob) || ob == TP || !MEMBER(ob)) return 0;
   
   notify_fail("You cannot wear the crown when resigning!\n");
   if (query_worn()) return 0;
   
   notify_fail("Only a Mystic Archon can become the new Patriarch!\n");
   if (ob->query_mystic_rank() != MYSTIC_ARCHON) return 0;
   
   notify_fail("That Mystic Archon is not yet worthy to become the " +
         "new Patriarch!\n");
   if (ob->query_advance_rank() == 0) return 0;
   
   TP->catch_msg("You put the " + short() + " on " + QTNAME(ob) +
      "'s head.\n");
   ob->catch_msg(QCTNAME(TP) + " puts the "+short()+" on your head.\n");
   ob->advance_rank(TP);
   TP->catch_msg(QCTNAME(ob) + " is now the new Patriarch.\n");
   ob->catch_msg("You are now the Patriarch of the Ancients.\n");
   TP->set_rank(MYSTIC_ARCHON);
   say(QCTNAME(TP) + " puts the " + short() + " on " + QTNAME(ob) +
      "'s head.\n", ({TP, ob}));
   move(ob);
   ob->command("wear crown");
   return 1;
}
