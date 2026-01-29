/*
 * /d/Gondor/common/obj/torchstand.c
 *
 * A standard torch stand.
 *
 * Copied and modified from
 * /d/Gondor/mordor/obj/torchstand.c
 * The torch stand in the tower at Cirith Ungol. (It also contains a torch)
 * by
 * /Mercade 12 October 1993
 *
 * Olorin, 28-may-1995
 * Revision history:
 *
 * 14-Mar-1998, Gnadnar: add no_desc so that rooms may fold torchstand
 *	desc into the room long; add query_torch_is_lit(); tell replacement
 *	message to room when torch is replaced in reset_container().
 */
inherit "/std/container";

#include <language.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

/*
#define TORCH_OBJECT (OBJ_DIR + "torch_tmp")
*/
#define TMP_NO_REPLACE_MSG  "_tmp_no_replace_msg"
#define IN_TEXT BSN("There already is a torch in the stand.")
#define GET_TEXT ("You cannot take the torch from the stand.\n")


/*
 * Prototype
 */
void    reset_container();

/*
 * Globals
 */
static string  torch_file = 0,	// the torch file that is cloned into the
				// stand. if = 0, no torch is cloned
               stand_desc,
               replace_msg = 0;	// if this is defined, a burned out torch 
				// will be replaced by a new one
				// this will work only for torches that 
				// autodestruct when burned out
				// like /d/Gondor/common/obj/torch_tmp, but
				// not for /std/torch
static int     lit = 0,		// torches are not lit
               remove_torch = 1,	// torches can be removed
               time = 600,	// burn time of torches
	       no_desc = 0;	// add torch to room extra descs

void    set_torch_file(string file)	{ torch_file = file;  }
string  query_torch_file()		{ return torch_file;  }
void    set_stand_desc(string desc)	{ stand_desc = desc;  }
string  query_stand_desc()		{ return stand_desc;  }
void    set_replace_msg(string msg)	{ replace_msg = msg;  }
string  query_replace_msg()		{ return replace_msg; }
void	set_no_desc(int i)		{ no_desc = i;        }

void
set_time(int t)
{
    time = t;
    if (time > 600)
        remove_torch = 0;
}

int     query_time() { return time; }
void    set_lit(int i) { lit = i; }
int     query_lit() { return lit; }

void
set_remove_torch(int i)
{
    remove_torch = i;
    if (time > 600)
        remove_torch = 0;
}

int     query_remove_torch() { return remove_torch; }

object
query_torch()
{
    return present("torch", TO);
}

int
query_torch_is_lit()
{
    object torch = present("torch", TO);
    return ( objectp(torch) && torch->query_lit() );
}


void
create_torchstand()
{
    set_torch_file(OBJ_DIR + "torch_tmp");
    set_stand_desc("iron torch stand");
}

/*
 * Called to create the torch stand.
 */
nomask void
create_container()
{
    set_name("stand");
    add_name(({"bracket", "torchstand"}));
    set_pname("stands");
    add_pname("brackets");
    set_adj(({"torch", "iron"}));
    set_long(BSN("The iron torch stand is mounted on the wall."));

    add_prop(OBJ_M_NO_GET,
        BSN("The iron torch stand is secured to the wall."));
    add_prop(OBJ_I_VALUE, 0);

    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 11000);
    add_prop(CONT_I_MAX_VOLUME, 11000);

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,  1);

    create_torchstand();

    set_no_show_composite(1);
}

int
get_torch(string str)
{
    if (str == "torch" && !present("torch",ENV(TO)))
    {
        write("Get torch from torchstand?\n");
        return 1;
    }
    return 0;
}

void
init()
{
    add_action("do_light",      "light");
    add_action("do_extinguish", "extinguish");
    add_action("get_torch", "get");
    add_action("get_torch", "take");
}

/*
 * Reset the torch stand from time to time.
 */
void
reset_container()
{
    object torch = present("torch", TO);

    if (!objectp(torch) && strlen(torch_file))
    {
        seteuid(getuid());
        torch = clone_object(torch_file);
        torch->set_time(time);
        if (lit)
            torch->light_me();
        if (torch->move(TO))
            torch->move(TO, 1);
        if (!remove_torch)
            torch->add_prop(OBJ_M_NO_GET, GET_TEXT);
        add_prop(CONT_M_NO_INS, IN_TEXT);
        if (strlen(replace_msg))
        {
            if (!TO->query_prop(TMP_NO_REPLACE_MSG))
                tell_room(ENV(TO), check_call(replace_msg));
            else
                TO->remove_prop(TMP_NO_REPLACE_MSG);
        }
        set_alarm(2.0, 0.0, "update_desc");
    }
}

