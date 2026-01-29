inherit "/std/monster";

#include "rdefs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Shire/common/defs.h"

void arm_me(int i);

#define RNAMES ({ "tawanka", "grimpesta", "ragabast", "fjortis",\
		  "trakamash", "trashinku", "snytarakk", "peisatull",\
		  "wendiko", "heptasite", "syfilis", "grimface" })

#define RLONG ({ \
    "This is a stout little fellow with fierce green eyes.",\
    "He looks like a stubborn, grim looking small troll.",\
    "He looks like a furry and wild little creature.",\
    "This one looks like a child when compared to the others.",\
    "His feet look really odd! They are definitely wider than normal.",\
    "He smells like trash. Honestly!",\
    "Yukk, this one has green snot hanging out of his nose!",\
    "This fellow looks funny with a grinning smile.",\
    "He! He looks funny with those glasses on.",\
    "This one is just disgusting smelling.",\
    "Poor small troll. He is bandaged around his loin.",\
    "Geez, he looks so grim you almost faint."\
})

#define RADJ ({ \
    "green-eyed, stout",\
    "grim-looking, stubborn",\
    "wild, furry",\
    "small, childish",\
    "flatfooted, odd-looking",\
    "bad-smelling, trashy-looking",\
    "sneezing, snotty",\
    "grinning, funny-looking",\
    "serious, glasses-wearing",\
    "disgusting, smelling",\
    "injured, ugly-looking",\
    "grim, violent",\
})

#define RCACTS\
({\
    ({	"shout Come on fellas! Let's waste that sucker!!",\
	"grin","laugh", "say This is fun! That's a looser!" }),\
    ({	"shout Yeah! That's a DEAD thing!", "shout I *like* this killing!",\
	"emote dodges upon you with a grinning laugh!" }),\
    ({	"shout Dream on babes! I'm looking COOL!", "shout Watch this fellas!",\
	"emote jumps upon your face and bites your nose!" }),\
    ({	"cry", "say You can't do that!", "emote bites his long nails." }),\
    ({	"emote steps on his large foot and falls..", "scream",\
	"emote makes a perfect roundhouse kick on you.", "laugh" }),\
    ({	"fart", "puke", "cackle" }),\
    ({	"sneeze", "emote pulls out a huge snot and throws it into your face!!",\
	"emote laughs hysterically.", "cough loudly" }),\
    ({	"grin", "emote makes a double salto mortale and hits you on your back!",\
	"spit" }),\
    ({	"emote sings a merry song.", "emote pushes his glasses into place again",\
	"whine", "say I wunder if the stars are correctly in motion." }),\
    ({	"fart", "emote puts his finger in his throut, and you have puke all over you!",\
	"emote bends down and shits on the floor" }),\
    ({	"sulk", "say Come on guys, I am injured!", "pout" }),\
    ({	"emote grabs something and with a blindingly fast move he throws sand into your eyes!",\
	"emote tumbles across the ground and sweeps you as he goes!!",\
	"emote thunders in a large voice: LOOSER!!!!",\
	"emote tells the others: Come on! Let's waste this sucker!!!",\
	"emote shouts with death in his eyes: VICTORY!!",\
	"laugh", "grin" })\
})

#define RWEAP ({ "spear", "axe", "ss", "knife", "axe", "club",\
		 "knife", "club", "ss", "spear", "knife", "waraxe" })

