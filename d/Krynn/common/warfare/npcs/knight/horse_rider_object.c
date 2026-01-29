// Adapted by Navarre, March 2006, to allow npcs to charge.


inherit "/d/Genesis/steed/new/rider_object";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/solamn/vin/knight/guild.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <formulas.h>

#define BAN(x) add_action("fail_function", x)
#define SOULDESC(x)    (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))
#define RIDER_SUBLOC "_live_i_mounted"

#define DEBUG(x)    find_living("boron")->catch_msg("Debug: " + x + "\n");

object horse = E(TO)->query_steed();

void
create_object()
{
    set_name("rider_object");
    set_short("Knights rider_object");
    set_long("Knights rider_object");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
}

int try_maneuver(string str)
{
    if (TP->query_cavalry_shadow())
    {
    return TP->maneuver(str);
    }

    return 0;
}

int try_charge(string str)
{
    if (TP->query_cavalry_shadow())
    {
    return TP->charge_special(str);
    }
    return 0;
}

init()
{
    add_action("try_charge", "charge");
    add_action("try_maneuver", "maneuver");
    add_action("do_calm", "hcalm");
    add_action("do_halt", "htug");
    add_action("do_rear", "hrear");
    add_action("do_snap", "hsnap");
    add_action("do_pat", "hrub");
    add_action("horsehelp", "horsehelp");

    /* Changed and modified standard emotes */
    add_action("pounce", "pounce");
    add_action("laugh", "laugh");
    add_action("back", "back");
    add_action("hug", "hug");
    add_action("wiggle", "wiggle");
    add_action("nudge", "nudge");
    add_action("bounce", "bounce");

    BAN("double");
    BAN("2");
    BAN("search");
    BAN("tackle");
    BAN("tap");
    BAN("dance");
    BAN("flip");
    BAN("bow");
    BAN("curtsey");
    BAN("kbow");
    BAN("cringe");
    BAN("curl");
    BAN("cuddle");
    BAN("kfirm");
    BAN("jump");
    BAN("grovel");
    BAN("nuzzle");
    BAN("snuggle");
    BAN("stomp");
    BAN("strut");
    BAN("sulk");
    BAN("worship");

    ::init();
}

void welcome_message(object ob)
{
    DEBUG("welcome_message ob is: " + ob->short() +
            "\nCalling function is: " + calling_function(-1));
}

int horsehelp(string str)
{
    write("While mounted you may use the following commands:\n"+
      " hrub         - rub your mount's neck soothingly\n"+
      " hcalm        - calm your mount by grasping the reins\n"+
      " hsnap        - snap the reins to make your horse move\n"+
      " htug         - tug on the reins to still your horse\n"+
      " hrear        - yank the reins so your horse rears up\n"+
      " autodismount - You figure it out\n"+
      " automount    - Yes, you are right!\n"+
      "\nAssuming the room contains the necessary items, you\n"+
      "may also 'feed' or 'water' your horse.\n");
    return 1;
}

int do_calm(string str)
{
    horse = TP->query_steed();

    if (!horse)
    remove_object();

    write("You gather the reins in your hand, calming your "+horse->steed_short()+".\n");
    say(QCTNAME(TP)+" gathers the reins in "+POSSESSIVE(TP)+" hand, calming "+
      POSSESSIVE(TP)+" "+horse->steed_short()+".\n");
    return 1;
}

int do_pat(string str)
{
    horse = TP->query_steed();

    if (!horse)
    remove_object();

    write("You lean forward, rubbing your "+horse->steed_short()+"'s neck soothingly.\n");
    say(QCTNAME(TP)+" leans forward, rubbing "+POSSESSIVE(TP)+" "+horse->steed_short()+
      "'s neck soothingly.\n");
    return 1;
}

int do_rear(string str)
{
    horse = TP->query_steed();

    if (!horse)
    remove_object();

    write("You pull sharply on the reins and dig your heels into the "+
      horse->steed_short()+"'s flanks, which rears back, kicking "+POSSESSIVE(horse)+
      " front legs high in the air.\n");
    say(QCTNAME(TP)+" pulls sharply on the reins and digs "+POSSESSIVE(TP)+
      " heels into the "+horse->steed_short()+"'s flanks, which rears back, kicking "+
      POSSESSIVE(horse)+" front legs high in the air.\n");
    return 1;
}

int do_halt(string str)
{
    horse = TP->query_steed();

    if (!horse)
    remove_object();

    write("You tug on the reins slightly, stilling your "+horse->steed_short()+".\n");
    say(QCTNAME(TP)+" tugs on the reins slightly, stilling "+POSSESSIVE(TP)+
      " "+horse->steed_short()+".\n");
    return 1;
}

int do_snap(string str)
{
    horse = TP->query_steed();

    if (!horse)
    remove_object();

    write("You snap the reins, prodding your "+horse->short()+" forward.\n");
    say(QCTNAME(TP)+" snaps the reins, prodding "+POSSESSIVE(TP)+" "+
      horse->steed_short()+" forward.\n");
    return 1;
}


void enter_env(object inv, object from)
{
    inv->add_subloc(RIDER_SUBLOC, TO);
}

