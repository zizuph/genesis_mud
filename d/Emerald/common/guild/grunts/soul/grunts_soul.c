/* This is what you've all been waiting for... the infamous Grunts soul!  */
/* With a bit of luck it will give Goblins the important position of      */
/* being the most disgusting, foul race on the face of Genesis.           */
/* This soul was based on the work of others - Tricky, Quis, Nick et al.  */
/* The original soul was developed by Tulix I, 29/3/1993.                 */
/* Recoded 11/08/95 with various improvements, Tulix III.                 */

/* Adverbs added to 'grunt' command, 'crap' command recoded 04/11/95.     */
/* Recoded to improve fault tolerance 27/12/95.                           */
/* Fleas added and grnews, grlevels & grhelp recoded 04/05/96.            */
/* Recruit function added 27/01/2000 by Tulix V.                          */

inherit "/cmd/std/command_driver";
inherit "/d/Emerald/lib/help";

/* These two lines are put in to keep Mercade happy */
#pragma strict_types
#pragma save_binary  

#include <macros.h>
#include <adverbs.h>
#include "../guild.h"

#include "idea.c"

void
create()
{
    set_help_type(({ "grunts", "grunt" }));
    read_help_dir(GRUNTS_HELP_DIR);
}

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
        "gridea"     : "_idea",
        "grshake"    : "grshake",
        "grthink"    : "grthink",
        "grunt"      : "grunt",
        "harvest"    : "harvest",
        "knuckles"   : "knuckles",
        "leak"       : "leak",
        "leave"      : "_leave",
        "munch"      : "munch",
        "ogle"       : "ogle",
        "pick"       : "pick_nose",
//      "recruit"    : "recruit",
        "roar"       : "roar",
        "smells"     : "smells",
        "stink"      : "stink",
        "tongue"     : "tongue",
        "warcry"     : "warcry"
    ]) + help_cmdlist();
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

    if (!strlen(str))
    {
        write("You flick the bird to the heavens above.\n");
        allbb(" flicks the bird to the heavens above.\n");
        return 1;
    }
   
    oblist = parse_this(str, "[to] [the] %l");
   
    if (!sizeof(oblist))
    {
        notify_fail("Flick the bird to whom?\n");
        return 0;
    }
      
    targetbb(" flicks you the bird. Thats not very nice.", oblist);
    actor("You flick the bird to", oblist);
    all2actbb(" flicks the bird to", oblist);
    return 1;
}

public int
breath(string str)
{
    object *oblist;
   
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
    {
        notify_fail("At whom do you wish to aim your breath?\n");
        return 0;
    }
   
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
   
    if (!strlen(str))
    {
        write("You headbutt the nearest convenient object.\n");
        allbb(" headbutts the nearest convenient object.");
        return 1;
    }
   
    oblist = parse_this(str, " %l");
   
    if (!sizeof(oblist))
    {
        notify_fail("Whom do you wish to headbutt?\n");
        return 0;
    }
   
    target(" headbutts you in the stomach. You collapse to the floor."
        , oblist);
    actor("You headbutt", oblist," in the stomach, who falls to the floor.");
    all2actbb(" headbutts", oblist," in the stomach, who falls to the floor.");
    return 1;
}

public int
crap(string str)
{
    object crap, room;
    int crap_number, delay, full, grunt_level;

    if (strlen(str))
    {
        return 0;
    }

    room = environment(this_player());
    full = this_player()->query_stuffed();

    if (this_player()->query_prop(LIVE_I_CRAPPED_NUMBER) >= 2)
    {
        write("You have already crapped recently.....\n");
        return 1;
    }
    
    notify_fail("You have not had enough to eat to do that.\n");
    if(full < 80)
        return 0;
    
    crap_number = this_player()->query_prop(LIVE_I_CRAPPED_NUMBER);
    this_player()->add_prop(LIVE_I_CRAPPED_NUMBER, crap_number + 1);
    
    grunt_level = this_player()->query_grunts_level();
    if (grunt_level >= 100)
        grunt_level = 100;
    
    /* How often you can crap is determined by your guild level */
    delay = 350 - ( 2 * grunt_level );

    set_alarm( itof(delay), 0.0, &allow_crap(this_player()));

    write("You defecate on a convenient spot.\n");
    setuid();
    seteuid(getuid(this_object()));
    crap = clone_object(GRUNTS_CRAP);
    crap ->move(room);
    allbb(" defecates on a convenient spot.");
    this_player()->eat_food(-80);
    
    this_player()->remove_prop(LIVE_I_SLIP_POSSIBLE); /* So player won't slip in crap */

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
        notify_fail("Curse [how] whom?\n");
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
   
    notify_fail("Wiggle your ears at whom?\n");
   
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
   
    notify_fail("Pull silly faces at whom?\n");
   
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
   
    notify_fail("Shake your fist at whom?\n");
   
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
   
    notify_fail("Flick a bogey at whom?\n");
   
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
   
    notify_fail("Flob a brown hocker at whom?\n");
    
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
        notify_fail("Drool [how] over whom?\n");
        return 0;
    }
    
    target(" drools saliva" + how[1] + " over you.", oblist);
    actor("You drool saliva" + how[1] + " over", oblist);
    all2actbb(how[1] +" drools saliva over", oblist);
    return 1;
}

