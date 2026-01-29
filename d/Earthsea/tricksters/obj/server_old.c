inherit "/std/room";

#include <macros.h>

#include "../defs.h"
#include "../titles.h"

#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

mapping stick;
mapping kit;
string leader;
string guildmaster;
string *jamadar;
string *members;
mapping restrict;
mapping punish;
mapping baned;
mapping to_be_promoted;
mapping appeal;
int apply_block;
// apply: ([name: ({ title , level , gender , race , occ , lay , 
//                   race , prev_guilds ,
//                   ({ ({ date1 , name1 , repond1 }) ,... }) ,
//                   allowed 0/1/2 , allowed/denied by, a/d date]);

mapping apply;

int max_jamadar;

void add_member(string name);
void remove_member(string name);
string members_string();
string jamadars_string();
void save_stick(string name,int *q);
void save_kit(string name,int q);
int *query_stick_contents(string name);
int query_kit_contents(string name);
int query_leader(string name);
int query_jamadar(string name);
void accept_jamadar(string name);
void deny_jamadar(string name);
string get_leader();
string *get_jamadar();
void set_leader(string name);
void exchange_leader(string name);
void set_guildmaster(string name);
string query_guildmaster();
void restrict_member(string name);
void unrestrict_member(string name);
string restrict_string();
int query_member(string name);
int has_autority(string executor,string executed);
void set_max_jamadar(int num);
int query_max_jamadar();
int query_baned(string name);
void add_baned(string name);
void add_apply(string name,string text,string prev_guilds);
void fill_apply();
string cut_spaces(string str);
string apply_string();
string get_applicant_info(string name);
int query_applicant(string name);
void discard_apply(string name);
string view_apply(string name);
void respond_apply(string name);
void add_respond(string name,string text);
void reject_applicant(string name);
mixed query_rejected(string name);
void set_reject_by(string name,string by);
string rejected_string();
string approved_string();
mixed query_approved(string name);
void approve_applicant(string name);
void set_approve_by(string name,string by);
void revert_apply(string name);
void reply_council(string name);
void promote(string name,int lv);
void do_promote(object pl,int lv);
void add_promote(string name,int lv);
void check_promote_on_logon(object pl);
void demote(string name,int lv);
string promotion_plan_string();
void cancel_promotion(string name);
void punish_member(string name);
void unpunish_member(string name);
int query_punished(string name);
int query_restricted(string name);
string punished_string();
void remove_baned(string name);
string baned_string();
void check_inside(object pl);
void remove_apply(string name);
void appeal_banish(string name);
int query_appeal(string name);
void discard_appeal(string name);
string appeal_string();
string get_appeal(string name);
void add_respond_appeal(string name,string text);
string get_info(string name);
string view_appeal(string name);
void dismiss_apply(string name);
void dismiss_appeal(string name);
void dismiss(string name);
void block_apply();
void block_remove();
int query_apply_block();
string *query_council();
string *get_members();
void tell_all(string msg);
void discard_respond(string name);

void create_room()
{
 stick=([]);
 kit=([]);
 leader="";
 guildmaster="";
 jamadar=({});
 members=({});
 restrict=([]);
 punish=([]);
 max_jamadar=0;
 baned=([]);
 apply=([]);
 to_be_promoted=([]);
 appeal=([]);
 apply_block=0;

 restore_object(SERVERO);
}

void add_member(string name)
{
 stick+=([LC(name):({0,0,0,0,0})]);
 kit+=([LC(name):0]);
 members+=({LC(name)});

 save_object(SERVERO);
}

void remove_member(string name)
{
 stick=m_delete(stick,LC(name));
 kit=m_delete(kit,LC(name));
 members-=({LC(name)});

 if(query_jamadar(name)) jamadar-=({ LC(name) });
 if(query_leader(name)) leader="";

 save_object(SERVERO);
}

string members_string()
{
 return implode(sort_array(members,"order_members",TO)," , ");
}

string jamadars_string()
{
 if(!sizeof(jamadar)) return "There are no Jamadars registred.\n";

 return implode(sort_array(jamadar,"order_members",TO)," , ");
}

void save_stick(string name,int *q)
{
 int *data;

 data=stick[name];
 if(!sizeof(data)) stick+=([name:q]);
   else stick[name]=q;

 save_object(SERVERO);
}

mapping get_stick() {return stick;}
mapping get_kit() {return kit;}

int *query_stick_contents(string name)
{
 int *data;

 data=stick[name];
 if(!sizeof(data)) return 0;

 return data;
}

void save_kit(string name,int q)
{
 int data;

 data=kit[name];
 if(!sizeof(data)) kit+=([name:q]);
   else kit[name]=q;

 save_object(SERVERO);
}

int query_kit_contents(string name)
{
 int data;
 
 data=kit[name];
 return data;
}

int query_leader(string name)
{
 return (LC(name)==leader || LC(name)==guildmaster ? 1 : 0);
}

int query_jamadar(string name)
{
 return (member_array(LC(name),jamadar)==-1 ? 0 : 1);
}

void accept_jamadar(string name)
{
 object pl;

 if(query_jamadar(name))
  {
   write(C(LC(name))+" is already Jamadar!\n");
   return;
  }

 pl=find_player(LC(name));
 if(!pl)
  {
   write("Trickster must be online to be accepted into Jamadars!\n");
   return ;
  }

 if(!pl->query_trickster_level())
  {
   write(C(LC(name))+" is not a Trickster!\n");
   return;
  }

 if(sizeof(jamadar)==query_max_jamadar())
  {
   write(sprintf("No more then %d Jamadars can serve Kina!\n",
     query_max_jamadar()));
   return;
  }

 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 if(LC(name)==TP->query_real_name())
  {
   write("Wanna become Jamadar - relinquish leadership!\n");
   return;
  }

 tell_room(ENV(TP),TP->query_name()+" accepts "+C(LC(name))+
   " into Jamadars.\n");
 pl->catch_msg(TP->query_name()+" accepts you as Jamadar of "+
   "Tricksters!\nServe Kina , the Goddess of Mischief!\n");
 jamadar+=({LC(name)});

 save_object(SERVERO);
}

