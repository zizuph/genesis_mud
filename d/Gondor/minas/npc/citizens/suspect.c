/*
 * The suspects in the whodunnit (pw quest to 5th gate)
 */
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan";
inherit "/d/Gondor/minas/npc/arrest_attacker";

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

// names banished on 11-jan-1995
#define SUSPECT_NAMES	({ "Forweg", "Androg", "Algund", "Ulrad", \
			   "Orleg", "Ulfang", "Ulfast", "Ulwarth", "Uldor", \
			})
#define SUSPECT_LONG	({ "This is a massive large dunadan. He seems to "\
			 + "be used hard physical work, "\
			 + "and does not look to be very bright.",\
			   "A large citizen of Minas Tirith. Large in more than one dimension, "\
			 + "so one might even call him thick.",\
			   "A small wiry person, nervously moving around, always twiddling with "\
			 + "his fingers.",\
			   "A tall and energetic citizen of Minas Tirith. He might be a trader "\
			 + "or a craftsman, but he does not look to be wealthy.",\
			   "This man tries to compensate for his bald head with an enormous black "\
			 + "beard which could rival the beard of a mighty dwarf lord.",\
			   "This dunadan looks like a mighty warrior. Most remarkable about him "\
			 + "are his broad shoulders and his long hair which is falling down over "\
			 + "his shoulders.",\
			   "This nervous round-faced dunadan looks like a rather well to-do "\
			 + "merchant or shop-keeper. But appearances may be deceiving.",\
			   "The wind and weather of many years has left its marks in the face of "\
			 + "this slender man. But surprisingly, this outdoors man is a resident "\
			 + "of this city.",\
			   "Short-legged almost like a dwarf, this man is ugly as only few of "\
			 + "the dunedain are.",\
			})

#define SUSPECT_ADDNAME	({ 0, 0, 0, ({"trader", "craftsman", }), 0,\
			   ({ "warrior", }), ({ "merchant", "shop-keeper", }),\
			   ({ "outdoors man", "traveller", }), 0, })
			   
#define SUSPECT_TITLE		({ "Citizen of Minas Tirith", \
				   "Citizen of Minas Tirith", \
				   "Citizen of Minas Tirith", \
				   "Citizen of Minas Tirith", \
				   "Citizen of Minas Tirith", \
				   "Citizen of Minas Tirith", \
				   "Citizen of Minas Tirith", \
				   "Citizen of Minas Tirith", \
				   "Citizen of Minas Tirith", \
				})
#define SUSPECT_ADJS		({ ({"massive", "large", }), \
				   ({"thick", "tall", }), \
				   ({"small", "wiry", }), \
				   ({"energetic", "tall", }), \
				   ({"bald", "black-bearded", }), \
				   ({"long-haired", "broad-shouldered", }), \
				   ({"nervous", "round-faced", }), \
				   ({"weathered", "slender", }), \
				   ({"ugly", "short-legged", }), \
				})
#define SUSPECT_HOUSE	({ "Aranarth", "Agarwaen", "Umarth", \
			   "Thalion", "Belecthor", \
			   "Borlad", "Hallacar", "Borlad", "Hallacar", \
			})

#define ARMOUR_BODY	({ (ARM_DIR + "fjacket"), (ARM_DIR + "fjacket"), \
		   (MINAS_DIR + "obj/ltunic"), (MINAS_DIR + "obj/ltunic"), \
		   (MINAS_DIR + "obj/cloak"), (MINAS_DIR + "obj/cloak"), \
		   (MINAS_DIR + "obj/mtunic"), (MINAS_DIR + "obj/mtunic"), \
		   (MINAS_DIR + "obj/mtunic"), \
			})

#define ARMOUR_REST ({ (ARM_DIR + "ltrousers"), (MINAS_DIR + "obj/ctrousers"),\
		   (MINAS_DIR + "obj/legging"), (MINAS_DIR + "obj/ctrousers"),\
		   (ARM_DIR + "ltrousers"), (MINAS_DIR + "obj/legging"),\
		   (MINAS_DIR + "obj/ctrousers"), (MINAS_DIR + "obj/legging"),\
		   (MINAS_DIR + "obj/ctrousers"), \
			})

public int    do_arrest(string str);
public void   confess_murder(object hunthor);

int     suspect = 0,		// fix the name of the suspect
        is_murderer = 0;	// is this suspect the murderer?
static  int     arrest_id;
object  arrested_by;

void    set_arrested_by(object pl) { arrested_by = pl; }
object  query_arrested_by() { return arrested_by; }

