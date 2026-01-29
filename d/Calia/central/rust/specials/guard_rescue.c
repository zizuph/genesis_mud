
#include <defs.h>
#include <stdproperties.h>
#include <macros.h>

public void set_priority(int priority, object rescued);
public void guard_resc(object *rescued, object *rescuer);
public void guard_keep_checking(object *rescuer, 
    object rescuer_home);
public void guard_go_back(object *rescuer, object rescuer_home);
public void add_guard(object ob);
public void remove_guard(object ob);
public object get_guard();

public object *el_resc = ({}), *rescuer = ({0});
public object *other_resc = ({});
public object loc, rescuer_home, rescued;

void
set_priority(int priority, object rescued)
{
    int time;
    time = 5 + random(5);
    loc = environment(rescued);

    if (!present(rescuer[0], loc))
    {
        rescuer = ({0});

        if (sizeof(el_resc))
        {
            rescuer[0] = get_guard();
            rescuer += rescuer[0]->query_team_others();
        }
        else
        {
            find_living("bishop")->catch_msg("Noone to rescue.\n");
            return;
        }
    }
    else
    {
        return;
    }

    find_living("bishop")->catch_msg("Step one.\n");

    el_resc -= ({rescuer[0]});

    if (priority == 0 && random(5) == 0)
    {
        set_alarm(itof(time), 0.0, &guard_resc(rescued, rescuer));
    }
    else
    if (priority == 1)
    {
        find_living("bishop")->catch_msg("Step two.\n");
        set_alarm(itof(time), 0.0, &guard_resc(rescued, rescuer));
    }
    else
    {
        add_guard(rescuer[0]);
    }
}

void
guard_resc(object rescued, object *rescuer)
{
    int i, n;
    n = sizeof(rescuer);
    loc = environment(rescued);

    rescuer_home = environment(rescuer[0]);

    if (!objectp(rescuer[0]->query_attack()))
    {
        for (i=0 ; i < n ; i++)
        {
            rescuer[i]->move_living("in response to a disturbance" +
                " in the village", loc, 0);
        }
    } 

    set_alarm(2.0, 0.0, 
        &guard_keep_checking(rescuer, rescuer_home));
    
}

void
guard_keep_checking(object *rescuer, object rescuer_home)
{
    int i, n, k;


    for (i=0 ; i < sizeof(rescuer) ; i++)
    {
        if (!living(rescuer[i]))
        {
            rescuer -= ({rescuer[i]});
        }
    }

    n = sizeof(rescuer);

    if (n == 0)
    {
        return;
    }	

    other_resc = filter(all_inventory(environment(rescuer[0])), 
        &->query_npc());
    k = sizeof(other_resc);

    for (i=0 ; i < k ; i++)
    {
        if (other_resc[i]->query_race() == "gnome" &&
            objectp(other_resc[i]->query_attack()))					
        { 
            rescued = other_resc[i];
        }
    } 

    if (!objectp(rescuer[0]->query_attack()))
    {
        if (rescued == 0)
        {
            set_alarm(8.0, 0.0, 
                &guard_go_back(rescuer, rescuer_home));
        }
        else
        if (!objectp(rescued->query_attack()))
        {
            set_alarm(8.0, 0.0, 
                &guard_go_back(rescuer, rescuer_home));
        }
        else
        {
            rescuer[0]->command("say Stop that, you cretin!");

            for (i=0 ; i < n ; i++)
            {
                rescuer[i]->command("assist " + OB_NAME(rescued));
            }
            set_alarm(4.0, 0.0, 
                &guard_keep_checking(rescuer, rescuer_home));
        }
    }
    else
    {
        set_alarm(10.0, 0.0, 
            &guard_keep_checking(rescuer, rescuer_home));
    }
}

void
guard_go_back(object *rescuer, object rescuer_home)
{
    int i, n, k;
    n = sizeof(rescuer);

    for (i=0 ; i < n ; i++)
    {
        if (!living(rescuer[i]))
        {
            rescuer -= ({rescuer[i]});
        }
    }

    n = sizeof(rescuer);

    if (n == 0)
    {
        return;
    }

    other_resc = filter(all_inventory(environment(rescuer[0])),       
        &->query_npc());
    k = sizeof(other_resc);

    for (i=0 ; i < k ; i++)
    {
        if (other_resc[i]->query_race() == "gnome")
        { 
            rescued = other_resc[i];
        }
    } 

    if (objectp(rescued->query_attack()))
    {
        guard_keep_checking(rescuer, rescuer_home);
    }
    else
    if (!objectp(rescuer[0]->query_attack()))
    {
        for (i=0 ; i < n ; i++)
        {
            rescuer[i]->move_living("back to his post", rescuer_home,
                0);
        }
        el_resc += ({rescuer[0]});
    }
    else
    {
        set_alarm(10.0, 0.0, 
            &guard_keep_checking(rescuer, rescuer_home));
    }
}

void
add_guard(object ob)
{
    find_living("bishop")->catch_msg("Guard added.\n");
    el_resc += ({ob});
    el_resc -= ob->query_team_others();
}

void
remove_guard(object ob)
{
    if (sizeof(el_resc))
    {
        return;
    }

    el_resc -= ({ob});
}

object
get_guard()
{
    int n = sizeof(el_resc);
    find_living("bishop")->catch_msg("Guard gotten.\n");

    if (n == 0)
    {
        return 0;
    }
    else
    {
        return el_resc[n-1];
    }
}