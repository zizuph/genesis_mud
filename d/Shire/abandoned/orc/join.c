/*
* /d/Shire/orc/join.c
*
* This is the join room of the Hobbit race guild. You may join here.
* Modified from the join room of the Rockfriend guild, created by
   *
* /Mercade, 9 January 1994
*
* This room:
* /Dunstable
* /Mercade, 13 November 1994
*
* Revision history:
* Changed the descriptive aspects of the room
* /Dunstable 18 March 1994
*/

#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/lib/guild_support";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "orc.h"
#include "titles.h"

#define ARMBAND_ID        "_orc_race_guild_armband_"
#define START          (ORCGLD_DIR + "start")
#define LOG_SIZE       25000

#define MEMBERS_FAMILY 0 /* index to the family name            */
#define MEMBERS_AGE    1 /* the age of the last birthday        */
#define MEMBERS_TIME   2 /* index to the date the player joined */
#define INTERVAL 8640000 /* One day */
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))

/*
* Global variables.
*
* The mapping members has the names of the players as indices and the
* values are an array with two elements, the family name of the player
* and the date the player joined.
*/
private mapping members;
static private string *titles = TITLES;

//   Prototypes
void dest_armband(object player);


/*
* Functio name: create_room
* Description : Called when the room is first loaded into memory.
*/
nomask public void
create_room()
{
   set_short("a rustic room");
   set_long("This is an old, rustic room. The floor is made of some " +
      "sort of wood arranged in a block pattern. There are torches " +
      "mounted firmly to each wall, giving the room a magnificant glow. " +
      "There is a small hole in the wall with a sign just above it. " +
      "There are three paintings standing prominently on the wall.\n");
   
   add_item( ({ "pictures", "paintings" }),
      "To look at each individual painting try to examine the first " +
      "painting, the second painting, etc. etc.\n");
   
   add_item(({"first painting"}),
      "The first painting depicts a happy, but obviously tired orc "+
      "sanding the wooden floor of this very room.  Underneath the "+
      "painting, a plaque reads:\nLord Dunstable Uruva, Mayor of the "+
      "Shire.\n");
   
   add_item( ({ "second painting" }),
      "Two figures are prominently visible in the picture; left you see " +
      "a dwarf wearing a majestic white beard. He smiles in a friendly " +
      "way, but you can see a dour trait in his eyes and he wields a large " +
      "axe, decorated with diamonds. The other figure is Lady Justice, " +
      "blindfolded, and carrying a balance and a sword. The hand of the " +
      "dwarf rests on her shoulder. The title of the piece is:\nProctor " +
      "Mercade, Counsellor and Judge.\n");
   
   add_item(({"third painting"}),
      "This painting is a rather odd one indeed.  It shows a tall human "+
      "with very strange eyes, it is a scary visage to behold. The "+
      "caption below reads:\nLord Vladimir Dracul the Impaler.\n");
   
   add_item( ({ "hole" }),
      "It seems very small, about the size of a armband.\n");
   add_item( ({ "sign" }),
      "It contains writing, you can read it.\n");
   add_cmd_item( ({ "sign" }), ({ "read" }),
      "Here you can join or leave the Adventuresome Hobbits Guild. There " +
      "are many families you may join. To get information on the families " +
      "you may use the command \"families\". You can use it to list the " +
      "families in the guild and to see the pedigrees of the families.\n" +
      "If you want to join the guild, you must \"start smoking with " +
      "<family>\", where <family> is the name of the family you wish to " +
      "join. To leave the family, you must \"break habit\". Members can " +
      "\"request armband\" to have their armbands back after they lost them.\n" +
      "When memory fails you, you can always \"list guilds\" to see which " +
      "major guilds you are already a member of.\n" +
      "The air in this room is so tranquil that it would be possible to " +
      "come to yourself and \"meditate\".\n");
   
   add_exit(ORCGLD_DIR + "entrance","north");
   add_exit(ORCGLD_DIR + "hall", "south","@@check_member@@");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_CLEANUP,      1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   
   create_guild_support();
   
   setuid();
   seteuid(getuid());
   
   restore_object(ORC_RACE_GUILD_SAVE);
   if (!mappingp(members))
      {
      members = ([ ]);
   }
   
   /* Test the validity of the members only at the first day of the month.
   */
   if (atoi(ctime(time())[8..9]) == 1)
      {
      set_alarm(12.0, 0.0, "test_members");
   }
}

int
check_member()
{
   
   object tp = this_player();
   
   if((!tp->query_wiz_level()) && (!IS_MEMBER(tp)))
      {
      write("Only guildmembers are allowed past this point.\n");
      return 1;
   }
   return 0;
}

