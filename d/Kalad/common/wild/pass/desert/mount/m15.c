#pragma strict_types
#include "/d/Kalad/defs.h"

inherit "/d/Kalad/room_std";

/* by Antharanos */
// Polished by Ibun 2007-05-11

void
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("At the base of a pinnacle of rock");
   set_long("Among this apparently endless sea of rock high " +
       "in these mountains is a gigantic pinnacle of rock that " +
       "rises above it all like an arrow pointed towards the " +
       "heavens. Harsh, almost cold winds rush through the " +
       "surroundings, lashing everything within its path. A " +
       "narrow, winding trail strewn with rocks winds its way " +
       "among the barren landscape. Above you, the previously " +
       "blinding rays of the Kaladian sun seem somehow, " +
       "lessened in their intensity.\nDespite these sensory " +
       "distractions, an underlying odor, one that is not " +
       "quite identifiable, pervades the area.\n");
   add_item(({"slate-grey rocks","rocks","rock"}),"Large, featureless "+
      "stones that have fallen from the mountains.\n");
   add_item(({"narrow trail","winding trail","trail"}),"A rugged path "+
      "that winds its way through this rocky terrain.\n");
   add_item(({"base","mountains","mountain"}),"The dark, grey peaks "+
      "rise high above you, daunting in their size.\n");
   add_item(({"kaladian sun","sun"}),"Its fierce rays nearly " +
       "blind you!\n");
   add_item(({"edge","steep cliff","cliff"}),"A rocky precipice "+
      "overlooking the rugged terrain around you.\n");
   add_item(({"gigantic pinnacle","pinnacle"}),"An edifice of rock that "+
      "rises at a sharp ninety degree angle to the surrounding " +
      "mountain plateau.\n");
   add_item(({"mountain plateau","plateau"}),"A flat area in these " +
       "otherwise mountainous surroundings.\n");
   add_exit(CPASS(desert/mount/m14),"northwest",0,4);
   add_exit(CPASS(desert/mount/p1),"up","@@check_feather",5);
   add_exit(CPASS(desert/mount/m16),"east",0,4);
}

int
check_feather()
{
    object *ob;
    int i;

    if(TP->query_skill(SS_CLIMB) < 50)
    {
        write("This rock is far to difficult to climb for you.\n");
        return 0;
    }
   ob = deep_inventory(TP);

   for(i = 0; i < sizeof(ob); i++)
       if(ob[i]->id("sacredfeatherofnathla"))
       {
           write("You begin to scale the sheer face of the pinnacle " +
               "of rock, when suddenly you feel your body become " +
               "lighter than air and float upwards along the length " +
               "of the pinnacle.\n");
           say(QCTNAME(TP) + " begins to scale the sheer face of " +
               "the pinnacle of rock, when suddenly " +
               TP->query_pronoun() + " begins to float upwards and " +
               "out of sight.\n");
           return 0;
        }
   write("You try to climb up the pinnacle of rock but fail miserably.\n");
   say(QCTNAME(TP) + " tried to climb up the pinnacle of rock but " +
       "fails miserably.\n");
   return 1;
}

