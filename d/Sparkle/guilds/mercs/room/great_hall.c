/*
 * /d/Genesis/guilds/merc/room/great_hall.c, by Morrigan 11/2001
 *
 */
inherit "/std/room";

#include "../merc.h"
#include "room.h"

#define LIVE_LAST_EXTRA_SHORT "_live_last_extra_short"
#define PLAYER_I_AT_DESK "_player_i_at_desk"
#define PLAYER_I_ON_COUCH "_player_i_on_couch"
#define ARENA MBATTLE + "battlegrounds"

private void add_to_couch(object who);
public int merc_only();


mapping statues = ([ ]);

object guard1, guard2;

int
merc_only()
{
    if (this_player()->id("_mercenary_guild_guard_"))
        return 0;

    if (this_player()->query_merc_dog())
	return 0;

    if (this_player()->query_wiz_level())
	return 0;

    if (!this_player()->query_guild_member(MERC_NAME))
    {
        write ("Several guards prevent you from going that way.\n");
        return 1;
    }

    write("You are allowed to pass into the inner areas of the guildhouse.\n");
    return 0;
}            

int
arena_entrance()
{
    if (this_player()->id("_mercenary_guild_guard_"))
	return 1;

    if (this_player()->query_wiz_level())
	return 0;

    if (this_player()->query_leader())
    if (!this_player()->query_guild_member(MERC_NAME) &&
    IS_MERC(this_player()->query_leader()) && 
        (environment(this_player()->query_leader()) == find_object(ARENA) ||
        environment(this_player()->query_leader()) == find_object(MHALL)))
    {
        write("A guard says: You are permitted to enter in "+
        this_player()->query_leader()->query_name()+"'s company.\n");
        this_player()->query_leader()->catch_msg("The guards permit "+
            this_player()->query_name()+" to enter in your company.\n");
        return 0;
    }

    if (!this_player()->query_guild_member(MERC_NAME))
    {
        write ("Several guards prevent you from going that way.\n");
        return 1;
    }

    write("As you step into the arena, you are filled with a sense of "+
	"wonder.\n");
    return 0;
}            


public void setup_statues()
{
    int i;
    string *remove_list = ({ }), tmp, ctmp, tmp2, *items = ({ });

    if (sizeof(m_indexes(statues)) < 1)
        return;

    for (i = 0; i < sizeof(this_object()->query_item()); i++)
        items += ({ this_object()->query_item()[i][0][0] });

    /* Add the statues to the room */
    for (i = 0; i < sizeof(m_indexes(statues)); i++)
    {

        if (!MCREST->query_crest_lord(m_indexes(statues)[i]))
        {
		remove_list += ({ m_indexes(statues)[i] });
		continue;
	}


        if (statues[m_indexes(statues)[i]][1] = "0")
        {
  	    statues[m_indexes(statues)[i]][1] = 
		MCREST->query_crest_description(m_indexes(statues)[i]);
            save_object(MERC_STATUES);
        }

        if (this_object()->item_id(m_indexes(statues)[i]) == 0)
        {
            tmp = "statue of "+lower_case(m_indexes(statues)[i]);
            ctmp = "statue of "+m_indexes(statues)[i];

	    tmp2 = "You curiously inspect a very realistic statue of a "+
		statues[m_indexes(statues)[i]][0]+"."; 

            if (statues[m_indexes(statues)[i]][1] != "nothing")
                tmp2 += " At the base of the "+
		"statue, there has been painted a crest of a "+
		statues[m_indexes(statues)[i]][1]+".\n";
           else
                tmp2 += "\n";

            if (member_array(tmp, items) == -1)
            this_object()->add_item(({ tmp, ctmp }),  tmp2);
        }
    }

    /* Don't bother removing if there are no statues to remove */
    if (sizeof(remove_list) == 0)
        return;

    /* Remove the statues */
    for (i = 0; i < sizeof(remove_list); i++)
    {
        statues = m_delete(statues, remove_list[i]);
	save_object(MERC_STATUES);

       this_object()->remove_item(remove_list[i]);
    }

    return;
}

