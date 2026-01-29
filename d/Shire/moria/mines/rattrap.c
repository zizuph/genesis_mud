/*
 * Converted room to a dirty tunnel. The rattrap is no longer needed now that 
 * the ogress is gone.
 * Finwe, June 2004
 */

#include "defs.h"
#include <filter_funs.h>

//int rat_alarm;

//void ratrace();

CONSTRUCT_ROOM {
    set_short("Dirty tunnel");
    set_long("This is a dirty tunnel used by orcs. Rats and mice come here " +
        "to feed on the scraps of food dropped by orcs. Leftovers lay " +
        "scattered on the floor and hordes of small dirty rats scamper " +
        "about. To the west is a white-clothed opening of pentagonal " +
        "cross-section, and to the south is a square door.\n");
   add_item(({"left-overs","floor"}),
      "The food is perhaps good for mice and rats, but not for you.");
   add_item("rats",
      "You turn to examine them more closely, but they run away.");
   add_item("opening",
      "Ah! The exit out. That was from where you entered this hole.");
   add_item(({"door","sign"}),
      "The sign says:\n  'Nothing ventured, nothing gained.'\n\n"+
      "Wonder what it means? Perhaps something dangerous is behind "+
      "the door? Well, if you turn, nothing is gained for sure.");
   EXIT("pyramid","west");
   EXIT("dwelling","south");
}

init() {
   ::init();
//   add_action("do_read","read");
//   init_race();
}

/*
int do_read(string str)
{
   if (str!="door" && str!="sign")
      return notify_fail("Read what?\n");
   write("The sign is written in ancient runes, and looks unintelligable.\n");
   say(QCTNAME(TP)+" reads the sign.\n");
   return 1;
}

ratrace() {
   object *all = FILTER_PLAYERS(all_inventory(TO));
   object ob;
     if (!sizeof(all))
     {
	remove_alarm(rat_alarm);
	rat_alarm = 0;
	return;
     }
   
   ob = all[random(sizeof(all))];
   ob->catch_tell("Some rats run over the room! One of them bites you on "+
      "the heel.\n");
   say("Some rats run over the room! One of them bites "+
      QTNAME(ob)+" on "+HIS_HER(ob)+" heel!\n", ({ob}));
   ob->catch_msg("OUCH!!\n");
   //   say(QCTNAME(ob) + " screams: OUCh!\\n",ob);
   ob->heal_hp(-5);
}

init_race()
{
   if (!rat_alarm)
      rat_alarm = set_alarm(3.0,20.0,ratrace);
}
*/
