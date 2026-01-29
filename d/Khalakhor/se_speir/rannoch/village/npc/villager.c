/* File         : /d/Khalakhor/se_speir/rannoch/npc/villager.c
 * Creator      : Darragh@Genesis
 * Date         : 00-12-22      
 * Purpose      : Npc in the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_type
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/random.h"
#include "/d/Khalakhor/common/room/nameserver.h"
#include "npc.h"
#define  SEPT (({"Goireas","Garradair","Turail","Coirbte","Reamhar","Deireannach","Aiteas"}))
 
inherit STDHUMAN;
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";
int     has_armed=0;

/*
 * Function name: arm_me
 * Description  : Clones in the villager's equipment
 *                and has him/her wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */

public void arm_me() 
{
    if (has_armed) return;

    seteuid(getuid());
 
    if (query_gender()==G_MALE)
       {
       clone_object("/w/darragh/rannoch/arm/shirt")->move(TO);
       clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
       clone_object("/w/darragh/rannoch/arm/breeches")->move(TO);
       clone_object("/w/darragh/rannoch/arm/boots")->move(TO);
       }
    else
       {
       clone_object("/w/darragh/rannoch/arm/skirt")->move(TO);
       clone_object("/w/darragh/rannoch/arm/bonnet")->move(TO);
       clone_object("/w/darragh/rannoch/arm/shirt")->move(TO);
       clone_object("/w/darragh/rannoch/arm/boots")->move(TO);
       }
       command("wield all");
       command("wear all");
       has_armed = 1;
}
  
void do_add_acts() 
{
   add_act("emote murmurs something about the weather.");
   add_act("emote glares at you.");
   add_act("stretch");
   add_act("scratch chin");
   add_act("say Blasted weather.");
   add_act("say I wish the roads were safe.");
   add_act("say I need something to drink.");
   add_act("say Our walls will keep them all out, that's for sure.");
   add_act("say No need for worries today, I hope.");
   add_act("say It's getting crowded around here these days!");

   add_cact("scream");
   add_cact("swear loudly");

   add_cchat("Help! I'm being attacked!");
   add_cchat("Somebody help me!");
   add_cchat("Alert the guards, someone!");
   add_cchat("Please stop!");

   if (query_gender()==G_FEMALE)
      {
      add_act("emote reties her bonnet beneath her chin.");
      add_act("emote wipes her hands on her shirt.");
      add_act("emote smiles slightly at you.");

      add_act("emote smooths the wrinkles of her skirt.");
      add_cchat("I'm just a defenseless woman!");
      add_cchat("How very brave of you!");

      }
   else
      {
      add_act("emote sneezes into his hand.");
      add_act("emote runs his grimy fingers through his hair.");
      add_act("emote scratches his armpit.");
      add_act("emote inspects his boots closely.");
      add_act("emote glances briefly in your direction.");

      add_cchat("I have a wife and children at home! Sod off!");
      }
}
 
 
/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a villager.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void create_khalakhor_human() {
    int     level=11+random(50);
    string* adj;
    string  sept=SEPT[(random(sizeof(SEPT)))];
 
    //randomly select male/female
    if (random(3))
       {
       set_gender(G_MALE);
       set_name(SERVERFILE->get_name(G_MALE));
       add_name(({"man","gent"}));
       set_adj(RANDOM_DETAILED_ADJS(TO));
       adj=query_adj(1);
       add_adj("handsome");
       set_long("This "+adj[0]+" "+adj[1]+" male human "
              + "seems to be one of the few villagers who does "
              + "not hurry about with some daily task.\n");
       }
    else
       {
       set_gender(G_FEMALE);
       set_name(SERVERFILE->get_name(G_FEMALE));
       add_name(({"lass","woman"}));
       set_adj(RANDOM_DETAILED_ADJS(TO));
       adj=query_adj(1);
       add_adj("bonnie");
       set_long("This "+adj[0]+" "+adj[1]+" female human is "+
                "probably taking a break from her duties.\n");
       }
 
    set_living_name(lower_case(query_name()));
    add_name("villager");
    set_random_size_descs();
    cs_set_clan(sept);
    set_title(sept+" of Clan Abhainn");
    default_config_npc(level);
    set_skill(SS_UNARM_COMBAT, level);
    set_skill(SS_DEFENCE, level);
    set_alignment(0);
    set_exp_factor(50);
    set_act_time(60);
    do_add_acts();
    set_restrain_path("/w/darragh/rannoch/village");
    set_random_move(10);
arm_me();
 
    set_default_answer("Can't help you there I'm afraid.");
    add_ask(({"abhainn"}),
        "say That's where you are now, yes.",1);
}
/*
 * Function name: remove_object (MASK)
 * Description  : Return name to name server before we die
 * Arguments    : n/a
 * Returns      : n/a
 */
public void remove_object() {
    SERVERFILE->return_name(query_gender(),lower_case(query_name()));
   ::remove_object();
}
/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces themselves
 *                to us.
 * Arguments    : str - Name of the player introducing.
 * Returns      : 1
 */
public int
hook_return_intro(string str)
{
 
   if (query_gender()==G_MALE)
      {
      command("say Well met, "+capitalize(str)+".");
      command("say I'm "+query_name()+" "+query_title()+", I hope "+
              "you won't cause us any trouble.");
      command("bow slightly");
      }
   else
      {
      command("say Hello there, "+capitalize(str)+".");
      command("say I'm "+query_name()+" "+query_title()+", nice "+
              "to meet you.");
      command("curtsey quickly");
      }
   (find_player(lower_case(str)))->add_introduced(lower_case(query_name()));
   return 1;
}
 
