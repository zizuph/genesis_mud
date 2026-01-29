/*
 * /d/Kalad/common/guilds/new_thanar/arm/medallion.c
 * The reward for collecting four parts of a medallion and having
 * the blacksmith in kalad mending it into a medallion. This 
 * item will be be part of the Quest to summon the Avatar.
 * 
 * Created by Zignur Feb 2018
 *
 */


#pragma strict_types
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Kalad/defs.h"
inherit "/std/object";
inherit "/lib/wearable_item";



/* Global Variables */

/* How much extra stat that the armour will grant in the top two stats */
static int BONUS_STAT =10;
int highest_stat;
int second_highest_stat;

#define ADJ1 ({"extravagant","shimmering","flashy","beautiful",\
                      "magnificient","opulent"})
#define ADJ2 ({"golden","platinum","topaz","diamond-encrusted","gold",\
                   "silver"})

/*
 * Function name:        create_object
 * Description  :        Function used to create the medallion
 *                   
 */
public void
create_object()
{
   string adj1 = one_of_list(ADJ1);
   string adj2 = one_of_list(ADJ2);
   
   setuid();
   seteuid(getuid());
    
   set_name("medallion");
   set_adj(adj1);
   add_adj(adj2);
   set_short(adj1 + " " + adj2 + " medallion");
   set_long("A long, beautifully-crafted "+adj2+" chain medallion. It is a "+
      "symbol of servitude to the beliefs and purpose of the Thanarians "+
      "and the patron god of humanity, Thanar. It radiates with power " +
      "this is clearly a very ancient and powerful artifact. The front " +
      "of the the medallion is engraved with a symbol of a snake. Its " +
      "back is covered with delicate inscribed ancient writing.\n");
   set_wf(this_object());
   set_slots(A_NECK);
   
   add_item(({"symbol", "engraved symbol", "snake symbol", "snake"}),
      "The symbol is engraved within the medallion and the design "+
      "is of a snake wrapped around a sword.\n");
   add_item(({"writing", "ancient writing", "delicate ancient writing"}),
      "Delicate ancient writing covers the back of the medallion, but "+
      "you fail to understand its meaning.\n");
   
   add_prop(OBJ_S_WIZINFO, "Item used for the Quest to Summon the avatar " +
      " in Kalad, it also increase its wearers two highest stats by 10.\n");
  
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 100);
} /* create_object */

int
sort_descending(int stat1, int stat2)
{
    return wearer->query_stat(stat2) - wearer->query_stat(stat1);
}

public int
wear(object item)
{
    int *stats = ({ SS_STR, SS_DEX, SS_CON, SS_INT, SS_WIS, SS_DIS });
    sort_array(stats, sort_descending);
    
    /* Get the highest and second highest stat */
    highest_stat = stats[0];
    second_highest_stat = stats[1];
    /* Add the stat bonuses */
    wearer->set_stat_extra(highest_stat,wearer->query_stat_extra(highest_stat)
                           + BONUS_STAT);
    wearer->set_stat_extra(second_highest_stat,wearer->
                           query_stat_extra(second_highest_stat) + BONUS_STAT);            
    write("You wear the " + short() + " around your neck " +
      "adjusting it to sit straight. Highest stat is "+ highest_stat + " second highest is " + second_highest_stat + " .\n");
    say(QCTNAME(TP) + " wears the " + short() + " around " +
      HIS(TP) + " neck adjusting it to sit straight.\n");
    
    return 1;
} /* wear */

public int
remove(object item)
{
    /* Remove the stat bonuses */   
    wearer->set_stat_extra(highest_stat,wearer->query_stat_extra(highest_stat)
                           - BONUS_STAT);
    wearer->set_stat_extra(second_highest_stat,wearer->
                           query_stat_extra(second_highest_stat) - BONUS_STAT);     
    write("You remove the " + short() + " from around your neck.\n");
    say(QCTNAME(TP) + " removes the " + short() +
      " from around " + HIS(TP) + " neck.\n");       
    return 1;
} /* remove */

void
enter_env(object env, object from)
{
    /* Required to add magic obj effects to the item */
    ::enter_env(env, from);
 
} /* enter_env */

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
} /* leave_env */