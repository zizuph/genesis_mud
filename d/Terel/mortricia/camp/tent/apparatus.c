/* A weird apparatus */
inherit "/std/container";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define NF(xx)        notify_fail(xx)
#define TO            this_object()
#define TP            this_player()

public object check_content(object ob);
public void boil_off(object who);
public void cool_down();
public void press_left(object who);
public void press_middle(object who);
public void press_right(object who);

int filled, hot;

public void
init()
{
    ::init();
    add_action("do_press", "press");
    add_action("do_press", "push");
    add_action("do_touch", "touch");
    add_action("do_touch", "get");
    add_action("do_touch", "take");
}

public void
create_container()
{
    set_name("apparatus");
    set_short("weird apparatus");
    set_pshort("weird apparatus");
    set_long("@@my_long");
    set_adj("weird");
    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 20000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "It's far too heavy to take!\n");

    add_item(({"buttons", "button", "labels"}), "@@my_buttons");
    filled = 0;
    hot = 0;
}

public string
my_long()
{
    int tp_smart;
    string str;

    tp_smart = (TP->query_stat(SS_WIS) + TP->query_stat(SS_INT))/2;
    if (tp_smart >= 0) {
	str = "It's a weird apparatus. " +
	      "It's made out of bronze, that's about all you can " +
	      "figure out with your present brain capabilities.";
    }
    if (tp_smart > 20) {
	str = "It's a weird apparatus. " +
	      "Most of it is made of bronze. " +
	      "You also notice three glass pipes that connect " +
	      "a large bronze sphere at the bottom with a smaller " +
	      "one in the top. You have no idea how this thing works, " +
	      "and even less understanding about its use.";
    }
    if (tp_smart > 30) {
	str = "It's a weird apparatus. " +
	      "Most of it is made of bronze. " +
	      "There are three glass pipes that connect " +
	      "a large bronze sphere at the bottom with a smaller " +
	      "one in the top. Moreover, there are three buttons " +
	      "on the large bronze sphere. You don't know the " +
	      "purpose of this thing, although by examining the " +
	      "buttons you may figure out how to handle it.";
    }
    if (tp_smart > 50) {
	str = "It's a weird apparatus. " +
	      "Most of it is made of bronze. " +
	      "There are three glass pipes that connect " +
	      "a large bronze sphere at the bottom with a smaller " +
	      "one in the top. Moreover, there are three buttons " +
	      "on the large bronze sphere. " +
	      "By examining the " +
	      "buttons you may figure out how to handle it. You " +
	      "better ask the magician about its purpose.";
    }
    return str + "\n";
}

public string
my_buttons()
{
    int tp_smart;
    string str;

    str = "Yes, there are buttons on the apparatus, but you can't \n" +
	  "understand the labels.\n";
    tp_smart = (TP->query_stat(SS_WIS) + TP->query_stat(SS_INT) +
		TP->query_skill(SS_LANGUAGE) )/3;
    if (tp_smart > 30) {
	str = "The three buttons are labeled as:\n" +
	      "    left button:   fill large sphere with water\n" +
	      "    middle button: heat the water in the sphere\n" +
	      "    right button:  transform (WARNING! This is " +
					    "dangerous)\n\n";
    }
    say(QCTNAME(TP) + " examines the buttons on the apparatus.\n");
    return str;
}

public int
do_press(string what)
{
    if (what == "button" || what == "buttons") {
	write("Which one? Left, middle, or right?\n");
	return 1;
    }
    if (what == "left" || what == "left button") {
	write("You press the left button.\n");
	set_alarm(5.0, -1.0, &press_left(TP));
	return 1;
    }
    if (what == "middle" || what == "middle button") {
	write("You press the middle button.\n");
	set_alarm(15.0, -1.0, &press_middle(TP));
	return 1;
    }
    if (what == "right" || what == "right button") {
	write("You press the right button.\n");
	set_alarm(10.0, -1.0, &press_right(TP));
	return 1;
    }
    NF(capitalize(query_verb()) + " what?\n");
    return 0;
}

public int
do_touch(string what)
{
    string self;

    NF(capitalize(query_verb()) + " what?\n");
    if (what != "apparatus") return 0;

    if (hot) {
       self = TP->query_possessive();
       if (self == "his") self = "him";
       write("Ouch! It's VERY hot. You hurt yourself!\n");
       say(QCTNAME(TP) + " burned " + self + "self.\n");
       TP->reduce_hit_point(20);
       TP->do_die(TO);
    } else {
       write("It feels a bit warm but that's all.\n");
    }
    return 1;
}

public void
press_left(object who)
{
    object room;

    if (filled) return;
    room = environment(TO);
    tell_room(room, "You hear some noise from the apparatus.\n");
    if (who && room == environment(who)) {
        tell_object(who, "The apparatus is filled with water.\n");
        if (hot) {
	    tell_object(who, "The water cools down the apparatus.\n");
	}
    }
    hot = 0;
    filled = 1;
    return;
}

public void
press_middle(object who)
{
    object room;

    if (hot) return;
    hot = 1;
    room = environment(TO);
    if (filled) {
        tell_room(room, "The water is boiling in the apparatus.\n");
        set_alarm(60.0, -1.0, &boil_off(who));
    }
    set_alarm(180.0, -1.0, &cool_down(who));
    return;
}

public void
press_right(object who)
{
    object room, mag, ring;

    room = environment(TO);
    tell_room(room, "A terrible noise is coming from the apparatus.\n");
    mag = present("magician", room);
    if (mag) mag->command("grin");
    tell_room(room, "A light flash emerges from the apparatus.\n");
    ring = check_content(who);
    if (ring && hot && filled) {
	if (ring->query_prop("q_number") == 6) {
	    ring->set_short("gold ring");
	    ring->set_adj("gold");
	    ring->inscript("Fetch the magician's treasure.");
	} else {
	    ring->set_short("gold ring");
	    ring->set_adj("gold");
	    ring->inscript("Fetch  he  a  c a  s t      e ");
	    ring->remove_prop("q_solver");
	    ring->remove_prop("q_number");
	}
	if (mag) mag->command("shout It worked!");
        if (who && room == environment(who)) {
	    tell_object(who, "The ring has been transformed.\n");
	    tell_object(who, "You are hit by the flash.\n");
	    if (mag) mag -> command("shout You fool!");
	    tell_object(who, "You are burned, quite seriously, by " +
			     "the flash.\n");
	    who->reduce_hit_point(1500);
	    who->do_die(TO);
	}
    } else {
        if (who && room == environment(who)) {
	    tell_object(who, "You are hit by the flash.\n");
	    if (mag) mag->command("shout You fool!");
	    tell_object(who, "You are burned by " +
			     "the flash.\n");
	    who->reduce_hit_point(100);
	    who->do_die(TO);
	}
    }
    if (filled) filled=0;
    return;
}

public void
boil_off(object who)
{
    object room;

    room = environment(TO);
    tell_room(room, "Steam is coming from the apparatus.\n");
    if (who && room == environment(who)) {
        tell_object(who, "The water has boiled off.\n");
    }
    filled = 0;
}

public void
cool_down()
{
    hot = 0;
}

public object
check_content(object ob)
{
    int i;
    object *ob_arr, r_ob=0;

    r_ob = 0;
    ob_arr = all_inventory(TO);
    for (i=0; i<sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_short() == "iron ring" &&
	    ob_arr[i]->query_prop("q_solver") ) {
	    r_ob = ob_arr[i];
	} else {
	    ob_arr[i]->remove_object();
	}
    }
    return r_ob;
}