/*
* Function name: init
* Description  : When someone enters the room, the commands are linked
*                to him/her.
*/
nomask public void
init()
{
   ::init();
   
   init_guild_support();
   
   add_action("do_try",   "try");
   add_action("do_try",   "begin");
   add_action("do_try",  "start");
   add_action("do_break", "break");
   add_action("request",  "request");
   add_action("families", "tribes");
   add_action("do_list",  "list");
}

/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());
   
   if (file_size(ORC_RACE_GUILD_LOG) > LOG_SIZE)
      {
      rename(ORC_RACE_GUILD_LOG, (ORC_RACE_GUILD_LOG + ".old"));
   }
   
   write_file(ORC_RACE_GUILD_LOG, text);
}

/*
* Function name: do_try
* Description  : When a orc wants to join the guild, this function
*                makes him/her a member.
* Arguments    : string str - the command line argument.
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_try(string str)
{
   object tp = this_player();
   object shadow;
   string family;
   int    result;
   
   if (!strlen(str))
      {
      notify_fail(capitalize(query_verb()) + " what? Smoking? To join " +
            "the guild, you must \"start smoking with <tribe>\".\n");
      return 0;
   }
   
   if (sscanf(lower_case(str), "smoking with %s", family) != 1)
      {
      notify_fail(capitalize(query_verb()) + " what? Smoking? To join " +
            "the guild, you must \"start smoking with <tribe>\".\n");
      return 0;
   }
   
   if (tp->query_race() != "goblin")
      {
      write("You are not a goblin. Leave now!.\n");
      return 1;
   }
   if(tp->query_alignment() >= -150)
      {
      write("You do not follow the path of goodness which all "+
         "Fearsome Orcs are required to do.\n"+
         "Please take your mischief elsewhere.\n");
      return 1;
   }
   
   if (IS_MEMBER(tp))
      {
      write("You are already a member of the guild. If you have lost " +
         "your armband, you may get a new one using <request armband>. In " +
         "case you want to change tribes, you shall have to leave the " +
         "guild and re-join selecting another tribe.\n");
      return 1;
   }
   
   if (tp->query_guild_member(ORC_RACE_GUILD_TYPE))
      {
      write("You cannot be a member of two racial guilds at a time.\n");
      return 1;
   }
   
   family = capitalize(family);
   if (member_array(family, titles) == -1)
      {
      write("The tribe \"" + family + "\" does not exist in our guild. " +
         "Use the command \"tribes\" to list all possible tribe " +
         "names.\n");
      return 1;
   }
   
   shadow = clone_object(ORC_RACE_GUILD_SHADOW);
   
   if ((result = shadow->shadow_me(tp, ORC_RACE_GUILD_TYPE,
               ORC_RACE_GUILD_STYLE, ORC_RACE_GUILD_NAME)) != 1)
   {
      log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to add shadow with result " + result + ".\n");
      shadow->remove_shadow();
      
      write("How odd. For some reason you cannot seem to pick up the " +
         "habit. However, that should not have happened. Please leave " +
         "a bugreport in this room.\n");
      
      return 1;
   }
   
   //  write("You seem to have a shadow...");
   write("You have become a habitual armband smoker.\n");
   tp->set_family_name(family);
   //    write("Setting family name - Joinroom.\n");
   set_alarm(3.0,0.0,"init_me",tp);
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " +
      ORC_RACE_GUILD_NAME + ".\n");
   
   clone_object(ORC_RACE_GUILD_ARMBAND)->move(tp, 1);
   write("*** Armband cloned ***\n");
   //    write("Getting armband...\n");
   write("A terrible looking orc walks in and give you a dirty " +
	   "armband, then leaves.\n");
   say(QCTNAME(tp) + " is handed a dirty armband by a terrible " +
	   "looking orc\n");
   
   tp->clear_guild_stat(SS_RACE);
   tp->set_guild_pref(SS_RACE, ORC_RACE_GUILD_TAX);
   tp->add_cmdsoul(ORC_RACE_GUILD_SOUL);
   tp->update_hooks();
   //    write("Adding cmdsoul...\n");
   
   members[tp->query_real_name()] = ({ family, tp->query_age(), time() });
   
   save_object(ORC_RACE_GUILD_SAVE);
   //    write("Saving master object...\n");
   
   return 1;
}

int
init_me(object ob)
{
   ob->init_race_shadow();
   return 1;
}
/*
* Function name: lower_skill
* Description  : When a member leaves the guild or is kicked out due
*                to a change of race, this function punishes him/her,
*                removes the soul, shadow, etcetera.
* Arguments    : object tp - the object leaving.
*/
nomask private void
lower_skill(object tp)
{
   object armband;
   
   tp->set_guild_pref(SS_RACE, 0);
   tp->clear_guild_stat(SS_RACE);
   tp->remove_cmdsoul(ORC_RACE_GUILD_SOUL);
   tp->update_hooks();
   tp->setup_skill_decay();
   
   /* If the player starts in the guild by default, set this to
   * the default starting location for all players.
   */
   if (tp->query_default_start_location() == START)
      {
      tp->set_default_start_location(tp->query_def_start());
   }
   
   set_alarm(2.0,0.0,&dest_armband(tp));
   {
      armband->remove_object();
   }
   
   /* Remove him/her from the list of members.
   */
   members = m_delete(members, tp->query_real_name());
   
   setuid();
   seteuid(getuid());
   
   save_object(ORC_RACE_GUILD_SAVE);
}

