
/* The light object of the Heralds of the Valar          */
/* Modified from the candle.c                            */
/* by Sir Denbarra of Gondor                             */
/* 7 May 1995                                            */
/* Modified to serve as special language for the Heralds */
#pragma save_binary

inherit "/std/object";
 
#include "herald.h"
#include <macros.h>
#include <stdproperties.h>
#include "/sys/ss_types.h"
 
#define MAX_TIME 450    /* about 7 mins */
#define TP this_player()

/* prototypes */
void normal_voice();
int query_max();

int time_left, maxtime;

void
create_object()
{
   time_left = query_max();
   set_name("mic");   /* extra unique name */
   set_pname("mics");
   set_adj("sound");
   set_no_show();

   add_prop(OBJ_I_LIGHT,0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_S_WIZINFO, "This is the special voice of the Heralds of " +
      "the Valar guild, summoned to provide a secret language.");
   maxtime = 30;
}

void
init()
{
   ::init();
   add_action("speak","speak");
}

void
set_max(int time)
{
   if (time > MAX_TIME)
      maxtime = MAX_TIME;
   else if (time < 30)
      maxtime = 30;
   else
      maxtime = time;
}

int
query_max()
{
   return maxtime;
}

void
silence()
{
   set_alarm(itof(query_max()),0.0,&normal_voice());
}

 
void
normal_voice()
{
   object ob;

   time_left = 0;

   ob = environment();
   if (!ob)
      return;
   if (living(ob))
   {
      ob->catch_msg("Your powerful voice dwindles and you begin to "+
     "speak normally again.\n");
      tell_room(environment(ob), "The powerful speaking voice of " + QTNAME(ob)
          + " returns to normal.\n", this_player());
      this_object()->remove_object();
      return;
   }
}


int
speak(string str)
{
   string list,who, cap_name, tmpstr, wrtstr, prestr, *expl_arr, *tell_arr;
   int i,sobj,argnum, cnt ,cnt2;
   object *obj;

   if (!strlen(str)) return 0;
   if (TP->query_invis()) cap_name = "Someone";
   if (!tell_arr)
      tell_arr = allocate(20);
   if (!expl_arr)
      expl_arr = allocate(100);
   str += " ";
   if (str != " ") { /* Now let's cut the string in pieces! */

      expl_arr = explode(str," ");
      argnum = sizeof(expl_arr);
      cnt = cnt2 = 0;
      while (cnt < argnum && cnt2 < 20) {
         wrtstr = expl_arr[cnt++];
         while (cnt < argnum && strlen(wrtstr + " " + expl_arr[cnt]) < 60) {
            wrtstr = wrtstr + " " + expl_arr[cnt++];
            }
         tell_arr[cnt2++] = wrtstr;
       }
   }
   write("You spoke with the voice of Manwe.\n");
   obj=all_inventory(environment(TP));
   sobj = sizeof(obj);
   notify_fail("There is nobody here to hear you.\n");
   if (!sobj) return 0;
   while (i < sobj)
   {
      if ((living(obj[i])) && (obj[i] != TP))
         {
if ((!IS_MEMBER(obj[i])) && (obj[i]->query_skill(SS_LANGUAGE) <65))
            {
            if (CAN_SEE(obj[i],TP))
               obj[i]->catch_msg(QCTNAME(TP)
               +" says something in a high, unknown tongue.\n");
            else obj[i]->
               catch_msg("Someone says something in a high, unknown tongue.\n");
            if (CAN_SEE(TP,obj[i]))
               TP->catch_msg(QCTNAME(obj[i])+" cannot decipher your words.\n");
          }
         else
            {
            if (CAN_SEE(TP,obj[i]))
               TP->catch_msg(QCTNAME(obj[i])+" understood your meaning.\n");
            if (CAN_SEE(obj[i],TP))
               for (cnt = 0; cnt < cnt2; cnt++)
            obj[i]->catch_msg(QCTNAME(TP)
               +" speaks in a high and beautiful tongue: "+tell_arr[cnt] + "\n");
            else
               for (cnt = 0; cnt < cnt2; cnt++)
            obj[i]->catch_msg("Someone speaks in a high and beautiful tongue: "
               +tell_arr[cnt]+"\n");
          }
          }
      i++;
   }
   return 1;
}


