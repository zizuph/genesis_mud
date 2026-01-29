#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

#define OTHER_ROOM FORNOST_DIR+"hideout_entr"

public int check_ranger();

void
create_room()
{
    set_short("In a stair inside a tower");
    set_long(BS("You are in a staircase inside an old tower. Torches are "+
    "set in torch sconces along the walls, illuminating the stairs. "+
    "There is a stone door in the wall leading out. The stairs "+
    "lead down.\n"));
    add_item("stairs","The stair look well used, but in good repair.\n");
    add_item("torches","They provide light for the stairs.\n");
    add_item(({"door","stone door"}),BS("The stone door is of excellent "+
    "quality, made by the best dwarven craftsmen.\n"));

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR+"o_corridor","down","@@stop_stealth");
    add_exit(OTHER_ROOM,"out","@@door_open");
}

void
door_close()
{
    object  tp = TP;

    if (present(tp, TO) || present(tp, find_object(OTHER_ROOM)))
        tp->catch_msg("The stone door closes behind you.\n");
    tell_room(TO,"The stone door closes.\n",tp);
    tell_room(OTHER_ROOM,"The stone door closes.\n",tp);
}

void
door_open()
{
    TP->catch_msg("You open the stone door.\n");
    say(QCTNAME(TP)+" opens the stone door.\n");
    tell_room(OTHER_ROOM,"The stone door opens.\n",);
    set_alarm(1.0, 0.0, door_close);
    if (TP->query_prop("_ranger_was_stealthy"))
    {
        TP->remove_prop("_ranger_was_stealthy");
        if (TP->query_autosneak() || sizeof(TP->query_team()))
            return;
        TP->set_autosneak(1);
        TP->catch_msg("You prepare to move stealthily again as "
          + "you were when entering the halls.\n");
    }
}

int
stop_stealth()
{
    if (check_ranger())
    {
	return 1;
    }
    if (TP->query_autosneak())
    {
        TP->set_autosneak(0);
        TP->catch_msg("You stop sneaking as you enter the hidden halls.\n");
        TP->add_prop("_ranger_was_stealthy", 1);
    }
    return 0;
}


public int
check_ranger()
{
    if (TP->query_wiz_level()) 
        return 0;
    if (TP->query_skill(SS_PUNISHMENT) == NOACCESS) 
    {
        write(BSN("You are stopped on the stairs, since the Council of Rangers"+
	      " has punished you with limited access to the guildhouses."));
	return 1;
    }
    if (!present("ranger_guild_object", TP))
    {
	write("You are stopped on the stairs, as you have no "+
	      "membership-token to show.\n");
        return 1;
    }
    return 0;
}
