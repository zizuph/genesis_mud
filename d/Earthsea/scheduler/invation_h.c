inherit "/lib/event/event_handler";

#include <macros.h>

#include "defs.h"

#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

mapping kills;  // ([name: ({ kills,points,monsters_left }) ])
mapping death; // Players deaths ([player:deaths])
int monsters_left; // Invaders left
string *mon,*pts,*rooms; // Event props
float inter;            // Event props
int *quant,teaming,wonder,aggr; // Event props
mixed *formation; // Event props
int a_handle; // Alarm handle
int mon_count; // Global counter, used to clone monsters first time
int team_no,team_ind; // Global counters of current team and index
int leader; // Current team leader index for cloned monsters to join
object *portal; // Rooms with open portals
object *monsters; // Array of pointers to all cloned monsters
mixed *stats; // Array of statistics, filled after event ends
int total; // Total of monsters

void create_object()
{
 ::create_object();
 kills=([ ]);
 death=([ ]);
}

int arr_sum(int *arr)
{
 int i,res=0;

 for(i=0;i<sizeof(arr);i++) res+=arr[i];

 return res;
}

void init()
{
 ::init();

 add_action("report","report");
}

mixed *validate_formation()
{
 int i,j,mons,*qa,*rqa;
 string *f,*str,*strqa;
 mixed *errs,*form;

 errs=({ });
 if(prop_not_set("teaming")) return errs;

 if(prop_not_set("formation"))
   return ({ ({ "formation","Prop must be set." }) });

 f=query_prop_value("formation");
 mons=sizeof(query_prop_value("monsters"));
 strqa=query_prop_value("quant");
 rqa=allocate(sizeof(strqa));
 for(i=0;i<sizeof(strqa);i++) rqa[i]=atoi(strqa[i]);

 form=allocate(sizeof(f));
 for(i=0;i<sizeof(f);i++)
  {
   str=explode(f[i]," ");
   form[i]=allocate(sizeof(str));
   for(j=0;j<sizeof(str);j++)
    {
     if(!is_number(str[j]))
      {
       errs+=({ ({ "formation","Invalid number: "+str[j] }) });
       form[i][j]=-1;
      }
     else
      {
       form[i][j]=atoi(str[j]);
       if(form[i][j]<1 || form[i][j]>mons)
         errs+=({ ({ "formation","Invalid monster index: "+str[j] }) });
      }
    }
  }

 if(sizeof(errs)) return errs;

 qa=allocate(mons);
 for(i=0;i<sizeof(form);i++)
   for(j=0;j<sizeof(form[i]);j++)
     qa[form[i][j]-1]++;

 for(i=0;i<mons;i++)
   if(qa[i]!=rqa[i])
     return ({ ({"formation","Formation is invalid"}) });

 return ({ });
}

mixed *validate_monsters()
{
 int i,flag;
 string *mon;
 mixed *errs=({ });
 object obj;
 mixed repeat;

 mon=query_prop_value("monsters");
 if(prop_not_set("monsters"))
   return ({ ({"monsters","Prop not set"}) });

 flag=1;
 for(i=0;i<sizeof(mon);i++)
  {
   mon[i]=fix_file(mon[i]);
   if(!file_exists(mon[i]))
    {
     flag=0;
     errs+=({ ({"monsters","File does not exist: "+mon[i]}) });
    }
  }

 if(!flag) return errs;

 repeat=is_unique(mon);
 if(sizeof(repeat)) errs+=({ ({"monsters","The following files "+
   "are repeated: "+implode((string *)repeat,",") }) });
 else
  {
   for(i=0;i<sizeof(mon);i++)
    {
     setuid();
     seteuid(getuid());
     obj=clone_object(mon[i]);
     if(!obj)
      {
       errs+=({ ({"monsters","failed to load: "+mon[i]}) });
       continue;
      }
     if(!function_exists("create_living",obj))
       errs+=({ ({"monsters",mon[i]+" is not a living."}) });
     obj->remove_object();
    }
  }

 return errs;
}

