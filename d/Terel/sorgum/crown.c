/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include "/d/Terel/include/Terel.h"
inherit "/std/armour";

#include <formulas.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define OFFICE_DATA "/d/Terel/mecien/valley/guild/offices"

#define OFFICES ({"novices", "orator", "seal"})

mapping office_map;

query_recovery(){ return 0; }

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
        "It is an ancient silver crown, set with jade and encrusted\n"
        +"with chalcedony and amethysts.\n"
    );
    set_at(A_HEAD);
    add_prop("mystic_armour", 1);
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
        add_action("speech", "speech");
	add_action("gaze",   "gaze");
	add_action("appoint", "appoint");
        add_action("resign", "resign");
    }
}

int
gaze(string str)
{
   object ob;

   if (TP->query_mystic_rank() < MYSTIC_PATRIARCH) return 0;

   notify_fail("Gaze at whom?\n");
   if (!str) return 0;

   if (!parse_command(str, ETP, " [at] %o ", ob)) return 0;
   if (!living(ob) || ob == TP) return 0;

   TP->catch_msg("You gaze at " + QTNAME(ob) + ".\n");
   ob->catch_msg(QCTNAME(TP) + " gazes at you.\n");
   say(QCTNAME(TP) + " gazes at " + QTNAME(ob) + ".\n", ({ob, TP}));
   if (MEMBER(ob)) {
      if (ob->query_present_rank()) {
	 TP->catch_msg(QCTNAME(ob) + " is worthy of " + ob->query_possessive() +
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
appoint(string str)
{
    string what;
    object who;
    string *office_holders;

    if (!str) {
	NF("Appoint who?\n");
	return 0;
    }

    if (!parse_command(str, ENV(ETO), "%o [to] %s", who, what)) {
	NF("Appoint whom to what office?\n");
	return 0;
    }

    
    if (!MEMBER(who)) {
	TP->catch_msg("That person is not of the order.\n");
	return 1;
    }

    if (member_array(what, OFFICES) == -1) {
	TP->catch_msg("That is not a valid office.\n");
	return 1;
    }

    if (office_map[what] != 0) {
	if (office_map[what] == who->query_real_name()) 
	    TP->catch_msg(QCTNAME(who) + " already holds that office.\n");
	else
	    TP->catch_msg("That office is currently filled by " +
			  capitalize(office_map[what]) + ".\n");
	return 1;
    }

    office_holders = m_values(office_map);

    if (member_array(who->query_real_name(), office_holders) != -1) {
	TP->catch_msg(QCTNAME(who) + " presently holds an office.\n");
	return 1;
    }

    office_map[what] = who->query_real_name();
    FIX_EUID;
    save_object(OFFICE_DATA);
    
    tell_room(ENV(ETO), QCTNAME(TP) + " appoints " + QCTNAME(who) +
	      " to the office of " + what + ".\n", ({TP, who}));
    
    TP->catch_msg("You appoint " + QCTNAME(who) + " to the office of " +
		  what + ".\n");
    
    who->catch_msg(QCTNAME(TP) + " appoints you to the office of " +
		   what + ".\n");
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

   ul = users();
   for (i=0; i<sizeof(ul); i++)
       if (MEMBER(ul[i]) && present(MYSTIC_RING, ul[i]))
	   ul[i]->catch_msg("Your hear " + QTNAME(TP) +
			    " mystically: " + msg + "\n");
   return 1;
}

public int
resign(string str)
{
   object ob;

   if (TP->query_mystic_rank() < MYSTIC_PATRIARCH) return 0;

   notify_fail("Resign to whom?\n");
   if (!str) return 0;
   if (!parse_command(str, ETP, " 'to' %o ", ob)) return 0;
   if (!ob || !living(ob) || ob == TP || !MEMBER(ob)) return 0;

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
