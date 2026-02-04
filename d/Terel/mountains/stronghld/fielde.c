/*
 *west_gate.c Gate leading into the stronghold barracks  
 *
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>


int gate_closed;

#define IN_GATE MOUNTAIN_DIR + "stronghld/forta"
#define GATEHOUSE  ({ MOUNTAIN_DIR + "stronghld/forta" })

int query_gate();
int goblin_check();
void open_gate();


public void
create_room()
{
    gate_closed = 1;

    set_short("Stronghold entrance");
    set_long("The cobblestone road ends before a large metal gate.\nTo the north and " +
       "south are barren fields. To the east leads back towards the main road.\n");

    add_item(({"rock","pass","cliffs","cliff","walls"}),
       "The pass looks as if it was carved out of solid rock presumably " +
       "by dwarven hands. The tall cliffs rise up on either side of the " +
       "the field and road. Covered catwalks run the length of the cliffs " +
       "on either side.\n");

    add_item(({"gate","metal gate"}),
       "The large metal gate extends from the arch design entranceway " +
       "ceiling to the ground. The iron bars of the gate are made " +
       "from thick mithril alloy. It looks very strong. You can " +
       "look at the gatehouse just inside the gate from here.\n");

    add_item(({"catwalk","catwalks"}),
       "The catwalks extend high above the cliffs on either side of " +
       "the pass.\n");

    add_item(({"snow","debris"}),
       "The area is void of any debris or snow. The dwarves make sure " +
       "that the fields and road are clear.\n");

    add_item(({"field","fields","road","cobblestone road","cobblestones",
               "cobblestone","stone","stones"}),
       "The rocky fields make up for the floor of the pass. The dwarves " +
       "built a road out of stones fit tightly together of which runs between " +
       "the northern and southern gates.\n");

    add_item(({"gatehouse"}),"@@exa_gatehouse");

    add_item(({"wall","walls","fortress"}),
       "The fortress beyond the gate looks like a series of tunnels " +
       "dug into the mountain. You see no other way in. The walls are " +
       "actually the natural cliff face made of solid rock.\n");

    add_cmd_item(({"wall","walls"}),({"scale","climb"}),
       "You dont seem to find a decent looking hand or foothold. " +
       "You cant climb the walls.\n");

    add_cmd_item(({"metal gate","gate"}),({"scale","climb"}),
       "The gate is an arch design, extending downward from " +
       "solid rock. You would accomplish nothing by attempting " +
       "to climb it.\n");

    add_cmd_item(({"gate","gates"}), "open", 
       "The gates can only be opened by the guards above them.\n");
 
   add_cmd_item(({"gate","metal gate","on gate"}), "knock",
                            "@@knock_gate");


    add_exit(MOUNTAIN_DIR + "stronghld/fieldg","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fieldc","south",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/roadc","east",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/roadb","southeast",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/roadd","northeast",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/forta", "west", "@@check_west");

    reset_room();

}


int
goblin_check()
{
    if(TP->query_race() == "goblin" && TP->query_alignment() < 910)
    { 
       return 1;
    }
    return 0;
}


int
was_attacked()
{
    if (TP->query_prop("_stonehld_attacked"))
    { 
       return 1;
    }
    return 0;
}


int
query_gate()
{
    return gate_closed;
}



int
knock_gate()
{

    object gatekeep, room;
    room = find_object("/d/Terel/mountains/stronghld/forta");
    gatekeep = find_living("Terel:golan");
   
    if(!present(gatekeep, room))
    {
       write("No one seems to be attending the gate.\n");
      return 1;
    }


    if(!query_gate())
    {
        write("The gate is already open.\n");
        return 1;
    }

    if(TP->query_prop(OBJ_I_INVIS))
    {
        write("The guards peer through the metal bars of the gate " +
              ", but see nothing and go back about "+
              "their business.\n");
        say("The guards peer through the metal bars of the gate, " +
            "but see nothing and go back about their business.\n");
        return 1;
    }

    if(goblin_check())
    {
        write("The guards peer through the metal bars of the gate " +
            "at you.\n");
        say("The guards peer through the metal bars of the gate at " +
            QCTNAME(TP)+".\n");
        write("One of the guards shouts at you: I dont know how you got in " +
              "here, but you better crawl on out before I come out there!\n");
        say("One of the guards shouts at "+QCTNAME(TP)+ ": I dont know " +
            "how you got in here, but you better crawl on out before I " +
            "come out there!\n");

        return 1;
    }


   if(was_attacked())
     {
        write("The guards peer through the metal bars of the gate at " +
              "you.\n");

        write("One of the guards says to the other guard, yah. " +
           "This one matches the description of a " +
           "troublemaker the previous watch had earlier. Hey, " +
            "you better leave now, we got orders to " +
            "to kill you onsight, get lost or ELSE!\n");

        say("The guards peer through the metal bars at " +
             QCTNAME(TP)+ ". \n\nOne of the guards says to the other "+
           "guard: yah. "+QCTNAME(TP)+" matches the description of a " +
           "troublemaker the previous watch had earlier.\n Hey, " +
            QCTNAME(TP)+"! Better leave now, we got orders to " +
            "to kill you onsight, get lost or ELSE!\n");

        return 1;
     }


    write("You knock on a wood panel attached to the gate.\n");
    say(QCTNAME(TP) + " knocks on the gate.\n");

    write("The guards peer through the metal bars at you.\n");
    say("The guards peer through the metal bars at "+QCTNAME(TP)+".\n");

    write("A guard motions to someone to raise the gate.\n");
    say("A guard motions to someone to raise the gate.\n");

    set_alarm(2.0, -1.0, "open_gate");
    set_alarm(8.0, -1.0, "close_gate");
    return 1;

}

void
open_gate()
{
    tell_room(TO,"The metal gate raises slowly.\n");
    tell_room(IN_GATE,"The metal gate raises slowly.\n");
    gate_closed = 0;
    return;
}
    
void
close_gate()
{
    if(query_gate())
    {
        return;
    }

    tell_room(TO,"The metal gate lowers to the ground.\n");
    tell_room(IN_GATE, "The metal gate lowers to the ground.\n");
    gate_closed = 1;
    return;
}

   
int
check_west()
{
   object guard;

    if(query_gate())
    {
        write("The metal gate is closed.\n");
        return 1;
    }

    if(goblin_check() && TP->query_prop(OBJ_I_INVIS))
    {
        write("You pass through the metal gate and into the stronghold.\n");
        return 0;
    }

    if(goblin_check())
    {
        write("The guards inside the gate notice you moving towards the gate.\n");
        close_gate();
        return 1;
    }
    write("You pass through the metal gate entering the dwarven stronghold.\n");
    return 0;
}
       


public string
exa_gatehouse()
{
  object *inv, *live, room;
  int i;

  inv = ({});
  for (i = 0; i < sizeof(GATEHOUSE); i++)
    if ((room = find_object(GATEHOUSE[i])))
      inv += all_inventory(room);

  if (sizeof(inv)) {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if (sizeof(live))
      return " Gazing through the gate you see " +
        COMPOSITE_LIVE(live) + " standing there.\n";
  }
  return "  The gatehouse looks empty.\n";
}
