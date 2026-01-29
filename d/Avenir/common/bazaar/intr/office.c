// updates:  Lilith May 2022: added limiter to how many messengers can be 
//              purchased before the guard needs to summon more. Added
//              whistles. Looks like the "new" office with whistles for
//              sale never got copied over.

inherit "/std/room";
inherit "/lib/trade";
inherit "/d/Avenir/inherit/room_tell";
#include "../bazaar.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "/d/Avenir/include/relation.h"

// 6 * 1 gold each + 1 gold for convenience
#define WHISTLE_VAL 1008
#define WHISTLE_MAX 5
// 1 gold each
#define WAIF_VALUE  144
#define WAIF_MAX 12

#define NUM sizeof(MONEY_TYPES) 

int waif, whit, alarm_id, alarm_id2;

void
create_room() 
{
   set_short("A place to hire child messengers");
   set_long("A dark, dusty room smelling of stale sweat and ammonia. "+
      "The only way out seems to be by the stairs you came up. "+
      "A single lantern swings from the rafters, casting a pool "+
      "of light over a long, narrow table. Along one side of the "+
      "table huddles a group of small children. They appear to be "+
      "staying out of the range of the guard's flail and feet.\n"+
      "Several small children and a dark-eyed half-elf guard.\n");

 
   set_tell_time(45);
   add_tell("The dark-eyed half-elf says: If you want a messenger, "+
      "you can <hire child>.\n");
   add_tell("The dark-eyed half-elf guard watches you and the children "+
      "carefully.\n");
   add_tell("The dark-eyed half-elf kicks one of the small children.\n");

   add_item("table", "It is a long, narrow table, covered with dust.\n");
   add_item("dust", "There is lots of it!\n");
   add_item(({"lamp", "lantern", "light", "pool", "mineral"}),
       "The lantern has a fist-sized piece of mineral in it. "+
       "The mineral glows weakly, casting a small pool of light "+
       "onto the table.\n");
   add_item("stairs", "The stairs lead down into brightness.\n");	   
   add_cmd_item(({"lamp", "lantern", "light", "pool", "mineral"}),
       ({"get", "take", "open"}), "The dark elf snaps his flail "+
       "at you.\nPerhaps you shouldn't be trying that?\n");
   add_item(({"child", "children", "small children", "waif"}),
       "This unwashed waif is the orphan of Sybarite slaves.\n"+
       "He earns his food and a corner to sleep in by running "+
       "messages for his master or mistress.\nHe looks coarse.\n"+
       "He seems to be feeling very well.\n");
   add_item(({"guard", "elf", "half-elf"}),
       "This half-elf looks both cruel and unhappy.\n"+
       "He is here to guard the childen and sell them as messengers.\n"+
       "If you want to hire a messenger, try <hire child> for 1gc.\n"+
	   "If you want to whistle for your own messengers, try <buy "+
       "whistle> for 7gc.\n"+
	   "He is wielding a thick-handled flail.\nHe looks "+
       "ugly.\nHe seems to be feeling very well.\n");
   add_cmd_item(({"guard", "half-elf", "child"}), "kill",
       "Not in here!\n");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.
    add_prop(ROOM_M_NO_ATTACK, "The goddess Azauph is the patron here. It "+
	    "would not be wise to try fighting in this place.");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "The goddess Azauph is the patron here."+
	    "It would not be wise to try fighting in this place.");


   add_exit("/d/Avenir/common/bazaar/intr/post", "down", 0, 0, 1);
   add_exit("/d/Avenir/common/bazaar/intr/post", "stairs", 0, 0, 1);

   config_default_trade();
   set_money_give_out(   ({ 10000,    32,   2,    1 }));
   set_money_give_reduce(({     0,     4,   2,    1 })); 

   add_npc("/d/Avenir/common/mon/porter", 1, &->arm_me());
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);

  if (interactive(ob))
    start_room_tells();
}      

void
clear_waif()
{
    waif = 0;
    alarm_id = 0;
    tell_room(this_object(), "A dozen messengers sidle up to the guard and "+
        "tug on his sleeves.\n");
}


void
clear_count() 
{
    whit = 0;
    alarm_id2 = 0;
    tell_room(this_object(), "A child messenger arrives and hands the "+
        "dark-elf guard some whistles.\n");    
}

