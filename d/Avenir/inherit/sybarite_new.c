#pragma strict_types
/* -*-C++-*-
 * file name:     /d/Avenir/inherit/sybarite.c
 * creator(s):    Lilith    9/17/97
 * purpose:       Inheritable component for Sybarites. 
 *                This file will add the cmdsoul below:
 *                   /d/Avenir/common/obj/npc_soul.c
 *  
 *                Makes it possible to configure an NPC with the 
 *                characteristics common to sybarites.
 * 
 * note:          To provide attacks and combat abilities common
 *                to humanoid Sybarites. For use with the
 *                special_attack() function.
 *
 *                See below for list of functions/abilities
 *                and instructions for usage.
 *
 *      Available combat specials: 
 *  Function   Effect
 *  ===================================================================
 *  cdisarm    Disarms (non-damaging attack).
 *  punch      Damaging unarmed attack.
 *  neck       Damaging weapon attack, targets neck.
 *  pluck      Damaging weapon attack.
 *  pommel     Damaging weapon attack, targets face.
 *  skick      Damage&stun unarmed attack, targets legs.
 *
 *      Non-combat special abilities:
 *  Function   Effect
 *  ===================================================================
 *  cure       Cures npc of poisons.
 *  heal       40% chance of healing w/ random messages.
 *
 *
 * --------------------------------------------------------------------
 *
 *  To use the special attack functions, add the following function to
 *  your npc:
 *
 *   int
 *   special_attack(object target)
 *   {
 *       switch (random(6))
 *       {
 *           case 1: command("punch"); 
 *              return 1;    // We are done with this round.
 *           case 2: command("heal me");
 *              return 0;    // Allow another attack in this round.
 *           default: 
 *       }
 *       return 0;
 *   }
 */

inherit  "/std/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/sigil";
inherit "/d/Avenir/inherit/hair_eyes";
inherit "/d/Avenir/inherit/logrotate";


#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/relation.h"

public static string skintone;
public static int check_alarm, prestige;

/* This is for skin tone */
#define TYR_COLOR  "/d/Cirath/tyr/paint/colourob"
/* Ziggurat makeover */
#define MAKEOVER_SHADOW    (ZIG_OBJ + "makeover_shadow")

static void
skin_tone(string str)
{
    object ob = present("_colour_ob_");

    if (!strlen(str))
    {
        if (objectp(ob))
            ob->remove_object();

        return;
    }

    skintone = str;

    if (!objectp(ob))
    {
        ob = clone_object(TYR_COLOR);
        ob->move(this_object());
    }

    ob->set_colour_desc(skintone);
}

public void
create_sybarite(void)
{
    setuid();
    seteuid(getuid());

    /* Lets make it sybarite */
 	MAKE_SYBARITE;
    add_name("sybarite");
    add_prop(LIVE_I_SEE_DARK, 1);
    set_appearance_offset(-(20 +random(31)));
	
    /* Lets add the command soul with the special attacks, etc. */
    add_cmdsoul("/d/Avenir/common/obj/npc_soul");
    update_hooks();
   	
	if (!skintone)
        skin_tone("pale, translucent white");
	
	/* To further customize, add these:
	 set_title("dei Atrei, Experienced Defender of Sybarus");
	 set_syb_house("Atrei");  // List of houses is in  /d/Avenir/inherit/sigil.c
	 add_extra_long("He looks like one of the guards stationed at the Fort of Syabarus.");
     set_size_descs("short", "skinny");  or   set_random_size_descs();
     configure_eyes("confident", "golden", 2);
     configure_hair("shoulder length", "black", "falls about his "+
        "shoulders in waves");   

     clone_object(MAKEOVER_SHADOW)->shadow_me(TO);
     TO->set_unique_look("pleasantly masculine");

     clone_object(BEARD_SHADOW)->shadow_me(TO);
	         TP->add_autoshadow(aut);
	    TP->add_subloc(BEARD_SUBLOC, shadow);

	 add_dancer();
	 add_mummer();
	 
    */

	
}

public void
create_monster(void)
{
    create_sybarite();
}
/*
public string(string s)
add_extra_long()
{
    extra_long = s;	
}	

public string
query_extra_long()
{
    return extra_long;
}
*/
public string 
query_exp_title(void)
{
    return "sybarite "+ ::query_exp_title();
}

private static string ave_sound = one_of_list(({ "lilting", "sybarite" }));

public string 
race_sound(void)
{           
    return "speaks with a "+ ave_sound +" accent";   
}

/* This means whoever kills them is in trouble */
public void
do_die(object killer)
{
    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    /* Mark the murderers */
    WRATHOBJ->load_me();
    WRATHOBJ->mark_enemy(killer);

    ::do_die(killer);
}


/* The functions below handle getting help when attacked */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    /* Give our team a chance to help. */
    foreach(object who : query_team_others())
        who->notify_ob_attacked_me(this_object(), ob);
}

static void
help_friend(object who, object foe)
{
    /* Ignore if attacking or foe isn't nearby. */
    if (query_attack() || !present(foe, environment()))
        return;

    say(QCTNAME(this_object()) + " assists " +
        QTNAME(who) +" and attacks "+ QTNAME(foe) +".\n",
        ({ this_object(), who, foe }) );

    tell_object(foe, query_The_name(foe) +" attacks you!\n");

    attack_object(foe);
    add_prop(LIVE_O_LAST_KILL, foe);
}   

public void
notify_ob_attacked_me(object me, object foe)
{
    float ran;

    /* Ignore if attacking or friend isn't nearby. */
    if (query_attack() || !present(me, environment()))
        return;

    ran = itof(1 + random(3));
    set_alarm(ran, 0.0, &help_friend(me, foe));
}


public string
query_long(void)
{
    string res;

        
    if (!notmet_me(TP))
    {
        res = TO->query_name() + " is " +
            LANG_ADDART(TO->query_nonmet_name()) +
            ", presenting " + TO->query_objective() + "self as:\n" +
            TO->query_presentation() + ".\n";
    }
    else if (!(TO->short(TP)))
    {
        return "";
    }
    else
    {
        res = CAP(TO->query_pronoun()) + " is " +
            LANG_ADDART(TO->short(TP)) +".\n";
    }
/*
    if (extra_long)
        res += extra_long +"\n";    
*/   
    if (obj_long)
        res += check_call(obj_long);

    return res;
}

static void
check_meet(object who, string oname)    {  }

private nomask void
init_meet(object who)
{
    check_alarm = 0;

    if (objectp(who) && present(who, environment()))
        check_meet(who, OB_NAME(who));
}

public void
init_living(void)
{
    ::init_living();

    if (!check_alarm &&
        query_interactive(TP) && CAN_SEE(TO, TP))
    {
        float delay = 1.5 + itof(random(2));
        check_alarm = set_alarm(delay, 0.0, &init_meet(TP));
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc == hair_subloc())
        return gelan_hair();

    if (subloc == eyes_subloc())
        return gelan_eyes();

    return ::show_subloc(subloc, on, for_obj);
}

/* Add the dancer commands. */
static void
add_dancer(void)
{
    add_cmdsoul("/d/Avenir/common/clubs/dance/dancer_soul");
    update_hooks();
}

/* Add the mummer commands. */
static void
add_mummer(void)
{
    add_cmdsoul("/d/Avenir/common/clubs/mummer/mummer_soul");
    update_hooks();
}


