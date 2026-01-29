/*
 *
 * This is the ruling Troll of the trollshaws, its not agressive
 * but it is rather tough	- Sir Odin
 *
 */

inherit "/std/monster.c";

#include "rdefs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Shire/common/make_money.h"

#define RNAMES ({"Sgnoh","Bahh","Musha","Hallo"})

#define RLONG ({\
    "has got some dark red eyes, penetrating your mind. "+\
       "From the scars on his face you can see that he has been in a lot of fighting.\n",\
    "looks very powerful. you do not want to mess with him."+\
       "He looks kind of stupid just like all the trolls in this area.\n",\
    "is obviously not the one you should try to talk to. He looks "+\
       "big and powerful, the perfect trollsoldier!!.\n",\
    "is laughing at you, a minor snaga in his eyes.\n"})

#define RWEIGHT ({300,250,360,200})
#define RHEIGHT ({300,200,450,250})

#define RADJ ({ "red eyed","balded fierceful looking",\
		"awesome huge","pitful looking"})

/* str dex con int wis dis */
#define RSTAT ({\
		({ 78, 90, 120, 15, 20, 80 }), \
		({ 70, 60, 80, 20, 10, 50 }), \
		({ 100, 80, 115, 5, 7, 76 }), \
		({ 70, 100, 80, 3, 5, 60 }) })

#define SKUCOM ({ 70, 40, 80, 45 })
#define SKDEF  ({ 70, 60, 75, 50 })

int time_next;

create_monster()
{
    seteuid(getuid());
    TO->create_shaw_troll(random(4));
}

int myrand(int val)
{
    return val-val/4+random(val/2)+1;
}

void setup_skills();
void arm_me();


create_shaw_troll(int r)
{
    set_name(({RNAMES[r], "soldier","troll soldier","_shaw_troll_"}));
    set_pname("soldiers");
    set_short(RADJ[r] + "troll soldier");
    set_pshort("troll soldier");
    set_adj(RADJ[r]);
    set_race_name("troll");
    set_long(
	"This is one of the evil trolls created by Morgoth, and ever since "
	+"his death they have been wandering about in this forest. They  "
	+"are close relatives with the trolls in Hollin and Khazad-dum,  "
	+"but because of their stupidness they still have not found their "
	+"way into Khazad-dum. \n"
	+"This specific creature, " + RLONG[r]);

	add_prop(CONT_I_WEIGHT, RWEIGHT[r] * 1000);
	add_prop(CONT_I_HEIGHT, RHEIGHT[r]);

	set_stats(RSTAT[r]);

	setup_skills();

   MAKE_MONEY;
	set_skill(SS_UNARM_COMBAT, myrand(SKUCOM[r]));
	set_skill(SS_WEP_CLUB,	   myrand(SKUCOM[r]));
	set_skill(SS_WEP_SWORD,    myrand(SKUCOM[r]));
	set_skill(SS_DEFENCE,	   myrand(SKDEF[r]));
	set_skill(SS_PARRY,	   myrand(SKDEF[r]));
	set_pick_up(80);

	set_aggressive(1);
	set_attack_chance(65);

	set_alignment(-400 - random(200));


	set_act_time(5);
	add_act("sigh evil");
	add_act("emote headbutts you right in your nose!");
	add_act("emote Hisses: Hr du st nan? Nazgul urk burza! Uruk-Hai, din SNAGA!!");
	add_act("emote Screams: Glfs ike te me!! Dn Snaga!!!");
	add_act("swear");
	add_act("Hisses: Hr du st Bert?");
	add_act("emote screams: Bolg kr e du, AAAAARRRGH!!!!");
	add_act("shout GRooomsss smooooocksssaaaaalaa");
	add_act("emote prepares his weapon for battle.");


	set_cact_time(4);
	add_cact("scream");
	add_cact("emote shouts for his friends!");
	add_cact("emote looks at you and shouts: SNAGA OBEY OR DIE");
	add_cact("peer");
	add_cact("shout here coms dinr!!!");
	add_cact("emote screams: Stk av SNAGA!");
	add_cact("sneeze");
	add_cact("emote Snarls: Ztn d e stg!!");

   set_alarm(1.0,0.0, &arm_me());

	set_m_in("arrives searching for humans to eat.");
	set_m_out("leaves peering evilly at you");

}


void
setup_skills()
{
    mapping allskills = SS_SKILL_DESC;
    int *skills = m_indexes(allskills);
    int i;

    for(i=0;i<sizeof(skills);i++)
	set_skill(skills[i], myrand(query_stat(allskills[skills[i]][2]))/2);

}


arm_me()
{
    string wep = ({"trollmaul", "trollsword", "trollclub" })[random(3)];
    clone_object(D_WEAPON+wep)->move(TO);
    command("wield all");

}
