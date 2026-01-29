#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/object";
inherit "/cmd/std/command_driver";


object shadow; 
int act_alarm;

string* flag_acts  = ({"The black Jolly Roger flutters in the breeze.\n",
                       "Sunlight glints off of a silver thread woven "+
                       "into the black Jolly Roger.\n", 
                       "A drop of blood drips slowly down the black "+
                       "Jolly Roger.\n",
                       "The wind dies down, eerily bringing the black "+
                       "Jolly Roger to a complete standstill.\n",
                       "A strong gust of wind blows in, almost ripping "+
                       "the black Jolly Roger from its place in the ground.\n"}); 
 
void 
create_object()
{
   set_name("flag");
   add_name("roger");
   add_adj("jolly");
   add_name("_nav_pirate_jolly_flag");
   set_adj("black");
   set_short("black Jolly Roger");

   set_long("This is the Jolly Roger, the dreaded flag of the deadly Pirates "+
            "of the Blood Sea. It is black and adorned with a gruesome "+
            "skeleton. In one hand, the skeleton holds a spear. In the other, "+
            "it raises a cup of grog in a fearless toast to Death. The flag's "+
            "intentions are clear: 'Woe betide any one who would dare to cross "+
            "its owner!'\nYou notice some words sewn into into the corner of "+
            "the flag.\n");
   add_prop(OBJ_I_VALUE, 300+random(200));
   add_prop(OBJ_I_WEIGHT,100+random(100)); 
   add_prop(OBJ_I_VOLUME, 100+random(100));
   add_prop(OBJ_I_NO_SELL, "The shopkeeper says: That has no value to me.\n");
   add_item(({"corner", "words"}), "The words read: <help flag> for information.\n");
   seteuid(getuid());
}

int
wave_flag(string args)
{
   string *how;
   object player = this_player();

   if(!strlen(args))
   {
     notify_fail("Wave what? The flag?\n");
     return 0;
   }
   if(!parse_command(args, ({}), "[the] [black] [Jolly] [Roger] 'flag' %w"))
   {
     if(!parse_command(args, ({}), "[the] [black] [Jolly] [Roger] 'flag'"))
     {
       notify_fail("Wave what? The flag?\n");
       return 0; 
     }
     else
     {
       if(!present("_nav_pirate_jolly_flag", player))
       {
        player->catch_tell("You need to hold a flag before you can wave it.\n");
        return 1;
       }
       player->catch_tell("You wave the Jolly Roger, boldly declaring: "+
                          "'No life will be spared, no Quarter given!\n");
       tell_room(environment(player), QCTNAME(player)+" waves the Jolly Roger, declaring: '"+
                 "No life will be spared, no Quarter given!'\n", player);
       return 1;
     }
   }
   how = parse_adverb(args, "", 1);
   if(!present("_nav_pirate_jolly_flag", player))
   {
     player->catch_tell("You need to hold a flag before you can wave it.\n");
     return 1;
   }
   player->catch_tell("You "+how[1]+" wave the Jolly Roger, boldly declaring: "+
                      "'No life will be spared, no Quarter given!\n");
   tell_room(environment(player), QCTNAME(player)+" "+how[1]+" waves the Jolly Roger, declaring: '"+
             "No life will be spared, no Quarter given!'\n", player);
   return 1;
}


void do_act()
{
  tell_room(environment(this_object()), ONE_OF(flag_acts));
}


/* Function to be called when the flag is planted */
public void check_alarm()
{
  object* players;
  object* objs;
  int was_player = 0;

  objs = all_inventory(environment(this_object()));
  for(int i = 0; i<sizeof(objs); i++)
  {
    if(interactive(objs[i]))
    {
      was_player = 1; 
      if(!act_alarm)
      {
        act_alarm = set_alarm(5.0,  60.0, &do_act());
        return;
      }
    }
  }
  if(was_player == 0)
  {
    remove_alarm(act_alarm);
    act_alarm = 0;
  }  

}



int check_args(object player)
{
    object* flags;

    if(!present("_nav_pirate_jolly_flag", player))
    {
      player->catch_tell("You need to hold a flag before you can plant one.\n");
      return 1;
    }

    if(environment(player)->query_prop(ROOM_I_INSIDE))
    {
      player->catch_tell("You can not plant your flag inside.\n");
      return 1;
    }

    flags = filter(all_inventory(environment(player)), &->id("_nav_pirate_jolly_flag"));
    
    for(int i = 0; i<sizeof(flags); i++)
    { 
      if(flags[i]->query_prop(OBJ_I_NO_GET))
      {
        player->catch_tell("But there is already a flag planted here!\n");
        return 1;
      }
    }
   return 0;
}


