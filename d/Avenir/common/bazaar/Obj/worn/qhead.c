// file name:    ~Avenir/common/bazaar/Obj/worn/qheadress
// creator(s):    Grace  May  1995
// last update:            
// purpose:       ornamentation for the lovely dancer
// note:                   
// bug(s):                 
// to-do:                                           

inherit "/std/armour";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_short("ornamental veil headress");
  set_name("headress");
  add_name(({"veil", "circlet"}));
  set_adj(({"veiled", "rose"}));
  set_long ("This headress is made of a jeweled circlet through "+
            "which a large, nearly transparent veil has been threaded. "+
            "The veil is rose-coloured and the circlet looks like it "+
            "is made of gold. Small ornaments dangle from the circlet.\n");

  add_item(({"ornament", "ornaments", "figurines", "figurine"}),
            "There are many small figurines, some carved of bone, others "+
            "made of painted wood or precious metals. They are so small "+
            "that it is difficult to determine what eac one represents.\n");
  add_item("veil", "It is rose-coloured and made of fine silk. It can be "+
           "raised and lowered over your face, though its sheerness is "+
           "poor for concealment.\n");
 

  set_ac(6);
  set_am(({ 0, 0, 0}));
  set_at (A_HEAD);
  add_prop(OBJ_I_VALUE,  1200);
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 500);
}

void
init()
{
   ::init();
      add_action("rfunc", "raise");
      add_action("lfunc", "lower");
}


int
rfunc(string arg)
{
    notify_fail("Do what with the veil?\n");
    if (!arg) return 0;

    if(!query_worn())
           {
              write("You need to be wearing the headress, first.\n");
              return 1;
            }

    if (arg == "veil" || arg == "headress")
       {
        TP->catch_msg("You raise the rose silk veil of the headress, "+
          "exposing your face.\n");
        say(QCTNAME(TP) +" raises the rose-coloured veil of "+ 
          TP->query_possessive() + " headress.\n");
       return 1;
       }
}

int
lfunc(string arg)
{
    notify_fail("Do what with the veil?\n");
    if (!arg) return 0;

    if(!query_worn())
           {
              write("You need to be wearing the headress, first.\n");
              return 1;
            }

    if (arg == "veil" || arg == "headress")
       {
        TP->catch_msg("You lower the rose silk veil of the headress, "+
          "covering your face.\n");
        say(QCTNAME(TP) +" lowers the rose-coloured veil of "+
          TP->query_possessive() + " headress over "+ 
          TP->query_possessive()+ "face.\n");
       return 1;
       }
}

