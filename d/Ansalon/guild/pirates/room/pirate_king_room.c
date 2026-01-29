/**
 * January 21th 2007, Navarre
 *
 * Added special mapping containing banished press gangers
 * used at trainer to disallow pirates that had their
 * press ganger status removed by the king to automatically
 * become press ganger.
 *
 */

#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <std.h>

inherit MITHAS_IN;


object chest;
string currentTarget,currentTarget2, currentTarget3;
int warned, warning, warning3;
string target, target2, target3;


string paper_desc = 0;
string* messages = ( {} );

static mapping banned_pressgangers = ([]);


/* prototype */
public string read_paper();

void
reset_pirate_room()
{
   if(!objectp(chest))
      {
      chest = clone_object(GUILD_OBJ + "chest");
      chest->move(TO);
   }
}


void
create_mithas_room()
{

    set_short("The private quaters of the Pirate King");

    set_long("The first thing that strikes you is the awful mess that inhabits this "+
             "room. Even though the grotto might be rather large, now only a short "+
             "corridor from here to a large mahogany table is clear. The back of the "+
             "room is filled to the ceiling with boxes of all shapes and sizes. In "+
             "front of the boxes and on each sides of the table, the floor is completely "+
             "filled with bottles. Some broken, some not, but all are empty. Next to the "+
             "table a large chest has been placed. Many items seem to have been stewn "+
             "across the large table in the middle of the room.\n"+
             "A heavy stench of alcohol mixed with sea water hangs in the air.\n");

    add_item(({"table", "mahogany table", "large table"}),
       "It is a large table made from beautiful dark mahogany adorned with many "+
       "carvings and much detail. It must have been an extremely expensive piece of "+
       "furniture. The table is filled with lots of different stuff. Most noticeably "+
       "a large, well-worn log-book, a tattered piece of paper with some sort of list "+
       "written on it and next to it lies what looks like a map of sorts.\n"+
       "Behind it is stands a chair of the same design.\n");

    add_item(({"book","large log-book","well-worn","log-book"}),
       "This book seems rather old, by the worn look of its covers. On the front "+
       "written with large letters is:\n"+
       "                                'Sum rules fer da crew'\n"+
       "                                          'by'\n"+
       "                              'Captain Mortimor Bloodnose'\n");
       
    add_item(({"paper", "tattered paper", "tattered piece of paper"}),
       "It's a rather new piece of paper. Written on it, you can see a list of commands "+
       "that the Pirate King or Queen can use in this room and a list of members.\n"+
       "You can study the papers to inspect these commands in detail.\n");
 
    add_item(({"map"}),
       "It is a treasure map!\n"+
       "As you eagerly examine the map more intensely, you realize that you "+
       "have never heard of the name of the island, that is drawn on it. It mentions "+
       "an island named 'Booty Island', and there seems be specific instructions "+
       "on how to find, some treasure. A big X is drawn near the entrance to cave "+
       "drawn much like a skull.\n");

    add_item(({"chair"}),
       "This chair is as beautiful as the table, made also from the same exquisit dark "+
       "mahogany wood, with a great deal of carvings and intricate detail. The seat and "+
       "back of the chair are covered with expensive red satin cushions. It must have "+
       "cost a fortune.\n");

    add_item(({"boxes"}),
       "Untold numbers of boxes coveres the back wall of the cave. As you take a "+
       "closer look at the boxes, you realize that they are all filled with a layer "+
       "of hay. They were obviously used to store bottles of liquor of all sorts. "+
       "Most of the boxes have 'RUM' follwed by a skull painted on the side, though.\n"+
       "The majority of the boxes have been opened and are empty, and only a few "+
       "seems to contain anything anymore.\n");

    add_item("words","They are readable.\n");
   
    add_item(({"bottles"}),
       "All over the floor, you can see bottles in all shapes and sizes. You cannot "+
       "recall ever having seen so many different bottles before in your life. "+
       "Although many of them lay broken, you can read the labels of most of them, "+
       "and you have heard of most of the names, printed on the bottles.\n"+
       "'Salty Seawater', 'Krakens Venom', 'Ghost Captains Gold', 'Grotto Grime'"+
       "and 'Bloodnose Supreme' is only a few of the exotic names you find."+
       "On most of the bottles only have a simple label with 'RUM' printed on it "+
       "followed by three 'XXX' below it.\n"+
       "From the many broken bottles, a heavy stench filles the room.\n");

    add_cmd_item("book", "read", "@@read_book");
    add_exit("pirate_center_room","southeast","@@king_exit",0); 
    seteuid(getuid(TO));
    reset_pirate_room();
}

