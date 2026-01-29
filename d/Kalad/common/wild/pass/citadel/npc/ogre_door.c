/*
 * By Korat
 * September 1996
 * 
 * A big ogre placed in the citadel. It has booze it drinks.
 * It will let the ones who gives him something to drink
 * through the door/blanket.
*/
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"

create_monster()
{
   int i;
   ::create_monster();
   set_name("ogre");
   set_race_name("ogre");
   set_adj("lethal");
   add_adj("drunk");
   set_long("This huge ogre stinks of cheap booze! But it will not "+
      "lay down and play dead because of that ... rather the oposite. "+
      "It would be dangerous to irritate it!\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 100 + random(90));
   set_base_stat(3, 20);
   set_base_stat(4, 30);
   set_base_stat(5, 140);
   set_alignment(-800);
   set_knight_prestige(800);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_2H_COMBAT,70);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_DEFENCE,95);
   set_skill(SS_PARRY,90);
   set_skill(SS_AWARENESS,60);
   set_act_time(12);
   add_act(({"say Ugly bugs!","kill dwarf"}));
   add_act("growl .");
   add_act("fart");
   add_act("roar");
   add_act("get all from corpse");
   add_act("drink spirit");
   add_act("emote grins with sharp and dirty teeth.");
   set_cact_time(6);
   add_cact("snarl");
   add_cact("say I crush you with rock!");
   add_cact("laugh evil");
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(NPC_I_NO_RUN_AWAY, 1);

   trig_new("%w 'drops' %s","react_drop");
}
void
arm_me()
{
   object booze, item;
   int i;

   seteuid(getuid(TO));

   booze = clone_object(CPASS(citadel/obj/booze));
   booze -> set_heap_size(random(20)+20);
   booze -> move(TO);

   item = clone_object(CPASS(wep/mol_club));
   item -> move(TO);
   item = clone_object(CPASS(citadel/wep/ogre_scimitar));
   item -> move(TO);
   command("wield all");

   MONEY_MAKE_SC(random(5))->move(TO,1);
   MONEY_MAKE_CC(random(75))->move(TO,1);
}

/*
 * Function name: attack_object
 * Description:   This function is called when we attack another object
 * Arguments:     enemy - The object we are about to attack
 */
public void
attack_object(object enemy)
{
    ::attack_object(enemy);

    /* Always best to get a few drinks down you during a fight */
    command("drink all");

    return;
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     enemy - The attacker
 */
public void
attacked_by(object enemy)
{
    ::attacked_by(enemy);

    /* Always best to get a few drinks down you during a fight */
    command("drink all");

    return;
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      if (F_DARE_ATTACK(TO,ob)) /* we dare to attack it */
         {
         command("say Ye stupid " + TP->query_nonmet_name() + "!");
         command("say Me eat you now!");
         command("kill " + (ob->query_real_name()));
         command("drink all");
      }
      else
         {
         command("emote takes a step back.");
         command("emote groans: Me not anything do ta dis dude!!");
         command("drink all");
      }
   }
}

public void
introduce_me(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("smirk");
      command("burp");
      command("say Got any booze on yah?");
   }
}
int
react_drop(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_drop",who);
      return 1;
   }
}
void
return_drop(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("get all coins");
      command("grin greed");
      command("get booze");
   }
}

/*
 * Function name:   special_attack
 * Description:     called when it is his turn to attack 
 * Arguments:       enemy: the player we are currently fighting
 * Returns:         1 if he makes a special attack, 0 if he doesn't
 */
public int
special_attack(object enemy)
{
    object me;
    int num;

    me = TO;
    
    num = random(10);
    
    if (!num)
    {
        /* No special attack this time. Just has a quick pint, instead. */
        command("drink spirit");
    }
    
    /* Carry out normal attack if no special attacks were executed. */
    return 0;
}

do_die(object enemy)
{
   if (TO->query_hp()>0) return;
   
   command("say Urghh! Dis not posseble! Me hurt!!");
   ::do_die(enemy);
}

/*
 * Function name:   reset_monster
 * Description:     get some more beers from the bar
 */
public void 
reset_monster()
{
    object booze, me;
    
    me = TO;

    command("drink all");  /* Looks like its time to get another round */
    
    booze = present("spirit", TO);
    if (!booze)
    {
        booze = clone_object(CPASS(citadel/obj/booze));
        booze -> set_heap_size(30);
        booze -> move(TO);
    }
}
