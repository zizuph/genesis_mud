/*
 * letter.c
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"

public void
create_object()
{
    set_name("letter");
    add_name("parchment");
    add_name(DQ_LAST_LETTER);
    set_adj("short");
    
    set_long("A letter written on a piece of parchment.\n");
    
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 11);
    add_prop(OBJ_I_VALUE, 2);
}

public int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (!str || !id(str))
        return 0;
           
    if (TP->query_skill(SS_LANGUAGE) < 40)
    {
        write("You don't understand what it says. It's looks short though.\n");
    }
    else
    {
        write("The letter reads:\n" +
              "Beloved Amelia,\n" +
              "    I must flee. I going down to the beach outside port\n" +
              "Larousel. I'm going to catch a ship there. While waiting\n" +
              "for the ship I'll hide in the cave. Remember when we went\n" +
              "there so many years ago...\n" +
              "  With all of my love,\n" +
              "    Vernon  (hopefully not the last of the Avenchirs)\n\n" +
              "PS. Save this letter if you need to get past the hydra\n" +
              "    and get hold of the treasure. It's made of the special\n" +
              "    kind of parchment the guardian prefers.\n");
    }
    say(QCTNAME(TP) + " reads a letter.\n");
    return 1;
}

public void
init()
{
    ::init();
    
    add_action(do_read, "read");
}
