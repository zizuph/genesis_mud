/* Modified:
 * June 2005 - Louie.  Non-guilded evil people are allowed into camp.
 */

/** 
 * Navarre February 4th 2007
 * - Added permission for templars to go through the camp
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include "/d/Ansalon/guild/dragonarmy/guild.h"

inherit SANCOUTROOM;


// Prototypes

void handle_friendship_token(object player, object guard, object token);
void let_player_pass(object player, object guard, object token);
void move_the_player(object player, object guard, object token);

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
//	guard[0]->set_dragonarmy_rank(2);
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
//	    guard[1]->set_dragonarmy_rank(1, 7);
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
//	    guard[i]->set_dragonarmy_rank(1);
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

        object token = present("_da_friendship_token_", TP);
        
        if(token)
        {
            set_alarm(2.0, 0.0, &handle_friendship_token(TP, g, token));
        }
          
	write(g->query_The_name(TP)+" stops you.\n");
	g->command("say Camp entrance only in company of dragonarmy soldier!");
	return 1;
    }
    return 0;
}

void
handle_friendship_token(object player, object guard, object token)
{
    player->catch_msg("You put on your best show and confidently hand your "+token->short()+" to the "+QTNAME(guard)+".\n");
    tell_room(this_object(), QCTNAME(player)+" shows a "+token->short()+" to the "+QTNAME(guard)+".\n", player);

    set_alarm(2.0, 0.0, &let_player_pass(player, guard, token));
}


void
let_player_pass(object player, object guard, object token)
{
    guard->command("say Kalen finally got someone to do his dirty work for him did he?");
    guard->command("say Tell him that he needs to inform us of change of plans next time... " +
                   "and tell him that he owes us double for letting you pass in his stead.");
    guard->command("grin");
    set_alarm(1.0, 0.0, &move_the_player(player, guard, token));
}

void
move_the_player(object player, object guard, object token)
{
    guard->command("emote pockets a "+token->short()+".");
    guard->command("emote waves you off.");
    player->catch_msg("You quickly enters the camp before the guard decide to ask additional questions.\n");
    tell_room(this_object(), QCTNAME(player)+" enters the camp in a hurry.\n", player);
    player->move_living("east", "/d/Ansalon/taman_busuk/sanction/room/blue/r1", 0, 0);
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

    add_item("torches", "Some guards patrolling the bridge must have "+
             "placed them here.\n");

    add_prop(ROOM_I_LIGHT, 5);

    add_prop(ROOM_I_HIDE, 90);

    add_exit(SCITY + "street18","west",0);
    add_exit(SBLUE + "r1", "east", block_camp);

    reset_sanction_room();
}


string
long_descr()
{
    return tod_short_descr()+ "You stand on a " +
    "stone bridge over a lava stream. " +
    "You feel dizzy from the super-heated air and noxious "+
    "sulphur fumes that rise from below. " +season() + 
    "A couple of torches sits in a torch stand on the bridge, they illuminate "+
    "the bridge effectively.\n";
}
