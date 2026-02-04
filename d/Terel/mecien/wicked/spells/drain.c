/*
 * drain.c
 */

#include <comb_mag.h>
#include <macros.h>
#include "../wicked_defs.h"

nomask int
drain(string str)
{
     object who;
     string poss;

     NF("Drain whom of mana?\n");
     if (!str)
	  return 0;

     who = present(lower_case(str), ENV(TP));
     if (!who)
	  return 0;

     NF("Some force prevents your magic\n");
     if (NPMAGIC(who))
	  return 0;

     write("You cast drain on " + str + "\n");
     poss = TP->query_possessive();
     if (poss == "his")
	  poss = "him";
     
     say("Summoning a dark aura about " + poss  + "self, " + QCTNAME(TP) +
	 " extends " + TP->query_possessive() + " hands and then draws them" +
	 " in towards " + poss + "self\n");
     who->add_mana(-1 * who->query_mana());
     who->catch_msg(QCTNAME(TP) + " pulls life force from your mind.\n");
     who->catch_msg("You feel like your brain is corroding!\n");
     return 1;
}

     
