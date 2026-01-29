/* 
 * /d/Gondor/fangorn/npc/oat_ent.c  
 *
 * An ent for the oat quest
 *
 * Alto, 22 August 2001
 *
 * Note: People have been cheating constantly on this
 * quest, so I have decided to make it a little more
 * random.
 *
 */

#pragma strict_types

inherit "/std/monster";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <money.h>
#include <tasks.h>
#include "/d/Gondor/minas/lib/porter_defs.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

/* Define some attack and hitloc id's */

#define A_L_FIST   0
#define A_R_FIST   1
#define A_L_ROOT   2
#define A_R_ROOT   3

#define H_HEAD    0
#define H_TRUNK   1
#define H_RARM    2
#define H_LARM    3
#define H_RLEG    4
#define H_LLEG    5

#define FANGORN_DIR "/d/Gondor/fangorn/"
#define FAILED_TO_ANSWER  "_failed_to_answer"


static       object  Victim;
object       huorn, actor;
string       Index, Value;

string       riddles_answer();
int          answer_riddle(string str);
string       alignlook();
string       alignlook2();
void         add_gems();
string       wizard_greeting();
public int   remove_ent();
public int   did_not_answer();

#define HAMMER_TASK	TASK_ROUTINE
#define HAMMER_SKILLS	({ TS_DEX, TS_STR })
#define HAMMER_VICTIM_SKILLS	({ TS_DEX })

#define HAMMER_RATE	25
#define HAMMER_PEN	60

static int     hammer_rate  = HAMMER_RATE,
               hammer_pen   = HAMMER_PEN;

void
set_hammer_rate(int i) { hammer_rate = i; }

void
set_hammer_pen(int i)  { hammer_pen = i; }

string *riddles =
/*1*/   ({"How many needles, per bundle, are found on lodgepole pines?", 
/*2*/     "How many needles, per bundle, are found on white pines?", 
/*3*/     "True or false. Pine trees flourish in dense shaded forests?",
/*4*/     "Are pine trees coniferous or deciduous?",
/*5*/     "Which genus of coniferous tree has needles in small clusters?",
/*6*/     "Which genus of tree is the tallest to grow on the face of Arda?",
/*7*/     "Are sequoia trees coniferous or deciduous?",
/*8*/     "Are oak trees coniferous or deciduous?",
/*9*/     "To what genus do oak trees belong?",
/*10*/    "What kind of deciduous tree is characterized by alternating "
            + "branches, with simple lobed leaves - oak, maple, walnut "
            + "or ash?",
/*11*/    "What kind of deciduous tree is characterized by alternating "
            + "branches, with simple non-lobed leaves - oak, birch, walnut "
            + "or ash?",
/*12*/    "What kind of deciduous tree is characterized by alternating "
            + "branches, with compound leaves - oak, maple, walnut "
            + "or ash?",
/*13*/    "What kind of deciduous tree is characterized by opposite "
            + "branches, with simple leaves - oak, maple, walnut "
            + "or ash?",
/*14*/    "What kind of deciduous tree is characterized by opposite "
            + "branches, with compound leaves - oak, maple, walnut "
            + "or ash?",
/*15*/    "What tree has the larger cones - the cypress or the false cedar?",
/*16*/    "What genus of coniferous tree has small fruits that look like "
            + "blue berries?",
/*17*/    "Which kind of coniferous tree has leaves that are all sharp, "
            + "flattened, short and scale-like - pine, sequoia, juniper "
            + "or cypress?",
/*18*/    "Which kind of coniferous tree has leaves that are not all sharp, "
            + "but are all flattened, short and scale-like, with soft "
            + "cones - pine, sequoia, juniper or cypress?",
/*19*/    "Which genus of tree is characterized by catkins?",
/*20*/    "What tree kills plants growing nearby - walnut, birch, maple or "
            + "oak?",
/*21*/    "In which kind of forest would you most likely be able to see the "
            + "sun through the canopy - sequoia, pine, juniper or false cedar?",
/*22*/    "Which has the largest acorns - the pin oak or black oak?",
/*23*/    "True or false - maple syrup is most commonly made from the sap "
            + "of red maples?",
/*24*/    "What conifer has needles oriented in a fern-like spray - pine, "
            + "juniper, false cedar or sequoia?",
/*25*/    "To what genus do walnut trees belong?"});


string *answers =
/*1*/     ({"two", 
/*2*/       "five", 
/*3*/       "false",
/*4*/       "coniferous",
/*5*/       "pinus",
/*6*/       "sequoiadendron",
/*7*/       "coniferous",
/*8*/       "deciduous",
/*9*/       "quercus",
/*10*/      "oak",
/*11*/      "birch",
/*12*/      "walnut",
/*13*/      "maple",
/*14*/      "ash",
/*15*/      "cypress",
/*16*/      "juniperus",
/*17*/      "sequoia",
/*18*/      "juniper",
/*19*/      "betula",
/*20*/      "walnut",
/*21*/      "pine",
/*22*/      "black oak",
/*23*/      "false",
/*24*/      "false cedar",
/*25*/      "juglans"});



