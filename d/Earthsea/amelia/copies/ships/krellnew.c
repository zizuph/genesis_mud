/*
 * Updated by Finwe, June 1997
 * Replaced call_outs with set_alarm and added new messages for
 * when Krell comes and goes.
 */

#pragma save_binary
 
inherit "/std/monster";
inherit "/lib/trade";
 
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Roke/common/defs.h"
#include "/sys/filter_funs.h"
 
 
#define NUM     sizeof(MONEY_TYPES)
#define ENV(xx) environment(xx)
 
object  ship;
int has_introduced=0;
 
string *killers;
int *killingtimes;
 
void make_expensive(string who)
{
    int i;
 
    i = member_array(who,killers);
 
    if(!sizeof(killers))
    {
        killers = ({});
        killingtimes = ({});
    }
 
    if(i<0)
    {
        killers += ({ who });
        killingtimes += ({ 1 });
    }
    else
    {
        killingtimes[i]++;
    }
    save_object("/d/Roke/common/ships/gontsparkle/capt");
}
 
string remove_killer(string name)
{
    int i;
    if ((i = member_array(name,killers)) == -1)
        return "No killer with that name.";
 
    killers = exclude_array(killers, i, i);
    killingtimes = exclude_array(killingtimes, i, i);
    save_object("/d/Roke/common/ships/gontsparkle/capt");
    return "Removed.";
}
 
le()
{
    int i;
 
    for(i=0;i<sizeof(killers);i++)
    {
        TP->catch_msg(killers[i]+" "+killingtimes[i]+"\n");
    }
}
 
void
do_die(object killer)
{
    object dm;
 
    make_expensive(killer->query_real_name());
 
 
    tell_room(E(TO),"Just before Krell dies, he chants a few words.\n");
    if (ship)
        ship->stop_ship("The ship stops; someone killed the admiral!\n");
 
    dm = clone_object(SHIPS + "monster/dragonmaster");
    dm->move_living("X",E(killer));
    dm->not(killer->query_real_name());
 
    ::do_die(killer);
}
 



void
set_ship(object s)
{
    ship=s;
}
 
void
create_monster()
{
    int x;
    string *songs;
 
    songs =   ({"and almost falls overboard.",
                "and mutters something about bad weather.",
                ", singing an old war song.",
                "and looks you up and down warily.",
                "and sings a raucous drining tune off-key.",
                "and yells 'anchors away!'",
                "and gets ready to sail away."});
 
    x = random(sizeof(songs));
 
    set_name("krell");
    add_name("admiral");
    set_living_name("krell");
    set_race_name("human");
    add_adj("friendly");
 
    add_subloc("snok",this_object());
 
    default_config_npc(60);
    set_skill(SS_SWIM,100);
    set_skill(SS_UNARM_COMBAT,45);
    set_skill(SS_DEFENCE,34);
 
    heal_hp(10000);
    set_hp(50000);
 
    set_alignment(200);
 
    config_default_trade();
 
    seteuid(getuid(TO));
 
    trig_new("%w 'introduces' %s", "react_introduce");
 
    restore_object("/d/Roke/common/ships/gontsparkle/capt");
    has_introduced = 0;
 
    set_mm_in("sails in from the ocean.");
    set_mm_out("sails out to sea.");
    set_m_in("staggers in " + songs[x]);
    set_title("the famous admiral");
    add_notify_meet_interactive("no_grimoire");
 
}
public string
show_subloc(string subloc, object on, object for_obj)
{
 
  return "He is wearing a huge ring with a picture of a dragon.\n";
 
 
}
 
void
init_living()
{
    add_action("buy", "buy");
}
 
int
buy(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;
    int    snok,*result, m_res, price;
 
    price = 24;
 
    if (!str)
    {
        notify_fail("Buy what?\n");
        return 0;
    }
 
    if(TP->query_average_stat()<20 && !present("GontSparkle",TP))
    {
        TP->catch_msg("You're so small and tiny that I'll let " +
            "you ride for free.\n");
         clone_object(SHIPS+"gontsparkle/ticket")->move(TP);
    return 1;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
        if (sscanf(str, "%s with %s", what, for_c) != 2)
            what = str;
    if (what != "ticket")
    {
        notify_fail("I have no such thing for sale.\n");
    return 0;
    }
 
// tell_room(environment(TO),
//  QCTNAME(TO)+" says: You don't need a ticket for the " +
//      "Gont-Sparkle boat.\n");
 
    buy_ob=clone_object(SHIPS+"gontsparkle/ticket");
    if (!buy_ob)
    {
        notify_fail("I seem to be out of tickets.\n");
    return 0;
    }
 
    snok = member_array(TP->query_real_name(),killers);
 
    price=buy_ob->query_prop(OBJ_I_VALUE);

    if(!(snok<0))
    {
        TP->catch_msg("Hey! You have killed my brother! " +
            "It costs more for you!\n");
        price = price * (1+killingtimes[snok]);
    }

 
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1)
    {
        buy_ob->remove_object();
        return 0;
    }
 
    if (buy_ob->move(this_player()))
    {
        write("You drop the " + buy_ob->short() + " on the ground.\n");
        say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
            " on the ground.\n");
        buy_ob->move(environment(this_player()));
    }
    else
    {
        write("You get your " + buy_ob->short() + ".\n");
        say(QCTNAME(this_player()) + " buys a " + buy_ob->short() + ".\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
        write("You get " + change + " as change.\n");
 
    return 1;
}
 
void
react_introduce(string person,string who)
{
    if (!has_introduced)
    {   set_alarm(4.0,0.0,"introduce_me");
//        call_out("introduce_me", 4);
        has_introduced=1;
        set_alarm(15,0,0,0,"remove_int");
//        call_out("remove_int",15);
    }
}
 
void
introduce_me()
{
    command("introduce myself");
}
 
void
remove_int()
{
    has_introduced=0;
}
 
/*  This routine steals the grimoire from the castle so that it cant
    get out of the domain...
    Some code changed by Ged (Orig code by Mercade) to
    check for grimoires in sacks and chests and so on...
 */
 
void
no_grimoire()
{
    object *players;
    object *obs;
    int i;
    int j;
    int set_alarm_time;
 
    set_alarm_time = 4;
    players = FILTER_LIVE(all_inventory(ENV(TO)));
 
    for (i = 1; i < sizeof(players); i++)
    {
        obs = deep_inventory(players[i]);
 
        for (j = 1; j < sizeof(obs); j++)
        {
            if (obs[j]->id("refnasgrim"))
            {
                obs[j]->remove_object();
 
set_alarm(set_alarm_time,0.0,"grimoire_found(players[i])");
//                call_out("grimoire_found", call_out_time, players[i]);
//                call_out_time += 2;
            }
        }
    }
 
    return;
}
 
void
grimoire_found(mixed ob)
{
    command("shout I don't want such dangerous things on my ship!");
    command("shout Give me that.");
    ob->catch_msg(" takes your grimoire.\n");
    tell_room(ENV(TO), "The captain takes something from " + QTNAME(ob) +
        ".\n", ob);
 
    return;
}
