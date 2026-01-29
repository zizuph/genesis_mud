#include "event_defs.h"

// Set value errors

#define SE_OK "OK"
#define SE_INVALID_DATETIME "Invalid value for datetime"
#define SE_INVALID_INT "Invalid value for integer"
#define SE_INVALID_BOOLEAN "Invalid value for boolean"
#define SE_END_BEFORE_START "End datetime must be greater then "+\
  "start datetime"
#define SE_CANT_USE_DOMAIN "You do not have privilege to schedule "+\
  "events in this domain"

int type_exists(string tp_name)
{
 return (member_array(tp_name,m_indexes(event_types))==-1 ? 0 : 1);
}

int is_basic_prop(string prop)
{
 return (member_array(prop,BASIC_PROPS)==-1 ? 0 : 1);
}

int is_priv_wiz(string name)
{
 return (member_array(name,m_indexes(privs))==-1 ? 0 : 1);
}

int has_priv_on(string name,string domain)
{
 mixed *data;

 if(!is_priv_wiz(name)) return 0;

 data=privs[name];
 return (member_array(domain,data)==-1 ? 0 : 1);
}

int can_use_domain(object wiz,string domain)
{
 if(AOE(wiz)) return 1; 

 switch(WIZ_LEVEL(wiz))
  {
   case WIZ_KEEPER:
   case WIZ_ARCH:
     return 1;
   case WIZ_LORD:
   case WIZ_STEWARD:
     if(WIZ_DOMAIN(wiz->query_real_name())!=domain && 
     !has_priv_on(wiz->query_real_name(),domain))
       return 0;
     return 1;
   default:
     if(!has_priv_on(TP->query_real_name(),domain)) return 0;
     return 1;
  }
}

string *get_priv_domains(string name)
{
 string *res=({});
 mixed *data;
 int i;

 data=privs[name];
 for(i=0;i<sizeof(data);i++)
   res+=({ data[i] });

 return res;
}

string *get_domain_privs(string domain)
{
 int i;
 mixed *ind,*data;
 string *res=({});
 
 ind=m_indexes(privs);
 for(i=0;i<sizeof(ind);i++)
  {
   data=privs[ind[i]];
   if(member_array(domain,data)!=-1) res+=({C(ind[i])});
  }

 return res;
}

int event_exists(string name)
{
 return (member_array(name,m_indexes(events))==-1 ? 0 : 1);
}

string event_handler(string type)
{
 mixed *data;

 data=event_types[type];
 return data[0];
}

int custom_prop_exists(string e_type,string prop)
{
 int i;
 mixed *data,*props;

 data=event_types[e_type];
 props=data[1];
 for(i=0;i<sizeof(props);i++) if((props[i])[0]==prop) return 1;

 return 0;
}

mixed prop_type(string e_type,string prop)
{
 int i;
 mixed *data,*props;

 if(!custom_prop_exists(e_type,prop)) return 0;

 data=event_types[e_type];
 props=data[1];
 for(i=0;i<sizeof(props);i++)
   if((props[i])[0]==prop) return (props[i])[1];

 return 0;
}

int is_legal_type(string tp)
{
 return (member_array(tp,PROP_TYPES)==-1 ? 0 : 1);
}

mixed *event_custom_props(string e_type)
{
 int i;
 mixed *data;

 data=event_types[e_type];
 return data[1];
}

mixed query_prop_value(string e_name,string prop)
{
 int prop_ind,i;
 mixed *data,*props;

 if(!event_exists(e_name)) return -1;
 data=events[e_name];

 if(prop==P_DATE) return get_date(data[E_START]);

 if(is_basic_prop(prop))
  {
   prop_ind=member_array(prop,BASIC_PROPS);
   return data[prop_ind];
  }

 if(!custom_prop_exists(data[E_TYPE],prop)) return -1;
 props=data[E_PROPS];
 for(i=0;i<sizeof(props);i++)
   if(props[i][0]==prop) return props[i][1];

 return NOT_SET;
}

int prop_not_set(string e_name,string prop)
{
 return(query_prop_value(e_name,prop)==NOT_SET ? 1 : 0);
}