int
set_suspect(int is)
{
    object  o;

    if ((is < 0) || (is >= sizeof(SUSPECT_NAMES)))
        return 0;

    // is there already someone with this name?
    if (objectp(o = find_living(LOW(SUSPECT_NAMES[is]))))
         if ((MASTER_OB(o) == MASTER) && (o != TO))
            return 0;

    suspect = is;
    set_living_name(LOW(SUSPECT_NAMES[suspect]));
    set_name(LOW(SUSPECT_NAMES[suspect]));
    set_long(BSN(SUSPECT_LONG[suspect]));
    if (pointerp(SUSPECT_ADDNAME[suspect]))
        add_name(SUSPECT_ADDNAME[suspect]);
    remove_adj(query_adjs());
    set_adj(SUSPECT_ADJS[suspect]);
    set_title(SUSPECT_TITLE[suspect]);
    set_dunedain_house(SUSPECT_HOUSE[suspect]);

    // check with the quest master if this is the murderer
    if (MT_PW5_MASTER->query_murderer() == suspect)
        is_murderer = 1;
    // log this suspect with the master
    MT_PW5_MASTER->add_suspect(suspect, TO);
    return 1;
}

int
set_is_murderer()
{
    object  dagger;

    if (previous_object() != find_object(MT_PW5_MASTER))
        return 0;
    is_murderer = 1;
    // load the dagger
    if (objectp(dagger = present("dagger", TO)))
        dagger->set_doses(5);
    return 1;
}

int query_is_murderer() { return is_murderer; }

