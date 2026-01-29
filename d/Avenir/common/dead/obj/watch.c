 //   watch             (/d/Avenir/common/dead/obj/watch.c)
 // creator(s):       Glinda june -95
 // last update:      Lilith Aug 2014
 //                   Lilith Dec 2007
 //                   Lilith Feb 2015 Added magic props. Changed speed from 150 to 30.
 //                   Cotillion Apr 2017 - Fixed various issues related to the effect
 //                         too high and not terminating.
 //                   Lilith updated statserv log topic from "dead" to "necronisi"
 //                   Lilith Nov 2021 Added a counter to limit the number of USES
 //                      before it self-destructs.
 //
 // purpose:          A watch that can be repaired for a small bit of quest exp.
 //                   It gives the time in Sybarus.
 //                   It is also useful for the Catacombs quests on the Necronisi. 
 //                Player must be at same 'speed' as Banshee to interact with her.
 //                   Wind the watch, and time speeds up for the player,
 //                   ie, it adds live_i_quickness 30 until the power 
 //                   source runs down in 45 minutes.
 //                   Stop the watch and the quickness is removed. 
 // notes:    Some might think that watches are not 'medieval' but in 
 //           fact the first personal timepieces were made ~1500.
 //           Cloned after searching in room /d/Avenir/common/port/ledge
 // bug(s):
 // to-do:

inherit "/std/object";
inherit "/lib/keep";
inherit "/d/Avenir/inherit/quest";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"

#define QLOG "/d/Avenir/log/quest/fix_watch"

// This keeps people from benefitting from multiple watches
#define WIND_PROP   "_av_wind_watch"

// crystals power down 5 minutes after warning
#define DESTRUCT_TIME                   600.0
// power-down time in 45 minutes, give warning 
#define BATT 2700
// player gets 6 winds of the watch for 4.5 hours of play.
// stopping it and winding it still counts as a use.
#define USES 6

int open, source, fixed, incr, wind, batt, btime, count;

int i = 5;
int alarm_id;
int power_alarm;
int dest_alarm;

/* Prototypes */
int do_tick(object who);
void self_destruct();
void start_fade();

void 
reset_watch()
{
    open = 0;
    source = 0;
    fixed = 0;
    incr = 0;
    wind = 0;
    batt = 0;
    btime = 0;
}

string
my_long()
{
    string str1, str2;
    string where = file_name(environment(TP));
    int hour = 0;

    if (!fixed)
    {
        str1 = "";
        str2 = "It does not appear to be in working order.\n";
    }

    if (fixed)
    {
#include "/sys/language.h"        
        str1 =" The "+ 
        LANG_WORD("/d/Avenir/inherit/avenir_time"->get_avenir_hour()) +
        " symbol seems to pulse with an inner light, indicating "+
        "that it is the "+ capitalize(
        LANG_WORD("/d/Avenir/inherit/avenir_time"->get_avenir_hour())) +
        " hour in Sybarus.";
        if (where == "/d/Avenir/common/dead/hill/cairn")
            str2 ="\n     The golden watch hums and glows with an eldritch light.\n";
        else str2 ="\n";
	}
    
    return "A golden pocket watch with an attached chain and "+
      "a winding mechanism at the top. "+
      "A piece of thin glass covers the face, which is missing "+
      "the arms characteristic of most watches. Instead of numbers, "+
      "twelve small symbols have been etched into the surface, "+
      "which appears to be made of mother-of-pearl."+ str1 +" "+ str2;
}

void
create_object()
{
    set_short("golden watch");
    set_pshort("golden watches");
    set_name("watch");
    set_pname("watches");
    add_name(({"_avenir_hours_amulet_", "amulet", "disk"}));
    add_adj(({"gold","golden"}));
    set_long(my_long);
    add_item(({"surface", "face", "mother-of-pearl"}), "The face of "+
      "the watch is made of mother-of-pearl, and has that character"+
      "istic fluid opacity to it. Twelve symbols have been etched "+
      "into it.\n");
    add_item(({"chain"}), "A gold chain is attached to the watch.\n");
    add_item(({"mechanism", "winding mechanism", "knob"}), 
       "The winding mechanism is a small knob located at the top "+
       "of the watch.\n");
    add_item(({"symbols", "symbol"}), "There are twelve symbols "+
       "finely etched into the mother-of-pearl surface, each "+
       "evenly spaced along the edges.\n");
    add_item("first symbol", "It is an octagon with a lock and key.\n");
    add_item("second symbol", "It is a circle divided by a jagged line.\n");
    add_item("third symbol", "It is a crescent outlined in flames.\n");
    add_item("fourth symbol", "It is the outline of an eye.\n");
    add_item("fifth symbol", "It is a stylus within a circle.\n");
    add_item("sixth symbol", "It is a cross on a coin-like circle.\n");
    add_item("seventh symbol", "It is a knife within two half-merged circles.\n");
    add_item("eighth symbol", "It is a pentagram within a circle.\n");
    add_item("ninth symbol", "It is a clenched fist.\n");
    add_item("tenth symbol", "It is a simple rectangle.\n");
    add_item("eleventh symbol", "It is a wand crossed with a wavy line.\n");
    add_item("twelfth symbol", "It is two opposing triangles.\n");

    add_prop( OBJ_I_VOLUME, 97);
    add_prop( OBJ_I_WEIGHT, 240);
    add_prop( OBJ_I_VALUE, "@@value");
    add_prop( OBJ_S_SEARCH_FUN, "do_search");
    add_prop( OBJ_I_SEARCH_TIME, 5 );
	add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment"}));
	add_prop(MAGIC_AM_ID_INFO,({
		"The "+short()+" is mildly enchanted.\n",1,
		"When fixed and wound, it will add quickness to whomever "+
		"owns it.", 30, }));
    add_prop(OBJ_S_WIZINFO,"This is an object used by two quests. "+
        "When powered-up and wound-up, it will give 30 points of "+
        "haste to the player for about 45 minutes. Can be found "+
		"via searching in room: /d/Avenir/common/port/ledge\n");

    set_keep(1); 

   seteuid(getuid());
   reset_watch();
}