void drop_prop(string e_name,string prop)
{
 mixed *data,*props,*tmp;
 int i;

 data=events[e_name];
 props=data[E_PROPS];

 tmp=({ });
 for(i=0;i<sizeof(props);i++)
   if(props[i][0]!=prop) tmp+=({ ({props[i][0],props[i][1]}) });

 data[E_PROPS]=tmp;
 events[e_name]=data;
}

string set_prop(string name,string prop,string value)
{
 mixed *data,*props,pt,val;
 int i,found;

 data=events[name];
 props=data[E_PROPS];
 pt=prop_type(data[E_TYPE],prop);
 switch(pt)
  {
   case PT_BOOLEAN:
     if(value!="T" && value!="F" && value!="t" && value!="f" && 
        value!="true" && value!="false" && value!="True" && 
        value!="False") return SE_INVALID_BOOLEAN;
     val=(value=="T" || value=="t" || value=="True" || value=="true");
     break;
   case PT_INT:
     if(!is_number(value)) return SE_INVALID_INT;
     sscanf(value,"%d",val);
     break;
   case PT_DATETIME:
     if(!is_valid_datetime(value)) return SE_INVALID_DATETIME;
     val=value;
     break;
   case PT_STRING:
   case PT_MEMO:
     val=value;
     break;
   case PT_ARRAY:
     val=explode(value,"\n");
     break;
   default:
     break;
  }

 found=0;
 for(i=0;i<sizeof(props);i++)
  {
   if(props[i][0]==prop)
    {
     found=1;
     props[i][1]=val;
     break;
    }
  }

 if(!found) props+=({ ({prop,val}) });
 data[E_PROPS]=props;
 events[name]=data;

 return SE_OK;
}

string *filter_events(string *props,string *values)
{
 int i,j,match;
 string *ind,*res;

 ind=m_indexes(events);
 res=({ });
 for(i=0;i<sizeof(ind);i++)
  {
   match=0;
   for(j=0;j<sizeof(props);j++) 
     if((string)query_prop_value(ind[i],props[j])==values[j]) 
       match++;
   if(match==sizeof(props)) res+=({ ind[i] });
  }

 return res;
}

string desc_event(string name)
{
 string res;
 string domain,creator,start,end,desc,reward,type;
 int reward_type;

 domain=query_prop_value(name,P_DOMAIN);
 creator=query_prop_value(name,P_CREATOR);
 start=query_prop_value(name,P_START);
 end=query_prop_value(name,P_END);
 desc=query_prop_value(name,P_DESC);
 reward_type=query_prop_value(name,P_RW_TYPE);
 type=query_prop_value(name,P_TYPE);

 res=desc+"\n"+
   "The event type is "+type+".\n"+
   "This event is created by "+creator+".\n"+
   "The event will take place at the lands of "+domain+".\n"+
   "The event will start at "+start+" and will end at "+end+".\n";
 
 reward=RW_DESC[reward_type];

 if(reward!="none")
   res+="The reward for winner is "+reward+".\n";
 return res;
}

int history_exists(string name)
{
 return (member_array(name,m_indexes(history))==-1 ? 0 : 1);
}

string *filter_history(string from,string to)
{
 string dt,*ind,*res;
 int i;
 
 res=({ });
 ind=m_indexes(history);
 for(i=0;i<sizeof(ind);i++)
  {
   dt=get_date(history[ind[i]][H_START]);
   if(between_date(dt,from,to)) res+=({ ind[i] });
  }

 return res;
}

int cevent_exists(string name)
{
 return (member_array(name,m_indexes(cevents))==-1 ? 0 : 1);
}

