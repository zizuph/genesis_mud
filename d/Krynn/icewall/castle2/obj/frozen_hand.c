inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include "/d/Krynn/icewall/castle2/local.h"

int ring_found = 0;  /* 0 = ring NOT found yet */

void
create_object()
{
   set_name(({"arm", "frozen arm","black frozen arm"}));
   set_short("black frozen arm");
   set_long("@@long_descr");

   add_adj("black");
   add_adj("frozen");

   add_item(({"fingers","finger","band","silver band"}),"@@finger_descr");
   
   add_prop(OBJ_I_NO_GET, "The rest of the corpse is deep in the ice!\n");
   add_prop(OBJ_I_NO_GIVE, "Now how would you do it?\n");
   add_prop(OBJ_M_NO_STEAL, "It is frozen to the ground...\n");
 
   seteuid(getuid(TO));
}


string
long_descr()
{
   string ret_str = "This is a black, stiff, frozen arm sticking out " +
                    "from the solid ice. By the mummiefied look of it, " +
                    "it is hard to decide its origin, but if you had to, " +
                    "you would bet human. The arm had been recently gnawed " +
                    "upon";

   if(!ring_found)
      ret_str += ". On one of the frozen fingers, you notice a shimmering " +
                 "band of silver.";
   if(ring_found)
      ret_str += " and has only four fingers left.";

   ret_str += "\n";

   return ret_str;
}


string
finger_descr()
{
   if(ring_found)
      return "The hand lacks its little finger. Something tore it off.\n";

    return "Upon the little finger of the frozen hand, you notice a silver " +
     "ring. Undulled and shiny after Gods know how long, it must be magical. " +
     "The metal band appears frozen to the hand. One would have to break off " +
     "a finger to retrieve it... but does one wish to despoil the dead?\n";
}

int
break_descr(string str)
{
  if (str == "little finger from arm" ||
        str == "finger from arm" ||
        str == "finger from hand" ||
        str == "little finger from hand" ||
        str == "finger from corpse" ||
        str == "little finger from corpse")
     {
       if(present("roc",environment(TO)))
          {  
            say("The roc screeches angrily and moves to block " +
             QTNAME(TP) + " as " + HE(TP) + " reaches for the " +
             "frozen arm.\n");
            write("The roc screeches angrily and moves to block you " +
             "as you try to reach for its meal.\n");   
      
            return 1;
          }


       if(!ring_found)
       {
           write("Hoping the owner of the hand will not mind it, you " +
                 "steel yourself and work the frozen finger backward " +
                 "until it snaps! The silver band falls into your hand.\n");
           ring_found = 1;
           tell_room(E(TO), QCTNAME(TP) + " breaks off a finger " +
                     "from the black frozen arm, retrieving a silver ring.\n", TP);
           if(!random(3))
           {
               clone_object(UNIQUE(OBJK + "nice_ring",5,OBJK + "ring2"))->move(TP);
           }
           else
           {
               clone_object(OBJK+"ring2")->move(TP);
           }
           return 1;
       }
       
       write("There is no point in further despoilment of the dead.\n");
       return 1;
 
 
      }

     write("Break what from what?\n");
     return 1;

}


void
init()
{
    ::init();

    add_action(break_descr, "break");
}     
