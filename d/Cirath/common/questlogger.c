
inherit "/std/object";

#include "/d/Cirath/common/qbits.h"

string logdir = 0;

mixed create_logdir_name()
{
  string *apa;

  apa = explode(ctime(time())," ");

  return "/d/Cirath/log/"+apa[sizeof(apa)-1]+"/"+apa[1];
}

int create_object()
{
/*  if(logdir)
    return -1;
*/
  logdir = create_logdir_name();

  seteuid(getuid());

  return mkdir(logdir);
}

void special_log(string file,string text)
{
  write_file(logdir+"/"+file,text);
}

void log_quest(string who)
{

  special_log("questlog",extract(ctime(time()),4,15)+" "+who+" "+
             capitalize(TP->query_real_name())+"\n");
}

void old_log_quest(string who)
{
  write_file(QUESTLOG,extract(ctime(time()),4,15)+" "+who+" "+
             capitalize(TP->query_real_name())+"\n");
}

