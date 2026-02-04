inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>

#define TO           this_object()
#define TP           this_player()
#define ETO          environment(TO)
#define ETP          environment(TP)
#define AH(xx)       (xx->query_skill(SS_ANI_HANDL))
#define TP_AH        (TP->query_skill(SS_ANI_HANDL))
#define NF(xx)       notify_fail(xx + "\n")

#define RIDE_PROP     "_can_ride_here"
#define NPC_HORSE_CMD "_npc_horse_cmd"
#define HORSE_BACK    "/d/Terel/mortricia/horses/hb"
#define HORSE_FLEA    "/d/Terel/mortricia/horses/hf"
#define LONG_DESC     "The horse looks very strong and healthy."

static object horse_back;
static object horse_flea;
static object rider;
static string long_desc;
static string extra_name="";
static object named_by;

public void set_rider(object ob);
public object query_mounted();
public object query_horse_flea();
public int half_ran(int i);
public int query_running();
public void create_horse();
public string query_horse_long();
public void set_horse_long(string str);
public object query_named_by();
public void  reset_named_by();

public void
init_living()
{
    ::init_living();
    if (ETP == ETO) {
        add_action("mount", "mount");
        add_action("feed", "feed");
	add_action("halt", "halt");
    }
    if (ETP == ETO && !strlen(extra_name)) add_action("name", "name");
}

public void
create_creature()
{
    set_name("horse");
    set_race_name("horse");
    set_long("@@my_long");
    set_horse_long(LONG_DESC);
    set_gender(G_NEUTER);

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_WEIGHT, 180000);
    add_prop(CONT_I_MAX_WEIGHT, 280000);
    add_prop(CONT_I_VOLUME, 180000);
    add_prop(CONT_I_MAX_VOLUME, 280000);

    set_tell_active(1);

    create_horse();

    seteuid(getuid());
    horse_back = clone_object(HORSE_BACK);
    set_room(horse_back);
    horse_back->set_horse(TO);
    horse_back->halt_horse();

    horse_flea = clone_object(HORSE_FLEA);
    horse_flea -> set_horse(TO);

    add_item("rider", "@@my_rider");
}

public string
my_long()
{
    string s = "";

    s += LANG_ADDART(query_adj()) + " ";
    s += lower_case(query_name()) + ".";
    if (strlen(long_desc)) s += " " + long_desc;
    if (rider) {
	s += " ";
	if (rider == TP) {
	    s += "You are";
	} else {
	    s += process_string(QCTNAME(rider)) + " is";
	}
	s += " riding it.";
    }
    return (capitalize(s) + "\n");
}

public string
my_rider()
{
    if (!rider) return "There is no rider.\n";
    return rider->long();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (horse_flea) horse_flea->move_living("M", to);
    if (rider && horse_back) horse_back->get_desc("l", rider, to);
    if (!rider || !(rider->query_npc())) return;
    if (!to->query_prop(NPC_HORSE_CMD)) return;
    rider->horse_cmd(to, from);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (to->query_prop(RIDE_PROP) ||
	to->query_prop(ROOM_I_INSIDE)==0) return;
    if (rider) rider->catch_msg("You cannot ride there!\n");
    move_living("M", from);
}

public int
name(string str)
{
    string what, pet_name;
    object *ob;

    if (strlen(extra_name)) return 0;

    NF(capitalize(query_verb()) + " what?");
    if (!str) return 0;

    if (sscanf(str, "%s %s", what, pet_name) != 2) return 0;

    ob = FIND_STR_IN_OBJECT(what, ETP);
    if (sizeof(ob)==0 || sizeof(ob) >= 2) return 0;
    if (ob[0] != TO) return 0;

    ob = TP->query_enemy(-1);
    if (member_array(TO, ob) >= 0) return 0;

    if ("/secure/master"->finger_player(lower_case(pet_name))) {
	write("That name cannot be used. Sorry.\n");
	return 1;
    }
    write("You name the "+short()+" to "+capitalize(pet_name)+".\n");
    say(QCTNAME(TP) + " seems to whisper something to " +
	short() + ".\n");
    extra_name = lower_case(pet_name);
    add_name(extra_name);
    named_by = TP;
    if (horse_back) horse_back->add_my_name_item(extra_name);
    return 1;
}

