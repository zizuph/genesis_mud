/*
 * /d/Genesis/start/human/sparkle/mouse.c
 * 
 * This file will serve two purposes. The first is to provide
 * a more dynamic generation of a mouse complete with unique
 * descriptions randomly chosen at the time of cloning. The
 * second purpose is to make the mouse more realistic in size
 * and stature as compared to the brand new newbie player. A
 * mouse should be relatively easy to kill even for a newbie.
 *
 * This file was originally modified from mouse.c, created by
 * Styles for the human start area on 22-March-1992.
 *
 * Copyright (c) June 2000, by Shadow deForest (Shadowlynx)
 *
 * Revision history:
 *     March 26, 2013 - general code and style revision (Gorboth)
 *                    - enabled April Fool's Joke (Gorboth)
 */
#pragma save_binary
#pragma strict_types

inherit "/std/creature";         /* generate a generic creature */
inherit "/std/combat/unarmed";   /* reference to unarmed combat */
inherit "/std/act/domove";       /* random move and follow */

#include <ss_types.h>            /* reference to skill types */
#include <wa_types.h>            /* reference to weapon types */
#include <formulas.h>            /* reference to hit/pen etc */
#include <macros.h>              /* reference to names/cloning etc */
#include <const.h>               /* reference to gender */
#include <stdproperties.h>       /* reference to setting properties*/
#include <time.h>                /* reference to date checking */

#define A_BITE  0                /* method of attack */

#define H_HEAD 0                 /* hit locations */
#define H_BODY 1
#define H_TAIL 2

#define APRIL_FOOL_ENABLED        1
#define TELL_G(x) find_living("gorboth")->catch_msg("DEBUG: " + x + "\n")


/* Global Variables */
public string    Randomname = one_of_list( ({ "mouse", "rodent" }) );
public string    Randomadj  = one_of_list( 
                                 ({ "tiny", "small", "large",
                                    "gigantic", "skinny", "fat",
                                    "dirty", "hairy",
                                    "frightened", "scared",
                                    "timid", "confused",
                                    "bewildered", "waterlogged",
                                    "noisy", "sneaky" }) );
public string    Rndcoloradj = one_of_list(
                                 ({ "black", "coal-black", "jet-black",
                                    "gray", "soot-gray", "sable-gray",
                                    "steel-gray", "ashen-gray", "brown",
                                    "silvery-gray", "coppery-brown",
                                    "russet-brown", "sorrel-brown",
                                    "chocolate-brown", "white",
                                    "chalk-white", "snow-white" }) );
public string    April_Fool_Name = "balrog";
public int       Joke_Activated  = 0;
public string    Joke_Date       = "Apr 01";


/* Prototypes */
public void      check_april_fool();
public string    describe_short();
public string    describe_pshort();
public string    describe_long();

public void      set_joke_date(string s) { Joke_Date = s; }
public string    query_joke_date()       { return Joke_Date; }


/*
 * Function name:        create_creature
 * Description  :        set up the creature
 */
public void
create_creature()
{
    if (!IS_CLONE)
	return;

    set_race_name("mouse"); 
    set_name(Randomname);
    add_pname("mice");
    set_adj(Randomadj);
    add_adj(Rndcoloradj);

    set_short(describe_short);
    set_pshort(describe_pshort);
    set_long(describe_long);

    /* sets random gender */
    if(random(2))
	set_gender(G_MALE);
    else
	set_gender(G_FEMALE);

    set_random_move(40); /* allows npc to move around */

    set_stats(({ 1, 3, 2, 1, 1, 2})); /* str/dex/con/int/wis/dis */
    set_skill(SS_SWIM, 45);     /* native skills */

    /* properties */
    add_prop(NPC_I_NO_LOOKS, 1);     /* has no defining looks */
    add_prop(LIVE_I_NEVERKNOWN, 1);  /* never introduced */
    add_prop(LIVE_I_NON_REMEMBER,1); /* unable to remember npc */
    add_prop(LIVE_I_SEE_DARK, 1);    /* npc can see in the dark */
    add_prop(OBJ_I_NO_INS, 1);       /* npc can't be put in container*/
    add_prop(LIVE_I_QUICKNESS, 2);   /* more attacks per combat round */
                                     /* npc cannot be sold */
    add_prop(OBJ_M_NO_SELL, "Set the "+ short() +" free instead.\n");
    remove_prop(OBJ_I_NO_GET);       /* can pick up npc */
    remove_prop(OBJ_I_NO_DROP);      /* can drop npc */
    add_prop(CONT_I_WEIGHT, 1000);   /* weight = 1 kilogram */
    add_prop(CONT_I_HEIGHT, 60);     /* height = 6 centimeters */
    add_prop(CONT_I_VOLUME, 220);    /* volume = 220 milliliters */

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   2, 3, W_IMPALE, 80, "sharp teeth");

    /* Hit_loc, *Ac against (impale/slash/bludgeon/magic), %hit, hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 5, 7, 3, 2 }), 30, "head");
    set_hitloc_unarmed(H_BODY, ({ 2, 4, 8, 0 }), 60, "body");
    set_hitloc_unarmed(H_TAIL, ({ 3, 0, 1, 0 }), 10, "tail");
} /* create_creature */


