
/* 
  Drown object for the Calia sea.  

  Copyright (C) Miguel Leith 1996 

  This object is moved to players when they enter one of our standard 
  water rooms.  It has three functions: 
        Firstly it monitors the player's fatigue caused by swimming, 
  in both surface deep water rooms and underwater rooms. This includes 
  the dangers of entering deep water when you can't swim. 
        Secondly, in _underwater_ rooms it monitors the respiratory status 
  of the player, by a value from 0 (oxygen debt 0%) to 100000 (oxygen debt 
  100%, you drown). This number is increased on each heartbeat of the drown 
  object, with the size of the increase depending on the MAGIC_I_BREATH_WATER 
  value, the Con stat, and the swim skill.  
        Lastly it makes sure that, of the standard social actions,
  one can only do them if they are reasonable underwater. 


  Coded by Maniac, December 1995 & Jan 1996.
  Last updated by Maniac, 21/3/98
 
  Cotillion - 2020-01-16
  - Fixed division by zero for players without skill

*/
#pragma save_binary

inherit "/std/object";
inherit "/lib/commands";
#include <stdproperties.h>
#include <ss_types.h> 
#include <macros.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Calia/sys/water.h"

#include "sea_objs.h"

#define OK_SURFACE_ANY \
 if (IN_WATER(this_player())) return 0;

#define OK_SURFACE_SHALLOW \
 if (IN_SHALLOW_WATER(this_player())) return 0;

int oxygen_debt; /* 0 is 0% oxygen debt, 100000 is 100% oxygen debt */
int last_signal; /* o.d. when the last indication of drown status was made */
int last_aod; /* last increase in oxygen debt */
int doff; /* this is 1 if wizard drown info is turned off */

object player, mobility_ob;
int mibw; /* Current value of player's MAGIC_I_BREATH_WATER prop */


/*  
 *  reset_oxygen_debt
 *  Breathing as normal, so oxygen debt is reset. 
 */
void
reset_oxygen_debt()
{
     last_signal = 0;
     oxygen_debt = 0; 
}


/* 
   Calculate and return how much to increase the player's oxygen debt by
   for this heartbeat. Returns a value between 0 and 10000 (0 means not only
   that there is no increase in oxygen debt, but that it may be reset,
   because one is breathing as on dry land and hence may "catch one's breath").
*/
int
query_add_oxygen_debt()
{
     int s, c, c_inc, s_inc, inc; 

     if (!objectp(player)) { 
         remove_object();
         return 0;
     } 

     s = max(player->query_skill(SS_SWIM), 1);
     c = max(player->query_stat(SS_CON), 1); 

     /* We must take into account the value of MAGIC_I_BREATH_WATER at this
        time. How we interpret it is given later in this function 
     */
     mibw = player->query_prop(MAGIC_I_BREATH_WATER); 

    /* Calculate the ordinary increase in oxygen debt based on Con and swim 
       skill. Con is considered equally important as the swim skill in 
       determining the increase in oxygen debt, because the swim skill 
       determines how _efficiently_ the player treads water etc. */

    c_inc = (100000 / c); /* 1000 for Con==100; 10000 for Con==10 */

    s_inc = (100000 /(s+10)); /* 1000 for swim skill==90; 10000 for ss==0 */


    inc = c_inc + s_inc; /* Total ordinary increase in oxygen debt */

    /* Now make sure the increase is in the right range */
    if (inc < 2000)
        inc = 2000;       /* So the ordinary maximum time one can stay under
                             water 100000/2000 heartbeats = 50 heartbeats, 
                             which is 500 seconds. */
    else if (inc > 10000) 
        inc = 10000;      /* So the ordinary minimum time one can stay under
                             water 100000/10000 heartbeats = 10 heartbeats,
                             which is 50 seconds */
    /* Note: Yes, I know these durations are a bit on the high side, but 
       let's consider playability here not just realism :) */


    /* Now let's take magic into account */
    /* The higher the property MAGIC_I_BREATH_WATER, the more oxygen one
       can get from the water. A value of 100 means that one is getting 
       as much oxygen as on dry land. */ 

    if (mibw > 0) {
        inc = inc / 10; /* For starters, divide the basic increase in 
                          oxygen debt by 10 if magic is being used: Let's make 
                          this magic have a substantial basic effect no matter 
                          what the level of the magic. */
        inc -= (mibw * inc / 100); /* i.e. reduce the basic oxygen debt by 
                                      a percentage equal to mibw */ 
    }

    return inc;
}


/* Report breathing water status to the player */
string
query_breathe_status_report()
{
    string str;

    if (!objectp(player)) { 
         remove_object();
         return "";
    } 

    if (mibw == 0) 
        return "You are holding your breath.";

    str = "You are breathing water ";
    if ((mibw > 0) && (mibw < 15))
        str += "with practically no success.";
    else if ((mibw >= 15) && (mibw < 30))
        str += "with very little success.";
    else if ((mibw >= 30) && (mibw < 45)) 
        str += "with a little success.";
    else if ((mibw >= 45) && (mibw < 60))
        str += "passably.";
    else if ((mibw >= 60) && (mibw < 70))
        str += "with reasonable success.";
    else if ((mibw >= 70) && (mibw < 80))
        str += "with a lot of success.";
    else if ((mibw >= 80) && (mibw < 90)) 
        str += "with impressive success.";
    else if ((mibw >= 90) && (mibw < 99))
        str += "nearly like a fish!";
    else if (mibw == 100)
        str += "just like a fish!";

    return str;
}


