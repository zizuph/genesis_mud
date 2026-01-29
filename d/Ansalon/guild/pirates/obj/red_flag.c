#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/object";
inherit "/cmd/std/command_driver";


object shadow; 
int act_alarm;

string* flag_acts  = ({"The war-torn Red Dragonarmy flag flutters in the breeze.\n",
                       "Sunlight glints off of a silver thread woven "+
                       "into the war-torn Red Dragonarmy flag.\n", 
                       "A drop of blood drips slowly down the war-torn Red "+
                       "Dragonarmy flag.\n",
                       "The wind dies down, eerily bringing the war-torn Red "+
                       "Dragonarmy flag to a complete standstill.\n",
                       "A strong gust of wind blows in, almost ripping "+
                       "the war-torn Red Dragonarmy flag from its place in the ground.\n"}); 
 
void 
create_object()
{
   set_name("flag");
   add_name("_nav_pirate_jolly_flag");
   set_adj("Red");
   add_adj("red");
   add_adj("war-torn");
   add_adj("Dragonarmy");
   add_adj("dragonarmy");
   set_short("war-torn Red Dragonarmy flag");
   set_long("This is the flag of the mighty Red Dragonarmy.  It is blood-red "+
            "and adorned with a five-headed, multi-coloured dragon, which is flying "+
            "above a black-sailed Pirate ship.  The flag is war-torn and "+
            "blood-splattered from the many battles it has seen.\nYou notice "+
            "some words sewn into the corner of the flag.\n");
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
   object player = this_player();
   string* how;

   if(!strlen(args))
   {
     notify_fail("Wave what? The flag?\n");
     return 0;
   }
   if(!parse_command(args, ({}), "[the] [war-torn] [red] [dragonarmy] 'flag' %w") &&
      !parse_command(args, ({}), "[the] [war-torn] [Red] [dragonarmy] 'flag' %w") &&
      !parse_command(args, ({}), "[the] [war-torn] [Red] [Dragonarmy] 'flag' %w") &&
      !parse_command(args, ({}), "[the] [war-torn] [red] [Dragonarmy] 'flag' %w"))
   {
     if(!parse_command(args, ({}), "[the] [war-torn] [red] [dragonarmy] 'flag'") &&
        !parse_command(args, ({}), "[the] [war-torn] [red] [Dragonarmy] 'flag'") &&
        !parse_command(args, ({}), "[the] [war-torn] [Red] [dragonarmy] 'flag'") &&
        !parse_command(args, ({}), "[the] [war-torn] [Red] [Dragonarmy] 'flag'"))
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

       player->catch_tell("You wave the war-torn Red Dragonarmy flag, declaring: "+
                          "'No life will be spared, no Quarter will be given!\n");
       tell_room(environment(player), QCTNAME(player)+" waves the war-torn Red Dragonarmy flag, declaring: '"+
                 "No life will be spared, no Quarter will be given!'\n", player);
       return 1;
     }
   }
   how = parse_adverb(args, "", 1);
   if(!present("_nav_pirate_jolly_flag", player))
   {
     player->catch_tell("You need to hold a flag before you can wave it.\n");
     return 1;
   }
   player->catch_tell("You "+how[1]+" wave the war-torn Red Dragonarmy flag, declaring: "+
                      "'No life will be spared, no Quarter will be given!\n");
   tell_room(environment(player), QCTNAME(player)+" "+how[1]+" waves the war-torn Red Dragonarmy flag, declaring: '"+
             "No life will be spared, no Quarter will be given!'\n", player);
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
    object* flags;
    int check = 0;
    string* how;

    if(!strlen(args))
    {
      notify_fail("Plant what? The flag?\n");
      return 0;
    }
    if(!parse_command(args, ({}), "[the] [war-torn] [red] [dragonarmy] 'flag' %w") &&
       !parse_command(args, ({}), "[the] [war-torn] [red] [Dragonarmy] 'flag' %w") &&
       !parse_command(args, ({}), "[the] [war-torn] [Red] [dragonarmy] 'flag' %w") &&
       !parse_command(args, ({}), "[the] [war-torn] [Red] [Dragonarmy] 'flag' %w"))
    {
      if(!parse_command(args, ({}), "[the] [war-torn] [red] [dragonarmy] 'flag'") &&
         !parse_command(args, ({}), "[the] [war-torn] [red] [Dragonarmy] 'flag'") &&
         !parse_command(args, ({}), "[the] [war-torn] [Red] [dragonarmy] 'flag'") &&
         !parse_command(args, ({}), "[the] [war-torn] [Red] [Dragonarmy] 'flag'"))
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
        player->catch_tell("You plant the war-torn Red Dragonarmy flag, "+
                           "claiming this land by force and without mercy.\n");

        tell_room(environment(player), QCTNAME(player)+" plants a war-torn Red Dragonarmy flag, "+
                  "claiming this land in the name of the Highlord Ariakas.\n", player);
      }
    }
    else
    {
      how = parse_adverb(args, "", 1);

      player->catch_tell("You plant the war-torn Red Dragonarmy flag, "+how[1]+
      " claiming this land in the name of the Highlord Ariakas.\n");

      tell_room(environment(player), QCTNAME(player)+" plants a war-torn Red Dragonarmy flag, "+how[1]+
                " claiming this land in the name of the Highlord Ariakas.\n", player);
    }

    set_short("war-torn Red Dragonarmy flag hanging from a spar");
    add_item("spar", "The spar is planted in the ground.\n");
    add_prop(OBJ_I_NO_GET, "The war-torn Red Dragonarmy flag is stuck in the ground and can not be taken.\n");
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

  if(parse_command(args, ({}), "[the] [red] [dragonarmy] 'flag'") ||
     parse_command(args, ({}), "[the] [red] [Dragonarmy] 'flag'") ||
     parse_command(args, ({}), "[the] [Red] [dragonarmy] 'flag'") ||
     parse_command(args, ({}), "[the] [Red] [Dragonarmy] 'flag'"))
  {
    this_player()->catch_tell("You grab hold of the "+short()+
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

