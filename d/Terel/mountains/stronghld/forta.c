#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

inherit STDROOM;

int close_gate;

#define GATE    MOUNTAIN_DIR + "stronghld/fielde"
#define FIELDS   ({ MOUNTAIN_DIR + "stronghld/fielde" })

object gatekeep;
object warrior1;
object warrior2;
object warrior3;
object warrior4;

public void
reset_room()
{
    if (!warrior1) {
        warrior1=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior1->move(this_object());
    }

    if (!warrior2) {
        warrior2=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior2->move(this_object());
        warrior1->team_join(warrior2);
    }

    if (!warrior3) {
        warrior3=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior3->move(this_object());
        warrior1->team_join(warrior3);
    }

    if (!warrior4) {
        warrior4=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior4->move(this_object());
        warrior1->team_join(warrior4);
    }

    if (!gatekeep) {
        gatekeep=clone_object(MOUNTAIN_DIR + "stronghld/npc/gatekeep");
        gatekeep->move(this_object());
        warrior1->team_join(gatekeep);
    }

}


public void
create_room()
{
    set_short("Gatehouse");
    set_long("You are standing in the gatehouse, entrance " +
       "to Stonehold's barracks. To the east is the " +
       "metal gate leading outside. To the west is a passageway " +
       "heading deeper into the mountain.\n");

    add_item(({"gate","metal gate"}),
       "The large metal gate extends from the arch design entranceway " +
       "ceiling to the ground. The iron bars of the gate are made " +
       "from thick mithril alloy. It looks very strong. You can " +
       "look at the field just outside the gate from here.\n");
 
    add_item(({"fields","field"}),"@@exa_fields");

    add_cmd_item(({"metal gate","gate"}),"open",
       "@@open_gate");

    add_exit(MOUNTAIN_DIR + "stronghld/fielde", "east", "@@check_east");
    add_exit(MOUNTAIN_DIR + "stronghld/fortb","west",0,1);
    reset_room();
}


int
check_east()
{

    if(!(GATE)->query_gate())
    {
        write("You pass through the metal gate.\n");
        return 0;
    }
    else
    {
        write("The gates are closed. Perhaps, the " +
           "gatekeeper might open them for you.\n");
        return 1;
    }
} 

/* This function is illegal per AoB and AoD -- Clubs should not give out
 * advantages of this nature.
 * Removed by Lilith, May 2008
 
int
open_gate()
{
    object explorer;
    explorer = TP->query_prop("_live_i_am_explorer");

    if(!(GATE)->query_gate())
    {
        command("say The gate is already open.\n");
        return 1;
    }

   if (explorer)
    {
       write("You press your signet ring against " +
          "a metal plate next to the gate.\n");
       say(QTNAME(TP) +" presses his ring against a plate " +
          "next to the gate.\n");

       (GATE)->open_gate();
       set_alarm(8.0, -1.0, "close_gate");
       return 1;
    }
       write("You cannot seem to figure out how to " +
          "open the gate. Perhaps, the gatekeeper " +
          "can help.\n");
       return 1;
}
*/
int
open_gate()
{
    if(!(GATE)->query_gate())
    {
        command("say The gate is already open.\n");
        return 1;
    }

    write("You cannot seem to figure out how to " +
        "open the gate. Perhaps, the gatekeeper " +
        "can help.\n");
    return 1;
}


void
close_gate()
{
    (GATE)->close_gate();
    return;
}


public string
exa_fields()
{
  object *inv, *live, room;
  int i;

  inv = ({});
  for (i = 0; i < sizeof(FIELDS); i++)
    if ((room = find_object(FIELDS[i])))
      inv += all_inventory(room);

  if (sizeof(inv)) {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if (sizeof(live))
      return "  gazing through the gate you see " +
        COMPOSITE_LIVE(live) + " standing there.\n";
  }
  return "  The field outside the gate looks barren.\n";
}


