// created: Lilith ~2000
// updates: Lucius May 2009: Disabled ogre raids. Too much whining.
// updates: Lilith Oct 2021: Bringing back ogre raids if there are at least
//                           2 SU logged in and in Avenir. 
//                           Now Logging to /d/Avenir/log/ogre. 
//                           Also added "bash gate" action for ogres.

#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

inherit "/std/room";
#include "../dark.h"
#include "/d/Avenir/smis/sys/statserv.h"

// Define this to disable ogre raids, undef to enable.
//#define DISABLED
#define TOKEN_ID        "_Shadow_Union_Token"

#define WRITE(x)  tell_room(TO, x + "\n");
#define DEBUG(x)  tell_room(TO, "OGRE: " + x + "\n")

// Default time between raid checks.
// 80 hours.
#define CHECK_DELAY	288000.0
// Default time between ogre movements.
#define MOVE_ALARM	7.0

#define IS_UNION(x) \
    ((x)->query_guild_name_occ() == "Union of the Warriors of Shadow")

#define OGRE	(MON + "ogre")
#define RAIDER	(MON + "ogre_raider")
#define RSIZE   (2)

private static object *ogres = ({ });
private static int last_raid, raid_alarm, move_alarm, updating_alarm;

private static string *locs = ({
	L5 + "e12",
	L5 + "w12",
	L5 + "s12",
});