void
remove_from_list(string player)
{
   player = lower_case(player);
   members = m_delete(members,player);
   setuid(); seteuid(getuid());
   save_object(ORC_RACE_GUILD_SAVE);
}

void
dest_armband(object player)
{
   object armband;
   
   armband = present(ARMBAND_ID, player);
   if (objectp(armband))
      {
      armband->remove_object();
      }
}

/*
* Function name: do_break
* Description  : This is a waste of memory since no-one would ever
*                consider leaving a guild like this, or would they?
*                Just for the completeness, this function takes care
*                of a voluntary leave.
* Arguments    : string str - the command line argument
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_break(string str)
{
   object tp = this_player();
   object armband;
   int    result;
   
   if (str != "habit")
      {
      notify_fail("Break what? Your habit?\n");
      return 0;
   }
   
   if (!IS_MEMBER(tp))
      {
      write("You cannot stop smoking since you never started it.\n");
      return 1;
   }
   
   if ((result = tp->remove_guild_race()) != 1)
      {
      log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to remove shadow with result " + result + ".\n");
      
      write("You cannot seem to break the habit! However, everyone who " +
         "wishes so, should be able to do so. Please leave a bugreport " +
         "in this room.\n");
      
      return 1;
   }
   
   write("You are no longer a habitual smoker.\n");
   
   lower_skill(tp);
//   armband = present(ARMBAND_ID, tp);
    armband = present("_orc_race_guild_armband_", tp);
write(ARMBAND_ID + " armbad \n");
   if (objectp(armband))
      {
      armband->remove_object();
      write("Your armband is ripped from your hands and destroyed right " +
         "before your eyes. You have a feeling of overwhelming " +
         "depression come over you, like the roll of thunder.\n");
      say(QCTNAME(tp) + " has " + tp->query_possessive() +
         " armband destroyed.\n");
   }
   
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      ORC_RACE_GUILD_NAME + ".\n");
   
   return 1;
}

/*
* Function name: do_list
* Description  : This function allows people to list their (major) guilds.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int
do_list(string str)
{
   if (str != "guilds")
      {
      notify_fail("List what? Your guilds?\n");
      return 0;
   }
   
   str = this_player()->list_major_guilds();
   
   if (strlen(str))
      {
      write("You are a member of the following major guilds:\n" + str);
   }
   else
      {
      write("You are not a member of any major guild.\n");
   }
   
   return 1;
}

/*
* Function name: request
* Description  : Members who have lost their armband, may get it back here.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int
request(string str)
{
   object tp = this_player();
   
   if (str != "armband")
      {
      notify_fail("Request what? A new armband?\n");
      return 0;
   }
   
   if (!IS_MEMBER(tp))
      {
      write("You are not a member of this guild. You have no right to a " +
         "armband.\n");
      return 1;
   }
   
   if (objectp(present(ARMBAND_ID, tp)))
      {
      write("You already have a armband. You don't need two.\n");
      return 1;
   }
   
   setuid();
   seteuid(getuid());
   
   clone_object(ORC_RACE_GUILD_ARMBAND)->move(tp, 1);
   
   write("A brand new armband pops out of the hole in the wall. You catch it " +
      "and light it immediately. Then you relax and take a long drag.\n");
   say(QCTNAME(tp)  + " catches the armband that pops out of the hole in the " +
      "wall and lights it immediately.\n");
   
   return 1;
}

/*
* Function name: remove_player_changed_race
* Description  : Whenever a member changes his/her race (s)he is
*                mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void
remove_player_changed_race(object tp)
{
   tp->catch_msg("\nYou are no longer a orc. Therefore you do not " +
      "belong in the " + ORC_RACE_GUILD_NAME + " any more. You " +
      "are being expelled from the guild. Your armband is removed.\n");
   
   lower_skill(tp);
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
      tp->query_race_name() + ") was kicked out.\n");
}

/*
* Function name: remove_player_low_alignment
* Description  : Whenever the alignment of a player is too low, the player
*                is mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void
remove_player_low_alignment(object tp)
{
   tp->catch_msg("\nEvil is not something a orc should be. Therefore " +
      "you do not belong in the " + ORC_RACE_GUILD_NAME + " any more. " +
      "You are being expelled from the guild. Your armband is removed.\n");
   
   lower_skill(tp);
   
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
      tp->query_alignment() + ") was kicked out.\n");
}

/*
* Function name: leave_inv
* Description  : Called to remove the guild support if it is stuck.
   * Arguments    : object obj - the leaving object.
*                object to  - the new destination of the object.
*/
nomask public void
leave_inv(object obj, object to)
{
   ::leave_inv(obj, to);
   
   gs_leave_inv(obj, to);
}

