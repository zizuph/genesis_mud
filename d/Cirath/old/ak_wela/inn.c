
/*
 * This is a Common Room, complete with tables,
 * chairs and local table conversations and a sample
 * local table emote.
 * Coding by Asmodean, started 4/29/1995
 * Modified by Xarguul (formerly Asmodean) on 5/22/1995
 *
 * 
 * NOTE : To inherit this file is quite easy, this is what a sample
 * inherit would look like:
 * (includes)
 * inherit "/doc/examples/new/room/common_room";
 *
 * create_room()
 * {
 *   ::create_room();
 *   set_short("The Xarguul is the niftiest Inn Common Room");
 *   set_long("This is the Common Room of the 'Xarguul is the "+
 *            "niftiest Inn'\n\n");
 *   add_exit("/d/Genesis/wiz/post","south");
 * }
 *
 * THIS IS ONLY AN EXAMPLE  (Standard Disclaimer)
 *
 * Also, if the drink prices are too high, remove them and
 * add your own drinks, and re-define the read() function.
 */


inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"
#include <composite.h>
#include "/d/Immortal/pale/paladin/hold.h"



inherit "/std/room";
inherit "/lib/pub";


#include <language.h>
#include <money.h>

int get_my_table_num();
string dump_tables();
string dump_chairs();
/* I have to declare do_stand because I call it from another
 * function --above-- it in the code.
 */
int do_stand(string str);

/*
 * Global variables to the room related to people in chairs.
 */

/* Table #s range from 0-6 */
#define MAXTABLES 7

static int *totalseats = ({ 4, 4, 4, 4, 6, 6, 2});
/* TableContents begins as empty, eventually will have the
 * player objects stored in them, for use in tablewhos and
 * table emotes and conversations.
 */
static mixed *tablecontents = ({
  ({}),({}),({}),({}),({}),({}),({}) });

void
create_room()
{
    set_short("The Smiling Shark Inn");
    set_long(	"You have entered the Smiling Shark. The smell "+
		"of the sea mixes with the smoke from the fireplace. "+
		"There are several cushions around low tables in this room, "+
		"separated by rice-paper walls. This allows people to  "+
		"have private conversations. An aroma of spices and sea-food "+
		"lies in the air, and you can hear the cooks shouting at each "+
		"other in the kitchen.\n"+
                "There is a menu behind the bar.\n\n");
    
  
    add_item("bar", "The bar is made of some hard dark wood, which "+
	     "you suspect is mahogony. "+
	     "There is a menu behind it.\n");
    add_item("menu", "The menu is etched into a bone plaque attached "+
	     "to the wall behind the "+
	     "bar. It uses symbols of various kinds, as most people"+
             "here are illiterates.\n");

    /* The Following add_item contains a VBFC call to dump_chairs, 
     * which is a function that uses write() to print all the
     * chairs and which ones are empty. For more info on VBFC,
     * check out the manual.
     */

    add_item("cushions",
	     "They are cushion chairs, which matches the low tables "+
	     "perfectly.\n@@dump_chairs@@"); 
    /* 
     * The VBFC here uses write() to print out who's sitting at
     * which tables.
     */

    add_item("tables", "The tables are very low , they "+
	     "are obviously made to sit cross-legged by as they are "+
              "far to low to have room for your legs under. "+
              "Try 'tablehelp' for more info."+
		"\n@@dump_tables@@");
    add_item(({"fireplace","hearth"}),
	     "The fireplace is an open area in the middle of the room. "+
	     "Over the open fire different meals are being prepared. A "+
	     "chef is standing by the fire, watching the meals, so that "+
	     "they won't start burning.\n");

    add_cmd_item("menu", "read", "@@read");
    add_cmd_item("meal","get","As you try to steal a meal from the fire "+
                 "the chef stops you and frowns at you angrily.\n");

    add_item("chef","The chef stands by the fire, watching the meals.\n");

    add_exit(AK_WELA_DIR+"bunks","up","@@block",2);
    add_exit(AK_WELA_DIR+"szun_moon2","south",0,2);
    INSIDE;

    /*
     * The prices below --should-- be accurate, but they were originally
     * coded for the Immortal domain, so check them before using.
     */

    add_drink( ({ "beer", "beers", "large", "large beer", "large glass of beer",
	"glass of beer" }),
         "beer","large",250,10,100,0,0,
        "A mug of thurst-quenching brew, which is probably imported.\n");
    add_drink( ({"sake", "glasses of sake", "glass of sake","sakes"}),
         "sake","fine",100,15,150,0,0,
        "A glass of fine sake, strong rice wine. The locals seem to"+
	"like this drink.\n",0);
    add_food( ({ "soup","sharkfin soup" }),
        "sharkfin","soup",50,120,"bowl of sharkfin soup","bowls of sharkfin soup",
        "A bowl of sharkfin soup, delicately spiced. It smells wonderful.\n",0);
    add_food( ({"roll","spring roll"}),
        "roll", "spring", 25,80,"small spring roll",
        "small spring rolls",
        "A small spring roll, stuffed with minced meat and some vegetables. "+
	"It smells wonderful, and you can't wait to sink your teeth "+
	"into it.\n",0);
    add_food( ({ "grill","platter","large grill platter",
                 "large platter"}),
        "grill platter","large",150,225,"large grill platter",
        "large grill platters",
        "This is the house special, several types of meat, both sea-food and "+
	"others, mixed with vegetables and roasted over the open fire.\n",0);

    /*
     * version of create room. See top of document for info on
     * how to inherit this file.
     */
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    /* If you do not call the previous instance of init if you've
     * re-defined init() (which we've done here), then NO useful
     * commands will work in a room at all! 
     */

    ::init();

    init_pub();
    add_action("my_rent","rent");
    add_action("do_sit","sit");
    add_action("do_stand","stand");
    add_action("table_say","tablesay");
    add_action("table_who","tablewho");
    add_action("table_help","tablehelp");
    add_action("table_smile","tablesmile");
}