public int
mount(string str)
{
    int sp, mount_lim, tp_ah;
    object *ob;

    NF(capitalize(query_verb()) + " what?");
    if (!str) return 0;

    ob = FIND_STR_IN_OBJECT(str, ETP);
    if (sizeof(ob)==0 || sizeof(ob) >= 2) return 0;
    if (ob[0] != TO) return 0;

    ob = TP->query_enemy(-1);
    NF("The "+short()+" doesn't allow you to mount it.");
    if (member_array(TO, ob) >= 0) return 0;

    if (lower_case(str) == extra_name) {
	mount_lim = 9;
    } else if (strlen(extra_name)) {
	mount_lim = query_stat(SS_DIS);
    } else {
	mount_lim = 12;
    }

    tp_ah = half_ran(TP_AH);

    NF("You try but fail to mount the "+short()+".");
    if (tp_ah < mount_lim) return 0;

    sp = query_running();
    if (sp) {
        NF("The "+short()+" is moving too fast for you!");
        if (5*sp + mount_lim + 6 > tp_ah) return 0;
    }

    if (rider) {
	TP->catch_msg(QCTNAME(rider) + " is already mounted on the " +
		      short() + ".\n");
        return 1;
    }

    write("You mount the " + short() + ".\n");
    say(QCTNAME(TP) + " mounts the " + short() + ".\n");
    set_rider(TP);
    if (TP->move_living("M", query_room(), 1)) {
	write("You fell of the "+short()+".\n");
	say(QCTNAME(TP) + " fell of the "+short()+".\n");
	set_rider(0);
	return 1;
    }
    say(QCTNAME(TP) + " mounts the " + short() + ".\n");
    return 1;
}

public int
feed(string str)
{
    int i, sp, feed_lim, tp_ah;
    object *ob, food;
    string s1, s2;

    NF(capitalize(query_verb()) + " who with what?");
    if (!str) return 0;
    if (sscanf(str, "%s with %s", s1, s2) != 2) return 0;
    
    ob = FIND_STR_IN_OBJECT(s1, ETP);
    if (sizeof(ob)==0 || sizeof(ob) >= 2) return 0;
    if (ob[0] != TO) return 0;

    ob = TP->query_enemy(-1);
    NF("The "+short()+" doesn't allow you to feed it.");
    if (member_array(TO, ob) >= 0) return 0;

    ob = FIND_STR_IN_OBJECT(s2, TP);
    ob = filter(ob, "food_filter", TO);
    NF(capitalize(query_verb()) + " who with what?");
    if (sizeof(ob)==0) return 0;
        
    if (lower_case(s1) == extra_name) {
	feed_lim = 9;
    } else if (strlen(extra_name)) {
	feed_lim = query_stat(SS_DIS);
    } else {
	feed_lim = 12;
    }

    tp_ah = half_ran(TP_AH);

    NF("You try but fail to feed the "+short()+".");
    if (tp_ah < feed_lim) return 0;

    sp = query_running();
    if (sp) {
        NF("The "+short()+" is moving too fast for you to feed it!");
        if (5*sp + feed_lim + 6 > tp_ah) return 0;
    }

    write("You feed the " + short() + ".\n");
    say(QCTNAME(TP) + " feeds the " + short() + ".\n");
    for (i=0; i<sizeof(ob); i++) ob[i]->move(ETP);
    command("eat " + s2);
    return 1;
}

public int
food_filter(object ob)
{
    if (ob && function_exists("create_food", ob)) return 1;
    return 0;
}

public void
set_rider(object ob)
{
    rider = ob;
}

public object
query_mounted()
{
    return rider;
}

public object
query_horse_flea()
{
    return horse_flea;
}

public void
do_die(object killer)
{

    if (query_hp() > 0) return;

    horse_back->halt_horse();
    if (rider) {
	rider->catch_msg("Your " + short() +
		      " stumbles to its knees.\n");
        horse_back->fall_off_horse();
    }
    command("emote neighs awefully.");

    ::do_die(killer);
}

public int
half_ran(int i)
{
    if (i==0) return 0;
    return (i + random(i))/2;
}

public string
query_m_out()
{
    int sp;

    sp = query_running();
    if (sp == 1) return "leaves, in walking pace,";
    if (sp == 2) return "slowly trots";
    if (sp == 3) return "trots";
    if (sp == 6) return "gallops";
    return "leaves";
}

public string
query_m_in()
{
    int sp;

    sp = query_running();
    if (sp == 1) return "arrives in walking pace.";
    if (sp == 2) return "arrives in a slow trot.";
    if (sp == 3) return "arrives trotting.";
    if (sp == 6) return "arrives galloping.";
    return "arrives.";
}