string
query_stand_short()
{
    object  torch = present("torch", TO);
    string  desc = stand_desc;

    if (objectp(torch))
        desc += " containing " + LANG_ADDART(torch->short());

    return CAP(LANG_ADDART(desc) + ".\n");
}

/*
 * The short description dependant on whether a torch is in it.
 */
string
short()
{
    return stand_desc;
}

/*
 * If the torch is removed from the stand, it is possible to add a new torch
 * to the stand.
 */
void
leave_inv(object ob, object to)
{
    int     std_torch;
    int     is_torch = ob->id("torch");

    ::leave_inv(ob, to);
    remove_prop(CONT_M_NO_INS);
    set_alarm(0.0, 0.0, "update_desc");

    if (is_torch && !objectp(to))
    {
        if (strlen(replace_msg))
        {
            if (std_torch)
                TO->add_prop(TMP_NO_REPLACE_MSG, 1);
#if 0
		/* unnecessary, i believe, now that reset_container does msg */
            tell_room(ENV(TO), check_call(replace_msg));
#endif
            set_alarm(0.0, 0.0, "reset_container");
        }
        else
            ENV(TO)->hook_torch_burned_out(TO);
    }
    else if (is_torch && objectp(to))
    {
        /* A living stole the torch.
         * We'll let it be replaced after a while. */
        set_alarm(itof(random(1800) + 1800), 0.0, "reset_container");
    }
}

/*
 * You can only put a torch in the stand.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!(ob->id("torch")))
    {
        set_alarm(2.0, 0.0, "drop_non_torch", ob);
        return;
    }
    if (objectp(from))
    {
        if (strlen(replace_msg) && MASTER_OB(ob) != (OBJ_DIR + "torch_tmp"))
        {
            ob->remove_object();
        }
    }

    set_alarm(0.0, 0.0, "update_desc");
    add_prop(CONT_M_NO_INS, IN_TEXT);
}

/*
 * If you put another object than a torch in the stand, it will fall out.
 */
void
drop_non_torch(object ob)
{
    tell_room(ENV(TO), BSN("The "+stand_desc+" is only meant for torches and " +
        "therefore the " + check_call(ob->short()) + " falls onto the " +
        "ground."));
    ob->move(ENV(TO));
}

/*
 * If you try to light the torch in the stand, it will probably happen.
 * All it does is call the light function in the torch itself.
 */
int
do_light(string str)
{
    object torch = present("torch", TO);
    int result;

    if (objectp(torch))
    {
        torch->move(ENV(TO));
        result = torch->do_light(str);
        torch->move(TO);
// I need a 2 sec delay here since /std/torch uses a 1 sec delay
        set_alarm(2.0, 0.0, "update_desc");

        return result;
    }

    return 0;
}

/*
 * If you try to extinguish the torch in the stand, you will probably succeed.
 * All this function does is call the extinguish function in the torch itself.
 */
int
do_extinguish(string str)
{
    object torch = present("torch", TO);
    int result;

    if (objectp(torch))
    {
        torch->move(ENV(TO));
        result = torch->do_extinguish(str);
        torch->move(TO);
// I need a 2 sec delay here since /std/torch uses a 1 sec delay
        set_alarm(2.0, 0.0, "update_desc");

        return result;
    }

    return 0;
}

/*
 * Function name: enter_env
 * Description:   The torch stand enters a room
 * Arguments:     dest - The destination room,
 *                old - Where it came from
 */
void
enter_env(object dest, object old)
{
    if (strlen(torch_file))
    {
        reset_container();
        enable_reset();
    }

    set_alarm(2.0, 0.0, "update_desc", dest);
}

varargs void
update_desc(object ob)
{
    if (!objectp(ob))
        ob = ENV(TO);
    if (!objectp(ob))
        return;
    if ( !no_desc )
    	ob->change_my_desc(query_stand_short(), TO);
    ob->update_light(1);
}
