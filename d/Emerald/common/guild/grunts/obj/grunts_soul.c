/* This is what you've all been waiting for... the infamous Grunts soul!  */
/* With a bit of luck it will give Goblins the important position of      */
/* being the most disgusting, foul race on the face of Genesis.           */
/* This soul was based on the work of others - Tricky, Quis, Nick et al.  */
/* The original soul was developed by Tulix I, 29/3/1993.                 */
/* Recoded 11/08/95 with various improvements, Tulix III.                 */

/* Adverbs added to 'grunt' command, 'crap' command recoded 04/11/95.     */
/* Recoded to improve fault tolerance 27/12/95.                           */
/* Fleas added and grnews, grlevels & grhelp recoded 04/05/96.            */

inherit "/cmd/std/command_driver";

/* These two lines are put in to keep Mercade happy */
#pragma strict_types
#pragma save_binary  


#include <adverbs.h>
#include "/d/Emerald/tulix/t_defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"


/* ************************************************************************
 * These three functions are for the grunts guild soul only.
 */
public void
allow_crap(object player)
{
    int crap_number;
    
    /* Allow player to crap again after a certain period of time. */
    crap_number = player->query_prop(LIVE_I_CRAPPED_NUMBER);
    player->add_prop(LIVE_I_CRAPPED_NUMBER, crap_number - 1);
    
    if (player->query_prop(LIVE_I_CRAPPED_NUMBER) <= 0)
        player->remove_prop(LIVE_I_CRAPPED_NUMBER);
}

public void
add_flea(object player)
{
    int flea_number;
    
    /* Allow the player to harvest another flea after a period of time. */
    flea_number = player->query_prop(LIVE_I_HARVESTED_FLEAS);
    player->add_prop(LIVE_I_HARVESTED_FLEAS, flea_number - 1);
    
    if (player->query_prop(LIVE_I_HARVESTED_FLEAS) <= 0)
        player->remove_prop(LIVE_I_HARVESTED_FLEAS);
}

public void
cool_head(object player)
{
    int number_of_thoughts;
    
    /* Allow the player to harvest another flea after a period of time. */
    number_of_thoughts = player->query_prop(LIVE_I_HAS_BEEN_THINKING);
    player->add_prop(LIVE_I_HAS_BEEN_THINKING, number_of_thoughts - 1);
    player->catch_msg("Your head now cools down after the tremendous " +
            "effort of thinking.\n");
    
    allbb("'s head cools down after the tremendous effort of thinking.");

    if (player->query_prop(LIVE_I_HAS_BEEN_THINKING) <= 0)
    {    
        player->catch_msg("Your head has cooled down enough to allow " +
            "your fleas to prosper.\n");
        player->remove_prop(LIVE_I_HAS_BEEN_THINKING);
    }
}

/* ************************************************************************
 * Return the proper name of the soul in order to get a nice printout.
 */
public string
get_soul_id()
{
    return GUILD_SOUL_ID;
}

/* ************************************************************************
 * This is a command soul.
 */
public int
query_cmd_soul()
{
   return 1;
}

/* ************************************************************************
 * The list of commands. Please add new ones in alphabetical order.
 */
public mapping
query_cmdlist()
{
   return ([
        "arm"        : "arm",
        "bird"       : "bird",
        "breath"     : "breath",
        "butt"       : "butt",
        "crap"       : "crap",
        "curse"      : "curse",
        "ears"       : "ears",
        "faces"      : "faces",
        "fist"       : "fist",
        "flick"      : "flick",
        "flob"       : "flob",
        "grdrool"    : "grdrool",
        "grlevels"   : "grlevels",
        "grnews"     : "grnews",
        "grshake"    : "grshake",
        "grthink"    : "grthink",
        "grunt"      : "grunt",
        "harvest"    : "harvest",
        "help"       : "help",
        "knuckles"   : "knuckles",
        "leak"       : "leak",
        "munch"      : "munch",
        "ogle"       : "ogle",
        "pick"       : "pick_nose",
        "roar"       : "roar",
        "stink"      : "stink",
        "tongue"     : "tongue",
        "warcry"     : "warcry"
    ]);
}

