/*
 * This dragon is used in dragonfear special.
 * Louie 2005 Added new special attacks.
 *
 *
 * Modified Louie July 9 2005 - Added bonus to battleraging Neidars
 *        to resist dragon Awe.
 * Louie March 2006 - Don't damage enemies who aren't in the room.
 * Louie Nov 2006 - Expand my previous fix that didn't fix all cases.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Krynn/std/dragon_base";

#include "../guild.h"

#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*proto*/
public void attempt_action();
public void dragons_do_not_fight();

private object summoner;
private string* elec_hits = ({"unhurt","slightly shocked","somewhat burned",
                             "shocked","charred","electrocuted"});
private string* fire_hits = ({"unhurt","slightly heated","somewhat burned", 
                             "burned","roasted","severely blasted"});
private string* how_hits;
private int     follow_alarm;

void
set_summoner(object ob)
{
    summoner = ob;
    set_colour(ob->query_dragonarmy_division());
}

object
query_summoner()
{
    return summoner;
}

void
remove_object()
{
    // If the dragon is in the middle of an attack, we don't want it to
    // disappear just yet. Simply add a property so that upon completion of
    // the ability, the dragon will be removed.
    if (DRAGON_BREATH_SPECIAL->query_ability_preparing(summoner)
        || DRAGON_SWOOP_SPECIAL->query_ability_preparing(summoner))
    {
        summoner->add_prop(PENDING_DRAGON_SPECIAL, 1);
        set_alarm(5.0, 0.0, remove_object); // try again in 5 seconds.
        return;
    }
    
    tell_room(E(TO), "The "+ ::short_desc()+" soars up into the sky and disappears.\n");
    move_living("M", TEMP_DRAGON_ROOM, 1, 1);
    DRAGONS_MANAGER->remove_strike_dragon(query_summoner());
    ::remove_object();
}

void
set_dragonfear_time(int t)
{
    set_alarm(itof(t), 0.0, remove_object);
}


void
follow_summoner()
{
    remove_alarm(follow_alarm);
    follow_alarm = set_alarm(itof(5+random(5)), 0.0, follow_summoner);
    if (objectp(summoner) && E(TO) != E(summoner) 
        && !E(summoner)->query_prop(ROOM_I_INSIDE))
    {
        tell_room(E(TO), "The "+ ::short_desc()+" flies away following "+
            QTNAME(summoner)+".\n");
        tell_room(E(summoner), C(LANG_ADDART(::short_desc()))+
            " swoops out of the clouds above with a shriek, circling over "+
            "the battlefield with cruel interest.\n");
        move_living("M", E(summoner), 1, 1);
    }
}

void
create_dragon_npc()
{
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);

    setup_dragon();
    add_prop(OBJ_M_NO_ATTACK, "Attack flying dragon? How???\n");
    set_adj("flying");

    // Begin the actions soon after creation.
    set_alarm(itof(10+random(30)), 0.0, &attempt_action());
    
    /*There are apparently some NPCs that start fights */
    /*with dragons - this makes sure the dragons don't fight */
    /*...in theory */
    set_alarm(5.0, 5.0, &dragons_do_not_fight());
    
    setuid();
    seteuid(getuid());    

}

string
long_desc()
{
    return "Flying above you is one of the children of " +
      "Takhisis, "+LANG_ADDART(::short_desc()) +". This " +
      "massive reptile is covered with thick scales from its " +
      "sinuous tail to its sinister head, a formidable defense " +
      "overshadowed only by its awesome destructive capability. "+
      C(HE(TO))+" circles over the battlefield with cruel interest.\n";
}

string
short_desc()
{
    return "flying " + ::short_desc();
}

public int
query_dragonarmy_dragon()
{
    return 1;
}

public object
clone_dragon_fear_object()
{
    object dfear_object;

    dfear_object = clone_object(DRAGONARMY_DRAGON + "dragon_fear_obj_new");
    
    return dfear_object;
}

public int
query_age_mod()
{
    int age_mod = 100;

    switch (query_age()) {
        case "young":
            age_mod = 100;
            break;
        case "adult":
            age_mod = 90;
            break;
        case "aged":
            age_mod = 80;
            break;
        default:
            age_mod = 100;
            break;
    }

    return age_mod;

}

public void
attempt_action()
{
    /*Wait til we're in the same room*/
    if (objectp(summoner) && (E(TO) != E(summoner)))
    {
        set_alarm(1.0, 0.0, &attempt_action());
        return;
    }

    // Repeat the alarm later.
    set_alarm(itof(10+random(30)), 0.0, &attempt_action());

    // Check if the dragon is already performing an attack action
    if (DRAGON_BREATH_SPECIAL->query_ability_active(summoner)
        || DRAGON_SWOOP_SPECIAL->query_ability_active(summoner))
    {
        return;
    }
    
    // 25% chance of an action.
    if (!random(4)) {
        switch(random(6)) 
        {
            case 0: 
                tell_room(E(TO),QCTNAME(TO)+" glides lazily "+
                        "through the air.\n", TO);
                break;
            case 1: 
                tell_room(E(TO),QCTNAME(TO)+" bends "+HIS(TO)+
                        " neck to watch the combat below.\n",TO);
                break;
            case 2: 
                tell_room(E(TO),QCTNAME(TO)+" menacingly circles "+
                        "the area.\n",TO);
                break;
            case 3: 
                tell_room(E(TO),QCTNAME(TO)+" briefly drifts down "+
                        "for a closer view.\n",TO);
                break;
            case 4: 
                tell_room(E(TO), QCTNAME(TO)+" lets out a "+
                        "piercing shriek.\n",TO);
                break;
            case 5:
            default: 
                tell_room(E(TO), QCTNAME(TO)+" stretches "+
                         HIS(TO)+" wings in boredom.\n",TO);
                break;
        }
        return;
    }
}

/*This keeps the dragon from fighting*/
public void
dragons_do_not_fight() {
    object* en = TO->query_enemy(-1);

    for (int i = 0; i<sizeof(en);i++) {
        TO->stop_fight(en[i]);
        en[i]->stop_fight(TO);
    }
}

public void
refresh_livings_in_room(object room)
{
    object * people;
    
    if (!IS_CLONE)
    {
        return;
    }
    
    if (objectp(room))
    {
        people = FILTER_LIVE(all_inventory(room)) 
                 - ({ this_object() });
        if (sizeof(people))
        {
            send_debug_message("strike_dragon", "Refreshing dragonfear.");
            people->refresh_dragon_fear();
        }
    }
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{   
    object old_room;
    
    setuid();
    seteuid(getuid());

    old_room = environment(this_object());    
    ::move_living(how, to_dest, dont_follow, no_glance);
    refresh_livings_in_room(old_room);
    refresh_livings_in_room(environment(this_object()));
}
