#define DAYS_OF_WEEK ({"Sun","Mon","Tue","Wed","Thu","Fri","Sat"})
#define DAY_OF_WEEK(d) member_array(d,DAYS_OF_WEEK)+1
#define CHECK_ABORT if(str=="q") {abort(); return;}

void do_cleanup();
void type_dialog();
void r_f_time_dialog(string msg);
void r_f_day_dialog();
void day_num_dialog();
void days_dialog();
void enter_random_time();
void enter_fixed_time();
void done();
void abort();

void do_cleanup()
{
 TP->remove_prop(EVENT_I_FREQ);
 TP->remove_prop(EVENT_I_TIME_TYPE);
 TP->remove_prop(EVENT_I_DAY_TYPE);
 TP->remove_prop(EVENT_I_TIME);
 TP->remove_prop(EVENT_I_TO_ENTER);
 TP->remove_prop(EVENT_I_NAME);
 TP->remove_prop(EVENT_I_DAYS);
}

void start_scheduler_wizard(string event)
{
 do_cleanup();
 TP->add_prop(EVENT_I_NAME,event);

 write("Entering the custom events scheduler wizard.\n");
 write("Type 'q' to abort from any step.\n\n");

 type_dialog();
}

void type_dialog()
{
 write("Choose event frequency.\n"+
       "  [1] - Every day\n"+
       "  [2] - Every week\n"+
       ">> ");
 input_to("choose_type");
}

void choose_type(string str)
{
 int tp;

 CHECK_ABORT

 if(str!="1" && str!="2")
  {
   write("Choose 1 or 2.\n>> ");
   input_to("choose_type");
   return;
  }

 sscanf(str,"%d",tp);
 TP->add_prop(EVENT_I_FREQ,tp); 
 switch(tp)
  {
   case FR_DAY:
     r_f_time_dialog(""); break;
   case FR_WEEK:
     r_f_day_dialog(); break;
  }
}

void r_f_day_dialog()
{
 write("Chose one of the following:\n"+
       "  [1] - Random days\n"+
       "  [2] - Fixed days\n>> ");
 input_to("choose_day_type");
}

void choose_day_type(string str)
{
 int dt;

 CHECK_ABORT

 if(str!="1" && str!="2")
  {
   write("Choose 1 or 2.\n>> ");
   input_to("choose_day_type");
   return;
  }

 sscanf(str,"%d",dt);
 TP->add_prop(EVENT_I_DAY_TYPE,dt); 
 switch(dt)
  {
   case DY_RANDOM:
     day_num_dialog(); break;
   case DY_FIXED:
     days_dialog() ; break;
  }
}

void r_f_time_dialog(string msg)
{
 write(msg+"\nChose one of the following:\n"+
       "  [1] - Random time\n"+
       "  [2] - Fixed time\n>> ");
 input_to("choose_time_type");
}

void choose_time_type(string str)
{
 int tm;

 CHECK_ABORT

 if(str!="1" && str!="2")
  {
   write("Choose 1 or 2.\n>> ");
   input_to("choose_time_type");
   return;
  }

 sscanf(str,"%d",tm);
 TP->add_prop(EVENT_I_TIME_TYPE,tm); 
 switch(tm)
  {
   case TM_RANDOM:
     enter_random_time(); break;
   case TM_FIXED:
     enter_fixed_time(); break;
  }
}

void enter_random_time()
{
 write("Enter time period of format: hrs:mins-hrs:mins\n>> ");
 input_to("get_random_time");
}

