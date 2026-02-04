// thbracers.c 
// Coded by Shinto 092700

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/d/Terel/include/quest_bits.h"
#include <files.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>
#define LOG_FILE "/d/Terel/log/cloned_armours"

int added_skill;

int     given_away;
string  dropped_by_wiz,
        cloned_by_wiz;

public void
create_terel_armour()
{
    set_name("bracers");
    set_adj("black");
    set_adj("steel");
    set_short("pair of black steel bracers");
    set_long("These are black steel bracers made of black cold steel. "+
                   "On the underside of both arms is an insignia of a black hand.\n");
    set_af(TO);
    set_ac(45);
    set_at(A_ARMS);
    set_am(({0,0,0}));
    set_armour_size(ANY_SIZE);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(10)+5);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,
               "The bracers provide excellent protection for the arms and "+
               "will raise a wearers pick pockets and open locks skill to "+
               "a max of 25 based on the players dex.\n");
    add_prop(MAGIC_AM_ID_INFO,({
         "The bracers provide excellent protection.",50, 
         "The bracers will improve some thieving abilities of the wearer.",70}));
}

public mixed
wear_terel_armour(object obj)
{

     if(!TP->test_bit("Terel", QUEST_HAQ_GROUP, QUEST_HAQ_BIT))
         return 0;

   // Check the players dex and then add the extra skills in wielding.

    added_skill = (10 + ((TP->query_stat(SS_DEX))/10));
    if(added_skill > 25)
        added_skill = 25;
    if ((TP->query_skill(SS_OPEN_LOCK) + added_skill) > 100)
    {
        added_skill = (100-(TP->query_skill(SS_OPEN_LOCK)));
    }

    if ((TP->query_skill(SS_PICK_POCKET) + added_skill) > 100)
    {
        added_skill = (100-(TP->query_skill(SS_PICK_POCKET)));
    }

    TP->set_skill_extra(SS_OPEN_LOCK, (TP->query_skill_extra(SS_OPEN_LOCK) +
added_skill));

    TP->set_skill_extra(SS_PICK_POCKET, (TP->query_skill_extra(SS_PICK_POCKET) +
added_skill));
    return 0; 
}

int remove(object arm) {

    object wearer;
    wearer = query_worn();
    if(!TP->test_bit("Terel", QUEST_HAQ_GROUP, QUEST_HAQ_BIT))
        return 0;  

    // Remove the extra skill when the bracers are removed.

    wearer->set_skill_extra(SS_OPEN_LOCK, 
            (wearer->query_skill_extra(SS_OPEN_LOCK) - added_skill));
    wearer->set_skill_extra(SS_PICK_POCKET, 
            (wearer->query_skill_extra(SS_PICK_POCKET) - added_skill));
    return 0; 
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
