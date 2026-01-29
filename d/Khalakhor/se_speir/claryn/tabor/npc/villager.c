/*
 *
 * Random villager in Tabor Sogh
 *
 * Zima, March 14, 1998
 * Refactored
 * Tapakah, 08/2021
 */

#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/random.h"
#include "/d/Khalakhor/common/room/nameserver.h"
#include "npc.h"
#define  SEPT (({"Gilvary","Neese","Stuart","Larsech","Ogden"}))
 
inherit BASE_NPC;
 
void
arm_me () { 
  armours = query_gender() == G_MALE
    ? ({ "/d/Khalakhor/common/arm/shirt_cloth",
         "/d/Khalakhor/common/arm/belt",
         "/d/Khalakhor/common/kilts/kilt_tabor"})
    : ({ "/d/Khalakhor/common/arm/dress",
         "/d/Khalakhor/common/arm/bonnet",
         "/d/Khalakhor/common/arm/apron" });
  ::arm_me();
}
 
void
do_add_acts ()
{
  add_act("emote breaths in the sea air deeply.");
  add_act("emote glances out over the sea vigilantly.");
  add_act("say 'Tis a beautiful day, truly tis!");
  add_act("say There's the smell 'o a storm brewing, I say.");
  add_act("say Top 'o the mornin' to ya, stranger.");
  if (query_gender()==G_FEMALE) {
    add_act("emote reties her bonnet beneath her chin.");
    add_act("emote wipes her hands on her apron.");
    add_act("emote nods her head to you politely.");
    add_act("emote smooths the wrinkles of her dress.");
  }
  else    {
    add_act("emote pulls his kilt up higher above his hips.");
    add_act("emote rubs his chin thoughtfully.");
    add_act("emote adjusts his vest vainly.");
    add_act("emote smooths the wrinkles of his kilt.");
    add_act("emote admires your arms covetously");
  }
}

void
configure_me () {
  object env = previous_object(0);
  string in_pub = env ? function_exists("init_pub", env) : 0;
  string* adj;
  //randomly select male/female
  if (in_pub || random(2)) {
    set_gender(G_MALE);
    set_name(SERVERFILE->get_name(G_MALE));
    add_name(({"man","gent"}));
    set_adj(RANDOM_DETAILED_ADJS(TO));
    adj=query_adj(1);
    add_adj("handsome");
    set_long("He is a "+adj[0]+" "+adj[1]+" villager. Dressed in the "+
             "garb of Clan Tabor, he looks a handsome gent in his "+
             "kilt and vest.\n");
  }
  else  {
    set_gender(G_FEMALE);
    set_name(SERVERFILE->get_name(G_FEMALE));
    add_name(({"lass","woman"}));
    set_adj(RANDOM_DETAILED_ADJS(TO));
    adj=query_adj(1);
    add_adj("bonnie");
    set_long("This bonnie lass is a "+adj[0]+" "+adj[1]+" villager, "+
             "dressed modestly with her apron and bonnet, the traditional "+
             "garb of the local women.\n");
  }

}

void
create_khalakhor_human () {
  int     level=10+random(50);
  string  sept=SEPT[(random(sizeof(SEPT)))];

  set_living_name(lower_case(query_name()));
  add_name("villager");
  set_random_size_descs();
  cs_set_sept("Gilvary");
  cs_set_clan(sept);
  set_title(sept+" of Clan Tabor");
  default_config_npc(level);
  set_skill(SS_UNARM_COMBAT, level);
  set_skill(SS_DEFENCE, level);
  set_alignment(0);
  set_act_time(60);
  do_add_acts();
  set_restrain_path("/d/Khalakhor/se_speir/claryn/tabor/room");
  set_monster_home("/d/Khalakhor/se_speir/claryn/tabor/room/road_1_5");
  set_random_move(60);
 
  set_default_answer("I'm afraid I can't answer that.");
  add_ask(({"gebann","Gebann","prior","Prior"}),
          "say Prior Gebann is usually in his priory, the house just "+
          "south of the kirk.",1);
  add_ask("kirk",
          "say We've a wee kirk, but it serves us well. It's on the north "+
          "side of the village.",1);
  set_alarm(0.5, 0.0, arm_me);
  configure_me();
}
/*
 * Function name: remove_object (MASK)
 * Description  : Return name to name server before we die
 * Arguments    : n/a
 * Returns      : n/a
 */
void
remove_object ()
{
  SERVERFILE->return_name(query_gender(),lower_case(query_name()));
  ::remove_object();
}

void
hook_return_intro_new (string str)
{
  if (query_gender()==G_MALE) {
    command("say Top 'o the mornin' to ya, "+capitalize(str)+"!");
    command("say I'm "+query_name()+" "+query_title()+", and welcome to "+
            "Tabor Sogh!");
    command("bow deeply");
  }
  else {
    command("say Goo' day to ya, "+capitalize(str)+"!");
    command("say I'm "+query_name()+" "+query_title()+", and pleased to "+
            "make yer acquaintance.");
    command("curtsey politely");
  }
  (find_player(lower_case(str)))->add_introduced(lower_case(query_name()));
}
 
