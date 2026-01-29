/* A Censor
** This is a ritualist tool used to burn incense, consisting of a "bowl"
** suspended from a long chain. Player can put a cake of incense in
** it, burn  the incense, and it will smoke. Player can swing the
** censor to "cense" an object or the room. Can extinguish depletable
** cake of incense (sr/objects/cake_incense.c). Is a holdable object.
**
** History:
** Date         Coder         Action
** -------- ----------------  -----------------------------------------
** 5/16/98  Zima              Created
*/
inherit "/std/object";
inherit "/lib/holdable_item";
#include "defs.h"
#include "powder.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
 
//constants for the "state" of incense in censor
#define  NONE           0
#define  UNLIT          1
#define  LIT            3
#define  SMOKE_TIME    15.0
#define  SW_EFF_DELAY   2.0
 
//constants for how censor is swung
#define  SW_REGULAR     1
#define  SW_CIRCLE      2
#define  SW_LIVING      3
#define  SW_OBJ         4
 
//constant patterns for parse commands for do_swing()
#define  PC_CIRCLE    "'censor' [in] 'circle' / 'circles'"
#define  PC_FRONT     "'censor' [in] 'front' / 'before' [of] [me] [myself]"
#define  PC_SIDE      "'censor' [at] [side]"
#define  PC_DIREX     "'censor' [to] [toward] [the] %s"
#define  PC_DIR       "'censor' [to] [toward] [the] 'n' / 's' / 'e' / 'w'"+ \
                      " / 'north' / 'south' / 'east' / 'west' / "+ \
                      "'ne' / 'se' / 'sw' / 'nw' / 'northeast' / "+ \
                      "'southeast' / 'southwest' / 'northwest'"
#define  PC_OBJ       "'censor' 'at' / 'toward' [the] %o"
 
//
// global variables
//
static int    amt     = 0;      // amt of incense left in censor
static int    held    = 0;      // is it held or not?
static int    incense = NONE;   // is incense in censor?
static string cs;               // short short_desc, without "hanging by chain"
static int    inc_type;         // type of incense put in the censor

// 
// simple query functions for global variables
//
int    query_incense()     { return incense; }
int    query_inc_type()    { return inc_type; }
int    query_amt()         { return amt; }
string query_short_short() { return cs; }
 
//
// update_desc - updates the description of the censor when incence is
//               placed/lit/extinguished/removed
//
void update_desc(int new_inc) 
{
   string long=
      "It is a censor made of silver, a ritualistic tool which consists "+
      "of an ornate covered bowl with large openings in the top, attatched "+
      "to a long silver chain. ";
   string short="ornate silver censor";
 
   incense=new_inc;
   switch (incense)
   {
      case NONE: long+="A cake of incense can be placed in it and burned.\n";
                 break;
                 remove_adj("smoking");
      case UNLIT:long+="There is a cake of incense in it.\n";
                 remove_adj("smoking");
                 break;
      case LIT:  long+="There is a cake of burning incense in it, "+
                       "plumes of fragrant smoke billowing out from "+
                       "the openings in its top.\n";
                 short="smoking silver censor";
                 add_adj("smoking");
   }
   cs=short;
   if (held) short+=" hanging from a long silver chain";
   set_long(long);
   set_short(short);
}
 
//
// create_object
//
void create_object() 
{
   set_name("censor");
   add_name(SR_CENSOR);
   add_adj(({"silver","ornate"}));
   update_desc(NONE);
   add_item(({"incense in censor","cake in censor",
              "cake of incense in censor"}),"@@exa_incense");
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_VALUE,6*12); // 12 silver
   set_slots(W_BOTH);
}
 
//
// exa_incense - allows player to examine the incense in the censor
//
string exa_incense() 
{
   switch (incense) {
   case NONE: write("There is no incense in the censor.\n"); break;
   case LIT:  write("The incense in the censor is burning, releasing "+
                    "plumes of fragrant white smoke.\n");
                    break;
   case UNLIT:write("There is a cake of incense in the censor. "+
                    "It is not burning.\n");
   }
   return "";
}
 
//
// leave_env - make sure we realease if being held
//
public void leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

//
// appraise_object
//
public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}
 
//
// hold and release - mask to change desc when held/released
//
public int release()
{
   held=0;
   update_desc(incense);
   return 0;
}
 
