/***************************************************
 *   Kalad Wizard's Key
 *   - Gives us some nifty extra commands
 *
 *   Written by Ashbless with code borrowed
 *   from Windwalker's domain line.
 *   Modified by Antharanos.
 ***************************************************/
inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <std.h>
#include <options.h>
#include <filepath.h>


#define COMFILE            "/cmd/wiz/apprentice"
#define TOOLFILE           "/cmd/std/tracer_tool_base"
#define KIOSK              CENTRAL(test/kiosk)
#define SHOWCASE           CENTRAL(test/showcase)
#define MOTD               KALAD(motd)
#define DOM_BOARD          KALAD(private/private_board)


/* Used by kd()                            */
#define WIZARD_AS_DIRPATH  "_wizard_as_dirpath"
#define WIZARD_S_LAST_DIR  "_wizard_s_last_dir"

#define DIR_ALIASES  ([                                                  \
"log"    : ({ KALAD(log),              "Kalad logs directory"        }), \
"priv"   : ({ KALAD(private),          "Kalad private code directory"}), \
"cent"   : ({ COMMON(central) ,        "Central District of Kabal"   }), \
"port"   : ({ COMMON(port) ,           "Port District of Kabal"      }), \
"cvan"   : ({ COMMON(caravan) ,        "Caravan District of Kabal"   }), \
"wild"   : ({ COMMON(wild) ,           "Wild lands outside Kabal"    }), \
"pass"   : ({ WILD(pass) ,             "Pass NE of Kabal"            }), \
"high"   : ({ WILD(high) ,             "Highlands North of Kabal"    }), \
"farm"   : ({ WILD(farm) ,             "Farmlands West of kabal"     }), \
"undr"   : ({ CPASS(drow) ,            "Drow city of Undraeth"       }), \
"acad"   : ({ CPASS(guild) ,           "The Academy"                 }), \
"vill"   : ({ CPASS(kaldoro) ,         "Village of Kaldoro"          }), \
"des"    : ({ CPASS(desert) ,          "Great Kalad Waste"           }), \
"sewer"  : ({ COMMON(sewers) ,         "Sewers under Kabal"          }), \
"trade"  : ({ COMMON(trade) ,          "Trade District of Kabal"     }), \
"mark"   : ({ COMMON(market) ,         "Market District of Kabal"    }), \
"open"   : ({ KALAD(open) ,            "Kalad Open code and info"    }), \
"nob"    : ({ COMMON(noble) ,          "Noble District of Kabal"     }), \
"std"    : ({ KALAD(std) ,             "Kalad standard inherits dir" }), \
"com"    : ({ KALAD(common) ,          "Kalad common code directory" }), \
"kal"    : ({ "/d/Kalad" ,             "Kalad home directory"        }), \
"cant"   : ({ COMMON(canthyr) ,        "Empire of Canthyr"           }), \
"raum"   : ({ COMMON(raum) ,           "Kingdom of Raumdor"          }), \
"dwarf"  : ({ CPASS(dwarf) ,           "Dwarven city of Underhome"   }), \
"uc"     : ({ CPASS(uc) ,              "Underground Connection dir"  }), \
"mind"   : ({ CPASS(mind) ,            "Mind Flayer directory"       }), \
"gnome"  : ({ CPASS(dgnome) ,          "Deep Gnome city of Heartrock"}), \
"than"   : ({ CVAN(thanar) ,           "Thanarian Human race guild"  }), \
"drow"   : ({ CPASS(drow/guild) ,      "Drow race guild"             }), \
"acc"    : ({ CPASS(drow/guild1) ,     "Accursed guild"              }), \
"guild"  : ({ COMMON(guilds) ,         "Kalad guilds directory"      }), \
"duer"   : ({ GUILDS(duergar) ,        "Duergar Dwarven race guild"  }), \
"shad"   : ({ GUILDS(shadow_walkers) , "Shadow Walkers thieves guild"}), \
"merc"   : ({ GUILDS(merchant) ,       "Merchant guild              "}), \
"zint"   : ({ GUILDS(zintra) ,         "Zintra assasins guild"       }), \
"sship"  : ({ PORT(shipline1) ,        "Shipline to Shire domain"    }), \
"tship"  : ({ PORT(shipline2) ,        "Shipline to Terel domain"    }), \
"eship"  : ({ PORT(shipline5) ,        "Shipline to Emerald domain"  }), \
"rship"  : ({ PORT(shipline6) ,        "Shipline to Raumdor"         })  \
])

