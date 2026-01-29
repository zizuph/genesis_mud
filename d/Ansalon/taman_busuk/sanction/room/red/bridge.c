#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include "/d/Ansalon/guild/dragonarmy/guild.h"

inherit SANCOUTROOM;

object *guard = allocate(5);

void
reset_sanction_room()
{
    int i;

    setuid();
    seteuid(getuid());

    if (!objectp(guard[0]))
    {
	guard[0] = clone_object(SNPC + "da_member");
	guard[0]->set_color("red");
	guard[0]->set_dragonarmy_rank(2);
	guard[0]->arm_me();
	guard[0]->move(TO, 1);
	tell_room(TO, QCTNAME(guard[0])+" arrives.\n");
    }
    if(!objectp(guard[1]))
    {
	if (random(4))
	{
	    guard[1] = clone_object(SNPC + "da_member");
	    guard[1]->set_color("red");
	    guard[1]->set_dragonarmy_rank(1, 7);
	    guard[1]->arm_me();
	}
	else
	{
	    guard[1] = clone_object(DRAGONARMY_NPC + "aurak");
	    guard[1]->set_color("red");
	    guard[1]->arm_draconian();
	}
	guard[1]->move(TO, 1);
	tell_room(TO, QCTNAME(guard[1])+" arrives.\n");
    }
    guard[0]->team_join(guard[1]);

    for (i=2; i<sizeof(guard); i++)
    {
	if (!objectp(guard[i]))
	{
	    guard[i] = clone_object(SNPC + "da_member");
	    guard[i]->set_color("red");
	    guard[i]->set_dragonarmy_rank(1);
	    guard[i]->arm_me();
	    guard[i]->move(TO,1);
	}
	guard[0]->team_join(guard[i]);
    }
    for (i=0; i<sizeof(guard); i++)
    {
	if (E(guard[i]) != TO)
	{
	    tell_room(E(guard[i]), QCTNAME(guard[i])+" leaves.\n");
	    guard[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCTNAME(guard[i])+" arrives.\n");
	}
    }
}

int
block_camp()
{
    int i;
    object g, *team;

    for(i=0; i<sizeof(guard); i++)
    {
	if(guard[i] && E(guard[i]) == TO)
	{
	    g = guard[i];
	    break;
	}
    }
    if(g)
    {
	if(!TP->check_seen(g) && !TP->query_wiz_level())
	{
	    TP->catch_tell(g->query_The_name(TP)+" on guard stays so that "+
		"not even a mouse could sneak past him into the camp.\n");
	    return 1;
	}
	if (IS_MEMBER(TP) || TP->query_wiz_level() || IS_MEMBER(TP->query_leader()) ||
	    TP->query_guild_name_occ() == "Priests of Takhisis"
        || (!TP->query_guild_name_occ() && TP->query_alignment() < -200))
	{
	    write(g->query_The_name(TP)+" lets you into the camp.\n");
	    return 0;
	}
	team = TP->query_team_others();
	for(i=0; i<sizeof(team); i++)
	{
	    if (IS_MEMBER(team[i]) ||
		team[i]->query_guild_name_occ() == "Priests of Takhisis"
        || (!TP->query_guild_name_occ() && TP->query_alignment() < -200))
	    {
		write(g->query_The_name(TP)+" lets you into the camp.\n");
		return 0;
	    }
	}
	write(g->query_The_name(TP)+" stops you.\n");
	g->command("say Only potential recruits or those in the company of "+
            "dragonarmy soldiers may enter!");
	return 1;
    }
    return 0;
}

void
create_sanction_room()
{
    set_short("on a stone bridge over a lava stream");
    set_long("@@long_descr");

    add_item(({"bridge","stone bridge"}),
      "This bridge of indeterminable age spans over a lava stream " +
      "that flows through the city of Sanction.\n");
    add_item(({"lava","lava stream"}),
      "A lava stream flows slowly under the bridge. The heat " +
      "from it hits you like a physical blow.\n");
    add_item(({"fumes","air","super-heated air","noxious fumes"}),
      "Super-heated air rises on either side of you, blurring " +
      "your field of sight. Noxious fumes added with the heat makes " +
      "you feel dizzy and eager to move on.\n");

    add_prop(ROOM_I_HIDE, 90);

    add_exit(SCITY + "street16","south",0);
    add_exit(SRED + "r1","north", block_camp);

    reset_sanction_room();
}


string
long_descr()
{
    return tod_short_descr()+ "You stand on a " +
    "stone bridge over a lava stream. " +
    "You feel dizzy from the super-heated air and noxious "+
    "sulphur fumes that rise from below. " +season() + "\n";
}