/*
 * Function name:        check_april_fool
 * Description  :        Check to see if it is April 1st, and if so,
 *                       switch the short description and race name
 *                       to the balrog.
 */
public void
check_april_fool()
{
    string  date = TIME2FORMAT(time(), "mmm dd");

    if (date != Joke_Date)
    {
        if (Joke_Activated)
        {          
            set_race_name("mouse"); 
            set_name(Randomname);
            add_pname("mice");
            remove_name(April_Fool_Name);

            set_short(implode(query_adj(1), " ")
              + " " + lower_case(query_name()));
            set_pshort(implode(query_adj(1), " ")
              + " " + lower_case(query_pname()));

            tell_room(environment(this_object()),
                "There is a sudden flash, and the "
              + April_Fool_Name + " seems to have changed!\n");
            TELL_G("Morphing Balrog back to mouse!");

            Joke_Activated = 0;
        }

        return;
    }

    if (!Joke_Activated)
    {
        set_race_name(April_Fool_Name); 
        set_name(April_Fool_Name);
        remove_pname("mice");
        remove_name(Randomname);

        set_short(implode(query_adj(1), " ")
          + " " + lower_case(query_name()));
        set_pshort(implode(query_adj(1), " ")
          + " " + lower_case(query_pname()));

            tell_room(environment(this_object()),
                "There is a sudden flash, and the "
              + Randomname + " seems to have changed!\n");

            TELL_G("Morphing mouse to Balrog!");

        Joke_Activated = 1;
    }

    return;
} /* check_april_fool */


/*
 * Function name:        describe_short
 * Description  :        We want to have this function called whenever
 *                       someone gets the short desc of the creature
 *                       to see if the date has changed.
 * Returns      :        string - the short desc
 */
public string
describe_short()
{
#ifdef APRIL_FOOL_ENABLED
    check_april_fool();
#endif

    return implode(query_adj(1), " ") + " " + lower_case(query_name());
} /* describe_short */


/*
 * Function name:        describe_pshort
 * Description  :        We want to have this function called whenever
 *                       someone gets the pshort desc of the creature
 *                       to see if the date has changed.
 * Returns      :        string - the pshort desc
 */
public string
describe_pshort()
{
#ifdef APRIL_FOOL_ENABLED
    check_april_fool();
#endif

    return implode(query_adj(1), " ") + " " + lower_case(query_pname());
} /* describe_pshort */


/*
 * Function name:        describe_long
 * Description  :        We want to have this function called whenever
 *                       someone gets the long desc of the creature
 *                       to see if the date has changed.
 * Returns      :        string - the long desc
 */
public string
describe_long()
{
#ifdef APRIL_FOOL_ENABLED
    check_april_fool();
#endif

    return "This "+ lower_case(short()) + " is a regular inhabitant" +
      " among the various warehouses situated along the harbour. It" +
      " twitches its tiny whiskers back and forth as it looks around for" +
      " food. On occasion these rodents can be seen scurrying up" +
      " the rough hemp ropes anchoring ships to the piers.\n";
} /* describe_long */


/*
 * Function name:        init_living
 * Description  :        We want to have this function called whenever
 *                       someone enters the room of the creature
 *                       to see if the date has changed.
 */
public void
init_living()
{
    ::init_living();

#ifdef APRIL_FOOL_ENABLED
    check_april_fool();
#endif
} /* init_living */