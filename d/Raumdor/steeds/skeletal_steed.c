/*
 *  /d/Raumdor/steeds/skeletal_steed.c
 *
 *  An undead skeletal steed.
 *
 *  Based on a steed by Deagol, Middle Earth
 *  Nerull. 2010
 */
/* 2017-09-07 Malus: Removed saddlebag due to a number of issues. */
inherit "/d/Genesis/steed/new/steed";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/commands";

#include <adverbs.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Genesis/steed/new/steed.h"

#define TO               this_object()
#define TP               this_player()
#define POSSESSIVE(x)    ((x)->query_possessive())
#define OBJECTIVE(x)     ((x)->query_objective())



string  text;
int     Hgallop;
string  emote;

void    add_acts();
string  rider_description();
void    pet_horse(object who);
int     hgallop(string str);
int     check_attack();

void
create_steed()
{

    setuid();
    seteuid(getuid());

    set_name(({"horse", "steed"}));
    set_pname(({"horses", "steeds"}));
    add_name("_steed_");
    set_adj(({"putrid", "skeletal"}));
    set_gender(G_NEUTER);
    
    set_stats(({180, 150, 250, 40, 40, 150}));
    set_skill(SS_CLIMB, 30);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_SWIM, 40);
    set_skill(SS_AWARENESS, 40);

    set_short("putrid skeletal horse");
    set_long("This is an animated rotten corpse of a dead " +
            "horse. Putrid flesh dangles everywhere, infested with maggots " +
            "and surrounded by buzzing flies. The rotten flesh on its chest " +
            "is torn away, revealing bone. A dim white glow radiates from " +
            "the empty eye sockets of the almost bare skull.\n");
 
    set_m_in("comes galloping in");

    set_m_out("gallops");
    
    add_prop(OBJ_M_NO_ATTACK, check_attack);
    add_prop(CONT_I_WEIGHT, 230000);
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(LIVE_I_UNDEAD,100);
    
    set_alignment(-250);
    
    set_rider_object_file("/d/Raumdor/steeds/skeletal_rider_object");
    set_leader_object_file("/d/Raumdor/steeds/skeletal_leader_object");
    set_rider_shadow_file("/d/Genesis/steed/new/rider_shadow");

    set_allowed_food(({"oats", "apple", "hay", "leftover", "corpse"}));
    
    allow_mounted_combat(1);
    set_no_trans(1);
    set_max_riders(1);
    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    
    seteuid(getuid(TO));

    add_acts();
}

string
rider_description()
{
    object rider = TO->query_driver();
    
    if (!rider)
    {
        return "You find no rider.\n";
    }
    return rider->long();
}

int
check_attack()
{
    if (TP->query_npc())
    {

        return 1;
    }
    return 0;
}

/*
 * Function name: query_gallop
 * Description  : Returns whether we are galloping or not.
 * Returns      : int 1/0 - if true, we gallop, otherwise not.
 */
int
query_gallop()
{
    return Hgallop;
}

int
hgallop(string str)
{   
    if ((TO->query_driver())->query_name() != TP->query_name())
    {   
        return 0;
    }
    if (str != "on" && str != "off")
    {   
        notify_fail("hgallop on/off?\n");
        return 0;
    }
    if (str == "on")
    {
        Hgallop = 1;
        write("Your horse will gallop now.\n");
        query_driver()->steed_is_updated();
        return 1;
    }
    if (str == "off")
    {
        Hgallop = 0;
        write("Your horse will not gallop now.\n");
        query_driver()->steed_is_updated();
        
        return 1;
    }
}

/*
 * Function name: query_rider_m_in
 * Description  : Routine to modify the m_in of the rider. Since the person
 *                is mounted, we need to give him the mounted messages. The
 *                horse itself is described in the name or nonmet description
 *                of the player in the rider_shadow.c so we don't have to do
 *                that here anymore. We do take into account whether the horse
 *                is galloping or not.
 * Arguments    : object rider - the player for whom to give the message.
 * Returns      : string - the m_in text.
 */
public string
query_rider_m_in(object rider)
{
    return (Hgallop ? "charges" : "rides") + " in";
}

/*
 * Function name: query_rider_m_out
 * Description  : Routine to modify the m_out of the rider. Since the person
 *                is mounted, we need to give him the mounted messages. The
 *                horse itself is described in the name or nonmet description
 *                of the player in the rider_shadow.c so we don't have to do
 *                that here anymore. We do take into account whether the horse
 *                is galloping or not.
 * Arguments    : object rider - the player for whom to give the message.
 * Returns      : string - the m_out text.
 */
public string
query_rider_m_out(object rider)
{   

    return (Hgallop ? "charges" : "rides");

}

void
add_acts()
{
    set_act_time(5);
    add_act("emote chews a few maggots that fell into " + POSSESSIVE(TO) + " mouth.");
    add_act("emote scrapes " + POSSESSIVE(TO) + " hoof on the ground.");
    add_act("emote paces slowly in a circle, and small pieces of rotten flesh "
        +"falls on the ground.");
    add_act("emote stares with " + POSSESSIVE(TO) + " dim glowing eyes at a "
        +"fly that currently rests on " + POSSESSIVE(TO) + " hoof.");
    add_act("emote lowers " + POSSESSIVE(TO) + " head, scraping " 
        + POSSESSIVE(TO) + " teeth in the ground.");
    add_act("emote tries to look sturdy, but fails.");
    add_act("emote lets off a terrible stink, as putrid flesh continues "
        +"to decay.");
    add_act("emote looks around furiously.");
}

public void
emote_hook(string emote, object actor, string adverb, object *oblist,
    int cmd_attr = 0, int target = 0)
{
    /* Don't react if we aren't the target of the emote. */
    if (!target)
    {
        return;
    }
    if (!interactive(actor))
    {
        return;

    }

    switch(emote)
    {
    case "pet":
    case "touch":
    case "snuggle":
    case "scratch":
    case "fondle":
    case "tickle":
    case "pat":
        pet_horse(TP);
    default:
        break;
    }
}

void
pet_horse(object who)
{
    write("The " + TO->query_nonmet_name() + 
            " swiftly rears its rotten skull and tries to bite you!\n");
    say("The " + TO->query_nonmet_name() +
            " swiftly rears its rotten skull and tries to bite " + 
            QTNAME(who) + "!\n");
    return;
}

public varargs string 
short_old(object for_obj)
{
    return steed_short(for_obj);
}

public varargs string
short(object for_obj)
{

    /* If no riders return the original short desc of the horse. */
    if (!has_riders)
    {
        return steed_short(for_obj);
    }
    
    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }
        
    /* If the person knows the rider, see the name and description of the
     * horse. */
    return steed_short(for_obj) + " with " + composite_riders(for_obj) +
        " riding on " + query_objective();
}

public int
can_mount(object rider)
{
    
    if (rider->query_skill(SS_ANI_HANDL) < 20)
    {
        return STEED_STS_SKILL_TOO_LOW;
    }
    
    return STEED_STS_OK;
}
