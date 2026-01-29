// copied to this dir from /d/Krynn/solamn/hctower/spur/npc/archer_base.c 
// Knight Archers /d/Krynn/solamn/vkeep/mnstrs/archer_base.c
// creator(s):   Grace Aug 94
// last update:  
// purpose:      Add a little variety to the npcs in the area.            
// note:         Most of the code is taken from the vkeep guards
//               which Aridor and I modified earlier this year.
// bug(s):
// to-do:        

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include "../local.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit M_FILE

int sublevel, level;
string subtitle, title; 
string randadj();
string randadj2();
string do_align_check();

object quiver;

string
set_my_title()                       
{
    if (!level)
    {
	level = random(2) + 2;
	sublevel = random(5) + 3;
    }
    if (level == 3)
    {
	subtitle = CROWN_TITLES[sublevel];
	return "Knight of the Crown";
    }
    else
    {
	subtitle = SQUIRE_TITLES[sublevel];
	return "Squire of Solamnia";
    }
}              


void
create_krynn_monster()
{
    int i;

    set_name("archer");
    add_name(({"knight","squire","human","archer"}));
    set_pname("knight archers");
    add_pname(({"knights","squires","humans"}));
    // set_short("knight archer");
    // set_pshort("knight archers");
    set_race_name("archer");
    set_adj(randadj());
    set_adj(randadj2());
    set_extra_long("He wears a quiver filled with arrows on his back.\n");
    LONG("This is a dedicated " + set_my_title() + ". He takes his "+
      "assignment to defend the Knights' Spur very seriously.\n" +
      "He is wearing the medal of the Solamnian "+
      "Knighthood, and he is " + subtitle + ".\n"); 

    for (i = 0; i < 5; i++)
	set_base_stat(i, 70); 
    set_base_stat(SS_DIS, 85+random(5));

    set_alignment(500+random(100));
    set_appearance(80);
    set_knight_prestige(-100);
    set_aggressive("@@do_align_check@@");  // will attack if align < 0

    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_AWARENESS, 45);
    set_skill(SS_2H_COMBAT, 75); 

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1); 
    add_prop(LIVE_O_ENEMY_CLING, 1);   // does this work??


    set_cchat_time(30+random(10));
    add_cchat("To die is to fulfill my destiny.");
    add_cchat("Do you think you can attack us with impunity?");
    add_cchat("You're no better than a draconian!");
    add_cchat("Who taught you to fight? Your granny?");
    add_cchat("Est Sularus Oth Mithas!");
    add_cchat("Bows are completely useless in these close quarters.");

    set_act_time(10+random(10));
    add_act("@@do_rescue");
    add_act("say I heard that the Blue Army is in the Plains and the Red Army "+
      "is camped near Crystalmir lake.");
    add_act("emote smiles just like if Nick had taught him.");
    add_act("say I heard the same.");
    add_act("@@do_rescue");
    add_act("say Keep those arrows cocked. It is our responsibility to take " +
      "out anyone who gets past those guarding the gates.");
    add_act("emote bursts into hearty, infectious laughter.");
    add_act("say One day I hope to earn a suit of Solamnic Armour.");
    add_act("@@do_rescue");
    add_act("say Gunthar is a wise man and a hard task-master.");
    add_act("say On my next leave I'm planning to stay at the Silver Dragon Inn " +
      "in Palanthas. I'm going to have myself a shot of Leiden's Kusten"+
      "nebel if I have to make it myself!");
    add_act("emote bows to you with the old-fashioned courtesy of a " +
      "Solamnic Knight.");
    add_act("say The quests for the Sword and Rose orders are dangerous. Quite "+
      "a few Knights have died attempting them.");
    add_act("@@do_rescue");   
    add_act("emote begins telling a joke in old Solamnian.");   

    set_cact_time(10+random(5));
    add_cact("@@do_rescue");
    add_cact("emote cries:  By the Measure, now and always, let swords " +
      "fall as swords will fall!");
    add_cact("emote sings an ancient song of war.");
    add_cact("emote tries to shoot at you with his bow, but fails.");


    MONEY_MAKE_SC(random(15) + 10)->move(TO);

    if (IS_CLONE)
	set_alarm(1.0,0.0,"arm_me"); 

}

void
arm_me()
{
    seteuid(geteuid(this_object()));
    quiver=clone_object(SOBJ + "quiver")->move(TO);
    clone_object(SOBJ + "bow")->move(TO);
    clone_object(SOBJ + "arrow")->move(quiver);
    clone_object(SOBJ + "arrow")->move(quiver);
    clone_object(SOBJ + "arrow")->move(quiver);
    clone_object("/d/Krynn/solamn/vin/armour/s_armour")->move(TO);
    clone_object("/d/Krynn/solamn/vin/weapon/s_shortsword")->move(TO);
    command("wield sword");
    command("wear armours");
}

