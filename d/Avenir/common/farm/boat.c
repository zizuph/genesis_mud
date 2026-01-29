#pragma strict_types
#include <composite.h>
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>


inherit "/std/container";

string desc_lake();
string desc_close_to_reed(string str);
int move_the_boat(string str);
int check_light();
string query_action();
int bite_alarm;
int bob_alarm;
void do_bob();
void do_bite();
int is_anchored;
int sack_alarm;
int drift_alarm;
int have_sack;
void fish_for_sack(object ob);
void fish_for_sack2(object ob);

void
create_container()
{
    set_name("rowing boat");
    add_name("boat");
    add_name("_boat");
    set_short("small rowing boat");
    set_long("@@desc_long");
    add_item(({"view","lake"}),"@@desc_lake");
    add_prop(CONT_I_RIGID, 0);          // Fixed volume
    add_prop(CONT_I_TRANSP, 1);         // Transparent
    add_prop(CONT_I_VOLUME, 50000);  // 50 l
    add_prop(CONT_I_WEIGHT, 1000000);    // Boat weights 1000Kg
    add_prop(CONT_I_MAX_WEIGHT, 3000000);
    add_prop(CONT_I_MAX_VOLUME, 4000000);
    add_prop(ROOM_I_LIGHT, check_light());
    add_item(({"wood", "bare wood" }),
        "The wood itself is solid and sound. The paint has flaked off, "+
        "but this doesn't effect the sea-worthiness of the boat.\n");
    add_item(({"paint", "blue paint", "white paint", "white trim"}),
        "The paint, or what remains of it, is blue and white.\n");
    add_item("rock","@@desc_rock");
    add_item("tower","@@desc_tower");
    add_item("mill","@@desc_mill");
    add_item("house","@@desc_house");
    add_item("reed","@@desc_reed");
    add_item("water","@@desc_water");
    add_item("bottom","@@desc_bottom");
    add_item(({"oak","trees","oaks"}), "@@desc_oaks");
    add_item("shores", "@@desc_shores");
    add_item(({"sunken boat","wreck"}),"@@desc_sunken_boat");
    add_item("oilskin sack","@@desc_sack");
    add_item("stem","The wooden stem has scratches and cracks in it. " +
        "Most likely from poor seamanship and carelessness when " +
        "fastening the boat in her place in the boathouse.\n");
    add_item("stern","The stern looks the same as the rest " +
        "of the boat. Flaked off paint and lack of maintenance.\n" +
        "You lean over and look at it from the outside and read " +
        "painted in white:\n" +
        " -- The Lily --.\n");
    setuid();
    seteuid(getuid());
}

void
init()
{
    ::init();
    add_action("do_row","row");
    add_action("do_enter","enter");
    add_action("do_enter", "board");
    add_action("do_leave","leave");
    add_action("do_leave","disembark");
    add_action("do_leave", "dis");
    add_action("do_look","look");
    add_action("do_look","l");
    add_action("do_look","glance");
    add_action("do_fish","fish");
    add_action("do_anchor","anchor");
    add_action("pull_anchor","pull");
    add_action("pull_anchor","raise");
    add_action("do_rock","rock");
    add_action("get_sack","get");
    add_action("search_far_away_items","search");
}

string
desc_long()
{
    string text = "This is a small and steady rowing boat. It was once "+
        "painted blue with white trim, but most of the paint has "+
        "flaked off, exposing the bare wood from stem to stern. " +
        "It has seen better days when it comes to maintenance, "+
        "but it was soundly constructed, so it should be secure " +
        "as long as it is not overloaded with too many passengers.";

    if (is_anchored)
    {
        text += " Right now the boat is anchored. You see the anchor " +
            "chain stretch out now and then when the breeze pulls the " +
            "boat in random directions, but the anchor easily holds " +
            "the boat in place.";
    }
    return text + "\n";
}

int
get_sack(string str)
{

    if ((str) && (str == "oilskin sack"))
    {
        write("It is impossible to get the sack from here. " +
            "You better try another manouver.\n");
        return 1;
    }
    return 0;
}


