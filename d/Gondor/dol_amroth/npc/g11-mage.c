/* -*- Mode: C -*-
 *
 * npc/g11-mage.c
 *
 * By Skippern 20(c)02
 *
 * This is the lord of the mansion G-11 in Dol Amroth.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";
inherit "/lib/unique";

#include "../defs.h"
#include <const.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>

#define ING_ARR_1   ({ "apple", "bread", "cake", "pie" })
#define ING_ARR_2   ({ "whiskey", "ale", "water", "wine" })
#define ING_ARR_3   ({ "feather" })
#define ING_ARR_4   ({ "rock", "pebble" })
#define ING_ARR_5   ({ "knife", "leather jacket", "helmet", \
                        "leather trousers", "leather glove" })
#define ING_ARR_6   ({ "shirt", "pants", "pumps" })

/* Global variables */
static object wep, tower;

/* Prototypes */
public string         help_me();
       string         query_is_behind(string str);

/* Code */
void set_tower(object o) { tower = o; }

public void
create_dunadan()
{
    FIX_EUID;

    set_living_name("halvgorn");
    set_name("halvgorn");
    set_adj("old");
    add_adj("magical");
    add_name( ({ "dunadan", "master", "sir", "lord", "lore master", "loremaster",
		     "halvgorn_the_wise" }) );
    set_race_name("human");
    set_gender(G_MALE);
    set_title("Master of Lore");
    set_dunedain_house("Borlad");
    set_long("This highborn man is clearly a lord of the dunadan. This wise man have obviously " +
		"dedicated his life in the study of the lores. His eyes are weary after many a night over " +
		"the books.\n");

    default_config_npc(85);
    set_base_stat(SS_INT, 95);
    set_base_stat(SS_WIS, 100);
    set_skill(SS_SPELLCRAFT, 150);
    set_skill(SS_WEP_KNIFE, 75);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_DEFENCE, 45);
    set_skill(SS_PARRY, 20);
    set_skill(SS_BLIND_COMBAT, 35);
    set_skill(SS_UNARM_COMBAT, 15);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_TRADING, 75);

    set_whimpy(100 * query_hp() / query_max_hp() < 95);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    add_cmdsoul("/d/Gondor/common/dunedain/dunedain_soul");

    add_ask( ({ "task", "job", "quest", "help" }), &help_me(), 0);

    set_alignment(random(350) - 50);

    set_chat_time(200);
    add_chat("I wish I had any artifacts to aid me on my task.");
    add_chat("How can I consentrate on my work with people constantly " +
	     "bothering me?");
    add_chat("If the guards still was around, I would call for somebody " +
	     "to throw you out of here.");
	add_chat("If only one could tame lightning, that would be something.");
	add_chat("The war is really weighing down on our city.");

    set_act_time(75);
    add_act("ponder");
    add_act("glitter");
    add_act("gleam");
    add_act("silence");
    add_act("dpace");

    set_cact_time(10);

    clone_object(DOL_OBJ+"arm/mage-robe")->move(this_object());
    command("wear all");

    //    tower = environment(this_object());
    enable_reset();
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings "+capitalize(name));
    command("introduce me to "+name);
    command("grumble");
    command("say If you have nothing important to me please leave, I am " +
	    "a busy man.");
}

public void
add_introduced(string name)
{
    object    pl;

    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr, o;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
    if (!objectp(wep))
    {
	wep = clone_unique(DOL_OBJ+"wep/mage-pole", 3, 
			 DOL_OBJ+"wep/mage-dagger");
	wep->move(this_object());
	command("emote does a magical gesture and summons a "+
		wep->short()+".");
	command("wield all");
	if (wep->id("dagger"))
	{
	    add_cact("fire dagger");
	    add_cact("freeze dagger");
	}
	else
	{
	    add_cact("emote does something with the quarterstaff.");
	}
    }
    if (tower->no_of_gargoyls() > 0)
    {
	o = clone_object(DOL_NPC + "g11-gargoyl");
	tell_room(tower, "A massive gargoyl flaps its wings and flys down " +
	    "from its pedistall high up on the wall.\n", o);
	o->set_Mage(this_object());
	o->set_Tower(tower);
	tower->remove_g();
	o->move(environment(this_object()));
	o->command("assist halvgorn");
	set_alarm(4.0, 0.0, &query_is_behind(DOL_NPC+"g11-gargoyl"));
    }
}

