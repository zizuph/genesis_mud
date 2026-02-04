/* A carriage. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <cmdparse.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define CAMP_DIR        MORTRICIADIR + "camp/"

object check_short(string sh_desc, object ob);
object check_sh(string sh_desc, object ob);

init()
{
    add_action("do_practise", "practise");
    add_action("do_practise", "juggle");
    ::init();
}

void
reset_room()
{
    object red_ball, blue_ball, green_ball;
    object bag;
    object red_cone, blue_cone, green_cone;

    if (!present("ball", TO)) {
        red_ball = clone_object(CAMP_DIR + "ball");
        red_ball -> set_short("red ball");
        red_ball -> set_adj("red");
        red_ball -> move(TO);
        blue_ball = clone_object(CAMP_DIR + "ball");
        blue_ball -> set_short("blue ball");
        blue_ball -> set_adj("blue");
        blue_ball -> move(TO);
        green_ball = clone_object(CAMP_DIR + "ball");
        green_ball -> set_short("green ball");
        green_ball -> set_adj("green");
        green_ball -> move(TO);
    }
    bag = present("bag", TO);
    if (!bag) {
        bag = clone_object(CAMP_DIR + "bag");
        bag -> move(TO);
    }
    if (!present("cone", bag)) {
        red_cone = clone_object(CAMP_DIR + "cone");
        red_cone -> set_short("red cone");
        red_cone -> set_adj("red");
        red_cone -> move(bag);
        blue_cone = clone_object(CAMP_DIR + "cone");
        blue_cone -> set_short("blue cone");
        blue_cone -> set_adj("blue");
        blue_cone -> move(bag);
        green_cone = clone_object(CAMP_DIR + "cone");
        green_cone -> set_short("green cone");
        green_cone -> set_adj("green");
        green_cone -> move(bag);
    }
}

void
create_room()
{
    set_short("Juggler's carriage");
    set_long(BSN(
	"This is the carriage where the juggler lives, and " +
	"where he practises his juggling."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CAMP_DIR + "camp_04", "south", 0);

    reset_room();
}

do_practise(string what)
{
    int i, j, j_val, intox;
    object *obs, ring, ob1, ob2, ob3;
    string str, str1, str2, verb;

    i = -1;
    verb = capitalize(query_verb());
    if (!what) {
	write(verb + " with what?\n");
	return 1;
    }
    if (sscanf(what, "with %s", str) !=1) {
	write(verb + " with what?\n");
	return 1;
    }
    if (str == "balls" || str == "ball") {
	i = 0;
	if (ob1 = check_sh("red ball", TP)) i++;
	if (ob2 = check_sh("blue ball", TP)) i++;
	if (ob3 = check_sh("green ball", TP)) i++;
	str = "ball";
    }
    if (str == "cones" || str == "cone") {
	i = 0;
	if (ob1 = check_sh("red cone", TP)) i++;
	if (ob2 = check_sh("blue cone", TP)) i++;
	if (ob3 = check_sh("green cone", TP)) i++;
	str = "cone";
    }
    if (i < 0) {
	obs = FIND_STR_IN_OBJECT(str, TP);
	if (sizeof(obs) <= 0) {
	    write(verb + " with what?\n");
	    return 1;
	}
	str = "";
	for(j=0; j<sizeof(obs); j++) {
	    str = str + " " + obs[j]->short();
	    if (j <= sizeof(obs)-3) str += ",";
	    if (j == sizeof(obs)-2) str += " and";
	}
	write(BSN("You juggle with:"+str+"."));
	say(QCTNAME(TP) + " juggles with:"+str+".\n");
	if (TP->query_skill(SS_ACROBAT) < 10 + random(5)) {
	    for(j=0; j<sizeof(obs); j++) {
		obs[j]->move(TO);
	    }
	    write("Oops! You drop some of it!\n");
	    say(QCTNAME(TP) + " drops some of the stuff.\n");
	}
	return 1;
    }
    if (i == 0) {
	write("Yes, yes, but you do not have them!\n");
	return 1;
    }
    if (i == 1) str1 = str;
    if (i == 2) str1 = "two "   + str + "s";
    if (i == 3) str1 = "three " + str + "s";
    write("You practise juggling with the "+str1+".\n");
    say(QCTNAME(TP) + " practises juggling with the "+str1+".\n");
    ring = check_short("iron ring", TP);
    if (i == 3 && ring) {
	str2 = str + "_juggling";
	j_val = ring -> query_prop(str2);
	j_val++;
	intox = TP->query_intoxicated() > 3;
	if (intox) j_val--;
	ring -> add_prop(str2, j_val);
	if (j_val <= 1) {
	    write("You drop all three "+str+"s.\n");
	    if (intox) {
	        write("You better wait until you are sober!\n");
	    } else {
	        write("Next time you will do better!\n");
	    }
	    say(QCTNAME(TP) + " drops all three "+str+"s.\n");
	    ob1 -> move(TO);
	    ob2 -> move(TO);
	    ob3 -> move(TO);
	}
	if (j_val == 2) {
	    write("You drop two "+str+"s.\n");
	    say(QCTNAME(TP) + " drops two "+str+"s.\n");
	    ob3 -> move(TO);
	    ob2 -> move(TO);
	}
	if (j_val == 3) {
	    write("You drop one "+str+".\n");
	    say(QCTNAME(TP) + " drops one "+str+".\n");
	    ob1 -> move(TO);
	}
	if (j_val >= 4) {
	    write("You are a skillful " + str + "-juggler!\n");
	    write("You don't need to practise that anymore!\n");
	    say(QCTNAME(TP) + " is a skillful "+str+"-juggler.\n");
	}
    }
    return 1;
}

object
check_short(string sh_desc, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_short() == sh_desc &&
	    ob_arr[i]->query_prop("q_solver") == ob->query_name()) {
	    r_ob = ob_arr[i];
	}
    }
    return r_ob;
}

object
check_sh(string sh_desc, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_short() == sh_desc) {
	    r_ob = ob_arr[i];
	}
    }
    return r_ob;
}