private static mapping rooms = ([
	L5 + "s18" : L5 + "s7",
	L5 + "s19" : L5 + "s7",
	L5 + "s7" : L5 + "s8",
	L5 + "s8" : L5 + "s9",
	L5 + "s10" : L5 + "s9",
	L5 + "s9" : L5 + "s20",
	L5 + "s20" : L4 + "e1",  // link betweek L5 and L4

	L5 + "center" : L5 + "s1",
	L5 + "s1" : L5 + "s2",
	L5 + "s12" : L5 + "s2",
	L5 + "s11" : L5 + "s2",
	L5 + "s2" : L5 + "s3",
	L5 + "s14" : L5 + "s3",
	L5 + "s13" : L5 + "s3",
	L5 + "s3" : L5 + "s4",
	L5 + "s15" : L5 + "s4",
	L5 + "s4" : L5 + "s5",
	L5 + "s16" : L5 + "s5",
	L5 + "s17" : L5 + "s5",
	L5 + "s5" : L5 + "s6",
	L5 + "s6" : L5 + "s7",
	L5 + "e19" : L5 + "e17",
	L5 + "e18" : L5 + "e17",
	L5 + "e17" : L5 + "e6",
	L5 + "e6" : L5 + "e5",
	L5 + "e5" : L5 + "e4",
	L5 + "e4" : L5 + "e3",
	L5 + "e3" : L5 + "e2",
	L5 + "e2" : L5 + "e1",
	L5 + "e1" : L5 + "center",

	L5 + "e8" : L5 + "e9",
	L5 + "e9" : L5 + "e10",
	L5 + "e10" : L5 + "e11",
	L5 + "e16" : L5 + "e14",
	L5 + "e14" : L5 + "e13",
	L5 + "e15" : L5 + "e13",
	L5 + "e13" : L5 + "e12",
	L5 + "e12" : L5 + "e11",
	L5 + "e11" : L5 + "n3",
	L5 + "n6" : L5 + "n5",
	L5 + "n5" : L5 + "n4",
	L5 + "n4" : L5 + "n3",
	L5 + "n3" : L5 + "n2",
	L5 + "n2" : L5 + "n1",
	L5 + "n1" : L5 + "center",

	L5 + "n14" : L5 + "n13",
	L5 + "n15" : L5 + "n13",
	L5 + "n13" : L5 + "n12",
	L5 + "n12" : L5 + "n11",
	L5 + "n11" : L5 + "n7",
	L5 + "n10" : L5 + "n9",
	L5 + "n9" : L5 + "n8",
	L5 + "n8" : L5 + "n7",
	L5 + "n7" : L5 + "n6",
	L5 + "n18" : L5 + "n17",
	L5 + "n19" : L5 + "n17",
	L5 + "n17" : L5 + "n16",
	L5 + "n16" : L5 + "n6",
//	L5 + "w17" : L5 + "w16",
	L5 + "w16" : L5 + "w14",
//	L5 + "w15" : L5 + "w14",
	L5 + "w13" : L5 + "w12",
	L5 + "w12" : L5 + "w11",
	L5 + "w11" : L5 + "w10",
	L5 + "w10" : L5 + "w4",
	L5 + "w9" : L5 + "w8",
	L5 + "w8" : L5 + "w7",
	L5 + "w7" : L5 + "w6",
	L5 + "w6" : L5 + "w5",
	L5 + "w5" : L5 + "w4",
	L5 + "w4" : L5 + "w3",
	L5 + "w3" : L5 + "w2",
	L5 + "w2" : L5 + "w1",
	L5 + "w1" : L5 + "center",
	L5 + "s20" : L4 + "e1",
	L4 + "e1" : L4 + "center",

	L4 + "center" : L4 + "n1",
	L4 + "n1" : L4 + "n12",
	L4 + "n12" : L4 + "n13",
	L4 + "n13" : L4 + "n20",
	L4 + "n20" : L4 + "n21",
	L4 + "n21" : L4 + "n22",
    L4 + "n22" : L4 + "n23",
    L4 + "n23" : L4 + "n24",
    L4 + "n24" : L4 + "n25",
    L4 + "n25" : L4 + "n25b",
    L4 + "n25b" : L2 + "n10",
    L4 + "n22" : L4 + "n23",
	L4 + "n27" : L4 + "n29",
	L4 + "n29" : L4 + "n30",
	L4 + "n30" : L4 + "n31",
	L4 + "n31" : L3 + "ec3",  // link between L4 and L3

	L3 + "ec3" : L3 + "e2",
	L3 + "e2" : L3 + "e1",
	L3 + "e1" : L3 + "center",
	L3 + "center" : L3 + "s1",
	L3 + "s1" : L3 + "s2",
	L3 + "s2" : L3 + "s3",
	L3 + "s3" : L3 + "s4",
	L3 + "s4" : L3 + "s5_l2",
	L3 + "s5_l2" : L2 + "n10",  // link between L3 and L2

	L2 + "n10" : L2 + "n9",
	L2 + "n9" : L2 + "n8",
	L2 + "n8" : L2 + "n7",
	L2 + "n7" : L2 + "w8",
	L2 + "w8" : L2 + "ut1",
	L2 + "ut1" : L2 + "ut2",
	L2 + "ut2" : L2 + "ut3",
	L2 + "ut3" : L2 + "ut4",
	L2 + "ut4" : L2 + "ut5",
	L2 + "ut5" : UNION + "room/entry",  // link between L2 and Union
	UNION + "room/entry" : "END"

//	UNION + "room/entry" : UNION + "room/hall_w1",
//	UNION + "room/hall_w1" : UNION + "room/hall_w2",
//	UNION + "room/hall_w2" : UNION + "room/crossing",
//	UNION + "room/crossing" : UNION + "room/hall_e",
//	UNION + "room/hall_e" : UNION + "room/landing",
//	UNION + "room/landing" : UNION + "room/hall_low",
//	UNION + "room/hall_low" : UNION + "room/guild"  // destination
//	UNION + "room/guild" : "END",
]);

public int
has_sphere(object who)	{ return objectp(present(TOKEN_ID, who)); }

private void
write_error(string str)
{
    write_file("/d/Avenir/log/ogre",
	ctime(time()) + ": Ogre attack error: " + str + "\n");
}

public void test_rooms()
{
    foreach (string room_path, string dest : rooms)
    {
        if (dest == "END")
        {
        continue;
        }
        room_path->blah();
        object room = find_object(room_path);
        //write(room_path + "size: " + sizeof(room->query_exit_rooms()) + "\n");
        int index = member_array(dest, room->query_exit_rooms());
        if (index == -1)
        {
            write("Could not establish move command from " +
                room_path + " to " + dest + "\n");
        }
    }
}

public void test_ogre_paths()
{
    string orig;
    foreach(string room_path : locs)
    {
        orig = room_path;
        string dest = rooms[orig];
        while (dest != "END")
        {
           orig->blah();
           object room = find_object(orig);
           int index = member_array(dest, room->query_exit_rooms());
           if (index == -1)
           {
               write("Could not establish move command from " +
                   orig + " to " + dest + "\n");
               break;
           }
           orig = dest;
           dest = rooms[orig];
        }
        write("Path : " + room_path + " is checked.\n");
    }
}

