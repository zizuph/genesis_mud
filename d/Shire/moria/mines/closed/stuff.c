inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/bits.h"

#define QUEST_NAME "locket"

/* Function prototypes */
void reward_moria_quest(object player);
void test_moria_quest(object player);



void test_moria_quest(object player)
{

    if(player->test_bit("Shire",EASTERN_GROUP,MORIA_EXIT_BIT))
    {
      return 1;
    }
     if(!player->query_prop("_found_the_key"))
     {
       say(QCTNAME(player)+ " places the key on the runes but nothing happens.\n");
       write("The key seems to have no magic for you.\n");
       return 1;
      }
     
            reward_moria_quest(player);
						return 1;
}


void
reward_moria_quest(object player)
{
          player->remove_prop("_found_the_key");
          player->set_bit(EASTERN_GROUP,MORIA_EXIT_BIT);
          player->add_exp(MORIA_EXIT_EXP,0);
          seteuid(getuid(TO));
          log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
          CAP(player->query_real_name()) + " rewarded with "+MORIA_EXIT_EXP+" exp, "+
          "<"+player->query_average_stat()+"> avg stats.\n");
          tell_object(player,"You feel much more experienced!\n");
}

