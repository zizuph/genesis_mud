/*
 * A travellers hat, for sale in the Ranger guild
 * By Gilgalad, June 1995.
 * With help from Rohim
 */
#pragma save_binary

inherit "/std/armour.c";
#include "/d/Shire/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
 
int alarm_id, hatstat;
 
void
create_armour()
{
 set_name("hat");
 set_adj(({"wide brim","green","forest"}));
 set_short("wide brim, forest green hat");
 set_long("The "+short()+" has a wide brim. And has "+
  "a forest green shade to it. The "+short()+" is a "+
  "little too big. You might want to yank on your "+
  "hat once and a while to make sure you don't loose "+
  "it.\n");
 set_ac(3);
 set_at(A_HEAD);
 set_af(TO);
 add_prop(OBJ_I_VOLUME,350);
 add_prop(OBJ_I_WEIGHT,25+random(10));
 add_prop(OBJ_I_VALUE,25+random(2));
 hatstat = 0;
}
 
init()
{
 ::init();
 add_action("do_yank","yank");
}
 
int
do_yank(string str)
{
 notify_fail("Yank what?\n");
 
 if(!this_object()->query_worn())
 {
  write("You need to be wearing the hat to "+
	"do that.\n");
  return 1;
 }
 
 if(str != "hat")
  return 0;
 
 write("You yank your "+short()+" over your eyes.\n");
 tell_room(ENV(TP),QCTNAME(TP) +" pulls "+HIS_HER(TP)+
  " "+short()+" over "+HIS_HER(TP)+" eyes.\n",TP);
 remove_alarm(alarm_id); 
 alarm_id = set_alarm(300.0,10.0,"do_wind");
 return 1;
}
 
public int
wear(object arm) 
{
 int wear;
 
 wear = random(2);
 hatstat = 0;
 
 if(wear == 0)
 {
  TP->catch_msg("You wear the "+ short() +" on "+
	"your head.\n");
  tell_room(ENV(TP),QCTNAME(TP)+" wears a "+
	short()+" on "+ HIS_HER(TP) +" head.\n",TP);
/* This is so that when a person puts on the hat
 * that the hat could blow off.
 */
  alarm_id = set_alarm(500.0,20.0,"do_wind");
  return 1; 
 }
 if(wear == 1)
 {
  TP->catch_msg("You wear the "+short()+" on "+
	"your head.\nYour "+short()+" slides in front "+
	"of your eyes.\n");
  tell_room(ENV(TP),QCTNAME(TP)+" wears a "+ short()+
	" on "+HIS_HER(TP)+" head.\n"+QTNAME(TP)+"'s "+
	short()+" slides in front of "+HIS_HER(TP)+" eyes.\n",TP);
/* This takes longer for the hat to blow off. */
  alarm_id = set_alarm(1000.0,40.0,"do_wind");
  return 1;
 }
}
 
public int
remove(object arm) 
 
{
 if(hatstat == 1)
  {
  TP->catch_msg("You try to grab the hat as it "+
   "blows out of your grasp!\n");
  tell_room(ENV(TP),QCTNAME(TP)+" tries to catch "+
   HIS_HER(TP) +" hat but fails!\n",TP); 
  remove_alarm(alarm_id); 
  hatstat = 0;
  return 1;
  }
 if(hatstat == 2)
  {
  TP->catch_msg("You are just barely able to "+
   "catch your hat!\n");
  tell_room(ENV(TP),QCTNAME(TP)+" just barely "+
   "caught "+ HIS_HER(TP) +" hat!\n",TP); 
  remove_alarm(alarm_id); 
  hatstat = 0;
  return 1;
  }
 TP->catch_msg("You remove the "+ short() +" from "+
  "your head.\n");
 tell_room(ENV(TP),QCTNAME(TP)+" removes the "+
  short() +" from his head.\n",TP);
/* Well it wold look pretty funny if the hat blow  
 * off when it is not being worn. 
 */
 remove_alarm(alarm_id); 
 return 1; 
}
 
void 
do_wind()
{
 int ran = random(3);
 
 if(ran == 0)
  {
  hatstat = 1;
  TP->catch_msg("All of a sudden a huge gust of "+
   "wind comes along and whips loose your hat!\n");
  tell_room(ENV(TP),"All of a sudden a huge gust "+
   "of wind comes along and whips loose "+ QCTNAME(TP)+
   "'s hat!\n",TP);
  TO->move(ENV(TP));
  return;
  }
 if(ran == 1)
  { 
  hatstat = 2;
  TP->catch_msg("All of a sudden a gust of wind "+
	"comes along and whips loose your hat!\n");
  tell_room(ENV(TP),"All of a sudden a gust of wind "+
	"comes along and whips loose "+QCTNAME(TP)+ "'s "+
	"hat!\n",TP);
  TP->command("remove hat");
  return;
  }
 if(ran == 2)
  { 
   hatstat = 3;
   TP->catch_msg("A small gust of wind comes along and "+
    "gently rocks the "+ short() +". You hold on to it "+
    "so that it does not blow away.\n");
	tell_room(ENV(TP),"A small gust of wind comes along and "+
	 "gently rocks "+ QCTNAME(TP) +"'s "+ short() +". "+
	 QCTNAME(TP) +" holds on to "+ HIS_HER(TP) +" "+ short() +
	 " so that it does not blow away.\n",TP);
	hatstat = 0;
	remove_alarm(alarm_id); 
	alarm_id = set_alarm(300.0,10.0,"do_wind");
	return;
  }
}