private int
advance(object mon)
{
    object env;

    if (!objectp(mon))
	return 0;

    if (!objectp(env = environment(mon)))
	return 0;

    string where = file_name(env);
    string dest = rooms[where];

    if (!strlen(dest))
    {
	write_error("Could not find destination room from " + where);
	ogres -= ({ mon });
	return 0;
    }

    if (dest == "END")
    {
    write_file("/d/Avenir/log/ogre", ctime(time()) + ": Raiders reached Gate.\n");
	WRITE("Final destination reached: "+ file_name(mon));
	mon->command("bash gate with weapon");
//	mon->set_random_move(300 + random(50));
//	mon->set_restrain_path(0);
	ogres -= ({ mon });
	return 0;
    }

    int index = member_array(dest, env->query_exit_rooms());

    if (index == -1)
    {
//	write_error("Could not establish move command from " +
//	    where + " to " + dest);
	return 0;
    }

    string cmd = env->query_exit_cmds()[index];

    DEBUG("Moving " + file_name(mon) + " command: "+ cmd +
	"\n\tfrom: " + where + "\n\t  to: " + dest);

    // Send a message once in a while
    if (random(30) == 0)	
      filter(users(), has_sphere)->catch_tell(
      "\nJazur's Passion burns through your veins.\n   "+
      "A vision pierces its way into your mind, that of ogres "+
	  "moving through the utterdark toward the Halls of Shadow...\n\n");

    return mon->command(cmd);
}

private int
will_move_ogre(void)
{
    return random(7);
}

private void
advance_ogres(void)
{
    if (!sizeof(ogres))
    {
	WRITE("OGRE: move_alarm disabled; no ogres left to move.");
	remove_alarm(move_alarm);
	move_alarm = 0;
	return;
    }

    ogres = filter(ogres, objectp);

    if (will_move_ogre())
	map(ogres, advance);
}

private void
start_attack(void)
{
#ifdef DISABLED
    /* This disables ogre raids. */
    return;
#endif

    if (move_alarm)
	return;

    WRITE("OGRE: move_alarm initiated.");
	write_file("/d/Avenir/log/ogre", ctime(time()) + ": Ogre attack initiated.\n");
	filter(users(), has_sphere)->catch_tell(
      "\nA feeling of dread floods you.\n   "+
      "A vision pierces your mind, that of ogres "+
	  "amassing for an attack upon the Halls of Shadow...\n\n");

    last_raid = time();
    move_alarm = set_alarm(MOVE_ALARM, MOVE_ALARM, advance_ogres);

    foreach(string loc : locs)
    {
	int chance = (sizeof(ogres) ? 2 : 3);

	/* Chance to skip this team. */
	if (!random(chance))
	    continue;

	object mon;
	int size = RSIZE;

	while(size--)
	{
	    mon = clone_object(OGRE);
	    mon->equip_me();
		mon->command("wield all");
		mon->add_prop("_i_am_raiding_ogre", 1);
	    mon->move_living("xx", loc);

	    ogres += ({ mon });
	}

	/* Raider will auto-form a team but 
     * Only with ogres with the raiding prop.	
	 */
	mon = clone_object(RAIDER);
	mon->equip_me();
	mon->command("wield all");
	mon->move_living("xx", loc);

	ogres += ({ mon });
    }

    WRITE("OGRE: Raider teams cloned; NUM of Ogres: "+ sizeof(ogres));
	write_file("/d/Avenir/log/ogre", ctime(time()) + ": NUM of Ogres: "+ 
	  sizeof(ogres) +"\n");
	STATSERV_LOG_EVENT("Utterdark", "Ogre raids");
}

/*
 * Checks to see if a raid should begin.
 */