void
create_suspect()
{
    int     i = 0;

    // set_suspect(i);

    // knife skill not too bad, so he will be able to use the dagger
    set_skill(SS_WEP_KNIFE, 50 + random(21));
    // but he is not a trained fighter, so the other skills rather low
    set_skill(SS_DEFENCE,   10 + random(21));
    set_skill(SS_PARRY,      1 + random(10));
    set_skill(SS_AWARENESS, 10 + random(11));

    set_act_time(30);
    add_act("close door");
    add_act("pace");
    add_act("glitter");

    add_ask(({"alibi", }), VBFC_ME("ask_alibi"));
    add_ask(({"follow me", "follow",}), VBFC_ME("ask_follow"));
    add_ask(({"stop following me", "stop following", "stop follow", "stop",}),
        VBFC_ME("ask_stop_follow"));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

nomask void
create_dunadan()
{
    set_default_answer(VBFC_ME("default_answer"));

    set_stats(({ 40 + random(11),
                 50 + random(16),
                 45 + random(11),
                 30 + random(21),
                 30 + random(21),
                 25 + random(16),}));
    set_whimpy(55);

    create_suspect();
}

public varargs void
arm_me(int mt_equip = 0)
{
    object  dagger;

    ::arm_me(0);

    FIX_EUID

    if (!present("dagger", TO))
    {
        dagger = clone_object(WEP_DIR + "poison_dagger");
        if (is_murderer)
            dagger->set_doses(5);
        else
            dagger->set_doses(0);
        dagger->move(TO);
    }

    clone_object(ARMOUR_BODY[suspect])->move(TO);
    clone_object(ARMOUR_REST[suspect])->move(TO);

    command("wear all");
}

int
evidence_found(object tp)
{
    return ((tp->query_prop(MT_PW5_I_FOUND_MOTIVE) == 3) &&
            (tp->query_prop(MT_PW5_I_MERDOL_TESTIMONY)));
}

/*
 * Function name: call_for_help
 * Description:   If the suspect is innocent, or if the player
 *                does not have all the evidence, the suspect will
 *                shout for help
 * Arguments:     the attacking object
 * Returns:       %
 */
void
call_for_help(object enemy, object attacker)
{
    if (query_attack() != enemy)
        return;

    if (is_murderer && evidence_found(enemy))
        return;

    command("shout Help! Help!");
    command("shout "+CAP(LANG_ADDART(enemy->query_race_name()))+" is trying to kill me!");

    check_for_guards(enemy);

    arrest_id = set_alarm(15.0 + 30.0 * rnd(), 0.0, &arrest_attacker(enemy));
}

public void
attacked_by(object ob)
{
    command("wield dagger");

    ::attacked_by(ob);

    set_alarm(5.0, 0.0, &call_for_help(ob, ob));
}

public void
attack_object(object ob)
{
    command("wield dagger");

    ::attack_object(ob);

    set_alarm(5.0, 0.0, &call_for_help(ob, TO));
}

int
do_surrender(object enemy)
{

    if ((query_attack() != enemy) || (!present(enemy, ENV(TO))))
        return 0;

    command("shout I surrender!");
    command("say I confess everything!");
    command("say I killed Gimilzor!");
    command("drop weapons");
    stop_fight(enemy);
    enemy->stop_fight(TO);
    set_arrested_by(enemy);
    set_alarm(1.0, 0.0, &command("say I will follow you if you ask me to."));
    return 1;
}

private int
start_follow(object ob)
{
    object *follower,
            shadow;

    if (ob != arrested_by)
	return 0;

    if (!objectp(ob) || !objectp(present(ob, ENV(TO))))
	return 0;

    if (pointerp(follower = ob->query_follower()))
    {
	if (member_array(TO, follower) < 0)
	    ob->add_follower(TO);
    }
    else
    {
	shadow = clone_object(GONDOR_FOLLOW_SHADOW);
	shadow->set_delay(1.0);
	shadow->follow(ob, TO, 0);
    }
    set_alarm(1.0, 0.0, &command("say I will follow you now, "+ob->query_name()+"."));
    set_alarm(4.0, 0.0, &command("say If I should stop following you, "
      + "ask me to do so."));
    return 1;
}

string
ask_follow()
{
    if (!start_follow(TP))
    {
        command("say Why should I follow you?");
        command("peer " + TP->query_real_name());
    }
    return "";
}

private int
stop_follow(object ob)
{
    if ((ob != arrested_by) ||
	(member_array(TO, ob->query_follower()) < 0))
        return 0;

    TP->remove_follow_shadow();
    set_alarm(1.0, 0.0, &command("say I will stop following you now."));
    set_alarm(4.0, 0.0, &command("say If you tell me so, I will "
      + "follow you again."));
    return 1;
}

string
ask_stop_follow()
{
    if (!stop_follow(TP))
    {
        command("peer " + TP->query_real_name());
        command("say What are you talking about?");
        command("say I am not following you! Why do you think I am?");
    }
    return "";
}

public void
run_away()
{
    object  enemy = query_attack();

    if (!objectp(enemy))
        return;

    // if the suspect actually is the murderer and the player
    // has sufficient proof -> surrender
    if (is_murderer && evidence_found(enemy))
    {
        do_surrender(enemy);
    }
    else
        ::run_away();
}

int filter_door(object x) { return (function_exists("create_object", x) == "/std/door"); }

/*
 * Description: monster will follow a player in combat,
 *              as long as the new room is inside the monsters
 *              restrain path
 *              Switch this feature off by setting the prop LIVE_I_DONT_CLING
 */
/*
void
do_follow(string pl, string dir)
{
    int     dn,
            dc;
    mixed   exits;
    object  room = ENV(TO),
           *doors;

    if ((lower_case(pl) != arrested_by->query_real_name()))
        return;

    // strip trailing .\n from dir string
    dir = dir[0..(strlen(dir)-3)];

    if (dir == "the game")
    {
        set_alarm(2.0 + 5.0*rnd(), 0.0, &react_quit(pl));
        return;
    }

    exits = room->query_exit();
    if ((dn = member_array(dir, exits)) < 0)
    {
        // check for doors: ugly, but I don't know how to do it any better
        doors = filter(all_inventory(ENV(TO)), &filter_door(TO));
        for (dc = 0; dc < sizeof(doors); dc++)
        {
            if (member_array(dir, doors[dc]->query_pass_command()) >= 0)
            {
                set_alarm(1.0, 0.0, &command(dir));
                return;
            }

        }
 
        return;
    }

    if (!sizeof(filter_exits(exits[dn-1..dn+1])))
    {
        command("shout I cannot follow you there.");
        return;
    }

    set_alarm(1.0, 0.0, &command(dir));
}
 */

mixed
query_suspect_name(int i)
{
    if (i < 0)
        return SUSPECT_NAMES;

    if (i >= sizeof(SUSPECT_NAMES))
        return 0;

    return SUSPECT_NAMES[i];
}

void
init_living()
{
    ::init_living();

    add_action(do_arrest, "arrest");

    if (!objectp(arrested_by))
        return;

    if (TP != find_living("hunthor"))
        return;

    set_alarm(2.0, 0.0, &confess_murder(TP));
}

public int
do_arrest(string str)
{
    object *victim;
    string  vb = query_verb();

    NFN(CAP(vb)+" whom?");
    if (!strlen(str))
        return 0;

    if (!parse_command(str, ENV(TO), "[the] %l", victim))
        return 0;

    victim = NORMAL_ACCESS(victim, 0, 0);

    if ((sizeof(victim) != 1) || (victim[0] != TO))
        return 0;

    if (!is_murderer)
    {
        command("say What are you trying to do?");
        command("say I've done nothing wrong!");
        command("say You cannot arrest me!");
        return 1;
    }

    if (!evidence_found(TP))
    {
        command("snicker");
        command("say You want to arrest me?");
        command("cackle");
        command("say You can't prove anything!");
        command("say Get out of here before I call the guard!");
        command("finger "+TP->query_real_name());
        return 1;
    }

    command("say You fool!");
    command("say Did you think I'd come with you just like this?");
    if (F_DARE_ATTACK(TO, TP))
    {
        command("say You should have cared about your own business!");
        set_alarm(1.0, 0.0, &command("kill "+TP->query_real_name()));
    }
    else
        command("say If you want to arrest me, you'll have to fight me first.");

    return 1;
}

void
remove_murderer()
{
    command("emote is led away by a guard.");
    set_alarm(1.0, 0.0, "remove_object");
}

public void
confess_murder(object hunthor)
{
    command("grovel hunthor");
    command("say My lord, I ask you to show mercy!");
    command("say I confess I killed Gimilzor!");

    hunthor->confession_murder_quest(arrested_by, TO);
}

string
default_answer()
{
    command("say I'm sorry, but I don't know what you are talking about, "
      + (TP->query_gender() ? "Madam" : "Sir") + "!");
    return "";
}

void
return_object(object obj, object to)
{
    if (obj->id("coin"))
    {
        command("thank "+to->query_real_name());
        command("grin");
        return;
    }

    command("say Thanks, but I don't think I need that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (ENV(obj) == TO)
    {
       command("drop " + OB_NAME(obj));
    }
}

void
check_owned_dagger(object dagger)
{
    int     ob_num;
    string *suspects,
            seller;

    suspects = query_suspect_name(-1);
    suspects -= ({ MT_PW5_MASTER->query_murderer_name() });
    sscanf(OB_NUM(dagger), "%d", ob_num);
    seller = suspects[random(sizeof(suspects), ob_num)];

    if (seller != query_real_name())
        return;

    command("say This looks like a dagger I bought from Herumegil once.");
    command("sigh");
    command("say But I had to sell it again when I needed some money.");
}

void
return_dagger(object obj, object to)
{
    if (!(obj->id(MT_PW5_MURDER_WEAPON)))
    {
        return_object(obj, to);
        return;
    }

    command("emote inspects the "+obj->short()+".");

    // has the evidence been tampered with?
    if (!obj->query_bloody())
    {
        return_object(obj, to);
        return;
    }

    if (!is_murderer)
    {
        check_owned_dagger(obj);
        command("ponder the blood on the dagger");
        command("say What am I supposed to do with this?");
        command("say It looks like this was used for some crime.");
        command("I don't want anything to do with it.");
        command("drop "+OB_NAME(obj));
        return;
    }
   
    if (!evidence_found(TP))
    {
        command("clean dagger");
        command("say What did you do with my dagger?");
        command("whistle inno");
        command("say What did you use it for?");
        command("say Where did you find it?");
        return;
    }

    command("clean dagger");
    command("say You fool!");
    command("say What's this supposed to prove?");
    command("drop dagger");

    command("say Try to arrest me if you dare!");
    command("glare "+TP->query_real_name());

    return;
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from) || !objectp(obj))
        return;
    if (!living(from))
        return;

    // Is this the murder weapon?
    if (obj->id(MT_PW5_MURDER_WEAPON))
        set_alarm(0.5, 0.0, &return_dagger(obj, from));
    else
        set_alarm(0.5, 0.0, "return_object", obj, from);
}

string
ask_alibi()
{
    string  alibi = "I was asleep last night. That is not illegal, is it?";

    command("ponder");

    if (!is_murderer)
    {
        alibi = ONE_OF_LIST( ({
            "I was asleep last night. That is not illegal, is it?",
            "I was in the tavern last night, having fun with a few friends.",
            "I don't have to answer any questions from you. I'll answer "
          + "only to the proper authorities!",
            "Who are you to go around and interrogate people?",
            "I was applying for a job with Thavron, the carpenter.",
            "I was on a visit to Pelargir and didn't return until a few "
          + "hours ago.", }) );
    }

    command("peer " + TP->query_real_name());
    command("say It's none of your business, is it?");
    command("say "+alibi);
    return "";
}


string *
query_trig_patterns()
{
    return trig_patterns;
}