/* ************************************************************************
 * The following functions are executed when the user of the soul types the
 * relevant command defined in query_cmdlist.
 */

public int
arm()
{
    write("You stick your hand under your armpit and start "+
        "making disgusting noises with your hand and armpit.\n");
    allbb(" starts making noises using " + this_player()->query_possessive() +
        " armpit.\nTTTHHHHHRRRRRPPPPPPTTTT");
    return 1;
}

public int
bird(string str)
{
    object *oblist;
   
    NF("Flick the bird to whom?\n");
   
    if (!strlen(str))
    {
        write("You flick the bird to the heavens above.\n");
        all(" flicks the bird to the heavens above.\n");
        return 1;
    }
   
    oblist = parse_this(str, "[to] %l");
   
    if (!sizeof(oblist))
        return 0;
      
     target(" flicks you the bird. Thats not very nice.", oblist);
     actor("You flick the bird to", oblist);
     all2act(" flicks the bird to", oblist);
     return 1;
}

public int
breath(string str)
{
    object *oblist;
   
    NF("At whom do you wish to aim your breath?\n");
   
    if (!strlen(str))
    {
        write("You smell your breath. Pheweee!!\n");
        allbb(" tests " + this_player()->query_possessive() + " breath,"
            + " and " + this_player()->query_possessive() + " face " +
            "turns a very unusual colour.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" makes you feel unwell with " + this_player()->query_possessive()
        + " smelly breath.", oblist);
    actor("You make", oblist," feel unwell with your breath.");
    all2actbb(" makes", oblist," feel unwell with "
        + this_player()->query_possessive() + " smelly breath.");
    return 1;
}

public int
butt(string str)
{
    object *oblist;
   
    NF("Whom do you wish to headbutt?\n");
   
    if (!strlen(str))
    {
        write("You headbutt the nearest convenient object.\n");
        allbb(" headbutts the nearest convenient object.");
        return 1;
    }
   
    oblist = parse_this(str, " %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" headbutts you in the stomach. You collapse to the floor."
        , oblist);
    actor("You headbutt", oblist," in the stomach, who falls to the floor.");
    all2actbb(" headbutts", oblist," in the stomach, who falls to the floor.");
    return 1;
}

public int
crap()
{
    object crap, room;
    int crap_number, delay, full, grunt_level;

    room = ENV(TP);
    full = TP->query_stuffed();

    if (TP->query_prop(LIVE_I_CRAPPED_NUMBER) >= 2)
    {
        write("You have already crapped recently.....\n");
        return 1;
    }
    
    NF("You have not had enough to eat to do that.\n");
    if(full < 80)
        return 0;
    
    crap_number = TP->query_prop(LIVE_I_CRAPPED_NUMBER);
    TP->add_prop(LIVE_I_CRAPPED_NUMBER, crap_number + 1);
    
    grunt_level = TP->query_grunts_level();
    if (grunt_level >= 100)
        grunt_level = 100;
    
    /* How often you can crap is determined by your guild level */
    delay = 350 - ( 2 * grunt_level );

    set_alarm( itof(delay), 0.0, &allow_crap(TP));

    write("You defecate on a convenient spot.\n");
    setuid();
    seteuid(getuid(this_object()));
    crap = clone_object(GRUNTS_CRAP);
    crap ->move(room);
    allbb(" defecates on a convenient spot.");
    TP->eat_food(-80);
    
    TP->remove_prop(LIVE_I_SLIP_POSSIBLE); /* So player won't slip in crap */

    return 1;
}

public int
curse(string str)
{
    object *oblist;
    string *how;
    
    if (!strlen(str))
    {
        write("You curse in a most bitter way.\n");
        all(" curses in a most bitter fashion.");
        return 1;
    }
    
    how = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    if (!strlen(how[0]))
    {
        write("You curse" + how[1] + ".\n");
        all(" curses" + how[1] + ".");
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Curse [how] whom?\n");
        return 0;
    }

    target(" curses you" + how[1] + ".", oblist);
    actor("You curse" + how[1] + " at", oblist);
    all2act(" curses" + how[1] + " at", oblist);
    return 1;
}

public int
ears(string str)
{
    object *oblist;
   
    NF("Wiggle your ears at whom?\n");
   
    if (!strlen(str))
    {
        write("You wiggle your ears, causing a small draft.\n");
        allbb(" wiggles " + this_player()->query_possessive() +
            " ears, causing a small draft.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" wiggles " + this_player()->query_possessive() 
        + " ears at you suggestively.", oblist);
    actor("You wiggle your ears at", oblist);
    all2actbb(" wiggles " + this_player()->query_possessive() 
        + " ears at", oblist);
    return 1;
}

public int
faces(string str)
{
    object *oblist;
   
    NF("Pull silly faces at whom?\n");
   
    if (!strlen(str))
    {
        write("You pull a couple of silly faces.\n");
        allbb(" pulls some very silly faces.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" pulls silly faces at you.", oblist);
    actor("You pull silly faces at", oblist);
    all2actbb(" pulls silly faces at", oblist);
    return 1;
}

public int
fist(string str)
{
    object *oblist;
   
    NF("Shake your fist at whom?\n");
   
    if (!strlen(str))
    {
        write("You angrily shake your fist around.\n");
        allbb(" angrily shakes " + this_player()->query_possessive() +
            " fist in the air.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" angrily shakes " + this_player()->query_possessive() +
        " fist at you.", oblist);
    actor("You angily shake your fist at", oblist);
    all2actbb(" angrily shakes " + this_player()->query_possessive() +
        " fist at", oblist);
    return 1;
}

public int
flick(string str)
{
    object *oblist;
   
    NF("Flick a bogey at whom?\n");
   
    if (!strlen(str))
    {
        write("You flick a bogey at the floor.\n");
        allbb(" flicks a bogey at the floor.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" flicks a large bogey at you.", oblist);
    actor("You flick a large bogey at", oblist);
    all2actbb(" flicks a large bogey at", oblist);
    return 1;
}

public int
flob(string str)
{
    object *oblist;
   
    NF("Flob a brown hocker at whom?\n");
    
    if(!strlen(str))
    {
        write("You flob a disgusting looking brown hocker to the ground.\n");
        all(" flobs a disgusting brown hocker on the ground at your feet.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
    
    if(!sizeof(oblist))  
        return 0;
   
    target(" flobs a disgusting brown hocker, which hits you in the chest.",
        oblist);
    actor("You flob a disgusting looking brown hocker, hitting the chest of ",
        oblist);
    all2actbb("  flobs a disgusting brown hocker at the chest of ", oblist);
    return 1;
   
}

public int
grdrool(string str)
{
    object *oblist;
    string *how;
    
    if (!strlen(str))
    {
        write("You drool saliva down your chin.\n");
        all(" drools saliva down " + this_player()->query_possessive() +
            " chin.");
        return 1;
    }
    
    how = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    if (!strlen(how[0]))
    {
        write("You drool saliva" + how[1] + " down your chin.\n");
        all(" drools saliva" + how[1] + " down " +
            this_player()->query_possessive() +" chin.");
        return 1;
    }

    setuid();
    seteuid(getuid());

    oblist = parse_this(how[0], "[over] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Drool [how] over whom?\n");
        return 0;
    }
    
    target(" drools saliva" + how[1] + " over you.", oblist);
    actor("You drool saliva" + how[1] + " over", oblist);
    all2actbb(how[1] +" drools saliva over", oblist);
    return 1;
}

public int
grlevels()
{
    setuid();
    seteuid(getuid());

    write(read_file(GRLEVELS_FILE));
    
    return 1;
}

public int
grnews()
{
    setuid();
    seteuid(getuid());

    write(read_file(GRNEWS_FILE));

    return 1;
}

public int
grshake(string str)
{
    object *oblist;
    string init_str;

    init_str = str;

    NF("Spit on you hand, and then shake hands with whom?\n");
    
    if (!strlen(str))
        return 0;
    
    oblist = parse_this(str, " %l");
   
    if (!sizeof(oblist))
        return 0;

    write("You spit on your hand.\n");
    allbb(" spits on " + this_player()->query_possessive() + " hand.");
    this_player()->command("shake " + init_str);
    return 1;    /* This means that you will try to shake hands as usual */
}

public int
grthink()
{
    int grunt_level, number_of_thoughts, delay;

    /* Find out what rank the player has attained in the guild. */
    grunt_level = TP->query_grunts_level();
    if (grunt_level >= 100)
        grunt_level = 100;
    
    number_of_thoughts = TP->query_prop(LIVE_I_HAS_BEEN_THINKING);
    TP->add_prop(LIVE_I_HAS_BEEN_THINKING, number_of_thoughts+1 );
    
    /* How quickly your head cools is determined by your guild level */
    delay = 350 - ( 2 * grunt_level );

    set_alarm( itof(delay), 0.0, &cool_head(TP) );
    
    write("Your fleas hop around madly as your head rapidly heats up " +
        "from the great effort of thinking.\n");
    allbb(" thinks very hard about something, causing " +
        this_player()->query_possessive() + " head to heat up at an " +
        "alarming rate!\n" + capitalize(this_player()->query_possessive()) +
        " fleas hop around madly because of the heat.");

    return 1;
}


public int
grunt(string str)
{
    object *oblist;
    string *how;
    
    if (!strlen(str))
    {
        write("You grunt like a constipated rhinoceros.\n");
        all(" grunts like a constipated rhinoceros.");
        return 1;
    }
    
    how = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    if (!strlen(how[0]))
    {
        write("You grunt" + how[1] + ".\n");
        all(" grunts" + how[1] + ".");
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Grunt [how] at whom?\n");
        return 0;
    }

    target(" grunts" + how[1] + " at you.", oblist);
    actor("You grunt" + how[1] + " at", oblist);
    all2act(" grunts" + how[1] + " at", oblist);
    return 1;
}

public int
harvest(string str)
{
    object flea;
    int flea_harvest, max_flea_harvest, grunt_level, delay;

    /* How many fleas has this player already harvested? */
    flea_harvest = TP->query_prop(LIVE_I_HARVESTED_FLEAS);
    
    /* Find out what rank the player has attained in the guild. */
    grunt_level = TP->query_grunts_level();
    if (grunt_level >= 100)
        grunt_level = 100;
    
    /* Calculate how many fleas this player is allowed to harvest. */
    max_flea_harvest = (grunt_level / 20) + 1;

    if (flea_harvest >= max_flea_harvest)
    {
        NF("You decide not to risk depleting your flea colony further.\n");
        return 0;
    }
    
    TP->add_prop(LIVE_I_HARVESTED_FLEAS, flea_harvest + 1);
    
    /* How often your fleas reproduce is determined by your guild level */
    delay = 350 - ( 2 * grunt_level );

    set_alarm( itof(delay), 0.0, &add_flea(TP) );

    write("You pluck one of the more substantial fleas from your scalp.\n");
    
    setuid();
    seteuid(getuid(this_object()));
    
    if (TP->query_prop(LIVE_I_HAS_BEEN_THINKING))
    {
        flea = clone_object(GRUNTS_ROASTED_FLEA);
        flea->move(TP);
    }
    else
    {
        flea = clone_object(GRUNTS_LIVE_FLEA);
        flea->move(TP);
    }

    return 1;
}

public int
help(string str)
{
    if (str != "grunts")
        return 0;
    
    setuid();
    seteuid(getuid());

    write(read_file(GRHELP_FILE));
    
    return 1;
}

public int
knuckles()
{
    write("You crack your knuckles.\n");
    all(" cracks " + this_player()->query_possessive() + " knuckles.");
    return 1;
}

public int
leak()
{
   write("You urinate in the corner.\n");
   allbb(" urinates shamelessly in the corner.");
   return 1;
}

public int
munch()
{
    write("You munch on a tasty looking flea, fresh from your scalp.\n");
    allbb(" picks a large flea from " + this_player()->query_possessive() +
        " scalp and munches it slowly.");
    return 1;
}

public int
ogle(string str)
{
    object *oblist;
   
    NF("Ogle whom?\n");
   
    if (!strlen(str))
    {
        write("Ogle whom?\n");
        return 1;
    }
   
    oblist = parse_this(str, " %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" looks lecherously at you.", oblist);
    actor("You ogle", oblist);
    all2actbb(" looks lecherously at", oblist);
    return 1;
}

public int
pick_nose(string arg)
{
    if (arg != "nose")
        return 0;
    write("You pick your nose.\n");
    allbb(" picks " + this_player()->query_possessive() + " nose.");
    return 1;
}

public int
roar(string str)
{
    object *oblist;
   
    NF("Roar at whom?\n");
   
    if (!strlen(str))
    {
        write("You roar like an angry lion, " +
            "revealing the mouldy moss on your teeth.\n");
        all(" roars like an angry lion, revealing the mouldy moss on " +
            TP->query_possessive() + " teeth.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" roars at you like an angry lion, revealing the mouldy moss on " +
        TP->query_possessive() + " teeth.", oblist);
    actor("You roar like an angry lion, revealing the mouldy moss on " + 
        "your teeth to", oblist);
    all2act(" roars like an angry lion at", oblist);
    return 1;
}

public int
stink(string str)
{
    object *oblist;
   
    NF("Fart at whom?\n");
   
    if (!strlen(str))
    {
        write("You let go an absolute stinker, that echoes like thunder.\n");
        all(" lets go an absolute stinker, that echoes like thunder.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" drops a real stinker, and wafts it at you.", oblist);
    actor("You drop a real stinker and waft it at", oblist);
    all2actbb(" drops a real stinker, and wafts it at", oblist);
    return 1;
}

public int
tongue(string str)
{
    object *oblist;
   
    NF("Stick your tongue out at whom?\n");
   
    if (!strlen(str))
    {
        write("You stick your tongue out and catch a passing fly.\n");
        allbb(" catches a passing fly with " 
            + this_player()->query_possessive() + " tongue, and eats it.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" sticks out " + this_player()->query_possessive() +
        " tongue out, and blows you a raspberry.", oblist);
    actor("You stick out your tongue, and blow a raspberry at", oblist);
    all2act(" blows a raspberry at", oblist);
    return 1;
}

public int
warcry(string str)
{
    object *oblist;
   
    string warcry;

    /* Check to see if player has the warcry prop set in them */
    if (!(TP->query_prop(LIVE_S_GRUNTS_WARCRY)))
    {
        write("It seems you do not have a warcry.\n");
        return 1;
    }

    warcry = capitalize(TP->query_prop(LIVE_S_GRUNTS_WARCRY));
    
    NF("Scream your war-cry at whom?\n");
   
    if (!strlen(str))
    {
        write("You scream out loud your war-cry!\n'" + warcry + "'\n");
        all(" screams out loud " + TP->query_possessive() + " war-cry:\n'"
            + warcry + "'");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" screams " + TP->query_possessive() + " war-cry at you:\n'"
        + warcry + "'", oblist);
    actor("You scream your war-cry:\n'" + warcry + "' at", oblist);
    all2act(" screams out loud " + TP->query_possessive() + " warcry:\n'"
        + warcry + "' at", oblist);
    return 1;
}
