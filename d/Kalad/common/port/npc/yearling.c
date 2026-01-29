/*
 *  /d/Kalad/common/port/npc/yearling.c
 *
 *  A tiny minotaur in the docks in Kalad
 *
 *  Created October 2017, by Andreas Bergstrom ( Zignur )
 */
#pragma strict_types
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include <money.h>


/* Prototypes */
public void        arm_me();

/* Global variables */
string *ArrAdj1 = ({ "young","juvenile","immature"});
string *ArrAdj2 = ({ "dark","brown","black"});
string Adj1 = one_of_list(ArrAdj1);
string Adj2 = one_of_list(ArrAdj2); 
 

/*
 * Function name:        create_monster 
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    ::create_monster();
    
    set_name("minotaur");
    add_name("yearling");
    set_race_name("minotaur");
    add_adj(({ Adj1, Adj2 }));

    set_short( Adj1+ " "+ Adj2 +" minotaur");
    
    set_long("A " +Adj1 + " " + Adj2 + " minotaur yearling. This" 
      + " " + Adj1+ " minotaur has massive horns, which look quite deadly." 
      + " He is clearly very drunk. He walks around in the harbor, looking"
      + " for something to amuse himself with. Even though this is"
      + " clearly a very young minotaur, you get a feeling he is"
      + " most likely more than capable of taking care of himself.\n");

    set_stats( ({70,70,70,70,70,70 }) );
                  
    set_skill(SS_WEP_SWORD,    60);
    set_skill(SS_WEP_AXE,      60);
    set_skill(SS_WEP_CLUB,     60);
    set_skill(SS_WEP_POLEARM,  60);
    set_skill(SS_WEP_KNIFE,    60);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_DEFENCE,      60);
    set_skill(SS_PARRY,        60);
    set_skill(SS_2H_COMBAT,    60);

    set_act_time(40 + random(10));
    add_act("emote looks around for something to drink.");
    add_act("emote takes a sip of beer.");
    add_act("emote complains about the hardship at sea.");
    add_act("emote boast about his massive horns.");
    add_act("emote wipes off some blood from his horns.");
    
    add_cact("say I will enjoy impaling you with my horns!");
    add_cact("emote cackles gleefully.");
    add_cact("say I always love a good fight! Bring it on landlubber!");
    add_cact("say You think you stand a chance against a minotaur?");

    setuid();
    seteuid(getuid());
} /* create_monster  */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{  
    /* Add the weapons */
    string  wep = one_of_list( ({ "sailor_sword","pgmclub" }) );                                  
    equip( ({ "/d/Kalad/common/port/wep/" + wep  }));
  
    /* Add the standard armours for minotaurs */
    equip( ({ "/d/Kalad/common/port/arm/sailor_armour",
              "/d/Kalad/common/port/arm/sailor_boots" }));
   
    /* Add some coins */
     MONEY_MAKE_SC(random(20))->move(this_object(),1);
    /* Add some booze */
    object beer;
    beer = clone_object("/d/Kalad/common/caravan/obj/jei_beer");   
    beer -> move(this_object());
    beer = clone_object("/d/Kalad/common/caravan/obj/jei_beer");   
    beer -> move(this_object());
    beer = clone_object("/d/Kalad/common/caravan/obj/jei_beer");   
    beer -> move(this_object());
    
} /* arm_me */