void
set_power_check_time()
{
    power_alarm = set_alarm(itof(btime), 0.0, &start_fade());
}

int
my_id(object ob)
{
    // this is /d/Avenir/common/outpost/obj/lsource.c 
	// found at /d/Avenir/common/ledge/ledge4, limit 10 pieces per reset.
    if( ob->id("_avenir_Source_gives_light_"))
        return 1;
    return 0;
}

int
do_close(string str)
{
    if(str != "hatch")
        return 0;
    if(!open)
    {
        NF("The hatch is closed already.\n");
        return 0;
    }
    open = 0;
    if(fixed || !source)
    {
        write("You close the hatch again.\n");
        return 1;
    }
    fixed = 1;
    add_name("_avenir_hours_amulet_");
    if(TP->test_bit("Avenir", 0, 16)) 
    {
        write("The watch starts ticking slowly.\n"+
			  "You feel a little more experienced in general.\n");
        TP->add_exp_general(100 + random(50));
        return 1;
    }
    write_file(QLOG, TP->query_name() + " fixed the watch and got 2000 xp "
        + ctime(time()) + "\n");
    write("Congratulations! You fixed the watch!\n");
    reward_quest("Fix Watch", TP, 0, 16, 2000);
    write("The watch starts ticking slowly.\n");
    return 1;
}

int
do_insert(string str)
{
   object ob, *obs;

    if(str != "source in hatch" && str != "crystal in hatch" &&
        str != "source into hatch" && str != "crystal into hatch" )
        return 0;
    if(fixed)
    {
        NF("The watch has been repaired already.\n");
        return 0;
    }
    if(source)
    {
        NF("There is already some crystal in the hatch.\n");
        return 0;
    }
    if(!open)
    {
        NF("But the hatch is closed.\n");
        return 0;
    }

    if( present("_avenir_Source_gives_light_", TP) )
    {
        obs=filter(all_inventory(TP), my_id);
        ob=obs[0];
        ob->remove_object();
        write("You place the piece of source into the hatch. "+
            "It fills the opening completely.\n");
        /*Source is in */
        source = 1;
        /* Battery fully charged */
        btime = BATT;
        /* Time to run out not set */
        batt = 0;
        return 1;
    }
    return 0;
}

int
do_listen(string str)
{
    NF("Listen to what?\n");
    if(str != "to watch" && str != "watch")
        return 0;
    
    if (environment() != this_player()) {
        return 0;
    }
    
    if (fixed)
        alarm_id = set_alarm(0.5, 1.5, &do_tick(TP));
    else
        write("You hear nothing.\n");
    say(QCTNAME(TP) + " holds a golden watch to " + TP->query_possessive()
        + " ear.\n");
    return 1;
}

int
do_tick(object who)
{
   if(i)
      who->catch_msg("TICK\n");
   else
   {
      remove_alarm(alarm_id);
      i=6;
      who->catch_msg("You stop listening to the watch.\n");
   }
   i--;
}

void
add_effect(object player)
{
    if (!player->query_prop(WIND_PROP)) { 
        player->inc_prop(LIVE_I_QUICKNESS, 30);
        player->add_prop(WIND_PROP, 1);
    }
}

void
remove_effect(object player)
{
    if (player->query_prop(WIND_PROP)) {
        player->inc_prop(LIVE_I_QUICKNESS, -30);
        player->remove_prop(WIND_PROP);
    }
}

int 
wind_effect(object pl)
{
    string where = file_name(environment(pl));

    if (pl->query_prop(WIND_PROP))
        return 1;

    if (IS_INFIDEL(pl))
        return 1;

    wind = 1;
    add_effect(pl);

    pl->catch_tell("As you look up from the face of the watch you notice "+
       "something odd...everything seems to be moving slower in relation "+
       "to you.\n");
	STATSERV_LOG_EVENT("necronisi", "Watch wound");

    /* Set time to run out of batteries */
    batt = btime + time();
    set_power_check_time();
    return 1;        
}

