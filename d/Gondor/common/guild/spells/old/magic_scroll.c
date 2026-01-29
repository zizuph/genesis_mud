/*
 * /d/Gondor/common/guild/spells/obj/magic_scroll.c      
 *
 * A standard ranger scroll that can load a spell into a player.
 * Is this scroll used in the game at present?
 *
 * set_file(string file) - Will connect a file to the read command
 * set_spell(string file)- Will connect a file defining the spell
 * set_autoload()        - Will make this object autoload
 *
 * Original version by Elessar (?)
 *
 * This version by Olorin, December 1996
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 *	27 May 1998, Gnadnar:	remove the code to "study" the scroll,
 *				since the spell files do NOT load.
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/spells/obj/copy_scroll.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

/*
 * Prototypes:
 */

/*
 * Global variables:
 */
static string  Spell_File;


/*
 * Function name: set_spell
 * Description:   Set the file to clone the spell from when the player
 *                studies the scroll.
 */
public void
set_spell(string file)
{
    Spell_File = file;
}

/*
 * Function name: query_spell
 * Description:   Query what file defines the spell
 */
public string query_spell() { return Spell_File; }

/*
 * Function name: init_arg
 * Description:   Set the parameters of the scroll when auto-loading
 */
public void
init_arg(string arg)
{
    string tmp;

    if (!strlen(arg))
	return;

    sscanf(arg, "%s##%s##%s", scroll_file, Spell_File, tmp);

    if (tmp == "0")
	add_prop(OBJ_M_NO_DROP, 0);
    else if (tmp == "1")
	add_prop(OBJ_M_NO_DROP, 1);
    else
	add_prop(OBJ_M_NO_DROP, tmp);

    auto_load = 1;
}

/*
 * Function name: query_auto_load
 * Description:   Autoload this object.
 */
public string
query_auto_load()
{
    if (auto_load)
        return MASTER + ":" + scroll_file + "##" +
		Spell_File + "##" + query_prop(OBJ_M_NO_DROP);
}

private void
dest_scroll()
{
    object  room = this_object();

    while (!(room = environment(room))->query_prop(ROOM_I_IS))
        ;

    tell_room(room, "The scroll is suddenly consumed by fire!\n");
    this_object()->remove_object();
}

public string
long_func()
{
    string  txt = "The yellowed paper of this scroll indicates that "
                + "it is quite old.";
    int     flg = 0;

    if (strlen(Spell_Name))
    {
        txt += " Below the title \"" + Spell_Name + "\" are some "
	    +  "intelligible words, followed by some rather unusual "
	    +  "letters of ancient elven origin.";
	if (objectp(present("ranger_spell_book", TP))) 
	{
	    flg++;
            txt += " You feel quite sure that you can copy this scroll "
	        +  "into your spellbook.";
	}
	if (strlen(Spell_File))
	{
	    flg++;
            txt += " What a pity you don't have a spellbook into which "
	        +  "you could copy the scroll.";
	}
	if (!flg)
            txt += " You have a feeling it is impossible for you to "
	        +  "use this scroll.";
    }
    else
        txt += " However, the letters on the scroll are so faded "
	    +  "that you cannot read them anymore.";

    return BSN(txt);
}

