

#include "/d/Krynn/raceguild/local.h"
#include "/d/Krynn/raceguild/guild.h"
#include <macros.h>
#include <ss_types.h>

inherit "/d/Krynn/std/room";

void
create_krynn_room()
{
    set_short("Laboratory");
    set_long("This is a backroom of a tent.\n");
    add_item("sign","You can read it.\n");
    add_cmd_item("sign","read",
		 "                   Draconians of Krynn Racial Guild                  \n" +
		 "=====================================================================\n" +
		 "| You can quaff one of the potions here to 'transmute' into a        |\n" +
		 "| draconian.                                                         |\n" +
         "| Eg. 'Transmute myself into <draconian type> from <location>'   	   |\n" +
		 "| Copper potion: kapak                                               |\n" +
		 "| gold potion: aurak                                                 |\n" +
		 "| bronze potion: bozak                                               |\n" +
		 "| silver potion: sivak                                               |\n" +
		 "| the available books. Note that you must give the complete title of |\n" +
		 "| a book (up to any '-') you want to borrow. Please do not forget to |\n" +
		 "| return borrowed books.                                             |\n" +
		 "+--------------------------------------------------------------------+\n");
    add_exit("/d/Krynn/raceguild/room/cellar","down");
}

void
init()
{
    ADA("transmute");
    ADA("transform");
    ::init();
}


/* If silent = 1, the function will return 0 if joining failed,
 * 1 otherwise.
 * If silent = 0, the function will always return 1, but will
 * give appropriate error messages to the player first.
 */
varargs int
do_join(string region, string fname, int silent = 0)
{
    int result;
    string *avnames;
    object sh;

    if (MEMBER(TP))
    {
	if (silent)
	  NF("You are already a member of the Krynn Racial guild.\n")
	else
	  write("You are already a member of Krynn Racial guild.\n");
	return !silent;
    }
    if (TP->query_guild_name_race())
    {
	if (silent)
	  NF("You are already a member of another race guild.\n")
	else
	  write("You are already a member of another race guild.\n");
	return !silent;
    }
    
    seteuid(getuid(TO));
    result = ((sh=clone_object(RACE_SHADOW))->shadow_me(TP, "race", "race",
							GUILD_NAME));
    if (result == 0)
    {
	if (silent)
	  NF("You are already a member of another race guild.\n")
	else
	  write("You are already a member of another race guild.\n");
	return !silent;
    }
    if (result == -4)
    {
	if (silent)
	  NF("The other guilds you have joined prevent you from joining here!\n")
	else
	  write("The other guilds you have joined prevent you from " +
		"joining here!\n");
	return !silent;
    }   

    TP->add_autoshadow(RACE_SHADOW + ":" + fname + "#" + region);
    if (TP->query_wiz_level())
      write("Since you're a wizard the autoshadowing and cmdsoul most likely did not " +
	    "succeed. Please use\n" +
	    "Call me add_autoshadow " + RACE_SHADOW  + ":" + fname + "#" + region +
	    "\ncmdsoul /d/Krynn/raceguild/obj/race_soul" +
	    "\nto patch yourself up!\n");
    TP->set_race_title(fname,region);
    if (!silent)
      write("You affiliate yourself with the " + region + "s in Krynn and take " +
	    "the name '" + fname + "'.\n");
    if (!silent)
      say(QCTNAME(TP) + " seems to have found " + HIS(TP) + " heritage in Krynn, and " +
	  "from now on affiliates " + HIM(TP) + "self with it.\n");
    
    find_living("aridor")->catch_msg("RACE JOIN: " + QCTNAME(TP) + " joined: " +
				     region + ", " + fname + "\n");
    
    TP->clear_guild_stat(SS_RACE);
    
    write_file(JOINPATH, extract(ctime(time()), 4, 15) + " " +
	       TP->query_real_name() + " " + region + ":" + fname + ".\n");
    
    return 1;
}

varargs int
transmute(string str, int silent = 0)
{
    mixed res;
    string region, famname, dracType, location;
    
    if (!silent)
      NF("Transmute myself into <draconian type> <location>?\n")

    if (!str || sscanf(str,"myself into %s %s",dracType,location) != 2)
      return 0;
    write("Location:" + location);
    res = MASTERROOM->check_name_ok(TP,"draconians",L(location));

    if (intp(res))
    {
	if (!silent)
	{
        if (res == 0)
	      NF("Sorry, your race is not allowed to join this guild.\n")
	    else if (res == 1)
	      NF("Sorry, the race-type you selected is not available.\n")
	    else if (res == 2)
	      NF("Sorry, the family name you selected is not available.\n")
	    else if (res == 3)
	      NF("Sorry, the family name you selected is restricted.\n")
	}
	return 0;
    }
    NF("Sorry, a strange bug has occured, please leave a bug report.\n");
    if (!pointerp(res) || sizeof(res) != 2)
      return 0;
    return do_join(res[0],res[1], silent);
}

void
rem_shadow(object ob)
{
    if (!ob->remove_guild_race())
      write_file(LEAVEPATH, extract(ctime(time()), 4, 15) + " " +
	       ob->query_real_name() + ": failed to remove shadow.\n");
}

void
do_leave(object who, int force)
{
    string region = who->query_region_title();

	who->remove_subloc(SUBLOC_MISCEXTRADESC);
	who->add_subloc(SUBLOC_MISCEXTRADESC, MISC_SUBLOC);
	who->reset_race_name();

    set_alarm(2.0,0.0,&rem_shadow(who));
    who->remove_cmdsoul(KRYNN_RACE_SOUL);
    who->update_hooks();
    who->set_guild_pref(SS_RACE,0);
    who->clear_guild_stat(SS_RACE);
    write_file(LEAVEPATH, extract(ctime(time()), 4, 15) + " " +
	       who->query_real_name() + (force ? " expelled" : "") + ".\n");
}

varargs int
transform(string str, int silent = 0)
{
    if (!silent)
      NF("Transform? Transform into your normal race?\n");
    if (!str)
      return 0;

    if (!parse_command(L(str),E(TP),"'into my normal race'"))
      return 0;

    if (this_player()->query_guild_name_race() != GUILD_NAME)
    {
        write("But you are not a draconian.\n");
        return 1;
    }

    do_leave(TP,0);
    if (!silent)
    {
	write("You transform into your normal race again.\n");
	say(QCTNAME(TP) + " transforms into " + HIS(TP) + " normal race again.\n");
    }
    return 1;
}

