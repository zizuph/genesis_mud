inherit "/std/room";
inherit "/lib/help_support";

#include <composite.h>
#include <std.h>
#include <macros.h>
#include <stdproperties.h>
#include <options.h>

#include "defs.h"

#define DATA_OBJ SCHEDULER_DIR+"data"
#define EVENT_I_NAME "_event_i_name"
#define EVENT_I_PROP "_event_i_prop"
#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

mapping history;         // Finished events data
mapping events;          // Event props
mapping cevents;         // Data on custom events
mapping privs;           // Privilegdes to run events in domains
string *reward_types;    // Reward types for winners
mapping event_types;     // Event types
static object *handlers; // Array of currently running events handlers

void save()
{
 save_object(DATA_OBJ);
}

#include "func.h"
#include "event.h"
#include "cevent.h"

void create_room()
{
 history=([ ]);
 events=([ ]);
 cevents=([ ]);
 privs=([ ]);
 event_types=([ ]);
 reward_types=({ });
 handlers=({ });

 help_dir="/d/Earthsea/scheduler/help/";
 main_topic="scheduler";

 restore_object(DATA_OBJ);

 set_short("Event scheduler room");
 set_long("This is main room for wizards to schedule various events "+
   "all around Exodus Realms. Use <help scheduler> to know more "+
   "about scheduling events.\n");
}

void init()
{
 ::init();

 add_action("privilege","privilege");
 add_action("etype","etype");
 add_action("prop","prop");
 add_action("event","event");
 add_action("alter","alter");
 add_action("cevent","cevent");
 add_action("schedule","schedule");
 add_action("plan","plan");

 init_help_support();
}

void show_event_table(string *name)
{
 int i;
 mixed *data;

 write("+"+dupl_char("-",15)+"+"+dupl_char("-",12)+"+"+
   dupl_char("-",10)+"+"+dupl_char("-",16)+"+"+
   dupl_char("-",16)+"+\n");
 write(sprintf("|%-15s|%-12s|%-10s|%-16s|%-16s|\n","  Event name",
   " Event type","  Domain","   Start time","    End time"));
 write("+"+dupl_char("-",15)+"+"+dupl_char("-",12)+"+"+
   dupl_char("-",10)+"+"+dupl_char("-",16)+"+"+
   dupl_char("-",16)+"+\n");
 for(i=0;i<sizeof(name);i++)
  {
   data=events[name[i]];
   write(sprintf("|%-15s|%-12s|%-10s|%-16s|%-16s|\n",name[i],
     data[E_TYPE],data[E_DOMAIN],data[E_START],data[E_END]));
  }
 write("+"+dupl_char("-",15)+"+"+dupl_char("-",12)+"+"+
   dupl_char("-",10)+"+"+dupl_char("-",16)+"+"+
   dupl_char("-",16)+"+\n");
}

