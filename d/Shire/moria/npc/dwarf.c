inherit "/std/monster";

#include "defs.h"

/* #include "/d/Shire/ Wonder what? */

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

#define RNAMES ({ "Bimbur", "Grombur", "Timbur", "Grambur", "Orul",\
		  "Darin", "Parin", "Gyrin", "Thirin", "Thain" })

#define RLONG ({ \
    "This is a stout strong fellow with fiercy eyes.\n",\
    "A fat little dwarf with plump feet.\n",\
    "A long-bearded dwarf with black eyes.\n",\
    "A mean grey-bearded dwarf of good stealth.\n",\
    "A menacing stout dwarf with grim looks.\n",\
    "A wild looking dwarf with heavy arms.\n",\
    "A cunning dwarf with strong arms.\n",\
    "A rough built dwarf with cold eyes.\n",\
    "A giggling funny-looking dwarf.\n",\
    "A heavy built dwarf with green eyes.\n",\
})

#define RADJ ({ \
    "strong stout",\
    "fat little",\
    "long-bearded black-eyed",\
    "mean grey-bearded",\
    "menacing stout",\
    "heavy-armed wild",\
    "strong-armed cunning",\
    "cold-eyed rough-built",\
    "funny-looking giggling",\
    "green-eyed heavy-built",\
})

#define RCACTS\
({\
})

#define RWEAP ({ "axe", "hammer", "jav", "waraxe", "spear",\
		 "sword", "sword", "axe", "waraxe", "jav" })

#define WEPMAP ([ \
    "spear": ({ "spear", "pointed", 10, 25, W_JAVELIN, W_BOTH, W_IMPALE,\
		"This is a pointed spear." }),\
    "axe":   ({ "axe", "heavy", 30, 36, W_AXE, W_ANYH, W_SLASH | W_BLUDGEON,\
		"This is a heavy axe." }),\
    "waraxe":({ "waraxe", "large", 20, 45, W_AXE, W_ANYH, W_SLASH | W_BLUDGEON,\
		"This is a rather large waraxe with blood in its edges." }),\
    "jav":   ({ "javelin", "heavy", 24, 30, W_JAVELIN, W_BOTH, W_IMPALE,\
		"This is a heavy dwarven javelin." }),\
    "sword": ({ "sword", "long", 25, 25, W_SWORD, W_ANYH, W_SLASH, \
		"This is a long sword of dwarven design." }),\
    "hammer":({ "hammer", "war", 23, 36, W_CLUB, W_ANYH, W_BLUDGEON, \
		"This is a warhammer of dwarven design hitting like a club."}) \
])

/* Str, Dex, Con, Int, Wis, Dis */

#define RSTAT ({\
    ({ 40, 23, 80, 23, 23, 80 }),\
    ({ 45, 43, 79, 44, 65, 90 }),\
    ({ 50, 50, 79, 23, 43, 70 }),\
    ({ 70, 43, 78, 53, 75, 80 }),\
    ({ 70, 24, 77, 21, 32, 80 }),\
    ({ 50, 90, 78, 34, 53, 47 }),\
    ({ 46, 76, 76, 52, 42, 57 }),\
    ({ 49, 14, 78, 12, 12, 87 }),\
    ({ 90, 53, 92, 32, 44, 45 }),\
    ({ 99, 45, 97, 55, 42, 59 }),\
})

void arm_me(int i);

arm_me(int i)
{
    object weapon = clone_object("/std/weapon");
    mixed *entry  = WEPMAP[RWEAP[i]];
    switch(RWEAP[i]) {
	case "spear": set_skill(SS_WEP_JAVELIN, RSTAT[i][0]); break;
	case "jav":   set_skill(SS_WEP_JAVELIN, RSTAT[i][0]); break;
	case "axe"  : set_skill(SS_WEP_AXE, RSTAT[i][0]); break;
	case "sword": set_skill(SS_WEP_SWORD, RSTAT[i][1]); break;
	case "waraxe":set_skill(SS_WEP_AXE, RSTAT[i][0]); break;
	case "hammer":set_skill(SS_WEP_CLUB, RSTAT[i][0]); break;
    }
    weapon -> set_name(entry[0]);
    weapon -> set_adj(entry[1]);
    weapon -> set_hit(entry[2]);
    weapon -> set_pen(entry[3]);
    weapon -> set_wt(entry[4]);
    weapon -> set_hands(entry[5]);
    weapon -> set_dt(entry[6]);
    weapon -> set_long(entry[7]);
    weapon -> move(TO);
    command("wield weapon");
}

create_monster()
{
}

int my_num;
int query_my_num() { return my_num; }

create_me(int i)
{
    int j;
    string *my_acts;
    my_num = i;
    set_name(RNAMES[i]);
    set_adj(explode(RADJ[i]," "));
    set_race_name("dwarf");
    set_short(RADJ[i]+" small dwarf");
    set_long(
	RLONG[i]+" "+
	"These are dwarves, which you probably know from before.\n"
    );
    add_prop(CONT_I_HEIGHT, 60 + random(60));
    add_prop(CONT_I_WEIGHT, (60 + random(60)*1000));
    set_stats(RSTAT[i]);
    set_hp(10000);
    set_skill(SS_UNARM_COMBAT, random(15)+5);
    set_skill(SS_BLIND_COMBAT, 50+random(20));
    set_skill(SS_PARRY, 10+random(RSTAT[i][1]/2));
    set_skill(SS_DEFENCE, 20+random(10));

    /*
    set_cact_time(2);
    my_acts = RCACTS[i];
    for(j=0;j<sizeof(my_acts);j++)
	add_cact(my_acts[j]);
    */

    set_alignment(400-random(300));
    set_aggressive(1);
    set_attack_chance(100);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alarm(0.0, 0.0, &arm_me(i));
    set_pick_up(93);
}

void
enter_inv(object ob, object from)
{
    if(ob->id("_durins_axe_"))
    {
	command("shout I've got it!!");
	command("laugh");
	command("say Let us leave!");
	CONTROL->dwarf_leave(ob);
    }
}


int
query_stat(int stat)
{
    object *pack;
    int dis = 0;
    int i;

    if(stat==SS_DIS) {
	pack = CONTROL->attacking_dwarfs();
	for(i=0;i<sizeof(pack);i++)
	    if(pack[i] && living(pack[i]) && ETO==ENV(pack[i]))
		dis += RSTAT[i][5];
	return dis;
    }
    return ::query_stat(stat);
}

int query_knight_prestige() { return -120-random(40); }
