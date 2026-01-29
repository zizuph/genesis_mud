/* 
 *	/d/Gondor/common/lib/wagon.c
 *
 *	A generic wagon to be inherited.
 *	By Elessar, March '92
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Recoded.
 */
#pragma strict_types

inherit "/std/object.c";
inherit "/lib/trade.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define DELAY		  2.0
#define TURN_DELAY	120.0
#define FEE              12

/*
 *	Prototypes:
 */
public string  carriage_short();
public string  carriage_long();
public string  exa_horses();
public void    tour_move();

/*
 *	Global variables:
 */
static int     Horses,
               Max_Horses,
               Move_Id,
	       Turn_Id,
	       Max_Passengers = 5,
	       Leavable,
	       Step = 0,
	       Speed,
	       Fee = FEE;
static object  Wagon_Inside;
static string *Path   = ({ }),
              *Tour   = ({ }),
	      *Retour = ({ }),
               Goal,
	       Tour_Goal,
	       Retour_Goal;

public void    set_tour(string *rooms)      { Tour        = rooms; }
public void    set_retour(string *rooms)    { Retour      = rooms; }
public void    set_tour_goal(string name)   { Tour_Goal   = name;  }
public void    set_retour_goal(string name) { Retour_Goal = name;  }
public void    set_max_passengers(int i)    { Max_Passengers = i;  }
public void    set_leavable(int i = 1)      { Leavable    = i;     }
public int     query_leavable()             { return Leavable;     }
public void    set_fee(int i)               { Fee = i; }

static string
read_sign()
{
    return "\n\tMinas Tirith - Edoras\n\n" +
	     "\tFare: 12 copper coins\n\n";
}

private void
adjust_speed()
{
    Speed = Max_Horses - Horses + 1;
}

public int
set_horses(int i)
{ 
    if (i > Max_Horses)
	return 0;
    Horses = i;
    adjust_speed();
    return 1;
}

public int     query_horses() { return Horses; }

public int
set_max_horses(int i)
{
    if (i < Horses)
	return 0;

    Max_Horses = i; 
    adjust_speed();
    return 1;
}

public int
set_wagon_inside(mixed obj)
{
    if (stringp(obj))
    {
	FIX_EUID;
	obj = clone_object(obj);
    }
    if (!objectp(obj))
	return 0;
    Wagon_Inside = obj;
    return 1;
}

public object  query_wagon_inside() { return Wagon_Inside; }

public void
create_wagon()
{
}

nomask void
create_object()
{
    create_wagon();

    FIX_EUID;
    set_short(carriage_short);
    set_pshort("carriages pulled by horses");
    set_long(carriage_long);
    add_item( ({ "horse", "horses" }), exa_horses);

    add_prop(OBJ_I_WEIGHT, 400000);  /* Well, a wagon is heavy - 400 kg...*/
    add_prop(OBJ_I_VOLUME, 400000);  /* Large volume too :) */
    if (IS_CLONE && objectp(Wagon_Inside))
	Wagon_Inside->set_wagon(TO);

    config_default_trade();

    add_item( ({ "sign", }), read_sign());
    add_cmd_item( ({ "sign", }), "read", read_sign());
}

public string
carriage_short()
{
    if (Horses > 1) 
	return "carriage pulled by " + LANG_WNUM(Horses) + " horses";
    else if (Horses > 0) 
	return "carriage pulled by one horse";
    else 
	return "horse carriage with no horses";
}

public string
carriage_long()
{
    int     s;
    object *pass;
    string  long_descf;

    if (Horses > 1) 
	long_descf = "This is a wooden horse carriage, currently "
	    + "pulled by " + LANG_WNUM(Horses) + " horses.";
    else if (Horses > 0) 
	long_descf = "This is a wooden horse carriage, currently "
	    + "pulled by one horse.";
    else 
	long_descf = "This is a wooden horse carriage, currently "
	    + "not pulled by any horses.";
    if (s = sizeof(pass = FILTER_LIVE(all_inventory(Wagon_Inside))))
	long_descf += COMPOSITE_LIVE(pass) + 
	    ((s == 1) ? " is " : " are ") + 
	    "riding in the carriage.";
    else 
	long_descf += " There is no one in the wagon right now, "
	    + "except the driver.";

    long_descf += " From a little sign on the side of the carriage, "
	+ "you understand that it runs between Minas Tirith and Edoras.";

    return BSN(long_descf);
}

