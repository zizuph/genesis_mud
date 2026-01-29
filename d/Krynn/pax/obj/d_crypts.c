/* A hole, the entrance to Sla-Mori
 *
 * 950409 by Rastlin
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include "../local.h"

inherit STDDOOR;
string gDirection;

create_door()
{
    ::create_door();

    set_door_name(({"door", "stone door"}));
    set_door_desc(BS("It is a large stone door, held in place by huge " +
	"iron hings, spiked directly into the rock wall. Carved on the " +
	"door is the royal crest. Behind this door rests someone from " +
	"Kith-Kanan's elite guard. They are pledged to continue their " +
	"duties, even in death, and guard the king - so the legends speak. " +
	"Written under the royal crest is 'Sothi Nuinqua Tsalarioth - " +
	"Faithful beyond Death'. The door has an iron handle, but " +
	"apparently no lock.", 70));

    set_open_desc("");
    set_closed_desc("");

    set_open_mess(({"@@standard_open_mess1", 
		"The stone door silently opens.\n"}));

    set_open(0);
}

public void
set_direction(string str)
{
    gDirection = str;
    set_door_name(({ str + " stone door", str + " door", "door", "stone door"}));
}

int
open_door(string arg)
{
    if (!this_door(arg))
        return 0;
  
    if (!other_door)
        load_other_door();

    if (!open_status)
    {
        if (lock_status)
            write(check_call(fail_open[1]));
        else if (this_player()->query_stat(SS_STR) < open_str)
            write("You lack the strength needed.\n");
        else
        {
            write("You open the " + short() + ".\n");
            say(QCTNAME(this_player()) + " " + check_call(open_mess[0]),
            this_player());
            do_open_door(0);
            other_door->do_open_door(1);

	    set_alarm(1.0, 0.0, "open_other_doors");
        }
    }
    else
        write(check_call(fail_open[0]));
 
    return 1;
}

/*
 * Function name: close_door
 * Description:   Close the door.
 * Arguments:  arg - arguments given
 */
int
close_door(string arg)
{
    if (!this_door(arg))
        return 0;
 
    if (!other_door)
        load_other_door();
 
    if (open_status)
	write("You try to close the door, but it wont move a bit.\n");
    else
        write(check_call(fail_close));
 
    return 1;
}

public void
open_other_doors()
{
    (PSLA + "tomb01")->open_other_doors();
    query_other_room()->start_zombie_alarm();
}

public void
crypt_open_door()
{
    if (!other_door)
	load_other_door();

    do_open_door(0);
    other_door->do_open_door(1);

    query_other_room()->start_zombie_alarm();
}

public void
crypt_close_door()
{
    if (!other_door)
      load_other_door();
    
    do_close_door(0);
    other_door->do_close_door(1);
}
