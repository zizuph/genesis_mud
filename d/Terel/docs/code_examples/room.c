/*

Room example for Terel
 by Udana, 03/06

*/


/*
 *This pragma forbids using functions with non-defined return values.
 * you should always write your code according to it.
 */
#pragma strict_types
/* Standard Terel definitions, this is most recent version*/
#include "/d/Terel/include/Terel.h"
/*
 * You'll probably want to include some more headers like
 * local settings for the project you're working at,
 * usually it's located in <project_dir>/include/defs.h or
 * <project_dir>/local.h
 */

/* That means you're inheriting from standard room for Terel */
inherit STDROOM;

/*
 *Global variables, and methods declarations should appear above
 *create_terel_room, and be properly commented.
 *This is a pointer to a npc we might have standing here.
 */
int gate_flag = 0;

/* NOT create_room(), notice no calls of ::create_room in it. */
public void create_terel_room()
{
	/* 
	 * A short descirption of that room, what players will see
	 * if they 'glance'. Not luck of '.' at the end.
	*/
	set_short("ordinary room in Terel");
	/*
	 * A long description, \n at the end means the line will be broken.
	*/
	set_long("A room in Terel I've been asked to write so new wizards "+
		"here could see how things work.\n");

	/*A time between messages added as tells will be displayed.*/
	set_tell_time(300 + random(100));	
	/* 
	 * A message added as a room tell will appear periodicaly to
	 * all players in that room, if the function start_room_tells was called.
	*/
	add_tell("Nothing really happends here.\n");
	
	/* Adding obvious exit */
	add_exit("another_room_file_name", "command", 1, 0, 0)
	
	
	/*
	 * A new and extremly cool mudlib feature, you don't have to watch to
	 * clone your npcs and object on every reset, mudlib does that for you.
	 * npc added this way will be cloned here every time reset occurs and
	 * he's absent.
	 */
	add_npc("npc_file_path_name");
	add_object("object_file_path_name");
	
	/*
	 *Calling that function inside create_terel_room is not obligatory
	 *but most of the things you'd like to happen when the room is
	 *reseted you'd also like to hapen when it's created.
	*/
	reset_terel_room();
	
	
}

/*
 * NOT reset_room, note that there is no call of ::reset_room() inside the
 * function's body.
 * Everything that you put here will happen each time the room is reseted.
 * this is a good place for reseting variables, etc,
 */
void reset_terel_room()
{
	/* Lets say gate is closed by default, and we want to close it on
	    every reset:
	*/
	gate_flag = 0;
}

/*
 * Masked from /std/room.c, this rutine is called every time
 * interactive player enters that room.
 */
public void init()
{
	/*
	 * Every time you overload that rutine you HAVE TO
	 * call old init in it's body.
	 */
	::init();
	/* Name says all */
	start_room_tells();
}