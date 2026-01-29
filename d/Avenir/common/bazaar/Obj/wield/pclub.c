
//  /bazaar/Obj/wield/pstick.c
// creator(s): Ilyian
// last update: May 1995
// purpose: Stick for the peasants of the bazaar
// note: modelled after Boriska's random objects
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Avenir/common/common.h"

string *randadj;
string *randtype;
string thisadj;
string thistype;

create_weapon ()
{
  randadj = ({ "battered", "long", "thick", "round", "wooden",
               "heavy", "light", "short" });
  randtype = ({ "stick", "cudgel", "cane", "branch"});

  thisadj = randadj[random(sizeof(randadj))];
  thistype = randtype[random(sizeof(randtype))];

  set_name(thistype);
   set_short(thisadj+" "+thistype);
  set_adj(thisadj);
  add_name ("_peasant_stick_in_bazaar_");

  set_long("This "+thistype+" is pretty shoddy, but it might "
          +"be able to do a bit of damage. You can swing it back "
          +"and forth if you are bored.\n");

  add_prop (OBJ_I_WEIGHT, 3000 );
  add_prop (OBJ_I_VOLUME, 2000 );

  set_hit (4); 
  set_pen (5);

  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hands(W_LEFT);
  set_likely_dull(18);
  set_likely_corr(0);
  set_likely_break(14);
}

void
init()
 {
   ::init();
    add_action("swing_func", "swing");
 }

int
swing_func(string arg)
 {
    string str;

    if(arg == thistype | arg == "stick")
       {
       write("You swing the "+short()+" back and forth lazily.\n");
       say(QCTNAME(TP)+" swings "+
            POSSESS(TP)+" "+short()+" back and forth lazily.\n");
      return 1;
        }
  notify_fail("Swing what?\n");
 }