/* Report oxygen debt status to the player */
string
query_oxygen_debt_report()
{
    int opc = oxygen_debt / 1000;
    string str = "Your oxygen debt is ";

    if (!objectp(player)) { 
        remove_object();
        return "";
    } 

    if (opc == 0) 
        str += "minimal.";
    else if ((opc > 0) && (opc < 15))
        str += "minor.";
    else if ((opc >= 15) && (opc < 30))
        str += "ok.";
    else if ((opc >= 30) && (opc < 45)) 
        str += "tolerable.";
    else if ((opc >= 45) && (opc < 55))
        str += "somewhat uncomfortable.";
    else if ((opc >= 55) && (opc < 65))
        str += "very uncomfortable.";
    else if ((opc >= 65) && (opc < 75))
        str += "serious.";
    else if ((opc >= 75) && (opc < 85)) 
        str += "dangerous.";
    else if ((opc >= 85) && (opc < 93))
        str += "desperate!";
    else if ((opc >= 93) && (opc < 100))
        str += "very close to fatal!";
    else if (opc >= 100)
        str += "killing you!";

    return str;
}


/* 
 * do_drown, 
 * This function carries out the drowning of a player 
 */ 
void
do_drown()
{
     log_file("water", player->query_name() + " drowned in " + 
              file_name(environment(player)) + " at " + 
              ctime(time()) + ".\n");
     player->catch_msg("You drown!\n");
     tell_room(environment(player), QCTNAME(player) + " drowns!\n", player);
     player->heal_hp(-(player->query_max_hp()));
     player->do_die(this_object());
     if (player->query_wiz_level())
         player->catch_msg("You would have died now, wiz.\n");
     remove_object();
}



/* 
 *  do_swim_effect. 
 *  This means add fatigue if player is swimming, depending on swim skill. 
 *  If player can't swim, they will be flailing and will drown if they 
 *  run out of fatigue points.
 */
void
do_swim_effect()
{
    int ss;

    if (!objectp(player)) { 
        remove_object(); 
        return;
    } 

    /* If we aren't in deep water, no problem, as one is not even 
       swimming. */  
    if (IN_SHALLOW_WATER(player))
        return;

    ss = player->query_skill(SS_SWIM);  
    if (ss > 40) 
         ss = 40;

    if (ss == 0) { 
        player->add_fatigue(-10);  
        player->catch_msg("You flail madly and swallow water as you " +
                          "cannot swim!\n"); 
        all(" flails madly and swallows water as " + 
            player->query_pronoun() + " cannot swim!"); 
        if (player->query_fatigue() == 0)  {
            do_drown(); 
            return;
        }
     }
     else  
         player->add_fatigue(-4 + (ss / 10)); 
}




/* 
   We have a heartbeat to make sure that we adjust the ability to breathe
   under water to the effect of magic, for instance the value of  
   player->query_magic_res(MAGIC_I_BREATH_WATER) may have changed, as may
   the player's CON stat, because of spells, or getting some magical item. 
   If we don't make regular checks for this a player can lose out or benefit
   unrealistically. The heartbeat informs the player if his/her respiratory
   status.
 */
void
drown_ob_heartbeat()
{
    int aod, in_water_room;

    if (!objectp(player) || player->query_ghost()) { 
        remove_object(); 
        return;
    } 

    /* If linkdead, keep object active but don't increase oxygen debt */
    if (player->query_linkdead())  {
        set_alarm(itof(DROWN_HEARTBEAT), 0.0, drown_ob_heartbeat);
        return;
    }

    /* This is a paranoid check, the drown object should be automatically 
       removed by the standard water rooms when one leaves them for an open
       air room. */
    in_water_room = (environment(player)->query_standard_water_room());

    if (!in_water_room) { 
        remove_object();
        return;
    } 

    /* The main swim skill factor. */ 
    do_swim_effect(); 

    /* Naturally if you're only _in_ water you don't have to hold your
       breath or breathe water, so exit this function now. */ 
    if (environment(player)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER) {
        set_alarm(itof(DROWN_HEARTBEAT), 0.0, drown_ob_heartbeat);
        return;
    }

    aod = query_add_oxygen_debt();
    if (aod == 0) 
        reset_oxygen_debt(); 
    else
        oxygen_debt += aod; /* Otherwise oxygen debt increased */

    /* Give a status message if it's relevant */
    if (((oxygen_debt - last_signal) >= 2000) ||
        (last_aod != aod) || (oxygen_debt >= 78000)) {
        player->catch_msg("\n" + query_breathe_status_report() + " " + 
                          query_oxygen_debt_report() + "\n");
        last_signal = oxygen_debt;
    }

    last_aod = aod;

    if (oxygen_debt >= 78000) 
        tell_room(environment(player), QCTNAME(player) + " seems to " +
                  "be having oxygen debt problems.\n", player);

    if (player->query_wiz_level() && !doff) 
        player->catch_msg("Wiz info: your oxygen debt is " + 
                          (oxygen_debt / 1000) + "." + 
                          ((oxygen_debt % 1000) / 100) +
                          ((oxygen_debt % 100) / 10) +
                          (oxygen_debt % 10) +
                          "%. Turn this msg off with <ox>.\n");

    if (oxygen_debt >= 100000) /* A drowning! */  {
         do_drown(); 
         return;
    }

    set_alarm(itof(DROWN_HEARTBEAT), 0.0, drown_ob_heartbeat);
}


/* 
 * All the torches in the deep inventory of the player should 
 * fizzle out when they first enter deep water. This is called from  
 * the standard water room. 
 */
void
extinguish_lights()
{
    object *inv;
    int i;

    if (!objectp(player)) { 
        remove_object();
        return;
    } 

    inv = deep_inventory(player);

    for (i = 0; i < sizeof(inv); i++) {
         if (inv[i]->query_lit(0) == -1)
             inv[i]->burned_out();
    }
}


void
create_object()
{
    set_short(DROWN_OBJECT_NAME);
    set_long(DROWN_OBJECT_NAME);
    set_name(DROWN_OBJECT_NAME);
    /* so player won't see in inventory */
    set_no_show();
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_M_NO_INS, 1);
}