public string
exa_horses()
{
    if (Horses <= 0) 
	return "There are no horses pulling the horse-carriage.\n";
    if (Horses == 1) 
	return "A strong cart-horse has been put before the horse-carriage. "+
	    "It looks to be able to pull the wagon without problem.\n";
    else 
	return CAP(LANG_WNUM(Horses)) + " cart-horses have been "
	    + "put in front of the horse-carriage. They look strong "
	    + "and fresh, quite able to pull the wagon, and at "
	    + "a decent pace too.\n";
}

private void
make_noise(string dir)
{
    tell_room(ENV(TO), "The wagon whirls up some dust as it passes "
	      + "you on its way "+dir+"wards.\n");
    tell_room(Wagon_Inside, "The wagon rambles on "+dir+"wards "
	      + "along the road to " + Goal + ".\n");
}

public void
prepare_tour() 
{
    Goal = Tour_Goal;
    Path = Tour;
    Step = -1;

    tell_room(ENV(TO), "The wagon-driver yells: "
	      + "All passengers aboard! The transport to "
	      + Goal + " leaves soon!\n");
    tell_room(Wagon_Inside, "The wagon-driver yells: "
	      + "All passengers aboard! The transport to "
	      + Goal + " leaves soon!\n");

    set_leavable(0);

    Move_Id = set_alarm(15.0, 0.0, tour_move);
}

public void
start(float delay) 
{
    Step = -1;
    tell_room(ENV(TO), "A horse-carriage comes rolling out of the stables.\n");
    set_alarm(delay / 2.0 + rnd() * delay, 0.0, prepare_tour);
}

public void
turn_back() 
{
    remove_alarm(Turn_Id);
    Turn_Id = 0;

    if (Goal == Tour_Goal)
    {
	Goal  = Retour_Goal;
	Path  = Retour;
    }
    else
    {
	Goal  = Tour_Goal;
	Path  = Tour;
    }

    Step = 0;
    tell_room(ENV(TO), "The wagon-driver yells: All passengers aboard! "
	      + "The transport to " + Goal + " is leaving soon!\n");
    tell_room(Wagon_Inside, "The wagon-driver yells: All passengers aboard! "
	      + "The transport to " + Goal + " is leaving soon!\n");
    set_leavable(0);

    Move_Id = set_alarm(itof(Speed) * DELAY, 0.0, tour_move);
}

public void
tour_move()
{
    int     ir;
    mixed   exits;
    string  dir,
            back_goal;

    remove_alarm(Move_Id);
    Move_Id = 0;

    if (Step < 0)
	Step = member_array(file_name(ENV(TO)), Path);
    if (Step < 0)
    {
	tell_object(Wagon_Inside, "BUG: Unknown location!\n");
	return;
    }

    if((ir = member_array(Path[++Step], exits = ENV(TO)->query_exit())) < 0)
    {
	tell_object(Wagon_Inside, "BUG: Unknown destination!\n");
	return;
    }

    dir = exits[ir + 1];
    ENV(TO)->hook_wagon_depart(TO, dir);
    make_noise(dir);

    move(Path[Step]);
    tell_room(ENV(TO), "A wooden carriage pulled by horses comes rambling in.\n");
    ENV(TO)->hook_wagon_arrive(TO, dir);

    // Did we arrive at the last stage of the trip?
    if (Step == (sizeof(Path) - 1))
    {
	set_leavable(1);
	if (Goal == Tour_Goal)
	    back_goal = Retour_Goal;
	else
	    back_goal = Tour_Goal;
	tell_room(ENV(TO), "The wagon-driver yells: "
		  + "The carriage will return to " + back_goal + " in 1 hour!\n");
	tell_room(Wagon_Inside, "The wagon-driver yells: "
		  + "All right, we have arrived in " + Goal +"! "
		  + "The carriage will return to " + back_goal + " in 1 hour!\n");
	Turn_Id = set_alarm(TURN_DELAY, 0.0, turn_back);
    }
    else
    {
	Move_Id = set_alarm(itof(Speed) * DELAY, 0.0, tour_move);
    }
}

public string
query_pay_prop()
{
    return "_Gondor_Generic_Wagon";
}