void deny_jamadar(string name)
{
 string mail_mesg;
 object pl;

 if(!query_jamadar(name))
  {
   write(C(LC(name))+" is not Jamadar!\n");
   return;
  }

 if(!has_autority(TP->query_name(),name))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 pl=find_player(LC(name));
 say(TP->query_name()+" denies "+C(LC(name))+" from Jamadars.\n");
 if(!pl)
  {
   mail_mesg="You have disappointed me , "+C(LC(name))+"!\n"+
	     "You now denied from Jamadars of Tricksters!\n"+
	     "Prove your faith and you will be allowed back.\n\n";
   MAIL("Denial","Kina",name,mail_mesg);
  }
 else pl->catch_msg("An apparition of Kina to you.\n"+
		    "She tells you: You have disappointed me!\n"+
		    "You now denied from Jamadars.\n");
 tell_room(ENV(TP),C(LC(name))+" denied from Jamadars by "+
   TP->query_name()+".\n");
 jamadar-=({LC(name)});

 if(ENV(TP)==ENV(pl))
  {
   pl->catch_msg("B E G O N E ! ! !\n");
   pl->move_living("M",TRICKSTERS+"hall");
   tell_room(ENV(TP),QCTNAME(pl)+" is thrown out!\n");
   pl->command("look");
  }

 save_object(SERVERO);
}

string get_leader()
{
 if(!leader) return "No leader has been registred.\n";

 return leader;
}

string *get_jamadar() {return jamadar;}
void set_leader(string name)
{
 leader=LC(name);

 save_object(SERVERO);
}

void exchange_leader(string name)
{
 object pl;

 pl=find_player(LC(name));
 if(!pl)
  {
   write("Player must be online.\n");
   return;
  }

 if(ENV(TP)!=ENV(pl))
  {
   write("Jamadar must be here.\n");
   return;
  }

 if(!query_jamadar(name))
  {
   write("You can relinquish leadership to Jamadar only!\n");
   return 0;
  }

 write("You take your gold rumel off and give it to "+
   pl->query_the_name(TP)+", giving him the power of Jamadar of "+
   "Jamadars.\n"+
   C(PRO(pl))+" accepts the rumel with words 'I swear to "+
   "dedicate my life serving Kina , the Goddess of Mischief!'\n");
 pl->catch_msg(TP->query_The_name(pl)+" takes "+POS(TP)+" gold "+
   "rumel off and gives it to you.\n"+
   "You accept it with words 'I swear to "+
   "dedicate my life serving Kina , the Goddess of Mischief!'\n");
 tell_room(ENV(TP),QCTNAME(TP)+" takes "+POS(TP)+" gold rumel off and "+
   "gives it to "+QTNAME(pl)+".\n"+
   C(PRO(pl))+" accepts the rumel with words 'I swear to "+
   "dedicate my life serving Kina , the Goddess of Mischief!'\n",
   ({TP,pl}));

 leader=pl->query_real_name();
 jamadar-=({pl->query_real_name()});
 jamadar+=({TP->query_real_name()});
 present(RUMEL_DESC,pl)->set_color("gold");
 present(RUMEL_DESC,TP)->set_color("silver");

 save_object(SERVERO);
}

int order_members(string aname, string bname)
{
 return (aname < bname ? -1 : (aname == bname ? 0 : 1));
}

void set_guildmaster(string name) 
{
 guildmaster=LC(name);

 save_object(SERVERO);
}
string query_guildmaster() {return guildmaster;}

int query_member(string name)
{
 return (member_array(LC(name),members)==-1 ? 0 : 1);
}

void restrict_member(string name)
{
 string *pl;
 object tr;
 string mail_mesg;

 pl=m_indexes(restrict);
 if(member_array(LC(name),pl)!=-1)
  {
   write(C(LC(name))+" is already restricted from training!\n");
   return;
  }

 if(!query_member(name))
  {
   write(C(LC(name))+" is not Trickster!\n");
   return;
  }

 if(LC(name)==TP->query_real_name())
  {
   write("Restrict yourself from training?? ARE YOU MAD??\n");
   return;
  }

 if(!has_autority(TP->query_name(),name))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 tell_room(ENV(TP),C(LC(name))+" was restricted from training "+
   "by "+TP->query_name()+".\n");
 tr=find_player(LC(name));
 if(tr) tr->catch_msg("You have been restricted from training by "+
   "Tricksters Council.\n\n");
 else
  {
   mail_mesg="You have disappointed me , "+C(LC(name))+"!\n"+
	     "You now restricted from training!\n"+
	     "Prove your faith and you will be allowed back.\n\n";
   MAIL("Restriction","Kina",name,mail_mesg);
  }

 restrict+=([LC(name):TP->query_real_name()]);
 save_object(SERVERO);
}

int has_autority(string executor,string executed)
{
 if(query_jamadar(LC(executor)) && 
   (query_jamadar(LC(executed)) || query_leader(LC(executed))))
     return 0;

 return 1;
}

