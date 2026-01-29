#pragma save_binary

inherit "/cmd/std/command_driver";

#include "/d/Rhovanion/defs.h"
#include <macros.h>

#define SHADOW  "/d/Rhovanion/common/shield_guild/rumour_sh"


/*
 * Function name: get_soul_id
 * Description  : Returns a proper name of the soul in order to get a nice
 *                printout. You should replace this function by your own.
 * Returns      : the name
 */
string
get_soul_id()
{
    return "Rumour soul";
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
    return ([
	"help"   : "rumour_help",
	"plant" : "do_rumour",
	 ]);
}

/*
 * Function name: query_cmd_soul
 * Description  : This is a command soul.
 * Returns      : 1
 */
int
query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * Here follows the actual functions. Please add new in alphabetical order.
 * **************************************************************************/

int
rumour_help(string str)
{
  if(str != "plant rumour") return 0;

  write("The syntax for planting a rumour is:\n\n"+
	"       plant rumour <rumour> to <who>\n\n"+
	"You can plant rumour into any living. Naturally you have to "+
	"make a mental effort with every creature you want to plant a "+
	"rumour. Of course the longer rumour the bigger effort you must "+
	"make so that it is remembered. For this you will be rewarded "+
	"by the chance to watch your rumour spread across the world.\n"+
	"Note that anyone can 'ask creature about rumours'. It is up to "+
	"you to remind other players about this possibility.\n"+
	"\nNote that <rumour> must not contain any abusive words and it "+
	"must not contain a name of a player either.\n"+
	"\nHave fun!\n\n"+
	"PS. Initially there will be many NPCs that will 'not be interested' "+
	"in the rumours. Please, if you feel that it should not be so leave "+
	"'idea'. One could expect that all shopkeepers, bartenders, ship "+
	"captains and similar NPCs on places with big trafic should be "+
	"interested in rumours.\n");
  return 1;
}

/*
 * This function returns true if message contains a name or potentially
 * offensive word exactly like in /secure/login.c
 *
 * returns 1 if potentially offensive
 */
int
it_is_unacceptable_message(string mess)
{
  int i;
  string *words = explode(mess, " ");
  string *offensive = ({ ".*fuck.*", ".*dick.*", ".*cunt.*", ".*arse.*", 
			".*shit.*", ".*pussy.*", ".*slut.*", ".*rape.*",
                   	".*fag.*", ".*penis.*", ".*hell.*", ".*bitch.*",
                   	".*suck.*", ".*clit.*", ".*peck.*", ".*cock.*",
                   	".*fart.*", "ass.*", ".*ass" });

  for (i = 0 ; i < sizeof(offensive) ; i++)
    if(sizeof(regexp(words, offensive[i]))) return 1;

  for(i=0; i<sizeof(words); i++)
    if("/secure/master"->exist_player(LOW(words[i]))) return 1;

  return 0;
}

object *
filter_bad_out(mixed list)
{
  object *tmp = ({ });
  int i;

  for(i=0; i<sizeof(list); i++)
    if ((!list[i]->query_npc() && !list[i]->query_wiz_level()) || 
	list[i]->query_prop(DO_I_TELL_RUMOURS))
      tmp += ({ list[i] });

  if(!sizeof(tmp))
    actor("You don't think that", list, (sizeof(list)>1 ? " are":" is")+
		" interested in your rumour.");
  return tmp;
} 

int
do_rumour(string str)
{
  string mess, from, *tmp;
  object *npc, shadow;
  int i, j;

  NF("Plant what?\n");
  if(!str) return 0;
  
  tmp = explode(str, " to ");
  if((i=sizeof(tmp)) < 2) return 0;

  from = tmp[i-1];

  j = strlen(str) - (strlen(from) + 5);
  mess = str[0..j];

  if(explode(mess, " ")[0] != "rumour") return 0;

  NF("You must give the rumour too.\n");
  if((i=strlen(mess))<8) return 0;
  
  mess = mess[7..(i-1)];
  npc = parse_this(from, "[the] %l ");

  if(!sizeof(npc))
  {
    NF("Plant rumour "+mess+" to whom?\n");
    return 0;
  }

  NF("This is unacceptable as a rumour.\n");
  if(it_is_unacceptable_message(mess)) return 0;

  npc = filter_bad_out(npc);
  NF("");
  if(!sizeof(npc)) return 0;

  NF("You can't concentrate on planting such a big rumour to so "+
	"many people.\n");
  i = (1 + (strlen(mess)/5)) * sizeof(npc);
  if(TP->query_mana() < (10+i)) return 0;

  TP->add_mana(-i);

  setuid();
  seteuid(getuid());

  mess = CAP(mess);
  from = TP->query_met_name();

  for(j=0; j<sizeof(npc); j++)
  {
    if(npc[j]->query_rumour_shadow())
      npc[j]->plant_rumour(mess, from, time());
    else 
    {
      shadow = clone_object(SHADOW);
      if(shadow && shadow->shadow_me(npc[j]))
      {
        if((i=npc[j]->query_no_of_rumours()) > (2+random(4)))
          npc[j]->remove_rumour(random(i));
        if(npc[j]->query_npc())
        {
          npc[j]->set_dont_answer_unseen(1);
          npc[j]->add_ask(({"rumours","about rumours","about the rumours"}), 
			"@@answer_rumours:"+file_name(shadow)+"@@");
        }
        npc[j]->plant_rumour(mess, from, time());
      }
    }
  }
  target(" tells you: "+mess+".\nVery interesting indeed!", npc);
  actor("You plant rumour in", npc);
  all2act("convinced", npc, " about something.");
  return 1;
}

