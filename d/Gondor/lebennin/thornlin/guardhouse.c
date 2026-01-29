/*
 * thornlin/guardhouse
 * Original author uncertain, Gnadnar perhaps
 * Modified to add facilities (bank, po, shop, etc)
 * by Auberon, Dec. 30 2000
*/

/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above.
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "locals.h"

#ifndef MJOIN
#define MJOIN (MILITIA_DIR + "room/join.c")
#endif

#define THORNLIN_CLOSED	0

object *guard = allocate(2),
*officer = allocate(1);
void
add_npcs()
{
    int    ig = sizeof(guard),
    io = sizeof(officer),
    statnr;

    while (ig--)
    {
	if (!objectp(guard[ig]))
	{
	    guard[ig] = clone_object(THORN_DIR + "npc/militia");
	    guard[ig]->set_long("This is a militia man of Thornlin. He "+
	      "seems to be waiting for someone to need his "+ 
	      "help.\n");
	    guard[ig]->arm_me();
	    guard[ig]->set_random_move(10);
	    guard[ig]->MILITIA_3RD_PATH;
	    guard[ig]->move_living("from the void", TO);
	}
    }
    while (io--)
    {
	if (!objectp(officer[io]))
	{
	    officer[io]->set_name("officer");
	    officer[io] = clone_object(THORN_DIR + "npc/militia");
	    for(statnr=0; statnr < 6; statnr ++)  
		officer[io]->set_stat_extra(statnr, 40);
	    officer[io]->set_long(BS("He seems to be an officer or at least "+ 
		"a better fighter than the normal militia men. It "+
		"looks like he has desk duty right now.\n"));
	    officer[io]->set_officer();
	    officer[io]->arm_me();
	    officer[io]->move_living("from the void", TO);
	    officer[io]->refresh_living();
	}
    }
}


void
reset_room()
{
    set_alarm(1.0, 0.0, "add_npcs");
}

int
militia_only()
{
    if (THORNLIN_CLOSED)
    {
	if (!IS_MILITIA(this_player()) &&
	  !this_player()->query_wiz_level())
	{
	    write ("A young guard stops you from going any further, but " +
	      "suggests you come back at a later date when the militia " +
	      "starts recruiting.\n");
	    return 1;
	}
    }

    return 0;
}

void
create_room()
{
    set_short("a Guard house");
    set_long("This room is small, but not too small to accomodate "
      + "a medium sized desk, a chair behind the desk, and several chairs lined up "
      + "along the walls.  On the west wall hangs a weapon cabinet.\n");

    INSIDE;
    add_item("desk", "It is a wooden desk with some papers on it. "
      + "Besides the papers there are a feather, a pot of ink, and "
      + "a bottle on the desk.\n");
    add_item("chair","You see a wooden chair, it seems well used.\n");
    add_item("chairs","You see the chairs standing up against the wall.\n");
    add_item(({"weapon cabinet","cabinet"}),"It is a weapon cabinet used "+
      "to store weapons in it until times when they are needed.\n");
    add_item("weapons", "They are mostly short stabbing spears.\n");
    add_item("feather","It's a goose feather, often used to write with.\n");
    add_item(({"pot", "ink", "pot of ink"}), "It is a small ink-pot containing some ink.\n");
    add_item("bottle","The bottle is empty. It probably contained wine or booze.\n");
    add_item(({"paper", "papers", }), 
      "The papers on the desk seem to be the typical kind of paperwork "
      + "that somehow accumulates everywhere that soldiers are not "
      + "actually in combat. You quickly glance at them and then decide "
      + "that you are not interested in most of them, although the militia "
      + "recruitment poster looks a bit interesting.\n");
    add_item(({"poster"}), "The poster reads: Join the Lossarnach militia! "
      + "Few wolves, even fewer orcs!  Great training and facilities!\n");

    add_exit(THORN_DIR + "po", "west", 0, 0);
    add_exit(THORN_DIR + "bank", "east", 0, 0);
    add_exit(MJOIN, "north", &militia_only(), 
      1, 0);
    clone_object(THORN_DIR + "obj/guarddoora")->move(TO);
    reset_room();
}

void
tour_done(object ob)
{
    object  mil;

    if (!objectp(mil = present("officer", TO)) &&
      !objectp(mil = present("_thornlin_mili", TO)))
    {
	write("Strangely, there are none of the militia men present "
	  + "here. Go back to Carastur and report this when you "
	  + "return the tour note to him.\n"
	  + "Your task is done.\n");
	return;
    }
    mil->command("greet " + OB_NAME(ob));
    mil->command("say You are coming from Carastur, aren't you?");
    mil->command("emote takes the tour note.");
    mil->command("emote scribbles a short report on the tour note.");
    mil->command("emote gives the tour note back.");
    mil->command("say Ok, go back to Carastur and give him the tour note.");
    mil->command("say Your task is done.");
}

public void
enter_inv(object ob, object from)
{
    int tracker = 0;
    object  note;

    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(ob))
	return;

    if (this_player()->query_wiz_level())
        return;
    else
    {
        if (MJOIN->query_not_allowed(ob->query_real_name()) && !tracker)
        {
            tracker = 1;
            write("A scowling guard steps in front of you.\nThe scowling guard " +
              "says: You're not welcome here!\nThe scowling guard shoves you " +
              "out the door.\n");
            tell_room(this_object(), "A scowling guard steps in front of " + 
              QTNAME(ob) + "\nThe scowling guard says: You're not welcome " +
              "here!\nThe scowling guard shoves " + QTNAME(ob) + " out the " +
              "door.\n", ob);
            tell_room(THORN_DIR + "r2a", QCTNAME(ob) + " is shoved out of " +
              "the guardhouse by a scowling guard.\n");
            ob->move_living("M", THORN_DIR + "r2a", 1, 1);
            tracker = 0;
            return;
        }
    }

    if (!objectp(note = present("Pelargir_Tour_Note", ob)))
	return;

    if (note->query_tour_no() != 2)
	return;

    if (note->query_tour_done())
	return;

    note->set_tour_done();

    set_alarm(2.0, 0.0, &tour_done(ob));
}


