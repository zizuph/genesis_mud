/* The Pirates eyepatch. This shows that you are a member of the guild.   */

inherit "/std/object";

#include <tasks.h>
#include "/d/Emerald/defs.h"
#include "pirates_defs.h"
#include "defs.h"

#define EYEPATCH_SUBLOC "_wearing_eyepatch"
#define EYEPATCH_ID "pirate_eyepatch"
#define EYEPATCH_FILE PIRATES_DIR+"obj/eyepatch"
#define OWN_SOUL SOUL_DIR+"pirate_soul"

int is_member(mixed who);

void
init_arg(string arg)
{
}

void
create_object()
{
   set_name("eyepatch");
   add_name(EYEPATCH_ID);
   set_adj("black");
   set_adj("old");
   set_long(break_string("It looks like something a pirate would wear. "
         + "For information on the Pirates guild <help eyepatch>. "
         + "\n",78));
   set_short("old black eyepatch");
   
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 25);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_S_WIZINFO, "The eyepatch loads the Pirates soul.\n");
   add_prop(OBJ_M_NO_DROP, "It would be an act of treason to "+
      "relinquish your eyepatch.\n");
}

string
query_auto_load()
{
   return PIRATES_DIR+"obj/eyepatch:" + "0";
}

void
enter_env(object env, object from)
{
   object lost_eye;
   ::enter_env(env, from);
   env->add_subloc(EYEPATCH_SUBLOC, this_object());
   if(present("lost_eye",TP))
      {
      lost_eye = present("lost_eye",TP);
      lost_eye ->remove_object();
      return;
   }
   return;
}

string
show_subloc(string subloc,object carrier,object for_obj)
{
   string which_eye;
   if(random(2))
      which_eye = "right eye";
   else
      which_eye = "left eye";
   if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if(for_obj == carrier)
      return "You are wearing an eyepatch over your "+which_eye+".\n";
   return capitalize(carrier->query_pronoun())+" is wearing an "+
   "old worn eyepatch over "+ POS(carrier)+" "+which_eye+".\n";
}



init()
{
   ::init();
   add_action("do_show_members","p",0);
   add_action("do_show_members", "pirates");
   add_action("do_give_explanation","help",0);
   add_action("ptoast","ptoast",0);
   if (this_player() == environment())
      call_out("init_soul", 1, this_player());
   if(environment()->query_real_name())
      {
      add_action("new_soul","psoul",0);
      add_action("do_renew","renew",0);
      add_action("do_eyepatch","giveeyepatch",0);
      add_action("do_eyepatch2","removeeyepatch",0);
      add_action("new_shadow","pshadow");
   }
}

int
ghost()
{
   return environment()->query_ghost();
}

int
fail_ghost()
{
   write("You fail.\n");
   return 1;
}


/*
* Function name:   add_soul_at_top
* Description:     add given soul at the top of the cmdsoul list
* Arguments:       soul: filename of soul to be added
*                  who:  player the soul must be added to
* Returns:         1 if successful, 0 otherwise.
   */
static int
add_soul_at_top(string soul, object who)
{
   string *soul_arr;
   int i;
   
   seteuid(getuid());
   if (member_array(soul, who->query_cmdsoul_list()) >= 0)
      return 0;
   soul_arr = who->query_cmdsoul_list();
   for (i = 0; i < sizeof(soul_arr); i++)
   who->remove_cmdsoul(soul_arr[i]);
   who->add_cmdsoul(soul);
   for (i = 0; i < sizeof(soul_arr); i++)
   who->add_cmdsoul(soul_arr[i]);
   who->update_hooks();
   return 1;
}

void
init_soul(object ob)
{
   add_soul_at_top(PIRATE_SOUL, ob);
}


int
do_show_members()
{
   string pir_name, pir_title, str;
   int i, cnt, lsize;
   object player_ob, eyepatch, *list;
   
   list = filter_array(users(), "is_member", this_object());
   lsize = sizeof(list);
   cnt = 0;
   
   write("Current Active Pirates include:\n");
   
   for (i = 0; i < lsize; i++ )
   {
      str = 0;
      player_ob = list[i];
      if (!(player_ob->query_invis())||!player_ob->query_wiz_level())
         {
         pir_name = player_ob->query_name();
         
         if (player_ob->short())
            {
            if (!(pir_title = player_ob->query_title()))
               pir_title = "";
            
            /* QCNAME does not work with write() */
            str = ":" + pir_name + " " + pir_title;
            cnt++;
          }
         eyepatch = present(EYEPATCH, player_ob);
         
         if (eyepatch && player_ob->short())
            {
            if (player_ob->query_ghost())
               str+=" <deceased>";
          }
         
         if (str)
            environment()->catch_msg(str+"\n");
        }
   }
   write("Total numer of Pirates: " + cnt + "\n");
   say(QCTNAME(this_player())+" hums a few bars and dances around "+
      "merrily.\n");
   return 1;
}

int
ptoast()
{
   string pir_name;
   int i, lsize;
   object player_ob, eyepatch, *list;
   
   list = filter_array(users(), "is_member", TO) - ({TP});
   lsize = sizeof(list);
   
   write("You propose a toast to your fellow pirates.\n");
   if(lsize < 1)
      write("However, you are the only pirate in Genesis.\n"+
      "You will have to drink a toast to yourself!\n");
   
   for (i = 0; i < lsize; i++ )
   {
      player_ob = list[i];
      pir_name = player_ob->short();
      if (!(player_ob->query_invis())||!player_ob->query_wiz_level())
         {
         eyepatch = present(EYEPATCH_ID, player_ob);
         if(eyepatch && player_ob->short() && !(player_ob->query_ghost()))
            {
            player_ob->catch_msg(TP->short()+" proposes a toast.\n");
          }
        }
   }
   return 1;
}


