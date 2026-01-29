/*
 *  Trashcan to throw gnomes in
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include "defs.h"

#include <stdproperties.h>
#include <macros.h>

void
create_container()
{
    set_short("trashcan");
    set_name(({"trashcan", "gnome_trash", "can", "bin"}));
    set_adj( ({"iron", "trash"}) );
    set_long("@@trash_long");

    /* Some properties of this thrashcan */
    add_prop(OBJ_I_NO_GET, 1);          /* Not gettable       */
    add_prop(CONT_I_LIGHT, 1);
    add_prop(CONT_I_IN,1);              /* It's a container!  */
    add_prop(CONT_I_RIGID,1);           /* A rigid object     */
    add_prop(CONT_I_TRANSP,0);          /* Not transparant    */
    add_prop(CONT_I_MAX_VOLUME,200000); /* Can contain 200 Ltr */
    add_prop(CONT_I_MAX_WEIGHT,200000); /* Can contain 200 Kg */
    add_prop(OBJ_S_WIZINFO,
             "A simple trashcan. Leave it outside the Hobbiton bank.\n");
}

int
do_toss(string str)
{
    object ob, tp;

    if (str == "" || !str)
        return 0;
    tp = this_player();
    if (!(ob = present(str,tp)))
        return 0;
    if(!(ob->move(this_object()))) {
        write("You toss the " + str + " in the trashcan.\n");
        say(QCTNAME(tp) + " tosses a " + str + " in the trashcan.\n");
        return 1;
    }
    write("Somehow it doesn't work, so you keep the " + str + ".\n");
    return 1;
}

int
do_crawl(string str)
{
    object tp;

    if (str == "" || !str)
        return 0;
    tp = this_player();

    /* Check if the player is inside the trashcan */
    if (this_object() == environment(tp))
    {
        if (str != "out")
        {
            write("Crawl where?");
            return 1;
        }
        write("With a lot of effort, you manage to crawl out of the trashcan.\n");
        tp->move_living("M", environment());
        say(QCNAME(tp) + " crawls out of the trashcan.\n");
        return 1;
    }
    /* it was someone outside the trashcan */
    return 0;
}

string
trash_long()
{
   if (environment(this_player()) == this_object())
   {
      return "It really smells foul in here. Trashcans never have been your "
          + "favourite place to hang out. You are quite uncomfortable in "
          + "here, so you feel in a hurry to 'crawl out' of it, before "
          + "someone throws some more trash in it.\n";
   }
   else
   {
       return "The iron trashcan has been used a lot. It is big enough "
           + "to put someone in it. A nearly unreadable note on it says: "
           + "Thank you for keeping Hobbiton clean!\n";
   }
}

void
init()
{
    ::init();
    
    add_action(do_toss, "toss");
    add_action(do_crawl, "crawl");
    add_action(do_crawl, "climb");
}