public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj(alignlook());
    add_adj(alignlook2());
    set_pname("ents");
    set_name("ent");

    set_race_name("ent");

    set_long("The creature appears to be half man and half tree! He is "
        + "at least fourteen feet tall, with branch-like arms and "
        + "leaf-like hair. His skin is covered with a thick bark-like "
        + "substance which looks like it would protect him very well. "
        + "The most impressive thing about him, however, are his eyes, "
        + "which are wise, patient, and echo millennia of sorrow and "
        + "joy.\n");

    rnd = random(60);
    default_config_npc(150+rnd/2);
    set_base_stat(SS_DIS, 150 + rnd);
    set_alignment(50+rnd*10);

    set_gender(0);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_LOC_SENSE, 100);
    set_skill(SS_TRACKING, 100);

    set_exp_factor(150);

    add_prop(LIVE_I_SEE_DARK, 200);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_m_out("rumbles");
    set_m_in("rumbles in");

    set_cact_time(2);
    add_cact("emote trumpets a painful high-pitched note.");
    add_cact("emote thunders: How dare you harm my trees! Hroom!");
    add_cact("emote thunders: Fangorn is not a place for tree-killers! Hrum!");
    add_cact("emote growls: Unfortunately for you, I am a hasty ent.");
    add_cact("emote grumbles: Do not touch the trees in my forest.");

    add_gems();

    clone_object("/d/Gondor/fangorn/obj/oat_q_branch.c")->move(TO);

    set_alarm(75.0, 0.0, &remove_ent());

    refresh_mobile();
}

string
alignlook() 
{
    string *alignlooks =
                 ({"towering", "gigantic", "massive", "lumbering",
                   "huge", "tall", "ancient", "giant", "weathered", 
                   "grim","hardy","friendly","hasty", "patient", 
                   "alert"});
    return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
    string *alignlooks2 =
                 ({"oak-like", "maple-like", "beech-like",
                   "elm-like", "spruce-like", "pine-like", "sycamore-like", 
                   "willow-like","birch-like","ash-like", 
                   "hickory-like"});
    return ONE_OF_LIST(alignlooks2);
}


string
gem_types() 
{
    string *gemtypes =
                 ({"agate", "amber", "amethyst", "beryl_red",
                   "chalcedony", "coral", "diamond", "emerald", "garnet", 
                   "jade","opal","peridot","ruby", "sapphire", 
                   "moonstone"});
    return ONE_OF_LIST(gemtypes);
}

void
add_gems()
{
    setuid();
    seteuid(getuid());

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);
}



/*
 * Add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */

public void
cr_configure()
{
    add_attack(40+random(5),40+random(5),W_BLUDGEON,10,A_L_FIST);
    add_attack(40+random(5),40+random(5),W_BLUDGEON,30,A_R_FIST);
    add_attack(40+random(5),40+random(5),W_BLUDGEON,20,A_L_ROOT);
    add_attack(40+random(5),40+random(5),W_BLUDGEON,40,A_R_ROOT);

    add_hitloc(({25+random(15),20+random(10),15+random(5)}),10,
        "massive head",H_HEAD);
    add_hitloc(({25+random(5),15+random(5),20+random(10)}),50,
        "thick trunk",H_TRUNK);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "knotted left arm",H_RARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "knotted right arm",H_LARM);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "huge root-like left leg",H_RLEG);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,
        "huge root-like right leg",H_LLEG);

}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_L_FIST:return "hammer-shaped left fist";
    case A_R_FIST:return "hammer-shaped right fist";
    case A_L_ROOT:return "gnarled left foot";
    case A_R_ROOT:return "gnarled right foot";
    }
    return "mind"; /* should never occur */
}

public string
query_combat_file()
{
    return "/std/combat/cplain";
}



/*
 * Function name:   start_follow
 * Description:     Start following the enemy.
 * Arguments:       The object to follow.
 */
public void
start_follow(object ob)
{
    object *follower,
            shadow;

    if (!objectp(ob) || !objectp(present(ob, ENV(TO))) || 
	(ob != query_attack()) || (Victim == ob))
	return;

    if (pointerp(follower = ob->query_follower()))
    {
	if (member_array(TO, follower) < 0)
	    ob->add_follower(TO);
    }
    else
    {
	shadow = clone_object(GONDOR_FOLLOW_SHADOW);
	shadow->follow(ob, TO);
    }
    Victim = ob;
}

public varargs void
remove_victim(object victim)
{
    if (objectp(victim) && (Victim != victim))
	return;
    Victim = 0;
}