int privilege(string str)
{
 string option,name,priv;
 string *list;
 mixed *data,*ind;
 int i;

 NF("Syntax: privilege [-l|-a|-r|-c] <name/full> <domain/all>\n");
 if(!str) return 0;

 if(str=="-c")
  {
   write("The privilege list cleared.\n");
   privs=([]);
   save();
   return 1;
  }

 if(sscanf(str,"-%s %s",option,name)==2 && 
    sscanf(str,"-%s %s %s",option,name,priv)<3)
  {
   if(option!="l") return 0;

   if(name=="full")
    {
     ind=m_indexes(privs);
     NF("No privileges granted.\n");
     if(!sizeof(ind)) return 0;
     for(i=0;i<sizeof(ind);i++)
      {
       list=get_priv_domains(ind[i]);
       write(C(ind[i])+" has privileges on: "+implode(list,", ")+"\n");
      }
     return 1;
    }

   NF("No such wizard/domain.\n");
   if(!domain_exists(name) && !PLAYER_EXISTS(name)) return 0;

   if(domain_exists(name))
    {
     list=get_domain_privs(name);
     NF("No wizards have privileges on "+name+".\n");
     if(!sizeof(list)) return 0;
     write("The following wizards have privilege on "+name+":\n"+
        implode(list,", ")+"\n");
     return 1;
    }
   
   list=get_priv_domains(LC(name));
   NF(C(name)+" has no privileges.\n");
   if(!sizeof(list)) return 0;
   write(C(name)+" has privileges to following domains:\n"+
     implode(list,", ")+"\n");
   return 1;
  }

 if(sscanf(str,"-%s %s %s",option,name,priv)!=3) return 0;

 NF("Come back when you are an Arch!\n");
 if(WIZ_LEVEL(TP)<WIZ_ARCH) return 0;
 
 switch(option)
  {
   case "a":
     NF("No such player: "+C(name)+".\n");
     if(!PLAYER_EXISTS(name)) return 0;
     NF("C'mon! "+C(name)+" is a mortal!\n");
     if(!WIZ_NM_LEVEL(name)) return 0;
     NF("Only wizard rank and higher may have a privileges.\n");
     if(WIZ_NM_LEVEL(name)<WIZ_NORMAL) return 0;
     NF("Archwizards do not need privileges.\n");
     if(WIZ_NM_LEVEL(name)>=WIZ_ARCH) return 0;

     NF("No such domain: "+priv+"\n");
     if(!domain_exists(priv) && priv!="all") return 0;

     if(!is_priv_wiz(LC(name)))
      {
       privs+=([ LC(name): ({ C(priv) }) ]);
       write("Granted privilege on "+priv+" to "+C(name)+".\n");
       save();
       return 1;
      }
     data=privs[LC(name)];
     NF(C(name)+" already has privilege on "+priv+".\n");
     if(data[0]=="All" || member_array(priv,data)!=-1) return 0;
     if(priv=="all") data=({ "All" });
     else data+=({ priv });
     privs[LC(name)]=data;
     save();
     write("Granted privilege on "+priv+" to "+C(name)+".\n");
     break;

   case "r":
     NF(C(name)+" has no privileges.\n");
     if(!is_priv_wiz(LC(name))) return 0;

     if(priv=="all")
      {
       privs=m_delete(privs,LC(name));
       write(C(name)+" is deleted from privilege list.\n");
       save();
       return 1;
      }

     NF(C(name)+" does not have privilege on "+priv+".\n");
     if(!has_priv_on(LC(name),priv)) return 0;
     data=privs[LC(name)];
     data-=({priv});
     privs[LC(name)]=data;
     write("Privilege on "+priv+" is removed from "+C(name)+".\n");
     save();
     break;
   
   default: return 0;
  }

 return 1;
}

int etype(string str)
{
 string option,name,handler,rest;
 mixed *ind,*data,*props;
 int i,j;

 NF("Syntax etype [-c|-a|-r|-l] <type> <handler file>\n");
 if(!str) return 0;

 if(str=="-l")
  {
   ind=m_indexes(event_types);
   NF("No event types registred.\n");
   if(!sizeof(ind)) return 0;

   for(i=0;i<sizeof(ind);i++)
    {
     data=event_types[ind[i]];
     write(dupl_char("*",10)+" "+ind[i]+" "+dupl_char("*",10)+"\n");
     write("Handler file: "+data[ET_HANDLER]+"\n");
     write("List of properties:\n");
     props=data[ET_PROPS];
     for(j=0;j<sizeof(props);j++)
       write(sprintf("%d - %s %s\n",j+1,(props[j])[0],(props[j])[1]));
    }
   return 1;
  }

 if(sscanf(str,"-%s %s",option,rest)!=2) return 0;

 switch(option)
  {
   case "a":
     if(sscanf(rest,"%s %s",name,handler)!=2) return 0;

     NF("Event type already exists.\n");
     if(type_exists(name)) return 0;

     NF("File does not exist: "+handler+"\n");
     handler=fix_file(handler);
     if(!file_exists(handler)) return 0;

     event_types+=([ name : ({ handler , ({ }) }) ]);
     write("Added event type: "+name+".\n");
     save();
     break;

   case "c":
     if(sscanf(rest,"%s %s",name,handler)!=2) return 0;

     NF("Event type does not exist.\n");
     if(!type_exists(name)) return 0;

     NF("File does not exist: "+handler+"\n");
     handler=fix_file(handler);
     if(!file_exists(handler)) return 0;

     data=event_types[name];
     write("Changed event handler for event type "+name+".\n");
     data[0]=handler;
     event_types[name]=data;
     save();
     break;

   case "r":
     NF("No such event type exists.\n");
     if(!type_exists(rest)) return 0;

     write("Removed event type: "+rest+".\n");
     event_types=m_delete(event_types,rest);
     save();
     break;

   default:
     return 0;
  }

 return 1;
}

