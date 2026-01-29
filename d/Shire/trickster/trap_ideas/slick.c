inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include <tasks.h>

/*  Prototypes */
void slipaway(string where, object player);
void player_slipped(object player);
void slip_on_rear(object player);
void go_byebye();

int    alarm_id;
string Trap_setter;
int Trap_qual;
int ready = 0;

void
create_object()
{
    set_short("slippery oil slick");
    set_long("It looks like someone has spilled a flask of oil here, "+
      "making the ground all slippery...   Looks like it could cause "+
      "someone to slip and fall on their behinds if they did not notice "+
      "it here.\n");
    set_name("slick");
    set_adj(({"slippery","oil"}));
    add_name("oil");
    add_name("trickster_oil_slick");

    add_prop(OBJ_M_NO_GET, "The puddle is too slippery to be taken.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
    alarm_id = set_alarm(itof(600+random(180)),0.0,go_byebye);

}

void
init()
{
    ::init();
    add_action("do_flames","burn");
    add_action("do_flames","light");
    add_action("do_cover","cover");
    //   To make sure when it's cloned it doesn't move someone.
    if (!ready)
    {
	ready = 1;
	return;
    }
    if (TP->query_real_name() == Trap_setter)
    {
	write("You grin mischievously as you avoid your slippery oil slick.\n");
	return;
    }
    if (TP->resolve_task(Trap_qual, ({SS_AWARENESS,TS_DEX})) > 0)
    {
	write("You managed to avoid the "+short()+" completely, preventing "+
	  "the embarassment of sliping on your behind.\n");
	return;
    }
    set_alarm(0.1,0.0,&player_slipped(this_player()));
}

void
slipaway(string where, object player)
{
    //  If someeone runs out of the room before this function is
    //  called we probably shouldn't move them now should we ;)
    if (!present(player,ENV(TO)))
	return;
    player->catch_msg("You mange to slip on the "+short()+", which "+
      "sends you sprawling "+where+"!\n");
    say(QCTNAME(player)+" slips on the "+short()+" causing "+
      HIM_HER(player)+" to slip and slide "+where+"!\n");
    player->command("$" + where);
}

void
slip_on_rear(object player)
{
    player->catch_msg("You slipped on the oilslick and fall on your behind!\n"+
      "Everyone laughs uproarously at you!\n");
    say(QCTNAME(player)+" slips on the "+short()+" and falls on "+HIS_HER(player)+
      " behind!!\nYou laugh uproariously at "+QTNAME(player)+".\n");
}

void
player_slipped(object player)
{
    string lastmove;
    int *dirs;

    lastmove = player->query_prop(LIVE_S_LAST_MOVE);
    dirs = ENV(player)->query_exit_cmds();
    if (member_array(lastmove, dirs) >= 0 && lastmove != "up" && lastmove != "out")
    {
	slipaway(lastmove,player);
	return;
    }
    else
    {
	switch (lastmove)
	{
	case "up":
	    if (member_array("down", dirs) >= 0)
		slipaway("down",player);
	    else
		slip_on_rear(player);
	    break;
	case "out":
	    if (member_array("in", dirs) >= 0)
		slipaway("in",player);
	    else
		slip_on_rear(player);
	    break;
	default:
	    slip_on_rear(player);
	    break;
	}
    }
}

void
set_trap_setter(string str)
{
    Trap_setter = str;
}

void
set_trap_qual(int num)
{
    Trap_qual = num;
}

int
do_flames(string str)
{
    object torch;

    if (!str)
    {
	return 0;
    }
    if (str == "slick" || str == "oil slick" || str == "oil")
    {
	torch = present("torch",TP);
	if (objectp(torch) && torch->query_lit() != 0)
	{
	    write("You "+query_verb()+" the oil slick, removing it from the ground!\n");
	    say("The oil slick, is lit by "+QTNAME(TP)+" and burns quickly and "+
	      "soon disappears.\n");
	    remove_alarm(alarm_id);
	    remove_object();
	    return 1;
	}
	else
	{
	    write("You need a lit torch to "+query_verb()+" the oil slick.\n");
	    return 1;
	}
    }
    return 0;
}

int
do_cover(string str)
{
    if (!str)
	return 0;
    if (str == "oil with dirt" || str == "slick with dirt" || "oil slick with dirt")
    {
	write("You cover the "+short()+" with dirt, making it useless as a trap.\n");
	say(QCTNAME(TP)+" covers the "+short()+" with dirt.\n");
	remove_alarm(alarm_id);
	remove_object();
	return 1;
    }
    return 0;
}

void
go_byebye()
{
    remove_alarm(alarm_id);
    tell_room(ENV(TO),"The "+short()+" evaporates completely and "+
      "no longer possess any threat of making you slip on your behind.\n");
    remove_object();
}
