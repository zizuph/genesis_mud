/**********************************************************************
 * - special_table.c                                                - *
 * - This gives a pub feeling to area so one can sit at a table and - *
 * - speak with each other at a certain table.                      - *
 * - Created by Damaris@Genesis 02/2005                             - * 
 * -                                                                - * 
 * - This was inspired by:                                          - *
 * - The Common Room, complete with tables,                         - *
 * - chairs and local table conversations and a sample              - *
 * - local table emote.                                             - *
 * - Coding by Asmodean, started 4/29/1995                          - *
 * - Modified by Xarguul (formerly Asmodean) on 5/22/1995           - *
 * - Updated for the Shire by Finwe January 2002                    - *
 **********************************************************************/

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "/d/Khalakhor/sys/defs.h"
inherit "/d/Khalakhor/std/room";

int get_my_table_num();
string dump_tables();
string dump_chairs();
public string figure_out_desc();
int do_stand(string str);
 
/**********************************************************************
 * - Global variables to the room related to people in chairs.      - *
 **********************************************************************/
 
/* Table #s range from 0-6 */
#define MAXTABLES 7

static int *totalseats = ({ 5, 5, 5, 6, 8, 8, 10});

/**********************************************************************
 * - TableContents begins as empty, eventually will have the player - *
 * - objects stored in them, for use in tablewhos and table emotes  - *
 * - and conversations.                                             - *
 **********************************************************************/
static mixed *tablecontents = ({
  ({}),({}),({}),({}),({}),({}),({}) });
 
void
create_khalakhor_room()
{
    set_short("Dining room");
    set_long("    This is a simple dining room for guests of the "+
      "Inn to enjoy. Many guests come and enjoy sitting down "+
      "at a table while resting their travel weary legs. "+
      "Conversations florish once a good meal is placed before them.\n");
    add_item(({"area", "dining room", "room", "pub", "inn"}), query_long);
    add_item(({"bar"}),
      "The bar is made of rare red oak and there is a menu displayed "+
      "upon it.\n");
    add_item(({"menu"}),
      "The menu is scribed into a golden plaque attached "+
        "to a piece of fine mahogany hanging on the wall behind the "+
        "bar.\n");
        
/**********************************************************************
 * - The Following add_item contains a VBFC call to dump_chairs,    - *
 * - which is a function that uses write() to print all the chairs  - *
 * - and which ones are empty.                                      - *
 * - For more info on VBFC, check out the manual.                   - *
 **********************************************************************/
    add_item("chairs",
        "They are made out of wood as is the rest of the "+
        "place.\n@@dump_chairs@@"); 
/**********************************************************************
 * - The VBFC here uses write() to print out who's sitting at       - *
 * - which tables.                                                  - *
 **********************************************************************/
    add_item("tables", "The tables are made of a fine oak. The "+
        "edges and legs are decorated with exquisite hand-carved "+
        "scrollwork. Try 'tablehelp' for more info."+
        "\n@@dump_tables@@");
 
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(ROOM_I_INSIDE, 1);
} 
 
void
init_table()
{
    add_action("do_sit","sit");
    add_action("do_stand","stand");
    add_action("table_say","tablesay");
    add_action("table_say","sayt");
    add_action("table_who","tablewho");
    add_action("table_who","whot");
    add_action("table_help","tablehelp");
    add_action("table_smile","tablesmile");
    add_action("table_help","helpt");
    add_action("table_smile","smilet");

}

void 
leave_inv(object ob, object to)
{
   int tn;
   if (ob->query_prop("_is_sitting_down_AsMo_"))
    {
      if ((tn = get_my_table_num()) != -1)
      {
      	  tablecontents[tn]-= ({ ob });
      	  ob->remove_prop("_is_sitting_down_AsMo_");
      	  remove_my_desc(TO);
      	  change_my_desc(figure_out_desc(),TO);
      }
    }
   ::leave_inv(ob,to);
}
 
 
/**********************************************************************
 * - CAUTION : This is where the code gets a bit nasty.             - *
 * -           This function decides what the extra desc looks like - *
 * -           for people sitting down in the room or not.          - *
 **********************************************************************/
 
public string
figure_out_desc()
{
    object *p;
   p = filter(all_inventory(TO),"prop_filt",TO);
    if (!sizeof(p))
        return "No one is sitting at any of the tables.\n";
    if (sizeof(p) == 1)
         return COMPOSITE_LIVE(p)+" is sitting at a table.\n";
   else
   return COMPOSITE_LIVE(p)+" are sitting at tables.\n";
}
 
/**********************************************************************
 * - This is a filter function which filters out people who are not - * 
 * - sitting down (or other way around depending on how you use it. - *
 * - All people sitting down have the property                      - * 
 * - _is_sitting_down_AsMo_                                         - *
 **********************************************************************/
 
