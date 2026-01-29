inherit "/d/Shire/std/room.c";

#include "/d/Shire/defs.h"
#include <std.h>
#include <macros.h>
#include <stdproperties.h>

//** Global Variables **//
int    Gate_open;
object Clock;
string Other_room,
       Direction;

//** Prototypes **//
string gate_desc();
int block();
void create_gate_room();
int query_gate_opened();


void
create_shire_room()
{
    set_short("A standard gate room");
    set_long("You stand within a standard gate room.\n");

    Clock = find_object("/d/Gondor/common/lib/clock");
    Gate_open = query_gate_opened();

    add_item(({ "gate", "gates" }), &gate_desc());
    add_exit(Other_room, Direction, &block());

    create_gate_room();
}


/*
 *  function name  : create_gate_room
 *  description    : define room specific things here for
 *                   objects inheriting this file
 */

void
create_gate_room()
{
}

void
init()
{
    ::init();
    
    add_action(knock, "knock");
}

int
query_gate_opened()
{
    int hour = Clock->query_hour;

    return (((hour < 8) || (hour > 22)) ? 0 : 1);
}

int
knock(string str)
{
    if (!strlen(str))
        return 0;

    if (str != "gate" && str != "gates" && str != "on the gates" &&
        str != "on the gate" && str != "on gate" && str != "on gates")
    {
        NF("Knock on what? The gates perhaps?\n");
        return 0;
    }

    if (query_gate_opened())
    {
        NF("You knock in the air wildly, just to discover "+
            "the gates are open.\n");
        return 0;
    }

    write("You knock loudly on the gates to wake the hobbit guard.\n");
    say(QCTNAME(TP)+" knocks loudly on the gates.\n");
    set_alarm(2.0, 0.0, &open_gate(TP));
}

void
open_gate(object player)
{
    if (!objectp(player))
        return;

    Gate_open = 1;
    write("The gate opens just wide enough to allow you into Bree.\n");
    say("The gates open and a sleepy guard motions for "+
        HIM_HER(player)+" to pass through quickly.\n");
    set_alarm(5.0, 0.0, close_gate);
}

void
close_gate()
{
    Gate_open = 0;
    write("The hobbit guard heads off to get some sleep closing "+
        "the gates behind him.\n");
}

int
block()
{
    if (query_gate_opened())
    {
        if (member_array(TP->query_name, Killers) == 1)
        {
            write("Avoiding the suspicious gaze of the guards you "+
                "manage to sneak through the gates.\n");
        }

        else
            write("You pass through the gates into Bree.\n");
    
        return 0;
    }

    if (member_array(TP->query_name(), Killers) == 1)
    {
        write("You murderous swine! I recognize you. Don't even think "+
            "about coming into our town again!\n");
        say("The hobbit guard seems furious with "+QCTNAME(TP)+" and "+
            "refuses to let "+HIM_HER(TP)+" past the gates.\n");
        return 1;
    }

    if (!TP->test_bit("Shire", EASTERN_GROUP, BREE_AID_BIT))
    {
        write("I see no reason why I should trust you. "+
            "Come back in the morning and I might let you in.\n");
        return 1;
    }

    return 0;
}

block() {
  check_gates();
  if (gatestate) write("You pass the gates.\n");
  else {
    if (this_player()->query_wiz_level()) {
      pass_msg();
      return 0;
    }
    write("You try desperately to get past the gates, but fail.\n");
    write("Maybe you should knock on the gates to wake up the guard...\n");
  }
  return !gatestate;
}

wizinfo() {
  string str;
  check_gates();
  str = gatestate ? "Open" : "Closed";
  return "Current game time:  " + clock->query_time() + "\n"+
         "Gates open at:      08:00\n"+
         "Gates close at:     22:00\n"+
         "Current gate state: " + str + ".\n";
}

check_gates() {
  int hour;

  hour = clock->query_hour();
  if (hour < 8 || hour >= 22) gatestate = 0;
  else gatestate = 1;
}

query_state() { return gatestate; }

set_other_room(string str) { other_room = str; }
query_other_room() { return other_room; }

set_direction(string str) { direction = str; }
query_direction() { return direction; }
