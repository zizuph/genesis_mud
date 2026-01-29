inherit "/std/container";

#include "default.h"
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <macros.h>

/* prototypes */
void reset_container();
int do_smash(string str);
int do_open(string str);
int do_close(string str);
int do_pick(string str);

void
create_container()
{
   set_name("strongbox");
   add_name("box");
   add_adj("iron");
   set_pname("strongboxes");
   set_short("iron strongbox");
   set_pshort("iron strongboxes");
   set_long("@@st_long");
   add_prop(CONT_I_MAX_WEIGHT, 20000);
   add_prop(CONT_I_MAX_VOLUME, 20000);
   add_prop(OBJ_M_NO_GET, 1);      /* Can't get it. */
   add_prop(CONT_I_RIGID, 1);      /* It's rigid. */
   add_prop(CONT_I_CLOSED, 1);     /* It's closed. */
   add_prop(CONT_I_LOCK, 1);       /* It's locked. */
   add_prop(CONT_I_WEIGHT, 3000);
   add_prop(CONT_I_VOLUME, 5000);
   add_prop(CONT_I_HEIGHT, 50);
   
   add_item("runes","The runes are all traced in bright red and don't " +
      "appear to be active in any shape or form.\n");
   add_item("iron","The iron looks tough and thick.\n");
   add_item(({"lock", "padlock"}), "@@lock_desc");
   
   add_prop(OBJ_S_WIZINFO, break_string("This is a strongbox which is part "+
         "of the Royalty quest of Emerald. It will contain(or will have) "+
         "a gemstone which the resourceful player will have to get. "+
         "They need the pick axe from the miner to break open the padlock "+
         "on the strongbox, then get the gemstone from it.", 76));
   
   enable_reset();
   reset_container();
}

void
reset_container()
{
   if(!present("gem", TO))
      {
      seteuid(getuid());
      /*
      change_prop(CONT_I_LOCK, 0);
      change_prop(CONT_I_CLOSED, 0);
      */
      clone_object("/d/Emerald/telberin/obj/gem.c")->move(TO, 1);
   }
   
   change_prop(CONT_I_LOCK, 1);
   change_prop(CONT_I_CLOSED, 1);
}

string
lock_desc()
{
   if(!query_prop(CONT_I_LOCK))
      {
      return "The padlock is smashed to pieces.\n";
   }
   return "The padlock looks strong and unbreakable to you.\n";
}

string
st_long()
{
   string sm_st;
   if(!query_prop(CONT_I_LOCK))
      sm_st = " The padlock has been smashed.";
   else
      sm_st = "";
   return "This strongbox is made of hard iron, with several runes traced " +
   "on the surface. There is a padlock on it." + sm_st + "\n";
}

void
init()
{
   ::init();
   add_action(do_smash, "smash");
   add_action(do_smash, "break");
   add_action(do_smash, "force");
   add_action(do_open, "open");
   add_action(do_close, "close");
   add_action(do_pick, "pick");
}

int
do_pick(string str)
{
   NF("Pick what?\n");
   if(!strlen(str))
      return 0;
   
   if(str != "lock" && str != "padlock")
      {
      write("Pick what? Your nose?\n");
      return 1;
   }
   write("You try to pick the " + str + " but fail miserably.\n");
   return 1;
}

int
do_open(string str)
{
   if(!(parse_command(str, TP, " [iron] 'box' / 'strongbox' ")))
      {
      NF("What do you want to open?\n");
      return 0;
   }
   
   if(query_prop(CONT_I_LOCK))
      {
      write("The box is locked.\n");
      return 1;
   }
   if(!query_prop(CONT_I_CLOSED))
      {
      write("The box is already open.\n");
      return 1;
   }
   
   write("You open the strongbox.\n");
   say(QCTNAME(TP) + " opens the strongbox.\n");
   add_prop(CONT_I_CLOSED, 0);
   return 1;
}

int
do_close(string str)
{
   if(!(parse_command(str, TP, " [iron] 'box' / 'strongbox' ")))
      {
      NF("What do you want to close?\n");
      return 0;
   }
   
   if (query_prop(CONT_I_LOCK))
      {
      NF("The strongbox is locked, you imbecile!\n");
      return 0;
   }
   
   if (query_prop(CONT_I_CLOSED))
      {
      NF("The box is already closed.\n");
      return 0;
   }
   
   write("You close the strongbox.\n");
   say(QCTNAME(TP) + " closes the strongbox.\n");
   change_prop(CONT_I_CLOSED, 1);
   return 1;
}

/* This function is currently obseolete. */
string
process_verb()
{
   string verb;
   
   verb = query_verb();
   
   /* specify "es" for all verbs that don't get "s" */
      if (verb == "smash") return "smashes";
   
   /* Else you get verb + "s" */
   return (verb + "s");   
}

int
do_smash(string str)
{
   object ob;
   
   if(str == "padlock" || str == "lock")
      {
      NF("What do you want to "+query_verb()+" the padlock with?\n");
      return 0;
   }
   
   if(!query_prop(CONT_I_LOCK))
      {
      NF("The padlock is already smashed.\n");
      return 0;
   }
   
   if (!parse_command(str, environment(this_player()), 
            "'padlock' / 'lock' 'with' %o", ob))
   {
      NF(capitalize(query_verb()) + " what with what?\n");
      return 0;
   }
   
   if(function_exists("create_object", ob) == "/std/weapon")
      {
      int wt;
      
      wt = (int)ob->query_wt();
      
      if (wt == W_KNIFE || wt == W_SWORD)
         {
         NF("You shouldn't use your " + check_call(ob->short()) + " to " +
            query_verb() + " the padlock with.\n");
         return 0;
      } 
      
      if(!(random(4)))
         {
         write("You "+query_verb()+" the padlock and it disintegrates "+
            "with a resounding crack.\n");
         say(QCTNAME(TP) + " smashes the padlock with a resounding crack.\n");
         ob->set_dull(ob->query_dull() + 4);
         change_prop(CONT_I_LOCK, 0);
         remove_prop(CONT_I_LOCK);
         return 1;
      }
      else
         {
         write("You "+query_verb()+" the padlock, but it won't give yet.\n");
         say(QCTNAME(TP) + " hits the padlock, but it won't give yet.\n");
         ob->set_dull(ob->query_dull() + 2);
         return 1;
      }
   }
   NF("You hit the padlock but nothing happens.\n");
   return 0;
}

