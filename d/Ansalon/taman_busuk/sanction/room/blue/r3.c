/** 
 * Navarre February 4th 2007
 * - Added permission for templars to go through the camp
 */


#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/taman_busuk/mountains/local.h"
#include <macros.h>
#include "/d/Ansalon/guild/dragonarmy/guild.h"

inherit SANCOUTROOM;

object *guard = allocate(3);

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
	guard[0]->set_dragonarmy_rank(1, 7);
	guard[0]->arm_me();
	guard[0]->move(TO, 1);
	tell_room(TO, QCTNAME(guard[0])+" arrives.\n");
    }
    for (i=1; i<sizeof(guard); i++)
    {
	if (!objectp(guard[i]))
	{
	    guard[i] = clone_object(SNPC + "da_member");
	    guard[i]->set_color("blue");
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
	for(i=0; i<sizeof(team); i++)
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
    return 0;
}

void
create_sanction_room()
{
    set_short("on a road passing through an encampment of the Blue Dragonarmy");
    set_long("@@long_descr");

    add_item(({"encampment","tents"}),
      "Surrounding you is an encampment of the Blue Dragonarmy.\n");
    add_item("road","A road passes through the encampment, eventually " +
      "entering the Khalkhist Mountains to your east.\n");
    add_item(({"mountains","khalkhist mountains"}),
      "Surrounding the city of Sanction is the most desolate " +
      "area of the Khalkist Mountains, the Doom Range.\n");
    add_item("trail","To your east a trail begins, " +
      "winding its way through the mountains.\n");

    add_prop(ROOM_I_HIDE, 78);

    add_exit(SBLUE + "r2", "west", block_camp);
    add_exit(SBLUE + "r5", "south", block_camp);

    if (LOAD_ERR(MOUNTAINS_OBJECT))
    {
        write("\nBug! Cannot link to the mountains! Please report immediately!\n\n");
        return;
    } 

    add_exit("","east","@@enter_map:" + MOUNTAINS_OBJECT + "|S@@");

    reset_sanction_room();
}


string
long_descr()
{
    return tod_short_descr()+ "You stand on a " +
    "road passing through an encampment of the Blue " +
    "Dragonarmy. " +
    "To your east the encampment ends and a trail through " +
    "the mountain range begins. To your south you can " +
    "enter further into the encampment, while to the west you " +
    "can head towards the city of Sanction. " +
    season()+ "\n";
}

int
start_trail()
{
    write("The trail is closed off due to a " +
      "landslide. Human slaves work furiously to get it " +
      "cleared, so the pass should be reopened soon.\n");
    return 1;
}
