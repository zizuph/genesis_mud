/* A circular room. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <cmdparse.h>

#include "/d/Terel/common/terel_defs.h"

#define TP              this_player()
#define TO              this_object()
#define HERE(xx)        (xx && present(xx))

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"
#define TENT_DIR        CAMP_DIR + "tent/"

#define NO_OF_RODS 3
#define VISION "You see an ancient king, dressed up in "+\
               "jewelled clothes. He is talking to someone. "+\
               "They seem to stand on some kind of lattice. "+\
               "They begin to argue... a fight is starting... "+\
               "suddenly you see the king fall down... "+\
               "Now you see the face of a young and beautiful "+\
               "woman, she is crying... The vision turns quickly "+\
               "into a wedding painting of a man and a woman, below it you see "+\
               "the letters:  v nc i s     You cannot see all letters "+\
               "as your vision gets weaker..."

object *rods, *snakes;
int has_throne, aid=0;
object other, sitter, ring;

public object find_q_ring(int q_no, object ob);
public void vision(object who);

public void
reset_room()
{
    int i;

    if (has_throne && !HERE(sitter)) has_throne = 0;
    for (i=0; i<NO_OF_RODS; i++) {
        if (rods[i] || snakes[i] || has_throne) continue;
        rods[i] = clone_object(HAUN_DIR + "rod");
        rods[i]->move(TO);
    }
}

public void
init()
{
    ::init();
    add_action("touch", "touch", 0);
    add_action("touch", "get", 0);
    add_action("touch", "take", 0);
    add_action("turn", "turn", 0);
    add_action("turn", "rotate", 0);
    add_action("sit", "sit", 0);
    add_action("rise", "rise", 0);
}

public void
create_room()
{
    set_short("Circular cave");
    set_long("@@my_long");
    add_item(({"walls", "wall"}),
        "The walls seem to be have polished by something. " +
        "It looks as if water is responsible for it, but " +
        "it could equally well be something else.\n"
    );
    add_item(({"stone", "stone wheel", "wheel"}), "@@my_wheel");
    add_item(({"hole"}), "@@my_hole");
    add_cmd_item("hole", "enter", "@@enter_my_hole");
    add_item(({"throne"}), "@@my_throne");
    add_item(({"inscription"}), "@@my_inscription");
    add_cmd_item("inscription", "read", "@@my_inscription");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 90);

    add_exit(HAUN_DIR + "shaft_5", "up", "@@check");

    rods = allocate(NO_OF_RODS);
    snakes = allocate(NO_OF_RODS);

    reset_room();
}

public int
check()
{
    int i;

    i = random(sizeof(NO_OF_RODS));
    if (HERE(snakes[i])) {
        snakes[i]->wiggle(TP);
    }
    return 0;
}

public int
turn(string str)
{
    int i, sum_str;

    notify_fail(capitalize(query_verb()) + " what?\n");
    if (str != "wheel" && str != "stone wheel") return 0;
    for (i=0; i<NO_OF_RODS; i++) {
        if (HERE(snakes[i])) {
            write("The "+snakes[i]->short()+" doesn't allow that.\n");
            return 1;
        }
    }
    for (i=0; i<NO_OF_RODS; i++) {
        if (HERE(rods[i])) {
             write("The "+rods[i]->short()+" locks the wheel.\n");
             return 1;
         }
    }
    sum_str = TP->query_stat(SS_STR);
    if (!other) {
        other = TP;
        set_alarm(6.0, -1.0, "zero_other");
    }
    if (other != TP) sum_str += other->query_stat(SS_STR);
    if (sum_str < 140 || other == TP || !present(other)) {
        write("You alone aren't strong enough to "+query_verb()+
            " the stone wheel.\n");
        say(QCTNAME(TP) + " failed to "+query_verb()+" the stone wheel.\n");
        return 1;
    }
    TP->catch_msg("With the aid of "+QTNAME(other)+" your " +
                  "combined efforts made the wheel to "+
                  query_verb()+".\n");
    other->catch_msg("Due to your previous try to "+query_verb()+
                     " the wheel "+QTNAME(TP)+" managed to do it.\n");
    say(QCTNAME(TP)+" and "+QTNAME(other)+" together managed to " +
        "turn the large wheel.\n", ({TP, other}));
    if (has_throne) {
        has_throne = 0;
        tell_room(TO, "The throne disappears down in the hole.\n");
    } else {
        has_throne = 1;
        tell_room(TO, "A large throne rises up from the hole.\n");
    }
    return 1;
}

public void
zero_other()
{
    other = 0;
}

public int
touch(string str)
{
    int i;
    object *obs;

    if (!str) return 0;
    seteuid(getuid(TO));
    obs = FIND_STR_IN_OBJECT(str, TO);
    if (!sizeof(obs)) return 0;
    for (i=0; i<NO_OF_RODS; i++) {
        if (rods[i] && member_array(rods[i], obs) >= 0) {
            write("As you touch the "+rods[i]->short()+
                  " it turns into a snake!\n");
            say("When "+QTNAME(TP)+" touches the "+short()+
                " it turns into a snake!\n");
            rods[i]->remove_object();
            snakes[i] = clone_object(HAUN_DIR + "snake");
            snakes[i]->move(TO);
            return 1;
        }
    }
    return 0;
}

public string
my_long()
{
    string s;

    s = "You have entered a circular cave. The walls are " +
        "very smooth. There is an opening above you. In the " +
        "middle of the cave a large stone wheel has been " +
        "placed.";
    if (has_throne) s += " An impressive throne stands on the wheel.";
    return s + "\n";
}

public string
my_wheel()
{
    string s;

    s = "The huge stone wheel rests upon some kind of " +
        "support that makes the wheel turnable.";

    if (has_throne) {
        s += " An impressive throne stands on the wheel.";
    } else {
        s += " In the middle of the wheel there is large hole.";
    }
    return s+ "\n";
}

public string
my_hole()
{
    string s;

    if (has_throne) {
        s = "The only hole you can see is the opening in the ceiling " +
            "of the cave, through which you entered.";
    } else {
        s = "The hole in the wheel looks dark and you can't " +
            "see anything in it.";
    }
    return s + "\n";
}

public string
enter_my_hole()
{
    string s;

    if (has_throne) {
        s = "What ?";
    } else {
        s = "You don't dare to enter the hole, since you realise " +
            "it would be like comitting suicide.";
    }
    return s + "\n";
}

public string
my_throne()
{
    string s;

    if (has_throne) {
        s = "The magnificient throne is made of some black " +
            "material, probably of vulcanic origin. " +
            "It's very smooth, apart from an inscription on " +
            "its back.";
        if (HERE(sitter)) s += " "+process_string(QCTNAME(sitter))+
            " is sitting in it.";
    } else {
        s = "What ?";
    }
    return s + "\n";
}

public string
my_inscription()
{
    string s;

    if (has_throne) {
        s = "It looks like a royal symbol.";
    } else {
        s = "What ?";
    }
    return s + "\n";
}

public int
sit(string str)
{
    if (!has_throne) return 0;
    notify_fail("Sit where?\n");
    if (str != "throne" && str != "on throne") return 0;
    if (HERE(sitter)) {
        TP->catch_msg("The throne is already occupied by "+
                      QTNAME(sitter)+".\n");
        return 1;
    }
    sitter = TP;
    write("You sit down in the throne.\n");
    say(QCTNAME(TP) + " sits down in the throne.\n");
    ring = find_q_ring(7, TP);
    if (ring && ring->query_prop("q_step") == 0 && aid == 0)
        aid = set_alarm(25.0, -1.0, &vision(TP));
    return 1;
}

public int
rise()
{
    if (!has_throne || TP != sitter) return 0;
    write("You rise from the throne.\n");
    say(QCTNAME(TP)+ " rises from the throne.\n");
    if (find_q_ring(7, TP) && aid) {
        remove_alarm(aid);
        aid = 0;
    }
    sitter = 0;
    return 1;
}

public object
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
vision(object who)
{
    aid = 0;
    if (!HERE(who) || who != sitter) return;
    who->catch_msg("You feel the presence of someone...\n");
    who->catch_msg("A vision begins to form in your mind.\n");
    who->catch_msg(VISION + "\n");
    who->catch_msg("The vision disappear.\n");
    if (ring) ring->change_prop("q_step", 1);
}