#define ROOM_ALIASES  ([                                                               \
"post"  : ({ "/d/Genesis/wiz/post"   ,"Goto wizard's post office"                  }), \
"cvan"  : ({ CVAN(shop/wayfar_guild) ,"Goto Wayfarer's Guild in Caravan District"  }), \
"port"  : ({ PORT(s8)                ,"Goto liftroom in Port District"             }), \
"trade" : ({ TRADE(tsquare/c2)       ,"Goto center of the Trade District"          }), \
"cent"  : ({ CENTRAL(plaza/sq_mon)   ,"Goto monument in Central District"          }), \
"kal"   : ({ KALAD(workroom)         ,"Goto Kalad domain workroom"                 }), \
"pass"  : ({ CPASS(w31)              ,"Goto Hill Giant village in NE wilderness"   }), \
"drow"  : ({ CPASS(drow/d5)          ,"Goto entrance of the Drow city of Undraeth" }), \
"des"   : ({ CPASS(desert/d1)        ,"Goto western edge of the Great Kalad Waste" }), \
"sdock" : ({ PORT(s81)               ,"Goto Shire shipline dock"                   }), \
"tdock" : ({ PORT(s97)               ,"Goto Terel shipline dock"                   }), \
"edock" : ({ PORT(s1)                ,"Goto Emerald shipline dock"                 }), \
"rdock" : ({ PORT(s104)              ,"Goto Raumdor shipline dock"                 })  \
])


/****************************
 *   Prototypes
 ****************************/
int get_body(string arg);
void kiosk_post(string body);
void get_type(string body);
void showcase_post(string type, string body);
void cleanup_msg(string filename, string str);
void cleanup_run();
void cleanup_typo();
void cleanup_err();
void cleanup_bug();
int kd(string str);
int motd();
void latest_domain_note();
int klist(string flag);
void do_login();
int kg(string arg);


masterp()
{
   string a;
   return sscanf( file_name( TO ), "%s#%s", a, a ) != 2;
}

create_object()
{
   ::create_object();
   if (masterp())
      return;
   
   set_name("key");
   add_name("wizard key");
   add_name("wizard's key");
   set_adj("kalad");
   set_short("kalad wizard's key");
   set_pname("keys");
   set_pshort("kalad wizard's keys");
   set_long("This is one of the fabled 'Keys to Kalad'. " +
   "It allows the wizards of Kalad certain powers. " +
   "For a listing of these powers type 'khelp'.\n");
   
   add_prop(OBJ_M_NO_DROP,"Now why would you want to drop the key?\n");
   
   move( TP );
   do_login();
}


void
do_login()
{
   if ("secure/master"->query_wiz_dom(TP->query_name()) == "Kalad")
   {
      motd();                       /* show message of the day */
      
      /* If board isn't loaded, leave some time for it to load */
      if (DOM_BOARD->query_latest_note())
         latest_domain_note();
      else
      {
         write("\n");
         ALARM(1.0,latest_domain_note);
      }
         
      klist("-a");                /* show info on Kalad wizzes */
   }
}


void
latest_domain_note()
{
   string fname, author, timestr, datestr;
   int time, last;
      
   if (fname = DOM_BOARD->query_latest_note())
      if (sscanf(fname,"b%d",time) == 1)
      {
         author = DOM_BOARD->query_author(DOM_BOARD->query_num_messages());
         write("\nLast note on Kalad domain board written by ");
         timestr = ctime(time);
         datestr = implode(explode(timestr," ")[0..2]," ");
         timestr = implode(explode(explode(timestr," ")[3],":")[0..1],":");
         write(C(author) + " on " + datestr + " at " + timestr + ".\n");
      }
      
   write("\n");
}