int prop(string str)
{
 string option,name,rest,e_type,p_name,p_type;
 int i;
 mixed *data,*props,*p_tmp;

 NF("Syntax: prop [-a|-r|-l] <event type> <prop name> <prop type>\n");
 if(!str) return 0;

 if(sscanf(str,"-%s %s",option,name)==2)
  {
   if(option=="l")
    {
     NF("No such event type: "+name+"\n");
     if(!type_exists(name)) return 0;
     data=event_types[name];
     props=data[ET_PROPS];
     write("Props list of event type: "+name+"\n");
     for(i=0;i<sizeof(props);i++)
       write(sprintf("%-30s %s\n",(props[i])[0],(props[i])[1]));
     write(dupl_char("=",70)+"\n");
     return 1;
    }
  }

 if(sscanf(str,"-%s %s %s",option,name,rest)!=3) return 0;

 NF("No such event type: "+name+"\n");
 if(!type_exists(name)) return 0;
 data=event_types[name];
 props=data[ET_PROPS];

 switch(option)
  {
   case "a":
     NF("Syntax: prop [-a|-r|-l] <event type> <prop name> "+
       "<prop type>\n");
     if(sscanf(rest,"%s %s",p_name,p_type)!=2) return 0;
     NF("Illegal prop type: "+p_type+"\n");
     if(!is_legal_type(p_type)) return 0;
     NF("Prop "+p_name+" already exists in event type "+name+"\n");
     if(custom_prop_exists(name,p_name)) return 0;
     props+=({ ({p_name,p_type}) });
     data[ET_PROPS]=props;
     event_types[name]=data;
     write("Property "+p_name+" of type "+p_type+" added to event "+
       "type: "+name+"\n");
     say(QCTNAME(TP)+" adds property "+p_name+" of type "+p_type+
       " to event type: "+name+"\n");
     save();
     break;

   case "r":
     NF("Property "+rest+" does not exist in event type: "+name+"\n");
     if(!custom_prop_exists(name,rest)) return 0;
     
     p_tmp=({});
     for(i=0;i<sizeof(props);i++)
       if((props[i])[0]!=rest) 
         p_tmp+=({ ({ (props[i])[0],(props[i])[1] }) });
     props=({});
     for(i=0;i<sizeof(p_tmp);i++)
       props+=({ ({ (p_tmp[i])[0],(p_tmp[i])[1] }) });
     data[ET_PROPS]=props;
     event_types[name]=data;
     write("Property "+rest+" was removed from event type: "+name+"\n");
     save();
     break;

   default:
     return 0;
  } 

 return 1;
}

