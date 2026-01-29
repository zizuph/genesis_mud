/* Standard Draconian Guards that patrol tantallon*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>

inherit M_FILE

#define NO_OF_TYPES 7
#define ANT_WEAPONS 5
#define ANT_ARMOURS 6

/*
 * Prototypes
 */
string d_short(int no);
string d_name(int no);
string d_long(int no);
string d_adj(int no);

void
create_krynn_monster()
{
    int i, j;
    string str;

    if (!IS_CLONE)
	return;

    j = random(NO_OF_TYPES);
 
    set_name("draco");
    set_race_name("draconian");
    set_living_name("draconian");

    set_short(d_short(j));
    set_long(BS(d_long(j), SL));
    if ((str = d_adj(j)) != "")
	set_adj(str);
    set_alignment(-(50 + random(j * 40)));
    set_knight_prestige(700 + j * 100);
    add_name(d_name(j));

    set_random_move(30);

    set_pick_up(30);

    set_act_time(3);
    add_act("screams");
    add_act("stare");
    add_act("emote shows you his claws.");
    add_act("say What are you doing here?");
    add_act(({"say Get lost!", "laugh"}));
    add_act("emote shows you the finger, or rather, his middle claw.");
    add_act("frown");
    add_act("grin");
    add_act("giggle");
    add_act("twiddle");
    set_cact_time(10);
    add_cact("say You really think you can defeat me?\n");
    add_cact("say Ahhh, now I can test my battle skill.\n");
    add_cact("say I didn't even feel that!\n");
    add_cact("say Is that all you can do?\n");
    add_cact("say Don't take it personally but I'll kill you.\n");
    add_cact("grin");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 20 + j * 4 + random(j * 5));
    set_skill(SS_DEFENCE, 20 + j * 7 + random(j * 5));
    set_skill(SS_WEP_AXE, 20 + j * 7);
    set_skill(SS_WEP_SWORD, 20 + j * 7);
    set_skill(SS_WEP_KNIFE, 30 + j * 7);

    for (i = 0; i < 7; i++)
        set_skill(i, 50 + j * 5);

    NEVERKNOWN;

    set_all_attack_unarmed(20 + j * 2, 10 + j * 2);
    set_all_hitloc_unarmed(16 + j * 2);


    set_alarm(1.0,0.0,"arm_me", j);
}

void
arm_me(int j)
{
    object arm, wep;
    int tmp;
    string arm_string, wep_string;

    arm_string = OBJ + "dr_";

    wep_string = OBJ + "dr_";

    seteuid(getuid(this_object()));

    tmp = (j + random(NO_OF_TYPES - 3)) / 2;
    if (tmp < 0)
        tmp = 0;
    if (tmp > ANT_WEAPONS)
    	tmp = ANT_WEAPONS - 1;

    wep = clone_object(wep_string +
		({ "knife", "spear", "stsword", "axe", "sword" })[tmp]);
    wep->move(this_object());

    tmp = (j + random(NO_OF_TYPES - 2)) / 2;
    if (tmp < 0)
    	tmp = 0;
    if (tmp > ANT_ARMOURS)
    	tmp = ANT_ARMOURS - 1;

    arm = clone_object(arm_string + 
		({ "helmet", "shield", "boots", "robe", "leggings",
		   "armour" })[tmp]);
    arm->move(this_object());

    command("wear armour");
    command("wield weapon");
}  

string
d_short(int no)
{
    string *draco_short;
  
    draco_short = ({
	"small draconian guard", "evil guard", "black draconian guardian",
	"draconian guard", "watching draconian", "black evil guard",
        "draconian lieutenant", "great draconian" });

    return draco_short[no];
}

string
d_long(int no)
{
    string *draco_long;

    draco_long = ({
	"A rather small one I would say, for a draconian of course.",
        "This one is evil, even for a draconian.",
        "The draconian stares back at you with deep black eyes.",
        "It's a bad looking draconian. You can see his wings sticking out " +
	"from behind.",
        "The draconians grins evilly and shows you his claws when you " +
	"approach.",
        "A very dark draconian, you feel that perhaps this one is more " +
	"evil than any other draconian guard in here.",
        "The lieutenant stands aside but he eyes you suspiciously",
        "This is one of the biggest and strongest draconians you have ever " +
	"seen" });

    return draco_long[no];
}

string
d_name(int no)
{
    string *draco_name;

    draco_name = ({ "guard", "guard", "guardian", "guard", "watcher", "guard",
	"lieutenant", "greatest" });

    return draco_name[no];
}

string
d_adj(int no)
{
    string *draco_name;

 
    draco_name = ({ "small", "evil", "black", "", "watching", "evil",
	"lieutenant", "great" });

    return draco_name[no];
}