int
motd()
{
   if (file_size(MOTD) > 0)
   {
      write("\n"); 
      cat(MOTD,0,25);
   }
   
   return 1;
}


void init()
{
   NF("The key is for Kalad wizzes only!\n");
   if (E(TO) != TP)
      return 0;
   if (!TP->query_wiz_level())
      {
      write("You're not a wizard so the key self-destructs!\n");
      remove_object();
      return 0;
   }
   if ("secure/master"->query_wiz_dom(TP->query_name()) != "Kalad")
      {
      write("You're not a member of the Kalad domain...\n" +
         "The key melts, leaving a slimy substance on your hands.\n");
      remove_object();
      return 0;
   }
   
   reset_euid();
   
      AA(khelp,khelp);
      
      AA(ker,ker);
      AA(kbug,kbug);
      AA(kid,kid);
      AA(ktyp,ktyp);
      AA(krun,krun);
      AA(kpr,kpr);
      AA(kered,kered);
      AA(kbuged,kbuged);
      AA(ktyped,ktyped);

      AA(klist,klist);
      add_action("show_exits","exits");
      AA(proj,proj);
      AA(reader,reader);
      AA(get_body,knote);
      AA(get_body,decree);
      AA(kd,kd);
      AA(motd,motd);
      AA(kg,kg);
}


int
kd(string str)
{
    int len, i;
    string old_path, new_path, *parts, *indexes, alias, msg;
    object ob;

    old_path = TP->query_path();

    /* If no argument was given, change to wizard's home directory */
    if (!stringp(str))
	   new_path = SECURITY->query_wiz_path(TP->query_real_name());

    else
       /* If the first character of the arg is "@", check aliases */
       if ( ((len = strlen(str)) > 0) && (str[0] == 64) )
       {
          indexes = m_indexes(DIR_ALIASES);
    
          if (len == 1)
          {
             msg = " #    Directory Alias   Description\n" +
                   "---   ---------------   -----------\n";
          
             for (i=0;i<sizeof(indexes);i++)
                msg += sprintf("%2d)   %15-s   %s\n", i, indexes[i],
                   DIR_ALIASES[indexes[i]][1]);
                 
             TP->more(msg);    
             return 1;
          }
      
          else
          {
             alias=extract(str,1,(len-1));
             NF("'" + alias + "' is not a directory alias.\n");
             
             if ( (i = member_array(alias, indexes)) >= 0 )
             {
                new_path = DIR_ALIASES[indexes[i]][0];
                write(DIR_ALIASES[indexes[i]][1] + ": ");
             }
             
             else
                return 0;
          }
       }
    
       else
          switch(str)
          {
             case ".":
                write(old_path + "\n\n");
                ls(old_path,"F");
	            return 1;

             case "-":
	            new_path = TP->query_prop(WIZARD_S_LAST_DIR);
	            break;

             default:
	            new_path = FTPATH(old_path, str);
	            break;
          }

    /* If the given arg is not a directory, see if it is an object */
    if (file_size(new_path) != -2)
    {
	   if (!objectp(ob = TOOLFILE->parse_list(str)))
	   {
	       NF("No such directory '" + str + "'.\n");
	       return 0;
	   }

	   parts = explode(FN(ob), "/");
	   new_path = implode(parts[0..(sizeof(parts) - 2)], "/");
    }

	write(new_path + "\n\n");
    TP->add_prop(WIZARD_S_LAST_DIR, old_path);
    TP->set_path(new_path);
    ls(new_path,"F");

    return 1;
}


int
get_body(string arg)
{
   string file, home, subdir;
   
   if (!arg)
      if (query_verb() == "knote")
         "/std/edit"->edit("kiosk_post");
      else
         "/std/edit"->edit("get_type");
      
   else
   {
      if ( sscanf(arg, "~%s/%s", home, subdir) == 2)
         if (home == "Kalad")
            arg = "/d/Kalad/" + subdir;
         else
            arg = "/d/Kalad/" + home + "/" + subdir;
   
      NF(arg + ": No such file!\n");
      if (! (file = read_file(arg)) )
         return 0;
      
      if (query_verb() == "knote")
         kiosk_post(file);
      else
         get_type(file);
   }
   
   return 1;
}