/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    ::attack_object(ob);
    start_follow(ob);
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    attack_object(ob);
}


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

    remove_prop(LIVE_I_ATTACK_DELAY);

    if (random(100) > hammer_rate)
        return 0;

    // check if we hit

    result = resolve_task(HAMMER_TASK, HAMMER_SKILLS,
        victim, HAMMER_VICTIM_SKILLS);

    er = (100 - ((2*victim->query_encumberance_weight() +
                    victim->query_encumberance_volume())/3));
    wr = (100 * query_prop(OBJ_I_WEIGHT)) / victim->query_prop(OBJ_I_WEIGHT);
    result += (100 * (wr - er)) / HAMMER_TASK;

    if (result <= 0)
        add_attack_delay(MIN(5, -result/5 + 1), 1);
    else
    {
        if (result < 10)
            result = 10;
        else if (result > 90)
            result = 90;
        hr = victim->hit_me(F_PENMOD(HAMMER_PEN, result), W_BLUDGEON, TO, A_R_FIST);
    }

    switch(hr[0])
    {
        case -1:
            vmsg = ", but misses entirely. " + CAP(he) + " hooms furiously.";
            break;
        case 0..4:
            vmsg = ", but only manages to scratch you with the rough surface "
                + "of his fists.";
            wmsg = ", but only manages to scratch " + vhim + " with the "
                + "rough surface of his fists.";
            break;
        case 5..9:
            vmsg = ", but only slightly bruises you.";
            wmsg = ", but only slightly bruises " + vhim + ".";
            break;
        case 10..19:
            vmsg = " and crunches " + his + " fists into your " + hr[1] + ".";
            wmsg = " and crunches his fists into " + vhis + " " + hr[1] + ".";
            break;
        case 20..34:
            vmsg = " and smashes his fists heavily into your " + hr[1] + ".";
            wmsg = " and smashes his fists heavily into " + vhis 
                + " " + hr[1] + ".";
            break;
        case 35..49:
            vmsg = " and hammers his massive fists painfully upon "
                + "your " + hr[1] + ".";
            wmsg = " and hammers his massive fists painfully upon "
                + vhis + " " + hr[1] + ".";
            break;
        case 50..59:
            vmsg = " and crushes your head with his fists.";
            wmsg = " and crushes " + vhis + " head with his fists.";
            break;
        case 60..79:
            vmsg = ", tosses you high into the air and tramples you with "
                + "his root-like feet.";
            wmsg = ", tosses " + vhim + " high into the air and tramples " 
                + vhim + "with his root-like feet.";
            break;
        case 80..99:
            vmsg = ", grabs you by the neck and shatters your body against "
                + "several trees.";
            wmsg = ", grabs " + vhim + " by the neck and shatters " + vhis 
                + " body against several trees.";
            break;
        default:
            vmsg = " and tramples you into the ground beneath his feet.";
            wmsg = " and tramples " + vhim + " into the ground beneath his feet.";
            break;
    }

    if (!strlen(wmsg))
        wmsg = vmsg;
    victim->catch_msg("The ent hammers at you" + vmsg + "\n");
    tell_watcher("The ent hammers at " + QTNAME(victim) 
        + wmsg + "\n", TO, victim);

    if (victim->query_hp() <= 0)
        victim->do_die(TO);
    return 1;
}


void
do_die(object killer)
{
    setuid();
    seteuid(getuid());

    huorn = clone_object(FANGORN_DIR + "npc/huorn.c");
    huorn->move(ENV(TO));


    tell_room(ENV(TO), "The ent shrieks so loudly that your ears hurt. "
        + "As it dies, it crumbles into the dust from which it was born.\n");

    ::do_die(killer);
}


/* Leave Wizards Alone */

void
init_attack()
{
    object  victim;

    if (objectp(query_attack()))
        return;

    if ((victim = TP)->query_npc())
        return;

    set_alarm(2.0, 0.0, "wizard_greeting", victim);
}