int
plant_flag(string args)
{
    object player = this_player();
    string *how;
    object* flags;
    int check = 0;

    if(!strlen(args))
    {
      notify_fail("Plant what? The flag?\n");
      return 0;
    }
    if(!parse_command(args, ({}), "[the] [black] [Jolly] [Roger] 'flag' %w"))
    {
      if(!parse_command(args, ({}), "[the] [black] [Jolly] [Roger] 'flag'"))
      {
        notify_fail("Plant what? The flag?\n");
        return 0; 
      }
      else
      {
        check = check_args(player);
        if(check == 1)
        {
          return 1;
        }
        player->catch_tell("You plant the Jolly Roger, "+
                           "claiming this land by force and without mercy.\n");

        tell_room(environment(player), QCTNAME(player)+" plants a Jolly Roger, "+
                  "claiming this land by force and without mercy.\n", player);
      }
    }
    else
    {
      how = parse_adverb(args, "", 1);

      player->catch_tell("You "+how[1]+" plant the Jolly Roger, "+
      "claiming this land by force and without mercy.\n");

      tell_room(environment(player), QCTNAME(player)+" "+how[1]+" plants a Jolly Roger, "+
                "claiming this land by force and without mercy.\n", player);
    }

    add_item("spar", "The spar is planted in the ground.\n");
    set_short("black Jolly Roger hanging from a spar");
    add_prop(OBJ_I_NO_GET, "The black Jolly Roger is stuck in the ground and can not be taken.\n");
    this_object()->move(environment(player), 1);
    seteuid(getuid());
    shadow = clone_object("/d/Ansalon/guild/pirates/shadow/flag_shadow");

    if(shadow->shadow_me(environment(player)) != 1)
    {
      shadow->destruct();
      notify_fail("You can't seem to plant a flag here.\n");
      return 0;
    }
    shadow->init_shadow(this_object(), environment(player), shadow);
    check_alarm();
    return 1;
}

void destroy_flag(object me)
{
  shadow->remove_shadow();
  me->remove_object();
}

int
break_flag(string args)
{
  if(!strlen(args))
  {
    return 0;
  }

  if(parse_command(args, ({}), "[the] [black] [Jolly] [Roger] 'flag'") ||
     parse_command(args, ({}), "[the] [black] 'Jolly' 'Roger'"))
  {
    this_player()->catch_tell("You grab hold of the planted black Jolly Roger"+
    " and defiantly break the spar to which it was attached.\nYou rip "+
    "the flag into pieces and discard all evidence its existance.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())+ 
    " grabs hold of the "+short()+" and defiantly breaks the spar to which it "+
    "was attached.\n"+QCTNAME(this_player())+" rips the flag into pieces and discards "+
    "all evidence of its existence.\n", this_player());
    set_alarm(0.0, 0.0, &destroy_flag(this_object()));
    return 1;
  }
  notify_fail("Break what?\n");
  return 0;
}

int
help_flag(string args)
{
  if(args == "flag")
  {
    this_player()->catch_tell("  ****************************************************************\n"+
                              "  *                                                              *\n"+
                              "  * wave flag  [how] : Allows you to wave your flag around.      *\n"+
                              "  * plant flag [how] : Plant your flag claiming this land.       *\n"+
                              "  * break flag       : Allows you to break and discard the flag. *\n"+
                              "  * help flag        : Gives you this help list.                 *\n"+
                              "  *                                                              *\n"+
                              "  ****************************************************************\n");
    return 1;
  }
  return 0;
}

int
read_words(string args)
{
  if(args == "words" || args == "the words")
  {
    this_player()->catch_tell("You can <help flag> for information on how to use this flag.\n");
    return 1; 
  }
  notify_fail("Read what? The words?\n");
  return 0;
}

public void init()
{
  ::init();
  add_action(wave_flag, "wave");
  add_action(plant_flag, "plant");
  add_action(break_flag, "break");
  add_action(help_flag, "help");
  add_action(read_words, "read");
}

