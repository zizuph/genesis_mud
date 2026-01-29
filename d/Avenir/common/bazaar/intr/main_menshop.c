// Main Men's Shop (/d/Avenir/common/bazaar/intr/main_menshop.c)
// creator(s):   Lilith, Sept 1997
// last update:  
// purpose:      Provides Pret a porter clothing for men ;)
// note:   
// bug(s):
// to-do:

inherit "/d/Avenir/common/lib/shop";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/include/relation.h"
#define STORE_ROOM   INTR + "main_menstore"

object helper;

/* Prototypes */
string read_me();

void
create_shop()
{
    set_shop_name("The Shop of Emarus the Tailor");
    set_store_room(STORE_ROOM);
    set_short("ready-to-wear men's clothing shop");
    set_long("This tent shop is rather austere. There "+
        "are no decorations or items attractively-displayed "+
        "to catch the eye. It is a busy place, however, with "+
        "a long counter separating the waiting area from the "+
        "goods for sale. Behind the counter can be seen racks "+
        "of mens clothing: shirts, pants, and cloaks of "+
        "various styles and materials.\nA sign carved into "+
        "the countertop and an ornate brass bell.\n");
    set_keeper_file(NPC+"t_helper");
    set_money_greed_buy(105); 
    set_suspected_race(({"hobbit", "kender"}));    // 'cause there aren't any in Avenir
    set_favoured_race(({"elf","gnome"}));
    	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    add_exit(INTR + "mens_shop", "tailor");
    add_exit(EXTR + "str5", "out", 0);  
    add_exit(STORE_ROOM, "down", "@@wiz_check", 1, 1);
   
    add_cmd_item(({"sign", "countertop" }), "read", "@@read_me");
    add_item("sign","@@read_me");
    add_item(({"bell", "small bell"}),
        "An ornate brass bell. It looks like it would ring with "+
        "a lovely, clear tone.\n");    
    add_item(({"tent", "walls", "structure", "canvas"}),
        "The dark-blue canvas walls of the tent are striped "+
        "with wide white bands.\n");
    add_item(({"lamp", "lamps", "brass lamps", "brass lamp"}),
        "The lamps are really just highly-polished brass containers "+
        "with strange, rapidly flickering crystals glowing inside. "+
        "They radiate light, but no heat.\n");
    add_item(({"crystal", "crystals", "source"}), 
        "Perhaps these crystals are part of what the Sybarites refer "+
        "to as the Source? They emit a cool yellow light.\n"); 
    add_item(({"rack", "racks", "silk", "clothing", "goods"}),
        "A fine array of clothing hangs on the racks. Try using <list>"+
        " to see what is avialable.\n");


}
int
wiz_check()
{
    if (!TP->query_wiz_level())
        return 1;
    else
        return 0;
}
       
int
do_buy(string args)
{
    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The tailor refuses to do business "+
            "with criminals.\n");
        return 1;
    }
    if (check_keeper()) return ::do_buy(args);
        return 0;
}

int
do_value(string args)
{
    if (check_keeper()) return ::do_value(args);
        return 0;
}

int
do_list(string args)
{
    if (check_keeper()) return ::do_list(args);
        return 0;
}


/*                                                                       
* Function name: do_sell                                                 
* Description:   Try to let the player sell the_item                     
* Returns:       1 on sucess, 0 fail; should always fail.                                             
* Arguments:     str - string holding name of item, hopefully                                           
*/                                                                       
int                                                                      
do_sell(string str)                                                      
{                                                                        
    
    if (str || !str)                                                 
    {                                                                  
        notify_fail("We only sell things here, we don't buy them.\n");                                       
            return 0;                                                          
    }                                                                     
        
    return 0; /* Player tried to sell a non sellable object. */             
}



int
do_ring(string str)
{
    NF("Ring what?\n");
    if ((str == "bell") || (str == "silver bell"))
      {
        write("You ring the bell.\n");
	say(QCTNAME(TP) + " rings the bell on the counter.\n");
        helper->command("say Celebrate the Source! How may I help you?");
	return 1;
      }
    return 0;
}

string read_me()
{
    write("              Emarus' Ready to Wear Men's Clothing\n"+
          "              ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"+
          "     Emarus the tailor has available a line of quality-crafted\n"+
          "     ready-to-wear mens clothing.\n\n"+
          "     This shop operates like any other. To see what items are\n"+
          "     for sale at this time, please use <list>.\n\n"+
          "     If you would like something custom-made, please see Emarus\n"+
          "     in the exit marked 'tailor'.\n\n"+
          "     Thank you for your patronage.\n\n");
  return "";
}

void
init()
{
    ::init();
    add_action(do_ring, "ring");
}