int
do_anchor(string str)
{
    object grappling;

    if ((str == "") || (!(str)))
    {
        write("Anchor the boat with what?\n");
        return 1;
    }

    if ((str == "boat with grappling") || (str == "boat")
        || (str == "boat with iron") || (str == "boat with grappling iron")
        || (str == "the boat") || (str == "the boat with grappling"))
    {
        if (TO->query_anchored())
        {
            write("The boat is already anchored.\n");
            return 1;
        }

        grappling = (present("grappling", TP));
        if (!(grappling))
        {
            write("You dont have anything fitting to anchor " +
                "the boat with!\n");
            return 1;
        }

        if (!(grappling->query_tied()))
        {
            if (!(grappling->query_prop("_tried_to_anchor")))
            {
                write("You could try, but if you drop the grappling " +
                    "overboard without any means to secure it to the " +
                    "boat, it would be gone forever.\n");
                grappling->add_prop("_tried_to_anchor", 1);
                return 1;
            }
            write("You try to anchor the boat with the iron grappling " +
                "without any means to secure it to the boat. With a plop " +
                "it disappears below the surface without ever to be seen " +
                "again.\n");
            say(QCTNAME(TP) + " drops a grappling into the water. With " +
                "a plop it disappears below the surface.\n");
            grappling->remove_object();
            return 1;
        }
        write("You secure the chain to the boat and throw the grappling " +
            "into the water. With a plop it disappears below " +
            "the surface.\n");
        say(QCTNAME(TP) + " fastens a chain to the boat and drops a " +
            "grappling into the water. With a plop it disappears below " +
            "the surface.\n");
        tell_room(TO, "As soon the grappling disappears the chain " +
            "stretches out. You feel a small jerk and then you realise " +
            "that it works fine. The boat is safely anchored at this " +
            "location of the lake.\n");
        grappling->remove_object();
        is_anchored = 1;
        return 1;
    }
    write("What do you want to anchor? The boat?.\n");
    return 1;
}

int
pull_anchor(string str)
{
    object grappling;

    if (!str || !strlen(str))
    {
        return 0;
    }

    if ((str == "anchor") || (str == "chain")
        || (str == "grappling") || (str == "up the anchor")
        || (str == "up anchor") || (str == "up grappling"))
    {
        if (!(is_anchored))
    {
            write("The boat isnt anchored.\n");
            return 1;
        }
        write("You take a good grip of the iron chain and start " +
            "to pull. After a short while the grappling appears " +
            "over the rail and lands with a slam in bottom of the " +
            "boat. Now its possible to row again.\n");
        say(QCTNAME(TP) + " bends down and start to pull the iron anchor " +
            "chain. After a short while it appears over the railing and " +
            "with a slam hitst the bottom of the boat. Now its possible " +
            "to row again.\n");
        (ENV(TO))->start_drift(TO);
        is_anchored = 0;
        grappling = clone_object(THIS_DIR + "obj/grappling");
        grappling->tie_chain();
        grappling->move(TO, 1);
        return 1;
    }
    return 0;
}

