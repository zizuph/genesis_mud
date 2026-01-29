// Street woman #1 (/d/Avenir/common/bazaar/NPCS/wom1.c)
// creator(s):   Tepisch&Grace
// last update:  Tepisch Sept 1994, 
//               Ilyian May 1995(fixed special, added stuff)
//               Glinda may-95(added asks and skills)
//               Cirion, May 30 1996: Fixed bugs due to new mudlib
//               Denis, May'00: Fixed answer_question functionality
//                              with book_wom.c file.
// purpose:      women to make part of the crowd, adds ambiance to bazaar
//
// note:
// bug(s):
// to-do:        make clothing and baskets/parcels, etc

inherit "/d/Avenir/inherit/monster.c";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/include/guilds.h"

#include <language.h>
#include <money.h>

string randadj();
string randrace();
string randdesc();

void
create_monster()
{
    if (!IS_CLONE)
	return;

    ::create_monster();

    set_name("female");
    add_name(({"hag", "slave", "crone", "adolescent", "peasant"}));
    set_race_name(randrace());
    set_gender(G_FEMALE);
    add_adj(randadj());
	set_short(randadj() +" "+ randdesc());
    set_long("She is making her way through the crowd, intent "+
      "upon some errand.\n");

    set_stats(({ 40+random(20), 60+random(20), 30+random(60),
	50+random(10), 30+random(10), 40+random(10) }));
    set_skill(SS_UNARM_COMBAT,30+random(45));
    set_skill(SS_AWARENESS,40);
    set_skill(SS_WEP_CLUB,40+random(30));
    set_skill(SS_DEFENCE,40+random(30));
    set_skill(SS_BLIND_COMBAT,40+random(30));
    set_all_hitloc_unarmed(10+random(30));
    set_skill(SS_WEP_CLUB, 20 + random (30));
    set_skill(SS_DEFENCE, 30 + random (45));
    set_skill(SS_AWARENESS, 25);
    set_skill(SS_BLIND_COMBAT, 10 );

    add_prop("_live_m_attack_thief", "thief_fun");
    NEVERKNOWN;

    set_alignment(0);  //chances are she is a little good
    set_pick_up(1);
    set_random_move(20, 0);
    set_restrain_path("/d/Avenir/common/bazaar/");
    set_monster_home("/d/Avenir/common/bazaar/extr/str18");

    set_act_time(10+random(15));
    add_act("emote sighs unhappily.");
    add_act("emote stands on tip-toes and looks over your head.");
    add_act("emote shifts her load from one hip to the other.");
    add_act("emote eyes you warily.");
    add_act("emote tries to move out of your way.");
    add_act("emote looks wistfully up at the Source.");
    add_act(({"emote smiles excitedly.","emote asks you: Do you know"+
	" if the Punisher has anyone in the pillory?"}));
    add_act("emote whispers: Keep an eye out for those pesky brats, they"+
      " pick pockets.");
    add_act("emote glances at you and quickly looks away.");
    add_act("swing stick");
    set_cact_time(15+random(5));
    add_cact("emote sobs: By the Light of the Source, why are "+
      "you killing me?");
    add_cact("emote looks like she is praying.");
    add_cact(({"say Isn't this just like you surface-dwellers?" +
	" Killing defenseless people!", "emote blows spittle "+
	"into your face"}));
    add_cact("say My master beat me once already today!");
    add_cact("say bursts into tears.");
    add_cact("shout Please don't kill me! I have children to raise!");

    add_ask(({"library"}),"say The library is up north, right across " +
      "the street from the bank.",1);
    add_ask(({"bank"}),"say The bank is up north, right across " +
      "the street from the library.",1);
    add_ask(({"postoffice","post"}),"say The postoffice is up north, " +
      "right across the street from the smith.",1);
    add_ask(({"smith","forge"}),"say The smith is up north, " +
      "right across the street from the postoffice.",1);
    add_ask(({"inn"}),"say The inn is up in the northwest.",1);
    add_ask(({"pier"}),"say The pier is up northwest.",1);
    add_ask(({"guild"}),"say The guild is on the west side of the bazaar.",1);
    add_ask(({"pub"}),"say The pub is on the east side of the bazaar.",1);
    add_ask(({"garden","park"}),"say Yes there is a park south of the bazaar.",1);
    set_default_answer("");
}
void
arm_me()
{
    seteuid(geteuid(this_object()));
    refresh_living();

    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_CC(random(40))->move(this_object());

    clone_object(BAZAAR + "Obj/wield/pclub")->move(TO);
    command("wield all");

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
    command("wear all");
}
void equip_me() {  arm_me();  }
/*
 * Function name: answer_question
 * Description:   This function is called after a short delay when this mobile
 *                wants to react to a question
 * Arguments:     An array ({ string msg, int cmd })
 */
