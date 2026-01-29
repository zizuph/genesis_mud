#pragma save_binary

inherit "/std/shadow";

#include <macros.h>
#include <filter_funs.h>
#include "../guild.h"

#define   MAX_HEAR            5
#define   LASTING_TIME        5000
#define   I_NO_TELL_RUMOUR    "_i_no_tell_rumour"

static mixed  *heard = ({ });
static string *rumour = ({ });
static string *from = ({ });
static int    *tt = ({ });
static int    alarm;

/*
 * Prototypes
 */
void tell_rumour();
void tell_all_rumours(int i);


object query_rumour_shadow() { return TO; }
mixed  query_rumour()        { return ({ rumour, from, tt }); }
mixed  query_heard()         { return heard; }
int    query_no_of_rumours() { return sizeof(rumour); }

void
plant_rumour(string a, string b, int c)
{
    int i;

    if ((i = member_array(a, rumour)) != -1)
    {
        if (c>tt[i]) tt[i] = c;
        return;
    } 
    rumour += ({ a });  from += ({ b }); tt += ({ c }); heard += ({ ({ }) });
}

void
init_living()
{
    if (!alarm && !random(5) && sizeof(rumour))
        alarm = set_alarm(itof(2+random(6)), 0.0, &tell_rumour() );
    shadow_who->init_living();
}

string
answer_rumours()
{
    remove_alarm(alarm);
    alarm = 0;
    set_alarm(0.0, 0.0, &tell_all_rumours(0) );
    shadow_who->answer_rumours();
    return "";
}

void
tell_all_rumours(int i)
{
    if (i < sizeof(rumour))
    {
        if (!i)
            shadow_who->command("say I have heard that "+from[i]+" said: "+
                                rumour[i]+"...");
        else
            shadow_who->command("say then "+from[i]+" said: "+
                                rumour[i]+"...");
        set_alarm(2.0, 0.0, &tell_all_rumours(i+1) );
        return;
    }
    if (!i) shadow_who->command("say Sorry, I don't know any rumours.");
    else    shadow_who->command("say Interesting, isn't it?");
}

void
remove_rumour(int r)
{
    mixed *tmp;
    int i, s;

    tmp = ({ });
    for (i = 0, s = sizeof(heard); i < s; i++)
        if (i != r) tmp += ({ heard[i] });
    heard = tmp;
    tmp = ({ });
    for (i=0, s=sizeof(rumour); i<s; i++)
        if (i != r) tmp += ({ rumour[i] });
    rumour = tmp;
    tmp = ({ });
    for (i=0, s=sizeof(from); i<s; i++)
        if (i != r) tmp += ({ from[i] });
    from = tmp;
    tmp = ({ });
    for (i=0, s=sizeof(tt); i<s; i++)
        if (i != r) tmp += ({ tt[i] });
    tt = tmp;
}

int
shadow_me(mixed to_shadow)
{
    if (!::shadow_me(to_shadow)) return 0;

    if (shadow_who->query_npc() && 
        !shadow_who->query_prop(I_NO_TELL_RUMOUR))
    {
        shadow_who->set_dont_answer_unseen(1);
        shadow_who->add_ask(({"rumours","about rumours","about the rumours"}), 
                            "@@answer_rumours:"+file_name(TO)+"@@");
    }
    return 1;
}

void
set_up_rumour(object ob, string a, string b, int t)
{
    int k;

    if (ob->query_wiz_level()) return;

    if (!ob->query_rumour_shadow())
    {
        FIXEUID;
        clone_object(MASTER)->shadow_me(ob);
    }
    if ((k = ob->query_no_of_rumours()) > (2+random(4)))
        ob->remove_rumour(random(k));
    ob->plant_rumour(a, b, t);
}

void
tell_rumour()
{
    int i, j, k;
    object *list;

    alarm = 0;
    i = random(sizeof(from));

    if ((tt[i] + LASTING_TIME) < time())
    {
        remove_rumour(i);
        return;
    }

    if (!shadow_who)
    {
        return;
    }
    
    list = FILTER_LIVE(all_inventory(ENV(shadow_who))) - (object 
    *)heard[i];
    list -= ({ shadow_who });
    if (sizeof(list))
    {
        j = random(sizeof(list));
        if (shadow_who->query_npc() && 
            !list[j]->query_prop(I_NO_TELL_RUMOUR) &&
            list[j]->query_humanoid())
        {
            shadow_who->command("say Hello! Do you know what I have heard?");
            shadow_who->command("say "+from[i]+" told me that: "+
            rumour[i]+".");
            shadow_who->command("say Do you believe it?");
            heard[i] += list;
            set_up_rumour(list[j], rumour[i], from[i], tt[i]);
            if (sizeof(heard[i]) > MAX_HEAR) remove_rumour(i);
        }
    }
}