int
do_fish(string str)
{
    int i;
    object pole, *all;
    float time_to_bite;

    if ((str == "") || (!(str)))
    {
        write("Fish with what?\n");
        return 1;
    }

    if ((str == "with pole") || (str == "with fishing pole")
        || (str == "with hook") || (str == "with maggot")
        || (str == "with bait"))
    {
        pole = (present("_fish_pole", this_player()));
        if (!(pole))
        {
            write("You dont have any pole to fish with!\n");
            return 1;
        }

        if (!(pole)->query_prop("_pole_is_ready"))
        {
            write("The pole isnt ready to fish with. You need " +
                "a bait.\n");
            return 1;
        }

        if ((ENV(TO))->query_prop(BH))
        {
            write("You can not fish in here.\n");
            return 1;
        }

        if (this_player()->query_prop("_is_fishing"))
        {
            write("You are already fishing.\n");
            return 1;
        }

        all = FILTER_PLAYERS(all_inventory((this_object())));
        for (i=0; i<sizeof(all); i++)
        {
            if (all[i]->query_prop("_is_fishing"))
            {
                write("You shouldnt try to fish while someone " +
                    "else is fishing.\n");
                return 1;
            }
        }
        write("You throw the float and the hooked maggot " +
            "into the water. With a plop the maggot disappears below " +
            "the surface while the float silently starts to bob " +
            "on the waves.\n");
        say(QCTNAME(TP) + " throws a float and a hooked maggot " +
            "into the water. With a plop the maggot disappears below " +
            "the surface while the float silently starts to bob " +
            "on the waves.\n");
        TP->add_prop("_is_fishing", 1);
        time_to_bite = (20.0 + rnd()*200.0);
        if (TP->query_wiz_level())
        {
            write("\nWizinfo: "+ ftoi(time_to_bite) + " seconds to " +
                "bite. Pull up and redo if you want to reduce the " +
                "time to catch the fish.\n");
        }
        bite_alarm = set_alarm(time_to_bite, 0.0, &do_bite());
        bob_alarm = set_alarm(1.0, 10.0, &do_bob());
        return 1;
    }

        if ((str == "for oilskin sack") || (str == "for bag")
        || (str == "for sack") || (str == "sack")
        || (str == "oilskin sack"))
    {
        pole = (present("_fish_pole", TP));
        if (!(pole))
        {
            write("You dont have anything to fish with!\n");
            return 1;
        }
        if (!(ENV(TO))->query_prop(X))  // Check if lake middle
        {
            write("Fish for what?\n");
            return 1;
        }
        if (!(ENV(TO))->query_sack())  // Check if sack is there
        {
            write("Fish for what?\n");
            return 1;
        }

    if (this_player()->query_prop("_fishing_for_sack"))
    {
        write("You are already fishing for it.\n");
        return 1;
    }
        TP->add_prop("_fishing_for_sack", 1);
        sack_alarm = set_alarm(3.0, 0.0, &fish_for_sack(TP));
        write("You try to catch the sack with the hook tied to " +
            "your fishingpole.\n");
        say(QCTNAME(TP) + " throws the hook and line into the water. " +
            "With a plop they disappear below the surface. You see "
            +TP->query_objective()+ " stare at something down " +
            "below while trying to manouver the hook in position.\n");
        return 1;
    }
    return 0;
}

void
fish_for_sack(object fisher)
{
    int i = random(4);

    if (!(ENV(TO))->query_prop(X))
    {
       fisher->catch_msg("You stop your attempt to fish for " +
           "the sack as you seem to be out of position.\n");
       fisher->remove_prop("_fishing_for_sack");
       return;
    }


    switch(i)
    {
        case 0:
        {
            fisher->catch_msg("You can clearly see the hook in " +
                "the dark water and you almost manage to catch " +
                "the sack before the current gets the hook and " +
                "drift it away from the boat on the bottom.\n");
            fisher->command("smile expect");
            sack_alarm = set_alarm(6.0, 0.0, &fish_for_sack(fisher));
            return;
        }

        case 1:
        {
            fisher->catch_msg("You move the pole over the surface " +
                "in an attempt to hook the sack. You feel you " +
                "might be lucky to catch it soon.\n");
            fisher->command("");
            sack_alarm = set_alarm(6.0, 0.0, &fish_for_sack(fisher));
            return;
        }

        case 2:
        {
            fisher->catch_msg("A slight breeze comes in from north " +
                "curling the water so you cannot see the sunken " +
                "boat temporarily. You await the breeze to pass.\n");
            fisher->command("grumble irrit");
            sack_alarm = set_alarm(6.0, 0.0, &fish_for_sack(fisher));
            return;
        }

        case 3:
        {
            fisher->catch_msg("You manage to get the hook in position " +
                "under a rope that is tied around the sack. With a jerk " +
                "you pull up the hooked sack.\n");
            fisher->command("smile expect");
            sack_alarm = set_alarm(6.0, 0.0, &fish_for_sack2(fisher));
            return;
        }
    }
    return;
}

void
fish_for_sack2(object fisher)
{
    object sack, key, horseshoe;

    if (!(ENV(TO))->query_prop(X))
    {
   fisher->catch_msg("Suddenly you feel a jerk in the line " +
       "and the weight is gone. The hook must have lost its " +
       "grip of the sack.\n");
   fisher->remove_prop("_fishing_for_sack");
   return;
    }

    if (!(is_anchored))
    {
        fisher->catch_msg("Suddenly you feel a jerk in the line " +
            "and the weight is gone. The hook must have lost its " +
            "grip of the sack.\n");
        fisher->remove_prop("_fishing_for_sack");
       (ENV(TO)->remove_alarm(ENV(TO)->query_drift_alarm()));
        TO->drift();
        return;
    }

    fisher->catch_msg("You see the sack lift from the sunken " +
        "boat in a cloud of mud and rotten kelp that covered " +
        "the boat and its possessions. After a short while " +
        "you pull the sack over the realing and drop it in " +
        "the bottom of the boat.\n");
    fisher->command("cheer");
    say(QCTNAME(fisher) + " pulls the fishing line until "
        +fisher->query_pronoun()+ " lifts something over the " +
        "railing and drops it inside the boat.\n");
    tell_room((ENV(fisher)), "A rotten smell of mud and old " +
        "kelp fills the air.\n");
    fisher->remove_prop("_fishing_for_sack");
    (ENV(TO)->get_sack());
    sack = clone_object(THIS_DIR + "obj/oilskin_sack");
    key = clone_object(THIS_DIR + "obj/tower_key");
    horseshoe = clone_object(THIS_DIR + "obj/horseshoe");
    key->move(sack, 1);
    horseshoe->move(sack, 1);
    sack->move(TO, 1);
    return;
}

