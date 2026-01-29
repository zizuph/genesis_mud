/*
 * ~/towel.c
 *
 * A towel for the bath house.
 *
 * Revisions:
 *   Lilith, Feb 2002: Created.
 *   Lucius, Aug 2016: Code Cleanups.
 *   Lucius, Mar 2018: Switched to /lib/commands
 *
 */
#pragma strict_types

inherit "/std/heap";
inherit "/lib/keep";
inherit "/lib/commands";
inherit "/lib/wearable_item";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>


public void
create_heap(void)
{
    set_name("towel");
    set_short("fluffy white towel");
    set_adj(({"fluffy", "white"}));
    set_long("This is a fluffy white bath towel provided to "+
       "patrons of Melchior's Bath House for a nominal fee. "+
       "A decorative border has been embroidered at each "+
       "end of the towel, which can be worn around the waist.\n");

    add_item(({"decoration", "decorations", "embroidered", 
       "embroidery", "border", "borders", "hem", "hems" }), 
       "A repeating pattern of golden trefoils and amphoras "+
       "forms a border at each end of the towel.\n");

    add_cmd_item("towel", "help", "Here are the emotes associated "+
        "with this towel:\n     wear - wear the towel\n"+
        "     snap - snap towel\n     rub - rub something dry\n");
     
    add_prop(OBJ_I_VOLUME, 500);   
    add_prop(OBJ_I_WEIGHT, 500);  
    add_prop(OBJ_I_VALUE,  25); 
    add_prop(HEAP_S_UNIQUE_ID, "av_bath_towel");

    set_slots(A_WAIST);    
    set_looseness(6);
    set_layers(3);
    set_wf(this_object());

    set_heap_size(1);
}   
          
public int
wear(object ob)
{
    if (!this_player()->query_gender(G_FEMALE))
    {
        write("You wrap the "+ short() +" about your waist and "+
            "tuck a corner under to hold it in place.\n");
        say(QCTNAME(this_player()) +" wraps the "+ short() +
            " around "+ this_player()->query_possessive() +
            " waist and tucks a corner to hold it in place.\n");
    }
    else
    {
        write("You wrap the "+ short() +" about your torso and "+
            "tuck a corner under your arm to hold it in place.\n");
        say(QCTNAME(this_player()) +" wraps the "+ short() +
            " around "+ this_player()->query_possessive() +
            " torso and tucks a corner to hold it in place.\n");
    }

    return 1;
}

/*
 * Add/mask emotions to make them more fun!
 */
public int
do_snap(string str)
{
    if (!query_worn())
        return 0;

    if (!strlen(str))
        return 0;

    if (str == "towel")
    {
        write("You twirl the "+ short() +" into a whip-like "+
            "shape and flick it with your wrist, causing a "+
            "loud snapping noise.\n");
        all(" twirls the "+ short() + " into a whip-like "+
            "shape and flicks it with "+ 
            this_player()->query_possessive() +
            " wrist, causing a loud 'SNAP'.");

	return 1;
    }

    object *oblist = parse_live(str, "[towel] [at] [the] %i");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
	notify_fail("Snap at <whom>?\n");
	return 0;
    }

    actor("You twirl the "+ short() +" into a whip-like "+
        "shape and flick it at", oblist, " with a loud 'SNAP'.");
    all2act(" twirls the "+ short() + " into a whip-like "+
        "shape and flicks it at", oblist," causing a "+
        "loud 'SNAP'.");
    target(" twirls the "+ short() + " into a whip-like "+
        "shape and flicks it at you. You feel a slight "+
        "sting at the same moment you hear a loud 'SNAP'.", oblist);

    return 1;
}

public int
do_rub(string str)
{
    string *how = parse_adverb_with_space(str, "gently", 0);
   
    if (!strlen(how[0]))
    {
        write("You" + how[1] + " rub yourself down with "+
            short() +".\n");
        all(how[1] +" rubs "+ this_player()->query_objective() +
            "self down with "+ short() +".");

        return 1;
    }
   
    object *oblist = parse_live(how[0], "%i [down] [with] [the] [towel]");
    if (!sizeof(oblist))
    {
        notify_fail("Rub whom with the towel?\n");
        return 0;
    }
   
    actor("You"+ how[1] +" rub", oblist, " down with your "+ 
        short() +".");
    all2actbb(" rubs", oblist, 0, how[1] +" down with "+
        this_player()->query_possessive() +" "+ short() +".");
    targetbb(" rubs you down"+ how[1] +" with "+ 
        this_player()->query_possessive() +" "+
	short() +".", oblist);

    return 1;
}

public int
do_bow(string str)
{
    if (!query_worn())
        return 0;

    string verb = query_verb();

    if (!strlen(str))
    {
        write("You try to "+ verb +" while wearing your "+ short() +
            " and then decide it wouldn't be appropriate "+
            "while wearing a towel.\n");
        allbb(" starts to "+ verb +", but then seems to realize that "+
	    this_player()->query_pronoun() +" would look "+
	   " incongruous "+ verb +"ing in a "+ short() +".");

	return 1;
    }

    object *oblist = parse_live(str, "[to] / [before] [the] %i");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
	return 0;

    actor("You try to "+ verb +" while wearing your "+ short() +
        " and then decide it wouldn't be appropriate "+
        "while wearing a towel.\n");
    all2actbb(" starts to "+ verb +", but then seems to realize "+
        "that "+ this_player()->query_pronoun() +" would look "+
	"incongruous "+ verb +"ing in a "+ short() +".");
    targetbb(" starts to "+ verb +" to you, but then seems to "+
        "that "+ this_player()->query_pronoun() +" would look "+
	"incongruous "+ verb +"ing in a "+ short() +".", oblist);

    return 1;
}

public void
init(void)
{
    ::init();

    if (this_player() != environment())
	return;

    add_action(do_snap,  "snap");
    add_action(do_snap,  "flick");
    add_action(do_rub,   "rub");
    add_action(do_bow,   "bow");
    add_action(do_bow,   "curtsey");
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);    
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
