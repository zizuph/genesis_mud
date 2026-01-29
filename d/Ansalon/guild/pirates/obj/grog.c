#pragma save_binary
#pragma strict_types

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>

//#include <language.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/object";

int WATER_AMOUNT = 25;
int ALCO_AMOUNT = 20;

int full = 100;
string chosen_decoration;

string* decorations = ({"large ship", "big skull", "parrot", "monkey",
                        "rusty iron hook", "pile of loot", "pirate "+
                        "fighting a shark", "treasure chest", "ship dog"});

string get_full_level();
string get_description();
string short_descr();
string pshort_descr();
string choose_decoration();

public nomask void
create_object()
{
    set_name("drink");
    add_name("bottle");
    set_pname("drinks");
    add_pname("bottles");
    add_name("grog");
    add_pname("grogs");
    add_adj("green");
    add_adj("glass");
    set_short(short_descr);
    set_pshort(pshort_descr);
    set_long("This is a @@short_descr@@ with a @@choose_decoration@@"+
               " painted on it. It must have taken quite some skill "+
               "to make that detailed decoration onto a glass bottle. "+
               "The bottle also carries a label stating its authenticity.\n"+
               "@@get_full_level@@.\n"+
               "@@get_description@@");
    add_item(({chosen_decoration, "decoration"}), "This is a @@c_decoration@@"+
               " decorated on the bottle.\n"); 
    add_item("label", "The label reads: Authentic grog of the Bloodsea!\n");
    add_prop(OBJ_M_NO_SELL, "Drinks are not to be resold.\n");
    add_prop(OBJ_I_VALUE, 350);
    add_prop(OBJ_I_WEIGHT, 350+random(200));
    add_prop(OBJ_I_VOLUME, 350+random(200));
    
    set_may_recover();
}

string get_full_level()
{
  switch(full)
  {
    case 0:
	return "There is no more grog in the bottle";
    case 1..15:
        return "There are still a few sips of grog left";
    case 16..45:
        return "It appears to be half full of grog";
    case 46..80:
        return "There is still plenty of grog left";
    case 81..100:
        return "There is grog enough for a long time";
    default: return "";
  }
}



string c_decoration()
{
  return chosen_decoration;
}

string choose_decoration()
{
  chosen_decoration = ONE_OF(decorations);
  return chosen_decoration;
}



string
get_description()
{
  if(!full) return "";

  if((this_player()->query_guild_name_lay())=="Pirate of the Bloodsea")
  {
    return "This drink looks very tempting.\n";
  }
  return "You might need to strengthen your sea legs before you attempt "+
         "this drink.\n";
}



string
short_descr()
{
  if(!full)
  {
    return "empty bottle of grog";
  }
  return "green bottle of grog";
}

string
pshort_descr()
{
  if(!full)
  {
    return "empty bottles";
  }
  return "green bottles of grog";
}

/*
 * Function name: query_soft_amount
 * Description  : Gives the amount of liquid in the drink.
 * Returns      : int - the amount.
 */
public int
query_soft_amount()
{
    return WATER_AMOUNT;
}

public int
query_alco_amount()
{
    return ALCO_AMOUNT;
}