void
answer_question(string msg, int cmd)
{
    if (msg == "" || msg == 0)
        command("shrug");
    else
	::answer_question(msg, cmd);
}

string
randadj()
{
    string *randadj;
    randadj = ({"little", "dark-eyed", "tall", "sad", "busy", "tired",
      "slender", "wise", "angry", "dirty", "voluptuous", "willowy",
      "bruised", "concerned", "frightened", "secretive", "plump",
      "wide-eyed", "innocent", "wart-nosed", "deformed"});
    return randadj[random(sizeof(randadj))];
}

string
randrace()
{
    string *randrace;
    randrace = ({"human", "dwarf", "gnome", "halfling"});
    return randrace[random(sizeof(randrace))];
}

string
randdesc()
{
    string *randdesc;
    randdesc = ({"hag", "slave", "crone", "adolescent", "peasant"});
    return randdesc[random(sizeof(randdesc))];
}

int
special_attack(object victim)
{
    int scrat;
    string who;
    object me = this_object();

    if(random(3)) return 0; /* normal attack */

    who = lower_case(victim->query_name());
    scrat = random(2);

    if(scrat == 0)
    {
	victim->catch_msg(QCTNAME(me)+
	  " scratches your face " +
	  "with her fingernails! Ouch!\n");
	tell_room(environment(victim), QCTNAME(me)+
	  " scratches " + QTNAME(victim) + " in the face with "+
	  "her fingernails!\n", victim);
	victim->heal_hp(-15);
	me->command("say Right in the face!");
	me->command("cackle");
    }
    if(scrat == 1)
    {

	victim->catch_msg(QCTNAME(me)+ " scratches your forearm "+
	  "with her fingernails! Ouch!\n");
	tell_room(environment(victim), QCTNAME(me)+
	  " scratches " + QCTNAME(victim) + " on the forearm "+
	  "with her fingernails!\n", victim);
	victim->heal_hp(-10);
	me->command("laugh insan");
    }

    return 1;
}

thief_fun(object thief, object victim, object ob)
{
    set_alarm(1.8, 0.0, &command("slap "+
	thief->query_real_name()));
    set_alarm(1.0, 0.0, &command("shout "+
	"You worthless thief!"));
}

void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(10);

    if (!present(tp, environment(TO)))
	return;

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
	if (i == 1)           
	    command("say to "+ tp->query_real_name() +
	      " Greetings, noble one.");
	if (i == 4)
	    command("curtsey deep "+ tp->query_real_name());
	if (i == 8)
	    command("say to "+ tp->query_real_name() +" Let me "+
	      "move out of your way, that my unworthy feet do "+
	      "not soil your path.");
	return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
	if (i == 0)
	    command("smile jeal "+ tp->query_real_name());
	if (i == 3)
	    command("say to "+ tp->query_real_name() +
	      " I envy you the teachings of Qalita!");
	if (i == 6)
	    command("say to "+ tp->query_real_name() +
	      " Would that I had your beauty and "+
	      "grace, fair one.");
	return;
    }       
    else
    {
	if (i == 2)
	    command("smile contag "+ tp->query_real_name());
	if (i == 5)
	    command("curtsey respect "+ tp->query_real_name());
	if (i == 9)
	    command("back "+ tp->query_real_name());
	return;
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
	set_alarm(2.0, 0.0, &check_meet(TP));
	return;
    }
}  
