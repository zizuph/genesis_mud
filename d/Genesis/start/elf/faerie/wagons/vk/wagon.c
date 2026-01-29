/*
 * /d/Ansalon/taman_busuk/neraka/caravan/wagon.c
 *
 * Based on the Neraka to Sanction wagon.
 * Originally coded by Ashlar for Krynn. Thanks!!
 * Converted over to Faerie by Finwe, May 2005
 */

#include "defs.h"
#include "caravan.h"
#include "path.h"

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

mixed *gPath = VK_TO_FAERIE + FAERIE_TO_VK;
string *gMessage = VK_TO_FAERIE_MESSAGES + FAERIE_TO_VK_MESSAGES;

#define SECSTEP 5
object gWagonbed;
int gMoveAlarm = 0;
int gPosition;
int gTimeAtPos;

void
create_object()
{
    if (!IS_CLONE)
        return;

    set_name("cart");
    set_adj("large");
    add_adj("wooden");

    set_long("This is a large wooden cart. It is rectangular with " +
        "sturdy wheels and pulled by two strong horses. A driver sits " +
        "at the front of the wagon, waiting to make his rounds.\n");

    add_item("wagonbed","The wagonbed is protected by an " +
    "arching roof of canvas. A flap at the rear makes it " +
    "possible to enter it.\n");
    add_item("canvas","An arching roof of canvas protects " +
    "the wagonbed.\n");
    add_item(({"horses","pair of horses"}),
    "A pair of brown working horses.\n");
    add_item("driver","The driver sits on the front " +
    "of the wagon, keeping an eye on the wagon and " +
    "the horses. As you approach him, he looks at you expectantly, " +
    "rubbing his thumb and forefinger together.\n");
    add_item(({"remounts","string of remounts","string"}),
    "A line of horses tied together with ropes trail after the wagon.\n");
    add_prop(OBJ_I_WEIGHT, 950000);
    add_prop(OBJ_I_VOLUME, 760000);
    add_prop(OBJ_M_NO_GET, 1);

    setuid();
    seteuid(getuid());

    if (LOAD_ERR(WAGONBED))
    {
//        (NERAKA_ADMIN)->adminlog("Could not load file: " + WAGONBED);
write("wagon bed not loaded.\n");
        set_alarm(1.0,0.0,remove_object);
    }

    gWagonbed = find_object(WAGONBED);
    if (gWagonbed)
        gWagonbed->set_wagon(TO);

}

public void
tell_wagon(string s)
{
    tell_room(gWagonbed, s);
}


public void
set_wagonbed(object wagonbed)
{ gWagonbed = wagonbed; }

public object
query_wagonbed()
{ return gWagonbed; }

string
set_wagon_empty()
{
    gWagonbed->set_cargo(0);
    tell_room(E(TO),"Some people rush out and begin unloading the wagon.\n");
    return "Some people start unloading the cargo.\n";
}

string
set_wagon_full()
{
    string cargo;
    cargo = CARGO_TYPES[random(sizeof(CARGO_TYPES))];
    gWagonbed->set_cargo(cargo);
    tell_room(E(TO),"Some people rush out and begin loading the wagon with " +
        cargo + ".\n");
    return "Some people begin loading the wagon with " + cargo + ".\n";
}   

int
is_wagonstop(object r)
{
    if (objectp(r) && member_array(file_name(r), WAGON_STOPS) != -1)
        return 1;
    else
        return 0;
}

public int
query_moving()
{
    if (E(TO) && is_wagonstop(E(TO)))
        return 0;
    else
        return 1;
}