void
wiz_cmds(object ob)
{
    ob->catch_msg("Drown object is now present: commands are " +
                  "<ox>, <br>, <ds>.\n"); 
}


/* 
 * The drown object enters the inventory of any living that hasn't 
 * got gills (this is controlled from water rooms). 
 * For efficiency in water rooms checking for the presence of a drown
 * object, the property LIVE_O_DROWN_OB is added here. 
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (living(to)) {
        seteuid(getuid()); 
        player = to;
        mobility_ob = clone_object(MOBILITY_OBJECT); 
        mobility_ob->move(player, 1); 
        oxygen_debt = 0;
        last_signal = 0;
        last_aod = 0;
        doff = 1;
        if (to->query_wiz_level())
            set_alarm(1.0, 0.0, &wiz_cmds(to)); 
    }
    else { 
        remove_object();
        return;
    } 

    to->add_prop(LIVE_O_DROWN_OB, this_object());
    set_alarm(2.0, 0.0, drown_ob_heartbeat);
}


void 
leave_env(object from, object to)
{
    from->remove_prop(LIVE_O_DROWN_OB);
    mobility_ob->remove_object(); 
    ::leave_env(from, to);
}




/* *********************************************************************
 *  Next come the communication actions and related functions for in or
 *  under water. Many of the standard emotes don't when in or under
 *  water rooms and so have to be adapted. 
 * ******************************************************************** */

int 
shout()
{
     OK_SURFACE_ANY; 
     write(NO_SAY_UNDER_WATER);
     return 1;
}


int 
rsay()
{
     OK_SURFACE_ANY; 
     write(NO_SAY_UNDER_WATER);
     return 1;
}


int 
whisper()
{
     OK_SURFACE_ANY; 
     write(NO_SAY_UNDER_WATER);
     return 1;
}


