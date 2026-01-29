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

   set_gender(my_gender());
   x = random(sizeof(arr)/2)*2;
   y = random(sizeof(arr)/2)*2;
   add_adj(arr[x]);
   add_adj(arr[y+1]);
   set_race_name("human");
   add_name("traveller");
   set_long("This human is one of many travellers on the roads of Emerald. "+
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
   set_chat_time(7);
   add_chat("Hmm...all these elves...");
   add_chat("We humans don't tire as easily.");
   set_act_time(8);
   add_act("grin charm");
   add_act("emote looks down the long, winding road");
   add_cchat("Damn you!! Get away!");
   add_cact("emote looks for a route of escape.");
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

my_equip()
{

	string mywep, myarm, myarm2;
	int g, h;
	g = random(5);
	h = random(5);
	switch (g)
	{
		case 0..1:
			mywep = "/d/Emerald/wep/trv_quarterstaff";
			break;
		case 2..4:
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