public int remove_statue(string str)
{
    if (member_array(capitalize(str), m_indexes(statues)) == -1)
        return 0;

    statues = m_delete(statues, capitalize(str));
    save_object(MERC_STATUES);
    setup_statues();
    return 1;
}

public void reset_room()
{
    setup_statues();

    /* They have all left. (Gorboth)
    if (!guard1)
	(guard1 = clone_object(MNPC + "merc_base"))->move(this_object());

    if (!guard2)
	(guard2 = clone_object(MNPC + "merc_base"))->move(this_object());
    */

}

private int do_pose(string str)
{
    object me = this_player();
    string extra_tell = "";

    NF("Pose what? Just pose.\n");
    if (str)
        return 0;

    NF("You strike a pose, but no one seems to care.\n");
    if (!MCREST->query_crest_lord(me->query_name()) &&
	!me->query_wiz_level())
	return 0;    

    if (member_array(me->query_name(), m_indexes(statues)) > -1)
    {
        statues = m_delete(statues, me->query_name());
	save_object(MERC_STATUES);
	extra_tell = " You also notice that the gnome seemed more than a little "+
	    "annoyed at having to redo his work.";
    }

    statues += ([ me->query_name() : ({ me->query_nonmet_name(), 
        MCREST->query_crest_description(me->query_name()) }) ]);
   save_object(MERC_STATUES);
   setup_statues();

    write("You pose briefly, and a small gnome appears from the west. As he "+
	"chisels furiously, the air becomes cloudy with stone dust. When the "+
	"dust settles, you notice a statue that bears a striking resemblance "+
	"to you."+extra_tell+"\n");
    say(QCTNAME(me)+" poses briefly, and a small gnome appears from the west. "+
	"As he chisels furiously, the air becomes cloudy with stone dust. "+
	"When the dust settles, the statue bears a striking resemblance to "+
	QTNAME(me)+".\n");
    return 1;
}

private int do_sit(string str)
{
	if (!strlen(str))
	{
		NF("Sit where? In one of the chairs?\n");
		return 0;
	}

	if (TP->query_prop(PLAYER_I_AT_DESK) ||
		TP->query_prop(PLAYER_I_ON_COUCH))
	{
		NF("You're already seated.\n");
		return 0;
	}

	if (parse_command(str, ({ }),
	 "[down] [at] [on] [the] 'chair' / 'chairs' / 'circle'"))
	{
		write("You find a seat at the circle and settle comfortably "+
		    "into it.\n");
		say(QCTNAME(TP)+" takes "+POSSESSIVE(TP)+" place around "+
		    "the circle and settles comfortably into a chair.\n");
		add_to_couch(TP);
		return 1;
	}
	
	NF("Sit where? In a chair??\n");
	return 0;
}

private void add_to_couch(object who)
{
	who->add_prop(PLAYER_I_ON_COUCH, 1);

	if (who->query_prop(LIVE_S_EXTRA_SHORT))
	    who->add_prop(LIVE_LAST_EXTRA_SHORT, 						who->query_prop(LIVE_S_EXTRA_SHORT));

    who->add_prop(LIVE_S_EXTRA_SHORT, " is seated at the circle");
	return;
}

private void remove_from_couch(object who)
{
	who->remove_prop(PLAYER_I_ON_COUCH);

	if (who->query_prop(LIVE_LAST_EXTRA_SHORT))
	{
		who->add_prop(LIVE_S_EXTRA_SHORT, 				                    who->query_prop(LIVE_LAST_EXTRA_SHORT));
		who->remove_prop(LIVE_LAST_EXTRA_SHORT);
	}

	who->remove_prop(LIVE_S_EXTRA_SHORT);
	return;
}

private int do_stand(string str)
{
	if (TP->query_prop(PLAYER_I_ON_COUCH))
	{
		write("You stand from the chair.\n");
		say(QCTNAME(TP)+" stands up from "+POSSESSIVE(TP)+" position "+
			"at the circle.\n");
		remove_from_couch(TP);
		return 1;
	}

	NF("You are already standing.\n");
	return 0;
}

