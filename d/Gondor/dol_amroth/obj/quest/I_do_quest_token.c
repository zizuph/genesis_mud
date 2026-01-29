/* -*- Mode: C -*-
 *
 * I_do_quest_token.c
 *
 * Skippern 20(c)02
 *
 * The Dol Amroth Quest object. this should be invisible, but carry the 
 *   datas that the various parts of the quest needs to control if it 
 *   has been done in the right order.
 */
#pragma save_binary

inherit "/std/object";
inherit "/d/Gondor/common/lib/binbit";

#include "../../defs.h"
#include <stdproperties.h>

/* Global variables */
static int             Task;
static int             Part;
static string          Ingr;
static string          VisitedHere = "";

/* Prototypes */
public void            give_reward(object player, int reward);

/* The code */
void set_task(int i)    { Task = i; }
void set_part(int i)    { Part = i; }
void set_ingr(string a) { Ingr = a; }
void set_visit(string a) { VisitedHere = a; }

void
create_object()
{
    set_name("dust");
    add_name("I_do_quest_token.c");
    set_short("grain of dust");
    set_long("This is a grain of dust, you shouldn't be able to see it.\n");
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
}

int query_task() { return Task; }
int query_part() { return Part; }
string query_ingr() { return Ingr; }
string query_visit() { return VisitedHere; }

public void
give_reward(object player, int reward)
{
    string TName;

    if (reward < LITE)
        tell_object(player, "You feel a little more experienced.\n");
    else if (reward < SOME)
        tell_object(player, "You feel somewhat more experienced.\n");
    else if (reward > MUCH)
        tell_object(player, "You feel much more experienced.\n");
    else
        tell_object(player, "You feel more experienced.\n");

    player->add_exp_quest(reward);
    //    set_bin_bits(DOL_Q_GROUP, DOL_FIRST_BIT, DOL_NO_BITS, player, Task);

    switch(Task)
    {
    case DOL_Q_M_EXPLORE_TOWN..DOL_Q_M_LAST:
	TName = "DOL AMROTH TOUR "+Task;
	break;
    case DOL_Q_TORMIR_CAHRM:
	TName = "TORMIR'S CHARM";
	break;
    case DOL_Q_MAGE_QUEST:
	TName = "MAGICAL COMPONENST";
	break;
    case DOL_Q_ASSASSIN:
	TName = "ASSASINATE NOBEL";
	break;
    case DOL_Q_JEWELER:
	TName = "JEWELER'S ACCOUNT";
	break;
    case DOL_Q_WINE:
	TName = "WINE TASTER";
	break;
    case DOL_Q_ALCHEMIST:
	TName = "ALCHEMIST'S LABLES";
	break;
    default:
	TName = "What Happened?";
	break;
    }
    log_file("quest", ctime(time()) + " "+TName+"\t"+player->query_name()+
	     "\t("+player->query_average()+") "+reward+"\n");

    return;
}


