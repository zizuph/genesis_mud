inherit "/std/object";
inherit "/d/Kalad/std/talk";
#include "/d/Kalad/defs.h"
#include <std.h>

#define KBUSY "_live_i_kalad_busy"
/* modified by Antharanos */
/* The Kalad-line was removed by Korat */

create_object()
{
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
   
   seteuid(getuid(TO));
   if (!masterp())
      {
      AA(khelp,khelp);
      
      AA(gpost,gpost);
      AA(gcvan,gcvan);
      AA(gport,gport);
      AA(gtrade,gtrade);
      AA(gcent,gcent);
      AA(gkal,gkal);
      AA(gpass,gpass);
      AA(gdrow,gdrow);
      AA(gdes,gdes);
      
      AA(ccent,ccent);
      AA(cport,cport);
      AA(ccvan,ccvan);
      AA(cwild,cwild);
      AA(cpass,cpass);
      AA(chigh,chigh);
      AA(cfarm,cfarm);
      AA(cdrow,cdrow);
      AA(cguild,cguild);
      AA(cvill,cvill);
      AA(cdes,cdes);
      AA(csewer,csewer);
      AA(ctrade,ctrade);
      AA(cmark,cmark);
      AA(copen,copen);
      AA(cnoble,cnoble);
      AA(cstd,cstd);
      AA(cclone,cclone);
      AA(ccom,ccom);
      AA(ckal,ckal);
      AA(ccant,ccant);
      AA(craum,craum);
      AA(cdwarf,cdwarf);
      AA(cuc,cuc);
      AA(cmind,cmind);
      AA(cgnome,cgnome);
      AA(cguild1,cguild1);
      AA(cguild2,cguild2);
      AA(cguild3,cguild3);
      
      AA(ker,ker);
      AA(kbug,kbug);
      AA(kid,kid);
      AA(ktyp,ktyp);
      AA(krun,krun);
      AA(kpr,kpr);

/* removed by Korat
      add_action( "line", "k");
      add_action("emote_line","ke");
      AA(kbusy,kbusy);
*/
      AA(klist,klist);
      add_action("show_exits","exits");
      AA(proj,proj);
      AA(reader,reader);
   }
}

