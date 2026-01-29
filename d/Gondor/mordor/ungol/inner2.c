#pragma strict_types

inherit "/d/Gondor/morgul/vale/morgul2.c";
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define PLAYER_HOLDS_PHIAL "_player_holds_phial"
#define PHIAL_FILE         MORDOR_DIR + "obj/phial.c"


public void
create_morgul_room()
{
    set_short("At the gate at the Morgul Pass, outside Mordor.\n");
    set_extraline("You are at the Pass into Mordor, at the gate to Mordor " +
        "To the north you can see a small courtyard. Here you can see a " +
        "great arch over the gate. Two stone watchers seem to guard the " +
        "gate into Mordor. To the east is the nameless land.\n");

    add_item(({"slope", "valley", "ephel duath"}), BSN(
        "Only shadows and nothing but shadows envelops the entire place, except for a dusty cobbered " +
        "road and huge rocks from the walls of Ephel Duath."));
    add_item(({"road"}), BSN(
        "This is a dusty cobbered road leading to the eastern gates of Minas Morgul and to Cirith Ungol."));
    add_item(({"field", "darkness", "field of darkness"}), BSN("When you try to look through " +
            "the arch, you cannot see " +
            "anything. You think this is because of an invisible field of " +
            "darkness. This field will prevent all mortal beings, perhaps " +
            "except orcs, from leaving Mordor."); 
//"@@exa_field");
    add_item(({"watcher", "watchers"}), BSN("The watchers are like great " +
        "figures seated upon thrones. Each has three joined bodies, and " +
        "three heads facing outward, inward and across the gateway. The " +
        "heads have vulture-faces, and on their great knees are laid " +
        "clawlike hands. They seem to be carved out of huge blocks of " +
        "stone, immovable, and yet they are aware: some dreadful spirit of " +
        "evil vigilance abode in them. They know an enemy. Visible or " +
        "invisible none can pass unheeded. They will forbid his entry, or " +
        "his escape."));
    add_item(({"gate", "arch"}), BSN("You are standing under a dark arch " +
        "and above you, you can see the dark tower of Cirith Ungol. Mighty " +
        "watchers have their obscure way of keeping the enemy out (OR IN!)" +
        "The stones of the arch are smooth and you don't think you can " +
        "climb your way into Mordor here."));
    add_item("tower", BSN("Standing here you see the tower of Cirith Ungol " +
        "in all its might. They rise all the way to the sky and you don't " +
        "look forward to climbing all the way to the top if yo udare. The " +
        "walls are so smooth that probably a spider wouldn't be able to " +
        "climb up to the top."));
    add_item(({"wall", "walls"}), BSN("The walls of the tower are so smooth " +
        "that a spider can't climb up to the top. You are amazed by the " +
        "skills the craftsman of the old had."));

//    add_prop(OBJ_S_WIZINFO, BSN("When a mortal travels east, his way is " +
//        "blocked by an invisible field of darkness. I don't know where " +
//        "mortals can find the phial from the Lady Galadriel yet, but that " +
//        "is the object that mrotals need to be able to break the force of " +
//        "the watchers. The phial is to be found in " + PHIAL_FILE + "."));
 
    add_exit(MORGUL_DIR + "vale/mrd16","west",0,3);
    add_exit(UNGOL_DIR + "yard1", "northwest", 0, 1);
    add_exit("/d/Gondor/common/mordor/common/gorgoroth/udun/room/gor1", "east", "@@pass_gate",1);

    reset_room();

       
}

void
reset_room()
{

}

void
init()
{
    ::init();

    add_action("do_climb", "climb");
}

int
player_holds_phial_filter(object obj)
{
    return (obj->query_prop(PLAYER_HOLDS_PHIAL));
}

/*str
*field_of_darkness()
*{
*    object other_room;
*    object arr_player;
*
*    arr_player = filter(all_inventory(TO), "player_holds_phial_filter", TO);
*
*    other_room = "/d/Gondor/common/mordor/common/gorgoroth/udun/room/gor1";
*
*    if (objectp(other_room))
*   {
*        arr_player += filter(all_inventory(other_room), "player_holds_phial_filter", TO);
*    }
*
*    if (sizeof(arr_player))
*    {
*        return 0;
*    }
*
*    return 1;
*}
*/

/*str
*exa_field()
*{
*    if (field_of_darkness())
*    {
*        return BSN("When you try to look through the arch, you cannot see " +
*            "anything. You think this is because of an invisible field of " +
*            "darkness. This field will prevent all mortal beings, perhaps " +
*            "except orcs, from leaving Mordor.");
*    }
*    else
*    {
*        return BSN("When you try to look through the arch, you cannot see " +
*            "much. You think this is because of an invisible field of " +
*            "darkness. This field is broken by a beam of magical white " +
*            "light, piercing through it. You think you can pass the arch " +
*            "now.");
*    }
*}
*/

void
watchers_cry()
{
    object other_room;

    other_room = "/d/Gondor/common/mordor/common/gorgoroth/udun/room/gor1";
    if (objectp(other_room))
    {
        other_room->watchers_cry();
    }
}

int
pass_gate()
{
    string gate_desc;

    if (!field_of_darkness())
    {
        write(BSN("The field of darkness is penetrated by a beam of white " +
            "light. It is therefor possible for you to travel east."));
        LSAY("The field of darkness is penetrated by a beam of white " +
            "light. It is therefor possible for ", " to travel east.");

        set_alarm(3.0, 0.0, "watchers_cry");

        return 0;
    }

 if(TP->query_wiz_level())
    {
        write(BSN("A field of darkness prevents you from going east. Begin " +
            "a wizard though, you mumble some ancient words and a beam of " +
            "white light flashes through the field of darkness and allows " +
            "you to travel east. If you read wizinfo, you know how mortals " +
            "can follow you east. :-)"));
        LSAY("A field of darkness prevents ", " from going east. Being a " +
            "wizard though, " + PRONOUN(TP) + " mumbles some ancient words " +
            "and a beam of white light flashes throught the field of " +
            "darkness and allows " + OBJECTIVE(TP) + " to travel east.");

        set_alarm(3.0, 0.0, "watchers_cry");

        return 0;
    }

    if (TP->query_stat(SS_WIS) > 65)
    {
        gate_desc = "You know however, from old tales, that a beam of white " +
            "light will help you to pass the field.";
    }
    else
    {
        gate_desc = "You think there must be a way to pass the field, but " +
            "you can't figure out how to pass it though. Maybe you should " +
            "pay more attention when you hear old tales next time.";
    }

    write(BSN("An invisible field of darkness blocks you way to the east. " +
        "All the torches and gems you can collect won't help you to pass " +
        "the field that blocks your way. " + gate_desc));
    LSAY("An invisible field of darkness prevents ", " from going east.");

    return 1;
}

int
do_climb(string str)
{
    if (!str)
    {
        NF("What do you intend to climb here?\n");
        return 0;
    }

    if ((str == "tower") || (str == "wall") || (str == "up"))
    {
        write(BSN("Do you really think that you can climb the tower and " +
            "evade the watchers?"));
        SAY(" in vain tries to climb up the tower.");

        return 1;
    }

    NF("It's a wrong assumption to think there is something to climb here.\n");
    return 0;
}