void unrestrict_member(string name)
{
 string *pl;
 object tr;
 string mail_mesg;

 pl=m_indexes(restrict);
 if(member_array(LC(name),pl)==-1)
  {
   write("But "+C(LC(name))+" is not restricted!\n");
   return;
  }

 if(!has_autority(TP->query_name(),name))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 tr=find_player(LC(name));
 tell_room(ENV(TP),TP->query_name()+" lifts restriction from "+
   C(LC(name))+".\n");
 if(tr) tr->catch_msg("Your restriction has been lifted by "+
   "Tricksters Council.\n");
 else
  {
   mail_mesg="You have proven your faith , "+C(LC(name))+"!\n"+
	     "Restriction from your training has been lifted!\n"+
	     "Serve me , Kina , the Goddess of Mischief!\n\n";
   MAIL("Restriction","Kina",name,mail_mesg);
  }

 restrict=m_delete(restrict,LC(name));
 save_object(SERVERO);
}

string restrict_string()
{
 int i;
 string *ind;
 string res="";

 ind=m_indexes(restrict);
 if(!sizeof(ind)) return "No restrictions at the moment.\n";

 for(i=0;i<sizeof(ind);i++)
   res+=sprintf("  %-12s %s\n",C(ind[i]),C(restrict[ind[i]]));
 return res;
}

void set_max_jamadar(int num)
{
 if(guildmaster!=TP->query_real_name())
  {
   write("You don't have authority to do that.\n");
   return;
  }

 if(sizeof(jamadar)>num)
  {
   write(sprintf("You cannot reduce maximum Jamadars number since %d "+
     "Jamadars are already registred!\n",sizeof(jamadar)));
   return;
  }

 max_jamadar=num;
 tell_room(ENV(TP),sprintf("%s sets number of maximum Jamadars "+
   "allowed to %d.\n",TP->query_name(),num));
 save_object(SERVERO);
}

int query_max_jamadar() {return max_jamadar;}

int query_baned(string name)
{
 return (member_array(LC(name),m_indexes(baned))==-1 ? 0 : 1);
}

int query_applicant(string name)
{
 return(member_array(LC(name),m_indexes(apply))==-1 ? 0 : 1);
}

void add_apply(string name,string text,string prev_guilds)
{
 string title,occ,lay,race,gender_str,race_str,mortal_level;
 object pl;

 pl=find_player(name);
 title=pl->query_title();
 occ=pl->query_guild_name_occ();
 if(!occ) occ="none";
 lay=pl->query_guild_name_lay();
 if(!lay) lay="none";
 race=pl->query_guild_name_race();
 if(!race) race="none";
 gender_str=pl->query_gender_string();
 race_str=pl->query_race_name();
 mortal_level=pl->query_exp_title();

 apply+=([name: ({title,mortal_level,gender_str,race_str,occ,lay,race,
		  prev_guilds,({ ({time(),C(LC(name)),text}) }) ,
                  0,"",0})]);
 save_object(SERVERO);
}

void fill_apply()
{
 if(query_member(TP->query_name()))
  {
   write("But you already Trickster!\n");
   return;
  }

 if(query_applicant(TP->query_name()))
  {
   write("You have already applied to Tricksters!\n"+
     "If you wish to reapply you'd better discard your application.\n");
   return;
  }

 if(query_baned(TP->query_name()))
  {
   write("You were baned by Council from this guild. You cannot apply.\n"+
     "You can <appeal banishment> though.\n");
   return;
  }

 if(apply_block)
  {
   write("Tricksters are currently closed for new members.\n"+
         "Please try later.\n");
   return;
  }

 write("\n\nUpon filling this form the following information about "+
   "yourself will be sent to Tricksters Council AUTOMATICALY: name "+
   ", full title , mortal level, gender , race and your current "+
   "guilds.\n"+
   "Do you still want to fill the application form(Yes/No)?\n");
 input_to("confirm_apply");
}

void confirm_apply(string str)
{
 string a;

 if(!str)
  {
   write("Yes or No?\n");
   input_to("confirm_apply");
   return;
  }

 a=LC(str);
 if(a!="y" && a!="ye" && a!="yes" && a!="n" && a!="no")
  {
   write("Yes or No?\n");
   input_to("confirm_apply");
   return;
  }

 if(a=="n" || a=="no")
  {
   write("\nYou stop filling application and put form aside.\n\n");
   return;
  }

 write("\n\nEnter here ALL of guilds you used to be member of "+
   "before.\n~q to stop filling the application.\n");
 input_to("get_guilds");
}

void get_guilds(string str)
{
 string gld;

 gld=cut_spaces(str);
 if(!strlen(gld))
  {
   write("\n\nEnter here ALL of guilds you used to be member of "+
     "before.\n~q to stop filling the application.\n");
   input_to("get_guilds");
   return;
  }

 if(str=="~q")
  {
   write("You stop filling application and put form aside.\n");
   return;
  }

 TP->add_prop("_trick_i_prev_guilds",gld);
 write("\n\nNow write an application , that must contain the "+
   "following:\nYour short history , how did you find Tricksters "+
   "guild and why you wish to join Tricksters.\n");
 EDIT("get_apply");
}

string cut_spaces(string str)
{
 string *ar,*res;
 int i,first,last;

 ar=explode(str," ");
 for(i=0;i<sizeof(ar);i++) if(strlen(ar[i])) break;
 first=i;
 for(i=sizeof(ar)-1;i>=0;i--) if(strlen(ar[i])) break;
 last=i;
 if(first==sizeof(ar) && last==-1) return "";
 res=({});
 for(i=first;i<=last;i++) res=res+({ ar[i] });
 return implode(res," ");
}