mixed *validate_points()
{
 string *p;
 int i;
 mixed *errs=({ });

 if(prop_not_set("points")) return ({ });

 p=query_prop_value("points");

 if(sizeof(p)!=sizeof(query_prop_value("monsters")))
   return ({ ({"points","Size of points must be equal to size of "+
     "monsters."}) });

 for(i=0;i<sizeof(p);i++)
   if(!is_number(p[i])) 
     errs+=({ ({"points",p[i]+": Invalid number."}) });
 
 return errs;
}

mixed *validate_rooms()
{
 mixed *err=({ });
 string *r,dom;
 int i,flag;
 mixed repeat;

 if(prop_not_set("rooms"))
   return ({ ({"rooms","Value must be set."}) });

 r=query_prop_value("rooms");
 flag=1;
 for(i=0;i<sizeof(r);i++)
  {
   r[i]=fix_file(r[i]);
   if(!file_exists(r[i]))
    {
     flag=0;
     err+=({ ({"rooms","File does not exist: "+r[i]+"."}) });
    }
  }

 if(!flag) return err;

 repeat=is_unique(r);
 if(sizeof(repeat)) err+=({ ({"monsters","The following rooms "+
   "are repeated: "+implode((string *)repeat,",") }) });

 dom=query_prop_value("domain");
 flag=1;
 for(i=0;i<sizeof(r);i++)
  {
   if(get_domain(r[i])!=dom)
    {
     err+=({ ({"rooms",r[i]+" must be in domain "+dom+"."}) });
     flag=0;
    }
  }

 if(!flag) return err;

 for(i=0;i<sizeof(r);i++)
  {
   (r[i])->blabla();
   if(!function_exists("create_room",find_object(r[i])))
     err+=({ ({"rooms",r[i]+" is not a room."}) });
  }

 return err;
}

mixed *validate_aggressive()
{
 if(prop_not_set("aggressive"))
   return ({ ({"aggressive","Value must be set."}) });

 return ({ });
}

mixed *validate_wandering()
{
 if(prop_not_set("wandering"))
   return ({ ({"wandering","Value must be set."}) });

 return ({ });
}

mixed *validate_teaming()
{
 if(prop_not_set("teaming"))
   return ({ ({"teaming","Value must be set."}) });

 return ({ });
}

mixed *validate_quant()
{
 string *p;
 int i;
 mixed *errs=({ });

 if(prop_not_set("quant"))
   return ({ ({"quant","Value must be set."}) });

 p=query_prop_value("quant");

 if(sizeof(p)!=sizeof(query_prop_value("monsters")))
   return ({ ({"quant","Size of quant must be equal to size of "+
     "monsters."}) });

 for(i=0;i<sizeof(p);i++)
   if(!is_number(p[i])) 
     errs+=({ ({"quant",p[i]+": Invalid number."}) });

 return errs;
}

mixed *validate_interval()
{
 if(query_prop_value("wandering")==1 && prop_not_set("interval"))
   return ({ ({"interval","Value must be set."}) });

 return ({ });
}

mixed *validate_death_penalty()
{
 if(prop_not_set("death_penalty"))
   return ({ ({"death_penalty","Value must be set."}) });

 return ({ });
}

mixed *validate_props()
{
 mixed *res,*monsters_err,*quant_err;

 res=::validate_props();

 monsters_err=validate_monsters();
 quant_err=validate_quant();

 res+=validate_points()+validate_rooms()+validate_aggressive()+
   validate_wandering()+validate_teaming()+validate_interval()+
   validate_death_penalty()+monsters_err+quant_err;

 if(!sizeof(monsters_err+quant_err)) res+=validate_formation();

 return res;
}

