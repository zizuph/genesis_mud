#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>

public int undrift(string arg);
public int dearm_myself(string arg);

public void
create_room()
{
    set_short("PlayerArch Office");
    set_long("This is one of the hot spots in the world of Genesis." +
      " This room is the office of the all powerful Archwizard of" +
      " Players. The room is very clean, all except for a desk in the" +
      " corner displaying a strange looking device. There is also" +
      " a banner and a painting hanging on the opposite walls." +
      " The Playerarch team can help you if you have problems " +
      "while wandering the realms of Genesis. " +
      "\n\n"+
      "You may post about restoration problems or bugs or private matters " +
      "on this board. Only other Archwizards and the Lieges will be able " +
      "to read your words. You may also mail the Playerarch from any " +
      "post office. Simply 'mail aop'."+
      "\n\n"+
      "Please note! If you've lost guild items, those are " +
      "restored by your guildmaster! All other rebootable items are " +
      "restored by the npcs who rewarded them. Any other questions " +
      "should be directed to the Playerarch."+
      "\n");

    add_item(({"painting","portrait","picture"}),"The painting" +
      " depicts the first Archwizard in charge of player" +
      " affairs, Tricky, attending to his daily work with" +
      " mortals.\n");

    add_item("banner","The banner fills the space between the" +
      " lintel and the ceiling, and is centered between the" +
      " two walls. It has some words written on it.\n");

//    add_cmd_item("banner", "read", "Nolite es Bastardes carbarundum.\n");
    add_cmd_item("banner", "read", "Nolite te Bastardes Carborundorum.\n");
    // What was I drinking when I agreed to this? *grin*

    add_item("desk","A strange device dominates the center of" +
      " the desk.\n");

    add_item("device","A mechanical device of gnomish origin" +
      " sporting a multitude of bells and whistles and even a horn.\n");

    add_item(({"bell","bells"}),"Bells of various sizes adorn" +
      " this strange contraption, tinkling occasionally with" +
      " the movement of air. Perhaps you could ring a bell.\n");

    add_cmd_item("bell","ring","Curiosity is a strange thing." +
      " You decide to ring a bell.\n\n" +
      " A bell rings!\n");

    add_item(({"whistle","whistles"}),"Whistles of all shapes" +
      " and sizes are attached haphazardly to the strange" +
      " device. Perhaps you could blow a whistle.\n");

    add_cmd_item("whistle","blow","Against better judgement" +
      " you decide to blow on a whistle.\n\n" +
      " A whistle shrieks loudly!\n");

    add_item("horn","A funny looking curved horn sit on top" +
      " of this strange device. Perhaps you could toot the horn.\n"); 

    add_cmd_item("horn","toot","Giving in to an urge, you" +
      " decide to toot the horn.\n\n" +
      " A horn toots!\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 100);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit("/d/Sparkle/area/city/rooms/streets/center_a", "west");

    reset_room();
}

public void
reset_room(){
    object board;
    if(!present("board")){
        board = clone_object("/w/postmaster/private/arch_boards/restorations");
	board->move(this_object());
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
//    if (!LOAD_ERR("/d/Emerald/alaron/private/restore_object"))
//        "/d/Emerald/alaron/private/restore_object"->restore_all_missing(ob);
    if (!LOAD_ERR("/d/Gondor/common/guild/recruithall"))
	"/d/Gondor/common/guild/recruithall"->test_restore_ranger(ob);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
}


public void
init()
{
    ::init();
    add_action("undrift", "undrift");
    add_action("dearm_myself", "dearm");
}


public int
dearm_myself(string arg)
{
    if (arg != "myself")
    {
	notify_fail("Dearm myself perhaps?\n");
	return 0;
    }

    this_player()->remove_skill(SS_UNARM_COMBAT);
    write("You are no longer skilled in unarmed combat.\n");
    return 1;
}

public int
undrift(string arg)
{
    if (strlen(arg))
    {
	notify_fail("You can only undrift yourself.\n");
	return 0;
    }

    this_player()->set_m_in(F_ALIVE_MSGIN);
    this_player()->set_m_out(F_ALIVE_MSGOUT);
    return 1;
}

