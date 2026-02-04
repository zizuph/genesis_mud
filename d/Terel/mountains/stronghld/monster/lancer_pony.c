/*

Terel's implementation of the standard steed.

coded by Trofast 4-1999

Horse modified for use with Dwarven Lancers 
Tomas  -- Feb. 2000

*/

inherit "/d/Genesis/steed/steed.c";

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/calathin/npc/terel_horse_saddlebag.c"

string *descs = ({"black","white","dappled","chestnut","reddish","brown",
                   "grey","tall","strong","young","frisky","wild","tame",
                   "black-maned", "white-maned","grey-maned", "brown-maned",
                   "black-tailed","white-tailed","grey-tailed",
                   "brown-tailed","spotted","sturdy","old"});

string *types = ({"pony"});

int price=0;

int
set_terel_horse_stats(string type)
{

  switch (type)
    {
    case "mare": {
      set_gender(G_FEMALE);
      set_m_in("comes dociley trotting in");
      set_m_out("trots");   
      set_long("This is a mare from Terel.  "+
               capitalize(TO->query_possessive())+
        " bright eyes watch you closely.\n"+"@@additional_longdesc@@");
      price=25;
      set_stats(({ 100, 80, 100, 30, 30, 120 }));
      break;
    }

    case "pony": {
      set_gender(G_MALE);
      set_m_in("prances in");
      set_m_out("prances");   
      set_long("This is one of the fabled dwarven " +
        "lancer ponies. Born and bred in the mountains, " +
        "this small horse looks very sturdy. The ponies " +
        "are trained at birth to only serve their lancer masters. " +
        "Its mane is braided tightly using leather cords.\n"+
        "@@additional_longdesc@@");
      price=15;
      set_stats(({ 75, 75, 75, 30, 30, 120 }));
      break;
    }
      
    case "stallion":{
      set_gender(G_MALE);
      set_m_in("comes galloping in");
      set_m_out("gallops");   
      set_long("This is a stallion from Terel.  "+
               capitalize(TO->query_pronoun())+
        " prances restlessly about.\n"+"@@additional_longdesc@@");
      price=50;
      set_stats(({ 140, 140, 140, 30, 30, 120 }));
      break;
}

    case "gelding":{
      set_gender(G_MALE);
      set_m_in("comes galloping in");
      set_m_out("gallops");   
      set_long("This is a gelding from Terel.  "+
               capitalize(TO->query_possessive())+
        " bright eyes watch you closely.\n"+"@@additional_longdesc@@");
      price=25;
      set_stats(({ 100, 100, 100, 30, 30, 120 }));
      break;
    }

    case "mule":{
      set_m_in("reluctantly walks in");
      set_m_out("walks");   
      set_long("This is a mule from Terel.  "+
               capitalize(TO->query_possessive())+
        " bright eyes watch you closely.\n"+"@@additional_longdesc@@");
      price=20;
      set_stats(({ 136, 80, 100, 30, 30, 120 }));
      break;
    }

    }
return 1;

}

void
feed_me()
{
int j, food,drink;
object horse=TO;

food= horse->eat_max() / 6;
drink=horse->drink_max() / 20;

    //can only eat 1/6 of your max at once.
    for (j=0;j<6;j++)   horse->eat_food(food);

    //top it off
    horse->eat_food (horse->eat_max() 
         - horse->query_stuffed());

    //can only drink 1/20 of your max at once 
    for (j=0;j<20;j++)  horse->drink_soft(drink);

}

void
create_steed()
{ string type, desc;

  if (!IS_CLONE) return;

  type = types[random(sizeof(types)) ];
  desc = descs[random(sizeof(descs)) ];

  set_race_name(type);
  set_name("pony");
  add_name("steed");
  add_name("horse");
  add_name("terel_ass_pony");  //blame it on Shinto 
  set_gender(random(2));
  add_adj (desc);

  /*   set_long("@@set_long_desc@@"); */
  
  /*  add_valid_dest(ROOM_I_ALLOW_STEED);
      add_invalid_dest(ROOM_I_NO_ALLOW_STEED); */

  set_max_riders(2);
  allow_mounted_combat(0);
  set_no_trans(0);
  set_allowed_food(({"hay", "oats", "barley", "sugar","apple","banana",
                       "grapefruit","grass","orange","bread","carrot"}));

  set_skill(SS_CLIMB, 30);
  set_skill(SS_UNARM_COMBAT, 75);
  set_skill(SS_DEFENCE, 70);
  set_skill(SS_SWIM, 40); 

  set_terel_horse_stats(type);
  
  set_alarm(2.0,0.0, feed_me);


}

public int
can_lead(object ob)
{
  if (ob->query_race_name() == "goblin")
    {
      command("emote snorts in defience");
      return 0;
    }

  if (ob->query_skill(SS_ANI_HANDL) <20)
    {
      write ("You can't handle animals well enough!\n");
      return 0;
    }

  if (ob->query_name() != "_lancer")
    {
      command("emote backs away, baring its teeth in warning");
      return 0;
    }

return 1;
}


public int
can_mount(object ob)
{
  //here we check various player races and horse types, to
  //see if it's appropriate for the player to mount.

  string horse_race=TO->query_race_name();

if (ob->query_name() != "_lancer")
    {
       write("The pony resists your attempt to mount it.\n");
       return 0;
    }
        
if (ob->query_skill(SS_RIDING) <20)
  {
    write("You can't ride well enough!\n");
    return 0;
  }

//Check if the player has any mounted combat skill, if so we allow it.
if (ob->query_skill(SS_MOUNTED_COMBAT))
  {
    allow_mounted_combat(1);
  }
  return 1;
}

public int
list_price()
{
  return price;
}

public int
check_mounted_destination(object room)
{
  if (room->query_prop(ROOM_I_INSIDE))
    {
      if (!environment()->query_prop(ROOM_I_INSIDE))
        {
          return room->query_prop(ROOM_I_ALLOW_STEED);
        }
      else
        {
          return (room->query_prop(ROOM_I_NO_ALLOW_STEED) ? 0 : 1);
        }
    }
  return (room->query_prop(ROOM_I_NO_ALLOW_STEED) ? 0 : 1);
}                

void
init_living()
{
  add_action("do_fill", "fill");
  add_action("do_empty","empty");
  add_action("do_drape", "drape");
  add_action("do_remove","remove");
  add_action("do_close", "close");
  add_action("do_open", "open");
  ::init_living();
}