public string
statues_desc()
{
    object me = this_player();
    string *remembered = m_indexes(me->query_remembered()), *statue_list = ({ });
    string stat_str,str;
    int i, my_statue = 0;

    remembered += ({ lower_case(me->query_name()) });

    if (sizeof(m_indexes(statues)) > 0)
    {
        for (i = 0; i < sizeof(m_indexes(statues)); i++)
            if((member_array(lower_case(m_indexes(statues)[i]), remembered) > -1) ||
                me->query_wiz_level())
		statue_list += ({ m_indexes(statues)[i] });
    }

    if (member_array(me->query_name(), statue_list) > -1)
    {
        statue_list -= ({ me->query_name() });
	my_statue = 1;
    }

    str = "The statues that line the walls of "+
	"the chamber look to be warriors of all sorts. Some hold great "+
	"swords or clubs, but most hold a shield and weapon at the ready. ";
        
    if (sizeof(statue_list))
        if (sizeof(statue_list) == 1)
            stat_str = "a statue";
           else
            stat_str = "statues";

    if (sizeof(statue_list) > 0 && my_statue == 1)
        str += "You recognize "+stat_str+" of "+COMPOSITE_WORDS(statue_list) +
	    ", as well as a statue of yourself.";
   else if (sizeof(statue_list) && my_statue != 1)
        str += "You recognize "+stat_str+" of "+COMPOSITE_WORDS(statue_list)+".";
   else if (!sizeof(statue_list) && my_statue == 1)
        str += "You recognize a statue of yourself.";

    return str + "\n";
}

public string
read_rules()
{
    string txt = "The Circle:\n\n"+
	"The circle is a place where mercenaries can come together "+
	"and share stories of adventure and battle. It has no head "+
	"or tail, everyone is to be treated equally.\n";
    return txt;
}

public void
create_room()
{
    set_short("The Great Hall of the Mercenaries");
    set_long("In the center of the vast chamber sits a circle of chairs, "+
	"which surround a circular, black rug adorned with the emblem of "+
	"a red dragon. Lifelike statues stand on eternal vigil around the "+
	"walls of the chamber, facing toward the center of the room. "+
	"Halls extend to the north, south, east and west of here. The "+
	"hall to the north leads outdoors into a vast open area. There "+
	"is also a small chamber to the northeast.\n");
    
    add_cmd_item(({"rug", "words", "enscription"}), "read", 
        &read_rules());

    add_item("rug", "The rug covers the floor surrounded by the circle of "+
	"chairs, upon its black background is a striking emblem of a red "+
	"dragon. Words have been sewn around the circular edge of the rug, "+
	"which you may read.\n");
    add_item(({"statue", "statues"}), "@@statues_desc");
    add_item(({"chair", "chairs", "circle"}), "A circle of chairs has been "+
	"set up here, surrounding the rug.\n");
    add_prop(ROOM_I_INSIDE, 1);

    seteuid(getuid(TO));
    restore_object(MERC_STATUES);

    reset_room();
    add_exit(MROOM + "join.c", "south", 0, 1, 0);
    add_exit(MROOM + "board_room.c", "northeast", &merc_only(), 1, 0);
    add_exit(MROOM + "rack_room.c", "east", &merc_only(), 1, 0);
    add_exit(MROOM + "west_hall.c", "west", &merc_only(), 1, 0);
    add_exit(MBATTLE + "battlegrounds.c", "north", &arena_entrance(), 1, 0);
}

public void init()
{
	::init();

	add_action(do_sit, "sit");
	add_action(do_stand, "stand");
	add_action(do_pose, "pose");
}

void leave_inv(object ob, object to)
{
	::leave_inv(ob, to);

	if (!living(ob))
		return;

	if (ob->query_prop(PLAYER_I_ON_COUCH))
	{
		ob->catch_tell("You rise from the circle before leaving.\n");
		tell_room(E(ob), QCTNAME(ob)+" rises from the circle before "+
			"leaving.\n", ob);
		remove_from_couch(ob);
	}	

}
