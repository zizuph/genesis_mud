/* Spectre himself. Mortricia 921001 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>

#include "/d/Terel/common/terel_defs.h"

#define NF(xx)          notify_fail(xx);
#define TP              this_player()
#define TO              this_object()
#define ETP             environment(TP)
#define ETO             environment(TO)
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"
#define EQUIP_DIR       HAUN_DIR + "equip/"
#define H_CLONE(xx)     clone_object(EQUIP_DIR + xx) -> move(TO)
#define W_DEL           6
#define W_STR   ({"You need my sceptre...",\
                  "Try to find it...",\
                  "...it's the only way for me to become living again...",\
		  "I lost it when I died...",\
		  "...hail me with it..."})
#define KING_KILLER     "_king_killer"
#define ALIGN           -10

/*** Functions: ***/
void haunt(object who);
object find_q_ring(int q_no, object ob);
void introduce_me(object who);
void multi_whisper(object who);
void set_w_str(string *tmp);
void set_w_del(int tmp);
void paralyze_all(object where, object killer);
int make_me_no_ghost(object who);

/*** Global variables: ***/
int i_whisper, w_del;
string *w_str;
object sword;

public void
create_monster()
{
    set_name("spekaros");
    add_name("spectre");
    add_name("king");
    set_living_name("spekaros");
    set_short("@@my_short");
    set_long("@@my_long");
    set_adj(process_string("@@my_adj"));

    set_race_name("human");
    set_title("the King of Makor");
    set_gender(0);

    set_stats(({99,99,99,99,99,99}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
    set_invis("@@can_see");
    set_ghost(1);

    i_whisper = 0;
    w_del = W_DEL;
    w_str = W_STR;

    set_skill(SS_2H_COMBAT, 99);
    set_skill(SS_WEP_AXE,   99);
    set_skill(SS_WEP_SWORD, 99);
    set_skill(SS_DEFENCE,   99);
    set_skill(SS_PARRY,     99);
    set_skill(SS_AWARENESS, 99);

    trig_new("%s 'introduces' %s", "react_introduce");
    set_alarm(2.0, -1.0, "dress_me");
}

public void
init_living()
{
    ::init_living();
    add_action("do_hail", "hail");
}

public int
do_hail(string str)
{
    object *obs;
    string who, what;
    string s;

    if (!str) return 0;
    if (sscanf(str, "%s with %s", who, what) != 2) {
        who = str;
        what = "";
    }
    obs = FIND_STR_IN_OBJECT(who, ETP);
    if (sizeof(obs) == 0) return 0;
    if (sizeof(obs) >= 2) return 0;
    if (obs[0] != TO) return 0;
    s = ".\n";
    if (!CAN_SEE(TP, TO)) return 0;
    if (strlen(what)) {
        notify_fail("Hail "+short()+" with what?\n");
        obs = FIND_STR_IN_OBJECT(what, TP);
        if (sizeof(obs) == 0) return 0;
        if (sizeof(obs) >= 2) return 0;
        if (MASTER_OB(obs[0]) != HAUN_DIR + "sceptre") return 0;
        s = " with "+LANG_ADDART(obs[0])+".\n";
        make_me_no_ghost(TP);
    }
    write("You hail the "+short()+s);
    say(QCTNAME(TP) + " hails "+QTNAME(TO)+s);
    return 1;
}

public string
my_long()
{
    string s;

    if (TO->query_ghost()) {
        s =
        "This being is a lost soul. Once this poor soul was a " +
        "proud and great king. You wonder what evil he might " +
        "have done to achieve his present state; or, even more " +
        "important, why is he here haunting people?";
    } else {
        s =
        "It's a king in all his splendour.";
    }
    return s + "\n";
}

public string
my_short()
{
    string s;

    if (TO->query_ghost()) {
        s = "faint spectre";
    } else {
        s = "great king";
    }
    return s;
}

public string
my_adj()
{
    string s;

    if (TO->query_ghost()) {
        s = "faint";
    } else {
        s = "great";
    }
    return s;
}

public void
dress_me()
{
    seteuid(getuid(TO));
    sword = clone_object(EQUIP_DIR + "sword_k");
    sword->add_prop(KING_KILLER, TO->query_name());
    sword->move(TO);
    H_CLONE("mail_k");
    H_CLONE("helmet_k");
    H_CLONE("cloak_k");
}

public void
haunt(object who)
{
    string name, race, s;

    if (TO->query_ghost() == 0) {
	if (who->query_skill(SS_AWARENESS) > 50) {
	    who->catch_msg("You feel the presence of someone.\n");
	}
	return;
    }
    if (environment(who) == ETO) {
        name = lower_case(who->query_name());
        command("stare at " + name);
        race = capitalize(who->query_race_name());
        if (race == "Human") {
            s = "Humans... bah... beings without brains...";
        } else if (race == "Elf") {
            s = "Elves... bah... such fussy beings...";
        } else if (race == "Dwarf") {
            s = "Dwarves... bah... such stupid creatures...";
        } else if (race == "Goblin") {
            s = "Goblins... bah... dirty little shits...";
        } else if (race == "Gnome") {
            s = "Gnomes... bah... they are just so boring...";
        } else if (race == "Hobbit") {
            s = "Hobbits... bah... can be crushed in a single blow...";
        } else {
            s = race + "... never heard of that race... Can they multiply? ";
        }
        command("whisper " + name + " " + s);
    } else {
	command("scream");
    }
}

public int
can_see()
{
    if (TP->query_ghost()) return 0;
    return query_ghost();
}

object
find_q_ring(int q_no, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
        if (ob_arr[i]->query_prop("q_number") == q_no &&
            ob_arr[i]->query_prop("q_solver") == ob->query_name()) {
            r_ob = ob_arr[i];
        }
    }
    return r_ob;
}

public void
introduce_me(object who)
{
    string name;

    if (!who || ETO != environment(who)) return;
    name = lower_case(who->query_name());

    if (!(who->query_met(TO))) command("introduce me to " + name);

    if (!find_q_ring(7, who) || !(who->query_ghost()) ||
        !(TO->query_ghost())) return;

    set_alarm(itof(1 + w_del), -1.0, &multi_whisper(who));
}

public void
react_introduce(string person, string who)
{
    object *obs;
    string name, dummy;

    if (sscanf(person, "Ghost of %s", dummy) == 1) {
        name = dummy;
    } else {
        name = person;
    }

    obs = FIND_STR_IN_OBJECT(lower_case(name), ETO);
    if (sizeof(obs) == 0) return;
    if (sizeof(obs) >= 2) return;
    if (!CAN_SEE(obs[0], TO)) return;
    set_alarm(5.0, -1.0, &introduce_me(obs[0]));
}

public void
multi_whisper(object who)
{
    int i;
    string whisper_string;

    i = sizeof(w_str);
    if (i == 0 || !who || i_whisper >= i) return;

    whisper_string = "whisper " + lower_case(who->query_name()) + " " +
                     w_str[i_whisper];
    if (environment(TO) == environment(who)) command(whisper_string);

    i_whisper++;
    if (i_whisper >= i) return;

    set_alarm(itof(1+w_del/2+random(w_del/2)), -1.0, &multi_whisper(who));
}

void set_w_str(string *tmp) { w_str = tmp; }

void set_w_del(int tmp) { w_del = tmp; }

public void
do_die(object killer)
{
    object ring, here;
    string name;

    if (query_hp() > 0) return;
    name = lower_case(killer->query_name());
    here = environment(TO);
    command("unwield sword");
    tell_room(here, "The "+short()+" coughs up some blood.\n");
    ring = find_q_ring(7, killer);
    if (ring && ring->query_prop("q_step") == 3) {
        ring->change_prop("q_step", 4);
        if (here == environment(killer)) {
            if (environment(sword) == TO) {
                sword->change_prop(KING_KILLER, killer->query_name());
                command("give sword to " + name);
            }
            command("whisper " + name + " Thanks for releasing me...");
        }
    }
    command("sigh");
    killer->catch_msg("You see the spirit of the "+short()+" ascent.\n");
    say("A tremendous light flash stuns you as the " +
                    short() + "'s released spirit ascents.\n", killer);
    paralyze_all(here, killer);
    ::do_die(killer);
}

public void
paralyze_all(object where, object killer)
{
    object p_ob;
    object *all;
    int i, t;

    all = all_inventory(where);
    seteuid(getuid(TO));
    for (i=0; i<sizeof(all); i++) {
        if (living(all[i]) && all[i] != killer && all[i] != TO) {
            t = 150 - random(all[i]->query_stat(SS_CON));
            if (t <= 10) t = 10;
            p_ob = clone_object("/std/paralyze");
            p_ob->set_stop_verb("");
            p_ob->set_stop_obj(0);
            p_ob->set_stop_fun("");
            p_ob->set_remove_time(t);
            p_ob->set_fail_message("You are too shocked to do that.\n");
            p_ob->set_stop_message("You regain control of yourself.\n");
            p_ob->move(all[i]);
        }
    }
    return;
}

int
make_me_no_ghost(object who)
{
    if (!who || environment(who) != environment(TO)) return 0;
    if (!find_q_ring(7, who)) return 0;
    if (query_ghost() == 0) return 0;
    set_ghost(0);
    set_invis(0);
    TO->command("wear all");
    TO->command("wield sword");
    return 1;
}
