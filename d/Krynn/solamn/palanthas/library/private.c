/* created by Aridor, 06/06/94 */

inherit "/std/room";

#include "local.h"
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/guilds/sohm/defs.h"
#include "/d/Krynn/common/defs.h"

#define SOHM_I_FOUND_SPELL "_sohm_i_found_palanthas_scroll"

object asti, scroll;

void
reset_room()
{
    if (asti)
      return;
    asti = clone_object(LIBRARY + "astinus");
    asti->move_living("xxx",TO);
}


void
create_room()
{
    set_short("Private chamber of Astinus");
    set_long("You are in Astinus' private study, where the great historian "
	     + "chronicles the events of Krynn as they happen. While bookshelves "
             + "line the walls of this room as most others in the library, the "
             + "main items distinguishing it from others is an ornate desk in the "
             + "middle with a comfortable chair sitting behind it.\n");
    
    add_prop(ROOM_I_LIGHT, 10);
    INSIDE;
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(OBJ_S_WIZINFO,"Wizards can add books here by simply putting "
	     + "the file into .../library/personal/<title>\n");

    add_exit(LIBRARY + "public","north","@@without_book_only");

    add_item(({"chair"}),"A comfortable chair for the master historian to " +
        "chronicle the histories of Krynn.\n");
    add_item(({"desk"}),"An ornate desk. It is largely devoid of items, "
	     + "with the exception of a crystal sphere set on a stand on the desk.\n");
    add_item(({"sphere","ball","crystal sphere"}),
	     "This curious crystal sphere is the famous Sphere of Time. This magical "
	     + "device created by the infamous wizard Fistandantilus allows Astinus " +
             "to see events happen across Krynn.\n");
    add_item(({"bookshelves","bookshelf","tomes"}),
             "Bookshelves line the walls in the private chamber of Astinus, filled " +
             "with tomes of the histories of Krynn.\n");

    add_cmd_item(({"volume","tome","tome diligently","volume diligently","the volume"}),
                 ({"study"}),"@@study_the_tome");

    set_alarm(1.0,0.0,"reset_room");
}

int
without_book_only()
{
    object ob = present(PALANTHAS_BOOK, TO);
    if (present(PALANTHAS_BOOK,TP))
      {
	  write("Don't forget to return the book first.\n");
	  return 1;
      }
    if (ob)
      ob->remove_object();
    (LIBRARY + "public")->back_from_audition(TP);
    return 0;
}

void
set_person_on_audition(object who)
{
    asti->give_out_book(who);
}

void
is_coming_on_audition(object who)
{
    set_alarm(10.0,0.0,"set_person_on_audition", who);
}

int
study_the_tome()
{
    if (!present(PALANTHAS_BOOK,TP))
    {
        NF("What?\n");
        return 0;
    }

    if (present(PALANTHAS_BOOK,TP)->query_prop("_obj_s_volume_number") != "huma")
    {
        NF("What?\n");
        return 0;
    }

    if((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery")) 
    {
        NF("What?\n");
        return 0;
    } 
   
    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
	NF("Your spellcraft skills are too poor to " +
          "comprehend the curious runes in the tome.\n");
	return 0;
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"ehtahxiekiv"))
    {
        NF("You study the volume diligently, but do not find anything " +
          "of interest.\n");
        return 0;
    }

    if(this_player()->query_prop(SOHM_I_FOUND_SPELL))
    {
        NF("You study the volume diligently, but do not find anything " +
          "further of interest.\n");
        return 0;
    }

    write("You diligently study the volume, and notice a parchment tucked " +
        "away as a bookmark within its pages. With a quick shake, you dislodge " +
        "it in to your inventory.\n");

    this_player()->add_prop(SOHM_I_FOUND_SPELL, 1);

    scroll = clone_object("/d/Krynn/common/scrolls/scry_scroll");
    scroll->move(this_player());
    seteuid(getuid());

    return 1;

}
