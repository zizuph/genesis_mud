#include "defs.h"

#define WEST_GATE "/d/Shire/common/hollin/under_wall"
#define STAIR     "/d/Shire/moria/mines/stair1"
#define DOORS_PROP  "_Shire_i_push_moria_doors"
#ifndef ROOM_I_NO_ALLOW_STEED
#define ROOM_I_NO_ALLOW_STEED  "_room_i_no_allow_steed"
#endif

int do_push(object player);

CONSTRUCT_ROOM
{
    set_short("A dark room in the mountain");
    set_long("@@my_long@@");
    add_item("stairs",
      "They are wide, climbing steeply up into the darkness.");
    UP("stair1");
    //  add_exit(STAIR, up, 0, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}

string
my_long()
{
    string str;
    if (file_name(TP->query_prop(LIVE_O_LAST_ROOM)) != STAIR)
    {
	str = "Standing stunned, enveloped in the sudden darkness, you realize " 
	+ "a considerable change in temperature. Outside it was freezingly cold, "
	+ "not like the humid and temperate air here. " 
	+ "Then it comes to you. You are inside the dreadful Mines of Moria! ";
	if (TP->query_race_name() == "dwarf")
	    str +="Dreadful yes, but only now, not before when the dwarves, the Khazad, "
	    + "ruled and mined this underground masterpiece. Khazad-dum it was called, "
	    + "glorious in tales, with prosperity for the whole Tribe of Durin. But "
	    + "considering the evil spirit of the Western Gate, the Bane of Durin must "
	    + "have made this dwarven city a vomiting, ruined and decayed manifest "
	    + "of long forgotten dwarven art and craftsmanship. ";
	else
	    str +="The Tales of Old tells of myriads of underground tunnels and caverns, "
	    + "once made by stocky dwarves. But it is a dark and omnious place now, "
	    + "utterly dangerous, with traps of many kinds. Free people entering "
	    + "these Mines are seldom ever seen again.. ";

	str += "Adapting to the dim light, you see a some wide steep stairs starting here. "+
	"But of the Western Gate, nothing can be seen.";
	return str;
    }
    else
    {
	return "You are standing at the bottom of the stairs you came from. "
	+ "Here is where the Western Gate is supposed to be, and you " 
	+ "remember the Lake of Sirannon and the dreadful Watcher in the "
	+ "Lake. Considering this, you should not seek an exit this way. " 
	+ "There is said to be another Gate, the East Gate, by the Dimrill "
	+ "Valley. Other exits, you do not know about.";

    }
} 
void
init()
{
    ::init();

    add_action("start_push","push");

    write("As you enter the gate-room, you notice the doors may be " +
        "pushed to take you out of here.\n");

    if (interactive(this_player()))
        catch(call_other(MORIA_NPC + "clone_handler", "??"));

}

int
start_push(string str)
{

    if(!str)
    {
	notify_fail("Push what? The doors?\n");
	return 0;
    }
    if((str != "door") && (str != "doors"))
    {
	notify_fail("Push the " + str + "? Why?\n");
	return 0;
    }
    if (objectp(TP->query_attack()))
    {
	notify_fail("You are unable to safely operate the doors " +
	  "whilst in combat.\n");
	return 0;
    }
    if (TP->query_prop(DOORS_PROP))
    {
	NF("You push the doors again but they won't open any faster.\n");
	return 0;
    }

    say(QCTNAME(this_player())+ " pushes on the doors, and they begin "+
      "to open.\n");
    write("You push hard on the doors and they begin to open.\n");

    set_alarm(3.0, 0.0, &do_push(TP));
    TP->add_prop(DOORS_PROP, 1);
    return 1;

}

int
do_push(object player)
{
    object enemy;

    player->remove_prop(DOORS_PROP);
    if (!present(player, this_object()))
	return 1;
    if (objectp(enemy = player->query_attack()) && enemy->query_npc())
    {
	tell_room(this_object(), QCTNAME(enemy) +" slams into the "+
	  "doors which closes them tight.\n");
	enemy->command("$laugh");
	return 1;
    }
    set_this_player(player);

    write("You tumble through the doors as they open, spilling out onto "+
      "the ground outside.\n"+
      "The doors slam shut behind you.\n");
    say(QCTNAME(this_player())+ " tumbles through the open doors.\nThey "+
      "immediately slam shut again.\n");
    tell_room(WEST_GATE,QCTNAME(this_player())+ " comes tumbling out "+
      "of nowhere, you hear doors slam behind.\n");
    this_player()->move_living("M",WEST_GATE,1);

    return  1;

}