string
randadj()
{
    string *randadjs;
    randadjs = ({"strong", "tall", "brave", "gallant", "valiant", "tired",
      "dedicated", "serious", "smiling", "hopeful", "muscular", "young", 
      "experienced", "amused", "thoughtful", "clean-shaven", "kind"});                
    return randadjs[random(sizeof(randadjs))];
}

string
randadj2()
{
    string *randadjs;
    randadjs = ({"loyal", "obedient", "self-righteous", "cynical", "wise",
      "heroic", "honourable", "virtuous", "generous", "courageous",
      "compassionate", "protective", "likeable", "truthful", "just"});                
    return randadjs[random(sizeof(randadjs))];
}

string
do_rescue()    // I edited this...question is, did I do it correctly?
{
    /* rescue a fellow knight who is currently under attack */
    object *whos = all_inventory(E(TO));
    object ene;
    int i;
    for(i = 0;i<sizeof(whos);i++) 
    {
	ene = whos[i]->query_enemy(0);
	if (ene && ene->id("archer") && ene != TO)
	{
	    if (random(5))
	    {   
		attack_object(whos[i]);
		whos[i]->attack_object(TO);
		return "";
	    }
	}
    }
    return "";
}                                


/* these guards have the knights special attacks,
* bash and ckick, too!
*/

int
do_bash(object enemy)
{
    object  me = this_object();
    mixed *hitresult;
    string  how;

    if (E(TO) == E(enemy))
    {
	say(QCTNAME(me) + " looks at " + QTNAME(enemy) + " with murder " +
	  "in " + me->query_possessive() + " eyes.\n", enemy);
	enemy->catch_msg(QCTNAME(TO) + " looks at you with murder in " +
	  TO->query_possessive() + " eyes.\n");

	hitresult = enemy->hit_me(80 + random(20), W_BLUDGEON, me, -1);

	enemy->catch_msg(QCTNAME(me)+" sends you sprawling with" +
	  " a wonderful bash!\n");
	say(QCTNAME(me)+" sends "+QTNAME(enemy)+" sprawling with" +
	  " a wonderful bash!\n",enemy);

	if(enemy->query_hp() <=0)   

	    enemy->do_die(me);
	return 1;
    }
}

int
do_ckick(object enemy)
{
    object  me = this_object();
    mixed *hitresult;
    string  how;

    if (E(TO) == E(enemy))
    {
	say(QCTNAME(me) + " looks at " + QTNAME(enemy) + " with rage " +
	  "in " + me->query_possessive() + " face.\n", enemy);
	enemy->catch_msg(QCTNAME(TO) + " looks at you with rage in " +
	  TO->query_possessive() + " face.\n");

	hitresult = enemy->hit_me(20 + random(80), W_BLUDGEON, me, -1);

	enemy->catch_msg(QCTNAME(me)+" kicks you hard! You can hear" +
	  " your bones crunch!\n");
	say(QCTNAME(me)+" kicks "+QTNAME(enemy)+" with a bonecrushing" +
	  " sound!\n",enemy);

	if(enemy->query_hp() <=0)
	    enemy->do_die(me);
	return 1;
    }
}
int
special_attack(object enemy)
{
    int i;

    if(random(4))
	return 0;

    switch(random(2))
    {
    case 0:
	do_bash(enemy);
	break;
    case 1:
	do_ckick(enemy);   
	break;
    }
    return 0;
}

int
query_knight_level() { set_my_title(); return level; }

int
query_knight_sublevel() { return sublevel; }       

/*
* Function name: attacked_by
* Description:   This function is called when somebody attacks this object
* Arguments:     ob - The attacker
*/
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
	arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
* Function name: notify_ob_attacked_me
   * Description:   This is called when someone attacks a team member of mine
* Arguments:     friend - My team mate
*                attacker - The attacker
*/
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
	return;

    if (random(10))
	set_alarm(itof(random(5)),0.0,"help_friend",attacker);
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say You must be a fool to attack us here!");
	command("kill " + ob->query_real_name());
    }
}   


int
do_align_check()
{
    if (TP->query_npc())
	return 0;
    if (TP->query_alignment() > 0)
	return 0;
    if (TP->query_average_stat() < 30)
	return 0;
    else
    {
	set_alarm(1.0,0.0,"command","say Prepare to die, you evil creature!");
	/*command("kill " + TP->query_real_name()); this is done from init_attack */
    }
    return 1;
}

/*
 * Function name: init_attack
 * Description:   Called from init_living() i monster.c
 */
public void
init_attack()
{
    int i = check_call(monster_aggressive);
    if ((!i) || (this_player()->query_npc()))
	return;

    if ((monster_attack_chance == 0) || (random(100) < monster_attack_chance))
	set_alarm(2.0,0.0,"aggressive_attack", this_player());
}