khelp()
{
   TP->more(STD(khelp),1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
   
   return 1;
}

gpost()
{
   TP->move_living("X","/d/Genesis/wiz/post");
   return 1;
}

gcvan()
{
   TP->move_living("X","/d/Kalad/common/caravan/shop/wayfar_guild");
   return 1;
}

gport()
{
   TP->move_living("X","/d/Kalad/common/port/s8");
   return 1;
}

gtrade()
{
   TP->move_living("X","/d/Kalad/common/trade/tsquare/c2");
   return 1;
}

gcent()
{
   TP->move_living("X","/d/Kalad/common/central/plaza/sq_mon");
   return 1;
}

gkal()
{
   TP->move_living("X","/d/Kalad/workroom");
   return 1;
}

gpass()
{
   TP->move_living("X","/d/Kalad/common/wild/pass/w31");
   return 1;
}

gdrow()
{
   TP->move_living("X","/d/Kalad/common/wild/pass/drow/d5");
   return 1;
}

gdes()
{
   TP->move_living("X","/d/Kalad/common/wild/pass/desert/d1");
   return 1;
}

ccent()
{
   TP->set_path("/d/Kalad/common/central");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cport()
{
   TP->set_path("/d/Kalad/common/port");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

ccvan()
{
   TP->set_path("/d/Kalad/common/caravan");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cwild()
{
   TP->set_path("/d/Kalad/common/wild");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cpass()
{
TP->set_path("/d/Kalad/common/wild/pass");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

chigh()
{
TP->set_path("/d/Kalad/common/wild/high");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cfarm()
{
TP->set_path("/d/Kalad/common/wild/farm");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cdrow()
{
TP->set_path("/d/Kalad/common/wild/pass/drow");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cguild()
{
TP->set_path("/d/Kalad/common/wild/pass/guild");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cvill()
{
TP->set_path("/d/Kalad/common/wild/pass/kaldoro");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cdes()
{
TP->set_path("/d/Kalad/common/wild/pass/desert");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

csewer()
{
   TP->set_path("/d/Kalad/common/sewers");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

ctrade()
{
   TP->set_path("/d/Kalad/common/trade");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cmark()
{
   TP->set_path("/d/Kalad/common/market");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

copen()
{
   TP->set_path("/d/Kalad/open");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cnoble()
{
   TP->set_path("/d/Kalad/common/noble");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cstd()
{
   TP->set_path("/d/Kalad/std");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cclone()
{
   TP->set_path("/d/Kalad/clone");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

ccom()
{
   TP->set_path("/d/Kalad/common");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

ckal()
{
   TP->set_path("/d/Kalad");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

ccant()
{
   TP->set_path("/d/Kalad/common/canthyr");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

craum()
{
   TP->set_path("/d/Kalad/common/raum");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cdwarf()
{
   TP->set_path("/d/Kalad/common/wild/pass/dwarf");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cuc()
{
   TP->set_path("/d/Kalad/common/wild/pass/uc");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cmind()
{
   TP->set_path("/d/Kalad/common/wild/pass/mind");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cgnome()
{
   TP->set_path("/d/Kalad/common/wild/pass/dgnome");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cguild1()
{
   TP->set_path("/d/Kalad/common/caravan/thanar");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cguild2()
{
   TP->set_path("/d/Kalad/common/wild/pass/drow/guild");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}

cguild3()
{
   TP->set_path("/d/Kalad/common/wild/pass/drow/guild1");
   write(TP->query_path() + "\n");
   ls(TP->query_path(),"F");
   return 1;
}
ker()
{
   tail("/d/Kalad/log/errors");
   return 1;
}

kbug()
{
   tail("/d/Kalad/log/bugs");
   return 1;
}

kid()
{
   tail("/d/Kalad/log/ideas");
   return 1;
}

ktyp()
{
   tail("/d/Kalad/log/typos");
   return 1;
}

kpr()
{
   tail("/d/Kalad/log/praise");
   return 1;
}

krun()
{
   tail("/d/Kalad/log/runtime");
   return 1;
}

show_exits()
{
   seteuid(getuid(TO));
   if (!find_object("/d/Kalad/room_std"))
      "/d/Kalad/room_std"->load_it();
   
   write("/d/Kalad/room_std"->list_exits(E(TP)));
   return 1;
}

/* removed by Korat
status line( string str )
{
   my_tell_domain( "Kalad", "Kalad @ " + TP_N + ": " + str );
   return 1;
}

status emote_line( string str)
{
   my_tell_domain( "Kalad", "Kalad @ " + TP_N + " " + str );
   return 1;
}

kbusy()
{
   if(!TP->query_prop(KBUSY))
      {
      write("Kalad wizline is now off.\n");
      TP->add_prop(KBUSY,1);
   }
   
   else
      {
      write("Kalad wizline is now on.\n");
      TP->add_prop(KBUSY,0);
   }
   return 1;
}
*/


/* List all Kalad wizzes currently on. Shows name, level, and
* Kalad wizline busy status. With "-a" flag will show all
* Kalad wizzes, including those not on.
*/ 

klist(string flag)
{
   string name, *members, biz, last;
   int c, klev, logtime;
   object player;
   
   NF("Usage: 'klist'    - list Kalad wizzes currently on.\n" +
      "       'klist -a' - list all Kalad wizzes.\n");
   
   if (flag && flag != "-a")
      return 0;
   
   if (flag == "-a")
      write("Listing all Kalad members:\n\n");
   if (!flag)
      write("Listing Kalad members currently on:\n\n");
   write("Name         Level   Kalad line   ");
   if (flag && flag == "-a")
      write("last login");
   write("\n\n");
   
   members = "/secure/master"->query_domain_members("Kalad");
   for (c=0; c < sizeof( members ); c++)
   {
      if (flag == "-a" || (!flag && find_player( members[c] ) ))
         {
         name = C(members[c]) + "            ";
         name = extract(name,0,12);
         klev = "/secure/master"->query_wiz_level(members[c]);
         
         if(player = find_player(members[c]))
            if(player->query_prop(KBUSY))
            biz = "busy         ";
         else
            biz = "open         ";
         else
            biz = "----         ";
         
         if (!flag)
            last = "";
         else if (flag == "-a")
            {
            if (find_player(members[c]))
               last = "currently in the game";
            else
               {
               player = (object)SECURITY->finger_player(members[c]);
               logtime = time() - (int)player->query_login_time();
               last = "/lib/time"->convtime(logtime);
               last = last + " ago";
}
          }
         
         write(name + klev + "      " + biz + last + "\n");
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
