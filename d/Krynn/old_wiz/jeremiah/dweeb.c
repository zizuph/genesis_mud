/*
   dweeb.c
   -------

   Coded ........: 95/03/12
   By ...........: :)

   Latest update : 95/03/12
   By ...........: :)

*/

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
inherit M_FILE

string sign_text;

create_krynn_monster()
{
   int i;
 
   set_name("dweeb");
   set_race_name("human");
   set_long("This is a young member of the Greenpeace organization " +
            "he is probably agitating for a just cause. Don't mess " +
            "with him, or he will blow up his rubber boat, drop it " +
            "on the floor and occupy this room for a very long time, " +
            "proclaiming that you are an evil scientist trying to " +
            "take over the world.\n");
   set_adj("young");
   add_adj("male");

   for (i = 0; i < 6; i++)
      set_base_stat(i,5 + random(5));

   set_all_attack_unarmed(5, 5);
   set_all_hitloc_unarmed(5);
   set_knight_prestige(-5);
   set_alignment(250);
   set_gender(G_MALE);

   add_item("sign", "@@get_text");

   add_prop(NPC_I_NO_RUN_AWAY,1);
   seteuid(geteuid(TO));
}

void
add_descr(string thing)
{
   add_prop(LIVE_S_EXTRA_SHORT," " + thing);
}

void
remove_descr()
{
   change_prop(LIVE_S_EXTRA_SHORT,"");
}


void
add_text(string text)
{
   sign_text = text + "\n";
}


void 
remove_text()
{
   sign_text = "\n";
}


string
get_text()
{
   return sign_text;
}