void
reset_monster()
{
    if (query_enemy(-1) && objectp(wep))
    {
	command("emote does a magical gestur and returns his " + wep->short() +
		".");
	wep->remove_object();
	wep = 0;
    }
}

void
Gargoyl_Death()
{
    command("emote screams: Nooooooooo!");
}

void
mix_ingr(object ob, int part)
{
    string dummy;

    dummy = ob->short();

    switch(part)
    {
    case 1:
	command("emote takes the "+dummy+" and drops it into a cooking " +
		"put containing some strange green liquid substance.");
	break;
    case 2:
	command("emote pours the "+dummy+" over some strange green liquid " +
		"substance while mumbling some strange words.");
	break;
    case 3:
	command("emote tries to drop the "+dummy+" into the pot, but the " +
		dummy+" stays float in the mist over the pot.");
	command("grumble");
	command("emote shouts some harsh words at the "+dummy+".\n" +
		"The "+dummy+" suddenly drops into the pot.");
	break;
    case 4:
	command("emote dips the "+dummy+" into the pot and then hurls it " +
		"out the window.\nYou notice the "+dummy+" explodes into a " +
		"red, green and blue mist.");
	break;
    case 5:
	command("emote stores the "+dummy+" in a small box on a shelf.");
	command("say I will need it real soon.");
	break;
    case 6:
	command("emote drops the "+dummy+" into the pot, and you hear a " +
		"load whining sound.");
	command("emote gets a look of power in his eyes and laughs: Moahaha!");
	command("dsay I did it!");
	break;
    }
}

void
new_part(object tp, object token)
{
    string ingr, ingrs, wanted = token->query_ingr();
    int    part, i;

    i = random(2);
    if (i ==  0)
    {
	command("say Ah, you found the " + wanted + ". Good.");
	command("smile");
    }
    else
	command("say Ah, the "+wanted+".");


    if (token->query_part() == 6)
    {
	command("say I think that was it.");
	command("nod sol");
	token->give_reward(tp, 3000);
        token->remove_object();
	command("say Thanks for your help.");
	return;
    }
    else
    {
	part = token->query_part() + 1;
	switch(part)
	{
	case 2:
	    ingr = one_of_list(ING_ARR_2);
	    break;
	case 3:
            ingr = one_of_list(ING_ARR_3);
            break;
	case 4:
            ingr = one_of_list(ING_ARR_4);
            break;
	case 5:
            ingr = one_of_list(ING_ARR_5);
            break;
	case 6:
            ingr = one_of_list(ING_ARR_6);
            break;
	}

	if (ingr == "water")
	    ingrs = "glass of "+ingr;
	else if (ingr == "wine")
	    ingrs = "bottle of "+ingr;
	else if (ingr == "pants" || ingr == "pumps")
	    ingrs = "pair of "+ingr;
	else
	    ingrs = ingr;

	switch(random(4))
	{
	case 0:
	    command("say Can you bring me " + LANG_ADDART(ingrs) + "?");
	    break;
	case 1:
	    command("hmm");
	    command("say I think I need " + LANG_ADDART(ingrs) + ".");
	    break;
	case 2:
	    command("say It would be nice if you could bring me " +
		    LANG_ADDART(ingrs) +".");
	default:
	    command("say " + capitalize(LANG_ADDART(ingrs)) + " would be " +
		    "nice.");
	    break;
	}

	token->set_part(part);
	token->set_ingr(ingr);
    }
}

/*
 * Function name:    enter_inv
 * Description  :    mask parent
 * Arguments    :    object ob -- the entering object
 *                   object from -- source
 */