void get_apply(string str)
{
 if(!strlen(str))
  {
   write("\n\nEmpty application - aborting.\n\n");
   return;
  }

 write("\n\nYour application has been stored and sent to Council.\n"+
   "Please be patient and wait for reply.\n");
 add_apply(TP->query_real_name(),str,
   TP->query_prop_setting("_trick_i_prev_guilds"));
}

string apply_string()
{
 int i;
 mixed *ind,*dt;
 string res;

 ind=m_indexes(apply);

 if(!sizeof(ind)) return "No applicants currently.\n";
 
 res=sprintf("%-12s %s\n","Name","Apply date")+
   "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
 for(i=0;i<sizeof(ind);i++)
  {
   dt=apply[ind[i]];
   res+=sprintf("%-12s %s\n",ind[i],ctime(((dt[8])[0])[0]));
  }

 return res;
}

string get_applicant_info(string name)
{
 mixed *dt,*respond;
 string res;
 int i;

 if(!query_applicant(name)) return C(LC(name))+" is not applicant!\n";

 dt=apply[LC(name)];
 respond=dt[8];

 res="Name: "+C(LC(name))+"\n"+
     "Title: "+dt[0]+"\n"+
     "Mortal level: "+dt[1]+"\n"+
     "Gender: "+dt[2]+"\n"+
     "Race: "+dt[3]+"\n"+
     "OCC guild: "+dt[4]+"\n"+
     "Lyaman guild: "+dt[5]+"\n"+
     "Race guild: "+dt[6]+"\n"+
     "Previous guilds: "+dt[7]+"\n"+
     "  On "+ctime((respond[0])[0])+" "+(respond[0])[1]+
     " has applied:\n"+
     "=============================================================\n"+
     (respond[0])[2]+"\n"+
     "=============================================================\n"+
     "                Responds to this application                 \n"+
     "=============================================================\n";

 for(i=1;i<sizeof(respond);i++)
   res+="  On "+ctime((respond[i])[0])+" "+(respond[i])[1]+
     " has responded:\n\n"+(respond[i])[2]+"\n"+
     "============================================================\n";
 return res;
}

void discard_apply(string name)
{
 if(!query_applicant(name))
  {
   write("But you have never applied!\n");
   return;
  }

 apply=m_delete(apply,LC(name));
 write("You find your application form , tear in off and throw out.\n");
 save_object(SERVERO);
}

string view_apply(string name)
{
 mixed *dt,*respond;
 string res;
 int i;

 if(!query_applicant(name))
   return "You never applied to Tricksters.\n";

 dt=apply[LC(name)];
 respond=dt[8];
 res="============================================================\n"+
     "  On "+ctime((respond[0])[0])+" you have applied:\n\n"+
     (respond[0])[2]+
     "============================================================\n"+
     "              Responds to your applications :               \n"+
     "============================================================\n";
 for(i=1;i<sizeof(respond);i++)
   res+="  On "+ctime((respond[i])[0])+" "+
     (C(LC(name))==(respond[i])[1] ? " you have " : " Council has ")+
     "responded:\n\n"+(respond[i])[2]+"\n"+
     "============================================================\n";

 return res;
}

void respond_apply(string name)
{
 if(!query_applicant(name) && !query_appeal(name))
  {
   write(C(LC(name))+" is niether an applicant nor an appealer!\n");
   return;
  }

 if(query_applicant(name)) 
   write("\n\nRespond to "+C(LC(name))+"'s application:\n");
 if(query_applicant(name)) 
   write("\n\nRespond to "+C(LC(name))+"'s appeal:\n");

 TP->add_prop("_trick_i_respond_to",LC(name));
 if(query_applicant(name)) EDIT("do_respond");
 if(query_appeal(name)) EDIT("do_respond_appeal");
}

void do_respond(string text)
{
 string name;

 if(!strlen(text))
  {
   write("No text entered - aborting\n");
   return;
  }

 name=TP->query_prop_setting("_trick_i_respond_to");
 add_respond(name,text);
 write("Your respond has been stored.\n");
}

void add_respond(string name,string text)
{
 mixed *dt,*respond;
 object pl;
 string msg;

 dt=apply[LC(name)];
 respond=dt[8];
 respond+=({ ({ time() , TP->query_name() , text }) });
 dt[8]=respond;
 apply[LC(name)]=dt;
 save_object(SERVERO);

 msg="Hail, applicant!\nMy Council has responded to your "+
   "application! You may want to visit the guildhall and check it!\n";
 pl=find_player(LC(name));
 if(!pl)
   MAIL("Council respond","Kina",LC(name),msg);
 else pl->catch_msg("You feel Kina's presence in your mind. She "+
   "tells you:\n"+msg);
}

void reject_applicant(string name)
{
 if(!query_applicant(name))
  {
   write(C(LC(name))+" is not an applicant!\n");
   return;
  }

 if(query_rejected(name))
  {
   write(C(LC(name))+" was already rejected by "+
     query_rejected(name)+".\n");
   return;
  }

 if(query_approved(name))
  {
   write("Cannot reject approved applicants!\n");
   return;
  }

 set_reject_by(name,TP->query_name());
 TP->add_prop("_trick_i_respond_to",LC(name));
 do_respond("Greetings.\nYou have been rejected by Tricksters "+
   "Council.\n");
 tell_room(ENV(TP),C(LC(name))+"'s application was rejected by "+
   TP->query_name()+".\n");
}

mixed query_rejected(string name)
{
 mixed *dt;

 dt=apply[LC(name)];
 return (dt[9]==2 ? dt[10] : 0);
}