/*
* Stuff for meditation.
*/

/*
* Function name: gs_hook_start_meditate
* Description  : Gives a nice description when someone starts to meditate.
*/
nomask public void
gs_hook_start_meditate()
{
   write("Sitting down on the floor, you let the tranquil surroundings have " +
      "their effect on you. You close your eyes and find your mind floating " +
      "away from your body. Finally, you become as relaxed as possible and " +
      "feel yourself able to \"estimate\" your different preferences for " +
      "concentration and \"set\" them to new values if desired. To go back " +
      "to the world outside, all you have to do is \"rise\".\n");
   say(QCTNAME(this_player()) + " sits down in order to meditate.\n");
}

/*
* Function name: gs_hook_rise
* Description  : Gives a nice description when someone is done meditating.
*/
nomask public void
gs_hook_rise()
{
   write("Having reached a new peace with yourself, you feel relaxed and " +
      "ready to conquer the world. You open your eyes and stand up.\n");
   say("Looking quite relaxed indeed, " + QTNAME(this_player()) + " opens " +
      this_player()->query_possessive() + " eyes and stands up.\n");
}

/*
* Function name: gs_hook_already_meditate
* Description  : Gives a nice message when someone tries to meditate
*                when (s)he is already mediating.
*/
nomask public int
gs_hook_already_meditate()
{
   write("It is not possible to come to an even higher level of meditation. " +
      "Since you are already meditating, you can now \"estimate\" your " +
      "different preferences for concentration and \"set\" them to new " +
      "values if you please. To relax and get back to the outside world, " +
      "just \"rise\".\n");
   return 1;
}

/*
* Function name: gs_hook_catch_error
* Description  : Gives a friendly error message when someone gives the
*                wrong command while meditating.
*/
nomask public int
gs_hook_catch_error(string str)
{
   write("It is not possible to do that in your current state. Since you are " +
      "meditating, you can only \"estimate\" your different preferences for " +
      "concentration and \"set\" them to new values if you please. To relax " +
      "and get back to the outside world, just \"rise\".\n");
   return 1;
}

/*
* This section takes care of the member administration.
*/

/*
* Function name: query_is_birthday
* Description  : This function determines whether it is the birthday of
*                the player.
* Arguments    : string - the name of the player.
* Returns      : int    - true if it is the players birthday.
   */

/*
public int
query_is_birthday(string name)
{
   
   return 0;
   if(((time() - members[name][MEMBERS_TIME]) % INTERVAL) <= INTERVAL)
      {
      return 1;
   }
   
   return 0;
}

*/

/*
* Function name: query_family_name
* Description  : Query the family name of a player.
* Arguments    : string - the name of the player.
* Returns      : string - the family name.
*/
public string
query_family_name(string name)
{
   if (!members[name])
      {
      return "";
   }
   
   return members[name][MEMBERS_FAMILY];
}


/*
* Function name: test_members
* Description  : At the first of the month, we test whether all members
*                listed are still valid. Ie. players who have quit will
*                be kicked out of the list.
*/
nomask static void
test_members()
{
   string *names = m_indices(members);
   int    index = -1;
   int    size = sizeof(names);
   
   setuid();
   seteuid(getuid());
   
   while(++index < size)
   {
      if (!(SECURITY->exist_player(names[index])))
         {
         log_guild(ctime(time()) +
            sprintf(" %-11s is no longer a player. -> removed.\n",
               capitalize(names[index])));
         
         members = m_delete(members, names[index]);
         }
   }
   
   save_object(ORC_RACE_GUILD_SAVE);
}

