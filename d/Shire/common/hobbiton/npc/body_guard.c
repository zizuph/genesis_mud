/*
 *  A body guard for Gorge the potion salesman.
 *  Cloned by a call_out() (200 sec. delay) in ~Shire/common/hobbiton/er10
 */

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"

//   Prototypes
void arm();
void talk();
void shit();
void move_after(string dir);

void
create_monster()
{
  object wep;
  
  if (!IS_CLONE)
    return;
  
  set_name("grimrock");
  set_living_name("grimrock");
  set_adj("bulky");
  set_race_name("dwarf"); 
  set_long(break_string(
			"This is the salesman's bodyguard. He seems to be very capable "
			+ "at what he does. You probably shouldn't mess with him or his "
			+ "employer.\n",70));
  
  
  
  default_config_npc();
  set_stats(({ 150, 150, 150, 60, 50, 100 }));
  set_hp(50000);
  
  
  
  set_skill(SS_UNARM_COMBAT,60);
  set_skill(SS_WEP_SWORD,50);
  set_skill(SS_WEP_AXE,100);
  set_skill(SS_WEP_KNIFE,30);
  set_skill(SS_DEFENCE,100);
  set_skill(SS_PARRY,100);
  set_skill(SS_AWARENESS, 70);
  set_skill(SS_2H_COMBAT, 100);
  
  set_aggressive(0);
  set_attack_chance(0);
  
  set_cchat_time(3);
  add_cchat("This is fun!");
  add_cchat("I love my work!");
  add_cchat("Well didn't we do a big misstake!");
  
  add_prop(CONT_I_WEIGHT, 90000);   /* 90 Kg  */
  add_prop(CONT_I_VOLUME, 90000);   /* 90 Ltr */
  
  trig_new("%s 'arrives.' %s", "threat");
  trig_new("%s 'leaves' %s", "follow");

  seteuid(getuid(this_object()));
  set_alarm(1.0,0.0,&arm());
}

/*
Code to arm grimrock
*/
arm() {
object wep;

  wep = clone_object(HOBBIT_DIR + "wep/dwarf_axe");
  wep->move(this_object());
  command("wield axe");

}


/* 
Move to gorge
*/
void
move_after(string dir) {
  object ob;

  ob = find_living("gorge");
  move_living(dir,environment(ob));

}

/*
  follow(str1,str2)     Code to follow gorge
*/
follow(str1,str2) {
  string *dir;

  if (strlen(str2))
    dir = explode(str2, " ");
  if(str1 == "Gorge")
    set_alarm(1.0,0.0,&move_after(dir[0]));
}

/*
talk()    To say something
*/

void
talk() {
  object ob;

  ob = this_player();
  command("say Should I kill this " + ob->query_race() + ".\n");
}

/*
shit()
*/

void
shit() {

  command("sigh");
  command("sulk");

}

/*
threat(str)    Code to threaten a player.
*/

threat(str,tmp) {
  int t;

  t = random(3);
  set_alarm(itof(t + 2),0.0,&talk());
  set_alarm(11.0,0.0,&shit());

}


/* This is for the solamnic Knights */

query_knight_prestige() { return (-2); }

