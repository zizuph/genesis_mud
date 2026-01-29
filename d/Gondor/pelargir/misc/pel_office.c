inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define	SAVE_FILE		(PELAR_DIR + "misc/quest_killers")
#define TMP_ASKED_FOR_TOUR      "_tmp_asked_for_tour"

static object  carastur;
string	*Killers = ({});	/* killed carastur or londhir */

public void	add_killer(mixed k, string which);
public int	query_killer(mixed k);
public void	remove_killer(mixed k);
public int	test_blocked();

void
reset_room()
{
    if (!objectp(carastur))
    {
        carastur = clone_object(PELAR_DIR + "npc/carastur");
        carastur->arm_me();
        carastur->move_living("down", TO);
    }
}

void
create_room()
{
    set_short("the Council Office in Pelargir");
    set_long(BSN("This is the office where the Lord Councillor of "
      + "Pelargir receives visitors and citizens seeking an audience "
      + "with him. The office is furnished in a surprisingly sparse "
      + "way, there is just a high desk in the center of the room. "
      + "Behind the desk is curtained doorway. On the west wall there "
      + "is the only decoration of the room, a large banner of Pelargir."));

    add_item(({"desk", "high desk", "furniture", }), BSN(
        "The only piece of furniture here is a high desk in the center "
      + "of the room. The top of the desk is slightly tilted so one "
      + "can comfortably write on the desk while standing behind it."));

    add_item(({"curtain", "doorway", "door", }), BSN(
        "A thick black curtain is blocking the doorway leading north, "
      + "probably leading to more offices. But since the Lord "
      + "Councillor receives all visitors here, you are not allowed "
      + "to pass."));

    add_item(({"banner", "west wall", "large banner", }), BSN(
        "On the west wall, there is a large banner of Pelargir: Three "
      + "golden ships in a blue field, surmounted by a silver crown."));
    
    add_exit("/d/Gondor/workroom", "north", "@@check_wizard@@", 0, 2);
    add_exit(PELAR_DIR + "misc/cityhall", "south", test_blocked, 0);

    add_prop(ROOM_I_INSIDE,1);

    FIX_EUID
    restore_object(SAVE_FILE);

    reset_room();
}

int
check_wizard()
{
    if (!TP->query_wiz_level())
    {
        write(BSN("As you try to pass through the doorway, you are stopped "
          + "by a guard on duty in the corridor behind the curtain."));
        return 1;
    }
    write("Welcome, wizard!\n");
    return 0;
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!objectp(ob) || !living(ob))
        return;

    ob->remove_prop(TMP_ASKED_FOR_TOUR);
}



/*
 * Function name:	add_killer
 * Description	:	remember who killed carastur or londhir
 * Arguments	:	mixed k -- killer name or object
 *			string which -- carastur or londhir
 */
public void
add_killer(mixed k, string which)
{
    string	name;
    if (objectp(k))
    {
	name = k->query_name();
    }
    else if (stringp(k) &&
	     strlen(k))
    {
	name = CAP(k);
    }
    if (strlen(name))
    {
	Killers += ({ name });
    }
    FIX_EUID
    save_object(SAVE_FILE);
} /* add_killer */


/*
 * Function name:	query_killer
 * Description	:	did this person kill carastur or londhir?
 * Arguments	:	mixed k -- killer name or object
 * Returns	:	int -- 1 if killer, 0 if not
 */
public int
query_killer(mixed k)
{
    int	i = -1;

    if (objectp(k))
    {
	i = member_array(k->query_name(), Killers);
    }
    else if (stringp(k) &&
	     strlen(k))
    {
	i = member_array(CAP(k), Killers);
    }
    return (i >= 0);
} /* query_killer */


/*
 * Function name:	remove_killer
 * Description	:	clear someone from killer list
 * Arguments	:	mixed k -- killer name or object
 */
public void
remove_killer(mixed k)
{
    if (objectp(k))
    {
	Killers -= ({ k->query_name() });
    }
    else if (stringp(k) &&
	     strlen(k))
    {
	Killers -= ({ CAP(k) });
    }
    FIX_EUID
    save_object(SAVE_FILE);
} /* remove_killer */



/*
 * Function name:	test_blocked
 * Description	:	block exit if player is fighting carastur or
 *			guards
 */
public int
test_blocked()
{
    object attacker = TP->query_attack();

    if (objectp(attacker) &&
	attacker->id("_Pelargir_soldier"))
    {
        TP->catch_msg(QCTNAME(attacker) + " blocks your way out!\n");
        return 1;
    }
    return 0;
} /* test_blocked */