void get_random_time(string str)
{
 string tm1,tm2,*to_enter;
 mixed *so_far;
 int i;

 CHECK_ABORT

 if(sscanf(str,"%s-%s",tm1,tm2)!=2)
  {
   write("Invalid format.\n"+
          "Enter time period of format: hrs:mins-hrs:mins\n>> ");   
   input_to("get_random_time");
   return;
  }

 if(!is_valid_time(tm1))
  {
   write("Invalid time: "+tm1+"\n"+
         "Enter time period of format: hrs:mins-hrs:mins\n>> ");
   input_to("get_random_time");
   return;
  }

 if(!is_valid_time(tm2))
  {
   write("Invalid time: "+tm2+"\n"+
         "Enter time period of format: hrs:mins-hrs:mins\n>> ");
   input_to("get_random_time");
   return;
  }

 if(compare_time(tm1,tm2)!=2)
  {
   write("Error: "+tm1+">="+tm2+"\n"+
         "Enter time period of format: hrs:mins-hrs:mins\n>> ");
   input_to("get_random_time");
   return;
  }

 so_far=TP->query_prop(EVENT_I_TIME);
 if(!so_far)
  {
   TP->add_prop(EVENT_I_TIME,({ tm1,tm2 }));
   done();
   return;
  }

 for(i=0;i<sizeof(so_far);i++)
  {
   if(!so_far[i])
    {
     so_far[i]=({ tm1,tm2 });
     TP->add_prop(EVENT_I_TIME,so_far);
     if(i==sizeof(so_far)-1) { done(); return; }
     to_enter=TP->query_prop(EVENT_I_TO_ENTER);
     r_f_time_dialog(to_enter[i+1]);
     return;
    }
  }
}

void enter_fixed_time()
{
 write("Enter fixed time of format: hrs:mins\n>> ");
 input_to("get_fixed_time");
}

void get_fixed_time(string str)
{
 string *to_enter;
 mixed *so_far;
 int i;

 CHECK_ABORT

 if(!is_valid_time(str))
  {
   write("Invalid time: "+str+"\n"+
         "Enter fixed time of format: hrs:mins\n>> ");  
   input_to("get_fixed_time");
   return;
  }

 so_far=TP->query_prop(EVENT_I_TIME);
 if(!so_far)
  {
   TP->add_prop(EVENT_I_TIME,str);
   done();
   return;
  }

 for(i=0;i<sizeof(so_far);i++)
  {
   if(!so_far[i])
    {
     so_far[i]=str;
     TP->add_prop(EVENT_I_TIME,so_far);
     if(i==sizeof(so_far)-1) { done(); return; }
     to_enter=TP->query_prop(EVENT_I_TO_ENTER);
     r_f_time_dialog(to_enter[i+1]);
     return;
    }
  }
}

void day_num_dialog()
{
 write("Enter number of random days you want the event to run on:\n>> ");
 input_to("get_day_num");
}

void get_day_num(string str)
{
 int days,i;
 string *to_enter;
 mixed *data;

 CHECK_ABORT

 if(!is_number(str))
  {
   write("Enter a valid number between 1 and 7.\n>> ");
   input_to("get_day_num");
   return;
  }

 sscanf(str,"%d",days);
 if(days<1 || days>7)
  {
   write("Enter a valid number between 1 and 7.\n>> ");
   input_to("get_day_num");
   return;
  }

 TP->add_prop(EVENT_I_DAYS,days);
 to_enter=allocate(days);
 data=allocate(days);

 for(i=0;i<days;i++)
   to_enter[i]="Specify time for "+LANG_WORD(i+1)+" day's event.";
 TP->add_prop(EVENT_I_TO_ENTER,to_enter);
 TP->add_prop(EVENT_I_TIME,data);
 r_f_time_dialog(to_enter[0]);
}

void days_dialog()
{
 write("Enter days of week you want your event to run on.\n"+
       "Format: day1,day2,...dayn.\n"+
       "Possible days: "+implode(DAYS_OF_WEEK,",")+".\n>> ");
 input_to("get_days");
}