public int
communicate(string str = "")
{
    OK_SURFACE_ANY; 

    /* Doesn't the ''' look cute? It is the fastest ;-) */
    if (query_verb()[0] == ''')
    {
        str = extract(query_verb(), 1) + " " + str;
    }

    all(" signals: " + str, "", 0, "signal");

    if (this_player()->query_option(OPT_ECHO))
        write("You signal: " + str + "\n");
    else
        write("Ok.\n");

    this_player()->gmcp_comms("signal", 0, "You signal: " + str + "\n");

    return 1;
}




/* *********************************************************************
 *    Next come all the emotes and related functions for under water 
 *    Many of the standard emotes don't with with underwater rooms and 
 *    so have to be adapted. 
 * ******************************************************************** */


/* Underwater ack */
int
ack(string str)
{
    OK_SURFACE_ANY;

    write("You go `blbbck!'\n");
    all(" goes `blbbck!'");
    return 1;
}


/* admire did not need changing */


/* Under water agreement */
int
agree(string str)
{
    object *oblist, tp;
    string qp;

    OK_SURFACE_ANY;

    tp = this_player();
    qp = tp->query_possessive();

    if (!stringp(str)) {
        write("You nod your head in agreement.\n");
        allbb(" nods " + qp + " head in agreement.");
        return 1;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
        write("Agree with whom?\n");
        return 1;
    }

    targetbb(" nods " + qp + " head in agreement at you.", oblist);
    actor("You nod your head in agreement at", oblist);
    all2actbb(" nods " + qp + " head in agreement at", oblist);
    return 1;
}


/* Give someone an apologetic look. */
int
apologize(string str)
{
    object *oblist, tp;

    OK_SURFACE_ANY;

    if (!stringp(str)) {
        write("You look apologetic.\n");
        allbb(" looks apologetic.");
        return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        write("Give whom an apologetic look?\n");
        return 1;
    }

    targetbb(" gives you an apologetic look.", oblist);
    actor("You give", oblist, " an apologetic look.");
    all2actbb(" gives", oblist, " an apologetic look.");
    return 1;
}


/* Under water applause */  
int 
applaud(string str)
{
    object *oblist, tp;

    OK_SURFACE_ANY;

    if (!stringp(str)) {
        write("You give a slow motion round of applause.\n");
        all(" gives a slow motion round of applause.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Applaud whom?\n");
        return 1;
    }

    targetbb(" gives you a slow motion round of applause.", oblist);
    actor("You give", oblist, " a slow motion round of applause.");
    all2actbb(" gives", oblist, " a slow motion round of applause.");
    return 1;
}


/* bat did not need changing */


/* Under water beg */
int
beg(string str)
{
    object *oblist;
    object tp = this_player();
    string pn = tp->query_pronoun();

    OK_SURFACE_ANY;

    if (!stringp(str)) { 
        write("Beg whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l [pardon] [forgiveness]");

    if (!sizeof(oblist)) {
        write("Beg whom?\n");
        return 1;
    }

    target(" swims underneath you and begins " +
           "a doggy paddle. It seems " + pn + 
            " is begging.", oblist);
    actor("You swim underneath", oblist, " and begin " +
        "a doggy paddle. Well, that is the nearest you can get to " +
        "begging under water!");
    all2act(" swims underneath", oblist, " and begins a doggy " +
            "paddle. It seems " + pn + " is begging.");
    return 1;
}


/* bite and blush did not need changing */


/* under water bounce attempt */
int
bounce(string str)
{
    OK_SURFACE_SHALLOW;

    write("You try to bounce around but end up flailing madly instead.\n");
    all(" tries to bounce around but ends up flailing madly instead.");
    return 1;
}


/* under water bow */
int
bow(string str)
{
    object *oblist;

    OK_SURFACE_SHALLOW;

    if (!stringp(str))
    {
        write("You swim upright and make an attempt at bowing.\n");
        allbb(" swims upright and makes an attempt at bowing.");
        return 1;
    }

    oblist = parse_this(str, "[to] / [before] [the] %l");

    if (!sizeof(oblist))
    {
        write("Bow to whom?\n");
        return 1;
    }

    targetbb(" swims upright and makes an attempt at bowing to you.", 
             oblist);
    actor("You swim upright and make an attempt at bowing to", oblist);
    all2actbb(" swims upright and makes an attempt at bowing to", oblist);
    return 1;
}


/* brighten did not need changing */

/* under water burp */
int
burp()
{
    OK_SURFACE_ANY;

    write("You burp, producing a single large bubble that floats upwards.\n");
    all(" burps, producing a single large bubble that floats upwards.");
    return 1;
}


/* under water cackle */
int
cackle()
{
    OK_SURFACE_ANY;

    write("You throw your head back and let out a gargling cackle!\n");
    all(" throws " + this_player()->query_possessive() +
        " head back and lets out a gargling cackle!");
    return 1;
}


/* caress does not need changing */


/* under water cheer */
int
cheer(string str)
{
    object *oblist;
    string p = this_player()->query_possessive();

    OK_SURFACE_ANY;

    if (!stringp(str))
    {
        write("You raise your arms and give a gargling cheer!\n");
        all(" raises " + p + " arms and give a gargling cheer!");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("Cheer at whom?\n");
        return 1;
    }

    target(" raises " + p + " arms and directs a gargling cheer at you!", 
           oblist);
    actor("You raise your arms and directs a gargling cheer at", oblist, "!");
    all2act(" raises " + p + " arms and directs a gargling cheer at", 
                    oblist, "!");
    return 1;
}


/* choke can stay the same */ 


/* under water chortle */
int
chortle()
{
    OK_SURFACE_ANY;

    write("You let out little chortling bubbles.\n");
    all(" lets out little chortling bubbles.");
    return 1;
}


/* under water chuckle */
int
chuckle()
{
    OK_SURFACE_ANY;

    write("You give a bubbly chuckle.\n");
    all(" gives a bubbly chuckle.");
    return 1;
}


/* under water clap */
int
clap(string str)
{
    object *oblist;
    string *how;

    OK_SURFACE_ANY;

    if (!stringp(str))
    {
        all(" claps in slow motion.");
        write("You clap in slow motion.\n");
        return 1;
    }

    oblist = parse_this(str, "[for] / [to] [the] %l");

    if (!sizeof(oblist))
    {
        write("Clap at whom?\n");
        return 1;
    }

    target(" claps in slow motion at you.", oblist);
    actor("You clap in slow motion at", oblist);
    all2act(" claps in slow motion at", oblist);
    return 1;
}

/* comfort can stay as normal */

/* under water complaint */
int
complain(string str)
{
    object *oblist;

    OK_SURFACE_ANY;

    if (!stringp(str))
    {
        write("Complain to whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        write("Complain to whom?\n");
        return 1;
    }

    targetbb(" gives you a look of complaint.", oblist);
    actor("You give", oblist, " a look of complaint.");
    all2actbb(" gives", oblist, " a look of complaint.");
    return 1;
}


/* under water compliment */
int
compliment(string str)
{
    object *oblist;

    OK_SURFACE_ANY;

    if (!stringp(str)) {
        write("Compliment whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Compliment whom?\n");
        return 1;
    }

    targetbb(" nods " + this_player()->query_possessive() +
        " head at you in complimentary fashion.", oblist);
    actor("You nod your head at", oblist, " in complimentary fashion.");
    all2actbb(" nods " + this_player()->query_possessive() +
        " head at", oblist, " in complimentary fashion.");
    return 1;
}

/* "conf", "confuse", "confused", "congrat" and "congratulate" 
   can stay as normal */ 


/* Cannot enter converse mode under water */
int
converse()
{
    OK_SURFACE_ANY;

    write("You may not converse under water.\n");
    return 1;
}


/* under water cough */
int
cough()
{
    OK_SURFACE_ANY;

    write("You cough, producing a several small bubbles which float " +
          "upwards.\n");
    all(" coughs, producing several small bubbles which float upwards.");
    return 1;
}


/* under water cower */
int
cower()
{
    OK_SURFACE_SHALLOW;

    write("You try unsuccessfully to perform the act of cowering while " +
          "treading water.\n");
    allbb(" tries unsuccessfully to perform the act of cowering while " +
          "treading water.");
    return 1;
}


/* under water cringe */
int
cringe(string str)
{
    object *oblist;

    OK_SURFACE_SHALLOW;
    if (!stringp(str))
    {
        write("You cringe in terror and start to float slowly downwards.\n");
        allbb(" cringes in terror and starts to float slowly downwards.");
        return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        write("Cringe to whom?\n");
        return 1;
    }

    targetbb(" cringes in terror from you and starts sinks slowly " +
          "downwards.", oblist);
    actor("You cringe in terror from", oblist, " and start to sink slowly " +
          "downwards.");
    all2actbb(" cringes in terror from", oblist, " and starts to sink slowly " +
              "downwards.");
    return 1;
}


/* under water cry */
int
cry(string str)
{
    object *oblist;

    OK_SURFACE_SHALLOW;
    if (!stringp(str))
    {
        write("You burst into tears, adding yet " +
              "more water to the surroundings.\n");
        all(" bursts into tears, adding yet more water to the surroundings.");
        return 1;
    }

    oblist = parse_this(str, "[on] [the] %l");

    if (!sizeof(oblist))
    {
        write("Cry [on] whom?\n");
        return 1;
    }

    if (sizeof(oblist) > 1) {
        write("You can only cry on one person's shoulder at once.\n");
        return 1;
    }

    str = this_player()->query_possessive();
    target(" swims over, rests " + str + " head on your shoulder " +
           "and cries " + str + " heart out, as if " +
           "you weren't soaked enough already.", oblist);
    actor("You swim over, rest your head on", oblist,
        "'s shoulder and cry your heart out, as if " +
        oblist[0]->query_pronoun() + " wasn't soaked enough already.");
    all2act(" swims over, rests " + str + " head on", oblist,
        "'s shoulder and cries " + str + " heart out, making " +
        oblist[0]->query_objective() + " even more soaked.");
    return 1;
}


/* cuddle can stay as normal */


/* under water curtsey */
int
curtsey(string str)
{
    object *oblist;

    OK_SURFACE_SHALLOW;

    if (!stringp(str))
    {
        write("You swim upright and make an attempt at curtseying.\n");
        allbb(" swims upright and makes an attempt at curtseying.");
        return 1;
    }

    oblist = parse_this(str, "[to] / [before] [the] %l");

    if (!sizeof(oblist))
    {
        write("Curtsey to whom?\n");
        return 1;
    }

    targetbb(" swims upright and makes an attempt at curtseying to you.", 
             oblist);
    actor("You swim upright and make an attempt at curtseying to", oblist);
    all2actbb(" swims upright and makes an attempt at curtseying to", oblist);
    return 1;
}


/* under water dance */
int
dance(string str)
{
    object *oblist;

    OK_SURFACE_SHALLOW;

    if (!stringp(str))
    {
        write("You do the funky fish.\n");
        all(" does the funky fish.");
        return 1;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
        write("Dance with whom?\n");
        return 1;
    }

    target(" does some synchronised swimming with you.", oblist);
    actor("You do some synchronised swimming with", oblist);
    all2act(" does some synchronised swimming with", oblist);
    return 1;
}

/* "despair" can stay as normal */


/* under water disagreement */
int
disagree(string str)
{
    object *oblist;
    object tp = this_player();

    OK_SURFACE_ANY;
    if (!stringp(str))
    {
        write("You shake your head in disagreement.\n");
        allbb(" shakes " + tp->query_possessive() + " head in disagreement.");
        return 1;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
        write("Disagree with whom?\n");
        return 1;
    }

    targetbb(" shakes " + tp->query_possessive() + " head at you " +
            "in disagreement.", oblist);
    actor("You shake your head at", oblist, " in disagreement.");
    all2actbb(" shakes " + tp->query_possessive() + " head at", oblist, 
              " in disagreement.");
    return 1;
}


/* under water duh */
int
duh(string str)
{
    object *oblist;
    object tp = this_player();

    OK_SURFACE_ANY;
    if (!stringp(str))
    {
        write("You knock on your head.\n");
        all(" knocks on " + tp->query_possessive() + " head.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist)) {
        write("Duh at whom?\n");
        return 1;
    }

    if (sizeof(oblist) == 1)
        str = "head";
    else
        str = "heads";

    target(" knocks on your head.", oblist);
    actor("You knock on the " + str + " of", oblist);
    all2actbb(" knocks on the " + str + " of", oblist);
    return 1;
}


/* under water eeks */
int
eeks()
{
    OK_SURFACE_ANY;
    write("You go `bleep!'\n");
    all(" goes `bleep!'");
    return 1;
}


/* "explodes" and "eyebrow "can stay as normal */


/* under water fart */
int
fart()
{
    OK_SURFACE_SHALLOW;
    write("You let off a real ripple-bubbler.\n");
    all(" lets off a real ripple-bubbler.");
    return 1;
}


/* "fawn" and "finger" can stay as normal */


/* under water flip */
int
flip()
{
    OK_SURFACE_SHALLOW;

    write("You paddle head over heels rapidly.\n");
    all(" paddles head over heels rapidly.");
    return 1;
}


/* flirt, fondle, forgive, french and frown can stay as normal */


/* under water fume */
int
fume(string str)
{
    object *oblist;

    OK_SURFACE_ANY;
    if (!stringp(str))
    {
        write("You fume, boiling the water nearby.\n");
        allbb(" fumes, boiling the water nearby.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("Fume at whom?\n");
        return 1;
    }

    targetbb(" fumes at you, boiling the water nearby.", oblist);
    actor("You fume at", oblist, ", boiling the water nearby.");
    all2actbb(" fumes at", oblist, ", boiling the water nearby.");
    return 1;
}

/* "gag" can stay as normal */


/* under water gasp */
int
gasp(string str)
{
    OK_SURFACE_ANY;
    write("You let out a sharp stream of bubbles in astonishment.\n");
    all(" lets out a sharp stream of bubbles in astonishment!");
    return 1;
}


/* under water giggle */
int
giggle()
{
    OK_SURFACE_ANY;
    write("You giggle, making a sound like a mountain stream.\n");
    all(" giggles, making a sound like a mountain stream.");
    return 1;
}


/* "glare", "greet" and "grin" "grope" can stay as normal */

/* under water groan */
int
groan()
{
    OK_SURFACE_ANY;
    write("You groan, producing a sound like water filling a tin bath tub.\n");
    all(" groans, producing a sound like water filling a tin bath tub.");
    return 1;
}


/* under water grovel */
int
grovel(string str)
{
    object *oblist;

    OK_SURFACE_SHALLOW;

    if (!stringp(str)) {
        write("Grovel in front of whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[to] / [for] / [before] [the] %l");

    if (!sizeof(oblist))
    {
        write("Grovel in front of whom?\n");
        return 1;
    }

    target(" swims up to you with head bowed, grovelling.", 
           oblist);
    actor("You swim up to", oblist, " with head bowed, grovelling.");
    all2act(" swims up to", oblist, " with head bowed, grovelling.");
    return 1;
}


/* under water growl */
int
growl(string str)
{
    object *oblist;
    string s = ("producing a sound like rocks grating on the " +
                "underside of a boat.");

    OK_SURFACE_ANY;
    if (!stringp(str))
    {
        write("You growl, " + s + "\n");
        all(" growls, " + s);
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("Growl at whom?\n");
        return 1;
    }

    target(" growls at you, " + s, oblist);
    actor("You growl at", oblist, ", " + s);
    all2act(" growls at", oblist, ", " + s);
    return 1;
}


/* under water unhappy */
int
grumble(string str)
{
    object *oblist;
    string s = ("releasing a stream of frustrated looking bubbles.");

    OK_SURFACE_ANY;
    if (!stringp(str))
    {
        write("You grumble, " + s + "\n");
        all(" grumbles, " + s);
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("Grumble at whom?\n");
        return 1;
    }

    target(" grumbles at you, " + s, oblist);
    actor("You grumble at", oblist, ", " + s);
    all2act(" grumbles at", oblist, ", " + s);
    return 1;
}


/* under water hiccup */
int 
hiccup()
{
    OK_SURFACE_ANY;

    write("You go `blip!', an under water hiccup!\n");
    all(" goes `blip!', an under water hiccup!");
    return 1;
}


/* under water hmm */
int
hmm(string str)
{
    OK_SURFACE_ANY;

    write("You go blublublublublublub.\n");
    all(" goes blublublublublublub.");
    return 1;
}


/* "hold", "hug" as normal */

/* under water ignore */
int
ignore(string str)
{
    object *oblist;

    OK_SURFACE_SHALLOW;

    if (!stringp(str))
    {
        write("Ignore whom?\n");
        return 1;
    }
    
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Ignore whom?\n");
        return 1;
    }

    targetbb(" swims away and starts to ignore you.", oblist);
    actor("You swim away and start to ignore", oblist);
    all2actbb(" swims away and starts to ignore", oblist);
    return 1;
}


int
jump()
{
    object tp = this_player();

    OK_SURFACE_SHALLOW;

    write("You make a strange lurch as you try to jump in deep water.\n");
    all(" makes a strange lurch as " + tp->query_pronoun() +
        " tries to jump in deep water.");
    return 1;
}


/* kick and kiss can stay as normal */

/* under water knee */
int
knee(string str)
{
    object *oblist;
    object *femlist;

    if (!stringp(str)) {
        write("Knee whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Knee whom?\n");
        return 1;
    }

    femlist = FILTER_GENDER(oblist, G_FEMALE);

    if (sizeof(femlist))
    {
        target(" tries to knee you, without much effect.", femlist);
        actor("You try to knee", femlist, ".\nNot very effective though.");
        all2act(" tries to knee", femlist, ".\nNot very effective though.");
    }

    oblist -= femlist;
    if (sizeof(oblist))
    {
        target(" hits you with " + this_player()->query_possessive() +
            " knee below your belt!\n" +
            "You double over, writhing in excruciating pain!", oblist);
        actor("You hit", oblist, " with your knee!");
        all2act(" suddenly raises " + this_player()->query_possessive() +
            " knee, making", oblist, " writhe in excruciating pain!");
    }
    return 1;
}


/* under water laugh */
int
laugh(string str)
{
    object *oblist;

    OK_SURFACE_ANY;
    if (!stringp(str))
    {
        write("You laugh like a gurgling fountain.\n");
        all(" laughs like a gurgling fountain.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("Laugh at whom?\n");
        return 1;
    }

    target(" laughs like a gurgling fountain at you.", oblist);
    actor("You laugh like a gurgling fountain at", oblist, ".");
    all2act(" laughs like a gurgling fountain at", oblist);
    return 1;
}


/* Can't light things in deep water if you aren't a wizard. */ 
int
light()
{
    object tp = this_player(); 

    if (UNDER_WATER(tp) || IN_DEEP_WATER(tp)) {
        if (!tp->query_wiz_level()) { 
            tell_object(tp, "You cannot light things when in deep water.\n"); 
            return 1;
        } 
        tell_object(tp, "As you are a wizard, you can use the light " +
                        "command in deep water and under water.\n");
    }
    return 0;
}


/* under water love */
int
love(string str)
{
    object *oblist;

    OK_SURFACE_ANY;
    if (!stringp(str)) {
        write("Love whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Love whom?\n");
        return 1;
    }

    target(" looks lovingly at you.", oblist);
    actor("You look lovingly at", oblist);
    all2act(" looks lovingly at", oblist);

    return 1;
}


/* under water moan */
int
moan()
{
    OK_SURFACE_ANY;
    write("You start to moan, releasing a sorry collection of " +
          "dreary bubbles.\n");
    all(" starts to moan, releasing a sorry collection of dreary bubbles.");
    return 1;
}


/* "lick","nibble", "nod", "nudge", "oops", "panic", "pat", "peer",
   "pinch", "point", "poke", "ponder", "pout"  can stay the same */


/* under water puke */
int
puke(string str)
{
    write("You puke into the water all around yourself, leaving a messy " +
          "orange-green cloud hanging there.\n");
    all(" pukes into the water all around " + this_player()->query_objective() 
        + "self, leaving a messy orange-green cloud hanging there.");
    return 1;
}


/* under water purr */
int
purr(string str)
{
    OK_SURFACE_ANY;
    write("You purr like a catfish!\n");
    all(" purrs like a catfish!");
    return 1;
}



/* under water roar */
int
roar(string str)
{
    OK_SURFACE_ANY;
    write("You roar like a sea lion!\n");
    all(" roars like a sea lion!");
    return 1;
}


/* "rolleyes" can stay the same */


/* under water ruffle */
int
ruffle(string str)
{
    object *oblist;

    OK_SURFACE_ANY;
    if (!stringp(str)) {
        write("Ruffle whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Ruffle whom?\n");
        return 1;
    }

    target(" ruffles your soaking wet hair.", oblist);
    actor("You ruffle", oblist, "'s soaking wet hair.");
    all2act(" ruffles", oblist, "'s soaking wet hair.");
    return 1;
}


/* under water scold */
int
scold(string str)
{
    object *oblist;

    OK_SURFACE_ANY;
    if (!stringp(str))
    {
        write("Scold whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Scold whom?\n");
        return 1;
    }

    target(" waggles an irate finger at you!", oblist);
    actor("You waggle an irate finger at", oblist);
    all2act(" waggles an irate finger at", oblist);
    return 1;
}


/* "scowl" "scratch" "shiver, "shake", "shrug", "slap" can stay the same */

/* under water scream */
int
scream(string str)
{
    OK_SURFACE_ANY;
    write("You scream, producing a flurry of frantic bubbles!\n");
    allbb(" screams, producing a flurry of frantic bubbles!");
    return 1;
}




/* under water sigh */
int
sigh()
{
    OK_SURFACE_ANY;
    write("You try to sigh but take in a mouth full of water.\n");
    all(" tries to sigh but takes in a mouth full of water.");
    return 1;
}


/* under water sing */
int
sing()
{
    OK_SURFACE_ANY;
    write("You let out a musical gargling sound.\n");
    all(" lets out a musical gargling sound.");
    return 1;
}


/* smile, snuggle, smirk, spank, squeeze, squirm and snap can stay the same */

/* under water snarl */
int
snarl(string str)
{
    object *oblist;

    OK_SURFACE_ANY;
    if (!stringp(str)) {
         write("You snarl like a dogfish!\n");
         allbb(" snarls like a dogfish!");
         return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("Snarl at whom?\n");
        return 1;
    }

    target(" snarls at you like a dogfish!", oblist);
    actor("You snarl at", oblist, " like a dogfish!");
    all2act(" snarls at", oblist, " like a dogfish!");
    return 1;
}

/* under water sneeze */
int
sneeze()
{
    OK_SURFACE_ANY;
    write("You sneeze into the water. The mucus hangs there " +
          "offensively in front of your nose.\n");
    all(" sneezes into the water. The mucus hangs there offensively " +
        "in front of " + this_player()->query_possessive() + " nose.");
    return 1;
}


/* under water snicker */
int
snicker()
{
    OK_SURFACE_ANY;
    write("You snicker out some evil bubbles.\n");
    all(" snickers out some evil bubbles.");
    return 1;
}


/* under water sniff */
int
sniff()
{
    OK_SURFACE_ANY; 
    write("Sniffing under water is not advisable!\n");
    return 1;
}


/* under water snore */
int
snore()
{
    OK_SURFACE_ANY; 
    write("You look tired and bored.\n");
    all(" looks tired and bored.");
    return 1;
}


/* under water spit */
int
spit()
{
    write("You spit into the water in disgust. It doesn't get very far.\n");
    all(" spits into the water in disgust. It doesn't get very far.");
    return 1;
}


/* stare, startle, stretch, thank, think can stay the same */

/* under water stomp */
int
stomp()
{
    object tp = this_player();

    OK_SURFACE_SHALLOW; 

    write("You make a strange lurch as you try to stomp in deep water.\n");
    all(" makes a strange lurch as " + tp->query_pronoun() +
        " tries to stomp in deep water.");
    return 1;
}


/* under water strut */
int
strut()
{
    OK_SURFACE_SHALLOW; 
    write("You swim around cockily.\n");
    all(" swims around cockily.");
    return 1;
}


/* under water sulk */
int
sulk(string str)
{
    OK_SURFACE_SHALLOW;
    write("You swim upside down, sulking.\n");
    allbb(" swims upside down, sulking.");
    return 1;
}


/* under water swear */
int
swear()
{
    OK_SURFACE_ANY;
    write("You mime some colourful expletives.\n");
    all(" mimes some colourful expletives.");
    return 1;
}


/* under water tackle */
int
tackle(string str)
{
    object *oblist;

    if (!stringp(str)) {
        write("Tackle whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Tackle whom?\n");
        return 1;
    }

    target(" tackles you awkwardly.", oblist);
    actor("You tackle", oblist, " awkwardly.");
    all2act(" tackles", oblist, " awkwardly.");
    return 1;
}


/* under water tap :) */
int
tap()
{
    OK_SURFACE_SHALLOW; 

    write("You stop paddling and make tapping motions with your foot.\n");
    all(" stops paddling and makes tapping motions with " + 
        this_player()->query_possessive() + " foot.");
    return 1;
}


/* tickle, tremble, twiddle, twinkle, wave as normal  */

/* under water whine */
int
whine(string str)
{
    object *oblist;

    OK_SURFACE_ANY;

    if (!stringp(str))
    {
        write("You look ready to whine but are frustrated by the sub-aqua " +
             "environment.\n");
        allbb(" looks ready to whine but is frustrated by the sub-aqua " +
             "environment.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        write("Whine at whom?\n");
        return 1;
    }

    targetbb(" looks ready to whine at you but is frustrated by the " +
            "sub-aqua environment.", oblist);
    actor("You look ready to whine at", oblist, " but are frustrated " +
          "by the sub-aqua environment.");
    all2actbb(" looks ready to whine at", oblist, " but is frustrated by " +
              "the sub-aqua environment.");
    return 1;
}


/* under water swear */
int
whistle()
{
    OK_SURFACE_ANY; 

    write("You blow out a stream of bubbles.\n");
    all(" blows out a stream of bubbles.");
    return 1;
}


/* wiggle and wink as normal */

/* under water worship */
int
worship(string str)
{
    object *oblist;

    OK_SURFACE_SHALLOW; 

    if (!stringp(str)) {
        write("Worship whom?\n");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Worship whom?\n");
        return 1;
    }

    target(" swims around you with head bowed in worship.", oblist);
    all2act(" swims around", oblist, " with head bowed in worship.");
    actor("You swim around", oblist, " with head bowed in worship.");
    return 1;
}


/* under water yawn */
int
yawn(string str)
{
    object *oblist;

    OK_SURFACE_ANY;

    if (!stringp(str))
    {
        write("You yawn like a hippopotamus.\n");
        all(" yawns like a hippopotamus.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        write("Yawn at whom?\n");
        return 1;
    }

    targetbb(" yawns at you like a hippopotamus.", oblist);
    actor("You yawn at", oblist, " like a hippopotamus.");
    all2act(" yawns at", oblist, " like a hippopotamus.");
    return 1;
}


/* under water yodel */
int
yodel(string str)
{
    OK_SURFACE_ANY;

    write("You go `Yygggllllgggllllugg!'\n");
    all(" goes `Yygggllllgggllllugg!'");
    return 1;
}


/* Wizards may want to switch off oxygen debt percentage messages */
int
ox()
{
    object tp = this_player();
    string mess; 

    if (!tp->query_wiz_level())
        return 0;

    if (doff) {
       mess = "You will now be notified of oxygen debt percentages.\n"; 
       doff = 0; 
    }
    else {
       mess = "You will no longer be notified of oxygen debt percentages.\n"; 
       doff = 1;
    }

    write(mess);
    return 1;
}


/* Wizards may want to set their water breathing to various levels */ 
int 
br(string str)
{
     int l;
     object tp = this_player(); 

     if (!tp->query_wiz_level())
         return 0;

     if (!stringp(str)) { 
         notify_fail("Syntax: br <0-100>.\n"); 
         return 0;
     }

     if (sscanf(str, "%d", l) == 1) { 
         if ((l < 0) || (l > 100))  {
              notify_fail("Must be in the range 0-100.\n"); 
              return 0;
         }
         tp->add_prop(MAGIC_I_BREATH_WATER, l); 
         tp->catch_msg("Ok, you breathe water with effectiveness " + l + 
                       " out of 100.\n"); 
         return 1;
     }

     notify_fail("Syntax: br <0-100>.\n"); 
     return 0;
}


int
ds()
{
     object tp = this_player(); 

     if (!tp->query_wiz_level())
         return 0;

     tp->catch_msg("Drown object removed.\n"); 
     remove_object(); 
     return 1;
}


/* 
   Called from the standard water_room code on each move, 
   so that we can always trap move verbs such as "north" etc. 
 */ 
void
reset_trap_move()
{
    mobility_ob->update_actions(); 
} 


/* Set up commands for standard underwater actions and emotes */
void
init()
{
    ::init();

    add_action(ox, "ox");
    add_action(br, "br"); 
    add_action(ds, "ds"); 

    /* Communication:  */
    /* ask must be allowed, gotta be practical with quests. */
    add_action(rsay, "rsay"); 
    add_action(shout, "shout");  
    add_action(communicate, "'", 1);
    add_action(communicate, "signal");
    add_action(communicate, "say");
    add_action(whisper, "whisper");

    /* general emotes */
    add_action(ack, "ack"); 
    add_action(agree, "agree"); 
    add_action(apologize, "apologize"); 
    add_action(applaud, "applaud");
    add_action(beg, "beg"); 
    add_action(bounce, "bounce"); 
    add_action(bow, "bow"); 
    add_action(burp, "burp"); 
    add_action(cackle, "cackle");   
    add_action(cheer, "cheer");  
    add_action(chortle, "chortle"); 
    add_action(chuckle, "chuckle"); 
    add_action(clap, "clap"); 
    add_action(complain, "complain"); 
    add_action(compliment, "compliment"); 
    add_action(converse, "converse"); 
    add_action(cough, "cough");  
    add_action(cower, "cower"); 
    add_action(cringe, "cringe"); 
    add_action(cry, "cry");  
    add_action(curtsey, "curtsey"); 
    add_action(dance, "dance"); 
    add_action(disagree, "disagree"); 
    add_action(duh, "duh");   
    add_action(eeks, "eeks"); 
    add_action(fart, "fart");  
    add_action(flip, "flip"); 
    add_action(fume, "fume"); 
    add_action(gasp, "gasp"); 
    add_action(giggle, "giggle"); 
    add_action(groan, "groan");  
    add_action(grovel, "grovel"); 
    add_action(growl, "growl"); 
    add_action(grumble, "grumble"); 
    add_action(hiccup, "hiccup"); 
    add_action(hmm, "hmm"); 
    add_action(ignore, "ignore");  
    add_action(jump, "jump"); 
    add_action(knee, "knee");  
    add_action(laugh, "laugh");  
    add_action(light, "light");
    add_action(love, "love"); 
    add_action(moan, "moan");
    add_action(puke, "puke");  
    add_action(purr, "purr");
    add_action(roar, "roar"); 
    add_action(ruffle, "ruffle"); 
    add_action(scold, "scold");   
    add_action(scream, "scream"); 
    add_action(sigh, "sigh");  
    add_action(sing, "sing"); 
    add_action(snarl, "snarl"); 
    add_action(sneeze, "sneeze"); 
    add_action(snicker, "snicker");
    add_action(sniff, "sniff");
    add_action(snore, "snore");
    add_action(cry, "sob"); 
    add_action(spit, "spit"); 
    add_action(stomp, "stomp"); 
    add_action(strut, "strut"); 
    add_action(sulk, "sulk"); 
    add_action(swear, "swear"); 
    add_action(tackle, "tackle");
    add_action(tap, "tap"); 

    add_action(whine, "whine"); 
    add_action(whistle, "whistle"); 
    add_action(worship, "worship"); 
    add_action(yawn, "yawn");   
    add_action(yodel, "yodel");
}

