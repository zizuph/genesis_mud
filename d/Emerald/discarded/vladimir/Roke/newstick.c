inherit "/std/object";
inherit "/d/City/quetzl/open/hardparser";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/varl/atuan/cape/guild/default.h"

#define RUMOUR_SOUL "/d/Rhovanion/common/shield_guild/rumour_soul"
#define MESSAGER    "/d/Roke/vladimir/messager"
#define GROUPS      ({"all","travellers","humans","elves","dwarves", \
                        "gnomes","hobbits","goblins"})
#define REALY_FOR  ({"all","travellers","human","elf","dwarf", \
                        "gnome","hobbit","goblin"})

void
create_object()
{
        set_name("stick");
     add_name("_stickly_");
        set_short("long crooked stick");
        set_long("This is what weary travellers use to rest their"
                + " tired bodies while walking. Carved into the"
                + " top portion of the stick is a symbol of two"
                + " crossed axes over a map of the world.\n");
        add_prop(OBJ_I_WEIGHT, 20);
        add_prop(OBJ_I_VOLUME, 5);
        add_prop(OBJ_I_VALUE, 0);
        add_prop(OBJ_M_NO_DROP,1);
}

void
init()
{
   ::init();
   add_action("do_leave_message","make");
   add_action("trav_help", "help");
   add_action("rumour_help","help");
    add_action("begin", "tnew");
   add_action("emote_help","ehelp");
    add_action("name", "tname");
    add_action("forward", "tforward");
   set_alarm(1.0, 0.0, "get_me_soul", TP);
}

string
query_auto_load() { return MASTER + ":"; }

void
get_me_soul(object ob)
{
  int i;
  string *souls;

  seteuid(getuid());
  souls = ob->query_cmdsoul_list();
  for (i = 0; i < sizeof(souls); i++)
    ob->remove_cmdsoul(souls[i]);

  ob->add_cmdsoul(TRAV_SOUL);
  ob->add_cmdsoul(RUMOUR_SOUL);

  for(i = 0; i < sizeof(souls); i++)
    if((souls[i] != TRAV_SOUL) && (souls[i] != RUMOUR_SOUL))
      ob->add_cmdsoul(souls[i]);
  ob->update_hooks();
}

int
do_leave_message(string str)
{ 
  int i;
  string *tmp, mess, who;
  object messager, room;

  notify_fail("Leave what?\n");
  if(!str) return 0;

  tmp = explode(str, " for ");
  if((i=sizeof(tmp)) < 2) return 0;

  who = lower_case(tmp[i-1]);

  i = strlen(str) - (strlen(who) + 6);
  mess = str[0..i];

  if(explode(mess, " ")[0] != "rumour") return 0;

  notify_fail("You must give the rumour too.\n");
  if((i=strlen(mess))<8) return 0;

  mess = mess[7..(i-1)];

  notify_fail("There is no player called '"+capitalize(who)+"'.\n");
  if((member_array(who, GROUPS) == -1) &&
     !("/secure/master"->exist_player(who)))
    return 0;

  i = 0;
  notify_fail("You do not feel right leaving a message here.\n");
  room = environment(TP);
  if(function_exists("config_default_trade", room) == "/lib/trade")
    i = 1;
  if(present("bulletin board", room))
    i = 1;
  if(present("_reader_", TP))
    i = 1;
  if(!i) return 0;

  notify_fail("You can't concentrate enough for leaving a rumour.\n");
  if(TP->query_mana() < 10) return 0;
  TP->add_mana(-5);


  seteuid(getuid());

  messager = present("_traveler_messager_", environment(TP));
  if(!messager)
  {
    messager = clone_object(MESSAGER);
    messager->move(environment(TP));
  }

  if((i = member_array(who, GROUPS)) != -1) who = REALY_FOR[i];

  messager->set_messager(TP->query_real_name(), who, mess);

  mess = ({"You lean over and whisper a rumour.\n",
           "You let out a rumour, watching it spread around the room.\n",
           "You start talking to someone.\n",
           "You start a conversation.\n",
           "You leave a message for someone.\n", })[random(5)];

  write(mess);
  say(QCTNAME(TP)+" mumbles something under "+TP->query_possessive()+" "+
        "breath.\n", TP);
  return 1;
}