private void
check_attack(void)
{
#ifdef DISABLED
    return;
#endif
    float delay = CHECK_DELAY;

    /* If there was a raid started last cycle,
     * then do not check again for while.
     */
    if (itof(time() - last_raid) <=(delay * 3.0))
	delay *= 4.0;

    raid_alarm = set_alarm(delay, 0.0, check_attack);

    /* There was already a raid recently. */
    if (delay != CHECK_DELAY)
	return;

    /* Random chance for raids. 25% currently. */
    if (random(4))
	return;

    object *valid = ({ });

    foreach(object who : users())
    {
	/* Check if Union. */
	if (!IS_UNION(who))
	    continue;

    if (who->query_wiz_level())
        continue;

	/* Check if Novice. */
	if (who->query_union_sphere() == "training")
	    continue;

	object room = environment(who);

	/* Check if in a room. */
	if (!objectp(room))
	    continue;

	/* Check domain travelling. */
	if (room->query_domain() != "Avenir")
	    continue;

	string file = file_name(room);

	/* Check for convenience. */
	if (wildmatch("*union/room/novlib*", file))
	    continue;

	if (wildmatch("*common/city/bath*", file))
	    continue;

	if (wildmatch("*city/zigg/level4*", file))
	    continue;

	/* We should be able to handle a raid. */
	valid += ({ who });
    }
    /* If more than one warrior active in Avenir, proceed. */
    if (sizeof(valid) > 1)
	start_attack();
}

private void
update_rooms(int i)
{
    int j, sz;
    string *places = m_indexes(rooms);

    updating_alarm = 0;

    if (i >= (sz = sizeof(places)))
    {
	WRITE("All rooms are loaded.");
	return;
    }

    j = (i - 1);
    i += 5;

    if (i >= sz)
	i -= (i - sz);

    while(++j < i)
    {
	if (find_object(places[j]))
	    DEBUG("Already loaded: " + places[j]);
	else
	{
	    places[j]->teleldensanka();
	    DEBUG("Loaded room: " + places[j]);
	}
    }

    updating_alarm = set_alarm(2.0, 0.0, &update_rooms(j+1));
}

private int
attack_stat(string str)
{
#ifdef DISABLED
    write("Ogre raids have been DISABLED.\n");
    return 1;
#endif

    object *places;
    string *files, s;

    if (!strlen(str) || str == "attack")
    {
	WRITE("Ogre raid statistics:");
	WRITE("  Ogre move_alarm is currently: "+
	    (move_alarm ? "on" : "off"));
	WRITE("  Ogre raid_alarm is currently: "+
	    (raid_alarm ? "on" : "off"));
	WRITE("  Ogre last_raid is: "+ 
	    (last_raid ? ctime(last_raid) : "none"));
	WRITE("There are currently " + sizeof(ogres) +
	    " ogres raiding.");

	places = map(ogres, environment);
	files = map(filter(places, objectp), file_name);

	if (sizeof(files))
	{
	    WRITE("The ogres currently reside in the following places:");
	    WRITE(COMPOSITE_WORDS(sort_array(files)));
	}

	return 1;
    }

    if (str == "load")
    {
	WRITE("Loading rooms.....");
	update_rooms(0);
	return 1;
    }

    if (str == "begin")
    {
	WRITE("Beginning attack...\n");
	start_attack();
	return 1;
    }

    if (str == "end")
    {
	WRITE("Ending attack...\n");

	if (move_alarm)
	{
	    remove_alarm(move_alarm);
	    move_alarm = 0;
	}

	return 1;
    }

    if (str == "off")
    {
	WRITE("Stopping ogre raids.....");
	remove_alarm(raid_alarm);
	raid_alarm = 0;
	return 1;
    }

    if (str == "on")
    {
	WRITE("Starting ogre raids.....");
	remove_alarm(raid_alarm);
	raid_alarm = set_alarm(CHECK_DELAY, 0.0, check_attack);
	return 1;
    }


    write(str + ": command not implemented.\n");
    write("Currently available commands are: begin, end, load, on, off.\n");
    return 1;
}

private void
create_room(void)
{
    set_short("Ogre attack master room");
    set_long("Ogre attack master room.\n"+
      "The commands are: attack, attack begin, "+
      "and attack off.\n");

    raid_alarm = set_alarm(CHECK_DELAY, 0.0, check_attack);
}

public void
init(void)
{
    ::init();

    add_action(attack_stat, "attack");
    add_action(attack_stat, "ogres");
}