string
wizard_greeting()
{
    actor = TP->query_real_name();

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
        return "";


    if (TP->query_wiz_level())
    {
        command("say to " + actor + " Greetings, Wizard.");
        command("bow " + actor);
        command("say to " + actor + " What brings you to our forest?");
        return "";
        
    }

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say to " + actor + " Hoom! Greetings friend "
            + "of the forest.");
        return "";
    }


    if (!TP->query_prop(QUESTING_FOR_OATS))
        {
        command("peer thoughtfully " + actor);
        command("say to " + actor + " It seems to me you have very "
            + "little business here. Perhaps you should be on your way. "
            + "Hroom!");
        return "";
        }

    if (TP->query_prop(FOUND_OAT_BRANCH))
        {
        command("say to " + actor + " You already have your branch, "
            + "please do not linger here. Hrum!");
        command("wave " + actor);
        return "";
        }

    if (TP->query_prop(FAILED_TO_ANSWER))
        {
        command("say to " + actor + " You have no business here, stranger.");
        command("poke " + actor);
        return "";
        }

    else
    {
        command("greet " + actor);
        command("say to " + actor + " Are you looking for "
            + "branches of the marsh oak?");
        set_alarm(1.0, 0.0, &command("say to " + actor + " We recently "
            + "chased off some scoundrel who "
            + "tried to cut one of our trees. I see you have some "
            + "respect for trees, though."));
        set_alarm(4.0, 0.0, &command("say to " + actor + " I have a "
            + "question for you. "
            + "If you answer it correctly, I will know you are a true "
            + "friend of the forest. If you fail to answer, Hroom! "
            + "Then even my slow wrath may come to a boil!"));
        set_alarm(7.0, 0.0, &riddles_answer());
        set_alarm(70.0, 0.0, &did_not_answer());
       return "";
    }
    command("say Hoom! Something is wrong. Make a bugreport!");
    return "";
}


string  
riddles_answer()
{
    int position;

    Index = ONE_OF_LIST(riddles);

    position = member_array(Index, riddles);

    Value = answers[position];

    riddles -= ({ Index });

    answers -= ({ Value });

    actor = TP->query_real_name();

    command("whisper " + actor + " " + Index + " \nYou have one "
        + "minute to provide me with 'answer <answer>'");

    set_alarm(1.0, 0.0, &answer_riddle());

    return Value;
}

void
init_living()
{
   ::init_living();
   add_action("answer_riddle", "answer");
}


int
answer_riddle(string str)
{
    string response = LOW(str);
    actor = TP->query_real_name();

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
        return 1;


    if (TP->query_wiz_level())
    {
        command("say to " + actor + " Wizard, I appreciate your "
            + "interest, but you "
            + "really should not be helping out here. Hoom!");
        return 1;
        
    }

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_OAT_BIT))
    {
        TO->command("say to " + actor + " You have shown yourself a "
            + "friend of the "
            + "forest in the past. Hoom! But I will not be giving "
            + "you any more branches. How hasty you are!");
        return 1;
    }


    if (!TP->query_prop(QUESTING_FOR_OATS))
        {
        command("peer thoughtfully " + actor);
        command("say to " + actor + " It seems to me you have very "
            + "little business here. Perhaps you should be on your way. "
            + "Hroom!");
        return 1;
        }

    if (TP->query_prop(FOUND_OAT_BRANCH))
        {
        command("say to " + actor + " You already have your branch, "
            + "please do not "
            + "linger here. Hrum!");
        command("wave " + actor);
        return 1;
        }

    if (TP->query_prop(FAILED_TO_ANSWER))
        {
        command("say to " + actor + " You have no business here, "
            + "stranger. Hoom!");
        command("poke " + actor);
        return 1;
        }


    if (!strlen(str))
        {
        command("say to " + actor + " Answer soon, lest I become hasty!");
        return 1;
        }

    if (response != Value)
        {
        command("say to " + actor + " That is incorrect. You are "
            + "not a friend of the "
            + "forest after all. Seek the learned of Minas Tirith, who "
            + "in days past were known to have lore of our ways.");
        command("sigh");
        TP->add_prop(FAILED_TO_ANSWER, 1);
        return 1;
        }

    if (response = Value)
        {
        if (TP->query_prop(FAILED_TO_ANSWER))
            {
            command("say to " + actor + " Are you still here? Begone.");
            return 1;
            }

        if (TP->query_prop(FOUND_OAT_BRANCH))
            {
            command("say to " + actor + " HOOM! I already gave "
                + "you a branch. Do "
                + "not be greedy.");
            return 1;
            }

            command("say to " + actor + " Correct! You obviously "
                + "know your lore of trees. "
                + "Hoom! It is good to see a friend of the forest.");
            TP->add_prop(FOUND_OAT_BRANCH, 1);

            command("give branch to " + actor);

            return 1;

        }

    else
        {
        command("say Something went wrong...Please make a bug report.\n");
        return 0;
        }

}

public int
remove_ent()
{
    say("The ent passes through the trees and is gone.\n");
    TO->remove_object();
    return 1;
}


int
did_not_answer()
{
    actor = TP->query_real_name();

    if (!objectp(present(TP, ENV(TO))))
        {
        return 1;
        }


    if (TP->query_prop(FOUND_OAT_BRANCH))
        {
        return 1;
        }

    command("say to " + actor + " Obviously you are not a friend of the "
        + "forest. Seek "
        + "the learned of Minas Tirith. Perhaps there you can learn "
        + "something of trees.");

    TP->add_prop(FAILED_TO_ANSWER, 1);

    return 1;
}


