/**
* Coded by Louie 2004
* 
* A control room that players never go to.  It is used to hold some
* variables and do some stuff that affects the whole area.
* It's not used that much.
*
*/
#pragma strict_types

#include "../local.h"

inherit GNOME_IR;


int destroyed;
int door1;
int door2;
int committee_approving;
int approving_id;

/* prototypes */
public int query_state_destroyed();
public void create_explosion();
public void set_state_repaired();
public void set_state_destroyed();
public int query_door1();
public void close_door1();
public void open_door1();
public int query_door2();
public void close_door2();
public void open_door2();
public void query_committee_approving();
public void set_committee_approving(int i);


/*
* Create
*/
void
create_gnome_room()
{

    destroyed = 0;
    door1 = 0;
    door2 = 1;
    committee_approving = 0;
    approving_id = 0;
    
    SHORT("Wizard control room");
    LONG("This room is a controller room for the gnome " +
      "explosives center.  It basically just keeps track "+
      "of whether or not a bomb has gone off.  It may " +
      "provide additional functions in the future.\n");

}

public int
query_committee_approving()
{
	return committee_approving;
}

/*
* This is for the Approval Committee debate room (expl4) to track
* if the committee is in session.
*/
public void
set_committee_approving(int i)
{
	committee_approving = i;
	
	/*automatically reset after a few minutes*/
	if (committee_approving > 0)
	{
		if (approving_id)
		{
			remove_alarm(approving_id);
		}
		
		approving_id = set_alarm(600.0, 0.0, &set_committee_approving(0));
	}
}

/*
* Has a bomb gone off?
* This just affects a one line description in each room, no biggie.
* Some day it could be used for cooler stuff.
*/		
public int
query_state_destroyed()
{
    return destroyed;
}


/* 
* Call this when an explosion goes off in the center.
*/
public void
create_explosion()
{

    destroyed = 1;
    /** Send tell messages? **/
    set_alarm(45.0, 0.0, "set_state_repaired");

}

void
set_state_repaired()
{
    destroyed = 0;
}

void
set_state_destroyed()
{

    destroyed = 1;
}
public int 
query_door1()
{
	return door1;
}

public int
query_door2()
{
	return door2;
}

/*
* This is for the gnome vault doors connected to expl1, expl6, and 
* expl7.  When you push a button the open one closes and the closed
* one opens - it's a safety measure so that the exploding area is
* always sealed off from the rest of the gnome area.
*/
public void 
close_door1() 
{
	/*If door1 closes, door2 opens*/
	
	tell_room(GNOME_ROOM+"expl1",
		"With a sound of scraping metal the gigantic door " +
		"to the west rolls shut.\n");
	tell_room(GNOME_ROOM+"expl6",
		"With a sound of scraping metal the gigantic door "+
		"to the east rolls shut.\n");		
	set_alarm(2.0, 0.0, "open_door2");		
		
	door1 = 0;
	
}

/*
* This is for the gnome vault doors connected to expl1, expl6, and 
* expl7.  When you push a button the open one closes and the closed
* one opens - it's a safety measure so that the exploding area is
* always sealed off from the rest of the gnome area.
*/
public void 
close_door2()
{
	/*if door2 closes, door1 opens*/
	tell_room(GNOME_ROOM+"expl7",
		"With a sound of scraping metal the gigantic door " +
		"to the east rolls shut.\n");
	tell_room(GNOME_ROOM+"expl6",
		"With a sound of scraping metal the gigantic door "+
		"to the west rolls shut.\n");		
	set_alarm(2.0, 0.0, "open_door1");			
		
	door2 = 0;
}

/*
* This is for the gnome vault doors connected to expl1, expl6, and 
* expl7.  When you push a button the open one closes and the closed
* one opens - it's a safety measure so that the exploding area is
* always sealed off from the rest of the gnome area.
*/
public void
open_door1()
{
	/*Really you shouldn't call this directly, call close_door2() */
	/*instead */
	tell_room(GNOME_ROOM+"expl1",
		"With a loud hiss of steam the gigantic door " +
		"to the west rolls open, exposing the passage west.\n");
	tell_room(GNOME_ROOM+"expl6",
		"With a loud hiss of steam, the gigantic door "+
		"to the east rolls open, exposing the passage east.\n");
	
	door1 = 1;
}


/*
* This is for the gnome vault doors connected to expl1, expl6, and 
* expl7.  When you push a button the open one closes and the closed
* one opens - it's a safety measure so that the exploding area is
* always sealed off from the rest of the gnome area.
*/
public void 
open_door2()
{
	/*Call close_door1() instead of this*/
	tell_room(GNOME_ROOM+"expl7",
		"With a loud hiss of steam the gigantic door " +
		"to the east rolls open.\n");
	tell_room(GNOME_ROOM+"expl6",
		"With a loud hiss of steam, the gigantic door "+
		"to the west rolls open.\n");
		
	door2 = 1;
}
		