int
banish(string str)
{
    if (!str)
    {
        write("Banish who from the guild?\n");
        return 1;
    }

    target = str;

    if (warned == 1 && target == currentTarget)
    {
        warned = 0;
        write(C(str)+ " will be thrown out of the pirates of the Bloodsea the next "+
              "time that person enters the Realm.\n");

        write_file(GUILD_LOG+"pirate_log.txt", C(str) + " banished " + 
                   extract(ctime(time()), 4, 15)+
                   ", StatAvg: "+find_living(str)->query_average_stat()+
                   ", Race: "+find_living(str)->query_race()+
                   ", Align: "+find_living(str)->query_alignment()+"\n");
    }
    else
    {
        write("Are you sure you want to throw "+C(target)+
              " out of the guild?!\n"+
              "If you are please retype the command.\n"+
              "Remember that player MUST be a member of this guild, otherwise errors will occur "+
              "and this command will be removed!\n");
        warned = 1;
        currentTarget = target;
    }
    return 1;
}

int
resign(string whom)
{
    object newKing;

    if(!PADMIN->query_pirate_king(TP))
    {
        write("What?\n");
        return 1;
    }

    if (!whom)
    {
        write("Resign your captains title to whom?\n");
        return 1;
    }

    target2 = whom;

    if(!PADMIN->query_member(whom))
    {
        write("The person, "+whom+", is not a member of this guild!\n");
        return 1;
    }
    else
    {
        if (warning == 1 && currentTarget2 == target2)
        {
             write("With a sign you take a brief glance at your various "+
                   "equipment around your captains room before erasing you "+
                   "name and title as captain of the Pirates of the Bloodsea.\n"+
                   "You are now a common pirate.\n"+
                   "Hail the new Pirate King, "+C(whom)+
                   " the Fearless.\n"+
                   "You leave the Kings room.\n");
             PADMIN->make_normal_member(TP);
             PADMIN->set_pirate_king(whom, TP); // set who by who :)
             TP->move_living("leaves the room",GUILD_ROOM+"pirate_center_room.c", 1, 0);
             warning = 0;
             newKing = find_player(whom);
             if(newKing)
             {
                 newKing->catch_tell("\n\nCongratulations! You have been chosen as "+
                                     "the new Legendary Pirate King!\n\n");
             }
        }
        else if (warning == 0)
        {
            write("Are you sure you want to resign your title to "+
                   C(whom)+ "? If you do so, you will loose your title and "+
                  "become a normal pirate.\n"+
                  "If you are sure, please retype the command.\n");
            warning = 1;
            currentTarget2 = target2;
        }

    }
    return 1;
}

/**
 * This function handles the promotion to press ganger
 *
 * @param whom The person to become press ganger
 */
int
designate(string whom)
{
    if(!PADMIN->query_pirate_king(TP))
    {
        write("What?\n");
        return 1;
    }

    if (!whom)
    {
        write("Designate who to recruit pirates?\n");
        return 1;
    }

    target2 = whom;

    
    if(!PADMIN->query_member(whom))
    {
        write("That person is not a member of this guild!\n");
        return 1;
    }

    if(PADMIN->query_pressganger(whom))
    {
        write("That person has already been designated to be a pirate recruiter!\n");
        return 1;
    }

    if (warning == 1 && currentTarget2 == target2)
    {
        write("You designate "+C(whom)+ " to recruit new pirates.\n");
        PADMIN->add_pressganger(whom);
        warning = 0;

        find_living(whom)->catch_msg("\n\nCongratulations! You have be designated by "+
                                     "the Legendary Pirate King to recruit new pirates! "+
                                     "You can now use the 'vote' command in the pirates "+
                                     "join room.\n\n");
        seteuid(getuid(TO)); 
        banned_pressgangers = restore_map(BAN_PRESSGANGER_FILE);
        // Make sure we remove the person from the banished list since we make him a press ganger.
        m_delkey(banned_pressgangers, whom);
        save_map(banned_pressgangers, BAN_PRESSGANGER_FILE);
     }
     else if (warning == 0)
     {
          write("Are you centain you want to allow "+
                C(whom)+ " to recruit new pirates?\n"+
               "If you are, please retype the command.\n");
          warning = 1;
          currentTarget2 = target2;
     }
    return 1;
}

int
promote(string whom)
{
    if(!PADMIN->query_pirate_king(TP))
    {
        write("What?\n");
        return 1;
    }

    if(!whom)
    {
        write("Promote who to be your first mate?\n");
        return 1;
    }

    if(!PADMIN->query_member(whom))
    {
        write("That person is not a pirate!\n");
        return 1;
    }

    if(PADMIN->query_firstmate(whom))
    {
        write("That pirate is already your first mate!\n");
        return 1;
    }

    if(TP->query_real_name() == whom)
    {
        write("You can't make yourself the first mate.\n");
        return 1;
    }

    PADMIN->set_firstmate(whom);
    TP->catch_tell("You promote "+C(whom)+" to be your first mate!\n");
    return 1;
}