void set_reject_by(string name,string by)
{
 mixed *dt;

 dt=apply[LC(name)];
 dt[9]=2;
 dt[10]=by;
 dt[11]=time();
 apply[LC(name)]=dt;
}

string rejected_string()
{
 mixed *names,*ind;
 mixed *dt;
 int i;
 string res;

 ind=m_indexes(apply);
 names=({});
 for(i=0;i<sizeof(ind);i++)
  {
   dt=apply[ind[i]];
   if(dt[9]==2) names+=({ ({ ind[i] , dt[10] , dt[11] }) });
  }

 if(!sizeof(names)) return "No rejections yes.\n";
 res=sprintf("%-12s %12s %s\n","Name","Rejected by","Rejection Date")+
   "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
 for(i=0;i<sizeof(names);i++)
   res+=sprintf("%-12s %-12s %s\n",(names[i])[0],(names[i])[1],
     ctime((names[i])[2]));
 return res;
}

string approved_string()
{
 mixed *names,*ind;
 mixed *dt;
 int i;
 string res;

 ind=m_indexes(apply);
 names=({});
 for(i=0;i<sizeof(ind);i++)
  {
   dt=apply[ind[i]];
   if(dt[9]==1) names+=({ ({ ind[i] , dt[10] , dt[11] }) });
  }

 if(!sizeof(names)) return "No approvals yes.\n";
 res=sprintf("%-12s %12s %s\n","Name","Approved by","Approval Date")+
   "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
 for(i=0;i<sizeof(names);i++)
   res+=sprintf("%-12s %-12s %s\n",(names[i])[0],(names[i])[1],
     ctime((names[i])[2]));
 return res;
}

mixed query_approved(string name)
{
 mixed *dt;

 dt=apply[LC(name)];
 return (dt[9]==1 ? dt[10] : 0);
}

void approve_applicant(string name)
{
 if(!query_applicant(name))
  {
   write(C(LC(name))+" is not an applicant!\n");
   return;
  }

 if(query_approved(name))
  {
   write(C(LC(name))+" was already approved by "+
     query_approved(name)+".\n");
   return;
  }

 if(query_rejected(name))
  {
   write("Cannot approve rejected applicants!\n");
   return;
  }

 set_approve_by(name,TP->query_name());
 TP->add_prop("_trick_i_respond_to",LC(name));
 do_respond("Greetings.\nYou have been approved by Tricksters "+
   "Council.\n");
 tell_room(ENV(TP),C(LC(name))+"'s application was approved by "+
   TP->query_name()+".\n");
}

void set_approve_by(string name,string by)
{
 mixed *dt;

 dt=apply[LC(name)];
 dt[9]=1;
 dt[10]=by;
 dt[11]=time();
 apply[LC(name)]=dt;
}

void revert_apply(string name)
{
 string mail_mesg;
 mixed *dt;

 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 if(!query_rejected(name) && !query_approved(name))
  {
   write(C(LC(name))+" was niether rejected nor approved.\n");
   return;
  }

 if(query_rejected(name))
  {
   mail_mesg="Greetings!\n"+
     "You have been given second chance.\n"+
     "Your application is active once again , but you will have "+
     "to work harder this time!\n";
   MAIL("Second chance","Kina",name,mail_mesg);
   tell_room(ENV(TP),TP->query_name()+" reverts "+C(LC(name))+"'s "+
     "rejection.\n");
  }

 else
  {
   mail_mesg="Greetings!\n"+
     "Tricksters Council has changed his mind and your approval "+
     "will be reconsidered.\n"+
     "Your application remains active though.\n";
   MAIL("Approval reverted","Kina",name,mail_mesg);
   tell_room(ENV(TP),TP->query_name()+" reverts "+C(LC(name))+"'s "+
     "approval.\n");
  }

 dt=apply[LC(name)];
 dt[9]=0;
 dt[10]="";
 dt[11]=0;
 TP->add_prop("_trick_i_respond_to",LC(name));
 do_respond(mail_mesg);
}

void reply_council(string name)
{
 if(query_applicant(name))
  {
   if(query_rejected(name))
    {
     write("Halas! Your application was rejected!\n");
     return;
    }

   EDIT("do_reply");
  }

 if(query_appeal(name))
  {
   EDIT("do_reply_appeal");
  }
}

void do_reply(string text)
{
 mixed *dt,*respond;
 string name;

 if(!strlen(text))
  {
   write("No text entered - aborting\n");
   return;
  }

 name=TP->query_real_name();
 dt=apply[name];
 dt=apply[name];
 respond=dt[8];
 respond+=({ ({ time() , C(name) , text }) });
 dt[8]=respond;
 apply[name]=dt;

 write("Your reply has been sent to Council.\n");
 save_object(SERVERO);
}

void promote(string name,int lv)
{
 object pl;

 if(!query_member(name))
  {
   write(C(LC(name))+" is not Trickster!\n");
   return;
  }

 if(query_leader(name) || query_jamadar(name))
  {
   write("Cannot promote Jamadars.\n");
   return;
  }

 pl=find_player(LC(name));
 if(pl)
  {
   if(pl->query_trickster_level()==sizeof(titles))
    {
     write("Cannot promote "+C(LC(name))+" anymore.\n");
     return;
    }

   if(pl->query_trickster_level()+lv>sizeof(titles))
     write(sprintf(
       "Cannot promote "+C(LC(name))+" %d levels.\n"+
       C(PRO(pl))+" will be promoted only %d levels.\n",
       lv,sizeof(titles)-pl->query_trickster_level()));

   tell_room(ENV(TP),
     C(LC(name))+" was promoted by "+TP->query_name()+".\n");
   pl->catch_msg("You were promoted by "+TP->query_name()+".\n");
   do_promote(pl,lv);
   return;
  }

 add_promote(name,lv);
}