int 
drink_grog(string args)
{
    int max_intox = this_player()->intoxicated_max();
    int pirate = 0;    
  
    if(args!="grog" && args !="from bottle" && args != "grog from bottle" &&
       args!="from green bottle")
    {
      notify_fail("Drink what?\n");
      return 0;
    }
    if(!full)
    {
      this_player()->catch_tell("You try to lick a few last drops out of "+
                                "your empty bottle.\n");
      tell_room(environment(this_player()), QCTNAME(this_player())+
                " sticks "+HIS(this_player())+" tongue into an empty "+
                "bottle.\n", this_player());
      return 1;
    }
    if(!this_player()->drink_soft(WATER_AMOUNT, 1))
    {
      this_player()->catch_tell("You should have stuck to grog, "+
                     "now you are too full to drink anymore.\n");
      return 1;
    }

    if(!this_player()->drink_alco(ALCO_AMOUNT, 1))
    {
      this_player()->catch_msg("You attempt to raise the "+short()+
                                " to your mouth to take a drink, but you "+
                                "only manage to hit yourself in the eye.\n");
      tell_room(environment(this_player()), QCTNAME(this_player())+
                " attempts to drink from a "+short()+" but manages to poke "
                +HIM(this_player())+"self in the eye instead.\n",
                this_player());
      return 1;
    }
    
    if(this_player()->query_guild_name_lay()=="Pirate of the Bloodsea")
    {
      this_player()->catch_tell("You take a swig of the grog and savour "+
                                "its flavour and burning sensation on "+
                                "your tongue and lips. Now that's the "+
                                "real thing!\n");
      tell_room(environment(this_player()), QCTNAME(this_player())+
                " takes a swig from "+HIS(this_player())+" "+short()+
                ".\n", this_player());
      this_player()->drink_alco(ALCO_AMOUNT);

      full--;      
      if(!full) add_adj("empty");
      return 1;
    }
    this_player()->catch_msg("You take a sip from the "+short()+
                             " and feel it burn as it goes down!"+
                             "\nYou feel your stomach's complaining "+
                             "twists.\n");
    this_player()->command("puke");
    full--;
    if(!full) add_adj("empty");
    return 1;
}


int 
fill_bottle(string args)
{
   if (!strlen(args))
   {
     notify_fail("Fill what?\n"); 
     return 0;
   }

   if(!parse_command(args, ({}), "[the] %o 'with' %s"))
   {
     notify_fail("Fill what with what?\n"); 
     return 0;
   }
   if(full)
   {
     this_player()->catch_tell("But your bottle is not empty yet!\n");
     return 1;
   }

   this_player()->catch_tell("You wouldn't feel right about filling "+
                             "using this bottle for anything but the "+
                             "authentic Bloodsea grog!\n");
   tell_room(environment(this_player()), QCTNAME(this_player())+
             " tips "+HIS(this_player())+" "+short()+
             " back and forth in "+HIS(this_player())+
             " hands as if considering something.\n");
   return 1;
}

int
empty_bottle(string args)
{
  if(args !="bottle" && args != "glass bottle" &&
     args!="green bottle" && args!="green bottle of grog" &&
     args!="bottle of grog" && args!="glass bottle of grog")
  {
    notify_fail("Empty what?\n");
    return 0;
  }
  if(!full)
  {
    this_player()->catch_tell("But your bottle is already empty!\n");
    tell_room(environment(this_player()), QCTNAME(this_player())+
              " turns "+HIS(this_player())+" bottle upside down, "+
              "wondering why it's empty!\n", this_player());
    return 1;
  }
  if(this_player()->query_guild_name_lay()=="Pirate of the Bloodsea")
  {
    this_player()->catch_tell("You take a deep breath, then empty "+
                              "the entire "+short()+" in one drawn.\n");
    this_player()->command("emote staggers around in a haze.");
    this_player()->set_intoxicated(this_player()->intoxicated_max());
    full = 0;
    return 1;
  }
  this_player()->catch_tell("You pour out the contents of the "+short()+
                            " feeling relieved you didn't have to "+
                            "drink it.\n");
  tell_room(environment(this_player()), QCTNAME(this_player())+
            " empties "+HIS(this_player())+" "+short()+
            ". What a waste!\n", this_player());
  full=0;
  return 1;
}

int
read_label(string args)
{
  if(args != "label" && args != "label on bottle")
  {
    notify_fail("Read what?\n");
    return 0;
  }
  this_player()->catch_tell("The label reads: Authentic grog of the "+
                            "Bloodsea!\n");
  tell_room(environment(this_player()), QCTNAME(this_player())+
            " looks at the label on "+HIS(this_player())+
            " "+short()+".\n", this_player());
  return 1;
}

public void init()
{
  ::init();
  add_action(drink_grog, "drink");
  add_action(fill_bottle, "fill");
  add_action(empty_bottle, "empty");
  add_action(read_label, "read");
}


string
query_recover()
{
    return MASTER + ":" + "&-&" + chosen_decoration + "&-&" + full + "&-&";
}

void
init_recover(string arg)
{
    sscanf(arg, "&-&%s&-&%d&-&", chosen_decoration, full);
}