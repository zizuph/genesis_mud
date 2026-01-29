inherit "/d/Emerald/std/emerald_monster.c";
inherit "/d/Emerald/std/aid_npc.c";

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
   set_gender(my_gender());
   add_adj(arr[x]);
   add_adj(arr[y+1]);
   set_race_name("elf");
   add_name("traveller");
   set_long("This elf is one of many travellers on the roads of Emerald. "+
        "Perhaps "+HE_SHE(TO) + " is seeking a new life in another city; "+
        "perhaps, just a change of scenery for a few days. "+
        capitalize(HE_SHE(TO)) + " seems weary from walking the roads.\n");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_short(arr[x] + " " + arr[y+1] + " " + query_race_name() + " traveller");

   set_alignment(250+random(500));
   set_stats(({ 20+random(20), 40+random(15), 30+random(20),
		30+random(20), 30+random(20), 50}));
   set_skill(SS_DEFENCE, 20+random(30));
   set_skill(SS_PARRY, 30);
   set_skill(SS_WEP_SWORD, 20+random(30));
   set_skill(SS_WEP_KNIFE, 20+random(30));
   set_skill(SS_WEP_POLEARM, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_restrain_path( ROAD_ROOMS );
   set_random_move(6);
   set_chat_time(6);
   set_cchat_time(4);
   set_act_time(7);
   set_cact_time(6);
   add_act("sigh wearily");
   add_act("smile hopeful");
   add_chat("Ahh...I can't wait to rest my feet!");
   add_cact("panic");
   add_cchat("What are you doing?!?");
   add_equipment(my_equip());
}

my_equip()
{

	string mywep, myarm, myarm2;
	int g, h;
	g = random(5);
	h = random(5);
	switch (g)
	{
		case 0:
			mywep = "/d/Emerald/wep/trv_quarterstaff";
			break;
		case 1:
			mywep = "/d/Emerald/wep/trv_walking_stick";
			break;
		case 2:
			mywep = "/d/Emerald/wep/trv_curved_dagger";
			break;
		case 3:
			mywep = "/d/Emerald/wep/trv_sharp_knife";
			break;
		case 4:
			mywep = "/d/Emerald/wep/trv_shortsword";
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
		case 3:
			myarm = "/d/Emerald/arm/trv_leather_shirt";
			myarm2 = "/d/Emerald/arm/trv_leather_boots";
			return ({ mywep , myarm , myarm2 });
			break;
		case 4:
			myarm = "/d/Emerald/arm/trv_robes";
			return ({ mywep ,  myarm });
			break;
		default:
			break;
	}
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
