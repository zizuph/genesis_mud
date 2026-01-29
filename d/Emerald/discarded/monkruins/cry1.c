/*
 * CRY1.c
 * Crypt in the Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

int open_door(string str);
int close_door(string str);

object outside_room;

void
create_room()
{
    if (!LOAD_ERR(MONKRUIN_DIR + "mr8"))
	outside_room = find_object(MONKRUIN_DIR + "mr8");

    set_short("Inside a dark, damp tomb");
    set_long("   You are standing in a wide, open foyer at one end of "+
	     "a long, stone crypt. Thick cobwebs hang down from the ceiling "+
	     "and all of the corners, draping the dimly lit stone rooms "+
	     "with a flowing, white blanket. Several small lamps and a "+
	     "few candles resting in black iron rings provide a small "+
	     "amount of flickering orange light. A soft, cool breeze blows "+
	     "through the crypt from some unseen source, causing the "+
	     "cobwebs to flutter slightly and scattering dust and ash. You "+
	     "can see rows upon rows of coffins just to the east. Further "+
	     "east the coffins give way to free-standing sarcophogi and "+
	     "huge, metal sculptures hanging by chains from the ceiling.\n"+
	     "There is an enormous, black iron door here.\n\n");
    
    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({"cobwebs", "webs", "spider webs"}),
	     "The cobwebs hang down from the ceiling and all of the corners "+
	     "of the massive, stone crypt. A soft, chill wind blows through "+
	     "the crypt, causing the cobwebs to flutter slightly.\n");

    add_item( ({"candles", "lamps", "rings", "iron rings", "torches",
		"light", "orange light","candle", "lamp"}),
	     "The candles and lamps are arranged neatly to cast a "+
	     "dim orange glow into the darker corners of the crypt. The "+
	     "light is barely sufficient to allow you to see in here, "+
	     "and casts eerie, flickering shadows against the stone "+
	     "walls and coffins.\n");

    add_item( ({"dust", "ash"}),
	     "Dust and ash have gathered on the surfaces of the coffins, "+
	     "a few dusty stones and the coffins.\n");

    add_item( ({"coffins", "coffin", "sarcophagi", "sarcophagus",
		"sarcophaguses"}),
	     "The coffins are all arranged neatly in the middle of the "+
	     "area to the east. Just beyond the stone coffins you can "+
	     "see the faint outlines of a few sarcophagi.\n");

    add_item( ({"sculptures", "metal sculptures", "huge metal sculptures"}),
	     "You try and discern the shape of the sculptures from here, "+
	     "but the poor, flickering light isn't bright enough to "+
	     "allow you a clear view. In addition, the flicker of the "+
	     "lamps keeps casting shadows against the ceiling which make it "+
	     "hard to picture their true shape.\n");

    add_item( ({"door", "black iron doors", "iron door", "black door"}),
	     "The huge, black iron door has begun to take on a greenish "+
	     "tinge from centuries of resting unkept in all of the "+
	     "surrounding moisture. It looks like an incredibly thick, "+
	     "sturdy door.\n"+
	     "The door is @@open_or_closed@@.\n");

    add_exit(MONKRUIN_DIR + "mr8", "out", "@@go_out@@");
    add_exit(MONKRUIN_DIR + "cry2", "east", 0);
}

init()
{
    ::init();
    add_action(open_door, "open");
    add_action(close_door, "close");
}

int
open_door(string str)
{
    if (!str) return 0;

    if ( (str!="door") && (str!="iron door") )
    {
	notify_fail("Open what?\n");
	return 0;
    }

    if (outside_room->query_door_status()==1)
    {
	notify_fail("The door is already open.\n");
	return 0;
    }

    write("You push and shove and manage to make the door squeal open on "+
	  "its rusted hinges.\n");
    say(QCTNAME(TP)+" pushes and shoves and manages to make the door "+
	"squeal open on its rusted hinges.\n");
    
    outside_room->do_open_door();
    return 1;
}

int
close_door(string str)
{
    if (!str) return 0;

    if ( (str!="door") && (str!="iron door") )
    {
	notify_fail("Close what?\n");
	return 0;
    }

    if (!outside_room->query_door_status())
    {
	notify_fail("The door is already closed.\n");
	return 0;
    }

    write("You pull and heave and manage to close the door tight.\n");
    say(QCTNAME(TP)+" pulls and heaves and manages to close the door tight.\n");

    outside_room->do_close_door();
    return 1;
}

int
go_out()
{
    if (outside_room->query_door_status()==1) {
	write("You step out of the tomb, suddenly feeling warmer. You feel "+
	      "a comforting sense of relief wash over you ... \n\n");
	return 0;
    }
    else {
	write("The door is shut. You can't walk through it!\n");
	return 1;
    }
}

string
open_or_closed()
{
  if (outside_room->query_door_status()==1)
      return "open";
  else
      return "closed";
}

    
