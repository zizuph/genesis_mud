/*
 * coded by Amelia 7/26/97
 * updated and added statue quest - Rhyn
 *
 * Ckrik March 2004, added two eunuchs to protect the priestess
 */

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Earthsea/quest_handler/quest_handler.h"

#define CLIMB_PROP "_player_climbing_karg_statue"
#define MIN_CLIMB 15

#define NUM_EUNUCHS 2

private object priestess;
private object *eunuchs = allocate(NUM_EUNUCHS);
private int eyes, niche, scroll, climb, button;

public void
reset_room()
{
    int i;
    niche = 0;
    scroll = 0;
    button = 0;
    eyes = 1;

    if(!objectp(priestess))
    {
        priestess = clone_object(
            "/d/Earthsea/gont/tenalders/npc/kargess_polearm"
        );
        priestess->move(this_object(), 1);
        priestess->command("emote swirls in like a black flame.");
    }
    for (i = 0; i < NUM_EUNUCHS; i++)
    {
        if(!objectp(eunuchs[i]))
        {
	    eunuchs[i] = clone_object(
               "/d/Earthsea/gont/tenalders/npc/eunuch"
	    );
            eunuchs[i]->move(this_object());
	    priestess->team_join(eunuchs[i]);
        }
    }
}

public void
create_earthsea_room()
{
    set_short("Limestone cave");
    set_long("The confined space suddenly opens into a vast "+
         "domed cave. The red flames from numerous torches leap up "+
         "and cast tall shadows. This seems to be a place for sacrifice, "+
         "as you see a blood-stained altar dominating the center of the "+
    "cave. Behind the altar there is huge stone statue of a " +
    "man kneeling with his arms outstretched. @@sit_desc");

    add_item(({"torch", "torches", "flame", "flames", "red flame",
        "red flames"}),
        "Red flames leap from dozens of torches set about the cave.\n");
    add_item(({"stain", "dark stain"}),
        "The stain looks like dried blood.\n");
    add_item(({"altar", "blood-stained altar", "sacrificial altar"}),
        "@@altar_desc");
    add_item(({"statue", "huge statue", "stone statue",
        "huge stone statue"}), "@@statue_desc");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_NCAVE);
//   add_prop(OBJ_S_SEARCH_FUN, "search_altar");
//   add_prop(OBJ_I_SEARCH_TIME, 3);
// haven't decided what to do yet, since we don't have the commander
    add_tell("You hear the sound of drums pounding.\n");
    add_tell("Flames leap up, casting dark shadows " +
        "all around the cave.\n");
    reset_room();
    set_tell_time(30);
    add_exit("tower_4", "north");
}

public string
sit_desc()
{
   if(this_player()->query_prop(CLIMB_PROP))
   {
      return "You are sitting on the altar.\n";
   }

   return "\n";
}

public string
statue_desc()
{
   string desc = "The statue is seemingly carved from the wall " +
        "itself. It is of a man kneeling, with his arms outstretched " +
        "and a peaceful expression on his face.";

    if(eyes == 1)
    {
        desc += " There is a faint light from the statue's head " +
        "and you notice that there is an empty eyesocket. The other " +
        "holds a green gem which is radiating the light.";
    } else {
        "There is a strong light radiating from the statue's head " +
        "and you notice that both eyesockets contain a glowing " +
        "green gem.";
    }

    return desc + "\n";
}

public string
altar_desc()
{
    string desc = "The altar appears to be part of the ground, you " +
        "cannot see any seams where it meets the floor. " +
        "You notice a dark stain spread over most of the altar.";

    if(niche == 1)
    {
        desc = desc + " There seems to be an opening on the top of " +
        "the altar. It is empty at the moment.";
    } else {
        "The altar is made of smoothed natural rock. It is simple " +
        "and unadorned.";
    }

    return desc + "\n";
}

public int
press_button(string str)
{
    string verb = query_verb();

    if(!button || str != "button")
    {
        return notify_fail(capitalize(verb) + " what?\n");
    }

    if(niche == 1)
    {
        write("You press the button but it has no effect.\n");
        return 1;
    } else {
        write("You press the button and the top of the altar opens!\n");
        niche = 1;
        clone_object(
            "/d/Earthsea/gont/tenalders/obj/items/karg_scroll"
        )->move(this_player(), 1);
        write("You find a piece of paper.\n");
        return 1;
    }
}

public int
climb_statue(string str)
{
    object tp = this_player();

    if(str == "up statue" || str == "up" || str == "statue")
    {
        if(tp->query_prop(CLIMB_PROP))
        {
            write("You are already up the statue.\n");
            return 1;
        }

        if(tp->query_skill(SS_CLIMB) >= MIN_CLIMB)
        {
            write("You manage to scramble up the statue.\n");
            say(QCTNAME(tp) + " manages to climb the statue.\n");
            tp->add_prop(CLIMB_PROP, 1);
            return 1;
        }

        write("You try to gain a foothold, but keep slipping down.\n");
        say(QCTNAME(tp) + " tries to climb the statue.\n");
        return 1;
    }

    if(str == "down statue" || str == "down")
    {
        if(!tp->query_prop(CLIMB_PROP))
        {
            write("You are on the ground!\n");
            return 1;
        }

        write("You climb down the statue.\n");
        say(QCTNAME(tp) + " climbs down the statue.\n");
        tp->remove_prop(CLIMB_PROP);
        return 1;
    }

    return notify_fail("Climb what?\n");
}

public int
put_gem(string str)
{
    object emerald, tp = this_player();

    if((str == "gem in socket" || str == "gem in eyesocket" ||
        str == "gem in hole" || str == "eye in socket" ||
        str == "eye in eyesocket" || str == "eye in hole" ||
        str == "emerald in socket" || str == "emerald in eyesocket" ||
        str == "emerald in hole") &&
        (emerald = present("_karg_eye_emerald_", tp)))
    {
        if(!tp->query_prop(CLIMB_PROP))
        {
            write("You are not up the statue!\n");
            return 1;
        }

        emerald->remove_object();

        if(!QH_QUERY_QUEST_COMPLETED(tp, "killian_carving_task"))
        {
            write("The emerald turns red and explodes in your hand!\n");
            tp->heal_hp(-50);
            return 1;
        }

        eyes = 2;

        if(!QH_QUEST_COMPLETED(tp, "karg_eye_quest"))
        {
            write("That same voice echoes through your mind again: " +
                "'Once more I am in debt to you.'\n");
            return 1;
        }

        write("A voice echoes through your mind: 'Thank you for " +
            "returning my eye. You shall be rewarded.'\n" +
            "You feel much more experienced!\n");
        return 1;
    }

    return 0;
}

public void
init()
{
    ::init();
    add_action(climb_statue, "climb");
    add_action(put_gem, "put");
    add_action(put_gem, "insert");
    add_action(press_button, "press");
    add_action(press_button, "push");
}

public string
search_altar(object tp, string str)
{
    if(str != "altar" && str != "blood-stained altar" &&
        str != "sacrificial altar")
        return 0;

    if(button == 0)
    {
        button = 1;
        return "Your search reveals a button on the side of the altar!\n";
    } else {
        return "You can see a button on the side of the altar.\n";
    }
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(ob->query_prop(CLIMB_PROP))
    {
        ob->catch_tell("You climb down the statue.\n");
    }

    ob->remove_prop(CLIMB_PROP);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
