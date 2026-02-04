#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
// inherit "/d/Terel/include/cloned_armours";
#include <files.h>
#include <macros.h>

#include <stdproperties.h>
#include <wa_types.h>

#define LOG_FILE "/d/Terel/log/cloned_armours"
#define WEARING_PROT_RING "_wearing_prot_ring"

int     given_away;
string  dropped_by_wiz,
        cloned_by_wiz;


void
create_terel_armour()
{
    set_name("ring");
    set_adj("gold");
    set_short("gold ring");
    set_long("This appears to be a plain gold ring.\n");
    set_at(A_ANY_FINGER);
    set_looseness(0);
    set_ac(15);
    set_armour_size(MEDIUM);
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_I_VALUE, 12*12*12*10);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "It appears to be enchanted. ", 10,
        "It will protect you from physical attacks.\n", 75 }));
    add_prop(OBJ_S_WIZINFO, "A ring of protection, adds 15 "+
        "ac to all locations, found on the assassin of Last, "+
        "Trevin. /d/Terel/last/npc/assassin \n");
}
mixed
wear_terel_armour(object obj)
{
    if(TP->query_prop(WEARING_PROT_RING))
    {
        write("The "+short()+" will not go on your finger.\n");
        return -1;
    }

    TP->add_prop(WEARING_PROT_RING, 1);
    write("The "+short()+" sparkles as you wear it.\n");
    return 0;
}

int
remove(object obj)
{
    TP->remove_prop(WEARING_PROT_RING);
    return 0;
}
public int *
query_shield_slots()
{
    return (::query_shield_slots() +
        ({A_BODY, A_L_ARM, A_R_ARM, A_LEGS, A_HEAD }));
}


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
