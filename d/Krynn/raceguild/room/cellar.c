#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <options.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"


inherit "/d/Krynn/std/room";

void
create_krynn_room()
{
    set_short("Dusty cellar underneath the Great Library");
    set_long("This is an old cellar underneath the library of Palanthas. " +
	     "Old, half-rotten books lie in large piles on the wooden floor " +
	     "most of them drenched in water. A few broken furnitures have "+
             "been shoved aside making a small open space in the middle of the "+
             "room, where a large shimmering crystal has been bolted to the "+
             "floor. You can feel a slight coldness emitted by the crystal.\n"+
             "A large plaque is on the wall here.\n");
    add_item("plaque","You can read it.\n");
    add_item("crystal","The crystal is a massive almost human-size and made out "+
             "of a dark-gray material.\n"+
             "You realize that this crystal must have been touched by the Gray "+
             "Gem and somehow inherited some of the powers that the Gem had.\n");
    add_cmd_item("plaque","read",
		 "The words on the plaque looks somewhat faded, but you do manage to read them:\n\n" +
		 "Minotaurs of Krynn\n"+
		 "==================\n\n"+
		 "Minotaurs are large creatures that look like seven foot tall "+
		 "bulls standing on their hind legs. They are covered with "+
		 "coarse fur that ranges in color from red to blond to black. "+
		 "As a minotaur grows old, his or her coat begins to mottle. "+
		 "Minotaurs take great pride in their horns, which can be up "+
		 "to 24 inches long.\n"+
		 "The Minotaurs of Krynn were created many years ago by the "+
		 "Graygem of Chaos. They put great stock on honor and family, "+
		 "each minotaur has a clan name indicating what clan a minotaur "+
		 "comes from. There is no worse punishment for a minotaur than "+
		 "to be banished by his or her clan, which results in all clan "+
		 "records having the banished one's name blacked out.\n"+
		 "Minotaurs are very stubborn and thick headed. They "+
		 "have a might makes right outlook on life. On matters of "+
 		 "honor, they are as strict as Knights of Solamnia, though "+
		 "their definition of honor varies from that of the Knighthood. "+
		 "A minotaur will always keep his or her word. Minotaurs are "+
		 "always very loyal to their clans and families. Anyone who "+
		 "questions the honor of a minotaur should be prepared to "+
		 "be challenged.\n"+
		 "Minotaurs don't get along particularly well with "+
		 "any race, including their own sometime. Minotaurs consider all "+
		 "other races weak and inferior. They think of the elves "+
		 "as tree-hugging sissies. Humans are too weak and fickle, "+
		 "however sometimes minotaurs do develop friendships with "+
		 "humans. Minotaurs hate kender with few exceptions. Kender love "+
		 "to taunt and enrage minotaurs, who invariably try to catch and "+
		 "kill the kender.\n\n"+
                 "You can use the 'affiliate' and 'deny' commands here aswell.\n"+
		 "Type    : Minotaur\n"+
		 "Region  : 'of Mithas', 'of Kothas', 'of Nethosak', 'of Holakan', 'of Morthosak'\n"+
		 "Families: 'de-Kaz', 'de-Orilg', 'de-Toron', 'de-Flarok', 'de-Teskos', 'Es-Hestos',"+
		 " 'Es-Kalin', 'Es-Istian', 'El-Halup', 'Et-Pethis', 'Ohn-Koraf', 'Ra-Kar'.\n");

    add_exit("/d/Krynn/raceguild/room/joinroom","up");
}

void
init()
{
    ADA("affiliate");
    ADA("deny");
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
    if (TP->query_guild_name_occ() == "School of High Magic")
    {
	if (silent)
	  NF("Minotaurs can't be students of the school of High Magic. " +
           "Leave the school before trying to become a minotaur.\n")
	else
	  write("Minotaurs can't be students of the school of High Magic. " +
           "Leave the school before trying to become a minotaur.\n");
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
    {
        write("You reach out and touch the shimmering crystal.\n");
        set_alarm(1.0,0.0, &write("You pause for a second as you grasp the crystal.\n"));
        set_alarm(2.0,0.0, &write("You are amazed by the coldness surrounding the "+
                                   "crystal.\n"));
        set_alarm(5.0,0.0, &write("A sharp pain shoots up your right arm as the "+
                                   "crystal begins to transform you into a minotaur.\n"));
        set_alarm(8.0,0.0, &write("You can feel your body changing shape into a much "+
                                  "more muscular creature.\n"));
        set_alarm(12.0,0.0, &write("You feel terrible pain as two large horns pierce the "+
                                  "skin on your head.\n"));
        set_alarm(15.0,0.0, &write("Your body starts growing rough fur.\n"));
        set_alarm(18.0,0.0, &write("You collapse on the ground.\n"));
        set_alarm(21.0,0.0, &write("The transformation seems to be finished, you are now "+
                                  "one of the " + region + "s in Krynn and take " +
                          	  "the name '" + fname + "'.\n"));
        set_alarm(24.0,0.0, &say(QCTNAME(TP) + " touches the shimmering crystal.\n"));
        set_alarm(27.0,0.0, &say(QCTNAME(TP) + " collapses on the ground!\n"));
        set_alarm(30.0,0.0, &say(QCTNAME(TP) + " has been turned into a minotaur.\n"));
    }

   
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
    NF("Affiliate myself with <family> <of where> within minotaur?\n")
    if (!str || sscanf(str,"myself with %s within %s",famname,region) != 2)
      return 0;

    res = MASTERROOM->check_name_ok(TP,L(region),L(famname));

    if (intp(res))
    {
	if (!silent)
	{
        if (TP->query_race_name() != "human" &&
        TP->query_race_name() != "dwarf" &&
            TP->query_race_name() != "goblin")
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

    /* REMOVE THE HEAD AC FROM THE PREVIOUS MINOTAUR */
    if (region == "minotaur")
        (who->query_combat_object())->cb_remove_hitloc(A_HEAD);

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
	write("The shimmering piece of crystal emits a bright light.\n");
        write("When you open your eyes again you have been transformed "+
              "into a normal "+TP->query_race_name()+"!\n");
        say("The shimmering piece of crystal emits a bright light.\n");
	say("When you open your eyes again you see that "+QCTNAME(TP) +
            " has been transformed into a normal "+TP->query_race_name()+" again!\n");
    }
    return 1;
}

