
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Shire/annuminas/club/gobdefs.h"
#include "/d/Shire/common/defs.h"

// Dunstable, 12/20/94, apologies to the Rangersoul of Elessar's :)

string
query_auto_load()
{
   seteuid(getuid());
   return MASTER_OB(TO);
}

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Smart Goblin"; }

public mapping
query_cmdlist()
{
    return ([
                  "gcontemplate" :     "gcontemplate",
                  "ghelp"             :      "ghelp",
                  "grabble"          :      "grabble",
                  "grecite"          :      "grecite",
                  "gturn"             :      "gturn",
                  "gwipe"            :      "gwipe"
        ]);
}


int
gcontemplate(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You contemplate life in general.\n");
        all("'s eyes glaze over, obviously lost in thought.");
        return 1;
    }
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Contemplate what?");
    }

    actor("You contemplate", oblist, " as possible dinner.");
    target(" eyes you up carefully, with a strange smile. ", oblist);
    all2act(" eyes carefully", oblist, " with a strange smile.");
    return 1;
}


int
ghelp()
{

   write("The possible commands for the Smart Goblins are:\n"+
   "==========================================================\n"+
   "   gcontemplate:  Think on life in general or a meal.\n"+
   "   ghelp:         This menu.\n"+
   "   grabble:       Mock the Angmarians who failed\n"+
   "                  to take over the realm of Arnor.\n"+
   "   grecite:       Recite some ancient Dunedain lore from your tome.\n"+
   "   gturn:         Flip through the pages of your tome.\n"+
   "   gwipe:         Wipe the sweat of academic effort from your brow.\n");
 
    return 1;

}

int
grabble()
{
        write("You shout Angmar! Angmar! Angmar! and sneer derisively.\n");
        all(" shouts: Angmar! Angmar! Angmar! and sneers derisively at the thought.");
        return 1;
   }


int
grecite()
{
   int ran;
   ran = random(3);

   switch(ran)
   {
    case 0:
        write("You tell the story of Beren Halflost and Lutvren Tunevial.\n");
        all(" haltingly tells you a story about Beren Halflost and Lutvren Tunevial.");
        break;

    case 1:
        write("You tell the tragic love story of Turin and Nuniel.\n");
        all(" weeps incoherently about people named Toorin and Nooniel.\n");
        break;

    case 2:
        write("You tell the tragic love story of Turin and Nuniel.\n");
        all(" weeps incoherently about people named Toorin and Nooniel.\n");
        break;

    case 3:
        write("You tell the importance of hobbits, your friends to the west.\n");
        all(" raves about some halflings and how wonderful they are.\n");
        break;

    }

    return 1;

}

int
gturn()
{
        write("You delicately flip through the pages of your precious tome.\n");
        all(" rips through an old tome, possibly trying to read it.");
        return 1;
}

int
gwipe()
{
        write("You wipe the sweat from your brow with your opened tome.\n");
        all(" opens an old tome and wipes the sweat of academic effort away with it.");
        return 1;

}

