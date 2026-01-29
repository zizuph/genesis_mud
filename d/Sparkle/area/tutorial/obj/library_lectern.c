/*
 *  /d/Sparkle/area/tutorial/obj/library_lectern.c
 *
 *  Library lectern holding the tutorial spell book.
 *
 *  Created August 2019, by Arman
 */

inherit "/std/object";
#include "/d/Sparkle/area/tutorial/defs.h"
#include <macros.h>
#include <cmdparse.h>

#define SPELLBOOK   "/d/Genesis/specials/examples/tutorial_grimoire"

object spellbook;

public void
create_object()
{
    set_name("lectern");
    add_name( ({ "_tutorial_item" }) );
    set_adj("wooden");
    add_adj("shallow");
    set_short("@@magic_tome_short@@");
    set_long("@@magic_tome_long@@");

    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_WEIGHT, 13200);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "The wooden lectern is too big to pick up.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    add_item( ({ "leather-bound grimoire", "grimoire" }),
        "@@exa_grimoire@@");
}

string
exa_grimoire()
{
    if (!present("_tutorial_magic_tome", this_player()))
        return "A closed leather-bound grimoire rests upon the wooden " +
            "lectern here. You feel an aura of magic about it! Perhaps " +
            "you should take it and see what mystical insights it might " +
            "impart to you?\n";
    else
        return capitalize(query_verb())+ " what?\n";
}

string
magic_tome_short()
{
    if (!present("_tutorial_magic_tome", this_player()))
        return "wooden lectern, upon which rests a closed " +
            "leather-bound grimoire";
    else
        return "wooden lectern";
}

string
magic_tome_long()
{
    if (!present("_tutorial_magic_tome", this_player()))
        return "A wooden lectern stands in the middle of the library, " +
            "upon which rests a closed leather-bound grimoire.\n";
    else
        return "A wooden lectern stands in the middle of the library. " +
            "A dust outline indicates a book once rested here.\n";
}

int 
take_grimoire(string str)
{
    string grimoire;

    if (!parse_command(str, ({ environment() }),  
        "[up] [the] [leather-bound] %w [from] [the] [wooden] [lectern]", 
        grimoire))
    {
	return 0;
    }   

    if(!present("_tutorial_magic_tome", this_player()))
    {
        if(grimoire != "grimoire")
        {
                 string verb = query_verb();
                 notify_fail(capitalize(verb)+ " what? The leather-bound " +
                     "grimoire?\n");
                 return 0;
         }
         string verb = query_verb();
         write("You gingerly " +verb+ " the leather-bound grimoire from " +
             "the lectern!\n\n");
         say(QCTNAME(this_player())+ " gingerly lifts the " +
             "leather-bound grimoire from the lectern!\n");

         setuid();
         seteuid(getuid());
         spellbook = clone_object(SPELLBOOK);
         spellbook->move(this_player(), 1);

         return 1;
    }
    else 
    {
        string verb = query_verb();
        notify_fail(capitalize(verb)+ " what??\n");
        return 0;
    }

    return 0;
}

int 
read_grimoire(string str)
{
    if ((str=="grimoire") || (str=="leather-bound grimoire") || 
        (str=="closed grimoire") || (str=="close leather-bound grimoire") ||
        (str=="grimoire") || (str=="leather grimoire")  ) 
    {
        if(!present("_tutorial_magic_tome", this_player()))
        {
             write("To read the leather-bound grimoire you should " +
                 "take it from the lectern!\n");
             return 1;
         }
         else 
         {
             string verb = query_verb();
             notify_fail(capitalize(verb)+ " what?\n");
             return 0;
         }
    }
    return 0;
}

void
init()
{
   ::init();
   add_action(take_grimoire, "take");
   add_action(take_grimoire, "get");
   add_action(take_grimoire, "pick");
   add_action(read_grimoire, "read");

}
