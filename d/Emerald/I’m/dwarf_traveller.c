inherit "/d/Emerald/std/emerald_monster.c";
inherit "/d/Emerald/std/aid_npc";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

#include "/d/Emerald/defs.h"

mixed my_equip();
int my_gender();

void
create_emerald_monster()
{
   int x, y;

   string *arr;

   arr = ({"stern", "long-haired", "smiling", "dark-eyed", "frowning",
		"tan-skinned", "confused", "ivory-skinned", "wrinkled",
		"blue-eyed", "grim", "green-eyed", "giggling", "brown-eyed",
		"carefree", "round-nosed", "scared", "thin-nosed",
		"confident", "hawk-nosed", "proud", "thin-lipped",
		"lonely", "rosey-cheeked", "sneering", "dimpled"});

   x = random(sizeof(arr)/2)*2;
   y = random(sizeof(arr)/2)*2;
   add_adj(arr[x]);
   add_adj(arr[y+1]);
   set_race_name("dwarf");
   add_name("traveller");
   set_gender(my_gender());
   set_long("This dwarf is one of many travellers on the roads of Emerald. "+
	"Perhaps "+HE_SHE(TO) + " is seeking a new life in another city; "+
	"perhaps, just a change of scenery for a few days. "+
	capitalize(HE_SHE(TO)) + " seems weary from walking the roads.\n");
   set_short(arr[x] + " " + arr[y+1] + " " + query_race_name() + " traveller");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_alignment(50+random(300));
   set_stats(({ 20+random(20), 40+random(15), 30+random(20),
		30+random(20), 30+random(20), 50}));
   set_skill(SS_DEFENCE, 20+random(30));
   set_skill(SS_PARRY, 30);
   set_skill(SS_WEP_AXE, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_restrain_path( ROAD_ROOMS );
   set_chat_time(8);
   set_act_time(7);
   add_chat("Ach...but the roads are long and the feet are weary.");
   add_act("emote grumbles something about the hardness of the road.");
   add_act("sigh wearily");
   set_cact_time("shout What did I do??");
   set_random_move(5);
   add_equipment(my_equip());
}

my_gender()
{
	int j;
	j = random(8);
	switch (j)
	{
		case 0..6:
			return 0;
			break;
		default:
			return 1;
			break;
	}
}

public void
add_introduced(string str)
{
  if(find_player(str)->query_npc())
	return;
  switch(random(5))
    {
    case 0:
      {
	command("say to "+str+" Greetings! I am happy to know you.");
	command("smile "+str);
	return;
	break;
      }
    case 1:
      {
	command("say to "+str+" Nice to know you.");
	command("nod "+str);
	return;
	break;
      }
    case 2:
      {
	command("say to "+str+" Well met, "+
		find_player(str)->query_race_name()+".");
	command("smile "+str);
	return;
	break;
      }
    case 3:
      {
	command("say to "+str+" May good fortune follow you.");
	command("nod "+str);
	return;
	break;
      }
    case 4:
      {
	command("say to "+str+" Hello. I hadn't met you before.");
	command("grin "+str);
	return;
	break;
      }
    }
}

my_equip()
{
	string mywep, myarm, myarm2;
	int g, h;
	g = random(5);
	h = random(5);
	switch (g)
	{
		case 0..2:
			mywep = "/d/Emerald/wep/trv_handaxe";
			break;
		case 3..4:
			mywep = "/d/Emerald/wep/trv_heavy_axe";
			break;
		default:
			break;
	}

	switch (h)
	{
		case 0:
			myarm = "/d/Emerald/arm/trv_cloak";
			myarm2 = "/d/Emerald/arm/trv_black_tunic";
			return ({ mywep , myarm , myarm2 });
			break;
		case 1:
			myarm = "/d/Emerald/arm/trv_black_tunic";
			return ({ mywep ,  myarm });
			break;
		case 2:
			myarm = "/d/Emerald/arm/trv_red_tunic";
			return ({ mywep ,  myarm });
			break;
		case 3..4:
			myarm = "/d/Emerald/arm/trv_leather_shirt";
			myarm2 = "/d/Emerald/arm/trv_leather_boots";
			return ({ mywep , myarm , myarm2 });
			break;
		default:
			break;
	}
}

attacked_by(object enemy)
{
  ::attacked_by(enemy);
  switch(random(3))
    {
    case 0:
      {
        command("shout Help me!!");
        break;
      }
    case 1:
      {
        command("emote cries out for help!");
        break;
      }
    case 2:
      {
        command("command say What the...??");
        break;
      }
    }
  get_assistance(enemy);
}
