/*
**  ARGOS - Metro - Press where olives can be pressed into oil and grapes
**                        into grape juice
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       8/24/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  OLIVES 1
#define  GRAPES 2
#define  CONTAINS_GRAPES  "are grapes"
#define  CONTAINS_OLIVES  "are olives"
#define  CONTAINS_NOTHING "is nothing"
string bin_contents=CONTAINS_NOTHING;
 
void make_press() {
   object press=clone_object(OBJ_DIR+"press");
   press->move(THIS);
   tell_room(THIS,"There is a large wooden press in the center of the room.\n");
}

create_room() {
   set_short("The Royal Press of Argos");
   set_long(
      "This is the Royal Press of Argos, a service provided free of "+
      "charge to the public by the King. The room is clean except the "+
      "floor looks rather stained. The only ornamentation is a blue "+
      "banner which hangs on the northern wall.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("floor",
      "It is stained with grape juice and looks a little slippery in "+
      "spots. Someone must have spilled something here.\n");
   add_item("banner",
      "It is a banner of blue silk bearing the arms of Argos, a shield "+
      "emblazoned with a rampant winged horse surmounted by a crown with "+
      "three jewels.\n");
   /* desc. of press on press object; detailed descr. here */
   add_item("frame",
      "The frame of the press is just a sturdy squared wooden box. "+
      "There is a plaque nailed to it.\n");
   add_item("bin","@@exa_bin");
   add_item("lever",
      "It is a large lever which can be pulled to press the contents "+
      "of the bin.\n");
   add_item("spigot",
      "It is a long tube through which the liquid pressed from the "+
      "fruit flows out.\n");
   add_item(({"plaque","instructions"}),
      "It is nailed to the frame of the press. It has instructions on "+
      "it.\n");
   add_cmd_item(({"plaque","instructions"}), "read",
      "+---------------------------------------+\n"+
      "| Instructions for pressing olives:     |\n"+
      "| - You must be holding an empty vial   |\n"+
      "| - place olives in bin (1 handful)     |\n"+
      "| - pull lever                          |\n"+
      "|                                       |\n"+
      "| Instructions for pressing grapes:     |\n"+
      "| - You must be holding an empty bottle |\n"+
      "| - place grapes in bin (1 bunch)       |\n"+
      "| - pull lever                          |\n"+
      "| Note: ask a Pharosian priest to bless |\n"+
      "|       the juice to get wine.          |\n"+
      "+---------------------------------------+\n");
 
 
   add_exit(ROOM_DIR+"troad10","east");
   add_exit(ROOM_DIR+"croad15","south");
   make_press();
}
 
string exa_bin() {
   return (
   "It is a large squared funnel on top of the press where the fruit to be "+
   "pressed is placed. There "+bin_contents+ " in the bin.\n");
}
 
/* allows player to 'place grapes in bin' or 'place olives in bin' */
/* subtracts one from a heap object, removes if only one left */
void decrement_heap(object heap) {
   int num;
   if (!(heap)) return;
   num=heap->num_heap();
   if (num==1)
      heap->remove_object();
   else
      heap->set_heap_size(num-1);
}
 
int place(string Parms) {
   object Tp=this_player();
   object Tr=this_object();
   object grapes=present(ARGOS_GRAPES,Tp);
   object olives=present(ARGOS_OLIVES,Tp);
   int    fruit=0; /* 1=olives, 2=grapes */
 
   /* check parameters to see if putting olives or grapes in bin */
   if (!(Parms)) { write("Place what in what?\n"); return 1; }
 
   if (Parms=="olives in bin")
      fruit=OLIVES;
   else if (Parms=="grapes in bin")
      fruit=GRAPES;
   else
      { write("Place what in what?\n"); return 1;}
 
   /* make sure player has the item */
   if ((fruit==GRAPES)&&(!(grapes)))
      { write("You don't have any Argosian grapes.\n"); return 1; }
   if ((fruit==OLIVES)&&(!(olives)))
      { write("You don't have any Argosian olives.\n"); return 1; }
 
   /* make sure bin is empty */
   if (bin_contents != CONTAINS_NOTHING)
      { write("There "+bin_contents+" in the bin already.\n"); return 1; }
 
   /* all is well, fill the bin */
   if (fruit==OLIVES) {
      write("You place some olives in the bin of the press.\n");
      tell_room(Tr,QCTNAME(Tp)+" places some olives in the bin of the "+
                   "press.\n",Tp);
      decrement_heap(olives);
      bin_contents=CONTAINS_OLIVES;
      }
   else { /* grapes */
      write("You place some grapes in the bin of the press.\n");
      tell_room(Tr,QCTNAME(Tp)+" places some grapes in the bin of the "+
                   "press.\n",Tp);
      decrement_heap(grapes);
      bin_contents=CONTAINS_GRAPES;
   }
   return 1;
}
 
/* allows player to pull the lever on the press                       */
/*   if nothing in the bin, does nothing                              */
/*   if grapes in bin and has empty bottle, fills bottle with juice   */
/*   if grapes in bin and does not have bottle, juice runs on floor   */
/*   if olives in bin and has empty vial, fills vial with oil         */
/*   if olives in bin and does not have vial, oil runs on floor       */
int pull(string Parms) {
   object Tp=this_player();
   object Tr=this_object();
   object bottle=present(ARGOS_EMPTY_BOTTLE,Tp);
   object vial  =present(ARGOS_EMPTY_VIAL,Tp);
 
   /* check parameters */
   if (!(Parms))       { write("Pull what?\n"); return 1; }
   if (Parms!="lever") { write("Pull what?\n"); return 1; }
 
   /* must have something in the bin */
   if (bin_contents==CONTAINS_NOTHING) {
      write("But the bin is empty. There is nothing to press.\n");
      return 1;
   }
 
   /* OK, something in bin, so press it */
   write("You pull down on the lever and the press creaks.\n");
   tell_room(Tr,QCTNAME(Tp)+" pulls down on the lever of the press "+
                "and it creaks.\n",Tp);
 
   /* now what happened to contents of bin? */
   if (bin_contents==CONTAINS_GRAPES)
      if (bottle) {
         /* presses grapes and has an empty bottle, so fill bottle */
         write("You hold the empty bottle under the spigot and fill it "+
               "with grape juice.\n");
         tell_room(Tr,QCTNAME(Tp)+" holds an empty bottle under the "+
                      "spigot of the press and the bottle fills with "+
                      "grape juice.\n",Tp);
         bottle->remove_object();
         bottle=clone_object(OBJ_DIR+"grape_juice");
         bottle->move(Tp);
         }
      else {
         /* presses grapes but has no bottle, so juice runs on floor */
         tell_room(Tr,"Grape juice runs out of the spigot of the press "+
                      "onto the floor!\n");
      }
   else   /* bin has olives */
      if (vial) {
         /* presses olives and has an empty vial, so fill vial */
         write("You hold the empty vial under the spigot and fill it "+
               "with olive oil.\n");
         tell_room(Tr,QCTNAME(Tp)+" holds an empty vial under the "+
                      "spigot of the press and the vial fills with "+
                      "olive oil.\n",Tp);
         vial->fill_vial();
         }
      else {
         /* presses olives but has no vial, so oil runs on floor */
         tell_room(Tr,"Olive oil runs out of the spigot of the press "+
                      "onto the floor!\n");
      }
   bin_contents=CONTAINS_NOTHING; /* bin empty now */
   return 1;
}
 
void init() {
   ::init();
   add_action("place","place");
   add_action("pull","pull");
}
