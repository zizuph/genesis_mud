/* On the boulders at the base of the waterfall.
** 
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/22/97   Zima          Created
**
** Notes:
** Special exits only:
**   "climb down" - climb down off boulders, back to river bank, wfpath5
**   "jump waterfall",
**   "enter waterfall" - jump into watefall, land in wfall1
** Players are "splashed/bashed" by the nearby watefall approx every 3 seconds.
**    if the player "sticks around" long enough, he will be "splashed off"
**    the boulder back onto the bank.
** Also, splash from waterfall "blinds" player, so "examine" and "look"
**   commands are overridden
*/
inherit "/std/room";
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "wfall.h"
 
/* prototypes */
int do_climb(string Parms);
int do_enter(string Parms);
int do_exa();
 
int splashing=0;
int  query_splash()         { return splashing; } /* for testing          */
void shutoff_splash(int i)  { splashing=0; }      /* emergency shutoff ;) */
 
/*
** CREATE_ROOM
*/
void create_room() {
   set_short("On the boulders at the base of the waterfall");
   set_long(
       "Water streams down into your face, deflected from the death-"+
       "promising crash of the water as it cascades over the side of the "+
       "mountains! You can barely keep your balance here, the boulders "+
       "being smooth and slippery, and the water constantly batting your "+
       "body in an attempt to send you to your death below! You can barely "+
       "breathe!\n");
   /* note: players can't look/examine here, so no add_items needed */
 
}
 
/*
** INIT - add commands
*/
void init() {
   ::init();
   add_action(do_climb,"climb");
   add_action(do_enter,"enter");
   add_action(do_enter,"jump");
   add_action(do_exa,  "$examine"); /* $ overrides aliased commands */
   add_action(do_exa,  "$look");
}
 
/*
** CLIMB - allows player to "climb down" off the boulders
*/
int do_climb(string Parms) {
   string *parm;
   object dest=(PROOM->get_this_object());
 
   if (!(Parms)) { write("Climb where?\n"); return 1; }
   parm=explode(Parms," ");
 
   if ((member_array("down",parm)>=0)||(member_array("off",parm)>=0)) {
      write("You climb down off the dangerous boulders onto the bank.\n");
      tell_room(TO,QCTNAME(TP)+" climbs down off the boulders onto "+
                               "the bank.\n", TP);
      tell_room(dest,QCTNAME(TP)+" climbs down off the boulders onto "+
                               "the bank.\n", TP);
      TP->move_living("M", PROOM);
      return 1;
   }
   write("You can only climb down from here!\n");
   return 1;
}
 
/*
** ENTER - allows player to "enter" or "jump" into waterfall
*/
int do_enter(string Parms) {
   string verb=capitalize(query_verb());
   string *parm;
   object dest=(F1ROOM->this_object());
 
   if (!(Parms)) { write(verb+" where?\n"); return 1; }
   parm=explode(Parms," ");
 
   if ((member_array("waterfall",parm)<0)&&(member_array("falls",parm)<0)) {
      write(verb+" where? Into the falls?\n");
      return 1;
   }
   write("You deftly jump off the boulder into the crushing cascade "+
         "of the falls!\n");
   tell_room(TO,QCTNAME(TP)+" jumps into the falls and disappears"+
                            " into the water!\n",TP);
   tell_room(dest,QCTNAME(TP)+" comes diving out of the falls into "+
                              " the cavern!\n", TP);
   TP->move_living("M", F1ROOM);
   write("You are drenched but safe!\n");
   return 1;
}
#include "wfboulders.ext"