int
query_anchored()
{
    return is_anchored;
}


int
query_bob_alarm()
{
    if (bob_alarm)
        return bob_alarm;
}

int
query_bite_alarm()
{
    if (bite_alarm)
        return bite_alarm;
}

int
remove_bob_alarm()
{
    if (bob_alarm)
        remove_alarm(bob_alarm);
        bob_alarm = 0;
}

int
remove_bite_alarm()
{
    if (bite_alarm)
        remove_alarm(bite_alarm);
        bite_alarm = 0;
}

void
do_bob()
{
    if (!(random(5)))
    {
        int bob = random(7);
        switch(bob)
        {
            case 0:
                tell_room(TO, "The float bobs silently up and down " +
                "in the waves.\n");
                break;
            case 1:
                tell_room(TO, "You see small rings of water around " +
                "the float while it bobs up and down.\n");
                break;
            case 2:
                tell_room(TO, "Suddenly the float disappears beneath " +
                "the surface but before you can react it comes up " +
                "again. Small fish nabbing the bait no doubt.\n");
                break;
            case 3:
                tell_room(TO, "Light is glittering in the water " +
                "around the bobbing float.\n");
                break;
            case 4:
                tell_room(TO, "The float tips over from one side " +
                "to the other as it bobs from a small breeze crossing " +
                "the lake.\n");
                break;
            case 5:
                tell_room(TO, "The float is pulled around and you see " +
                "a shadow of a fish but its a false alarm as the float " +
                "is bobbing slowly on the surface again.\n");
                break;
            case 6:
                tell_room(TO, "The float is silently bobbing up " +
                "and down on the calm surface of the lake.\n");
                break;
        }
    }
}

void
do_bite()
{
        object pole;

        TO->remove_bob_alarm();
        tell_room(TO, "The float disappears below the surface with a jerk. " +
            "Now its time to pull it up!\n");
        pole = (present("_fish_pole", TP));
        pole->add_fish();

}

string
desc_water()
{
return(ENV(TO)->desc_water());
}

string
desc_bottom()
{
    return(ENV(TO)->desc_bottom());
}

string
desc_sunken_boat()
{
    if (ENV(TO)->query_prop(BH))
       return "What?\n";
    return(ENV(TO)->desc_sunken_boat());
}

string
desc_sack()
{
    if (ENV(TO)->query_prop(BH))
        return "What?\n";
    return(ENV(TO)->desc_sack());
}

string
desc_lake()
{
    if (TO == environment(TP))
    {
        return(ENV(TO)->long_description());
    }
    return "You dont get a good view of the lake from here. " +
        "Use the boat and you might see more.\n";
}

string
desc_jetty()
{


}

