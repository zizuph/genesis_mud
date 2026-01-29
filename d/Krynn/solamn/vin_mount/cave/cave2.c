/* Terminator started this,
 * Aridor, 11/94
 */

#include "../local.h"

inherit CAVE_BASE

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

int bars = 1;
object hob1,hob2,hob3;

#define SOHM_DOUGAN_TASK "_sohm_earthskin_dougan_task_started"
#define SOHM_KIRK_TASK "_sohm_earthskin_kirk_task_hint"
#define RETRIEVED_ONJAT_DICE "_sohm_earthskin_onjat_dice_received"

void
reset_vin_mount_room()
{
    if (!sizeof(all_inventory(TO)))
      bars = 1;
    if (!hob1)
      {
	  hob1 = clone_object(LIV + "lhobgob");
	  hob1->move_living("M",TO);
	  hob1->command("emote gets up from his chair and glares at you!");
      }
    if (!hob2)
      {
	  hob2 = clone_object(LIV + "hobgob");
	  hob2->move_living("M",TO);
	  hob2->command("emote gets up from his chair and snarls at you!");
      }
    if (!hob3)
      {
	  hob3 = clone_object(LIV + "hobgob");
	  hob3->move_living("M",TO);
	  hob3->command("emote gets up from his chair and grins evilly at you!");
      }
    hob1->team_join(hob3);
    hob1->team_join(hob2);
}

void
create_vin_mount_room()
{
    set_short("Cave");
    set_long("The cave wall seems covered in lichen and water constantly "+
	     "drips on your head. There is a cold draft coming from "+
	     "the darkness somewhere ahead. There is an oak table in "+
	     "the center of this room with a couple of chairs " +
	     "standing around it.\n");
    
    add_exit(CAVE + "cave13", "west",0);
    add_item(({"draft","cold draft","darkness","wall"}),
	     "It is a very cold draft coming through a grid of iron that has " +
	     "been set into the wall.\n");
    add_item(({"hole","small hole"}),
	     "A small dark hole leading steeply downwards.\n");
    add_item(({"bars","bar","grid"}),
	     "The grid consists of a couple of iron bars that secure the hole, "+
	     "so no one falls into it.@@bend_already@@\n");
    add_item(({"table","chair","chairs"}),
	     "The old oak table is surrounded by four chairs. All pieces have seen " +
             "better days.@@onjat_dice_on_table@@\n");
    add_item(({"lichen","water"}),
	     "It is a little damp in this room, water is dripping down from " +
	     "above, giving the lichen here perfect living conditions.\n");
    add_item(({"dice","onjat dice"}),"@@onjat_dice");

    add_cmd_item(({"onjat dice from table","onjat dice","onjat dice from oak table",
                   "onjat dice from the table","onjat dice","dice","dice from table",
                   "dice from oak table","dice from the table"}),
                 ({"get","take","grab"}),"@@get_onjat_dice");

    LIGHT;
    INSIDE;
    set_alarm(1.0,0.0,"reset_room");
}   

string
onjat_dice()
{
    if(!this_player()->query_prop(SOHM_KIRK_TASK))
      return "Examine what?\n";
    else
      return "You notice a pair of onjat dice sitting in the middle of the table.\n";
}

string
onjat_dice_on_table()
{
    if(!this_player()->query_prop(SOHM_KIRK_TASK))
      return "";
    else
      return "\nYou notice a pair of onjat dice sitting in the middle of the table.";
}

string
get_onjat_dice()
{

    if(!this_player()->query_prop(SOHM_KIRK_TASK))
      return "Get what?\n";

    if(objectp(hob1))
    {
      return"The large hobgoblin blocks your attempt to approach the " +
	    "table.\n";
    }

    object dice = clone_object("/d/Krynn/solamn/vin_mount/obj/onjat_dice");
    dice->move(this_player());

    this_player()->add_prop(RETRIEVED_ONJAT_DICE, 1);
    this_player()->remove_prop(SOHM_KIRK_TASK);
    this_player()->remove_prop(SOHM_DOUGAN_TASK);

    say(QCTNAME(this_player())+ " grabs a pair of onjat dice off the table.\n");
    return "You grab a pair of onjat dice off the table.\n";

}

string
bend_already()
{
    if (bars)
      return "";
    else
      return " The bars are bent as though someone tried to climb through.";
}

void
init()
{
    ::init();
    ADD("crawl", "enter");
    ADD("crawl", "climb");
    ADA("crawl");
    ADA("bend");
}

int
crawl(string str)
{
    string dummy;
    object who;
    int i;
    if (!str || !stringp(str))
      {
	  NF(C(query_verb()) + " where?\n");
	  return 0;
      }
    i = sscanf(str,"%shole%s",dummy,dummy);
    if (!i)
      i = sscanf(str,"%sgrid%s",dummy,dummy);
    if (!i)
      i = sscanf(str,"%sbar%s",dummy,dummy);
    NF("What?\n");
    if (i == 2)
      {
	  if (hob3 && E(hob3) == TO) who = hob3;
	  if (hob2 && E(hob2) == TO) who = hob2;
	  if (hob1 && E(hob1) == TO) who = hob1;
	  if (CAN_SEE(who,TP))
	    {
		who->command("say Leave that alone will ya!");
		hob1->command("kill " + TP->query_real_name());
		hob2->command("kill " + TP->query_real_name());
		hob3->command("kill " + TP->query_real_name());
		return 1;
	    }
	  if (!bars || TP->query_prop(CONT_I_HEIGHT) < 80)
	    {
		write("You crawl into the small dark hole.\n");
		TP->move_living("into the hole", CAVE + "cave3", 1, 0); 
		return 1;
	    }
	  else
	    {
		write("You don't fit through the grid!\n");
		return 1;
	    }
      }
    else 
      return 0;
}

int
bend(string str)
{
    string dummy;
    int i;
    NF("What?\n");
    if (!str)
      return 0;
    i = sscanf(str,"%sgrid%s",dummy,dummy);
    if (!i)
      i = sscanf(str,"%sbar%s",dummy,dummy);
    if (i == 2)
      {
	  if (bars && TP->query_stat(SS_STR) > 22 + random(20))
	    {
		write("You summon all your strength and bend the bars enough " +
		      "to be able to enter.\n");
		say(QCTNAME(TP) + " bends the bars over the hole leading down.\n");
		bars = 0;
		return 1;
	    }
	  else
	    {
		write("You summon all your strength but the bars won't budge.\n");
		return 1;
	    }
      }
    else 
      return 0;
}

int
query_bars()
{
    return bars;
}

