/*
 * /d/Gondor/common/void.c
 *
 * An empty room to make unwanted npcs disappear before they are removed.
 *
 * Copyright (c) 1996 by Christian Markus
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

public void
create_gondor()
{
    set_long("The Void.\n" +
	     "There is absolutely nothing here. That is why it is " +
	     "called \"The Void\".\n");
    set_short("the void");
}