int event(string str)
{
 int i;
 mixed *ind,*data;
 string option,rest,file;
 string name,type,domain,start_d,end_d,start_t,end_t,start,end;
 string rw_str;
 mixed *rw_amnt,*props,pv,err;
 string prop_rep;
 string f_props,f_values,*f_prop,*f_value,*f_events;

 NF("Syntax: event [-l|-ls|-a|-r|-f|-load|-save] <name> "+
   "<event_type> <domain> <start datetime> <end datetime>\n");
 if(!str) return 0;

 if(str=="-l")
  {
   ind=m_indexes(events);
   NF("No scheduled events.\n");
   if(!sizeof(ind)) return 0;

   show_event_table(ind);

   return 1;
  }

 if(sscanf(str,"-%s %s",option,rest)!=2) return 0;

 switch(option)
  {
   case "save":
     if(sscanf(rest,"%s %s",name,file)!=2) return 0;

     NF("Event does not exist: "+name+".\n");
     if(!event_exists(name)) return 0;

     NF("This event is niether is scheduling nor in alter "+
       "status.\n");
     if(PV(name,P_STATUS)!=ST_SCHEDULING &&
        PV(name,P_STATUS)!=ST_ALTERING) return 0;

     NF("Failed to write into "+file+".\n");
     if(!save_event_to_file(name,file)) return 0;

     write("Saved event "+name+" into "+file+"\n");
     return 1;

   case "load":
     if(sscanf(rest,"%s %s",name,file)!=2) return 0;

     NF("Event does not exist: "+name+".\n");
     if(!event_exists(name)) return 0;

     NF("This event is niether is scheduling nor in alter "+
       "status.\n");
     if(PV(name,P_STATUS)!=ST_SCHEDULING &&
        PV(name,P_STATUS)!=ST_ALTERING) return 0;

     err=load_event_from_file(name,file);
     if(err==1) 
      {
       write("Loaded event "+name+" from "+file+"\n");
       return 1;
      }
     if(!err) NF("Failed to read from "+file+".\n");
       else NF(err+"\n");
     return 0;

   case "f":
     if(sscanf(rest,"%s %s",f_props,f_values)!=2) return 0;

     f_prop=explode(f_props,",");
     f_value=explode(f_values,",");

     NF("Number of filter props and values must be same.\n");
     if(sizeof(f_prop)!=sizeof(f_value)) return 0;

     for(i=0;i<sizeof(f_prop);i++)
      {
       NF("Invalid filter prop: "+f_prop[i]+".\n");
       if(member_array(f_prop[i],FILTER_PROPS)==-1) return 0;
      }

     f_events=filter_events(f_prop,f_value);
     NF("No events matching the filter were found.\n");
     if(!sizeof(f_events)) return 0;

     show_event_table(f_events);
     break;

   case "a":
     if(sscanf(rest,"%s %s %s %s %s %s %s",
       name,type,domain,start_d,start_t,end_d,end_t)!=7) return 0;
     start=start_d+" "+start_t;
     end=end_d+" "+end_t;

     NF("Event "+name+" is already scheduled.\n");
     if(event_exists(name)) return 0;

     NF("Event "+name+" has already occured.\n");
     if(history_exists(name)) return 0;

     NF("Event type does not exist: "+type+".\n");
     if(!type_exists(type)) return 0;

     NF("Domain does not exist: "+domain+".\n");
     if(!domain_exists(domain)) return 0;

     NF("You are not authorized to schedule events in "+
       domain+".\n");
     if(!can_use_domain(TP,domain)) return 0;

     NF("Invalid start datetime: "+start+".\n");
     if(!is_valid_datetime(start)) return 0;

     NF("Invalid end datetime: "+end+".\n");
     if(!is_valid_datetime(end)) return 0;

     NF("Scheduling allowed only for future dates.\n");
     if(compare_datetime(now(),start)!=2) return 0;
     if(compare_datetime(now(),end)!=2) return 0;

     NF("End datetime must be greater then start datetime.\n");
     if(compare_datetime(start,end)!=2) return 0;

     events+=([ name: ({ type,domain,start,end,ST_SCHEDULING,
       TP->query_name() ,RW_NONE,0,"","",0,({ }) }) ]);
     write("Added event: "+name+" of type: "+type+" in domain: "+
       domain+" starting at "+start+" ending at "+end+".\n");
     save();
     break;

   case "r":
     NF("Event "+rest+" does not exist.\n");
     if(!event_exists(rest)) return 0;

     NF("You are not authorized to remove this event.\n");
     if(!can_use_domain(TP,PV(rest,P_DOMAIN))) return 0;

     NF("Cannot delete currently running event.\n");
     if(PV(rest,P_STATUS)==ST_RUNNING) return 0;

     events=m_delete(events,rest);
     write("Event "+rest+" is deleted from events database.\n");
     save();
     break;

   case "ls":
     NF("Event "+rest+" does not exist.\n");
     if(!event_exists(rest)) return 0;

     data=events[rest];
     props=event_custom_props(data[E_TYPE]);

     write("Event name: "+rest+"\n");
     write(dupl_char("=",70)+"\n");
     write("B A S I C   P R O P S:\n");
     write(P_TYPE+": "+data[E_TYPE]+"\n");
     write(P_CREATOR+": "+data[E_CREATOR]+"\n");
     write(P_DOMAIN+": "+data[E_DOMAIN]+"\n");
     write(P_START+": "+data[E_START]+"\n");
     write(P_END+": "+data[E_END]+"\n");
     write(P_STATUS+": "+data[E_STATUS]+"\n");
     write(P_RW_TYPE+": "+RW_TYPES[data[E_RW_TYPE]]+"\n");
     write(P_RW_AMNT+": "+(data[E_RW_TYPE]==RW_ITEM ? 
       "(ARRAY)\n"+(data[E_RW_AMNT] ? 
         implode((mixed *)data[E_RW_AMNT],"\n") : "({ })") : 
         sprintf("%d",data[E_RW_AMNT]))+"\n");
     write(P_DESC+":\n"+data[E_DESC]);
     write(P_ANNOUNCE+":\n"+data[E_ANNOUNCE]);
     write(P_ANNOUNCE_MINS+": "+sprintf("%d",data[E_ANNOUNCE_MINS])+"\n");

     write("E V E N T   P R O P S:\n");
     for(i=0;i<sizeof(props);i++)
      {
       pv=PV(rest,props[i][0]);
       if(pv==NOT_SET) prop_rep="not set";
       else
        {
         switch(props[i][1])
          {
           case PT_BOOLEAN:
             prop_rep=(pv ? "True" : "False");
             break;
           case PT_INT: 
             prop_rep=sprintf("%d",(int)pv);
             break;
           case PT_STRING: 
           case PT_DATETIME: 
             prop_rep=(string)pv;
             break;
           case PT_MEMO: 
             prop_rep="(MEMO)\n"+(string)pv;
             break;
           case PT_ARRAY: 
             prop_rep="(ARRAY)\n"+implode((string *)pv,"\n"); break;
          }
        }
       write(props[i][0]+": "+prop_rep+"\n");
      }

     break;

   default:
     return 0;
  }

 return 1;
}