public int
enter_wagon(string str) 
{
    if (!strlen(str) || !id(str))
    {
	NFN("Enter what?");
	return 0;
    }

    if (TP->query_prop(query_pay_prop()) != TO)
    {
	write("You have to pay the driver first.\n" +
	      "The fee is just "+Fee+" copper coins.\n");
	return 1;
    }

    TP->remove_prop(query_pay_prop());

    write("You enter the horse carriage.\n");
    say(QCTNAME(TP) + " enters the horse carriage.\n", TP);
    tell_room(Wagon_Inside, QCTNAME(TP) + " enters the horse carriage.\n");
    if (IS_CLONE && objectp(Wagon_Inside))
    Wagon_Inside->set_wagon(TO);
    TP->move_living("M", Wagon_Inside);
    return 1;
}

public int
add_horse(int i = 1)
{
    if ((Horses + i) > Max_Horses) 
    {
	write("The carriage is already pulled by the maximal number "+
	      "of horses.\n");
	return 0;
    }
    Horses += i;
    adjust_speed();
    return 1;
}

public int
remove_horse(int i = 1)
{
    if (Horses >= i)
    {
	Horses -= i;
	adjust_speed();
	return 1;
    }
    write("There are no horses pulling the carriage!\n");
    return 0;
}

public int
pay_driver(string str)
{
    int     friend,
            n,
	    war;
    mixed   res;
    string  give,
            change;

    if (!strlen(str) || (str != "driver" && str != "fee"))
    {
	NFN("Pay whom?");
	return 0;
    }

    if (TP->query_prop(query_pay_prop()) == TO)
    {
	write("You have already paid the fee.\n");
	return 1;
    }

    if (Horses < 1) 
    {
	write("The carriage has no horses.\n" + 
	      "It will not go anywhere.\n");
	return 1;
    }


    FIX_EUID;
    war = CLOCK->query_war();
    friend = query_friend_or_foe(TP);

    if ((friend < 0) && !TP->query_wiz_level())
    {
	write("As you approach the wagon and driver, the horses " +
	      "start to whinny and kick, so eventually you give " +
	      "up the attempt.\n");
	say("As "+QCTNAME(TP)+" approaches the wagon and driver, " +
	    "the horses start to whinny and kick wildly, until " +
	    TP->query_pronoun() + " gives up.\n", TP);
	return 1;
    }

    if (M_TIRITH_MASTER->query_enemy(TP->query_real_name(),
				     TP->query_race())) 
    {
	write("The wagon-driver yells at you: " +
	      "Go away! I won't help enemies of Gondor to enter "+
	      "the White City!\n");
	say("The wagon-driver yells at " + QTNAME(TP) +
	      ": Go away! I won't help enemies of Gondor to enter "+
	      "the White City!\n", TP);
	return 1;
    }

    if ( war &&
	 friend == 0 )
    {
	write("The wagon-driver says to you: " +
	      "I'm sorry, but Gondor is at War. We are under firm "+
	      "instructions not to transport any strangers into "+
	      "the City.\n");
	say("The wagon-driver says to " + QTNAME(TP) +
	      ": I'm sorry, but Gondor is at War. We are under firm "+
	      "instructions not to transport any strangers into "+
	      "the City.\n", TP);
	return 1;
    }
	 

    if ((n = sizeof(FILTER_LIVE(all_inventory(Wagon_Inside)))) >=
	Max_Passengers)
    {
	write("The wagon-driver says to you: " +
	      "Sorry, but I've already got a full load of " +
	      LANG_WNUM(n) + " passengers for this trip.\n" + 
	      "The wagon-driver says to you: " +
	      "You'll have to wait.\n");
	say("The wagon-driver says to " + QTNAME(TP) + 
	      ": Sorry, but I've already got a full load of " +
	      LANG_WNUM(n) + " passengers for this trip.\n" + 
	      "The wagon-driver says to " + QTNAME(TP) +
	      ": You'll have to wait.\n", TP);
	return 1;
    }

    if (pointerp(res = pay(Fee, TP)) && (sizeof(res) > 1))
    {
	give = text(res);
	change = text(res[sizeof(MONEY_TYPES)..]);
	write("You pay " + text(res) + " to the driver" +
	      (strlen(change) ? " and get " + change +
	       " back as change" : "") + ".\n");
	say(QCTNAME(TP) + " pays the driver.\n");
	TP->add_prop(query_pay_prop(), TO);
	return 1;
    }
    write("You do not have the money.\n");
    return 1;
}

public void
init() 
{
    ::init();

    add_action(enter_wagon, "enter");
    add_action(enter_wagon, "board");
    add_action(pay_driver,  "pay");
}

