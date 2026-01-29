/*
 * /d/Ansalon/guild/society/room/faerie_temp.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Holdover spot for faerie messengers.
 * Gwyneth, Dec 2000
 */
inherit "/std/room";

public void
create_room()
{
	set_short("faerie resting place");
	set_long("This is a resting place for faeries.\n");
}