int
demote(string whom)
{
    if(!PADMIN->query_pirate_king(TP))
    {
        write("What?\n");
        return 1;
    }

    if(!whom)
    {
        write("Demote who from first mate?\n");
        return 1;
    }

    if(!PADMIN->query_member(whom))
    {
        write("The person, "+whom+", is not a pirate!\n");
        return 1;
    }

    if(!PADMIN->query_firstmate(whom))
    {
        write("That is not your first mate!\n");
        return 1;
    }

    PADMIN->remove_firstmate(whom);
    TP->catch_tell("You demote "+C(whom)+" from being your first mate!\n");
    return 1;
}

int
estrange(string str)
{
    object who;
    if (!PADMIN->query_pirate_king(TP))
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Estrange who from recruiting ?\n");
        return 1;
    }

    if (!PADMIN->query_member(str))
    {
        write("But "+C(str)+" is not a member of this guild!\n");
    }
    else if (!PADMIN->query_pressganger(str))
    {
        write("That pirate is not in the recruiting team!\n");
    }
    else
    {
        PADMIN->remove_pressganger(str);   
        
        who = find_player(str);
        if(who)
        {
            who->catch_tell("You can no longer recruit new pirates!\n");     

            write(C(str)+ " has been removed from the pirates recruiting team.\n");
            seteuid(getuid(TO));
            banned_pressgangers = restore_map(BAN_PRESSGANGER_FILE);
            banned_pressgangers += ([str : "Removed as Pressganger by the King/Queen"]); 
            save_map(banned_pressgangers, BAN_PRESSGANGER_FILE);
        }
    }
    return 1;
}


int
read_book()
{
    write("I write dis down to any future Kaptain, so ye might know which rules "+
       "I ran dis crew with. Dis is also the note that I keep on our board, at all "+
       "times, so if dere is any fergetful members, the rules are always there ta "+
       "read, if needs be.\n\n                                    --------------"+
       "---------------\n\n"+
       "Oi! Ye scurvy Pirate dogs!\n\n"+
       "I da captain of this rowdy crew, and people all over Ansalon know me as "+  
       "Mortimor, the Legendary Pirate King. And in dis lil letter I'll lay down sum "+
       "rules fer dis crew, and our operations. First of all, if someone wants ta "+ 
       "join our crew and become a scurvy Pirate, dey have ta act like a reel Pirate, "+
       "not some wheezy land lubber. Dis aint no tree-huggers retirement home, so I "+
       "want ta see real sea dogs in this crew. "+
       "Next on me list is dis...We is Pirates and we pillage and plunder whatever, "+
       "whereever we want. But dat does not mean dat you can kill or kidnap anyone you "+
       "feel like. I dont want any in-fighthin in this crew, so keep ya hands off ye "+
       "Mateys booty, and keep ya hook up the nose of land lubbers. If ya cant obey dem "+
       "rules, I am gonna kick ya sorry ass outta here.\n"+
       "Last thing on me list...Booty! I know dat we are all a bunch of greedy "+ 
       "bastards, and I'd rather throw me plunder in da sea, than spliting it wit any "+
       "of you, but I thing its a good idea to bring back booty dat ye fellow mateys "+
       "can use, like knives, swords, axes and armours. So bring those things back to "+
       "our grotto and toss them on our big nifty table east of here. And also, if I "+
       "see any of ya Freebooters takin loot from our table an sellin it, I is gonna "+
       "get reel pissed, and if its serious or ya do it again, ya gets ta walk da "+
       "plank right back to da borin life of da land lubbers!\n\n"+
       "Dat was bout it. Now go drink, fight, plunder and drink!\n\n"+
       "And remember, no land lubber tells a reel scurvy pirate dog what to do, no "+
       "matter how fancy pantsy dey think themself are!!!\n\n"+
       "Mortimor Bloodnose, da Kaptain.\n");
       return 1;
}


public void
remove_old_members(mixed names)
{
    int i = -1, size = sizeof(names);

    while(++i < size)
      if (!SECURITY->exist_player(L(names[i])))
      {
	  seteuid(getuid(TO));
	  write_file(GUILD_LOG+"pirate_log.txt", C(names[i]) + " left ~" + 
		     extract(ctime(time()), 4, 15) + " (deleted)\n");
	  paper_desc = 0;
      }
}