leave_inv(object ob, object to)
{
   if (ob->query_prop("_is_sitting_down_AsMo_"))
    {
      tablecontents[get_my_table_num()]-= ({ ob });
      ob->remove_prop("_is_sitting_down_AsMo_");
    }
   ::leave_inv(ob,to);
}

/* pub_hook_player_buys is a function in /lib/pub, called
 * each time a player buys something. I have re-defined it
 * so that if the player is standing, he/she gets a different
 * message than sitting at a table (a waiter brings food/drink
 * to the tables)
 */

void
pub_hook_player_buys(object ob, int price)
{
  if (TP->query_prop("_is_sitting_down_AsMo_"))
    {
      write("A waiter takes your order on "+ob->short()+" bows and runs "+
	    "off and fetches it for you. You pay him "+price+" coppers for it.\n");
      tell_room(TO,"A waiter delivers "+ob->short()+" and to "+
                QCTNAME(TP)+"'s table, who pays him "+price+" coppers for it.\n",TP);
    }
  else
    {
      write("You give the bartender "+price+" coppers, and order "+
	    ob->short()+" which you promptly get.\n");
      tell_room(TO,QCTNAME(TP)+" gives "+price+" coppers to the bartender "+
               "and is promptly served "+ob->short()+".\n",TP);
     }
}

/*
 * The ONLY reason I used a VBFC instead of typing it, is
 * because it seems clearer to me to have this big, bulky
 * menu in its own function.
 *
 * NOTE : These prices were originally for the Immortal domain,
 * so if you are inheriting this, not using a modified version,
 * please double-check these. If you want a new menu, simply
 * re-define the 'read' function in your common room.
 */

int
read(string str)
{
    write(
	"                  Smiling Shark menu\n"+
        ".--------------------------------------------------.\n" +
        "| o                                              o |\n" +
        "|                                                  |\n" +
        "|   Mug of Beer               1gc                  |\n" +
        "|                                                  |\n" +
        "|   Sake                      1gc   5 sc           |\n" +
        "|                                                  |\n" +
        "|   Spring roll                     5 sc           |\n" +
        "|                                                  |\n" +
        "|   Sharkfin soup             1 gc  2 sc           |\n" +
        "|                                                  |\n" +
        "|   Large grill platter       2gc   2 sc  5 cc      |\n" +
        "|                                                  |\n" +
        "|   Rent a room for           2gc                  |\n" +
        "|                                                  |\n" +
        "|  o                                              o|\n" +
        "`--------------------------------------------------'\n\n");
    return 1;
}




