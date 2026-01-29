/* Path2 coded by Teth
 * April 2, 1996
 * Last updated Oct 26 1996
 */

#include "local.h"
#include <macros.h>

inherit ROADOUT;
inherit HERBSEARCHNEW

#define SHELL   KROBJECT + "thrush_eggshell"

int shell_found;


string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

void
reset_darkenwd_room()
{
    set_searched(random(2));
    shell_found = 0;
}

void
create_darkenwd_room()
{
    set_place(PATH);

    set_long_desc("This narrow path runs between the shores of Crystalmir " +
                  "Lake and the road between Solace and Haven. Due to the "+
                  "undergrowth here, movement is quite tiring. Forest "+
                  "surrounds you on all sides now. The path extends both "+
                  "to the north and to the southwest. A small clump of "+
                  "grasses and sticks seems to have fallen or been placed on "+
                  "the path.");
    AI(({"path","narrow path","trail","game trail"}),"The path is an old "+
        "game trail. However, it is now covered with tangleshoot vines and "+
        "poison ivy, and movement is difficult.\n");
    AI(({"undergrowth","poison ivy","tangleshoot","ivy","vines",
        "tangleshoot vines"}),"These plants cover the path, hinting that "+
        "this trail has not been used for a long time.\n");
    AI("forest","The forest is thick, letting little light penetrate the "+
        "forest floor.\n");
    AI(({"forest floor","floor"}),"It is covered with thick vegetation, "+
        "struggling for light.\n");
    AI(({"small clump","clump","grasses","sticks"}),"It has the look of an "+
        "old bird nest that has fallen out of a tree.\n");
    AI(({"old nest","nest","bird nest","old bird nest"}),"This nest has "+
        "fallen out of a tree and has certainly been abandoned.\n");
    add_search(({"old nest","nest","bird nest","old bird nest"}),1,
        "find_shell",1);

    add_exit(TDIR + "path1", "north",0,4,1);
    add_exit(TDIR + "path3", "southwest",0,4,1);

    set_tell_time(120);
    add_tell("A rustling sound can be heard in the forest to the "+
             "southwest.\n");
    add_tell("The sound of a mole rooting about reaches your ears.\n");
    add_tell("The air has a thick silence to it.\n");
    
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"forest","herbs","trail","path",
        "undergrowth"}), 6);
       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();
   
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);
 
  if (interactive(ob))
    start_room_tells();
}

string
find_shell(object who, string what)
{
    if (shell_found)
    {
    return 0;
    }
 
    say(QCTNAME(who) + " finds something in the bird nest!\n");
    clone_object(SHELL)->move(TO, 1);
    shell_found = 1;
    return "You find an egg shell in the bird nest!\n";
}