void
kiosk_post(string body)
{ 
   if (!strlen(body))
   {
      write("No message entered.\n");
      return;
   }

   write("Message posted.\n");      
   KIOSK->post_it(body);
}


void
get_type(string body)
{
   int type;
   
   if (!strlen(body))
   {
      write("No message entered.\n");
      return;
   }
   
   write("\n" +
      " #  Message Type:           Author:\n" +
      "--- --------------------    --------------------------\n" +
      " 0) Royal Proclamation      High Lord\n" +
      " 1) Royal Decree            High Minister\n" +
      " 2) Council Edict           Speaker of High Council\n" +
      " 3) Church Bull             Arch Prelate of Solara\n" +
      " 4) Military Declaration    Knight General of Armies\n" +
      " 5) Principal Statute       Ring Prince\n" +
      " 6) Royal Canon             High Cleric of the Citadel\n" +
      " 7) City Ordinance          High Council\n" +
      " 8) Public Safety Mandate   Knight Captain of Militia\n" +
      " 9) Official Announcement   High Council\n" +
      "10) Official Notice         Knight Captain of Militia\n" +
      "11) Public Announcement     Public Relations Minister\n" +
      "\n");
      
   write("choice [11]: ");
   input_to("showcase_post",0,body);
}


void
showcase_post(string entry, string body)
{
   int type;
   
   if ( (sscanf(entry,"%d",type) != 1) || type < 0 || type > 11 )
      type = 11;
     
   write("Message posted.\n");      
   SHOWCASE->post_it(body, type);
}


khelp()
{
   TP->more(STD(khelp),1);   
   return 1;
}


/* Kalad goto command with room aliases */
int
kg(string arg)
{
   string room, msg, *indexes;
   int i;
   
   indexes = m_indexes(ROOM_ALIASES);
   
   if (!stringp(arg))
   {
      msg = " #    Room Alias   Description\n" +
            "---   ----------   -----------\n";
          
      for (i=0;i<sizeof(indexes);i++)
         msg += sprintf("%2d)   %10-s   %s\n", i, indexes[i],
            ROOM_ALIASES[indexes[i]][1]);
                 
      TP->more(msg);    
      return 1;
   }
      
   else
      if ( (i = member_array(arg, indexes)) >= 0 )
      {
         room = ROOM_ALIASES[indexes[i]][0];
         write(ROOM_ALIASES[indexes[i]][1] + ":\n\n");
         TP->move_living("X",room);
         return 1;
      }

   NF("'" + arg + "' is not a room alias.\n");
   return 0;
}


ker()
{
   NF("There are currently no errors logged.\n");
   if ( MTAIL(LOGS(errors),cleanup_err) )
      return 1;  
   else
      return 0;
}


kbug()
{
   NF("There are currently no bugs logged.\n");
   if ( MTAIL(LOGS(bugs),cleanup_bug) )
      return 1;  
   else
      return 0;
}


kid()
{
   tail("/d/Kalad/log/ideas");
   return 1;
}


ktyp()
{
   NF("There are currently no typos logged.\n");
   if ( MTAIL(LOGS(typos),cleanup_typo) )
      return 1;  
   else
      return 0;
}


kpr()
{
   tail("/d/Kalad/log/praise");
   return 1;
}


krun()
{
   NF("There are currently no runtime errors logged.\n");
   if ( MTAIL(LOGS(runtime),cleanup_run) )
      return 1;
   else
      return 0;
}


void
cleanup_run() { cleanup_msg(LOGS(runtime),"runtime errors"); }


void
cleanup_typo() { cleanup_msg(LOGS(typos),"typos"); }


void
cleanup_bug() { cleanup_msg(LOGS(bugs),"bugs"); }