void get_days(string str)
{
 string *days,*errs,*to_enter;
 int i,*p_days;
 mixed *data;

 CHECK_ABORT

 if(!str || !strlen(str))
  {
   write("Wrong format.\n"+
       "Format: day1,day2,...dayn.\n"+
       "Possible days: "+implode(DAYS_OF_WEEK,",")+".\n>> ");
   input_to("get_days");
   return;
  }

 days=explode(str,",");
 if(!sizeof(days))
  {
   write("Wrong format.\n"+
         "Format: day1,day2,...dayn.\n"+
         "Possible days: "+implode(DAYS_OF_WEEK,",")+".\n>> ");
   input_to("get_days");
   return;
  }

 errs=({ });
 for(i=0;i<sizeof(days);i++)
   if(member_array(days[i],DAYS_OF_WEEK)==-1) errs+=({ days[i] });

 if(sizeof(errs))
  {
   write("Invalid days of week: "+implode(errs,",")+".\n"+
         "Format: day1,day2,...dayn.\n"+
         "Possible days: "+implode(DAYS_OF_WEEK,",")+".\n>> ");
   input_to("get_days");
   return;
  }

 errs=is_unique(days);
 if(sizeof(errs))
  {
   write("Following days are repeated: "+implode(errs,",")+".\n"+
         "Format: day1,day2,...dayn.\n"+
         "Possible days: "+implode(DAYS_OF_WEEK,",")+".\n>> ");
   input_to("get_days");
   return;
  }
 
 to_enter=allocate(sizeof(days));
 data=allocate(sizeof(days));
 p_days=allocate(sizeof(days));

 for(i=0;i<sizeof(days);i++)
  {
   to_enter[i]="Specify time for "+days[i]+" event.";
   p_days[i]=DAY_OF_WEEK(days[i]);
  }

 TP->add_prop(EVENT_I_TO_ENTER,to_enter);
 TP->add_prop(EVENT_I_TIME,data);
 TP->add_prop(EVENT_I_DAYS,p_days);
 r_f_time_dialog(to_enter[0]);
}

string get_schedule_desc(string event)
{
 mixed *data,*time,*tm,days;
 int i;
 string *tmp;

 data=cevents[event][CE_SCHEDULE];
 if(!data) return "This event has not been scheduled yet.";

 switch(data[0])
  {
   case FR_DAY:
     time=data[1];
     if(!stringp(time)) 
       return "This event will run every day randomly between "+
         time[0]+" and "+time[1];
       return "This event will run every day at "+time;

   case FR_WEEK:
     days=data[1];
     time=data[2];
     if(sizeof(days))
      {
       tmp=allocate(sizeof(days));
       for(i=0;i<sizeof(days);i++)
        {
         tm=time[i];
         tmp[i]="on "+DAYS_OF_WEEK[days[i]-1];
         if(!stringp(tm)) tmp[i]+=" randomly between "+tm[0]+
           " and "+tm[1];
         else tmp[i]+=" at "+tm;
        }
       return sprintf("This event will run %d times a week, "+
         COMPOSITE_WORDS(tmp),sizeof(days));
      }

     tmp=allocate((int)days);
     for(i=0;i<days;i++)
      {
       tm=time[i];
       tmp[i]="on "+LANG_WORD(i+1)+" day";
       if(!stringp(tm)) tmp[i]+=" randomly between "+tm[0]+
         " and "+tm[1];
       else tmp[i]+=" at "+tm;
      }
     return sprintf("This event will run %d times a week randomly, "+
       COMPOSITE_WORDS(tmp),days);
  }
}

mixed *get_schedule(string event) {return cevents[event][CE_SCHEDULE];}

void done()
{
 mixed *data,*time,*days;
 string event;
 int fr;
  
 event=TP->query_prop(EVENT_I_NAME);
 time=TP->query_prop(EVENT_I_TIME);
 days=TP->query_prop(EVENT_I_DAYS);
 fr=TP->query_prop(EVENT_I_FREQ);

 switch(fr)
  {
   case FR_DAY:
     data=allocate(2);
     data[0]=FR_DAY;
     data[1]=time;
     break;

   case FR_WEEK:
     data=allocate(3);
     data[0]=FR_WEEK;
     data[1]=days;
     data[2]=time;
     break;
  }

 cevents[event][CE_SCHEDULE]=data;
 save();

 do_cleanup();
 write("DONE!\n");
 write(get_schedule_desc(event)+"\n");
 (CENGINE)->generate_plan(event);
}

void abort()
{
 do_cleanup();
 write("Aborted.\n");
}

string get_server(string event)
{
 return cevents[event][CE_SERVER];
}

string get_function(string event)
{
 return cevents[event][CE_FUNCTION];
}

string get_owner(string event)
{
 return cevents[event][CE_OWNER];
}

