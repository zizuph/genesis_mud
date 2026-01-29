// -*-C++-*-
// file name:    Kesoit bow
// creator(s):   Lilith  Jun 2004
// last update:
//             Cotillion 2015-02-14:    LIVE_I_QUICKNESS -> 50
//             Lilith Sep 2011, updated intox check to 50% intox
// purpose:      Something to help out the fledgling archers 
// note:         Magical bow, makes bowyer faster and creates less fatigue
// bug(s):
// to-do: 

inherit "/std/bow";
inherit "lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"

#define INCR 50 
#define WIELD_PROP   "_avenir_kesoit_bow"
#define B_CLONE_LOG  "/d/Avenir/log/misc/magic_bow"
#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 5000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

int alarm_id = 0;

void
create_bow()
{
    set_short("kesoit short bow");
    add_name(({"short bow", "bow"}));
    set_adj(({"kesoit", "wood", "short"}));
    set_long("The kesoit wood of this short bow glows with a blood-red "+
        "lustre. The veins of bright red within the curved wood seem "+
        "to pulse and shift, responding to some stimulus unknown to "+
        "you. The bow itself is perhaps half the height of a human, "+
        "no more, and the grip is made of rune-inscribed black leather. "+
        "\n");
    add_item(({"kesoit", "wood"}),
        "It has been hand-planed until it is smooth as skin. The "+
        "kesoit tree from which it has been made has a natural oil "+
        "that makes oiling or varnishing unnecessary. This natural "+
        "oil is also responsible for the subtle scent that emits "+
        "from the bow.\n");
    add_item(({"runes", "grip", "black leather"}),
        "The runes are carved deep into the black leather and filled "+
        "with a variety of precious metals.\n");
    add_item(({"veins", "grain" }),
        "As you focus on the veins of the kesoit bow, you realize "+
        "that they are pulsing just like the veins of a living "+
        "creature, ebbing and flowing in liquid brightness.\n");
    set_keep();
    set_hit(43 + random(5));
    set_pen(42 + random(6));  
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }) );
    add_prop(OBJ_S_WIZINFO, "This is a short bow made of the kesoit "+
        "tree sacred to Sybarus. It has hit of 43-47 and pen of 42-47. "+
        "Additionally, it grants a speed bonus of "+ INCR +" and "+
        "30-60 fatigue reduction every 15 minutes or so "+
        "while wielded. Cannot be wielded if >50% intoxicated.\n");
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "With gentleness hast the Lord of Doves\n", 10,
        "Bent the branch of the kesoit tree\n", 15,
        "And bound magic to this arc of life and death.\n", 20,
        "How quickly the fletched arrow flies\n", 25,
        "From the tireless arm of the bowyer\n", 30,
        "With music in his heart of hearts\n", 35,
        "And the cooing of doves in his ears.", 40 }));
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1400);
    set_wf(TO);
    seteuid(getuid(TO));
}

/*
 * Function     : do_fat
 * Description  : do fatigue healing
 */
void
do_fat()
{
	int max_tox;
    if (query_wielded())
    {
	    max_tox = query_wielded()->max_intoxicated() / 2;
        if (query_wielded()->query_intoxicated() > (max_tox))
			query_wielded()->command("$unwield kesoit bow");
        else
        {			
            query_wielded()->catch_msg("You find the distant sound of "+
                "cooing doves relaxing and restful, easing the lines "+
                "of fatigue in your body.\n");
            query_wielded()->add_fatigue(30 + random(30));
		}
    }
    else 
        remove_alarm(alarm_id);
    return;
}

/*
 * Function     : wield
 * Description  : Wield a weapon
 * Arguments    : Object what - The weapon to wield
 * Returns      : string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
mixed 
wield(object what)
{
    int go, max_tox;
    /* Is it broken? If so, dont wield */
    if (query_prop(OBJ_I_BROKEN))
        return "It is broken in such a way that you cannot wield it.\n";
    
    /* No infidel check on this one...it is wielded by one */ 

    /* Does living have alcohol level >50% ? If so, don't wield */  
	max_tox = TP->max_intoxicated() / 2;
    if (TP->query_intoxicated() > (max_tox))
        return "The alcohol in your system conflicts with the magic "+
            "of the "+ short() +".\n";
   
    /* All checks have passed, proceed with wielding */
    TP->catch_msg("The "+ short() +" flutters a bit like a bird about "+
        "to take wing, then settles lightly in your hands.\n");
    say(QCTNAME(TP)+" wields the "+short()+" in both hands.\n");
 
    /* I carried this over from the falchion. -Lil */
    if (!TP->query_prop(WIELD_PROP))
    {
        TP->add_prop(LIVE_I_QUICKNESS, 
            TP->query_prop(LIVE_I_QUICKNESS) + INCR);
        TP->add_prop(WIELD_PROP, 1);
    }
 
    alarm_id = set_alarm(1000.0, 1000.0, do_fat);
 
    SCROLLING_LOG(B_CLONE_LOG, capitalize(TP->query_real_name()) +
            " wielded a kesoit bow.");
 
    return 1;
}

 
/* 
 * Function    : unwield
 * Description : Unwield a weapon
 * Arguments   : object wep - the weapon to unwield
 */
mixed 
unwield(object wep)
{
    object owner = query_wielded();
 
    if (owner->query_prop(WIELD_PROP))
    {
        owner->add_prop(LIVE_I_QUICKNESS, 
               owner->query_prop(LIVE_I_QUICKNESS) - INCR);
    }

    remove_alarm(alarm_id);
    owner->remove_prop(WIELD_PROP);
    
    if (!interactive(environment(this_object())))
        return 0;
       
    owner->catch_tell("As you unwield the "+ short() +" it flutters "+
        "in your hands like a bird about to take flight.\n");
 
    return 0;
}
 

