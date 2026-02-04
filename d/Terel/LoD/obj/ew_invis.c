/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_invis.c
 *
 * A spell-like object that added invisiblity to the player/npc
 * Tailored for the evil warlord Mergula
 *
 * Checks for anti-magic and can be dispelled.
 *
 */

#include "/d/Terel/include/Terel.h"
#include <comb_mag.h>
inherit STDOBJECT;

int query_time_left();
void set_duration(int t);
int query_my_invis();
void set_my_invis(int i);

int invis_set_by_me = 0;
int id_dur, my_invis = 0;
int delta_i;
int duration;

void
create_object()
{
    set_name("_mergula_sword_invis_effect");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(MAGIC_AM_MAGIC, 1);
    add_prop(OBJ_S_WIZINFO,
	  "This is the invisibility object related to Mergula's "+
        "sword.\n");
    set_long("This is the invisibility object related to Mergula's "+
        "sword.\n");
    set_no_show();
}

void
enter_env(object dest, object old)
{
    int old_i, new_i;

    ::enter_env(dest, old);
    if (living(dest)) 
    {
        old_i = dest->query_prop(OBJ_I_INVIS);
	  new_i = old_i + query_my_invis();
 
	  if (new_i > 100) 
            new_i = 100;
	  delta_i = new_i - old_i;

        if (delta_i > 0) 
        {
            dest->catch_msg("Energy flows through your entire body "+
                "and projects outward, creating an invisibility "+
                "shield around you.\n");
            say(QCTNAME(dest) +" seems to shimmer for a moment and "+
                "then disappear from sight.\n");
	  }
	  if (old_i == 0) 
        {
	      dest->add_prop(OBJ_I_INVIS, new_i);
	  } 
        else 
        {
	      dest->change_prop(OBJ_I_INVIS, new_i);
	  }

        if (duration < 10) 
            duration = 10;
	  id_dur = set_alarm(itof(duration), -1.0, "remove_object");
        invis_set_by_me = 1;
    } 
    else 
    {
        remove_object();
    }
}


void
leave_env(object from, object to)
{
    int v;

    ::leave_env(from, to);

    if (living(from) && invis_set_by_me) 
    {
        invis_set_by_me = 0;
        v = from->query_prop(OBJ_I_INVIS) - delta_i;

        from->catch_msg("The invisibility shield surrounding "+
            "you fades.\n");
        say(QCTNAME(from) +" shimmers and appears solid again.\n");
    }
    if (v == 0) 
    {
        from->remove_prop(OBJ_I_INVIS);
    } 
    else 
    {
        from->change_prop(OBJ_I_INVIS, v);
    }
}

void
set_duration(int t)
{
    duration = t;
}

int
query_time_left()
{
    if (!id_dur) return -1;
    
    return ftoi(get_alarm(id_dur)[2]);
}

void
set_my_invis(int i)
{
    my_invis = i;
}

int
query_my_invis()
{
    return my_invis;
}


/*
 * Function name: dispel_spell_effect
 * Description:   Cause this spell effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_spell_effect(object dispeler)
{
    remove_alarm(id_dur);
    id_dur = set_alarm(1.0, -1.0, "remove_object");
    return 1;
}


/*
 * Function name: query_spell_effect_object
 * Description:   Easy way to tell if this object is a spell effect
 *                object
 * Returns:       1
 */
public int
query_spell_effect_object()
{
    return 1;
} 