/* This is called when the watch has exceeded it number of uses */
public void
dest_it(void)
{
    write("The old "+ short() +" crumbles to pieces in your hands. How sad!\n");
    remove_object();
}

/* Wind the watch, this brings player up to the same speed as the banshee */
int
do_wind(string str)
{
    NF("Wind what?\n");
    if(str != "watch")
    {
        return 0;
    }

    if(str == "watch")
    {
        if (environment() != this_player()) {
            return 0;
        }
        
        if (!fixed)
        {
            write("You turn the knob and wind the watch.\nNothing happens.\n");
            say(QCTNAME(TP) + " winds a golden watch.\n");
            return 1;
        }
		if (wind == 2)
        {
            write("The watch is coming apart in your hands!");
            return 1;			
        }	  
        if (wind == 1)
        {
			
            write("Its been wound it up tight enough! Any tighter "+
                "and you will break it.\n");     
            return 1;
        }
        if (TP->query_prop(WIND_PROP))
        {
            write("You've wound it up tight enough! Any tighter "+
                "and you will break it.\n");     
            return 1;
        }
		
        ++count;
        if (count > USES)
        {
	        int dest_alarm;	
            dest_alarm = set_alarm(15.0, 0.0, dest_it);
			write("You turn the knob and it snaps off!\n");
			wind = 2;
			return 1;
		}
		
        wind = 1;       
        write("You turn the knob and wind the watch.\n");
        say(QCTNAME(TP) + " winds a golden watch.\n");
        set_alarm(1.0, 0.0, &wind_effect(TP));
        return 1;
   }
}

int
do_open(string str)
{
   if( str != "hatch")
      return 0;
   write("You open the small hatch on the back of the watch.\n");
   open = 1;
   return 1;
}

/* Stop the watch, turn off the quickness, save it for the banshee */
void
stop_watch(object pl)
{
    int t;

    wind = 0;

    /* How much time is left on the battery */
    t = (batt - time());
    if (t > 0)
        btime = t;
    else 
        reset_watch();


    if (pl->query_prop(WIND_PROP))
    {
        //hopefully this ck will keep msgs out of the lp and debug logs
        if (interactive(pl))
            pl->catch_tell("You notice that time seems to have resumed "+ "its normal tempo.\n");
    }

    remove_effect(pl);
}

/* Stop the watch, turn off the quickness, save it for the banshee */
int
do_stop(string str)
{
    int t;

    if(str != "watch")
        return 0;
    if (!fixed)
    {
        write("You push on the winding mechanism.\nNothing happens.");
        return 1;
    }
    if (!wind)
    {
        write("You push on the winding mechanism.\nNothing happens.");
        return 1;
    }
    
    write("You press on the winding mechanism, causing it to unwind, "+
       "and thus the watch to stop.\n");
    remove_alarm(power_alarm);
    stop_watch(this_player());
    
    return 1;
}    

string
do_search(object searcher, string str)
{
   if(TP->query_skill(SS_AWARENESS) < 29)
      return 0;
   if(str != "watch" )
      return 0;
   add_item(({"hatch","hollow"}), "A small hollow in the back of the " +
      "watch. @@hatch_state@@\n");
   return "There is a small hatch on the back side of the watch.\n";
}

string
hatch_state()
{
   if(!open)
      return "The hatch is closed.";
   if(source)
      return "A piece of glowing mineral has been inserted into the " +
             "hatch, filling the opening.";
   else
      return "The hatch has been opened. It is empty.";
}

int
value()
{
   if(fixed)
      return 3500;
   else
      return 350;
}


void
start_destruct_timer()
{
    set_alarm(DESTRUCT_TIME, 0.0, &self_destruct());   
} 


/* This actually just clears the crystal and breaks the watch */
void
self_destruct()
{
    object *envs;
    object current_room;

    envs = all_environment(this_object());
    current_room = envs[sizeof(envs) - 1];

    tell_room(current_room, 
        "The illumination of the golden watch flickers and dies.\n" );

    // No more power, no more quickness
    stop_watch(environment(this_object()));

    //reset everything: time to find another crystal
    remove_name("_avenir_hours_amulet_");
    reset_watch();
} 

void
start_fade()
{
    object *envs;
    object current_room;

    envs = all_environment(this_object());
    current_room = envs[sizeof(envs) - 1];

    tell_room(current_room, "You hear a faint cracking noise and the " +
        "golden watch seems to flicker.\n");
    
    start_destruct_timer();
}


void
init()
{
    ::init();

    if (environment() != this_player()) {
        return;
    }

    add_action("do_listen","listen");
    add_action("do_insert","put");
    add_action("do_insert","insert");
    add_action("do_insert","place");
    add_action("do_insert","fit");
    add_action("do_insert","force");
    add_action("do_wind","wind");
    add_action("do_open","open");
    add_action("do_close","close");
    add_action("do_stop", "stop");
}

void
leave_env(object from, object to)
{

    //stop watch and remove props from the player
    stop_watch(from);

    ::leave_env(from, to);

}
