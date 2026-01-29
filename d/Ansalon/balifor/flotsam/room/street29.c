#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;
object door;
int    dAlarm_id1;

/*
* Prototypes
*/
void remove_door();


void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Secret room");
    set_long("@@long_descr");

    add_item(({"stairway","stairs","staircase"}),"A spiral " +
      "staircase that leads down into the " +
      "darkness. It may have once been painted white, but the paint has long cracked " +
      "and peeled off. The smell of death rises from " +
      "the darkness below. \n");
    add_item("lantern","A lit lantern that has been " +
      "filled recently. \n");
    add_item(({"dust","floor","footprints"}),"The dust is " +
      "thick on the floor, and thus " +
      "you do not have any difficulties in " +
      "noticing footprints travelling from the west wall " +
      "to the staircase marked in the dust. \n");
    add_item("presence","Hmm... it seems to be gone now. " +
      "It must have been your over-reactive imagination. \n");
    add_item("west wall","You see nothing special about " +
      "this wall. \n");
    add_item("darkness","Down the staircase is a darkness so thick " +
      "and eminates an aura of such evil that you doubt " +
      "you could make yourself go down there...\n");


    add_exit(FROOM + "cellar","down","@@construction");
    reset_flotsam_room();
}

string
long_descr()
{
    return "You find yourself in a small secret room " +
    "at the back of a deserted house. The room is very " +
    "bare, with no obvious exits except for a stairway " +
    "going down into the darkness. The hairs on the " +
    "back of your neck rise, as you feel a presence " +
    "linger here, a presence that is dark and sinister. " +
    "Dust lines the floor, and a lit lantern hangs " +
    "from a hook above the staircase. \n";
}

int
construction()
{
    write("You slowly walk down the staircase...\n");
    return 0;
}

init()
{
    ::init();
    ADA("search");
}

search(string str)
{
    if(str != "west wall")
	return 0;
    if(door)
	return 0;
    get_door();
    return 1;
}

get_door2()
{
    if(door)
	door->remove_object();

    if (dAlarm_id1)
    {
	remove_alarm(dAlarm_id1);
	dAlarm_id1 = set_alarm(20.0, 0.0, &remove_door());
    }
    else
    {
	dAlarm_id1 = set_alarm(20.0, 0.0, &remove_door());
    }

    door = clone_object(FOBJ + "secretdoorb.c");
    door->move(TO);
    door->set_key(K_FLOTSAM);
    tell_room(TO,"A secret door opens in the west wall! \n");
}

remove_door2()
{
    door->remove_object();

    if (dAlarm_id1)
    {
	remove_alarm(dAlarm_id1);
	dAlarm_id1 = 0;
    }
}

get_door()
{
    get_door2();
    call_other(FROOM + "street28.c","get_door2");
}

remove_door()
{
    remove_door2();
    call_other(FROOM + "street28.c","remove_door2");
    tell_room(TO, "The secret door slams shut and becomes "
      + "unnoticable again.\n");
}