public int hold()
{
   write("You take hold of your "+cs+" by its chain in both hands, its "+
         "bowl hanging by your side.\n");
   tell_room(ENV(TP),QCTNAME(TP)+" takes hold of "+HIS_HER(TP)+" "+cs+
             " by its chain in both hands, its bowl hanging by "+
             HIS_HER(TP)+" side.\n",TP);
   held=1;
   update_desc(incense);
   return 1; // print own messages
}
 
//
// help - give instructions on use
//
int help_censor(string cmd)
{
   if (cmd != "censor") return 0;
   write("Help on the ornate silver censor:\n");
   write("  'place incense in censor'\n");
   write("  'remove incense from censor'\n");
   write("  'light censor'\n");
   write("  'extinguish censor'\n");
   write("  'swing censor' (must be holding to swing)\n");
   write("  'swing censor in circles'\n");
   write("  'swing censor in front [of] [myself]'\n");
   write("  'swing censor at <person or object>'\n");
   write("  'swing censor <n/s/e/w/ne/se/nw/sw>'\n");
   return 1;
}

//
// check_cloud - clone/update the could of incense and increase its strength
//
void check_cloud()
{
   object rm,cloud,env=ENV(TO);
 
   // find the room
   if (env->query_prop(LIVE_I_IS))
      rm=ENV(env);
   else if (env->query_prop(ROOM_I_IS))
      rm=env;
   else
      return;
 
   // smoke dissipates too quickly outside to build up
   // if (!(rm->query_prop(ROOM_I_INSIDE))) return;
 
   // clone the cloud if necessary
   cloud=present(SR_INC_CLOUD,rm);
   if (!objectp(cloud))
      {
      seteuid(getuid());
      cloud=clone_object(SR_OBJ+"inc_cloud");
      cloud->move(rm);
      cloud->startup();
      }
   else
      cloud->strengthen();
}
 
//
// do_smoke - incense burns and smokes comes out of it, creating a
//            cloud of incense in the room.
void do_smoke()
{
   object env=ENV(TO);
 
   // if incense isn't lit, or censor not in hand or in room, stop smoking
   if (incense!=LIT) return;
   if ((!env->query_prop(LIVE_I_IS))&&(!(env->query_prop(ROOM_I_IS))))
      {
      if (amt>0) update_desc(UNLIT); else update_desc(NONE);
      return;
      }
 
   // decrement amount of incense left to burn and give messages
   amt--;
 
   if (env->query_prop(LIVE_I_IS)) // living has censor
      {
      if (amt<=0)
         {
         env->catch_msg("The fragrant white incense rising from of your "+
                        "censor dies out.\n");
         env->catch_msg("The fragile cake of incense collapses into "+
                        "ashes and disappears.\n");
         tell_room(ENV(env),"The fragrant white incense rising from "+
                   QTNAME(env)+"'s ornate silver censor dies out.\n",env);
         }
      else
         {
         env->catch_msg("Fragrant white incense billows from your censor.\n");
         tell_room(ENV(env),"Fragrant white incense billows from "+
                   QTNAME(env)+"'s ornate silver censor.\n",env);
         }
      }
   else // censor in room
      {
      if (amt>0)
         tell_room(env,"Fragrant white incense billows from the ornate "+
                       "silver censor.\n");
      else
         tell_room(env,"The fragrant white incense rising from the ornate "+
                       "silver censor dies out.\n");
      }
   check_cloud(); // check cloud of incense in this room
   if (amt>0)
      set_alarm(SMOKE_TIME,0.0,&do_smoke());
   else
      update_desc(NONE);
}
 
