/* An hourglass */
inherit "/std/container";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define CAMP_DIR      MORTRICIADIR + "camp/"
#define TENT_DIR      CAMP_DIR + "tent/"
#define TO            this_object()
#define ETO           environment(TO)
#define TP            this_player()

#define PERIOD        60

public void sand(object who);

int aid=0, up, down;
object huligan=0;

public void
init()
{
    ::init();
    add_action("do_turn", "turn");
    add_action("do_break", "break");
}

public void
create_container()
{
    set_name("hourglass");
    set_short("small hourglass");
    set_long("@@my_long");
    set_adj("small");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_M_NO_GET, "It is securely fastened in the wall.\n");
    add_prop(OBJ_M_NO_GIVE, "It is securely fastened in the wall.\n");
    add_prop(CONT_I_WEIGHT, 800);
    add_prop(CONT_I_MAX_WEIGHT, 1200);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 900);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
    clone_object(TENT_DIR + "sand")->move(TO);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
    add_item("sand", "It's inside the hourglass.\n");
    up = 0;
    down = PERIOD;
}

public int
do_turn(string what)
{
    mixed *call;

    if (what != "hourglass") return 0;

    if (aid) {
        call = get_alarm(aid);
        remove_alarm(aid);
        down = ftoi(call[2]);
        up = PERIOD - down;
        aid = 0;
    } else {
	up = PERIOD;
	down = 0;
    }
    write("You turn the hourglass.\n");
    say(QCTNAME(TP) + " turns the hourglass.\n");

    aid = set_alarm(itof(up), -1.0, &sand(TP));
    return 1;
}

public void
sand(object who)
{
    if (who && ETO == environment(who))
        who->catch_msg("There is no sand left in the upper segment.\n");
 
    aid = 0;
}

public string
my_long()
{
    int i;
    mixed *call;
    string str;

    str = "It's a rather small hourglass, firmly mounted on the wall. ";

    if (aid == 0) {
	str += "There is no sand left in the upper segment, but " +
	       "a tiny goblin, all dressed in red, sits in the " +
	       "upper chamber waving at you with an iron key. " +
	       "Strange indeed!";
    } else {
        call = get_alarm(aid);
        i = (100*ftoi(call[2]))/PERIOD;
	str += "A thin thread of silvery sand is falling from its " +
	      "upper segment to its lower. ";
        if (i < 10) {
	    str += "There isn't much sand left in the upper segment.";
        }
	if (i >= 10 && i < 42) {
	    str += "Most of the sand is in the lower segment.";
	}
	if (i >= 42 && i <= 58) {
	    str += "There is roughly as much sand left in the upper " +
		   "segment as in the lower.";
	}
	if (i > 58 && i <= 90) {
	    str += "Most of the sand is in the upper segment.";
	}
	if (i > 90) {
	    str += "There is very little sand in the lower segment.";
	}
    }
    return str + "\n";
}

public void
mag_react(object who)
{
    object mag = present("magician", ETO);
    
    if (!who || !present(who, ETO) || !mag) return;
    
    if (mag->query_attack() == TP) return;
    
    mag->command("frown");
    
    if (!CAN_SEE(mag, TP)) return;
    
    if (huligan == TP) {
        if (who->query_alignment() < -20) {
            mag->command("say I warned you, evil " +
                        who->query_race_name() + ".");
            mag->command("kill " + who->query_real_name());
        } else {
            mag->command("curse");
            mag->command("shout Stop that " + who->query_race_name() +
                         ", or I'll put the curse on you next time!");
        }
        huligan = 0;
    } else {
        mag->command("say " + capitalize(who->query_race_name()) +
                     ", I need the hourglass so I strongly advise you " +
                     "not to destroy it. You would regret it.");
        huligan = TP;
    }
}

public int
do_break(string str)
{
    if (!str) return 0;
    if (!id(str)) return 0;
    
    write("You try to break the hourglass, but it's far too " +
          "sturdy.\n");
    say(QCTNAME(TP) + " tries to break the hourglass.\n");
    
    set_alarm(2.0, -1.0, &mag_react(TP));
    return 1;
}