void
do_a_move()
{
    string s;
    object r,oldr;
    if ((gPosition==-1) || (gTimeAtPos>=gPath[gPosition*2+1]))
    {
        gPosition++;
        if (gPosition >= (sizeof(gPath)/2))
            gPosition = 0;
        s = gPath[gPosition*2];
        LOAD_ERR(s);
        r = find_object(s);
        if (!objectp(r))
            tell_wagon("Fatal error, couldn't find path! " +
                "Contact a wizard to help you out.\n");

        oldr = E(TO);
        move(r);
        if (is_wagonstop(r))
        {
            tell_wagon("The wagon stops as you reach your " +
                "destination.\n");
        }
        else if(oldr && is_wagonstop(oldr))
        {
            tell_wagon("You bump against the side of the " +
            "wagon as it starts moving.\n");
        }
        if (gMessage[gPosition])
            tell_wagon(check_call(gMessage[gPosition]));
        gTimeAtPos = 0;
    }
    else
        gTimeAtPos += SECSTEP;
}

void
start_moving()
{
    if (gMoveAlarm)
        return;
    gPosition = -1;
    gMoveAlarm = set_alarm(1.0, 5.0, do_a_move);
}

void
stop_moving()
{
    if (!gMoveAlarm)
        return;
    remove_alarm(gMoveAlarm);
    gMoveAlarm = 0;
}
void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    if (env && env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "The " + short() + 
        " rumbles away, in a cloud of dust.\n");
    }
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (env && env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "A " + short() + 
        " rumbles in.\n");
    }
}

int
do_enter(string arg)
{
    object steed;
    
    NF("Enter what? The wagon perhaps?\n");
    if ((!stringp(arg)) || !((arg == "wagon") ||
        (arg == "the wagon")))
    { return 0; }

    NF("The driver stops you from entering the wagon. Perhaps you should pay him first?\n");

    if (!TP->query_prop(FAERIE_PAID_WAGON_FEE))
        return 0;

    TP->remove_prop(FAERIE_LIVE_O_WAGON_STEED);
    if ((steed = TP->query_prop(LIVE_O_STEED)) && (!TP->query_wiz_level()))
    {
        TP->command("$dismount");
        TP->catch_msg("You tie your " + steed->short() + " to the back of the wagon so you can bring it along with you.\n\n");
        tell_room(E(TP), QCTNAME(TP) + " ties " + HIS_HER(TP) + " " +
            steed->short() + " to the back of the wagon.\n",
            ({ TP }));
        TP->add_prop(FAERIE_LIVE_O_WAGON_STEED, steed);
        steed->move_living("M",AVOID);
        
    }
    write("You climb into the covered wagon.\n");
    if (!TP->move_living("entering the wagon",gWagonbed,1))

        TP->add_prop(FAERIE_PAID_WAGON_FEE,
            TP->query_prop(FAERIE_PAID_WAGON_FEE) - 1);
    else if (steed = TP->query_prop(FAERIE_LIVE_O_WAGON_STEED))
    {
        write("As you failed to enter the wagon, you retrieve your horse.\n");
        steed->move_living("M",E(TP));
        TP->remove_prop(FAERIE_LIVE_O_WAGON_STEED);
    }
        
    return 1;
}

int
do_bribe(string arg)
{
    int *c;
    int pay;
    NF(capitalize(query_verb()) + " whom? The driver perhaps?\n");
    if ((!stringp(arg)) || !((arg == "driver") ||
        (arg == "the driver")))
    { return 0; }

    c = MONEY_COINS(TP);
    if (c[0] >= 6)
        pay = 6;
    else if (c[1] > 0)
        pay = 12;
    else if (c[2] > 0)
        pay = 144;
    else if (c[3] > 0)
        pay = 1728;
    else
    {
        NF("The driver looks at what you have to offer, and " +
            "laughs at you.\n");
        return 0;
    }

    MONEY_ADD(TP,-pay);
    TP->add_prop(FAERIE_PAID_WAGON_FEE,
        TP->query_prop(FAERIE_PAID_WAGON_FEE) + 1);
    write("You hand the driver " + MONEY_TEXT_SPLIT(pay) +
        ", and he nods at you, motioning you to climb into the wagon.\n");
    say(QCTNAME(TP) + " hands some coins to the driver.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
    add_action(do_enter,"board");
//  add_action(do_bribe,"bribe");
    add_action(do_bribe,"pay");
    add_action(do_bribe,"tip");
}
