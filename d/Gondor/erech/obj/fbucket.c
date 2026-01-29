inherit "/std/object";
#include "/d/Gondor/defs.h"
#include "../erech.h"

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
string short_desc();
string long_desc();
int    pour(string arg);
int    empty(string arg);
int    fill(string arg);

/* Global variables */
int    filled;
string content;

create_object() 
{
    set_short(&short_desc());
    set_long(&long_desc());
    set_name("bucket");
    add_name("Erech_farm_bucket");
    add_prop(OBJ_I_WEIGHT,57);
    add_prop(OBJ_I_VOLUME,25);
    add_prop(OBJ_I_VALUE,35);
    add_prop(ERECH_QUEST_ITEM,1);

    filled = 0;

}

string
short_desc()
{
    if (filled == 0)
        return "metal bucket";
    else if (filled == 1)
        return "metal bucket with little "+content;
    else if (filled == 2)
        return "metal bucket with some "+content;
    else if (filled == 3)
        return "metal bucket filled with "+content;
}

string
long_desc()
{
    if (filled == 0)
        return "A metal bucket. You can probably be able to fill it " +
	    "with something.\n";
    else if (filled == 1)
        return "A metal bucket. There are some "+content+" in it.\n";
    else if (filled == 2)
        return "A metal bucket. It is about half full with " +
	    content + ".\n";
    else if (filled == 3)
        return "A metal bucket. It is filled with " + content + ".\n"; 
}

void
init()
{
    ::init();
    add_action(pour, "pour");
    add_action(empty, "empty");
    add_action(fill, "fill");
}

int
pour(string arg)
{
    object plate;
    object worker;

    worker = this_player();
    plate = present("Erech_farm_plate", worker);

    if (arg == content+" on plate")
    {
        if (!plate)
	{
	    write("On what plate?\n");
	    return 1;
	}
	if (plate->query_filler() == 0)
	{
	    if (filled >= 1)
	    {
		write("You pour some " + content + " on the plate.\n");
		say(QCTNAME(worker) + " pours something on " +
		    worker->query_possessive() + " plate.\n");
		filled = filled - 1;
		plate->set_filled(content);
		if (filled == 0)
		  content = "";
		return 1;
	    }
	    else
	    {
	        write("The bucket is empty, you need to fill it first.\n");
		return 1;
	    }
	}
	if (plate->query_filled() == 1)
	{
	    write("The plate is already filled with " + plate->query_content()
		  + ".\n");
	    return 1;
	}
    }
    return 0;
}

int
set_filled(string arg)
{
    if (filled == 3)
    {
      //        write("The bucket is full of " + content + ".\n");
	return filled;
    }
    if (filled > 0)
    {
	if (arg == content)
	{
	    filled = filled + 1;
	    //	    write("You fill some more " + content + " into the bucket.\n");
	    return filled;
	}
	else
	{
	  write("Do you want to mix "+arg+" with "+content+"?\n");
	  return filled;
	}
    }
    //    write("You fill some " + arg + " into the bucket.\n");
    filled = 1;
    content = arg;
    return filled;
}

int query_filled() { return filled; }
string query_content() { return content; }

int
empty(string arg)
{
    object pool;

    if (arg != "bucket")
        return 0;
    else if (filled == 0)
    {
	notify_fail("The bucket is empty.\n");
	return 0;
    }
    write("You pour out all the " + content + " onto the ground.\n");
    say(QCTNAME(this_player()) + " pours out some " + content + " from " +
	this_player()->query_possessive() + " bucket.\n");
    pool = clone_object(E_OBJ + "pool");
    pool->set_content(content);
    pool->set_size(filled);
    pool->move(environment(environment(this_object())));
    filled = 0;
    content = "";
    return 1;
}

int
fill(string arg)
{
    object plate;
    object worker;

    worker = this_player();
    plate = present("Erech_farm_plate", worker);

    if (arg == "plate with "+content)
    {
        if (!plate)
        {
	    write("On what plate?\n");
	    return 1;
        }
	if (plate->query_filler() == 0)
        {
	    if (filled >= 1)
            {
	        write("You pour some " + content + " on the plate.\n");
		say(QCTNAME(worker) + " pours something on " +
		    worker->query_possessive() + " plate.\n");
		filled = filled - 1;
		plate->set_filled(content);
		if (filled == 0)
		    content = "";
		return 1;
            }
            else
	    {
	        write("The bucket is empty, you need to fill it first.\n");
                return 1;
	    }
        }
	if (plate->query_filled() == 1)
	{
	    write("The plate is already filled with " + plate->query_content()
		+ ".\n");
	    return 1;
        }
    }
    return 0;
}
