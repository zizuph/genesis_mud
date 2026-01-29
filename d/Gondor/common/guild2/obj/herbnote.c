/*
 *  /d/Gondor/common/guild2/obj/herbnote.c
 *
 *  Note for the herb shop report.
 */

inherit "/std/object.c";

#include <macros.h>
#include <stdproperties.h>

/*
 * Prototypes
 */

int do_discard(string str);

void
create_object()
{
    set_name( ({"note", "parchment", "herb note", "herb report"}) );
    set_pname( ({"notes", "parchments", "herb notes", "herb reports"}) );
    set_short("empty note");
    set_pshort("empty notes");
    set_long("This is a blank piece of parchment.\n");
}

void
init()
{
    ::init();

    add_action(do_discard, "discard");
}

int do_discard(string str)
{
   notify_fail("Discard what? The " +short()+ "?\n");

   str = lower_case(str);

   if(!str)
      return 0;
   
   if(str == "report" || str == "note" || str == "parchment")
   {
      this_player()->catch_msg("You crumble the " +short()+ " in your hand and discard it.\n");
      say(QCTNAME(this_player())+ " crumbles a " +short()+ " before discarding it.\n");

      remove_object();
      return 1;
   }
   else
      return 0;
}

public string query_recover()
{
   return 0;
}




