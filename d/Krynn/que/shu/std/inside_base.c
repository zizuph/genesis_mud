/*
 * The room base for the village of Que Shu (inside rooms)
 */

#include "/d/Krynn/common/defs.h"
#include CLOCKH
#include "../local.h"
#include <composite.h>
#include <filter_funs.h>
#include <files.h>
#include <language.h>

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_que_shu_room"
#define RESET  "reset_que_shu_room"

/*
 * Here we define some specific things that'll make it easier to
 * write rooms.
 */

int gPlace;
string gShort_desc, gLong_desc;

/*prototypes*/
public void add_tent_exit(string direction, string place);
public void add_tent();
public void add_carpet();
public void add_beds(int num);


public void
set_place(int i)
{
    gPlace = i;
    INSIDE;
}

public void
set_short_desc(string str)
{
    gShort_desc = str;
}

public void
set_long_desc(string str)
{
    gLong_desc = str;
}

public void
short_desc()
{
    string str;

    switch (gPlace)
    {
        case TENT:
            gShort_desc = "in a small round tent";
            add_tent();
            add_beds(random(3)+1);
	    add_carpet();
	    break;
        case TEMPLE:
	    gShort_desc = "in a temple made of stone";
            add_carpet();
	    break;
        case SHAMANHUT:
	    gShort_desc = "in a fair sized hut made of stone";
            add_carpet();
	    add_beds(1);
	    break;
	case HOUSE:
	    gShort_desc = "in a fair sized house made of stone";
            add_carpet();
            add_beds(4);      
	    break;
	case HALL:
	    gShort_desc = "in a fair sized house made of stone";
            add_carpet();
	    break;
	default:
	    break;
    }
}

public string
long_desc()
{
    string desc;

    desc = "You are " + gShort_desc + /* ". It is " + GET_TIME_STRING +*/ ". ";
    desc += check_call(gLong_desc) + "\n";
    return desc;
}

public void
add_tent_exit(string direction, string place)
{
    add_exit(place,"out",0,0,1);
    add_exit(place,direction);
}


public void
add_tent()
{
    add_item(({"tent","inside"}),
	     "This is a tent.\n");
    add_search(({"tent","inside"}),6,
	       ONE_OF(({JACKET,PANTS,KNIFE})),-1);
	       
}

public void
add_carpet()
{
    add_item(({"carpet","floor"}),
	     "The floor is covered by a carpet, occupying all the available " +
	     "space. The carpet looks rather dirty and used.\n");
    add_search(({"carpet","floor"}), 4, COINS_OBJECT, -random(2));
}

public void
add_beds(int num)
{
    if (num > 1)
    {      
	add_item(({"bed","beds"}),
		 "There are " + LANG_WNUM(num) + " beds in the tent, " +
		 "aligned along the walls.\n");
	add_search(({"bed","beds"}),6,
		   ONE_OF(({MSACK,KNIFE})),-1);
    }
    else if (num == 1)
    {
	add_item(({"bed"}),
		 "There is a bed in the tent, along the wall.\n");
	add_search(({"bed"}),3,
		   ONE_OF(({MSACK,KNIFE})),-1);
    }
    
}


/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);

    short_desc();

    set_short(gShort_desc);
    set_long("@@long_desc@@");
    reset();
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}