/*
 * This is a filter function which filters out people
 * who are not sitting down (or other way around depending
 * on how you use it. All people sitting down have the
 * property '_is_sitting_down_AsMo_'
 */

public int
prop_filt(object player)
{
    if (!player->query_prop("_is_sitting_down_AsMo_"))
        return 0;
    return 1;
}

/*
 * Called when a player types 'sit at table x'
 * This performs all modifications to the tablecontents
 * array and properties of players
 */

int
do_sit(string str)
{
  string *argarr;
  int tablenumber;

  if (TP->query_prop("_is_sitting_down_AsMo_")==1)
    {
      NF("You're already sitting down!\n");
      return 0;
    }
 
  if (!str)
   {
    NF("Try 'sit at table #'. For more info on the tables, "+
       "Use 'tablehelp'\n");
    return 0;
   }
  argarr=explode(str," ");
  if (sizeof(argarr)<2)
   {
    NF("What are you trying to do? Try 'tablehelp' if you're "+
       "confused.\n");
    return 0;
   }
  if ( (argarr[0]!="at") && (argarr[1]!="table") )
    {
      NF("Sit Where?\n");
      return 0;
    }
  if (sizeof(argarr)!=3) 
    {
     NF("Sit at which table?\n");
     return 0;
    }
  tablenumber=atoi(argarr[2]);
  if ( (tablenumber < 0) || (tablenumber > MAXTABLES) )
    {
      NF("You can't seem to find that particular table here.\n");
      return 0;
    }
  if (sizeof(tablecontents[tablenumber-1])==totalseats[tablenumber-1])
    {
      NF("There are no more cushions by that table.\n");
      return 0;
    }
  tell_room(TO,QCTNAME(TP)+" sits down in on a cushion at a table.\n",TP);
  TP->catch_msg("You sit down at table " + tablenumber + ".\n");
  TP->add_prop("_is_sitting_down_AsMo_",1);
  TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting at table "+tablenumber);
  tablecontents[tablenumber-1]+=({ TP });
  return 1;
}

/*
 * Called when people stand up
 */

int
do_stand(string str)
{
  int i;

  if (TP->query_prop("_is_sitting_down_AsMo_")!=1)
    {
      NF("You're not sitting down!\n");
      return 0;
    }
  tell_room(TO,QCTNAME(TP)+" rises froom "+TP->query_possessive()+" cushion. "+
            TP->query_pronoun()+" rubs "+TP->query_possessive()+ " behind absentmindedly and stands up.\n",TP);
  TP->catch_msg("You rise from your cushion.\n");
  TP->remove_prop("_is_sitting_down_AsMo_");
  TP->remove_prop(LIVE_S_EXTRA_SHORT);
  for (i=0;i<MAXTABLES;i++)
    {
      if ( (member_array(TP,tablecontents[i]))!=-1)
	tablecontents[i]-=({TP});
    }
    return 1;
  
}

/*
 * This was mentioned before, this is done inside a VBFC
 * to print out who is sitting at which table
 */

string
dump_tables()
{
   int i;

   for (i=0; i<MAXTABLES; i++)
     {
      write("Seated at table "+LANG_WNUM(i+1)+": ");
      if (sizeof(tablecontents[i]))
	{
         write(COMPOSITE_LIVE(tablecontents[i])+"\n");
       }
      else
	write("No one.\n");
    }
   return "";
 }

/*
 * Function to carry on local conversations by typing
 * 'tablesay <msg>'
 */

int
table_say(string str)
{
  int i;
   int mytable;
  int j;

  if (!str)
    {
      NF("Say What?\n");
      return 0;
    }
  if (!TP->query_prop("_is_sitting_down_AsMo_"))
    {
      NF("You're not sitting at a table.\n");
      return 0;
    }
  for (i=0; i<MAXTABLES; i++)
    {
      if ( (member_array(TP,tablecontents[i]))!=-1)
	{
          mytable=i;
	  for (j=0; j<sizeof(tablecontents[i]); j++)
	    {
	       if (tablecontents[i][j]->query_real_name()!=
		   TP->query_real_name())
		 {
		   tablecontents[i][j]->catch_msg(QCTNAME(TP)+" leans "+
			"across the table and says: "+str+"\n");
		 }
	     }
	}
    }
  TP->catch_msg("You lean across the table and say: "+str+"\n");
  tell_room(TO,QCTNAME(TP)+" murmurs something to those at "+
            TP->query_possessive()+" table.\n",tablecontents[mytable]);
  return 1;
}

