inherit "/std/object";
inherit "/cmd/std/command_driver";
#include <macros.h>
#include <stdproperties.h>

#define CIGAR_SUBLOC "_smoking_cigar"

int lit;
int burned_out;
int i;
string cigar_status;

int let_burn();

void

create_object()
{
   set_name("cigar");
   set_pname("cigars");
   add_name("butt");
   add_pname("butts");
   add_name("stogie");
   add_pname("stogies");
   set_adj("big");
   set_adj("foot-long");
   set_adj("long");
   set_short("@@short_status");
   set_pshort("@@pshort_status");
   set_long("@@long_status");
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 60);
   add_prop(OBJ_M_NO_DROP,"@@drop_cigar");
   add_prop(OBJ_M_NO_GIVE,"@@give_cigar");
}

string
long_status()
{
   if(i==0)
      cigar_status="\n";
   if(lit && !burned_out)
      return "This is a big stinky cigar.\n"+
   "It is lit. "+cigar_status;
   if(burned_out)
      return "This is a smelly cigar butt.\n";
   if(!lit && !burned_out)
      return "This is a big stinky cigar.\n";
}

string
short_status()
{
   if(burned_out)
      return "smelly cigar butt";
   else
      return "big foot-long stogie";
}

string
pshort_status()
{
   if(burned_out)
      return "smelly cigar butts";
   else
      return "big foot-long cigars";
}

string
drop_cigar()
{
   if(query_verb() == "give")
      return 0;
   if(lit && !burned_out)
      return "You can't drop a lit cigar.\n"+"Only you can prevent forest fires.\n";
   else
      return 0;
}

string
give_cigar()
{
   if(lit && !burned_out)
      return "Give away such a fine cigar?\n";
   else
      return 0;
}

void
init()
{
   ::init();
   add_action("blow","blow");
   add_action("do_light","light");
   add_action("do_light","smoke");
   add_action("do_extinguish","extinguish");
   add_action("do_puff","puff");
   add_action("do_smell","smell");
   add_action("do_smell","sniff");
   add_action("do_lick","lick");
}

int
blow(string arg)
{
   if(lit && !burned_out)
      {
      object *oblist;
      notify_fail("Blow smoke at whom?\n");
      if(!arg || arg == "smoke")
         {
         this_player()->catch_msg("You blow an array of puffy white "+
            "smoke rings.\n");
         say(break_string(QCTNAME(this_player())+" takes a big "+
               "puff of "+ this_player()->query_possessive() +" cigar and "+
               "blows a vast array of puffy white smoke rings.\n",74));
         return 1;
      }
      oblist = parse_this(arg, "'smoke' [at] [the] %l");
      if(!sizeof(oblist))
         return 0;
      target(" blows stinky cigar smoke right in your face!\n", oblist);
      actor("You blow cigar smoke in", oblist,"'s face!");
      all2actbb("blows smoke in", oblist,"'s face!");
      return 1;
   }
   if(burned_out)
      write("This old butt burned out long ago.\n");
   else
      write("The cigar is not lit.\n");
   return 1;
   
}

int
do_light(string arg)
{
   notify_fail("Light what?\n");
   if(!arg)
      return 0;
   if(arg == "cigar" || arg == "stogie")
      {
      if(burned_out)
         {
         write("This cigar has already been used.\n");
         return 1;
      }
      if(lit && !burned_out)
         {
         write("Your stogie is already burning.\n");
         return 1;
      }
      if(!lit && !burned_out)
         {
         write("You light the big stinky stogie.\n");
         allbb(" lights a big foot-long stogie.\n");
         this_player()->add_subloc(CIGAR_SUBLOC, this_object());
         lit=1;
        set_alarm(30.0, 30.0, let_burn);
         return 1;
      }
   }
   else
      return 0;
}

int
do_extinguish(string arg)
{
   notify_fail("Extinguish what?\n");
   if(!arg)
      return 0;
   if(arg == "cigar" || arg == "stogie")
      {
      if(!lit || burned_out)
         {
         write("You can not extiguish something that is not burning.\n");
         return 1;
      }
      if(lit && !burned_out)
         {
         write("You can not extinguish this cigar!\n");
      }
      return 1;
   }
}

int
do_puff(string arg)
{
   notify_fail("Puff what?\n");
   if(!arg)
      return 0;
   if(arg == "stogie" || arg == "cigar")
      {
      if(lit && !burned_out)
         {
         write("You take a puff of your cigar.\n");
         allbb(" puffs on "+ this_player()->query_possessive()+
            " cigar.\n");
         return 1;
      }
      if(burned_out)
         {
         write("You can not puff on an old unlit cigar butt.\n");
         return 1;
      }
      if(!lit)
         {
         write("You try to puff on your unlit cigar, but get nothing.\n");
         return 1;
      }
      return 1;
   }
}

int
do_smell(string arg)
{
   notify_fail("Smell what?\n");
   if(!arg)
      return 0;
   if(arg == "stogie" || arg == "cigar")
      {
      if(burned_out)
         {
         write("Unfortunately you can not determine the quality of this used cigar by its smell.\n");
         return 1;
         
      }
      if(lit && !burned_out)
         {
         write ("It has a fragrance only a buning "+
            "cigar can give.\n");
         return 1;
      }
      if(!lit)
         {
         write("You smell your cigar to determine its quality.\n"+"It is a fine cigar indeed!\n");
         allbb(" smells "+ this_player()->query_possessive() +
            " cigar to determine its quality.");
         return 1;
      }
      return 1;
   }
}

int
do_lick(string arg)
{
   notify_fail("Lick what?");
   if(!arg)
      return 0;
   if(arg == "cigar" || arg == "stogie")
      {
      if(!lit)
         {
         write("You lick the end of your cigar in preparation to smoke "+
            "it.\n");
         allbb(" licks "+ this_player()->query_possessive() +
            " cigar in preparation to smoke it.\n");
         return 1;
      }
      if(lit && !burned_out)
         {
         write("If you lick it while its lit, you may burn your tongue.\n");
         return 1;
      }
      if(burned_out)
         {
         write("Why would you want to lick an old smelly cigar butt?\n");
         return 1;
      }
      return 1;
   }
}



int
let_burn()
{
   if(i <= 19)
      {
      i++;
      tell_object(environment(this_object()),"i = "+i);
      say("Some ashes fall from "+
         QCTNAME(environment(this_object())) +"'s cigar.\n");
      tell_object(environment(this_object()),"Some "+
         "ashes fall from your cigar.\n");
      if(i <= 4)
         cigar_status = "You have smoked very little of the cigar.\n";
      if(i >= 5 && i < 10)
         cigar_status ="You have smoked 1/4 of the cigar.\n";
      if(i >= 10 && i < 15)
         cigar_status ="You have smoked 1/2 of the cigar.\n";
      if(i >= 15 && i < 18)
         cigar_status ="You have smoked 3/4 of the cigar.\n";
      if(i >= 18 && i <= 20)
         cigar_status ="You have almost finished this cigar.\n";
      return 1;
   }
   if(i = 20)
      {
      say(QCTNAME(environment(this_object()))+
         "'s cigar went out.\n");
      tell_object(environment(this_object()), "Your "+
         "cigar goes out.\n");
      this_player()->remove_subloc(CIGAR_SUBLOC, this_object());
      burned_out=1;
      return 0;
   }
}

string
query_recover()
{
   return MASTER;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
   if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if(for_obj == carrier)
      return "You are smoking a big foot-long stogie.\n";
   return capitalize(carrier->query_pronoun())+" is "+
   "smoking a big foot-long stogie.\n";
}