void alter_basic_prop(string name,string prop,string value,int drop)
{
 mixed *data;
 int i,rw,amnt,mins,ind;

 data=events[name];

 switch(prop)
  {
   case P_TYPE:
   case P_DOMAIN:
   case P_CREATOR:
   case P_STATUS:
     if(drop)
      {
       write("Cannot drop value of this prop.\n");
       return;
      }
     write("You cannot alter this prop.\n");
     return;

   case P_START:
     if(drop)
      {
       write("Cannot drop value of this prop.\n");
       return;
      }
     if(!value || !strlen(value))
      {
       write("You must specify a value for this prop.\n");
       return;
      }
     if(!is_valid_datetime(value)) 
      {
       write(value+" is not a valid datetime.\n");
       return;
      }
     data[E_START]=value;
     write("Prop "+name+"."+P_START+" was set to "+value+"\n");
     save();
     break;
   
   case P_END:
     if(drop)
      {
       write("Cannot drop value of this prop.\n");
       return;
      }
     if(!value || !strlen(value))
      {
       write("You must specify a value for this prop.\n");
       return;
      }
     if(!is_valid_datetime(value)) 
      {
       write(value+" is not a valid datetime.\n");
       return;
      }
     data[E_END]=value;
     write("Prop "+name+"."+P_END+" was set to "+value+"\n");
     save();
     break;

   case P_RW_TYPE:
     if(drop)
      {
       data[E_RW_TYPE]=RW_NONE;
       data[E_RW_AMNT]=0;
       save();
       write("Value of prop "+name+"."+prop+" was droped.\n");
       write("Prop "+name+".reward_amount was reset.\n");
       return;
      }

     if(value!="")
      {
       write("You cannot specify value for this prop.\n");
       return;
      }
     write("Choose one of the following:\n");
     for(i=0;i<sizeof(reward_types);i++)
       write(sprintf("[%d] - %s\n",i,reward_types[i]));
     write(" >> ");
     TP->add_prop(EVENT_I_NAME,name);
     input_to("get_rw_type");
     break;

   case P_RW_AMNT:
     if(drop)
      {
       data[E_RW_AMNT]=0;
       save();
       write("Value of prop "+name+"."+prop+" was droped.\n");
       return;
      }

     rw=PV(name,P_RW_TYPE);
     if(rw==RW_NONE)
      {
       write("Cannot alter amount reward, since reward type was not "+
         "set.\n");
       return;
      }
     if(rw==RW_ITEM)
      {
       if(value!="")
        {
         write("You cannot specify value for this prop.\n");
         return;
        }
       TP->add_prop(EVENT_I_NAME,name);
       EDIT("get_rw_amnt");
       break;
      }
     if(value=="")
      {
       write("You must specify value for this prop.\n");
       return;
      }
     if(!is_number(value))
      {
       write(sprintf("Invalid reward amount: %s\n",value));
       return;
      }
     sscanf(value,"%d",amnt);
     if(amnt<=0) 
      {
       write("Reward armout must be greater then zero.\n");
       return;
      }
     write("Prop reward_amount of event "+name+" was set to value "
       +value+"\n");
     data[E_RW_AMNT]=amnt;
     events[name]=data;
     save();
     break;

   case P_DESC:
   case P_ANNOUNCE:
     if(drop)
      {
       ind=(prop==P_DESC ? E_DESC : E_ANNOUNCE);
       data[ind]="";
       save();
       write("Value of prop "+name+"."+prop+" was droped.\n");
       return;
      }

     if(value!="")
      {
       write("You cannot specify value for this prop.\n");
       return;
      }
     TP->add_prop(EVENT_I_NAME,name);
     TP->add_prop(EVENT_I_PROP,prop);
     write("Enter value for the prop.\n");
     EDIT("get_memo");
     break;

   case P_ANNOUNCE_MINS:
     if(drop)
      {
       data[E_ANNOUNCE_MINS]=0;
       save();
       write("Value of prop "+name+"."+prop+" was droped.\n");
       return;
      }

     if(value=="")
      {
       write("You must specify value for this prop.\n");
       return;
      }
     if(!is_number(value))
      {
       write("Invalid number: "+value+"\n");
       return;
      }
     sscanf(value,"%d",mins);
     data[E_ANNOUNCE_MINS]=mins;
     write("Prop "+P_ANNOUNCE_MINS+" of event "+name+" was set to "+
       value+".\n");
     save();
     break;
  }
}

