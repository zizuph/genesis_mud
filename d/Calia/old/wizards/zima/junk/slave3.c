inherit "/std/monster";
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#define SLAVE_MERCHANT_NAME "Zima"
#define MY_NAME             "Andreas"
 
string MyMaster=SLAVE_MERCHANT_NAME;
 
void
equip_me()
{
    object this;
    string type;
    seteuid(getuid());
    this = THIS;
    clone_object(ARMOUR_DIR + "slvtunic")->move(this);
    command("wear all");
}
 
void
create_monster()
{
   if (!IS_CLONE) return;
 
   set_name(({"Andreas","andreas","servant","slave"}));
   set_adj("blonde-haired");
   set_adj("muscular");
   set_title("Servant of "+MyMaster);
   set_race_name("human");
   set_short("muscular blonde-haired human");
   set_long("He is a muscular blonde-haired human.\n");
 
   set_stats(({ 100, 70, 70, 30, 30, 70})); /* str dex con int wis dis */
   set_alignment(0);
   add_prop(CONT_I_WEIGHT, 100000);
   add_prop(CONT_I_VOLUME, 100000);
   call_out("equip_me", 1);
   set_all_hitloc_unarmed(query_average_stat() / 4);
 
   trig_new("%w %s '"+ MY_NAME + ",' 'your' 'master' 'is' 'now' %w %s",
            "set_master");
   trig_new("%w %s '" + MY_NAME + ",' %w %s", "obey");
   trig_new("%w %s 'whispers' 'to' 'you:' %w %s","obey");
   trig_new("%w 'leaves' %w","follow");
}
 
string remove_nl_endpunc(string parm) {
   /* remove a new line and ending pucntuation from the end of a string */
   string lastlet;
   int    lastpos;
 
   lastpos=strlen(parm)-1;
   lastlet=extract(parm,lastpos,lastpos);
   if (lastlet=="\n")
      parm=extract(parm,0,(lastpos-1));
 
   lastpos=strlen(parm)-1;
   lastlet=extract(parm,lastpos,lastpos);
   if ((lastlet=="!")||(lastlet==".")||(lastlet=="?"))
      parm=extract(parm,0,(lastpos-1));
 
   return parm;
}
 
/* use of these functions allows for a delay of the command, so to */
/* the player it seems he gives the command first, then the slave  */
/* follows. otherwise, slave obeys before the say is displayed     */
 
void do_delay_command(string cmd) {
   object TObj=this_object();
   TObj->command("bow "+MyMaster);
   if (!(TObj->command(cmd)))
     TObj->command("emote looks confused.");
}
 
void delay_command(string cmd) {
   set_alarm(1.0,0.0,"do_delay_command",cmd);
}
 
 
int follow (string who, string direction) {
   direction=remove_nl_endpunc(direction);
   if (who==MyMaster)
      delay_command(direction);
   return 1;
}
 
int obey(string who, string dummy, string cmd, string parms) {
   cmd=remove_nl_endpunc(cmd);
   who=remove_nl_endpunc(who);
   parms=remove_nl_endpunc(parms);
 
   if (who==MyMaster)
      delay_command(cmd+" "+parms);
   else
      delay_command("say I obey only my master.");
   return 1;
}
 
int set_master(string who, string dum1, string master, string dum2) {
   who=remove_nl_endpunc(who);
   master=capitalize(remove_nl_endpunc(master));
   if (who==MyMaster) {
      /* this conditon returns 0 if master isn't in the room */
      if (this_object()->command("examine "+master)) {
         MyMaster=capitalize(master);
         this_object()->set_title("Servant of "+MyMaster);
         delay_command("say I shall serve you well Master "+MyMaster);
         }
      else
         delay_command("xxx"); /* makes him look confused */
      }
   else
      delay_command("say I obey only my master.");
   return 1;
}