int save_event_to_file(string name, string file)
{
 int rw_tp,i,j;
 mixed rw_amnt;
 mixed *props;
 string type;

 setuid();
 seteuid(getuid(TP));

 rm(file);
 type=query_prop_value(name,P_TYPE);
 rw_tp=query_prop_value(name,P_RW_TYPE);
 rw_amnt=query_prop_value(name,P_RW_AMNT);
 if(!write_file(file,sprintf("%d\n",rw_tp))) return 0;
 if(rw_tp==RW_ITEM)
  {
   write_file(file,"{\n");
   for(i=0;i<sizeof(rw_amnt);i++) write_file(file,rw_amnt[i]+"\n");
   write_file(file,"}\n");
  }
 else write_file(file,sprintf("%d\n",rw_amnt));
 write_file(file,"{\n");
 write_file(file,query_prop_value(name,P_DESC));
 write_file(file,"}\n");
 write_file(file,"{\n");
 write_file(file,query_prop_value(name,P_ANNOUNCE));
 write_file(file,"}\n");
 write_file(file,sprintf("%d\n",query_prop_value(name,P_ANNOUNCE_MINS)));

 props=events[name][E_PROPS];
 for(i=0;i<sizeof(props);i++)
  {
   write_file(file,props[i][0]+"\n");
   switch(prop_type(type,props[i][0]))
    {
     case PT_INT:
     case PT_BOOLEAN:
       write_file(file,sprintf("%d\n",props[i][1]));
       break;
     case PT_STRING:
     case PT_DATETIME:
       write_file(file,props[i][1]+"\n");
       break;
     case PT_MEMO:
       write_file(file,"{\n");
       write_file(file,props[i][1]);
       write_file(file,"}\n");
       break;
     case PT_ARRAY:
       write_file(file,"{\n");
       for(j=0;j<sizeof(props[i][1]);j++) 
         write_file(file,props[i][1][j]+"\n");
       write_file(file,"}\n");
       break;
    }
  }

 return 1;
}

mixed load_event_from_file(string name, string file)
{
 string str,*line,desc,ann,prop,type,*tmp,err;
 int cur,last;
 mixed rw_amnt,value;

 setuid();
 seteuid(getuid(TP));

 str=read_file(file);
 if(!str) return 0;

 type=query_prop_value(name,P_TYPE);
 line=explode(str,"\n");
 last=sizeof(line);

 if(!is_number(line[0])) return "Failed to read reward type";

 events[name][E_RW_TYPE]=atoi(line[0]);
 if(atoi(line[0])==RW_ITEM)
  {
   if(line[1]!="{") return "Failed to read reward amount.";
   cur=2; rw_amnt=({ });
   while(line[cur]!="}")
    {
     rw_amnt+=({ line[cur] });
     cur++; if(cur==last) return "Failed to read reward amount.";
    }
   cur++;
  }
 else 
  {
   cur=2;
   if(!is_number(line[1])) return "Failed to read reward amount.";
   rw_amnt=atoi(line[1]);
  }

 events[name][E_RW_AMNT]=rw_amnt;

 if(line[cur]!="{") return "Failed to read description.";
 cur++; desc="";
 while(line[cur]!="}")
  {
   desc+=line[cur]+"\n";
   cur++; if(cur==last) return "Failed to read description.";
  }
 cur++;
 events[name][E_DESC]=desc;

 if(line[cur]!="{") return "Failed to read announcement.";
 cur++; ann="";
 while(line[cur]!="}")
  {
   ann+=line[cur]+"\n";
   cur++; if(cur==last) return "Failed to read announcement.";
  }
 cur++;
 events[name][E_ANNOUNCE]=ann;

 if(!is_number(line[cur])) return "Failed to load announcement_mins.";
 events[name][E_ANNOUNCE_MINS]=atoi(line[cur]);
 cur++;

 events[name][E_PROPS]=({ });
 while(cur!=last)
  {
   prop=line[cur];
   cur++;
   switch(prop_type(type,prop))
    {
     case 0: 
       return "Invalid prop: "+prop+".";
     case PT_BOOLEAN:
       value=(line[cur]=="1" ? "t" : "f");
       break;
     case PT_STRING:
     case PT_DATETIME:
     case PT_INT:
       value=line[cur];
       break;
     case PT_MEMO:
     case PT_ARRAY:
       if(line[cur]!="{") return "Failed to read prop: "+prop+".";
       cur++; value=""; tmp=({ });
       while(line[cur]!="}")
        {
         tmp+=({ line[cur] });
         cur++; if(cur==last) "Failed to read prop: "+prop+".";
        }
       value=implode(tmp,"\n");
       break;
    }
   
   err=set_prop(name,prop,value);
   if(err!=SE_OK) return "Failed to set prop: "+prop+".\n"+err;
   cur++;
  }

 return 1;
}