int alter(string str)
{
 string name,prop,rest,value,err_code;
 mixed pt,*data,*props,*err;
 int drop=0,i;
 object hndl;
 string err_file=0;
 string *err_str;
 int write_res;
 string st;
 object oldtp;
 string *war;

 NF("Syntax: alter <event>.<prop> set <value>\n"+
    "        alter <event>.<prop>\n"+
    "        alter <event>.<prop> drop\n"+
    "        alter <event> open [>> filename]\n"+
    "        alter <event> close\n");
 if(!str) return 0;

 if(sscanf(str,"%s close",name))
  {
   NF("Event "+name+" does not exist.\n");
   if(!event_exists(name)) return 0;

   NF("Event is not pending.\n");
   if(PV(name,P_STATUS)!=ST_PENDING) return 0;

   data=events[name];
   data[E_STATUS]=ST_ALTERING;
   events[name]=data;
   write("Event has been closed, it is now in altering status.\n");
   save();
   return 1;
  }

 if(sscanf(str,"%s open",name))
  {
   sscanf(str,"%s open >> %s",name,err_file);

   NF("Event "+name+" does not exist.\n");
   if(!event_exists(name)) return 0;

   st=PV(name,P_STATUS);
   NF("This event is already pending.\n");
   if(st==ST_PENDING) return 0;

   NF("This event currently running.\n");
   if(st==ST_RUNNING) return 0;

   NF("This event has already ended.\n");
   if(st==ST_FINISHED) return 0;

   data=events[name];
   hndl=clone_object(event_handler(data[E_TYPE]));
   NF("Cannot validate props, event handler failed to load.\n");
   if(!hndl) return 0;

   oldtp=TP;
   hndl->set_event(name);
   err=hndl->validate_props();
   set_this_player(oldtp);
   if(!sizeof(err))
    {
     war=hndl->get_warnings();
     if(sizeof(war))
      {
       write("Warnings:\n");
       for(i=0;i<sizeof(war);i++) write(war[i]+"\n");
      }
     write("Event has been opened succesfully. Now pending.\n");
     hndl->remove_object();
     data[E_STATUS]=ST_PENDING;
     save();
     return 1;
    }

   if(err_file)
    {
     err_str=({ });
     for(i=0;i<sizeof(err);i++) 
       err_str+=({ err[i][0]+" : "+err[i][1] });
     write_res=write_file(err_file,implode(err_str,"\n")+"\n");
     if(write_res)
       write("Cannot validate props. Errors stored in "+err_file+".\n");
     else write("Cannot validate props. Fail to write to "+err_file+
       ", displaying errors:\n");
    }

   NF("Fix the props before opening the event.\n");
   if(!write_res)
    {
     write("Cannot validate props. Following errors have occured:\n");
     for(i=0;i<sizeof(err);i++)
       write(err[i][0]+" : "+err[i][1]+"\n");
    }
   hndl->remove_object();
   return 0;
  }

 if(sscanf(str,"%s.%s",name,rest)!=2) return 0;

 NF("Event "+name+" does not exist.\n");
 if(!event_exists(name)) return 0;

 st=PV(name,P_STATUS);
 NF("Event is not in scheduling niether altering status.\n");
 if(st!=ST_SCHEDULING && st!=ST_ALTERING) return 0;

 if(sscanf(rest,"%s drop",prop)) drop=1; else
   if(sscanf(rest,"%s set %s",prop,value)!=2) {prop=rest;value="";}

 data=events[name];

 if(is_basic_prop(prop))
  {
   alter_basic_prop(name,prop,value,drop);
   return 1;
  }

 pt=prop_type(data[E_TYPE],prop);
 
 NF("Prop "+prop+" does not exist in event type "+data[E_TYPE]+".\n");
 if(!pt) return 0;

 if(drop)
  {
   drop_prop(name,prop);
   write("Droped value of prop "+prop+" of event "+name+".\n");
   save();
   return 1;
  }

 if(value=="")
  {
   NF("You must specify a value for this prop.\n");
   if(pt==PT_INT || pt==PT_DATETIME || pt==PT_STRING ||
      pt==PT_BOOLEAN) return 0;
   write("Please enter the value for prop "+name+"."+prop+" >>\n");
   TP->add_prop(EVENT_I_NAME,name);
   TP->add_prop(EVENT_I_PROP,prop);
   EDIT("get_prop_val");
   return 1;
  }

 NF("You cannot specify a value for this prop.\n");
 if(pt==PT_ARRAY || pt==PT_MEMO) return 0;
 err_code=set_prop(name,prop,value);

 if(err_code==SE_OK)
  {
   write("Prop "+prop+" of event "+name+" was set to value "+value+"\n");
   save();
   return 1;
  }

 NF(err_code+".\n");
 return 0;
}

void get_prop_val(string str)
{
 string name,prop;
 string err_code;

 name=TP->query_prop(EVENT_I_NAME);
 prop=TP->query_prop(EVENT_I_PROP);
 TP->remove_prop(EVENT_I_NAME);
 TP->remove_prop(EVENT_I_PROP);

 if(!str || !strlen(str))
  {
   write("You need to specify a value for prop "+name+"."+prop+".\n");
   return;
  }

 err_code=set_prop(name,prop,str);
 if(err_code!=SE_OK)
  {
   write(err_code+".\n");
   return;
  }

 write("Prop "+prop+" of event "+name+" was successfully altered.\n");
 save();
}