//
// do_burn - allows the player to burn/ignite incense in the censor
//
int do_burn(string cmd) {
   object ob;
   object *inv=all_inventory(TP);
   string verb=query_verb();
 
   notify_fail(verb+" what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"'censor' / 'incense' [in] [censor]'"))
      return 0;
 
   if (ENV(TO)!=TP)
      write("You must have the censor in your possession to do that.\n");
   else if (incense==NONE)
      write("There is no incense in the censor to "+verb+".\n");
   else if (incense==LIT)
      write("The incense in the censor is already burning.\n");
   else if (amt<=0)
      write("The incense in the censor is burnt out.\n");
   else
      {
      write("You ignite the incense in the censor.\n");
      tell_room(ENV(TP),QCTNAME(TP)+" ignites the incense in "+HIS_HER(TP)+
                        " ornate silver censor.\n",TP);
      update_desc(LIT);
      do_smoke();
      }
   return 1;
}
 
//
// do_extinguish - allows the player to extinguish incense in the censor
//
int do_extinguish(string cmd) 
{
   object ob;
   object *inv=all_inventory(TP);
   string verb=query_verb();
 
   notify_fail("Extinguish what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"[incense] [in] 'censor' / 'incense'"))
      return 0;
 
   if (ENV(TO)!=TP)
      write("You must have the censor in your possession to do that.\n");
   else if (incense==NONE)
      write("There is no incense in the censor to extinguish.\n");
   else if (incense==UNLIT)
      write("The incense in the censor is not burning.\n");
   else
      {
      write("You extinguish the incense in the censor.\n");
      tell_room(ENV(TP),QCTNAME(TP)+" extinguishes the incense in "+
                        HIS_HER(TP)+" ornate silver censor.\n",TP);
      update_desc(UNLIT); // will stop smoking
      }
   return 1;
}
 
//
// do_place - allows player to a cake of incense in the censor
//
int do_place(string cmd) {
   object ob;
   object *inv=all_inventory(TP);
 
   notify_fail("Place what in the censor?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"%o 'in' / 'into' [the] 'censor'",ob))
      return 0;
 
   if (incense!=NONE)
      write("There is already incense in the censor.\n");
   else if (ENV(TO)!=TP)
      write("You must have the censor in your possession to do that.\n");
   else if (!(ob->id("incense")))
      write("Only a cake of incense may be placed in the censor.\n");
   else if (!(ob->id(SR_CAKE_INCENSE)))
      write("That is not the type of incense used with this censor.\n");
   else
      {
      write("You place a cake of incense in the censor.\n");
      tell_room(ENV(TP),QCTNAME(TP)+" places a cake of incense into "+
                       HIS_HER(TP) +" ornate silver censor.\n",TP);
      amt=(ob->query_amt());
      inc_type=(ob->query_type());
      ob->remove_object();
      update_desc(UNLIT);
      }
   return 1;
}
 
//
// do_remove - allow player to remove incense from censor
//
int do_remove(string cmd) {
   object ob;
   object *inv = all_inventory(TP);
 
   notify_fail("Remove what from the censor?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,
      "[cake] [of] 'cake' / 'incense' 'from' 'censor'"))
      return 0;
 
   if (ENV(TO)!=TP)
      write("You must have the censor in your possession to do that.\n");
   else
      switch (incense) {
         case NONE: write("There is no incense in the censor.\n");
                    return 1;
         case LIT:  write("The incense is still burning!\n");
                    return 1;
      }
 
   seteuid(getuid());
   ob = clone_object(SR_OBJ+"cake_incense");
   ob->set_amt(amt);
   ob->set_type(inc_type);
   ob->move(TP);
   inc_type=0;
   write("You remove the cake of incense from the from the censor.\n");
   tell_room(ENV(TP),QCTNAME(TP)+" removes a cake of incense from "+
                     HIS_HER(TP)+" ornate silver censor.\n",TP);
   update_desc(NONE);
   return 1;
}

//
// do_swing_effect - do effect of swinging censor
//
void do_swing_effect(int sw, object tp, object ob)
{
   object rm=ENV(tp);
   string obs;
   if (incense!=LIT) return; // no effect if not lit
   switch(sw) {
      case SW_REGULAR:
         tell_room(rm,"Long plumes of fragrant white incense stream from "+
                      "the "+cs+".\n");
         break;
      case SW_CIRCLE:
         tell_room(rm,"Spirals of fragrant white incense rise in circles "+
                      "from the the "+cs+".\n");
         break;
      case SW_LIVING:
         tell_room(rm,QCTNAME(ob)+" is enveloped in spiraling plumes "+
                      "of fragrant white incense.\n",ob);
         ob->catch_msg("You are enveloped in spiraling plumes of "+
                       "fragrant white incense.\n");
         break;
      case SW_OBJ:
         obs=ob->query_short();
         if (!stringp(obs)) obs=query_name(ob);
         tell_room(rm,"The "+obs+" is enveloped in spiraling plumes "+
                      "of fragrant white incense.\n");
         break;
   }
   check_cloud();
}
 
//
// full_dir - give the full name of a direction
//
string full_dir(string dir)
{
   int len=strlen(dir);
   if (strlen(dir)>2) return dir;
   if (dir=="ne") return "northeast";
   if (dir=="se") return "southeast";
   if (dir=="sw") return "southwest";
   if (dir=="nw") return "northwest";
   if (dir=="n")  return "north";
   if (dir=="s")  return "south";
   if (dir=="e")  return "east";
   if (dir=="w")  return "west";
   return dir;
}
 
//
// do_swing - allow the player to swing the censor
//
int do_swing(string cmd) {
   object rm=ENV(TP),thing;
   object *inv=all_inventory(rm);
   string poss=HIS_HER(TP), obj=HIM_HER(TP), sthing, dir;
 
 
   notify_fail("Swing what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"'censor' %s")) return 0;
   if (!present(TO,TP))
      {
      write("You must have the "+cs+" in your possession to swing it.\n");
      return 1;
      }
   else if (query_holder()!=TP)
      {
      write("You must be holding the "+cs+" to swing it.\n");
      return 1;
      }
   else if (parse_command(cmd,inv,PC_CIRCLE))
      {
      write("You swing the "+cs+" in circles before you.\n");
      tell_room(rm,QCTNAME(TP)+" swings "+poss+" "+cs+" before "+
                   obj+"self in circles.\n",TP);
      set_alarm(SW_EFF_DELAY,0.0,&do_swing_effect(SW_CIRCLE,TP,TP));
      }
   else if (parse_command(cmd,inv,PC_FRONT))
      {
      write("You swing the "+cs+" left to right in front of you.\n");
      tell_room(rm,QCTNAME(TP)+" swings "+poss+" "+cs+" left to right "+
                   "in front of "+obj+"self.\n",TP);
      set_alarm(SW_EFF_DELAY,0.0,&do_swing_effect(SW_REGULAR,TP,TP));
      }
   else if (parse_command(cmd,inv,PC_SIDE))
      {
      write("You swing the "+cs+" back and forth at your side.\n");
      tell_room(rm,QCTNAME(TP)+" swings "+poss+" "+cs+" back and forth "+
                   "at "+poss+" side.\n",TP);
      set_alarm(SW_EFF_DELAY,0.0,&do_swing_effect(SW_REGULAR,TP,TP));
      }
   else if (parse_command(cmd,inv,PC_DIR,dir))
      {
      parse_command(cmd,inv,PC_DIREX,dir);
      dir = full_dir(dir);
      write("You reverently turn and face "+dir+".\n"+
            "You swing your "+cs+" towards the "+dir+ " three times.\n");
      tell_room(rm,QCTNAME(TP)+" reverently turns and faces "+dir+".\n"+
                   QCTNAME(TP)+" swings "+poss+" "+cs+" towards the "+
                   dir+" three times.\n",TP);
      set_alarm(SW_EFF_DELAY,0.0,&do_swing_effect(SW_REGULAR,TP,TP));
      }
   else if (parse_command(cmd,inv,PC_OBJ,thing))
      {
      if (thing->query_prop(LIVE_I_IS))
         {
         if (thing==TP)
            write("You can not swing your "+cs+" towards yourself.\n");
         else
           {
           TP->catch_msg("You swing your "+cs+" towards "+QTNAME(thing)+
                         " three times.\n");
           thing->catch_msg(QCTNAME(TP)+" swings his "+cs+" towards "+
                            "you three times.\n");
           tell_room(rm,QCTNAME(TP)+" swings his "+cs+" towards "+
                        QTNAME(thing)+" three times.\n",({TP,thing}));
           set_alarm(SW_EFF_DELAY,0.0,&do_swing_effect(SW_LIVING,TP,thing));
           }
         }
      else
         {
         sthing = (thing->query_short());
         if (!stringp(sthing)) sthing = (thing->query_name());
         write("You swing your "+cs+" towards the "+sthing+" three times.\n");
         tell_room(rm,QCTNAME(TP)+" swings his "+cs+" towards the "+
                      sthing+" three times.\n",TP);
         set_alarm(SW_EFF_DELAY,0.0,&do_swing_effect(SW_OBJ,TP,thing));
 
         }
      }
   else
      write("Swing censor how?\n");
   return 1;
}


//
// init - add actions
//
void init()
{
   ::init();
   add_action(&help_censor(),  "help");
   add_action(&do_place(),     "place");
   add_action(&do_remove(),    "remove");
   add_action(&do_burn(),      "burn");
   add_action(&do_burn(),      "ignite");
   add_action(&do_burn(),      "light");
   add_action(&do_extinguish(),"extinguish");
   add_action(&do_swing(),     "swing");
}


