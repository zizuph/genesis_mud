/*Coded by Cinder using White Tree Pub (by Nick and Elessar) as example*/
inherit "/d/Gondor/common/room";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#include "/d/Gondor/defs.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */

object make_statue(string name, string adj, string long, int weight,
   int volume);

object  mason;

void
reset_room()
{
    if (objectp(mason))
        return;

    mason = clone_object(MINAS_DIR + "npc/mason.c");
    mason->move_living("down", TO);
}

/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */
void
create_room()
{
   config_default_trade();
   set_short("The Stone Mason's Shop");
   set_long(break_string(
         "You are in the humble shop of the Stone Mason, Throman. "+
         "Though he used to busy himself in the repair of the city "+
         "walls, now he chips out his living making stone likenesses "+
         "for those adventurers who can pay him enough.  From the "+
         "amount of dust and stone chips on the floor it looks as "+
           "if he has been hard at work.\n" +
         "There is a huge stone tablet propped in one corner.\n",75));

   add_item("tablet","Carved into the huge stone tablet " +
         "are some instructions:\n" +
        "    Here I sell stone likenesses\n"+
        "    of anyone who can afford it.\n\n"+
        "    Statues cost 2 gold apiece.\n\n"+
        "Throman, Stone Mason of Minas Tirith.\n");
   add_item("stone chips","Some of these little chips "+
            "are sharp! watch your step.\n");
   
   add_exit(MINAS_DIR + "s2crc4.c","south",0);
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    reset_room();
}

int give_red_silv() { return random(4); } /* for more variations */

int
give_max()
{
   return 10000;
}


void
init()
{
   ::init(); /* Since it's a room this must be done. */
   add_action("order", "buy");
   add_action("order", "order");
   add_action("check_time","time");
}

int
order(string str)
{
   object statue;
   string name, adj, long, str1, str2, str3;
   int *arr, price, weight, volume, silent, i;
   
   if (!str) {
      NF("The Stone Mason says: What do you wanna order?\n");
      return 0;
   }
   
/* perhaps they defined how to pay and what change */
   if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
      {
/* perhaps just how to pay */
      str3 = "";
      if (sscanf(str, "%s for %s", str1, str2) != 2)
         {
         str2 = "";
         str1 = str;
       }
   }
   
   switch(str1)
   {
      case "statue":
      name = "statue";
      adj = "stone";
      long = "It's an intricate statue of a "+
          this_player()->query_nonmet_name() +
          " and a little plaque saying '" +
         this_player()->query_name() +
          "'.  It also has a little 'Minas Tirith' stamp on the bottom.\n";
      weight = 3000;
      volume = 600;
      price = 288;
      break;
      default:
      NF("The mason says:  kiddo, you need to pay attention to what i'm sellin.\n");
      return 0;
   }
   
   statue = make_statue(name, adj, long, weight, volume);
   if (!statue)
      {
      NF("Error in creating statue.\n");
      return 0;
   }
   
   silent = 0;
   
   if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3, silent)) == 1)
      {
      if (arr[0] == 1)
         NF("You have to give me more to choose from, that isn't enough.\n");
      else if(arr[0] == 2)
         NF("You don't carry that kind of money!!!!!!!!!\n");
      return 0;  /* pay() handles notify_fail() call */
   }
   
      write("You give the stone mason " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
      if (text(exclude_array(arr, 0, NUM-1)))
         write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
      
      if (!test && (statue->move(this_player())))
         {
         write("You drop the " + name + " on the floor.\n");
         say(QCTNAME(this_player()) + " drops a " + name + " on the floor.\n");
         statue->move(this_object());
       }
      else
         if (!test)
         {
         write("You get your " + name + ".\n");
         say(QCTNAME(this_player()) + " buys a " + name + ".\n");
       }
      else
         say(break_string(QCTNAME(this_player()) + " seems to be estimating something.\n",78));
      
      return 1;
   }
/*
 * Function name: make_statue
 * Description:   Set up the drinks
 * Arguments:     A lot of drink data to be set
 */
object
make_statue(string name, string adj, string long, int weight,
	   int volume)
{
    object statue;
    statue = clone_object("/std/object");
    statue->set_short();
    statue->set_name(name);
    if (strlen(adj)>0)
	statue->set_adj(adj);
    statue->set_long(long);
   statue->add_prop(OBJ_I_WEIGHT, weight);
    statue->add_prop(OBJ_I_VOLUME, volume);

    return statue;
}

/*
 * Function name: test
 * Description:   To allow the buyer to see what would happen with change and
 *                payment depending on how the buyer chooses to pay.
 */
int
test(string str)
{
    int i;
    string str1;
    
    NF("Test what?\n");
    
    if (sscanf(str, "buy %s", str1)) {
	test = 1;
	write("This would be the result of a buy:\n");
	i = order(str1);
	test = 0;
	return i;
    }
}