int
do_look(string str)
{

    int look = 1;

    if (ENV(TP) != (TO))
        return 0;


    if (!str || !strlen(str))
        return 0;

    if (ENV(TO)->query_prop(BH))
    {
        if (TP->query_option(2))
            write(ENV(TO)->short() + "\n");
        else
            write(ENV(TO)->long() + "\n");
        return 1;
    }

    if ((str == "east") || (str == "e"))

    {
        if (ENV(TO)->query_prop(BH))
    {
        if (TP->query_option(2))
            write(ENV(TO)->short() + "\n");
        else
            write(ENV(TO)->long() + "\n");
        return 1;
        }
        write(ENV(ENV(this_player()))->desc_east());
        write(desc_close_to_reed(str));
        return 1;
    }

    if ((str == "west") || (str == "w"))

    {
        if (ENV(TO)->query_prop(BH))
    {
        if (TP->query_option(2))
            write(ENV(TO)->short() + "\n");
        else
            write(ENV(TO)->long() + "\n");
        return 1;
        }
        write(ENV(ENV(this_player()))->desc_west());
        write(desc_close_to_reed(str));
        return 1;
    }

    if ((str == "south") || (str == "s"))

    {
        if (ENV(TO)->query_prop(BH))
    {
        if (TP->query_option(2))
            write(ENV(TO)->short() + "\n");
        else
            write(ENV(TO)->long() + "\n");
        return 1;
        }
        write(ENV(ENV(this_player()))->desc_south());
        write(desc_close_to_reed(str));
        return 1;
    }

    if ((str == "north") || (str == "n"))

    {
        if (ENV(TO)->query_prop(BH))
    {
        if (TP->query_option(2))
            write(ENV(TO)->short() + "\n");
        else
            write(ENV(TO)->long() + "\n");
        return 1;
            }
            write(ENV(ENV(this_player()))->desc_north());
            write(desc_close_to_reed(str));
            return 1;
    }

    if (str == "out")
    {
        write((ENV(TO))->long_description());
        return 1;
    }

    if ((str == "northwest") || (str == "nw") || (str == "northeast")
        || (str == "ne") || (str == "southwest") || (str == "sw")
        || (str == "southeast") || (str == "se"))
    {
        if (ENV(TO)->query_prop(BH))
        {
            if (TP->query_option(2))
                write(ENV(TO)->short() + "\n");
            else
                write(ENV(TO)->long() + "\n");
            return 1;
        }
        write(desc_close_to_reed(str));
        return 1;
    }
    write("Look where?\n");
    return 1;

}

string
return_long_env()
{
    object ob = environment(environment(TP));
    return ob->long();
}

string
return_short_env()
{
    object ob = environment(environment(TP));
    return ob->short() + "\n";
}

int
do_row(string str)
{
    int i;
    string desc;
    object *all, oars;

    if (!str || !strlen(str))
    {
        write("To row you must give a direction.\nLike 'row west' " +
            "or 'row lake'.\n");
        return 1;
    }

    if (ENV(TP) != TO)
        return 0;

    all = all_inventory((this_object()));
    for (i=0; i<sizeof(all); i++)
    {
        oars = (present("_oars", TP));
        if (!(oars))
        {
            write("You cant row without oars!\n");
            return 1;
        }

        if (TO->query_anchored())
        {
            write("You cant row the boat while its anchored. " +
                "Pull up the anchor first.\n");
            return 1;
        }

        if (all[i]->query_prop("_is_fishing"))
        {
            write("You shouldnt try to row while someone " +
                "is fishing.\n");
            return 1;
        }
    }

    if (str == "out")
    {
        if (ENV(TO)->query_prop(BH))
            write("Try 'row lake'.\n");
        else
            write("You cant row in that direction!\n");
        return 1;
    }

    if (str == "boat")
    {
        if (ENV(TO)->query_prop(BH))
            write("Try row <direction>. Inside the boathouse " +
                "that would be 'row lake'.\n");
        else
            write("Try row <direction>.\n");
        return 1;
    }

    switch(str)
    {
        case "n":
            str = "north";
            break;
        case "s":
            str = "south";
            break;
        case "w":
            str = "west";
            break;
        case "e":
            str = "east";
            break;
        case "nw":
            str = "northwest";
            break;
        case "ne":
            str = "northeast";
            break;
        case "sw":
            str = "southwest";
            break;
        case "se":
            str = "southeast";
            break;
    }

    i = member_array(str, environment(TO)->query_exit_cmds());
    if (i < 0)
    {
        notify_fail("Row where?\n");
        return 0;
    }

    if( move_the_boat(str) )
    {
         write("You row the "+ short() +" to the "+ str +".\n");
	     say(QCTNAME(TP) + " rows the boat to the " +str+".\n");

	     if (str == "lake")
	     {
	          tell_room(TO,"The boathouse disappears in the reed " +
                        "behind you.\n");
         }

    }

    return 1;
}

string
query_action()
{
    if (ENV(TP)->id("boat"))
        return "rowing on";
    return "swiming in";
}