public int
grshake(string str)
{
    object *oblist;
    string init_str;

    init_str = str;

    notify_fail("Spit on you hand, and then shake hands with whom?\n");
    
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
    grunt_level = this_player()->query_grunts_level();
    if (grunt_level >= 100)
        grunt_level = 100;
    
    number_of_thoughts = this_player()->query_prop(LIVE_I_HAS_BEEN_THINKING);
    this_player()->add_prop(LIVE_I_HAS_BEEN_THINKING, number_of_thoughts+1 );
    
    /* How quickly your head cools is determined by your guild level */
    delay = 350 - ( 2 * grunt_level );

    set_alarm( itof(delay), 0.0, &cool_head(this_player()) );
    
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
        notify_fail("Grunt [how] at whom?\n");
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
    flea_harvest = this_player()->query_prop(LIVE_I_HARVESTED_FLEAS);
    
    /* Find out what rank the player has attained in the guild. */
    grunt_level = this_player()->query_grunts_level();
    if (grunt_level >= 100)
        grunt_level = 100;
    
    /* Calculate how many fleas this player is allowed to harvest. */
    max_flea_harvest = (grunt_level / 20) + 1;

    if (flea_harvest >= max_flea_harvest)
    {
        notify_fail("You decide not to risk depleting your flea colony further.\n");
        return 0;
    }
    
    this_player()->add_prop(LIVE_I_HARVESTED_FLEAS, flea_harvest + 1);
    
    /* How often your fleas reproduce is determined by your guild level */
    delay = 350 - ( 2 * grunt_level );

    set_alarm( itof(delay), 0.0, &add_flea(this_player()) );

    write("You pluck one of the more substantial fleas from your scalp.\n");
    
    setuid();
    seteuid(getuid(this_object()));
    
    if (this_player()->query_prop(LIVE_I_HAS_BEEN_THINKING))
    {
        flea = clone_object(GRUNTS_ROASTED_FLEA);
        flea->move(this_player());
    }
    else
    {
        flea = clone_object(GRUNTS_LIVE_FLEA);
        flea->move(this_player());
    }

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
_leave(string str)
{
    if (!strlen(str) || (lower_case(str) != "grunts"))
    {
        return 0;
    }

    notify_fail("If you want to leave the Grunts guild, you must return to the"
      + " guildhall and do so there.\n");
    return 0;
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
   
    notify_fail("Ogle whom?\n");
   
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

/*
 * This function has been disabled, as the guild is now reopened.
 */
public int
recruit(string str)
{
    int grunt_level;
    object collar, *oblist, spike;
    string spike_material;

    grunt_level = this_player()->query_grunts_level();

    notify_fail("You're not big enough to be able to recruit just yet.\n");
    if (!(this_player()->query_wiz_level()) && (grunt_level <= 25))
        return 0; /* Need to be at least an adventurer to recruit */

    if (!strlen(str))
    {
        write("You look around for potential Grunts to recruit.\n");
        allbb(" looks around for potential Grunts to recruit.");
        return 1;
    }
   
    oblist = parse_this(str, "%l");

    notify_fail("Recruit whom?\n");
    if (!sizeof(oblist))
        return 0; /* Fail, can't find the specified target */
    
    notify_fail("One at a time! One at a time!!\n");
    if (sizeof(oblist) > 1)
        return 0; /* Fail, more than one target */

    notify_fail("Apparently, the Grunts guild is only for Goblins.\n");
    if (oblist[0]->query_race_name() != "goblin")
        return 0; /* Fail, can only recruit one race into a race guild */

    notify_fail("You can't recruit those who are already Grunts.\n");
    if (oblist[0]->query_guild_member(GUILD_NAME))
        return 0; /* Fail, don't waste time recruiting existing members */

    notify_fail("It seems that another race guild already has this one.\n");
    if (oblist[0]->query_guild_name_race())
        return 0; /* The Grunts is not the only race guild these days */

    collar = present("grunts_collar", this_player());
    notify_fail("You do not have a collar! So, alas - no spikes to give.\n");
    if ( !(this_player()->query_wiz_level()) && !(collar) )
        return 0;

    spike_material = collar->spike_desc();

    if (!(spike_material))
    {
        spike_material = "spikes"; /* Just in case collar isn't working */
    }

    target(" takes one of the " + spike_material + " from " + 
        this_player()->query_possessive() +
        " collar and gives it to you.", oblist);
    actor("You take one of the " + spike_material + " from your collar " +
        "and give it to", oblist);
    all2actbb(" takes a spike from " + this_player()->query_possessive() +
        " collar and gives it to", oblist);

    setuid();
    seteuid(getuid(this_object()));       /* Need this to be able to clone */
    spike = clone_object(GRUNTS_SPIKE);                   /* Clone a spike */
    spike->set_recruiting_grunt(this_player());         /* Set spike owner */
    spike->move(oblist[0]);                    /* Give the spike to target */

    return 1; /* Joining the guild is handled by the spike */
}

public int
roar(string str)
{
    object *oblist;
   
    notify_fail("Roar at whom?\n");
   
    if (!strlen(str))
    {
        write("You roar like an angry lion, " +
            "revealing the mouldy moss on your teeth.\n");
        all(" roars like an angry lion, revealing the mouldy moss on " +
            this_player()->query_possessive() + " teeth.");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" roars at you like an angry lion, revealing the mouldy moss on " +
        this_player()->query_possessive() + " teeth.", oblist);
    actor("You roar like an angry lion, revealing the mouldy moss on " + 
        "your teeth to", oblist);
    all2act(" roars like an angry lion at", oblist);
    return 1;
}

nomask int
filter_members(object ob)
{
    if (!ob->query_guild_member(GUILD_NAME))
    {
        return 0;
    }

    if (ob->query_wiz_level() && ob->query_invis())
    {
        return 0;
    }

    if (wildmatch("*jr", ob->query_real_name()))
    {
        return 0;
    }

    return 1;
}

nomask int
order_members(object ob1, object ob2)
{
    int l1 = ob1->query_grunts_level(),
        l2 = ob2->query_grunts_level();

    return ((l1 > l2) ? 1 : ((l1 == l2) ? 0 : -1));
}

public int
smells(string str)
{
    int i, lsize;
    object *list;
   
    if (strlen(str))
    {
        return 0;
    }

    list = filter(users(), filter_members);
    list = sort_array(list, order_members);

    str = "";
    lsize = sizeof(list);
   
    write("You can smell the following:\n");
   
    for (i = 0; i < lsize; i++ )
    {
        str += "- " + list[i]->query_name() + 
        " the " + list[i]->query_guild_title_race() + "\n";
    }

    write(str + 
        "===================================================\n" +
        "Total number of smelly Grunts: " + lsize + "\n");
    say(QCTNAME(this_player()) + " carefully smells the air for fellow Grunts.\n");
    return 1;
}

public int
stink(string str)
{
    object *oblist;
   
    notify_fail("Fart at whom?\n");
   
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
   
    notify_fail("Stick your tongue out at whom?\n");
   
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
    if (!(this_player()->query_prop(LIVE_S_GRUNTS_WARCRY)))
    {
        write("It seems you do not have a warcry.\n");
        return 1;
    }

    warcry = capitalize(this_player()->query_prop(LIVE_S_GRUNTS_WARCRY));
    
    notify_fail("Scream your war-cry at whom?\n");
   
    if (!strlen(str))
    {
        write("You scream out loud your war-cry!\n'" + warcry + "'\n");
        all(" screams out loud " + this_player()->query_possessive() + " war-cry:\n'"
            + warcry + "'");
        return 1;
    }
   
    oblist = parse_this(str, "[at] %l");
   
    if (!sizeof(oblist))
        return 0;
   
    target(" screams " + this_player()->query_possessive() + " war-cry at you:\n'"
        + warcry + "'", oblist);
    actor("You scream your war-cry:\n'" + warcry + "' at", oblist);
    all2act(" screams out loud " + this_player()->query_possessive() + " warcry:\n'"
        + warcry + "' at", oblist);
    return 1;
}
