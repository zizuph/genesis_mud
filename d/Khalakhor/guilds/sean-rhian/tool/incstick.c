/* A stick of incense
** This is a stick of incense used in rites of Sean-Rhian. A player can 
** can light the stick or extinguish it. When burnt out, the stick disappears.   
**
** History:
** Date         Coder         Action
** -------- ----------------  -----------------------------------------
** 4/5/07  Zima              Created
*/
inherit "/std/object";
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
 
#define  UNLIT          0
#define  LIT            1
#define  SMOKE_TIME    10.0

//
// global variables
//
static int    amt      = 12;     // amt of incense left to burn
static int    lit      = 0;      // is the stick lit?

// 
// simple query functions for global variables
//
int    query_amt()         { return amt; }
int    query_lit()         { return lit; }
 
//
// update_desc - updates the description when it is lit/extinguished
//
void update_desc(int new_lit) {
   string short, pshort;
   string long="It is a long, thin stick coated with powdered incense. ";
   
   lit = new_lit;
   switch (lit) {
      case UNLIT: long+="It can be lit to burn and release aromatic smoke.\n";
                 remove_adj("smoking"); remove_adj("burning");
                 short  = "stick of incense";
                 pshort = "sticks of incense";
                 break;
      case LIT:  long+="It is burning with a small glow, releasing fragrant "+
                       "smoke. You can wave the stick to increase its output\n";
                 short="smoking stick of incense";
	  	 pshort="smoking sticks of incense";
                 add_adj("smoking"); add_adj("burning");
   }
   set_long(long);
   set_short(short);
   set_pshort(pshort);
} // update_desc()
 
//
// create_object
//
void create_object() {
   set_name("stick");
   add_name(SR_STICK_INCENSE);
   add_name("stick of incense");
   add_name("incense");
   update_desc(UNLIT);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,10);
   add_prop(OBJ_I_VALUE,0);  
} // create_object()

//
// do_smoke - incense burns and smoke comes out of it 
//
void do_smoke() {
   object env, room;

   // if incense isn't lit, do nothing; otherwise decrement amount
   if (lit==UNLIT) return;
   amt--;

   // where am I?
   env  = ENV(TO);
   room = ENV(env); // maybe its a room!
   if (env->query_prop(ROOM_I_IS)) { // I am in a room
      if (amt > 0) 
         tell_room(env,"Fragrant white smoke whisps from the stick of incense.\n");
      else {
         tell_room(env,"The stick of incense burns out and collapses into ashes.\n");
         TO->remove_object();
      }
   }
   // I am held by a living
   else if (env->query_prop(LIVE_I_IS)) { 
      if (amt > 0) {
         env->catch_msg("Whisps of fragrant white smoke rise from the stick of incense.\n");
         tell_room(room,"Fragrant white smoke whisps from "+
                   QTNAME(env)+"'s stick of incense.\n",env);
      }
      else {
         env->catch_msg("The stick of incense dies out and collapses into dust.\n");
         tell_room(ENV(env), QTNAME(env)+"'s stick of incense dies out "+
                       "and collapses into dust.\n",env);
         TO->remove_object();
      }
   }
   // I am ON TOP of something in a room
   else if (env->query_prop(CONT_I_ATTACH) && room->query_prop(ROOM_I_IS)) { 
      if (amt > 0) 
         tell_room(room,"Fragrant white smoke whisps from the stick of incense on "+
                   "the " + env->query_short() + ".\n");
      else {
         tell_room(room,"The stick of incense on the " + env->query_short() + 
                   " dies out and collapses into dust.\n");
         TO->remove_object();
      }
   }
   else { // not in a room, held by a living, or on top of something in a room
      if (amt > 0) 
         update_desc(UNLIT);
      else
         TO->remove_object();
      return; // don't set alarm     
   }
   
   // schedule next smoke message
   set_alarm(SMOKE_TIME,0.0,&do_smoke());
} // do_smoke()
 
//
// cmd_refers_to_me
//
int cmd_refers_to_me(string cmd) {
   object ob;
   object *inv=all_inventory(TP);
   string verb=query_verb();
 
   notify_fail(verb+" what? incense?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"[stick] [of] 'incense' [stick]") &&
       !parse_command(cmd,inv,"'stick' [of] [incense]"))
       return 0;
   return 1;
} // cmd_referse_to_me

//
// do_burn - allows the player to burn/ignite incense in the incense
//
int do_burn(string cmd) {
   if (!cmd_refers_to_me(cmd)) return 0;
   if (ENV(TO)!=TP)
      write("You must have the stick of incense in your possession to do that.\n");
   else if (lit==LIT)
      write("The stick of incense is already burning.\n");
   else if (amt<=0) {
      write("The stick of incense burns out and crumbles into dust.\n");
      TO->remove_object();
   }
   else {
      write("You "+cmd+" the stick of incense.\n");
      tell_room(ENV(TP),QCTNAME(TP)+" lights a stick of incense.\n",TP);
      update_desc(LIT);
      do_smoke();
   }
   return 1;
} // do_burn()
 
//
// do_extinguish - allows the player to extinguish incense 
//
int do_extinguish(string cmd) {
   if (!cmd_refers_to_me(cmd)) return 0;
 
   if (ENV(TO)!=TP)
      write("You must have the stick of incense in your possession to do that.\n");
   else if (lit==UNLIT)
      write("The stick of incense is not burning.\n");
   else {
      write("You extinguish the stick of incense.\n");
      tell_room(ENV(TP),QCTNAME(TP)+" extinguishes a stick of incense.\n",TP);
      update_desc(UNLIT); // will stop smoking
   }
   return 1;
} // do_extinguish
 
//
// do_wave - allows the player to burn/ignite incense in the incense
//
int do_wave(string cmd) {
   if (!cmd_refers_to_me(cmd)) return 0;
   if (ENV(TO)!=TP) {
      write("You must have the stick of incense in your possession to do that.\n");
      return 1;
   }
   write("You wave the stick of incense in circles.\n");
   tell_room(ENV(TP),QCTNAME(TP)+" waves a stick of incense in circles.\n",TP);
   if (lit==LIT) 
        tell_room(ENV(TP), "Circles of fragrant white smoke rise from the "
                           + "stick of incense.\n");
   return 1;
} // do_wave()

//
// init - add actions
//
void init() {
   ::init();
   add_action(&do_burn(),      "burn");
   add_action(&do_burn(),      "light");
   add_action(&do_extinguish(),"extinguish");
   add_action(&do_wave(),      "wave");   
}