#define WEPMAP ([ \
    "spear": ({ "spear", "pointed", 10, 25, W_JAVELIN, W_BOTH, W_IMPALE,\
		"This is a pointed spear." }),\
    "axe":   ({ "axe", "small", 20, 26, W_AXE, W_ANYH, W_SLASH | W_BLUDGEON,\
		"This is a small axe." }),\
    "ss":    ({ "sword", "short", 20, 17, W_SWORD, W_ANYH, W_SLASH,\
		"This is a short sword." }),\
    "knife": ({ "knife", "curved", 10, 12, W_KNIFE, W_ANYH, W_SLASH | W_IMPALE,\
		"This is a curved knife." }),\
    "club":  ({ "club", "spiked", 20, 27, W_CLUB, W_ANYH, W_IMPALE | W_BLUDGEON,\
		"This is a small, but heavy club with nasty spikes on its end." }),\
    "waraxe":({ "waraxe", "large", 20, 45, W_AXE, W_BOTH, W_SLASH | W_BLUDGEON,\
		"This is a rather large waraxe with blood in its edges." })\
])

/* Str, Dex, Con, Int, Wis, Dis */

#define RSTAT ({\
    ({ 30, 30, 15, 40, 50, 50 }),\
    ({ 40, 10, 20, 10, 20, 90 }),\
    ({ 50, 40, 25,  5,	5, 10 }),\
    ({ 15,  3, 10,  2,	4,  6 }),\
    ({ 31,  7, 30, 20, 20, 60 }),\
    ({ 25, 15, 15, 15, 15, 15 }),\
    ({ 15, 16,	2,  5, 70, 30 }),\
    ({ 60,  4, 26,  5, 10, 60 }),\
    ({ 20, 40, 10, 80, 70, 20 }),\
    ({ 60, 50, 50,  4,	5, 50 }),\
    ({ 18, 40,	8, 20, 20, 30 }),\
    ({ 90, 50, 70,  1,	1, 10 })\
})


arm_me(int i)
{
    object weapon = clone_object("/std/weapon");
    mixed *entry  = WEPMAP[RWEAP[i]];
    switch(RWEAP[i]) {
	case "spear": set_skill(SS_WEP_JAVELIN, RSTAT[i][0]); break;
	case "axe"  : set_skill(SS_WEP_AXE, RSTAT[i][0]); break;
	case "ss"   : set_skill(SS_WEP_SWORD, RSTAT[i][1]); break;
	case "knife": set_skill(SS_WEP_KNIFE, RSTAT[i][1]); break;
	case "club" : set_skill(SS_WEP_CLUB, RSTAT[i][0]); break;
	case "waraxe":set_skill(SS_WEP_AXE, RSTAT[i][0]); break;
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
  MAKE_MONEY;
}

int my_num;
int query_my_num() { return my_num; }

create_me(int i)
{
    int j;
    string *my_acts;
    my_num = i;
    set_name(RNAMES[i]);
    set_adj(explode(RADJ[i],", "));
    set_race_name("troll");
    set_short(implode(explode(RADJ[i],", ")," ")+" small troll");
    set_long(
	RLONG[i]+" "+
	"He is a small troll of incredibly small stature, you'd say that "+
	"he is about 3 feet tall. But you should not be amazed if this "+
	"is a mean little fella'..\n"+
	"Small trolls are small, but strong monsters whose only purpose "+
	"in life is to line their own pockets. They prefer to attack in "+
	"packs, but only when they have superior numbers.\n"
    );
    add_prop(CONT_I_HEIGHT, 60 + random(60));
    add_prop(CONT_I_WEIGHT, (20 + random(20)*1000));
    set_stats(RSTAT[i]);
    set_hp(10000);
    set_skill(SS_UNARM_COMBAT, random(15)+5);
    set_skill(SS_BLIND_COMBAT, 50+random(20));
    set_skill(SS_PARRY, 10+random(RSTAT[i][1]/2));
    set_skill(SS_DEFENCE, 20+random(10));

    set_cact_time(2);
    my_acts = RCACTS[i];
    for(j=0;j<sizeof(my_acts);j++)
	add_cact(my_acts[j]);

    set_alignment(-200-random(151));
    set_aggressive(1);
    set_attack_chance(100);
    add_prop(NPC_I_NO_LOOKS, 1);
   set_alarm(1.0,0.0, &arm_me(i));
}

int query_knight_prestige() { return 200 + random(199); }
