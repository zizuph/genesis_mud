


inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"

int flag;

create_monster()
{
  object wep, arm;
  
  if (!IS_CLONE)
    return;

  set_short("shirriffe");
  set_name("donie");
  set_adj("fiery");
  set_race_name("hobbit"); 
  set_long(break_string(
    	"This is a Shire guard. He is placed here to keep the road"
       +"safe from the danger of the dark Trollshaws.\n",70));
  
  
  
  default_config_npc();
  set_stats(({120, 120, 100, 70, 40, 90 }));
  set_hp(4000);
  
  
  
  set_skill(SS_WEP_SWORD,      70);
  set_skill(SS_WEP_AXE,       100);
  set_skill(SS_DEFENCE,        50);
  set_skill(SS_PARRY,          50);
  set_skill(SS_AWARENESS,     100);
  set_skill(SS_2H_COMBAT,     100);
  
  
    trig_new("%w 'introduces' %s", "react_introduce");

  add_prop(CONT_I_WEIGHT, 90000);  
  add_prop(CONT_I_VOLUME, 90000);  
  
  set_alarm(1.0, 0.0, arm);
   set_alarm(1.0, 0.0, "arm1");

}


react_introduce(who, dummy)
{
	if (flag == 1)
	return 1;
	flag = 1;
    set_alarm(5.0, 0.0, "t0");
	return 1;
}
t0()
{
  command("say The dark and misty Trollshaws....");
  command("say it is not a safe place to be.");
   set_alarm(5.0, 0.0, "t1");
}

t1()
{
  command("say It is said to inhabit great danger.");
  command("say Trolls......lot's of trolls. "); 
   set_alarm(5.0, 0.0, "t2");
}

t2()
{
  command("say Be warned stranger....");
  command("say Trollshaws is a dangerous place.");
  set_alarm(5.0, 0.0, "t3");
}

t3()
{
  command("say Leave this place while still can.");
  command("say LEAVE!");
  set_alarm(5.0, 0.0, "t4");
}

t4()
{
  command("say The trolls may attacke any moment....");
  command("say Especially when it's dark.");
  set_alarm(5.0, 0.0, "t5");
}

t5()
{
  command("say The trolls show no mercy.....");
  command("say The trolls will eat you ALIVE.");
	flag = 0;

}


arm()
{
  object wep;

  wep = clone_object(STAND_WEAPON + "dwarf_axe");
  wep->move(this_object());
  command("wield axe");
}  


arm1()
{
  object arm;    

  arm = clone_object(STAND_ARMOUR + "boots.c");
  arm->move(this_object());
  arm = clone_object(STAND_ARMOUR + "m_plate.c");
  arm->move(this_object());
   
  command("wear all");
}






