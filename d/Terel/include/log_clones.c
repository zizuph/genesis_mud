/* Logs the cloning of items
 *
 * Tomas  -- July 2000
 */

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <files.h>
#include <macros.h>

inherit STDARMOUR;

#define LOG_FILE "/d/Terel/log/cloned_items"

int     given_away;
string  dropped_by_wiz,
        cloned_by_wiz;


public void
enter_env(object to, object from)
{
  string domain;

  ::enter_env(to, from);

  domain = SECURITY->query_wiz_dom(to->query_real_name());

  seteuid(getuid(this_object()));

  if ((domain != "Terel") && (domain != "Khalakhor"))

  if (!from && TP->query_wiz_level()) 
  {
     cloned_by_wiz = CAP(TP->query_real_name());
    if (!living(to)) write_file(LOG_FILE,TP->query_name()+ 
       " cloned the "+short()+" into "+file_name(ENV(TO))+". "+ctime(time())+".\n");
    else write_file(LOG_FILE,TP->query_name()+
       " cloned the "+short()+"."+ctime(time())+".\n");
  }
  else if (given_away && from->query_wiz_level())
  {
    write_file(LOG_FILE,from->query_name()+" gave the "+short()+" to "+
       to->query_name()+". "+ctime(time())+".\n");
    given_away = 0;
  }
  if (!living(from) && strlen(dropped_by_wiz)) {
    write_file(LOG_FILE,TP->query_name()+
    " picked up the "+short()+" dropped by "+dropped_by_wiz+" in "+
      file_name(ENV(TP))+". "+ctime(time())+".\n");
  }
  else if (!living(from) && strlen(cloned_by_wiz)) 
  {
    write_file(LOG_FILE,TP->query_name()+
       " picked up the "+short()+" cloned by "+cloned_by_wiz+
       " in "+file_name(ENV(TP))+". "+ctime(time())+".\n");
  }
}

/*

public void
enter_inv(object ob, object from)
{
   string str,domain,where;
   mixed rank;

    ::enter_inv(ob,from);
    if (ob->query_wiz_level())
    {
      where = file_name(ENV(ob));
      rank = WIZ_N[SECURITY->query_wiz_rank(ob->query_real_name())];
      domain = SECURITY->query_wiz_dom(ob->query_real_name());
      str = ob->query_real_name(); 
      str = str + ", " + rank + ", " + domain + ", " + where;
      if ((domain != "Terel") && (domain != "Khalakhor"))
        write_file(W_LOG, str + " (" + ctime(time()) + ")\n");
    }

}

*/
