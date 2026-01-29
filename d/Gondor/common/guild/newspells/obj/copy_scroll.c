/*
 * /d/Gondor/common/guild/spells/obj/copy_scroll.c
 *
 * A scroll that can be copied into the ranger spellbook.
 *
 * Original version (in the different scrolls) by Elessar.
 *
 * This generic version by Olorin, December 1996
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 *
 * Modified scroll for use with the new spells system.
 * -Igneous Apr 2000.
 */
#pragma strict_types

inherit "/std/scroll.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../spells.h"

/*
 * Prototypes:
 */
public string  long_func();

/*
 * Global variables:
 */
static string  Spell_Name;
static int Spell_Code;

/*
 * Function name: set_spell_name
 * Description:   set the variable Spell_Name
 * Argument:      str - the name
 */
public void
set_spell_name(string str)
{
    Spell_Name = str;
}

/*
 * Function name: set_spell_code
 * Description:   set the variable Spell_Code
 * Argument:      code - the bitwise int spell code
 */
public void
set_spell_code(int code)
{
    Spell_Code = code;
}

/*
 * Function name: create_copy_scroll
 * Description:   creator, replace this function in the inheriting file.
 */
public void
create_copy_scroll()
{

    add_name("genericscroll");
    add_adj("generic");
    set_spell_name("Generic Spell");
    set_spell_code(0);
    set_file(RANGER_SPELL_TXT + "cleanse.txt");
}

/*
 * Function name: create_scroll
 * Description:   creator
 */
nomask void
create_scroll()
{
    set_name("scroll");
    set_short("old scroll");
    set_adj("old");
    set_long(long_func);

    create_copy_scroll();
}

public string
long_func()
{
    string  txt = "The yellowed paper of this scroll indicates that "
    + "it is quite old.";

    if (strlen(Spell_Name))
    {
	txt += " Below the title \"" + Spell_Name + "\" are some "
	+  "intelligible words, followed by some rather unusual "
	+  "letters of ancient elven origin.";
	if (objectp(present("ranger_spell_book",TP))) 
	    txt += " You feel quite sure that you can copy this scroll "
	    +  "into your spellbook.";
	else 
	    txt += " You have a feeling it is impossible for you to "
	    +  "use this scroll.";
    }
    else
	txt += " However, the letters on the scroll are so faded "
	+  "that you cannot read them anymore.";

    return BSN(txt);
}

public int
copy_scroll(string str)
{
    object  scroll, 
    book;
    string  dummy, 
    scr_name;

    if (!strlen(str))
    { 
	NFN("Copy what?"); 
	return 0; 
    }

    if (!parse_command(str, environment(),
	"%o [into] / [in] / [to] %o", scroll, book))
    {
	NFN("Copy what into what?");
	return 0;
    }
    if (scroll != this_object())
    {
	NFN("Copy which scroll?");
	return 0;
    }
    if (book != present("ranger_spell_book", TP))
    {
	write("But you don't have the spellbook!\n"); 
	return 1; 
    }

    if (TP->query_skill(SS_RANGER_SPELL_LIST) & Spell_Code) 
    {
	write("But you already have that spell in your spellbook!\n");
	return 1;
    }
    // Pupils can only copy heal, whistle and rest spells.
    if (!TP->query_company() && (Spell_Code >= SPELL_CLEANSE)
      && !TP->query_wiz_level())
    {
	write("This scroll is to advanced for you to learn.\n");
	return 1;
    }

    TP->set_skill(SS_RANGER_SPELL_LIST, 
      TP->query_skill(SS_RANGER_SPELL_LIST) | Spell_Code);
    book->setup_spells(TP, Spell_Code);
    setuid(); seteuid(getuid());
    log_file("spellbook", ctime(time())+" "+TP->query_cap_name() + " adds " +
      Spell_Name + " to "+ POSSESSIVE(TP) + " spellbook.\n");

    write("You carefully copy the spell onto some blank pages of your spellbook.\n"
      + "Just as you are finished, the scroll crumbles to dust between your fingers!\n");
    say(QCTNAME(TP)+" copies a spell into "+TP->query_possessive()+" little brown book.\n"+
      "Suddenly, the scroll "+TP->query_pronoun()+" was copying from crumbles to dust!\n",TP);
    remove_object();
    return 1;
}

public void
init()
{
    ::init();
    add_action(copy_scroll, "copy");
}
