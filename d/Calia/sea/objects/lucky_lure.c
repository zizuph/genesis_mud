/*  file:  /d/Calia/sea/objects/lucky_lure.c
 *  Quest object for lucky lure quest
 *  coder:  Tigerlily
 *  date:  2002-01-25
 *  For other info on the quest see /d/Calia/private/QUESTS/lucky_lure_quest.doc
 *
 */



inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <defs.h>
#include SEA_QUESTS

int clean_lure(string str);
int cleaned = 0;

void
create_object()
{
    set_name("metal");
    add_name("piece of metal");
    add_name("piece");
    set_adj(({"dirty"}));
    set_short("@@short_desc");
    set_long("@@long_desc");

    add_prop(OBJ_I_WEIGHT, 200);

    add_prop(OBJ_M_NO_BUY, "No one would want to buy"+
      " this piece of junk!\n");
}

void
init()
{
    ::init();
    add_action(&clean_lure(), "clean");
    add_action(&clean_lure(), "shine");
    add_action(&clean_lure(), "polish");
    add_action(&clean_lure(), "wash");
}

int
clean_lure(string str)
{
    object tp = this_player();

    if (!str)
    {
	notify_fail("Clean what?\n");
	return 0;
    }

    if (cleaned)
    {
	notify_fail("It's already about as clean"+
	  " as you can get it.\n");
	return 0;
    }

    if (!objectp(present(this_object(), tp)))
    {
	notify_fail("You have to hold the object "+
	  "in order to clean it.\n");
	return 0;
    }

    if (!CAN_SEE_IN_ROOM(tp))
    {
	notify_fail("You can't see well enough"+
	  " to clean anything here!\n");
	return 0;
    }


    if ((environment(tp)->query_prop(ROOM_I_TYPE) != 
	ROOM_IN_WATER) && (environment(tp)->query_prop(ROOM_I_TYPE) !=
	ROOM_UNDER_WATER))
    {
	notify_fail("It is too dirty to clean with "+
	  "spit and your bare hands. You need water.\n");
	return 0;
    }

    if (this_object()->id(str))
    {
	cleaned = 1;
	write("You clean the dirty piece of metal"+
	  " in the water, rubbing it"+
	  " with your hands. A blue metallic frog"+
	  " lure appears from under the grime!\n");
	say(QCTNAME(tp) + " cleans something with "+
	  tp->query_possessive() + " hands"+
	  " in the water.\n");
	this_object()->add_name(LUCKY_LURE);
	remove_adj("dirty");
	add_adj(({"shiny", "blue", "metallic"}));
	add_name(({"frog", "lure"}));
	return 1;
    }
    notify_fail("Clean what?\n");
    return 0;
}

string
short_desc()
{
    if (this_object()->id(LUCKY_LURE))
	return "shiny blue metallic fishing lure";
    else
	return "dirty piece of metal";
}

string
long_desc()
{
    if (this_object()->id(LUCKY_LURE))
    {
	return "This is a shiny metallic object that fits easily"+
	" into the palm of your hand. It is fashioned from"+
	" tin and painted to look like a blue frog."+
	" There is a large hook embedded in the metal."+
	" The head contains a swivel gizmo where"+
	" it would attach to the fishing line, allowing it to spin"+
	" around in the water to attract fish.\n";
    }
    else
	return "Under the bird poop you can discern"+
	" that this is a piece of metal about the size of"+
	" your hand.\n";
}


int
query_recover()
{
    return 0;
}