public int
query_met(mixed name)
{
    if (rider) return rider->query_met(name);
    return 0;
}

public int
query_brief()
{
    if (rider) {
	if (rider->query_npc()) return 1;
	return rider->query_brief();
    }
    return 0;
}

public int
query_running()
{
    if (!horse_back) return 0;
    return horse_back->query_running();
}

public int
query_whimpy()
{
    if (rider) return rider->query_whimpy();
    return ::query_whimpy();
}

public int
remove_object()
{
    if (horse_back) {
	horse_back->fall_of_horse();
        horse_back->remove_object();
    }
    if (horse_flea) horse_flea->remove_object();
    ::remove_object();
}

public int
query_horse_value()
{
    int price;

    price = 12 * 7 * query_average_stat();

    return price;
}

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    mixed hres;

    hres = ::hit_me(wcpen, dt, attacker, attack_id);
    if (horse_back && rider) {
	if (half_ran(AH(rider)) < 35) horse_back->fall_of_horse();
    }
    return hres;
}

public void
create_horse()
{
    set_adj("non-descript");
    set_short("non-descript horse");
    set_stats(( {1,1,1,1,1,1 }));
    set_skill(SS_DEFENCE, 1);
    set_skill(SS_AWARENESS, 1);
    set_hp(9999);
    set_mana(9999);
    set_fatigue(9999);
}

public string
query_horse_long()
{
    return long_desc;
}

public void
set_horse_long(string str)
{
    long_desc = str;
}

public object
query_named_by()
{
    return named_by;
}

public void
reset_named_by()
{
    if (strlen(extra_name)) {
        remove_name(extra_name);
        extra_name = "";
    }
    if (named_by) named_by = 0;
    set_fatigue(query_max_fatigue());
}

public void
appraise_object(int num)
{
    int max_carry, max_speed, value;
    int i, min_i, max_i;
    int seed, sk, skill;
    string s, *speeds;

    ::appraise_object(num);

    if (!horse_back) return;

    max_carry = horse_back->query_max_weight();
    max_speed = horse_back->query_max_speed();
    value = query_horse_value();
    if (max_speed < 1) max_speed = 1;
    if (max_speed > 3) max_speed = 4;

    if (!num)
	sk = TP->query_skill(SS_APPR_MON);
    else
	sk = num;

    skill = sk;
    if (sk < 10) skill = 10;
    if (sk > 100) skill = 100;
    sscanf(OB_NUM(this_object()), "%d", seed);
    min_i = max_carry*skill/100;
    max_i = max_carry*100/skill;
    i = min_i + (max_i - min_i)*random(101, seed)/100;
    i = i/1000;
    write("It looks as if the "+short()+" could carry about " + i +
	  " kilograms.\n");
    speeds = ({"walk slowly", "slowly trot", "trot", "gallop"});
    if (sk < 20) 
	s = speeds[random(4, seed)];
    else
	s = speeds[max_speed-1];
    write("It seems as if it would be able to " + s + ".\n");
    min_i = value*skill/100;
    max_i = value*100/skill;
    i = min_i + (max_i - min_i)*random(101, seed)/100;
    i = i/144;
    write("You can sell it to a horse dealer for about " + i + 
	  " gold coins.\n");
}

public int
halt(string str)
{
    int sp, halt_lim;
    object *ob;

    NF(capitalize(query_verb()) + " what?");
    if (!str) return 0;

    ob = FIND_STR_IN_OBJECT(str, ETP);
    if (sizeof(ob)==0 || sizeof(ob) >= 2) return 0;
    if (ob[0] != TO) return 0;

    sp = query_running();
    if (!sp) return 0;

    ob = TP->query_enemy(-1);
    NF("The "+short()+" doesn't allow you to halt it.");
    if (member_array(TO, ob) >= 0) return 0;

    if (lower_case(str) == extra_name) {
	halt_lim = 15;
    } else if (strlen(extra_name)) {
	halt_lim = query_stat(SS_DIS);
	if (halt_lim < 40) halt_lim = 40;
    } else {
	halt_lim = 40;
    }

    NF("The "+short()+" is moving too fast for you to halt it!");
    if (3*sp + halt_lim > half_ran(TP_AH)) return 0;

    write("You halt the " + short() + ".\n");
    say(QCTNAME(TP) + " halts the " + short() + ".\n");

    if (horse_back) horse_back->halt_horse();

    return 1;
}