int
do_hire(string str) 
{
    object child, tp;
    string item_name, pay_type, get_type, str1, coin_pay_text, coin_get_text;
    int *money_arr;

    notify_fail("Hire what, a child?\n");
    if (!strlen(str))
	return 0;

    tp = this_player();

    if (IS_INFIDEL(tp))
    {
        tell_object(tp, "The guard refuses to put children in the hands "+
            "of criminals.\n");
        return 1;
    }

    if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
        get_type = "";
        if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
        {
            pay_type = "";
            item_name = str;
        }
    }

    if (!(item_name == "waif" || item_name ==  "child" || 
          item_name == "messenger" || item_name == "messenger"))
        return 0;

    if (sizeof(money_arr = pay(WAIF_VALUE, tp, pay_type, 0, 0, get_type)) == 1)
    {
        if (money_arr[0] == 1)
        {
            tell_room(this_object(), "The dark-eyed half-elf says : I fear "+
                "you cannot afford a messenger with only those "+
                "coins, "+ tp->query_nonmet_name() +".\n");
            return 1;
        }
        if (money_arr[0] == 2)
        {
            tell_room(this_object(), "The dark-eyed half-elf says: You have no "+ 
                pay_type + " coins on you, "+ tp->query_nonmet_name() + 
                ".\n");
            return 1;
        }
        else
        {
            tell_room(this_object(), "The dark-eyed half-elf says: I fear you "+
                "cannot afford a messenger, "+ tp->query_nonmet_name() + 
                ".\n");
            return 1;
        }
    }

    if (alarm_id)
    {
        tell_room(this_object(), "The dark-eyed half-elf says: I've summoned "+
             "more messengers... these are resting. Try again shortly, "+ 
                tp->query_nonmet_name() +".\n");
        return 1;
    }

    if (waif > WAIF_MAX)
    {
        tell_room(this_object(), "The dark-eyed half-elf says: I need a "+
                "minute to whistle up some more messengers, "+ 
                tp->query_nonmet_name() +".\n");
        tell_room(this_object(), "The dark-eyed half-elf blows a white "+
                "gold whistle.\n");
        alarm_id = set_alarm(60.0, 0.0, clear_waif);
        return 1;
    }     
  
    waif++;
    child = clone_object("/d/Avenir/common/bazaar/intr/child.c");
    if (child->move(tp))
    {
        write("You cannot carry that much!\n");
        child->remove_object();
        return 1;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    write("You pay "+ coin_pay_text +" and hire yourself a messenger.\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " back from the dark-eyed "+
        "half-elf.\n");
    return 1;
}


int
do_buy(string str) 
{
    object whistle, tp;
    string item_name, pay_type, get_type, str1, coin_pay_text, coin_get_text;
    int *money_arr;

    notify_fail("Buy what, a whistle?\n");
    if (!strlen(str))
	return 0;

    tp = this_player();

    if (IS_INFIDEL(tp))
    {
        tell_object(tp, "The guard refuses to put children in the hands "+
            "of criminals.\n");
        return 1;
    }

    if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
        get_type = "";
        if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
        {
            pay_type = "";
            item_name = str;
        }
    }

    if (!(item_name == "whistle"))
        return 0;

    if (sizeof(money_arr = pay(WHISTLE_VAL, tp, pay_type, 0, 0, get_type)) == 1)
    {
        if (money_arr[0] == 1)
        {
            tell_room(this_object(), "The dark-eyed half-elf says : I fear "+
                "you cannot afford a whistle with only those "+
                "coins, "+ tp->query_nonmet_name() +".\n");
            return 1;
        }
        if (money_arr[0] == 2)
        {
            tell_room(this_object(), "The dark-eyed half-elf says: You have no "+ 
                pay_type + " coins on you, "+ tp->query_nonmet_name() + 
                ".\n");
            return 1;
        }
        else
        {
            tell_room(this_object(), "The dark-eyed half-elf says: I fear you "+
                "cannot afford a whistle, "+ tp->query_nonmet_name() + 
                ".\n");
            return 1;
        }
    }
	
    if (alarm_id2)
    {
        tell_room(this_object(), "The dark-eyed half-elf says: I'm out "+
            "of whistles for now, try again in 5 to 10 minutes, "+ 
            tp->query_nonmet_name() +".\n");
        return 1;
    }

    if (whit > WHISTLE_MAX)
    {
        tell_room(this_object(), "The dark-eyed half-elf says: I am "+
                "out of stock on whistles. Try later, "+ 
                tp->query_nonmet_name() +".\n");
	    // 6 minute wait.
        alarm_id2 = set_alarm(360.0, 0.0, clear_count);
        return 1;
    }     
  
    whit++;
    // This file is a copy of the one in the Union dir.
    whistle = clone_object("/d/Avenir/common/bazaar/Obj/misc/whistle");
    if (whistle->move(tp))
    {
        write("You cannot carry that much!\n");
        whistle->remove_object();
        return 1;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    tell_room(this_object(), "The dark-eyed half-elf says to the "+
    "sybarite porter: They're talking to me, you fool!\n");
    write("You pay "+ coin_pay_text +" and get a whistle.\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " back from the dark-eyed "+
        "half-elf.\n");
    return 1;
}


void
init() 
{
    ::init();
    add_action(do_hire,"hire",0);
	add_action(do_buy, "buy", 0);
}
