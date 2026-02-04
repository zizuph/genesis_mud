/*
 * chill.c
 */

#include <ss_types.h>
#include <comb_mag.h>
#include <macros.h>
#include "../wicked_defs.h"

nomask int
chill(string str)
{
     object who;
     string poss;
     int dt, ds;

     NF("Chill whom?\n");
     if (!str)
	  return 0;

     who = present(lower_case(str), ENV(TP));
     if (!who)
	  return 0;

     NF("Some force prevents your magic\n");
     if (NPMAGIC(who))
	  return 0;

     write("You cast chill on " + str + "\n");
     poss = TP->query_possessive();
     if (poss == "his")
	  poss = "him";
     
     tell_room(ENV(TP), QCTNAME(TP) + " stares coldly at " + QTNAME(who)
	       + ".\n", ({who, TP}));
     tell_room(ENV(TP), QCTNAME(who) + " seems weakened.\n", ({who, TP}));
     ds = 10 + random(10);
     dt = 100;
     who->add_tmp_stat(SS_STR, ds, dt);
     who->catch_msg(QCTNAME(TP) + " gives you a cold stare that chills you " +
		    "to the bone and leaves you feeling weakened.\n");
     return 1;
}

     
     