/*
 * Lists people sitting at your table.
 */

int
table_who(string str)
{
  object *tmparr;
  int i;

  if (!TP->query_prop("_is_sitting_down_AsMo_"))
    {
      NF("You're not sitting at a table.\n");
      return 0;
    }
  for (i=0; i<MAXTABLES; i++)
    {
      if ( (member_array(TP,tablecontents[i]))!=-1)
	{
          tmparr=tablecontents[i];
          tmparr-= ({ TP });
          if (!sizeof(tmparr)) {
		write("There is no one else at the table.\n"); 
		return 1;
	}
	  write("You glance across the table and see:\n"+
           COMPOSITE_LIVE(tmparr)+"\n");
	}
    }
  return 1;
}

/*
 * This is outputted as the
 * 'tablehelp' command
 */
int
table_help(string str)
{
  write("\n"+
	".-------------------------------------.\n"+
	"| o                                 o |\n"+
	"|                                     |\n"+
	"| sit at table x                      |\n"+
	"| stand                               |\n"+
	"| tablesay <msg> - Talk to your Table |\n"+
        "| tablewho - look at your table       |\n"+
	"| tablehelp - this message            |\n"+
	"|                                     |\n"+
	"| o                                 o |\n"+
	"`-------------------------------------'\n\n");
  return 1;
}

/*
 * This is a utility function which returns the
 * table index number in the array of tables which
 * you are sitting at.
 */

int
get_my_table_num()
{
  int i;
  
  for (i=0;i<MAXTABLES;i++)
    {
      if ( (member_array(TP,tablecontents[i]))!=-1)
	return i;
    }
  return -1;
}

/*
 * table-local smile emote
 */
int
table_smile(string str)
{
  
  int n;
  int i;
  int sz;
  object *tmparr;

  if (!TP->query_prop("_is_sitting_down_AsMo_"))
    {
      NF("You're not sitting at a table!\n");
      return 0;
    }
  n = get_my_table_num();
  if (n==-1)
    {
      NF("Hmm..Can't seem to figure out what the hell's going on here.\n"+
	 "Notify the spiffy Mansho ASAP.\n");
      return 0;
    }
  tmparr=tablecontents[n];
  tmparr-= ({ TP });
  sz = sizeof(tmparr);
  if (!sz)
    {
      NF("There is no one else at the table.\n");
      return 0;
    }
  for (i=0; i<sz; i++)
    {
      tmparr[i]->catch_msg(QCTNAME(TP)+" smiles across the table.\n");
    }
  TP->catch_msg("You smile across the table.\n");
  return 1;
}

/*
 * Lists which chairs are empty and which are not
 */
string
dump_chairs()
{
  int i;
  int e;
  
  for (i=0;i<MAXTABLES;i++)
    {
      e = totalseats[i]-sizeof(tablecontents[i]);
      write("Table "+LANG_WNUM(i+1)+" has "+totalseats[i]+" cushions. "+
	    "( "+e+" are empty.)\n");
    }
  return "";
}

int block()
{
	if(!(present("_smiling_shark_key",TP)))
	{
		say(QCTNAME(TP)+" heads for the stairs but "+
                "then head back as "+TP->query_pronoun()+" forgot to buy a key.\n");
                write("You start heading for the stairs, but "+
                "then you remember that you forgot to buy a key and "+
                "head back.\n");
	return 1;
	}

write("You head up the stairs, and find an unoccupied room.\n");
return 0;
}

int
my_rent(string s)
{
	if(s!="room")
		{
		NF("Rent what ?\n");
		return 0;
		}
	if(TOTAL_MONEY(TP)<200)
		{
		NF("You can't afford a key.\n");
		return 0;
		}
	MONEY_ADD(TP,-200);
	write("You buy a key to a room.\n");
	say(QCTNAME(TP)+" buys a key to a room.\n");
	setuid();
        seteuid(getuid());
	TP->add_prop("_have_bought_key",1);
        clone_object(AK_WELA_DIR+"obj/sharkkey.c")->move(TP);
return 1;
}

		