int
is_member(mixed who)
{
   object ob;
   
   if (!who)
      return 0;
   if (stringp(who))
      ob = find_player(lower_case(who));
   else
      if (objectp(who))
      ob = who;
   else
      return 0;
   if (!ob || !interactive(ob))
      return 0;
if (ob->query_guild_name_occ()==GUILD_NAME)
      return 1;
   return 0;
}


int
do_give_explanation(string str)
{
   if(ghost())
      return fail_ghost();
   if(!str)
      return 0;
   str = lower_case(str);
   if(str == "eyepatch" || str == "ep")
      {
      seteuid(geteuid());
      cat(HELP_DIR + "eyepatch_info.txt");
      return 1;
   }
   if(str == "pirate emotes" || str == "pe")
      {
      seteuid(geteuid());
      cat(HELP_DIR + "pe.txt");
      return 1;
   }
   if(str == "pirate levels" || str == "pirate titles" || str == "pl" || str == "pt")
      {
      seteuid(geteuid());
      cat(HELP_DIR+"pl.txt");
      return 1;
   }
   return 0;
}

int
is_founder(string str)
{
   if(!str)
      return 0;
   if(SECURITY->query_wiz_dom(str) == DOMAIN_NAME)
      return 1;
}

static int
new_soul(string str)
{
   object *u1;
   string *souls;
   int i, silence;
   
   if(!is_founder(this_player()->query_real_name()))
      return 0;
   
   if (str == "-s")
      silence = 1;
   else
      silence = 0;
   
   seteuid(getuid());
   u1 = users();
   
   for(i=0; i <sizeof(u1);i++)
   {
      if(u1[i] == this_player())
         continue;
      
      souls = u1[i]->query_cmdsoul_list();
      
      if(member_array(OWN_SOUL, souls) == -1)
         continue;
      
      
      if(!silence)
         tell_object(u1[i],"You feel different somehow, almost as if "+
         "you were a new pirate.\n");
      u1[i]->update_hooks();
      write("Gave "+capitalize(u1[i]->query_real_name())+
         " a new soul.\n");
   }
   write("Ok.\n");
   return 1;
}

static int
do_renew(string str)
{
   object eyepatch, player_ob;
   object *list;
   int i, silence, test;
   
   if(!is_founder(this_player()->query_real_name()))
      return 0;
   if(!str)
      silence = 0;
   else if (str == "-s")
      silence = 1;
   
   list = filter_array(users(),"is_member",this_object());
   i=0;
   for(i=0;i<sizeof(list);i++)
   {
      if((player_ob=list[i]) != this_player())
         {
         eyepatch = present(EYEPATCH_ID, player_ob);
         eyepatch->remove_object();
         eyepatch = clone_object(EYEPATCH_FILE);
         if(silence)
            eyepatch->set_silent();
         eyepatch->move(player_ob);
         if(!silence)
            player_ob->catch_msg(QCTNAME(TP)+" gives you a new eyepatch.\n");
         write("Replaced the eyepatch of "
            + capitalize(player_ob->query_real_name()));
         if(silence)
            write(" silently");
         write(".\n");
       }
   }
   return 1;
}

static int
do_eyepatch(string str)
{
   object eyepatch, name;
   object list;
   int i, silence, test;
   
   if(!is_founder(TP->query_real_name()))
      return 0;
   
   NF("That person isn't here.\n");
   if(!str || !strlen(str))
      return 0;
   
   name = find_living(str);
   
   NF("That person is not in the game at present.\n");
   if(!name)
      return 0;
   
   setuid();
   seteuid(getuid());
   eyepatch = clone_object(EYEPATCH_FILE);
   if(!present(EYEPATCH_ID,name))
      {
      eyepatch->move(name, 1);
      name->catch_msg(QCTNAME(TP)+" gives you an eyepatch.\n");
      TP->catch_msg("Replaced the eyepatch of "+QCTNAME(name)+".\n");
      return 1;
   }
   NF("That person already has an eyepatch.\n");
   return 0;
}

static int
do_eyepatch2(string str)
{
   object eyepatch, name;
   object list;
   int i, silence, test;
   
   if(!is_founder(TP->query_real_name()))
      return 0;
   
   NF("That person isn't here.\n");
   if(!str || !strlen(str))
      return 0;
   
   name = find_living(str);
   
   NF("That person is not in the game at present.\n");
   if(!name)
      return 0;
   
   eyepatch = present(EYEPATCH_ID,name);
   if(present(EYEPATCH_ID,name))
      {
      eyepatch->remove_object();
      TP->catch_msg("Removed the eyepatch of "+QCTNAME(name)+".\n");
      return 1;
   }
   NF("That person didn't have an eyepatch.\n");
   return 0;
}

static int
new_shadow(string str)
{
   object shadow, name;
   object list;
   int i, silence, test;
   
   if(!is_founder(TP->query_real_name()))
      return 0;
   
   NF("That person isn't here.\n");
   if(!str || !strlen(str))
      return 0;
   
   name = find_living(str);
   
   NF("That person is not in the game at present.\n");
   if(!name)
      return 0;
   
   setuid();
   seteuid(getuid());
   shadow = clone_object(PIRATE_SH);
   NF("Not able to clone the shadow.\n");
   if(!shadow)
      return 0;
   
write("about to enter if\n");
   NF(QCTNAME(name)+" was not shadowed.\n");
   if(shadow->shadow_me(name,GUILD_TYPE,GUILD_STYLE,
            GUILD_NAME)!=1)
   {
write("inside if\n");
      shadow->remove_object();
      return 0;
   }
   TP->catch_msg("Added the pirate shadow to "+QCTNAME(name)+".\n");
   return 1;
}
