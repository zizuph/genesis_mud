#ifndef C_LOG
#define C_LOG 1
int given_away;
string dropped_by_wiz;

int
test_give()
{
  seteuid(getuid(this_object()));
  given_away = 1;
  return 0;
}

mixed
drop_check()
{
  if (TP->query_wiz_level())
    log_file("items",TP->query_name()+" dropped the "+TO->short()+" in "+file_name(ENV(TP))+" "+ctime(time())+".\n");
    dropped_by_wiz = TP->query_name();
  return 0;
}



void
enter_env(object to, object from)
{
  ::enter_env(to, from);
  seteuid(getuid(this_object()));
  if (!from && TP->query_wiz_level()) {
    if (!living(to)) log_file("items",TP->query_name()+" cloned the "+TO->short()+" into "+file_name(ENV(TO))+". "+ctime(time())+".\n");
    else log_file("items",TP->query_name()+" cloned the "+TO->short()+"."+ctime(time())+".\n");
    }
  if (given_away && from->query_wiz_level())
  {
    log_file("items",from->query_name()+" gave the "+TO->short()+" to "+to->query_name()+". "+ctime(time())+".\n");
  given_away = 0;
  }
  if (!living(from) && dropped_by_wiz) {
    log_file("items",TP->query_name()+" picked up the "+TO->short()+" dropped by "+dropped_by_wiz+" in "+file_name(ENV(TP))+". "+ctime(time())+".\n");
    }
}
#endif