void do_promote(object pl,int lv)
{
 int lev;

 lev=pl->query_trickster_level()+lv;
 if(lev>sizeof(titles)) lev=sizeof(titles);
 if(lev<1) lev=1;
 pl->set_skill(SS_KILL_POINTS,(titles[lev-1])[1]*AVG_PTS);
 if(pl->query_skill(SS_STRANGLE)>pl->query_trickster_level()*7)
   pl->set_skill(SS_STRANGLE,pl->query_trickster_level()*7);
 if(lv<0) present(RUMEL_DESC,pl)->update_level();
}

void add_promote(string name,int lv)
{
 mixed *dt;
 string prom_str;

 if(member_array(LC(name),m_indexes(to_be_promoted))==-1)
   to_be_promoted+=([LC(name):({ lv,TP->query_name() })]);
 else
  {
   dt=to_be_promoted[LC(name)];
   if(query_leader(dt[1]) && TP->query_real_name()!=LC(dt[1]))
    {
     write("You don't have authority to cancel "+dt[1]+"'s decision.\n");
     return;
    }
   dt=({ lv,TP->query_name() });
   to_be_promoted[LC(name)]=dt;
  }

 prom_str=(lv<0 ? "demoted" : "promoted");
 write(C(LC(name))+" is not online.\nIf possible , he/she will be "+
   prom_str+" as soon as he/she logs in.\n");
 save_object(SERVERO);
}

void check_promote_on_logon(object pl)
{
 string name,*ind,prom_by;
 mixed *dt;
 int lv,i;

 name=pl->query_real_name();
 ind=m_indexes(to_be_promoted);
 if(member_array(name,ind)==-1) return;

 dt=to_be_promoted[name];
 lv=dt[0];prom_by=dt[1];
 if(lv>0 && pl->query_trickster_level()!=sizeof(titles))
  {
   pl->catch_msg("In your absence you were promoted by "+prom_by+".\n");
   do_promote(pl,lv);
  }

 if(lv<0 && pl->query_trickster_level()!=1)
  {
   pl->catch_msg("In your absence you were demoted by "+prom_by+".\n");
   do_promote(pl,lv);
  }

 to_be_promoted=m_delete(to_be_promoted,name);
 save_object(SERVERO);
}

void demote(string name,int lv)
{
 object pl;

 if(!query_member(name))
  {
   write(C(LC(name))+" is not Trickster!\n");
   return;
  }

 if(query_leader(name) || query_jamadar(name))
  {
   write("Cannot demote Jamadars.\n");
   return;
  }

 pl=find_player(LC(name));
 if(pl)
  {
   if(pl->query_trickster_level()==1)
    {
     write("Cannot demote "+C(LC(name))+" anymore.\n");
     return;
    }

   if(pl->query_trickster_level()-lv<1)
     write(sprintf(
       "Cannot demote "+C(LC(name))+" %d levels.\n"+
       C(PRO(pl))+" will be demoted only %d levels.\n",
       lv,pl->query_trickster_level()-1));

   tell_room(ENV(TP),
     C(LC(name))+" was demoted by "+TP->query_name()+".\n");
   pl->catch_msg("You were demoted by "+TP->query_name()+".\n");
   do_promote(pl,-lv);
   return;
  }

 add_promote(name,-lv);
}

string promotion_plan_string()
{
 int i,lv;
 string res,prom_str,prom_by;
 mixed *ind,*dt;

 ind=m_indexes(to_be_promoted);
 if(!sizeof(ind)) return "No promotes/demotes planned.\n";

 res="Following demotes/promotes are planned:\n";
 for(i=0;i<sizeof(ind);i++)
  {
   dt=to_be_promoted[ind[i]];
   lv=dt[0];prom_by=dt[1];
   prom_str=(lv<0 ? "demotion" : "promotion");
   res+=sprintf(" - %s - %s %d levels by %s\n",
     C(ind[i]),prom_str,(lv<0 ? -lv : lv),prom_by);
  }

 return res;
}

void cancel_promotion(string name)
{
 mixed *dt;

 if(member_array(LC(name),m_indexes(to_be_promoted))==-1)
  {
   write(C(LC(name))+" hasn't been planned to be promoted/demoted.\n");
   return;
  }

 dt=to_be_promoted[LC(name)];
 if(query_leader(dt[1]) && TP->query_name()!=dt[1])
  {
   write("You don't have authority to cancel "+dt[1]+"'s decision.\n");
   return;
  }

 tell_room(ENV(TP),TP->query_name()+" cancels "+C(LC(name))+"'s "+
   (dt[0]<0 ? "demotion" : "promotion")+".\n");
 to_be_promoted=m_delete(to_be_promoted,LC(name));
 save_object(SERVERO);
}

void punish_member(string name)
{
 object pl;
 string mail_mesg;

 if(query_punished(name))
  {
   write(C(LC(name))+" is already punished!\n");
   return;
  }

 if(!query_member(name))
  {
   write(C(LC(name))+" is not Trickster!\n");
   return;
  }

 if(LC(name)==TP->query_real_name())
  {
   write("Punish yourself? Feeling wierd today?\n");
   return;
  }

 tell_room(ENV(TP),TP->query_name()+" punishes "+C(LC(name))+
   " by disabling abilities.\n");
 pl=find_player(LC(name));
 if(pl)
  {
   pl->catch_msg("You have been restricted from using abilities by "+
     "Tricksters Council.\n"+
     "Suddenly your stick , kit and rumel are disintergated!\n");
   present(STICK_DESC,pl)->remove_object();
   present(KIT_DESC,pl)->remove_object();
   present(RUMEL_DESC,pl)->remove_object();
  }
 else
  {
   mail_mesg="You have disgraced me , "+C(LC(name))+"!\n"+
             "You now restricted from using abilities!\n"+
	     "Prove your faith and I shell return then back.\n\n";
   MAIL("Restriction","Kina",name,mail_mesg);
  }

 punish+=([ LC(name):time() ]);
 save_object(SERVERO);
}