int
trav_help(string str)
{
    string filename;

    if (str == "traveller")
        return 0;
    filename=ATUAN+"cape/guild/thelp";
    if (file_size(filename)>0) {
        this_player()->more(filename);
        return 1;
    }
    notify_fail("No help on that subject available.\n");

    return 0;
}


int
emote_help(string str)
{
  if(str == "emote")
  {
    write( "Welcome to the Traveller emote making system. This\n"
+ "is a way that you, a Traveller, can contribute to\n"
+ "your guild. There only a few rules. No obscenity,\n"
+ "racist remarks, no sexism, basically if you have\n"
+ "nothing nice to say, don't say anything at all. All\n"
+ "suggested emotes are subject to the guild master's\n"
+ "approval. The emote maker leads you through a series\n"
+ "of questions and prompts that are harmles, and fun.\n"
+ "Remember the rules, and have fun!\n"
+ "\n"
+ "Getting started:\n"
+ "At any point you may decide to abort your emote by\n"
+ "using '~q'. Type 'tnew' to begin your emote. You\n"
+ "will be asked a series of questions. Some questions\n"
+ "ask for descriptions of what you see, the target\n"
+ "sees, and what the by standers see. When you want\n"
+ "to use a gender related word be sure to use:\n"
+ "\n"
+ "   #he#   -- For 'he' and 'she'\n"
+ "   #He#   -- For 'He' and 'She'\n"
+ "   #him#  -- For 'him' and 'her'\n"
+ "   #Him#  -- For 'Him' and 'Her'\n"
+ "   #his#  -- For 'his' and 'her'\n"
+ "   #His#  -- For 'His' and 'Her'\n"
+ "\n"
+ "If you decided to use and adverb with your emote,\n"
+ "you can make the adverb apear by using '#adv#'.\n"
+ "When it is desireable to have the user's name apear\n"
+ "on a line, use '#name#'. Finally, to have your\n"
+ "target's name apear use '#targ#'.\n"
+ "REMEMBER TO ALWAYS USE PUNCTUATION!\n"
+ "\n"
+ "After your emote is finished, you must name it. Do\n"
+ "this by typing 'tname <emotename>' after the\n" 
+ "emotemaker tells you you are ready. Then, after you\n"
+ "have named it, use 'tforward' to submit it for\n"
+ "approval.\n"
+ "\n"
+ "Try things out a few times. Get used to the system.\n"
+ "Mail your guildmaster with any problems-suggestions-\n"
+ "questions. Happy emote making!\n");


    return 1;
  }
  return 0;
}


int
rumour_help(string str)
{
  if((str == "rumour") || (str == "rumours"))
  {
    write("You have two possibilities:\n"+
        "    plant rumour <rumour> to <who>\n"+
        "    make rumour <rumour> for <name>\n"+
     "Try 'help plant rumour' and 'help make rumour' for more info.\n");
    return 1;
  }
  if(str == "make rumour")
  {
    write("The syntax for making a rumour is:\n\n"+
        "       make rumour <rumour> for <name>\n\n"+
        "You can leave rumour in any pub, shop, bank, post, "+
        "near public board or another place where "+
        "is usually big gathering of people. Rumour will stay in this "+
        "place where player you adressed it will be able to pick it up. "+
        "You can adress it to a single player or to the "+
        COMPOSITE_WORDS(GROUPS)+". Naturally you have to "+
        "make a little mental effort to make this rumour.\n"+
        "\nHave fun!\n\n");
    return 1;
  }
  return 0;
}

public void
catch_emote(string arg, string name)
{
    reset_euid();
     write_file(ATUAN + "cape/guild/emotes/" + name + "." + this_interactive()->
        query_real_name(), arg);
}
