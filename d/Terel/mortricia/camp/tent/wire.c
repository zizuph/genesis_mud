/* A wire room. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#include "/d/Terel/common/terel_defs.h"

#define TP              this_player()
#define TO              this_object()
#define ETP             environment(TP)

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define TENT_DIR        CAMP_DIR + "tent/"
#define HARD_TO_WALK    35

public object check_short(string sh_desc, object ob);

public void
init()
{
    ::init();
    add_action("do_dance", "dance");
    add_action("do_push", "push");
    add_action("do_push", "kick");
    add_action("do_push", "tackle");
}

public void
create_room()
{
    set_short("@@my_short");
    set_long("@@my_long");
    
    add_item(({"wire"}), "You feel quite uneasy standing on it.\n");
    add_item(({"manege"}), "It's some thirty feet below, " +
                           "but don't look down!.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "mast1", "northwest", "@@balance");
    add_exit(TENT_DIR + "mast2", "southeast", "@@balance");
}

public string
my_short()
{
    int tp_dis, wrod;
    string str;
    object rod;

    tp_dis = TP->query_stat(SS_DIS);
    tp_dis = tp_dis + TP->query_skill(SS_ACROBAT);
    rod = present("rod", TP);
    if (rod) wrod = rod->query_wielded();
    if (wrod) tp_dis = 2*tp_dis + 10;
    if (tp_dis > 45) {
        str = "Balancing on the wire";
    } else {
        str = "Clinging on to the wire";
    }
    return str;
}

public string
my_long()
{
    int tp_dis, wrod;
    string str;
    object rod;

    tp_dis = TP->query_stat(SS_DIS);
    tp_dis = tp_dis + TP->query_skill(SS_ACROBAT);
    rod = present("rod", TP);
    if (rod) wrod = rod->query_wielded();
    if (wrod) tp_dis = 2*tp_dis + 10;
    if (tp_dis > 45) {
        str = "You are now balancing on the wire. " +
              "All in the audience follow your manoeuvres.";
    } else {
        str = "You are desperately clinging on to the wire. " +
              "You wonder how to reach one of the masts. " +
              "What a dilemma!";
    }
    if (TP->query_wiz_level()) {
       str = "You are now balancing on the wire.";
    }
    return str + "\n";
}

public int
balance()
{
    int tp_dis, tp_hp;
    int drunk;
    int dam, wrod;
    object rod;

    drunk = TP -> query_intoxicated();

    if (TP->query_wiz_level() && drunk < 20) {
        if (!(TP->query_invis())) {
            write(
            "The audience is quite amazed to see a wizard " +
            "balancing on the wire. However, being impressed about " +
            "your performance they give you a round of applause.\n"
            );
        } else {
            write(
            "You are balancing on the wire. " +
            "However, since you are invisible " +
            "your performance remain unnoticed by the audience.\n"
            );
        }
        return 0;
    }

    tp_dis = TP->query_stat(SS_DIS) + TP->query_skill(SS_ACROBAT);
    rod = present("rod", TP);
    if (rod) wrod = rod->query_wielded();
    if (wrod) tp_dis = 2*tp_dis + 10;

    if (tp_dis > HARD_TO_WALK && drunk < 2) {
        write(
             "You feel that you have, at least some, of the " +
             "capabilities necessary to perform as a tight-rope " +
             "dancer. The audience applauds cheerfully.\n"
        );
        return 0;
    }
    write(
        "You now realise that walking out on the wire was far " +
        "above your capability and will most certainly result " +
        "in a severe accident, perhaps even your death. The " +
        "audience gasps as you try to proceed to the mast. " +
        "They smell blood.\n"
    );
    tp_hp = TP->query_max_hp();
    write("You slip, scream, and start to fall down...\n");
    TP->move_living("down with a scream",
                      TENT_DIR + "manege");
   
    dam = (tp_hp/3)+(5*drunk);
    TP->reduce_hit_point(dam);
    TP->do_die(ETP);
    return 1;
}

public int
do_dance()
{
    int tp_hp, drunk, dam;
    int wrod;
    object ring, rod, roses;
    string str;

    write("You start to dance on the wire!\n");
    say(QCTNAME(TP) + " starts to dance on the wire.\n");
    rod = present("rod", TP);
    if (rod) wrod = rod->query_wielded();
    tp_hp = TP->query_max_hp();
    drunk = TP->query_intoxicated();
    if (!wrod || drunk > 3) {
	str = "";
	if (!wrod) str += "Maybe you should use a balancing rod? ";
	if (drunk>3) str += "Being drunk isn't good for the balance!\n";
        str += "You slip, scream, and start to fall down...\n";
        write(str);
	say(QCTNAME(TP) + " slips while dancing!\n");
        TP->move_living("down with a scream",
                          TENT_DIR + "manege");
        dam = (tp_hp/3)+(5*drunk);
	if (TP->query_npc()) dam = tp_hp + 5;
        TP->reduce_hit_point(dam);
        TP->do_die(ETP);
	return 1;
    }
    write("You dance as if you were a real tight-rope dancer.\n");
    say(QCTNAME(TP)+" whirls and twirls on the wire.\n");
    ring = check_short("iron ring", TP);
    roses = check_short("bouquet of roses", TP);
    if (ring && !roses) {
        write("Someone in the audience manages to throw " +
	      "a bouqet of flowers up to you.\n");
        roses = clone_object(TENT_DIR+"roses");
        roses->add_prop("q_solver", TP->query_name());
        roses->move(TP);
    }
    return 1;
}

public object
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

public int
do_push(string whom)
{
    object rod, dancer, ob;
    string verb;

    verb = query_verb();
    notify_fail(capitalize(verb) + " whom?\n");
    if (!stringp(whom))
        return 0;
    if (!parse_command(whom, ETP, "%o", ob))
        return 0;
    dancer = present("dancer", TO);
    if (dancer != ob)
        return 0;
    write(
	"You "+verb+" the tight-rope dancer, and she loses her " +
	"balance for a moment.\n"
    );
    rod = present("rod", dancer);
    if (rod) dancer->command("drop rod");
    return 1;
}

public void
tell_down(object ob)
{
    if (!ob) return;
    tell_room(TO, "The "+ob->short()+" falls down to the manege.\n");
    tell_room(TENT_DIR + "manege", capitalize(LANG_ADDART(ob->short())) +
              " falls down to the floor, probably dropped by someone " +
              "up on the wire.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (living(ob)) return;
    ob->move(TENT_DIR + "manege");
    set_alarm(1.0, -1.0, &tell_down(ob));
}