void get_rw_type(string str)
{
 int ind;
 mixed *data;
 string name;

 if(!is_number(str))
  {
   write("Wrong index: "+str+".\n");
   return;
  }

 sscanf(str,"%d",ind);
 if(ind<0 || ind>sizeof(reward_types)-1)
  {
   write("Wrong index: "+str+".\n");
   return;
  }

 name=TP->query_prop(EVENT_I_NAME);
 TP->remove_prop(EVENT_I_NAME);
 data=events[name];
 data[E_RW_TYPE]=ind;
 data[E_RW_AMNT]=0;
 write("Prop "+name+".reward_type was set to "+reward_types[ind]+".\n");
 write("Prop "+name+".reward_amount was reset.\n");
 save();
}

void get_rw_amnt(string str)
{
 mixed *data;
 string name,*itm,*res;
 int i;

 if(!str || !strlen(str))
  {
   write("You need to specify a value for prop "+name+
     ".reward_amount.\n");
   return;
  }

 name=TP->query_prop(EVENT_I_NAME);
 TP->remove_prop(EVENT_I_NAME);

 data=events[name];
 itm=explode(str,"\n"); res=({ });
 for(i=0;i<sizeof(itm);i++)
  {
   if(itm[i] && strlen(itm[i])) 
    {
     itm[i]=fix_file(itm[i]);
     res+=({ itm[i] });
    }
  }
 if(!sizeof(res))
  {
   write("You need to specify a value for prop "+name+
     ".reward_amount.\n");
   return;
  }
 data[E_RW_AMNT]=res;
 events[name]=data;
 write("Prop reward_amount of event "+name+" was successfully "+
   "altered.\n");
 save();
}

void get_memo(string str)
{
 string name,prop;
 mixed *data;
 int ind;

 name=TP->query_prop(EVENT_I_NAME);
 prop=TP->query_prop(EVENT_I_PROP);
 TP->remove_prop(EVENT_I_NAME);
 TP->remove_prop(EVENT_I_PROP);

 if(!str || !strlen(str))
  {
   write("You need to specify a value for prop "+name+"."+prop+".\n");
   return;
  }

 data=events[name];
 switch(prop)
  {
   case P_ANNOUNCE: ind=E_ANNOUNCE; break;
   case P_DESC: ind=E_DESC; break;
  }
 data[ind]=str;
 write("Prop "+prop+" of event "+name+" was successfully altered.\n");
 save();
}

void event_start(string name)
{
 mixed *data;
 object hndl;

 data=events[name];
 data[E_STATUS]=ST_RUNNING;
 events[name]=data;

 save();

 hndl=clone_object(event_handler(data[E_TYPE]));
 if(!hndl)
  {
   DEBUG("\n\nEvent handler for event "+name+" failed to load!!\n\n");
   return;
  }

 handlers+=({ hndl });

 hndl->set_event(name);
 (ENGINE)->blablabla();
 hndl->move(find_object(ENGINE));
 hndl->launch_event();
}

void event_finish(string name, string winner, object hndl)
{
 (FAMEHALL)->add_winner(name,winner,PV(name,P_DATE),
   PV(name,P_RW_TYPE),PV(name,P_RW_AMNT));
 history+=([name: ({ PV(name,P_TYPE),PV(name,P_DOMAIN),
   PV(name,P_START),winner }) ]);

 events=m_delete(events,name);
 handlers-=({ hndl });
 hndl->remove_object();

 save();
}

void reopen_event(string name)
{
 mixed *data;

 data=events[name];
 data[E_STATUS]=ST_SCHEDULING;
 events[name]=data;

 save();
}

void show_history_table(string *name)
{
 int i;
 mixed *data;

 write("+"+dupl_char("-",15)+"+"+dupl_char("-",12)+"+"+
   dupl_char("-",10)+"+"+dupl_char("-",16)+"+"+
   dupl_char("-",11)+"+\n");
 write(sprintf("|%-15s|%-12s|%-10s|%-16s|%-11s|\n","  Event name",
   " Event type","  Domain","      Date","   Winner  "));
 write("+"+dupl_char("-",15)+"+"+dupl_char("-",12)+"+"+
   dupl_char("-",10)+"+"+dupl_char("-",16)+"+"+
   dupl_char("-",11)+"+\n");
 for(i=0;i<sizeof(name);i++)
  {
   data=history[name[i]];
   write(sprintf("|%-15s|%-12s|%-10s|%-16s|%-11s|\n",name[i],
     data[H_TYPE],data[H_DOMAIN],data[H_START],data[H_WINNER]));
  }
 write("+"+dupl_char("-",15)+"+"+dupl_char("-",12)+"+"+
   dupl_char("-",10)+"+"+dupl_char("-",16)+"+"+
   dupl_char("-",11)+"+\n");
}