int query_punished(string name)
{
 return (member_array(LC(name),m_indexes(punish))==-1 ? 0 : 1);
}

void unpunish_member(string name)
{
 object pl;
 string mail_mesg;

 if(!query_punished(name))
  {
   write(C(LC(name))+" is not punished!\n");
   return;
  }

 tell_room(ENV(TP),TP->query_name()+" removes punishment from "+
   C(LC(name))+".\n");
 pl=find_player(LC(name));
 if(pl) pl->catch_msg("Tricksters Council has removed a punishment "+
   "from you. You'd better run to guild and recover yor staff to be "+
   "able to use abilities again!\n");
 else
  {
   mail_mesg="You have been forgiven , "+C(LC(name))+"!\n"+
	     "Restriction from using abilities has been lifted!\n"+
	     "Serve me , Kina , the Goddess of Mischief!\n\n";
   MAIL("Restriction","Kina",name,mail_mesg);
  }

 punish=m_delete(punish,LC(name));
 save_object(SERVERO);
}

int query_restricted(string name)
{
 return (member_array(LC(name),m_indexes(restrict))==-1 ? 0 : 1);
}

string punished_string()
{
 int i;
 mixed *ind;
 string res;

 ind=m_indexes(punish);
 if(!sizeof(ind)) return "No punishments at the moment.\n\n";

 res=sprintf("%-12s %s\n","Name","Punishment date")+
   "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
 for(i=0;i<sizeof(ind);i++)
   res+=sprintf("%-12s %s\n",ind[i],ctime(punish[ind[i]]));

 return res;
}

void save_me() {baned=([]);save_object(SERVERO);}

void add_baned(string name)
{
 object pl;
 string mail_mesg;

 if(query_baned(name))
  {
   write(C(LC(name))+" is already baned!\n");
   return;
  }

 if(!query_member(name))
  {
   write(C(LC(name))+" is not Trickster.\n");
   return;
  }

 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 tell_room(ENV(TP),TP->query_name()+" bans "+C(LC(name))+
   " from guild.\n");
 pl=find_player(LC(name));
 if(pl)
  {
   pl->catch_msg("You have been baned from Tricksters by Council!\n"+
     "Suddenly your stick , kit and rumel are disintergated!\n");
   pl->kick_out_trickster();
   check_inside(pl);
  }
 else
  {
   mail_mesg=
     "You have disgraced me!!!\n"+
     "You have been banished from Tricksters!\n\n"+
   MAIL("AND DON'T COME BACK!","Kina",name,mail_mesg);
  }

 baned+=([ LC(name):time() ]);
 save_object(SERVERO);
}

void remove_baned(string name)
{
 if(!query_baned(name))
  {
   write(C(LC(name))+" is not banned.\n");
   return;
  }

 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 tell_room(ENV(TP),TP->query_name()+" lifts ban from "+C(LC(name))+".\n");
 baned=m_delete(baned,LC(name));
 save_object(SERVERO);
}

string baned_string()
{
 mixed *ind;
 int i;
 string res;

 ind=m_indexes(baned);
 if(!sizeof(ind)) return "No baned players for a moment.\n";

 res=sprintf("%-12s %s\n","Name","Ban date")+
   "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
 for(i=0;i<sizeof(ind);i++)
   res+=sprintf("%-12s %s\n",C(ind[i]),ctime(baned[ind[i]]));

 return res;
}

void check_inside(object pl)
{
 if(ENV(pl)->inside_trickster_guild())
  {
   pl->catch_msg("An apparition of Kina to you.\n"+
     "She tells you: Begone , disgrase!!!\n");
   pl->catch_msg("For a brief moment world around you fades away...\n");
   pl->catch_msg("You have been thrown out!\n");
   pl->move_living("X",pl->query_default_start_location());
  }
}

void check_in(string name) {check_inside(find_player(name));}

void remove_apply(string name)
{
 apply=m_delete(apply,LC(name));
 save_object(SERVERO);
}

int query_appeal(string name)
{
 return (member_array(LC(name),m_indexes(appeal))==-1 ? 0 : 1);
}

void appeal_banish(string name)
{
 if(!query_baned(name))
  {
   write("But you are not banished!\n");
   return;
  }

 if(query_appeal(name))
  {
   write("But you have already appealed!\n"+
	 "Discard your current appeal to reappeal.\n");
   return;

  }

 write("\n\nNow explain the Council why should you be unbanned.\n");
 EDIT("do_appeal");
}

void do_appeal(string text)
{
 if(!strlen(text))
   {
    write("No text - aborting.\n");
    return;
   }

 write("Your appeal was sent to Council.\n");
 appeal+=([ TP->query_real_name(): 
   ({ ({text,time(),TP->query_name() }) }) ]);
 save_object(SERVERO);
}

void discard_appeal(string name)
{
 if(!query_appeal(name))
  {
   write("But you have never appealed.\n");
   return;
  }

 write("You find your appeal form and tear it off.\n");
 appeal=m_delete(appeal,LC(name));
 save_object(SERVERO);
}

