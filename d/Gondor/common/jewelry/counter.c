/*
 * /d/Gondor/common/jewelry/counter.c
 *
 * A counter to put gems on in the jewelry shop.
 *
 * Coded by Gwyneth, 08/27/02
 */
inherit "/std/container";

#include <macros.h>
#include "jewelry.h"

/* gGems = ([ "gwyneth" : ({ "ruby", 20, "diamond", 15 }) ]) */
mapping gGems = ([]);

public int check_retrieve();

void
create_container()
{
    set_name("counter");
    add_name("tray");
    add_name("display");
    set_adj("glass");
    set_short("glass counter");
    set_long("The glass counter has a special tray for placing gems on. " +
        "Under the glass, you can see numerous pieces of jewelry. " +
        "Prominently displayed on velvet cushions, you see crowns, coronets, " +
        "circlets, equestrian rings and collars of office. Next to them " +
        "rest the regalia of the orders of chivalry -- collars of the Knight " +
        "Grand Cross and Knight Commander as well as gold medals of " +
        "membership. Elsewhere in the display, you can see rings, medals, " +
        "bracelets, anklets, necklaces, torcs, pendants and chokers. Perhaps " +
        "you could get a closer look at each of the items.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 20000);
    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_CLOSED, 0);
    add_prop(OBJ_M_NO_GET, "It's bolted down!\n");
    add_prop(CONT_M_NO_REM, &check_retrieve());
}

public string
check_retrieve()
{
    if (query_verb() == "retrieve")
        return 0;

    return "You can 'retrieve' your gems.\n";
}

public int
retrieve_gems(string str)
{
    int i, j, size;
    string name = this_player()->query_real_name(); 
    mixed *gems;
    object *gem_objs;

    if (!strlen(str) || str != "gems")
    {
        notify_fail("Retrieve gems?\n");
        return 0;
    }

    if (member_array(name, m_indexes(gGems)) == -1)
    {
        write("You have no gems on the counter to retrieve.\n");
        return 1;
    }

    gems = gGems[name];

    if (!sizeof(gems))
    {
        write("You have no gems or money on the counter to retrieve.\n");
        gGems = m_delete(gGems, name);
        return 1;
    }

    for (i = sizeof(gems) - 2; i >= 0; i -= 2)
    {
        gem_objs = all_inventory(this_object());
    
        for (j = sizeof(gem_objs) - 1; j >= 0; j--)
        {
            if (gem_objs[j]->query_name() == gems[i])
            {
                gem_objs[j]->split_heap(gems[i+1]);
                gem_objs[j]->move(this_player());
            }
        }
    }

    write("You retrieve the gems you placed on the counter.\n");
    say(QCTNAME(this_player()) + " retrieves the gems " +
        this_player()->query_pronoun() + " placed on the counter.\n");
    gGems = m_delete(gGems, name);
    return 1;
}

void
add_gems(string name, string gem, int num)
{
    int i;

    if (member_array(name, m_indexes(gGems)) == -1)
        gGems += ([ name : ({ gem, num }) ]);
    else
    {
        i = member_array(gem, gGems[name]);
        if (i == -1)
            gGems[name] += ({ gem, num });
        else
            gGems[name][i+1]++;
    }

    return;
}

void
remove_gems(string name, string gem, int num)
{
    int index, end;
    object gem_obj;

    if (!sizeof(gGems[name]))
        return;

    index = member_array(gem, gGems[name]);
    if (index == -1)
        return;

    if (gGems[name][index+1] > num)
    {
        gGems[name][index+1] -= num;
    }
    else if (sizeof(gGems[name]) == 2)
    {
        gGems = m_delete(gGems, name);
    }
    else
    {
        end = sizeof(gGems[name]) - 1;
        if (index != 0 && index+1 != end)
            gGems[name] = gGems[name][0..index-1] + gGems[name][index+2..end];
        else if (!index)
            gGems[name] = gGems[name][2..end];
        else
            gGems[name] = gGems[name][0..end-2];
    }

    gem_obj = present(gem, this_object());
    gem_obj->set_heap_size(gem_obj->num_heap() - num);
    return;
}

/* Function name: receive_offer
 * Description  : See if anything is needed. If nothing is needed, let 
 *                them know. If gems are needed, check if they have 
 *                *all* of the required items. If they do, delete the 
 *                mapping and reduce the items on the table by the 
 *                appropriate number. Let the room know to begin the crafting.
 * Arguments    : string name - who to check for
 */
public void
receive_offer(string name)
{
    int i, matched = 1, index, size;
    mixed *gems_here, *gems_need;
    object room = environment();

    gems_need = room->query_gems_need(name);

    if (!sizeof(gems_need))
    {
        set_alarm(1.0, 0.0,
            &room->keeper_say("You haven't ordered anything or you don't " +
                "owe me anything.", find_player(name)));
        return;
    }

    if (member_array(name, m_indexes(gGems)) == -1)
    {
        set_alarm(1.0, 0.0,
            &room->keeper_say("You don't have anything on the counter.",
            find_player(name)));
        return;
    }

    gems_here = gGems[name];

    for (i = 0, size = sizeof(gems_here); i < size; i += 2)
    {
        index = member_array(gems_here[i], gems_need);
        if (index == -1)
            matched = 0;
        else if (gems_here[i+1] != gems_need[index+1])
            matched = 0;
    }

    if (!matched)
    {
        set_alarm(1.0, 0.0, 
            &room->keeper_say("You haven't put the right number of gems " +
            "on the counter. Please put the exact number of gems on the " +
            "counter, no more, no less.", find_player(name)));
        return;
    }

    for (i = 0, size = sizeof(gems_need); i < size; i += 2)
        remove_gems(name, gems_need[i], gems_need[i+1]);

    /* We don't need anymore gems. */
    set_alarm(CONSTRUCT_TIME, 0.0, &room->pickup_msg(name));
    /* Don't want to use this_player() in an alarm, so
       we'll use find_player(name) instead. */
    set_alarm(1.0, 0.0, &room->keeper_say("Thank you! I will " +
        "begin my work right away.", find_player(name)));
    return;
}

public int
offer_gems(string str)
{
    string name = this_player()->query_real_name();

    if (member_array(name, m_indexes(gGems)) == -1)
    {
        write("You have no gems on the counter.\n");
        return 1;
    }

    receive_offer(name);
    write("You offer the gems you placed on the counter.\n");
    return 1;
}

void
enter_inv(object ob, object from)
{
    string name;

    ::enter_inv(ob, from);

    if (ob->query_gem())
    {
        add_gems(from->query_real_name(), ob->query_name(), ob->num_heap());
        return;
    }
    else if (!ob->num_heap())
        set_alarm(0.5,0.0,&tell_room(environment(),
            capitalize(LANG_ADDART(ob->short())) +
            " slips off the counter onto the ground.\n"));
    else
        set_alarm(0.5, 0.0, &tell_room(environment(), capitalize(ob->short()) +
            " slips off the counter onto the ground.\n"));

    ob->move(environment(), 1);
    return;
}

void
init()
{
    ::init();

    add_action(retrieve_gems, "retrieve");
    add_action(offer_gems, "offer");
}