void
cleanup_err() { cleanup_msg(LOGS(errors),"errors"); }


void
cleanup_msg(string filename, string str)
{
   int flen = sizeof(explode(read_file(filename), "\n"));
   
   if (flen > 0)
      write("******************************************************************\n" +
            "* Please clean out your " + str + " when they have been fixed. \n" +
            "* The log currently contains " + flen + " lines.\n" +
            "******************************************************************\n");
}


kbuged()
{
   ed("/d/Kalad/log/bugs");
   return 1;
}


ktyped()
{
   ed("/d/Kalad/log/typos");
   return 1;
}


kered()
{
   ed("/d/Kalad/log/errors");
   return 1;
}


show_exits()
{
   if (!find_object("/d/Kalad/room_std"))
      "/d/Kalad/room_std"->load_it();
   
   write("/d/Kalad/room_std"->list_exits(E(TP)));
   return 1;
}


/* List all Kalad wizzes currently on. Shows name, level, and
* Kalad wizline busy status. With "-a" flag will show all
* Kalad wizzes, including those not on.
*/ 
int
klist(string flag)
{
   string head, *members, last, biz;
   int c, logtime, deadtime;
   
   string USAGE = "Usage: 'klist'    - list info on Kalad wizzes currently on.\n" +
                  "       'klist -d' - list working directory of Kalad wizzes on.\n" +
                  "       'klist -a' - list info on all Kalad wizzes.\n";
   
   NF(USAGE);   
   if ( flag && (flag != "-a") && (flag != "-d") )
   {
      write(flag + ": bad option!\n");
      return 0;
   }

   head="Name         Lvl  ";
   if (flag == "-a")
      write("Listing all Kalad members:\n\n" + head + "Last Login");      
   else
   {
      write("Listing Kalad members currently on:\n\n" + head + "Busy       ");
      if (flag)
         write("Current Working Directory");
      else
         write("Location");
   }
   write("\n\n");
   
   members = "/secure/master"->query_domain_members("Kalad");
   for (c=0; c < sizeof( members ); c++)
   {
      int show_member=0;
      object player=find_player(members[c]);

      if (flag == "-a")
         show_member=1;
      else if (player)
         if (!player->query_linkdead())
            show_member=1;
         
      if (show_member)
      {
         int klev = "/secure/master"->query_wiz_level(members[c]);
         string name = C(members[c]) + "            ";

         name = extract(name,0,12);
         
         if (!flag)
            last=file_name(E(player));
            
         else
            if (flag == "-d")
               last = RTILDE(player->query_path()) + "/";
            
            else
            {
               if (player)
                  if (deadtime=player->query_linkdead())
                  {
                     deadtime = time() - deadtime;
                     last="linkdead for "+"/lib/time"->convtime(deadtime);
                  }
                  else
                     last = "currently in the game";
               else
               {
                  player = (object)SECURITY->finger_player(members[c]);
                  logtime = time() - (int)player->query_login_time();
                  last = "/lib/time"->convtime(logtime);
                  last = last + " ago";
               }
            }
         
         if (flag == "-a")
            write(name + klev + "   " + last + "\n");
         else
         {
            biz = COMFILE->busy_string(player->query_prop(WIZARD_I_BUSY_LEVEL));
            biz = extract(biz + "           ",0,10);
            write(name + klev + "   " + biz + last + "\n");
         }
      }
   }
   
   return 1;
}


int
proj()
{
   TP->more("/d/Kalad/korat/log/projects",1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
   return 1;
}


reader()
{
   object ob;
   int i;
   
   ob = deep_inventory(TP);
   for (i=0; i<sizeof(ob); i++)
   {
      if (ob[i]->id("mailreader"))
         {
            "secure/master"->do_debug("destroy",ob[i]);
            write("Mail reading is now off.\n");
            return 1;
        }
   }
   
   ob = clone_object("/secure/mail_reader");
   ob->move(TP);
   write("Mail reading is now on.\n");
   return 1;
}


string query_auto_load()
{
   return MASTER;
}