string appeal_string()
{
 int i;
 mixed *ind,*dt;
 string res;

 ind=m_indexes(appeal);
 if(!sizeof(ind)) return "No appeals for the moment.\n";

 res=sprintf("%-12s %s\n","Name","Appeal date")+
   "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";

 for(i=0;i<sizeof(ind);i++)
  {
   dt=appeal[ind[i]];
   res+=sprintf("%-12s %s\n",ind[i],ctime((dt[0])[1]));
  }

 return res;
}

string get_appeal(string name)
{
 mixed *dt;
 int i;
 string res;

 if(!query_appeal(name)) return "No such person appealed.\n";

 dt=appeal[LC(name)];
 res="-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
     "  On "+ctime((dt[0])[1])+" "+(dt[0])[2]+" has appealed:\n\n"+
     "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
     (dt[0])[0]+"\n";
 for(i=1;i<sizeof(dt);i++)
   res+="    On "+ctime((dt[i])[1])+" "+(dt[i])[2]+" has replied:\n\n"+
     (dt[i])[0]+"\n"+
     "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
 return res;
}

void do_reply_appeal(string text)
{
 mixed *dt;
 string name;

 if(!strlen(text))
  {
   write("No text entered - aborting.\n");
   return;
  }

 name=TP->query_real_name();
 dt=appeal[name];
 dt+=({ ({ text , time() , C(name) }) });
 appeal[name]=dt;
 write("Your reply was sent to Council.\n");
 save_object(SERVERO);
}

void do_respond_appeal(string text)
{
 string name;

 if(!strlen(text))
  {
   write("No text entered - aborting\n");
   return;
  }

 name=TP->query_prop_setting("_trick_i_respond_to");
 add_respond_appeal(name,text);
 write("Your respond has been stored.\n");
}

void add_respond_appeal(string name,string text)
{
 mixed *dt;

 dt=appeal[LC(name)];
 dt+=({ ({ text , time() , TP->query_name() }) });
 appeal[LC(name)]=dt;
 save_object(SERVERO);
}

string get_info(string name)
{
 if(query_applicant(name)) return get_applicant_info(name);
 if(query_appeal(name)) return get_appeal(name);

 return "No such applicant or appeal.\n";
}

string view_appeal(string name)
{
 mixed *dt;
 int i;
 string res;

 if(!query_appeal(name)) return "But you never appealed!\n";

 dt=appeal[LC(name)];
 res="-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
     "  On "+ctime((dt[0])[1])+" you have appealed:\n"+
     "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"+
     (dt[0])[0]+"\n";
 for(i=1;i<sizeof(dt);i++)
   res+="    On "+ctime((dt[i])[1])+
        (C(LC(name))==(dt[i])[2] ? " you have " : " Council has ")+
        "replied:\n\n"+(dt[i])[0]+"\n"+
        "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
 return res;
}

void dismiss_apply(string name)
{
 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 apply=m_delete(apply,LC(name));
 tell_room(ENV(TP),TP->query_name()+" dismisses "+C(LC(name))+
   "'s application.\n");
 save_object(SERVERO);
}

void dismiss_appeal(string name)
{
 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 appeal=m_delete(appeal,LC(name));
 tell_room(ENV(TP),TP->query_name()+" dismisses "+C(LC(name))+
   "'s appeal.\n");
 save_object(SERVERO);
}

void dismiss(string name)
{
 if(query_applicant(name)) 
  {
   dismiss_apply(name);
   return;
  }

 if(query_appeal(name))
  {
   dismiss_appeal(name);
   return;
  }

 write(C(LC(name))+" has niether applied nor appealed.\n");
}

void block_apply()
{
 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 if(apply_block)
  {
   write("Guild is already closed for applicants.\n");
   return;
  }

 tell_room(ENV(TP),TP->query_name()+" has closed guild for "+
   "applicants.\n");
 apply_block=1;
 save_object(SERVERO);
}

void block_remove()
{
 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 if(!apply_block)
  {
   write("Guild is already open for applicants.\n");
   return;
  }

 tell_room(ENV(TP),TP->query_name()+" has opened guild for "+
   "applicants.\n");
 apply_block=0;
 save_object(SERVERO);
}

int query_apply_block() {return apply_block;}

string *query_council() {return ({leader})+jamadar;}

string *get_members() {return members;}

void tell_all(string msg)
{
 int i;
 object pl;

 for(i=0;i<sizeof(members);i++)
  {
   pl=find_player(members[i]);
   if(!pl) continue;
   if(!interactive(pl)) continue;
   pl->catch_msg("Suddenly you feel someone's presence in your mind.\n");
   pl->catch_msg("Kina tells you:\nHail , my loyal worshipers!\n");
   pl->catch_msg(msg+"\n");
  }
}

void discard_respond(string name)
{
 mixed *responds,*last_resp;

 if(!query_applicant(name))
  {
   write(C(LC(name))+" is not applicant!\n");
   return;
  }

 if(!query_leader(TP->query_name()))
  {
   write("You don't have authority to do that.\n");
   return;
  }

 responds=(apply[LC(name)])[8];
 last_resp=responds[sizeof(responds)-1];
 if(LC(last_resp[1])==LC(name))
  {
   write("You havn't responded lately to this apply.\n");
   return;
  }

 tell_room(ENV(TP),QCTNAME(TP)+" discards latest respond to "+
   C(LC(name))+"'s apply.\n");

 responds-=({ last_resp });
 (apply[LC(name)])[8]=responds;
 save_object(SERVERO);
}

void save() { save_object(SERVERO); }