int
move_the_boat(string str)
{
	mixed room;

	if (str == "missingfisherman")
	{
		room = BOATHOUSE;
	}
	else
	{
		mixed exits = environment(TO)->query_exit();
		int index = member_array(str, exits);
		room = environment(TO)->check_call(exits[index - 1]);
		mixed arg3 = environment(TO)->check_call(exits[index + 1]);
		mixed e = filter(ENV(ENV(TP))->query_exit(), &wildmatch("*reed|*"));
		if (ENV(TO)->query_drift_alarm())
			remove_alarm(ENV(TO)->query_drift_alarm());
		if (arg3) // If arg3 = 1 we are trying to move into reed.
		{
			ENV(TO)->start_drift(TO);  // So we start a new driftprocess.
			return 0;
		}
	}

	tell_room(room, "A " +short()+ " arrives.\n");
    set_alarm(0.0, 0.0, &move(room, 1));
    return 1;
}

int
do_enter(string str)
{
    if (!str || !strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (str != "boat")
        return 0;

    if(TO == environment(TP))
    {
        notify_fail("You are already inside the "+query_short()+".\n");
        return 0;
    }

/*
    if (TP->weight() > 500000)
    {
        notify_fail("You are too heavy for the "+query_short()+".\n");
        return 0;
    }

    if (((TO->weight() - TO->query_prop(CONT_I_MAX_WEIGHT))
        + TP->weight()) > 200000)
    {
        notify_fail("That would sink the loaded "+query_short()+".\n");
        return 0;
    }

*/

    write("You lean down and take a step down into the "+query_short()+".\n");
    say(({METNAME + " bends down and steps into the "+query_short()+".\n",
       TART_NONMETNAME + " bends down and steps into the "+query_short()+".\n",
       ""}), TP);
    tell_room(TO, ({METNAME + " enters the " +query_short()+".\n",
        TART_NONMETNAME + " enters the " +query_short()+".\n",
        ""}), TP);
    TP->move(TO, 1);
    return 1;
}

int
do_leave(string str)
{
    if(TO != ENV(TP))
    {
    notify_fail(CAP(QVB)+" what?\n");
    return 0;
    }

    if (!(ENV(TO)->query_prop(BH)))
    {
        write("Before diving, you stick your hand into " +
            "the water to check the temperature. Its freezing " +
            "cold and you realise you wouldnt survive long. So " +
            "you decide leaving the "+query_short()+" wasnt " +
            "such a good idea after all.\n");
        say(QCTNAME(TP) + " sticks a hand into the water. From the " +
            "reaction you can deduct that the water is very cold.\n");
        return 1;
    }
    else
    say(QCNAME(TP) + " climbs out of the "+query_short()+".\n");
    write("You climb out of the "+query_short()+".\n");
    tell_room(ENV(TO), QCTNAME(TP) + " arrives from the " +
    query_short()+ ".\n");
    TP->move_living("M", ENV(TO));
    return 1;
}


int query_prop(string prop)
{
    if (prop == OBJ_I_LIGHT)
        return check_light();
    else
        return ::query_prop(prop);
}

int
check_light()
{
    int light;

    light = environment(TO)->query_prop(ROOM_I_LIGHT);
    return light;
}

string
desc_shores()
{
    if (ENV(TO)->query_prop(LAKE))
        return ENV(TO)->desc_shores();
    else
        return "What?\n";
}

string
desc_oaks()
{
    if (ENV(TO)->query_prop(LAKE))
        return ENV(TO)->desc_oaks();
    else
        return "What?\n";
}

string
desc_rock()
{
    if (ENV(TO)->query_prop(ROCK))
        return ENV(TO)->desc_rock();
    else
        return "What?\n";
}

string
desc_tower()
{
    if (ENV(TO)->query_prop(TOWER))
        return ENV(TO)->desc_tower();
    else
        return "What?\n";
}

string
desc_mill()
{
    if (ENV(TO)->query_prop(MILL))
    {
        return ENV(TO)->desc_mill();
    }
    else
        return "What?\n";
}

string
desc_house()
{
    if (ENV(TO)->query_prop(HOUSE))
        return ENV(TO)->desc_house();
    else
        return "What?\n";
}

string
desc_reed()
{
    if (ENV(TO)->query_prop(LAKE))
        return "The reed is growing thick around the lake. " +
            "Its impossible to pass through it.\n";
    else
    return "There is no reed here.\n";
}

string
desc_close_to_reed(string str)
{
    mixed exits, arg3;
    int index;

    switch(str)
    {
        case "n":
            str = "north";
            break;
        case "s":
            str = "south";
            break;
        case "w":
            str = "west";
            break;
        case "e":
            str = "east";
            break;
        case "nw":
            str = "northwest";
            break;
        case "ne":
            str = "northeast";
            break;
        case "sw":
            str = "southwest";
            break;
        case "se":
            str = "southeast";
            break;
    }
    exits = environment(TO)->query_exit();
    index = member_array(str, exits);
    arg3 = environment(TO)->check_call(exits[index + 1]);
    if (arg3) // If arg3 = 1 we are close to the reed
        return ""; // No text as that is returned by the add_exit()
    else
    return "There is clear water in that direction.\n";
}


/*
drift() is called from lake_base.c when its time to drift the boat
The drift is randomly called now and then.
If the boat is empty by quitting or LDing players, the boat will
be forced to drift back to the boathouse.
*/

int
drift()
{
    int i, index;
    string desc, str, text;
    mixed exits, room;

    if (TO->query_anchored())
    {
        if (!(sizeof(FILTER_PLAYERS(all_inventory(TO)))))
        {
            is_anchored = 0;  // If boat is empty, remove anchor status
        }
	else
	{
            tell_room(TO, "The wind pulls the boat, but as its safely " +
                "anchored, it doesnt drift away in the direction of " +
                "the wind.\n");
	}

        if (!(ENV(TO)->query_driftalarm()))
            (ENV(TO))->start_drift(TO);
        return 1;// No drift if we are anchored
    }

    i = (random(8) + 1);

/*
Now check if the boat is empty of players or not.
If its empty the boat should drift back to the boathouse
using the query_default_drift() in each room.
If there are players in the boat, the boat will drift
in a random direction.
*/

    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
    {
	switch(i)
	{
        case 1:
            str = "north";
            break;
        case 2:
            str = "south";
            break;
        case 3:
            str = "west";
            break;
        case 4:
            str = "east";
            break;
        case 5:
            str = "northwest";
            break;
        case 6:
            str = "northeast";
            break;
        case 7:
            str = "southwest";
            break;
        case 8:
            str = "southeast";
            break;
        }
    }
    else
    str = "missingfisherman"; //(ENV(TO))->query_default_drift();

    i = (random(5) + 1);
    switch(i)
    {
        case 1:
            text = "A breeze catches the " +short()+ " and drift it to " +
                "the " +str+ ".\n";
            break;
        case 2:
            text = "The " +short()+ " drifts to the " +str+ ".\n";
            break;
        case 3:
            text = "Suddenly the current turn the " +short()+ " around " +
                "and drift it to the " +str+ ".\n";
            break;
        case 4:
            text = "The water curls from a wind which pulls the " +
                short()+ " to the " +str+ ".\n";
            break;
        case 5:
            text = "A cold breeze moves the " +short()+ " to the " +str+
                ".\n";
            break;
    }
    tell_room(TO, text);
    tell_room((ENV(TO)), "The " +short()+ " slowly drifts away to " +
        "the " +str+ ".\n");
    move_the_boat(str);
    return 1;
}

int
query_time_to_drift()
{
    return (ENV(TO)->query_time_to_drift());
}

int
do_rock(string str)
{
    if(TO != ENV(TP))
    {
        notify_fail(CAP(QVB)+" what?\n");
        return 0;
    }

    if (!(str))
       return 0;
    if (str != "boat")
        return 0;

    write("You start to rock the "+query_short()+" from " +
        "side to side. The "+query_short()+ " is pretty " +
        "stabil, so there is no risk of it turning over.\n");

        say(({METNAME + " starts to rock the boat from " +
            "side to side.\n",
            TART_NONMETNAME + "  starts to rock the boat from " +
            "side to side.\n.\n",
            "The boat starts to rock from side to side."}), TP);
    return 1;
}

int
search_far_away_items(string str)
{
    if (!(ENV(TP) == TO))
        return 0;

    if ((str == "rock") || (str == "tower") || (str == "mill")
        || (str == "house") || (str == "reed") || (str == "bottom")
        || (str == "trees") || (str == "shores") || (str == "sunken boat"))
    {
        write("The " +str+ " is to far away to search.\n");
        return 1;
    }
    return 0;
}

string
exits_description()
{
	return "";
}
