

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>

inherit "/d/Krynn/std/room";
//inherit "/d/Krynn/std/library/library";

void
create_krynn_room()
{
    set_short("library backroom");
    set_long("This is a backroom of the Great Library. There are special books " +
	     "here dedicated to the races, regions and families of Krynn. You " +
	     "can then affiliate yourself with a family, a region or a tribe. " +
	     "Of course, you can always deny your heritage again, too. There " +
	     "is a sign how to use the library.\n");
    add_item("sign","You can read it.\n");
    add_cmd_item("sign","read",
		 "The Region, Family and Tribe archive of the Great Library of Palanthas\n" +
		 "======================================================================\n" +
		 "| Check the 'index' for a list of topics, and the 'catalog' of each  |\n" +
		 "| topic for a list of available books. You can then 'borrow' any of  |\n" +
		 "| the available books. Note that you must give the complete title of |\n" +
		 "| a book (up to any '-') you want to borrow. Please do not forget to |\n" +
		 "| return borrowed books.                                             |\n" +
		 "+--------------------------------------------------------------------+\n");
    add_exit(PAL_LIBRARY,"northwest");

//    set_lib_type(0);
 //   set_lib_id("race_guild_lib_id");
//    set_lib_long("the region, family and tribe archive section of the Great " +
 //                "Library of Palanthas");
//    set_lib_path(KRGDIR + "books/");
//    set_search_delay(4.0);
/*    set_default_topics((["New Arrivals":1,
			 "Trash":1,
			 "Regions of Krynn":0,
			 "Humans of Krynn":0,
			 "Elves of Krynn":0,
			 "Dwarves of Krynn":0,
			 "Gnomes of Krynn":0,
			 "Kender of Krynn":0,
			 "Minotaurs of Krynn":0,
			 "Goblins of Krynn":0,]));*/
  //  setup_library();
}

void
init()
{
    ADA("affiliate");
    ADA("deny");
 //   init_library();
    ::init();
}
/*
void
leave_inv(object player, object dest)
{
    library_leave_inv(player, dest);
    ::leave_inv(player, dest);
}
*/
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
	  NF("You are already a member of this guild.\n")
	else
	  write("You are already a member of this guild.\n");
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
    /*if (!TP->test_bit("Krynn", GUILD_GROUP, QUEST_BIT))
      {
      if (!silent)
      write("You are not worthy to join this guild.\n");
      return !silent;
      }*/
    
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
    {
        write("You reach out and touch the shimmering crystal.\n");
        set_alarm(1.0,0.0, &write("You pause for a second as you graps around the crystal.\n"));
        set_alarm(2.0,0.0, &write("You are amazed by the coldness surrounding the "+
                                   "crystal.\n"));
        set_alarm(4.0,0.0, &write("A sharp pain shoots up your right arm as the "+
                                   "crystal begins to transform you into a minotaur.\n"));
        set_alarm(6.0,0.0, &write("You can feel your body changing shape into a much "+
                                  "more muscular creature.\n"));
        set_alarm(8.0,0.0, &write("You feel a terribly pain as two large horns pierce the "+
                                  "skin on your head.\n"));
        set_alarm(10.0,0.0, &write("You're body is covered with rough fur.\n"));
        set_alarm(12.0,0.0, &write("You collaps on the ground.\n"));
        set_alarm(13.0,0.0, &write("The transformation seems to be finished, you are now "+
                                  "one of the " + region + "s in Krynn and take " +
                          	  "the name '" + fname + "'.\n"));
        set_alarm(13.0,0.0, &say(QCTNAME(TP) + " touches the shimmering crystal.\n"));
        set_alarm(13.0,0.0, &say(QCTNAME(TP) + " collapses on the ground!\n"));
        set_alarm(13.0,0.0, &say(QCTNAME(TP) + " has been turned into a minotaur.\n"));
    }

    
    find_living("aridor")->catch_msg("RACE JOIN: " + QCTNAME(TP) + " joined: " +
				     region + ", " + fname + "\n");
    
    TP->clear_guild_stat(SS_RACE);
    
    write_file(JOINPATH, extract(ctime(time()), 4, 15) + " " +
	       TP->query_real_name() + " " + region + ":" + fname + ".\n");
    
    return 1;
}

varargs int
affiliate(string str, int silent = 0)
{
    mixed res;
    string region, famname;
    
    if (!silent)
      NF("Affiliate myself with <family of where> within <race-type>?\n")
    if (!str || sscanf(str,"myself with %s within %s",famname,region) != 2)
      return 0;

    res = MASTERROOM->check_name_ok(TP,L(region),L(famname));

    if (intp(res))
    {
	if (!silent)
	{
	    if (TP->query_race_name() != "human")
	      NF("Sorry, your race is not allowed to join this guild.\n")
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

    if (region == "half-elf" || region == "half-human" ||
	region == "kender"   || region == "minotaur")
    {
	who->remove_subloc(SUBLOC_MISCEXTRADESC);
	who->add_subloc(SUBLOC_MISCEXTRADESC, MISC_SUBLOC);
	who->reset_race_name();
    }
    rem_shadow(who);
    who->remove_cmdsoul(KRYNN_RACE_SOUL);
    who->update_hooks();
    who->set_guild_pref(SS_RACE,0);
    who->clear_guild_stat(SS_RACE);
    write_file(LEAVEPATH, extract(ctime(time()), 4, 15) + " " +
	       who->query_real_name() + (force ? " expelled" : "") + ".\n");
}

varargs int
deny(string str, int silent = 0)
{
    if (!silent)
      NF("Deny what? Your heritage of Krynn maybe?\n");
    if (!str)
      return 0;

    if (!parse_command(L(str),E(TP),"[my] / [the] 'heritage' [in] / [of] 'krynn'"))
      return 0;

    if (this_player()->query_guild_name_race() != GUILD_NAME)
    {
        write("You have no heritage in Krynn to deny.\n");
        return 1;
    }
    if (this_player()->query_race_name() != "minotaur")
    {
        write("You can not leave this guild here.\n");
        return 1;
    }


    do_leave(TP,0);
    if (!silent)
    {
	write("You deny your heritage in Krynn! You are not affiliated with any region " +
	      "or family within Krynn from now on.\n");
	say(QCTNAME(TP) + " denies " + HIS(TP) + " heritage in Krynn.\n");
    }
    return 1;
}