public void
enter_inv(object ob, object from)
{
    object     token;
    int        part = token->query_part();

    if (objectp(from))
        token = present("I_do_quest_token.c", from);

    ::enter_inv(ob, from);

    if (token->query_task() == DOL_Q_MAGE_QUEST)
    {
	string wanted = token->query_ingr();
	if (token->query_ingr() == wanted)
	{
	    command("say Thank you "+ capitalize(from->query_name()) + ".");

	    switch(wanted)
	    {
	    case "apple":
	    case "bread":
	    case "cake":
	    case "pie":
		if (ob->id(wanted) && function_exists("create_food", ob))
		{
		    new_part(from, token);
		    mix_ingr(ob, part);
		}
		break;
	    case "ale":
	    case "water":
	    case "wine":
	    case "whiskey":
		if (ob->id(wanted) && function_exists("create_drink", ob))
                {
                    new_part(from, token);
                    mix_ingr(ob, part);
                }
		break;
	    case "pebble":
	    case "feather":
	    case "rock":
                if (ob->id(wanted) && function_exists("create_object", ob))
                {
                    new_part(from, token);
                    mix_ingr(ob, part);
                }
		break;
		case "knife":
                if (ob->id(wanted) && function_exists("create_weapon", ob))
                {
                    new_part(from, token);
                    mix_ingr(ob, part);
                }
		break;
	    case "helmet":
	    case "leather jacket":
	    case "leather glove":
	    case "leather trousers":
	        if (ob->id(wanted) && function_exists("create_armour", ob))
                {
                    new_part(from, token);
                    mix_ingr(ob, part);
                }
		break;
	    case "pants":
	    case "pumps":
	    case "shirt":
                if (ob->id(wanted) && function_exists("set_looseness", ob))
                {
                    new_part(from, token);
                    mix_ingr(ob, part);
                }
		break;
	    case "rope":
		if (ob->id(wanted) && function_exists("create_rope", ob))
                {
                    new_part(from, token);
                    mix_ingr(ob, part);
                }
		break;
	    }

	    if (objectp(ob))
		ob->remove_object();
	    else
		log_file("DolAmrothError", "ERROR: Cannot destruct ob ("+
			 ctime(time())+")\n");
	    return;
	}
    }
    
    command("say I am not interested in your "+ob->query_short()+".");
    command("give "+ob->query_name()+" to "+from->query_name());
}

/*
 * Give you help, I know
 */
public string
help_me()
{
    object tp = this_player();
    string ingr, ingrs, name = tp->query_name();
    object token;

    if (present("I_do_quest_token.c", tp))
    {
        command("say I have no tasks for you now.\n");
        return "";
    }

    ingr = one_of_list(ING_ARR_1);

    if (ingr == "bread")
      ingrs = "piece of "+ingr;
    else
      ingrs = ingr;

    command("say Ah, you want to help me?");
    command("say Good, just what I needed.");
    command("say I am researching a spell, and I need certain " +
	    "objects to find the solution.");

    command("think");
    command("say First I need you to find me " + LANG_ADDART(ingrs) + 
	    ". Any " + ingrs + " will do.");
    command("say Now, be on your way.");

    token = clone_object(DOL_OBJ + "quest/I_do_quest_token");
    token->set_task(DOL_Q_MAGE_QUEST);
    token->set_part(1);
    token->set_ingr(ingr);
    token->move(tp);

    return "";
}

int query_attack_me(object x) { return (x->query_attack() == TO); }

public void
run_away()
{
    int     hp = query_hp(),
	    mhp = query_max_hp();
    object  Garg,
	    *enemies;


    enemies = filter(query_enemy(-1), query_attack_me);
    map(enemies, "move_attack", this_object(), Garg);
    tell_room(tower,
	      QCTNAME(this_object())+" cowardly hides behind "
	      + QTNAME(Garg)+".\n", ({ this_object(), Garg, }) );
    enemies->catch_msg("You turn to attack "+QTNAME(Garg)+".\n");
    add_prop(OBJ_M_NO_ATTACK,
	     "@@query_is_behind" + ":" + file_name(this_object())
	     + "|" + file_name(Garg) + "@@");

    ::run_away();
}

string
query_is_behind(string prot_file)
{
    object  prot = find_object(prot_file);

    if (!objectp(prot) || !living(prot) ||
        !present(prot, ENV(TO)) ||
        (TP->query_attack() != prot) || !CAN_SEE(TO, prot))
    {
        set_alarm(0.0, 0.0, &remove_prop(OBJ_M_NO_ATTACK));
        return 0;
    }

    return process_string("That person is being protected by the "
			  + prot->query_nonmet_name()+"!\n");
}

