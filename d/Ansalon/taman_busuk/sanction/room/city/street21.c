#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/guild/dragonarmy/guild.h"

inherit SANCOUTROOM;

object *guard = allocate(4);

void
reset_sanction_room()
{
    int i;
    setuid();
    seteuid(getuid());
    if (!objectp(guard[0]))
    {
	guard[0] = clone_object(SNPC + "da_member");
	guard[0]->set_color("blue");
	guard[0]->arm_me();
	guard[0]->move(TO, 1);
	tell_room(TO, QCTNAME(guard[0])+" arrives.\n");
    }
    if(!objectp(guard[1]))
    {
	if (random(4))
	{
	    guard[1] = clone_object(SNPC + "da_member");
	    guard[1]->set_color("blue");
	    guard[1]->arm_me();
	}
	else
	{
	    guard[1] = clone_object(DRAGONARMY_NPC + "aurak");
	    guard[1]->set_color("blue");
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
	    guard[i]->set_color("blue");
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


void
create_sanction_room()
{
    set_short("a stone bridge over a hot lava stream");
    set_extra_long("You stand upon a stone bridge that crosses " +
       "a lava stream flowing from one of the volcanoes to your " +
       "east.");

    add_item(({"hot lava stream","lava stream","river",
	"flow","lava flow",
	"river of molten rock","lava"}),
      "From the east a lava river runs past you to the west and " +
      "into the harbour. The heat from this river is staggering, " +
      "and you feel faint standing at this distance from it.\n");
    add_item(({"stone bridge","bridge"}),
      "You stand on a stone bridge crosses a river of lava flowing from " +
      "your east to your west into the harbour. " +
      "How it was constructed is anyones guess, although it does look " +
      "recently repaired.\n");

    add_exit(SCITY + "street22","north",0);
    add_exit(SCITY + "street8","south", "@@block_camp");

    reset_sanction_room();

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
	if(!CAN_SEE(g, TP))
	{
	    TP->catch_tell("You manage to sneak past the guards unnoticed.\n");
	    return 0;
	}

	if (IS_MEMBER(TP) ||
            IS_MEMBER(TP->query_leader()) ||
	    TP->query_guild_name_occ() == "Priests of Takhisis" ||
            TP->query_wiz_level() ||
            TP->query_guild_name_lay() == "Templars of Takhisis" ||
           (!TP->query_guild_name_occ() && TP->query_alignment() < -200))
        {
	    write(g->query_The_name(TP)+" lets you into the camp.\n");
	    return 0;
	}
	team = TP->query_team_others();
	for(i=0; i < sizeof(team); i++)
	{
	    if (IS_MEMBER(team[i]) ||
		team[i]->query_guild_name_occ() == "Priests of Takhisis" ||
                team[i]->query_wiz_level() ||
                team[i]->query_guild_name_lay() == "Templars of Takhisis" ||
                (!TP->query_guild_name_occ() && TP->query_alignment() < -200))
	    {
		write(g->query_The_name(TP)+" lets you into the camp.\n");
		return 0;
	    }
	}
          
	write(g->query_The_name(TP)+" stops you.\n");
	g->command("say Camp entrance only in company of dragonarmy soldier!");
	return 1;
    }

    write("You cross the bridge into Sanction.\n");
    return 0;
}