/*
* Function name: report_families
* Description  : This object generates a list of the number of members
*                per family.
* Returns      : mapping - indices are the family names, values the
*                          numbers of members.
*/
public nomask mapping
report_families()
{
   int     index = -1;
   mapping report = ([ ]);
   string  *names = m_indices(members);
   int     size = sizeof(names);
   
   while(++index < size)
   {
      report[members[names[index]][MEMBERS_FAMILY]]++;
   }
   
   return report;
}

/*
* Function name: list_family
* Description  : It is possible to list all members of a certain family.
* Arguments    : string family - the family to list.
* Returns      : string * - the members of the family.
*/
public nomask string *
list_family(string family)
{
   string *names = m_indices(members);
   int    index = -1;
   int    size = sizeof(names);
   string *result = ({ });
   
   while(++index < size)
   {
      if (members[names[index]][MEMBERS_FAMILY] == family)
         {
         result += ({ names[index] });
         }
   }
   
   return result;
}

/*
* The families-command can be used to print statistics on members of
* the guild.
*/
int
families(string str)
{
   int    scrw;
   int    index;
   int    size;
   string *names;
   string date;
   
   if (!strlen(str))
      {
      write("The command \"tribes\" can be used to find information " +
         "on the members of this guild. You can \"tribes list\" to " +
         "list all members of the guild. \"tribes size\" will list the " +
         "number of members per family. The command \"tribes " +
         "<tribe>\" prints a pedigree of that tribe.\n" +
         "In the guild, you will find the following tribes:\n" +
         COMPOSITE_WORDS(titles) + ".\n");
      return 1;
   }
   
   if (!m_sizeof(members))
      {
      notify_fail("No members of the " + ORC_RACE_GUILD_NAME +
            " are registered.\n");
      return 0;
   }
   
   scrw = this_player()->query_prop(PLAYER_I_SCREEN_WIDTH);
   scrw = (scrw ? (scrw - 5) : 75);
   
   if (str == "list")
      {
      names = m_indices(members);
      index = -1;
      size  = sizeof(names);
      
      while(++index < size)
      {
         names[index] = capitalize(names[index] + " " +
            members[names[index]][MEMBERS_FAMILY]);
       }
      
      write("The following players are a member of the " +
         ORC_RACE_GUILD_NAME + ".");
      write(sprintf("\n%-*#s\n", scrw,
            implode(sort_array(names), "\n")));
      return 1;
   }
   
   if (str == "size")
      {
      mapping list = report_families();
      names = ({ });
      index = -1;
      while(++index < NUM_TITLES)
      {
         names += ({ sprintf("%-*s %3d", LONGEST_NAME,
                  titles[index], list[titles[index]]) });
       }
      
      write("The following table shows the number of members per tribe:");
      write(sprintf("\n\n%-*#s\n", scrw, implode(names, "\n")));
      return 1;
   }
   
   str = capitalize(str);
   if (member_array(str, titles) == -1)
      {
      write("No such tribe, \"" + capitalize(str) + "\". Do " +
         "\"tribes\" without arguments for the syntax.\n");
      return 1;
   }
   
   names = list_family(str);
   
   if (!sizeof(names))
      {
      write("No members of the " + ORC_RACE_GUILD_NAME +
         " in the tribe " + str + ".\n");
      return 1;
   }
   
   index = -1;
   size  = sizeof(names);
   names = sort_array(names, "sort_age", this_object());
   
   while(++index < size)
   {
      date = ctime(members[names[index]][MEMBERS_TIME]);
      names[index] = sprintf("%-11s (%-6s %-4s)", names[index],
         date[4..9], date[20..23]);
   }
   
   write("The following members are a member of the tribe " +
      str + ":\n");
   write(sprintf("\n%-*#s\n", scrw, implode(names, "\n")));
   
   return 1;
}

/*
* Function name: sort_age
* Description  : This function is used to sort the members of a
*                family based on the date they joined.
* Arguments    : string name1 - the name of the first player.
*                string name2 - the name of the second player.
* Returns      : int - the normal sort-return.
*/
int
sort_age(string name1, string name2)
{
   if (members[name1][MEMBERS_TIME] < members[name2][MEMBERS_TIME])
      {
      return -1;
   }
   
   if (members[name1][MEMBERS_TIME] == members[name2][MEMBERS_TIME])
      {
      return 0;
   }
   
   return 1;
}

/*
* Function name: cap
* Description  : Map-function to capitalize strings.
* Arguments    : string str - the string to capitalize.
* Returns      : string - the capitalized string.
*/
string
cap(string str)
{
   return capitalize(str);
}