/*
int
special_attack(object victim)
{
    int     result,
	er,
	wr;
    mixed   hr = ({ -1, 0, 0, 0 });
    string  wmsg = 0,
	vmsg,
	he = TO->query_pronoun(),
	his = TO->query_possessive(),
	vhim = victim->query_objective(),
	vhis = victim->query_possessive();
    string  vphrase, wphrase;

    remove_prop(LIVE_I_ATTACK_DELAY);

    if (random(100) > punch_rate)
        return 0;


    result = resolve_task(PUNCH_TASK, PUNCH_SKILLS,
        victim, PUNCH_VICTIM_SKILLS);

    er = (100 - ((2*victim->query_encumberance_weight() +
        victim->query_encumberance_volume())/3));
    wr = (100 * query_prop(OBJ_I_WEIGHT)) / victim->query_prop(OBJ_I_WEIGHT);
    result += (100 * (wr - er)) / PUNCH_TASK;

    if (result <= 0)
        add_attack_delay(MIN(5, -result/5 + 1), 1);
    else
    {
        if (result < 10)
            result = 10;
        else if (result > 90)
            result = 90;
	hr = victim->hit_me(F_PENMOD(PUNCH_PEN, result), W_BLUDGEON, TO, 
	    A_R_FIST);
    }

    switch(random(6))
    {
    case 0:
	vphrase = " cocks his arm back ";
	wphrase = " peers carefully at ";
	break;
    case 1:
	vphrase = " balls his fist ";
	wphrase = " stares balefully at ";
	break;
    case 2:
	vphrase = " screws up his fist ";
	wphrase = " growls angrily at ";
	break;
    case 3:
	vphrase = " draws back his fist ";
	wphrase = " burps disdainfully at ";
	break;
    case 4:
	vphrase = " cracks the knuckles on his fist ";
	wphrase = " gestures threateningly at ";
	break;
    case 5:
	vphrase = " tightens his fist ";
	wphrase = " screams obscenities at ";
	break;
    default:
	break;
    }

    switch(hr[0])
    {
    case -1:
	vmsg = " punches nothing but air. " + CAP(he) + " overbalances and "                + "almost falls down!";
	break;
    case 0..4:
	vmsg = " taps you lightly on the shoulder with his knuckles.";
            wmsg = " taps " + vhim + " lightly on the shoulder with his "
                + "knuckles.";
            break;
    case 5..9:
            vmsg = " swipes his knuckles over your chest just hard enough "
                + "to sting.";
            wmsg = " swipes at " + vhim + " just hard enough to sting.";
            break;
    case 10..19:
	vmsg = " pummels it into your " + hr[1] + ".";
	wmsg = " pummels it into " + vhis + " " + hr[1] + ".";
	break;
    case 20..34:
	vmsg = " slams it rapidly against your " + hr[1] + ".";
            wmsg = " slams it rapidly against " + vhis
                + " " + hr[1] + ".";
            break;
    case 35..49:
	vmsg = " sucker-punches you on the " + hr[1] + ".";
	wmsg = " sucker-punches " + vhis + " " + hr[1] + ".";
	break;
    case 50..59:
	vmsg = " nearly shatters your jaw.";
	wmsg = " nearly shatters " + vhis + " jaw.";
	break;
    case 60..79:
	vmsg = " brings it smashing down on your shoulder.";
	wmsg = " brings it smashing down on " + vhis + " shoulder.";
	break;
    case 80..99:
        vmsg = " clutches your throat. You see stars as his fist slams "
	    + "into your nose.";
	wmsg = " clutches " + vhis + " throat. You wince as the huge fist "
	    + "slams repeatedly into " + vhis + " nose.";
        break;
    default:
        vmsg = " tackles you! Blood flies in all directions as he beats "
	    + "you to a pulp.";
	wmsg = " tackles " + vhim + "! Blood flies in all directions as the "
	    + (implode(query_adjs()," ")) + " " + TO->query_race()
	    + " beats " + vhim + " to a pulp.";
        break;
    }
    if (!strlen(wmsg))
        wmsg = vmsg;
    victim->catch_msg("The " + (implode(query_adjs()," ")) + " "
		      + TO->query_race() + vphrase + "and"
		      + vmsg + "\n");
    tell_watcher("The " + (implode(query_adjs()," ")) + " "
		 + TO->query_race() + wphrase
		 + QTNAME(victim) + "," + vphrase + "and" + wmsg + "\n", TO, 
		 victim);

    if (victim->query_hp() <= 0)
        victim->do_die(TO);
    return 1;
}

/* */
