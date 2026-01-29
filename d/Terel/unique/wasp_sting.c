/* A stinging wound from Wasp the Cleaver
 *   /d/Terel/unique/wasp_the_cleaver.c
 *
 * A non-additive LIVE_I_ATTACK_DELAY prop is added 
 * to those who don't have one already.
 *
 * This effect can be avoided via the ring of the ancients:
 *   /d/Terel/common/moor/obj/safe_ring.c
 *
 * Created by Lilith, Jan 2022.
 *
 * Revisions:
 *     Lilith, Feb 2022: 
 *       Bumped up cool-down time to 30s-7s (23s)
 *       added more checks for stunned props to prevent stacking.
 *       added logging for the stings and the attack_delays
 */ 
#pragma strict_types
#pragma no_inherit

inherit "/std/object";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>

// This prop is added to the player by the ring of the ancients.
// It provides protection against this special effect.
#define RUNES_REVEALED  "_terel_ring_runes_revealed"
#define RECOVER_PROP    "_recover_from_sting"
#define RECOVER_TIME    30
#define STING_DELAY     7
#define WOUND           "wasp_stings"
#define WASP_LOG        "/d/Terel/unique/log/wasp_log"

string *hits = ({ });
int     heal_alarm = 0, sting_alarm = 0;
object  player;

void create_object()
{
    set_name("saw wound");
    add_name(({ WOUND, "wound", "saw wounds", "gash"}));

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, "Drop what?\n");
    
    set_no_show_composite(1);

    set_long("It is a gash sawn into your "+ VBFC_ME("query_hits") + 
         ", caused by Benton's Wasp. It stings like hell.\n");
	// For logging
	seteuid(getuid());	 
}

void avenir_weapon_damage() { /* empty function. Don't remove */ }

string query_hits()
{
    if(sizeof(hits) > 5)
        return COMPOSITE_WORDS(hits[0..4]);
    else
        return COMPOSITE_WORDS(hits);
}

public string
show_subloc(mixed subloc, object on, object for_obj)
{
    string str;

    if(!living(environment(this_object())))
    {
        set_alarm(0.0, 0.0, remove_object);
        return "";
    }

    if(for_obj != on)
        str = "There " + (sizeof(hits) > 1 ? "are ragged gashes" : 
            "is a ragged gash") + " on " + on->query_possessive() + 
            " " + query_hits() + ".\n";
    else
        str = "There " + (sizeof(hits) > 1 ? "are ragged gashes" : 
            "is a ragged gash") + " on your " + 
            query_hits() + ". "+ (sizeof(hits) > 1 ? "They feel" : 
            "It feels") + " like you've been stung by dozens of wasps.\n";

  return str;
}

/* Remind players they've got a wound from the weapon 
 * and that it fkn hurts :)
 */
void sting()
{
    // Player is protected by the ring of the ancients.
    // If they put it on after the wound is cloned, this
	// should remove it.
    if(player->query_prop(RUNES_REVEALED, 1))
    {
        remove_alarm(sting_alarm);
        player->remove_subloc(WOUND);		
        set_alarm(1.0, 0.0, remove_object);
        return;
    }
		
    if(!sizeof(hits))
    {
        remove_alarm(sting_alarm);
        set_alarm(1.0, 0.0, remove_object);
        return;
    }
	
	if (sizeof(hits) > 1)
	    player->catch_msg("Holy hell! Those gashes sawed into your "+ 	
            query_hits() +" hurt like you've been stung by "+
            "dozens of wasps!\n");			
    else
        player->catch_msg("Yikes! That saw mark on your "+ 
            query_hits() +" stings like hell!\n");
			
    sting_alarm = set_alarm((itof(20 + random(60))), 0.0, sting); 
}

void heal()
{

    if(!sizeof(hits))
    {
		remove_alarm(heal_alarm);
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    hits -= ({ hits[0] });

    if(!sizeof(hits))
    {
        remove_alarm(heal_alarm);
        set_alarm(1.0, 0.0, remove_object);
        return;
    }
}

/*
 *  Adds another gash mark and adds the attack_delay.
 */
void add_hurt(string where, object me)
{
	int delay, prop;

    // Add the gash to the array of other gashes.
    if(member_array(where, hits) == -1)
	{
        hits += ({ where });
        write_file(WASP_LOG, ctime(time()) +" "+me->query_name()
          +" was stung by Wasp.\n");	
    }
    // Should take away a gash every 30 secs or so
    if(!heal_alarm || !sizeof(get_alarm(heal_alarm)))
        heal_alarm = set_alarm(40.0, 30.0, heal);

    // I don't want to continously stun an enemy
    // so enforce a minimum cooldown period.
    prop = me->query_prop(RECOVER_PROP);
	if (prop && prop > time())
        return;
    // Is the enemy already delayed, then don't add.
	if (me->query_prop(LIVE_I_ATTACK_DELAY))
        return;
	// Is the enemy stunned? Don't add.
    if (me->query_prop(LIVE_I_STUNNED))
        return;
    // Is the enemy recovering from someone else's stun? Don't add.
    if (me->query_prop("_live_i_stun_begin") + 30 > time())
        return;

   // This isn't really a stun, its just...missing out
   // on a white hit or two while rubbing an ouchie.
    me->add_prop(LIVE_I_ATTACK_DELAY, STING_DELAY);
    me->catch_msg("\nYou take a short break to try to tend "+
        "to your wound.\n\n");
    // Set the recovery period.
    me->add_prop(RECOVER_PROP, (time() + RECOVER_TIME));
    write_file(WASP_LOG, ctime(time()) +" "+ me->query_name() 
        +" got a "+ STING_DELAY +" attack_delay.\n");	
}

void enter_env(object to, object from)
{
    ::enter_env(to, from);

  
    if(!living(to))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    to->add_subloc(WOUND, this_object());
		
	if(!sting_alarm  || !sizeof(get_alarm(sting_alarm)))
        sting_alarm = set_alarm(2.0, 0.0, sting);		
}

void leave_env(object to, object from)
{
   ::leave_env(to, from);

   from->remove_subloc(WOUND);
}