public string
read_paper()
{
    mixed names, names_tmp = ({});
    string output = "", name, t, outputw = "";
    int size, i = -1, pos;

    if (!PADMIN->query_pirate_king(TP))
    {
        write("You don't want to risk getting caught snooping through " +
              "the papers here. You would get to walk the plank for sure.\n");
        return "";
    }

    if (paper_desc)
      return paper_desc;

    names = explode(read_file(GUILD_LOG+"pirate_log.txt"), "\n");

    size = sizeof(names);
    while(++i < size)
    {
	if ((pos = sscanf(names[i], "%s left %s", name, t)) == 2)
	{
	    if ((pos = member_array(name, names_tmp)) != -1)
		names_tmp = exclude_array(names_tmp, pos, pos);
	}
	else
	{
	    if (sscanf(names[i], "%s joined %s", name, t) == 2)
		if (member_array(name, names_tmp) == -1)
		    names_tmp += ({ name });
	}
    }

    set_alarm(1.0,0.0,&remove_old_members(names_tmp));

    size = sizeof(names_tmp);
    i = -1;

    while(++i < size)
    {
        output += names_tmp[i] + "\n";
    }
    output = sprintf("%#-79s",output);
    paper_desc = "These are the members of the Pirates of the Bloodsea:\n" +
      "------------------------------------------------------------------------------\n" +
      output + "\n\n"+
      "------------------------------------------------------------------------------\n" +
      " You can use these commands within this room:                                 \n" +
      " - Banish <name>    : The target will be removed from the guild.              \n" +
      " - Resign <name>    : You will resign you captains title and become           \n"+
      "                      a standard pirate. <Name> will take over as the         \n"+
      "                      new Pirate King.                                        \n"+
      " - Designate <name> : Adds <name> to the pirate recruiting team.              \n"+
      " - Promote <name>   : Promotes <name> to be your first mate.                  \n"+
      " - Demote <name>    : Demotes <name> from being your first mate.              \n"+
      " - Estrange <name>  : Removes <name> from the pirate recruiting team.         \n"+
      " - Donations        : See the donations that has been made to the barrel.     \n"+
      " - Snoop            : See what the crew takes from the table.                 \n"+

      "                                                                              \n";
 // Currently disabled, as I only have some flags, and not all guilds.
 //     " - Order ally flags : Orders flags from guild for whom you privateer.         \n";
    return paper_desc;
}


int
donations()
{
    string output = "";

    if (!PADMIN->query_pirate_king(TP))
    {
        write("What?\n");
        return 1;
    }

    output = read_file("/d/Ansalon/log/donate_log.txt");
    write("Donations made to the barrel:\n"+
          "------------------------------\n"+output);
    return 1;
}


void
log_item(string str)
{
    messages += ({ str });

    while (sizeof (messages) > 400)
        messages -= ({ messages [0] });
}

int
snoop()
{
    TP->more (implode (messages, "\n"));
    return 1;
}

int
king_exit()
{
   if(TP->query_prop(I_AM_ALLOWED))
       TP->remove_prop(I_AM_ALLOWED,1);;
   return 0;
}


// This function is currently not used, we want more flags before we enable this one
void send_parrot(object player, object parrot)
{
  tell_room(environment(player), QCTNAME(parrot)+" goes: Awwwk! Off I goes..\n", parrot);
  parrot->remove_object();
}

// This function is currently not used, we want more flags before we enable this one
void get_ally_flags(object room)
{
  tell_room(room, "An old limping pirate arrives.\n");
  tell_room(room, "The old limping pirate tosses a stack of flags into the large oak chest.\n");
  tell_room(room, "The old limping pirate leaves to the southeast.\n");
  for(int i = 0; i <= 40; i++)
  {
      clone_object("/d/Ansalon/guild/pirates/obj/red_flag")->move(chest, 1);
  }
}


// This function is currently not used, we want more flags before we enable this one
int
order_flags(string args)
{
  object parrot; 
  if(args != "ally flags")
  {
    notify_fail("Order what? Ally flags?\n");
    return 0; 
  }
   
  parrot = present("parrot", this_player()); 

  if(!parrot)
  {
      this_player()->catch_tell("You will require a parrot to send your order.\n");
      return 1; 
  }
  set_alarm(4.0, 0.0, &send_parrot(this_player(), parrot));  
  set_alarm(900.0, 0.0, &get_ally_flags(this_object()));  
  this_player()->catch_tell("You scribble down your order and fasten it to your parrot's right leg.\n");
  tell_room(environment(this_player()), QCTNAME(this_player())+" scribbles "+
            "something on a piece of paper and fasten it to "+HIS(this_player())+
            "parrot's right leg.\n", this_player());
  return 1; 
}


int read_the_papers(string args)
{
  if(args == "paper" || args == "papers" ||
     args == "tattered paper" ||
     args == "tattered piece of paper")
  {
      this_player()->catch_msg(read_paper());
      return 1;
  }
  notify_fail("Read what? the paper?\n");
  return 0;
}

void
init()
{
    ::init();
    ADA("banish");
    ADA("resign");
    ADA("designate");
    ADA("estrange");
    ADA("donations");
    ADA("snoop");
    ADA("promote");
    ADA("demote");
//    add_action(order_flags, "order");
    add_action(read_the_papers, "study");
}
