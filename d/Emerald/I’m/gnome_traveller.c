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
   set_race_name("gnome");
   set_short(arr[x] + " " + arr[y+1] + " " + query_race_name() + " traveller");
   add_name("traveller");
 set_long("This gnome is one of many travellers on the roads of Emerald. "+
        "Perhaps "+HE_SHE(TO) + " is seeking a new life in another city; "+
        "perhaps, just a change of scenery for a few days. "+
        capitalize(HE_SHE(TO)) + " seems weary from walking the roads.\n");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_alignment(250+random(500));
   set_stats(({ 20+random(20), 40+random(15), 30+random(20),
		30+random(20), 30+random(20), 50}));
   set_skill(SS_DEFENCE, 20+random(30));
   set_skill(SS_PARRY, 30);
   set_skill(SS_WEP_SWORD, 20+random(30));
   set_skill(SS_WEP_KNIFE, 20+random(30));
   set_skill(SS_WEP_POLEARM, 20+random(30));
   set_skill(SS_AWARENESS, 30+random(20));
   set_act_time(7);
   set_chat_time(5);
   set_cchat_time(4);
   set_cact_time(6);
   add_act("yawn tired");
   add_act("smile gnomish");
   add_chat("HelloHowAreYouDoing??");
   add_chat("MyMyTheRoadsAreQuiteAJourneyFromOnePlaceToAnother!");
   add_cact("panic");
   add_cchat("HelpHelpI'mBeingAttacked!!");
   add_cchat("PleaseLeaveLittleMeAlone!");
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
		case 0..2:
			mywep = "/d/Emerald/wep/trv_sharp_knife";
			break;
		case 3..4:
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
			myarm = "/d/Emerald/arm/trv_multi_tunic";
			return ({ mywep ,  myarm });
			break;
		case 4:
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
        command("shout HelpMe!!");
        break;
      }
    case 1:
      {
        command("emote cries out for help!");
        break;
      }
    case 2:
      {
        command("command say WhatThe...??");
        break;
      }
    }
  get_assistance(enemy);
}