void leave_env(object inv, object to)
{
    inv->remove_subloc(RIDER_SUBLOC);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str, tmp;

    if (!horse)
    horse = E(TO)->query_steed();

    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (horse->query_barding())
    tmp = ", which is adorned in "+horse->query_barding();
    else
    tmp = "";

    /* Already done by steed.c
    if(for_obj == carrier)
        str = "You are riding your "+horse->steed_short()+tmp+".\n";
    else
        str = C(PRONOUN(carrier))+" is riding a "+
        horse->steed_short()+tmp+".\n";
     */
    return str;
}


/* CHANGED STANDARD EMOTES */

laugh(string str)
{
    object *oblist, me = E(TO), horse = me->query_steed();
    string *how;

    if (!stringp(str))
    {
    write("You nearly fall off your "+horse->steed_short()+
      " laughing.\n");
    all(" nearly falls off "+POSSESSIVE(me)+" "+horse->steed_short()+
      " laughing.\n");
    SOULDESC("laughing");
    return 1;
    }

    how = parse_adverb_with_space(str, "exuberantly", 1);

    if (!stringp(how[0]))
    {
    SOULDESC("laughing" + how[1]);
    write("You laugh" + how[1] + ".\n");
    all(" laughs" + how[1] + ".", how[1]);
    return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
    notify_fail("Laugh how [at whom]?\n");
    return 0;
    }

    SOULDESC("laughing" + how[1]);
    actor("You laugh" + how[1] + " at", oblist, ".");
    all2act(" laughs" + how[1] + " at", oblist, 0, how[1]);
    target(" laughs" + how[1] + " at you.", oblist, how[1]);
    return 1;
}

int pounce(string str)
{
    object *oblist, me = E(TO), horse = me->query_steed();
    string pos;
    string obj;

    oblist = parse_this(str, "[on] [the] %l");

    if (!sizeof(oblist))
    {
    notify_fail("Pounce on whom?\n");
    return 0;
    }

    pos = ((sizeof(oblist) > 1) ? "their" : oblist[0]->query_possessive());
    obj = ((sizeof(oblist) > 1) ? "them" : oblist[0]->query_objective());
    actor("You pounce from your "+horse->steed_short()+" onto",
      oblist, ", knocking " + obj + " flat on " + pos +
      " back!");
    all2act(" pounces from "+POSSESSIVE(me)+" "+horse->steed_short()+" onto",
      oblist, ", knocking " + obj + " flat on " + pos + " back!");
    target(" pounces on you from "+POSSESSIVE(me)+" "+horse->steed_short()+
      ", knocking you flat on your back.", oblist);
    horse->do_dismount(me, 1);
    return 1;
}

int back(string str)
{
    object *oblist, me = E(TO), horse = me->query_steed();
    string *how;

    how = parse_adverb_with_space(str, "slowly", 0);

    if (!stringp(how[0]))
    {
    write("You back your "+horse->steed_short()+" away" + how[1] + ".\n");
    all(" begins to back "+POSSESSIVE(me)+" "+horse->steed_short()+
      " away " + how[1] + ".");
    return 1;
    }

    oblist = parse_this(how[0], "[away] [from] [the] %l");

    if (!sizeof(oblist))
    {
    notify_fail("Back your horse [how] away from whom?\n");
    return 0;
    }

    actor("You back your "+horse->steed_short()+" away" + how[1] +
      " from", oblist);
    all2actbb(" backs "+POSSESSIVE(me)+" "+horse->steed_short()+" away" +
      how[1] + " from", oblist, 0, how[1]);
    targetbb(" begins to back "+POSSESSIVE(me)+" "+horse->steed_short() +
      how[1] + " away from you.", oblist, how[1]);
    return 1;
}


int nudge(string str)
{
    object *oblist, me = E(TO), horse = me->query_steed();

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
    notify_fail("Nudge whom?\n");
    return 0;
    }

    actor("You maneuver your "+horse->steed_short()+" to nudge", oblist);
    all2act(" maneuvers "+POSSESSIVE(me)+" "+horse->steed_short()+" to "+
      "nudge", oblist);
    target(" maneuvers "+POSSESSIVE(me)+" "+horse->steed_short()+" to "+
      "nudge you.", oblist);
    return 1;
}

int hug(string str)
{
    object *oblist, me = E(TO), horse = me->query_steed();
    string *how;

    how = parse_adverb_with_space(str, "tightly", 1);

    oblist = parse_this(how[0], "[the] %l");

    if (!sizeof(oblist))
    {
    notify_fail("Hug whom [how]?\n");
    return 0;
    }

    actor("You lean over in the saddle and hug", oblist, how[1] +
      ".");
    all2act(" leans over in the saddle and hugs", oblist, how[1] +
      ".", how[1]);
    target(" leans over in the saddle and hugs you" + how[1] +
      ".", oblist, how[1]);
    return 1;
}

wiggle(string str)
{
    object me = E(TO);

    str = check_adverb_with_space(str, "slowly", 0);

    write("Standing up in the stirrups, you wiggle your bottom" +
      str + ".\n");
    allbb(" stands up in the stirrups and wiggles " +
      POSSESSIVE(me)+ " bottom" + str + ".", str);
    return 1;
}

bounce(string str)
{
    object me = E(TO);

    str = check_adverb_with_space(str, "uncontrollably", 0);

    write("You bounce around in the saddle" + str + ".\n");
    all(" bounces around" + str + " in the saddle.", str);
    return 1;
}

int fail_function(string str)
{
    write("You may not use this command from horseback.\n");
    return 1;
}