void place_monster()
{
 int pt,j,to_clone;
 string rm;
 object om,orm;

 if(mon_count==total)
  {
   remove_alarm(a_handle);
   for(j=0;j<sizeof(portal);j++)
     present("_invation_portal_",portal[j])->close_portal();
   return;
  }

 if(!teaming)
  {
   if(team_ind==quant[team_no])
    {team_ind=0; team_no++;}
   to_clone=team_no;
   rm=RND(rooms);
   team_ind++;
  }
 else
  {
   if(team_ind==sizeof(formation[team_no]))
    {team_ind=0; team_no++; leader=mon_count;}
   to_clone=formation[team_no][team_ind]-1;
   rm=rooms[team_no%sizeof(rooms)];
   team_ind++;
  }

 om=clone_object(mon[to_clone]);
 monsters[mon_count]=om;
 if(aggr) om->set_aggressive(1);
 clone_object(SCHEDULER_DIR+"inv_shadow")->shadow_me(om);
 if(wonder) om->set_interval(inter);
 om->set_handler(TO);
 sscanf(pts[to_clone],"%d",pt);
 om->set_pts(pt);

 (rm)->blablabla();
 orm=find_object(rm);
 if(member_array(orm,portal)==-1)
  {
   clone_object(SCHEDULER_DIR+"portal")->open_portal(orm);
   portal+=({ orm });
  }

 om->move(orm);
 om->command("emote jumps from the portal and lands here!");

 if(teaming)
  {
   if(mon_count==leader) 
    {
     om->is_leader();
     om->command("shout Follow me! CHAAAAAARGE!!!");
    }
   else
    {
     om->command("cackle demon");
     tell_room(orm,QCTNAME(om)+" joins the team of "+
       QNAME(monsters[leader])+"\n");
     monsters[leader]->team_join(om);
    }
  }
 else
  {
   om->is_leader();
   om->command("shout Follow me! CHAAAAAARGE!!!");
  }

 om->go();
 mon_count++;
}

void start_event()
{
 int i,j;
 string *qn,*frm,*tmp;

 ::start_event();

 mon=query_prop_value("monsters");
 if(prop_not_set("points"))
  {
   pts=allocate(sizeof(mon));
   for(i=0;i<sizeof(pts);i++) pts[i]="1";
  }
 else pts=query_prop_value("points");
 rooms=query_prop_value("rooms");
 qn=query_prop_value("quant");
 quant=allocate(sizeof(qn));
 for(i=0;i<sizeof(qn);i++) quant[i]=atoi(qn[i]);
 monsters_left=arr_sum(quant);
 total=monsters_left;
 teaming=query_prop_value("teaming");
 frm=query_prop_value("formation");
 aggr=query_prop_value("aggressive");
 wonder=query_prop_value("wandering");
 inter=itof(query_prop_value("interval"));

 if(teaming)
  {
   formation=allocate(sizeof(frm));
   for(i=0;i<sizeof(frm);i++)
    {
     tmp=explode(frm[i]," ");
     formation[i]=allocate(sizeof(tmp));
     for(j=0;j<sizeof(tmp);j++) formation[i][j]=atoi(tmp[j]);
    }
  }

 portal=({ }); mon_count=0; team_no=0; team_ind=0; leader=0;
 monsters=allocate(total);

 setuid();
 seteuid(getuid());
 a_handle=set_alarm(0.5,0.5,&place_monster());
}

mixed query_kills() {return kills;}

void stop_clone() {remove_alarm(a_handle);}

int sort_func(mixed *a,mixed *b)
{
 if(a[2]<b[2]) return -1;
 if(a[2]>b[2]) return 1;

 if(a[1]<b[1]) return -1;
 if(a[1]>b[1]) return 1;

 if(a[3]<b[3]) return 1;
 return -1;
}

void set_winner()
{
 int i,j,max_ind;
 mixed *ind,*data,*tmp,*max_data;

 stats=({ });
 ind=m_indexes(kills);
 for(i=0;i<sizeof(ind);i++)
  {
   data=kills[ind[i]];
   stats+=({ ({ ind[i],data[0],data[1],data[2] }) });
  }

 if(!sizeof(stats)) {Winner="Noone"; return;}

 for(i=0;i<sizeof(stats);i++)
  {
   max_ind=i; 
   max_data=({ stats[i][0],stats[i][1],stats[i][2],stats[i][3] });
   for(j=i+1;j<sizeof(stats);j++)
    {
     if(sort_func(stats[j],max_data)==1)
      {
       max_data=({ stats[j][0],stats[j][1],stats[j][2],stats[j][3] });
       max_ind=j;
      }
    }
   tmp=({ max_data[0],max_data[1],max_data[2],max_data[3]});
   stats[max_ind]=({stats[i][0],stats[i][1],stats[i][2],stats[i][3]});
   stats[i]=({ tmp[0],tmp[1],tmp[2],tmp[3] });
  }

 if(stats[0][2]>0) Winner=C(stats[0][0]); else Winner="Noone";
}