void clear()
{
 history=([ ]);
 save();
}

void add_history(string name,string type,string domain,string start,
string winner)
{
 history+=([ name: ({type,domain,start,winner}) ]);
 save();
}

int cevent(string str)
{
 string *params,name,server,func;
 mixed *ind;
 int i;

 NF("Syntax cevent [-a|-r|-l] <name> <server> <start function>\n");
 if(!str || !strlen(str)) return 0;

 params=explode(str," ");
 if(!sizeof(params)) return 0;

 switch(params[0])
  {
   case "-l":
     switch(sizeof(params))
      {
       case 1:
         ind=m_indexes(cevents);
         NF("There are no registred custom events.\n");
         if(!sizeof(ind)) return 0;

         for(i=0;i<sizeof(ind);i++)
           write(ind[i]+":\n  Owner: "+
           cevents[ind[i]][CE_OWNER]+"\n  Event server: "+
           cevents[ind[i]][CE_SERVER]+"\n  Launch function: "+
           cevents[ind[i]][CE_FUNCTION]+"\n"+
           get_schedule_desc(ind[i])+"\n");

         return 1;       

       case 2:
         name=params[1];

         NF("No such custom event registred.\n");
         if(!cevent_exists(name)) return 0;

         write(name+":\n  Owner: "+
         cevents[name][CE_OWNER]+"\n  Event server: "+
         cevents[name][CE_SERVER]+"\n  Launch function: "+
         cevents[name][CE_FUNCTION]+"\n"+
         get_schedule_desc(name)+"\n");

         return 1;
      }

     return 0;

   case "-a":
     if(sizeof(params)!=4) return 0;

     name=params[1]; 
     server=fix_file(params[2]); 
     func=params[3];

     NF("Custom event with this name is already registred.\n");
     if(cevent_exists(name)) return 0;

     NF("File does not exist: "+server+".\n");
     if(!file_exists(server)) return 0;

     NF("You can't schedule events in specified domain!\n");
     if(!can_use_domain(TP,get_domain(server))) return 0;

     NF("Server cannot be loaded: "+server+".\n");
     if(!find_object(server)) return 0;

     NF("Function "+func+" does not exists in server "+server+".\n");
     if(!function_exists(func,find_object(server))) return 0;

     cevents+=([name : ({ server,func,0,TP->query_real_name() }) ]);
     save();
     write("Custom event with following info has been registred:\n"+
           "Name: "+name+"\nEvent server: "+server+
           "\nLaunch function: "+func+"\n");
     return 1;

   case "-r":

     if(sizeof(params)!=2) return 0;

     name=params[1];

     NF("No such custom event registred.\n");
     if(!cevent_exists(name)) return 0;

     NF("You are not authorized to delete this event.\n");
     if(!AOE(TP->query_real_name()) 
        && !can_use_domain(TP,get_domain(get_server(name)))
        && get_owner(name)!=TP->query_real_name()) return 0;

     cevents=m_delete(cevents,name);
     (CENGINE)->remove_plan(name);
     save();
     write("Custom event "+name+" was removed.\n");
     return 1;
  }

 return 0;
}

int schedule(string str)
{
 NF("Schedule what? Please specify custom event name.\n");
 if(!str || !strlen(str)) return 0;

 NF("No such custom event exists: "+str+".\n");
 if(!cevent_exists(str)) return 0;

 if(!cevents[str][CE_SCHEDULE])
  {
   start_scheduler_wizard(str);
   return 1;
  }

 write("Custom event "+str+" is already scheduled. Do you "+
   "want to re-schedule it?\n(y/n) >> ");
 TP->add_prop(EVENT_I_NAME,str);
 input_to("yes_no");

 return 1;
}

void yes_no(string str)
{
 if(str!="y" && str!="ye" && str!="yes" && str!="n" &&
    str!="no")
  {
   write("Chose either yes or no.\n(y/n) >> ");
   input_to("yes_no");
   return;
  }

 if(str=="n" || str=="no")
  {
   write("Scheduling aborted.\n");
   return;
  }

 start_scheduler_wizard(TP->query_prop(EVENT_I_NAME));
}

int plan(string str)
{
 NF("Syntax: plan <event_name>\n");
 if(!str || !strlen(str)) return 0;

 NF("No such custom event exists: "+str+".\n");
 if(!cevent_exists(str)) return 0;

 write((CENGINE)->get_event_plan(str));
 return 1;
}