public int
prop_filt(object player)
{
    if (!player->query_prop("_is_sitting_down_AsMo_"))
        return 0;
    return 1;
}
 
/**********************************************************************
 * - Called when a player types 'sit at table x'                    - *
 * - This performs all modifications to the tablecontents array and - *
 * - properties of players                                          - *
 **********************************************************************/
 
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
    if (!(tablenumber = LANG_NUMW(argarr[2])))
    {
        NF("You can't seem to find that particular table here.\n");
        return 0;
    }
/*
  tablenumber=atoi(argarr[2]);
 */
  if ( (tablenumber < 0) || (tablenumber > MAXTABLES) )
    {
      NF("You can't seem to find that particular table here.\n");
      return 0;
    }
  if (sizeof(tablecontents[tablenumber-1])==totalseats[tablenumber-1])
    {
      NF("There are no more chairs at that table.\n");
      return 0;
    }
  tell_room(TO,QCTNAME(TP)+" sits down in a chair at a table.\n",TP);
  TP->catch_msg("You sit down at table " + tablenumber + ".\n");
  TP->add_prop("_is_sitting_down_AsMo_",1);
  remove_my_desc(TO);
  change_my_desc(figure_out_desc(),TO);
  tablecontents[tablenumber-1]+=({ TP });
  return 1;
}
 
/**********************************************************************
 * -  Called when people stand up                                   - *
 **********************************************************************/
 
int
do_stand(string str)
{
  int i;
 
  if (TP->query_prop("_is_sitting_down_AsMo_")!=1)
    {
      NF("You're not sitting down!\n");
      return 0;
    }
  tell_room(TO,QCTNAME(TP)+" pushes "+TP->query_possessive()+" chair "+
            "away from the table and stands up.\n",TP);
  TP->catch_msg("You push your chair away from the table and stand up.\n");
  TP->remove_prop("_is_sitting_down_AsMo_");
  for (i=0;i<MAXTABLES;i++)
    {
      if ( (member_array(TP,tablecontents[i]))!=-1)
        tablecontents[i]-=({TP});
    }
  remove_my_desc(TO);
  change_my_desc(figure_out_desc(),TO);
  return 1;
  
}
 
/**********************************************************************
 * - This was mentioned before, this is done inside a VBFC          - *
 * - to print out who is sitting at which table                     - *
 **********************************************************************/
 
string
dump_tables()
{
   int i;
 
   for (i=0; i<MAXTABLES; i++)
     {
      write("   Seated at table "+LANG_WNUM(i+1)+" with " + 
        totalseats[i] + " seats: ");
      if (sizeof(tablecontents[i]))
        {
         write(COMPOSITE_LIVE(tablecontents[i])+"\n");
       }
      else
        write("Empty.\n");
    }
   return "";
 }
 
/**********************************************************************
 * - Function to carry on local conversations by typing             - *
 * - 'tablesay <msg>'                                               - *
 **********************************************************************/
 
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
 
/**********************************************************************
 * - Lists people sitting at your table.                            - *
 **********************************************************************/
 
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
 
/**********************************************************************
 * - This is outputted as the 'tablehelp' command                   - *
 **********************************************************************/
int
table_help(string str)
{
    write("\n"+
        "\t\t.-------------------------------------.\n"+
        "\t\t| +                                 + |\n"+
        "\t\t|                                     |\n"+
        "\t\t| sit at table <number>               |\n"+
        "\t\t| stand                               |\n"+
        "\t\t| tablesay <msg> - Talk to your Table |\n"+
        "\t\t| tablewho - look at your table       |\n"+
        "\t\t| tablehelp - this message            |\n"+
        "\t\t|                                     |\n"+
        "\t\t| You may also use sayt, whot, and    |\n"+
        "\t\t| helpt as shortcuts for these        |\n"+
        "\t\t| commands.                           |\n"+
        "\t\t| +                                 + |\n"+
        "\t\t`-------------------------------------'\n\n");
 return 1;
}
 
/**********************************************************************
 * - This is a utility function which returns the table index       - *
 * - number in the array of tables which you are sitting at.        - * 
 **********************************************************************/
 
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
 
/**********************************************************************
 * - table-local smile emote                                        - *
 **********************************************************************/
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
         "Notify the spiffy Asmo ASAP.\n");
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
 
/**********************************************************************
 * - Lists which chairs are empty and which are not                 - *
 **********************************************************************/
string
dump_chairs()
{
  int i;
  int e;
  
  for (i=0;i<MAXTABLES;i++)
    {
      e = totalseats[i]-sizeof(tablecontents[i]);
      write("Table "+LANG_WNUM(i+1)+" has "+totalseats[i]+" chairs. "+
            "( "+e+" are empty.)\n");
    }
  return "";
}