void finish_event()
{
 int i;

 for(i=0;i<sizeof(monsters);i++)
  {
   if(!monsters[i]) continue;

   monsters[i]->command("emote suddenly explodes into millions pieces!");
   monsters[i]->remove_object();
  }

 users()->remove_safe_shadow();
 set_winner();

 ::finish_event();
}

string get_statistics()
{
 string res;
 int i,dth;
 mixed *pl;

 res="Participants list:\n\n"+
     sprintf("%-11s %-5s %-5s\n","Name","Kills"," Pts ")+
     "-----------------------\n";
 for(i=0;i<sizeof(stats);i++)
   res+=sprintf("%-13s %-4d %-4d\n",C(stats[i][0]),stats[i][1],
     stats[i][2]);

 if(m_sizeof(death))
  {
   res+="\nPlayers defeated by invaders:\n\n";
   pl=m_indexes(death);
   for(i=0;i<sizeof(pl);i++)
    {
     dth=death[pl[i]];
     res+=sprintf("%-11s  %d %s\n",pl[i],dth,"time"+(dth==1 ? "":"s"));
    }
  }

 return ::get_statistics()+res;
}

void set_kills(mapping k) {kills=k;}

void notify_monster_killed(int pts,object killer,object victim)
{
 mixed *data;
 string name;

 name=killer->query_real_name();
 monsters_left--;

 notify_engine(sprintf(killer->query_name()+" killed "+
   victim->query_real_name()+" and gained %d points.",pts));

 if(member_array(name,m_indexes(kills))==-1)
   kills+=([ name: ({1,pts,monsters_left}) ]);
 else
  {
   data=kills[name];
   data[0]++;
   data[1]+=pts;
   data[2]=monsters_left;
   kills[name]=data;
  }

 if(!monsters_left) set_alarm(0.5,0.0,&finish_event());
}

string *get_warnings()
{
 string *res;

 res=::get_warnings();

 if(prop_not_set("points")) 
   res+=({"Points not set. Points of every monster will be set to 1."});

 return res;   
}

void notify_player_defeated(object player,object killer)
{
 int pen;
 string name=player->query_real_name();

 pen=query_prop_value("death_penalty");

 if(member_array(name,m_indexes(kills))==-1)
   kills+=([ name: ({0,-pen,monsters_left}) ]);
 else kills[player->query_real_name()][1]-=pen;

 notify_engine(sprintf(player->query_name()+" was defeated by "+
   killer->query_real_name()+" and lost %d points of penalty.",pen));

 if(member_array(name,m_indexes(death))==-1)
   death+=([ name:1 ]);
 else death[name]++;
}

int report(string str)
{
 string res;
 int i,dth;
 mixed *pl;

 NF("Report monsters or players?\n");

 if(str=="players")
  {
   set_winner();

   res="Participants list:\n\n"+
       sprintf("%-11s %-5s %-5s\n","Name","Kills"," Pts ")+
       "-----------------------\n";

   for(i=0;i<sizeof(stats);i++)
     res+=sprintf("%-13s %-4d %-4d\n",C(stats[i][0]),stats[i][1],
       stats[i][2]);

   if(m_sizeof(death))
    {
     res+="\nPlayers defeated by invaders:\n\n";
     pl=m_indexes(death);
     for(i=0;i<sizeof(pl);i++)
      {
       dth=death[pl[i]];
       res+=sprintf("%-11s  %d %s\n",pl[i],dth,"time"+(dth==1 ? "":"s"));
      }
    }

   if(sizeof(stats) && stats[0][2]>0) 
     res+="\nCurrent leader: "+C(stats[0][0])+"\n";

   write(res);
   return 1;
  }

 if(str=="monsters")
  {
   for(i=0;i<sizeof(monsters);i++)
    {
     if(!monsters[i]) continue;
     write(sprintf("%s: HP %d, Mana %d\n",monsters[i]->query_name(),
       monsters[i]->query_hp(),monsters[i]->query_mana()));
    }
   write(sprintf("\nMonsters killed: %d Monster left: %d\n",
     sizeof(monsters)-monsters_left,monsters_left));
   return 1;
  }
}

mapping query_death() {return death;}

mixed *query_formation() {return formation;}

