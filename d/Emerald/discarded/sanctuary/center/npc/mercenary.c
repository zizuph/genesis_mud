inherit "/d/Emerald/std/emerald_monster.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

#define	TO	this_object()

mixed my_equip();
int my_gender();

void
create_emerald_monster()
{
    int x, y;

    string *arr;

    arr = ({"stern", "long-haired", "scowling", "dark-eyed", "frowning",
      "dark-skinned", "nervous", "pale", "scarred",
      "black-eyed", "grim", "green-eyed", "sneering", "brown-eyed",
      "cautious", "hawk-nosed", "confident", "leering",
      "haughty", "thin-lipped", "proud", "arrogant",
      "dashing", "rugged", "roguish", "pock-marked"});

    x = random(sizeof(arr)/2)*2;   /* Sets random features of NPC */
    y = random(sizeof(arr)/2)*2;
    add_adj(arr[x]);
    add_adj(arr[y+1]);

    set_race_name("human");
    set_long("This mercenary stalks the inner streets of Sanctuary. \n");
    add_prop(LIVE_I_NEVERKNOWN, 1); /* Never introduces itself */
    add_prop(CONT_I_HEIGHT, 200);
    add_prop(OBJ_I_HIDE, 60+random(20)); /*NPC is automatically hidden*/
    add_prop(NPC_I_NO_RUN_AWAY, 1); /*NPC wont run away*/

    set_alignment(-100+random(-500));
    set_stats(({ 20+random(20), 40+random(15), 30+random(20),
	30+random(20), 30+random(20), 50}));
    set_skill(SS_DEFENCE, 35+random(30));
    set_skill(SS_BLIND_COMBAT, 20+random(20));
    set_skill(SS_HIDE, 50+random(20));
    set_skill(SS_PARRY, 30);
    set_skill(SS_WEP_SWORD, 40+random(30));
    set_skill(SS_WEP_KNIFE, 30+random(30));
    set_skill(SS_LOC_SENSE, 35+random(30));
    set_skill(SS_AWARENESS, 30+random(20));
    set_gender(my_gender());
    set_act_time(20); /* Set action Interval */
    add_act("hmm");
    add_act("sneer");
    add_act("growl");
    add_act("snicker");

    set_aggressive(1);
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
	mywep = "/d/Emerald/sanctuary/wep/mer_sword";
	break;
    case 1:
	mywep = "/d/Emerald/sanctuary/wep/mer_dagger";
	break;
    case 2:
	mywep = "/d/Emerald/sanctuary/wep/mer_stiletto";
	break;
    case 3:
	mywep = "/d/Emerald/sanctuary/wep/mer_poison_knife";
	break;
    case 4:
	mywep = "/d/Emerald/sanctuary/wep/mer_longsword";
	break;
    default:
	break;
    }

    switch (h)
    {
    case 0:
	myarm = "/d/Emerald/sanctuary/arm/mer_cloak";
	myarm2 = "/d/Emerald/sanctuary/arm/mer_blk_mantle";
	return ({ mywep , myarm , myarm2 });
	break;
    case 1:
	myarm = "/d/Emerald/sanctuary/arm/mer_blk_mantle";
	return ({ mywep ,  myarm });
	break;
    case 2:
	myarm = "/d/Emerald/sanctuary/arm/mer_red_tunic";
	return ({ mywep ,  myarm });
	break;
    case 3:
	myarm = "/d/Emerald/sanctuary/arm/mer_lshirt";
	myarm2 = "/d/Emerald/sanctuary/arm/mer_boots";
	return ({ mywep , myarm , myarm2 });
	break;
    case 4:
	myarm = "/d/Emerald/sanctuary/arm/mer_plate";
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
