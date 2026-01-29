// Laurent's Silken Pillow (/d/Avenir/common/bazaar/intr/silkshop.c)
// creator(s):   Grace Nov 15 1995
// last update:  
// purpose:      Provides women's clothing, esp for Dancers
// note:   
// bug(s):
// to-do:

inherit "/d/Avenir/common/lib/shop";

#include "/d/Avenir/common/bazaar/bazaar.h"
#define STORE_ROOM   INTR + "silkstore"

object silkseller;

/* Prototypes */
string read_me();

void
create_shop()
{
    set_shop_name("Laurent's Silken Pillow");
    set_store_room(STORE_ROOM);
    set_short("silk seller");
    set_long("The air in this tent shop is fragrant with patchouli "+
        "and jasmine, a welcome change from the mixture of scents "+
        "outside in the Sybarus Bazaar.  "+
        "A bronze sculpture dominates one corner of the structure, "+
        "a shimmering collection of jewelry at its base.  "+
        "Brass lamps dangle from above, reflecting a cool yellow"+
        "ish light upon bolts of silk and heaps of expensive women's "+
        "clothing.  "+  
        "There is a discreet sign hanging on the wall."+
        "\n");
    set_keeper_file(NPC+"silkseller");
    set_money_greed_buy(105); 
    set_suspected_race(({"hobbit"}));    // 'cause there aren't any in Avenir
    set_favoured_race(({"elf","gnome"}));
    IN
    add_exit(EXTR + "str7", "out", 0);  
   
    add_cmd_item("air", "smell", "It smells of patchouli and jasmine.\n");
    add_cmd_item("sign", "read", "@@read_me");
    add_item("sign","@@read_me");
    add_item(({"bell", "small bell"}),
        "An ornate brass bell. It looks like it would ring with"+
        "a lovely, clear tone");    
  /* Sialul and Sabrus of the Tenth Hour: Prosperity and Sustenance */
    add_item(({"sculpture", "bronze sculpture", "figure", "figures"}),
        "It is of two figures kissing. One of the figures is male, "+
        "his arms covered with bangles and his chest with chains. "+
        "The other figure is female. She holds a goblet in one hand "+
        "and a knife in the other.\n");
    add_item(({"jewelry", "base"}),
        "There are chains and armbands piled at the base of the sculp"+
        "ture.\n");
    add_item(({"tent", "walls", "structure", "canvas"}),
        "The white canvas walls of the tent are striped with green and "+
        "pink.\n");
    add_item(({"lamp", "lamps", "brass lamps", "brass lamp"}),
        "The lamps are really just highly-polished brass containers "+
        "with strange, rapidly flickering crystals glowing inside. "+
        "They radiate light, but no heat.\n");
    add_item(({"crystal", "crystals", "source"}), 
        "Perhaps these crystals are part of what the Sybarites refer "+
        "to as the Source? They emit a cool yellow light.\n"); 
    add_item(({"bolt", "bolts", "silk", "clothing", "heap", "heaps"}),
        "The bolts of silk are neatly arranged, but the clothing lies "+
        "in carelessly decadent heaps of rainbow colour that catch "+
        "the eye.\n");


}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:

void
init()
{
    ADD("do_ring", "ring");
}

*/

int
do_buy(string args)
{
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
	  
	  if (!silkseller)
	    {
         	silkseller = clone_object(NPC + "silkseller");
	        silkseller->move(TO);
		tell_room(TO, "The shopkeeper moves swiftly toward you " +
			  "with an polite smile on his face.\n");
		return 1;
	    }
	  silkseller->command("say Celebrate the Source! How may I help you?");
	  return 1;
      }
    return 0;
}

string read_me()
{
    write("              Laurent's Silken Pillow\n"+
        "              ^^^^^^^^^^^^^^^^^^^^^^^^\n"+
        "     Laurent proudly supplies Sybarus with its most sensual,\n"+
        "  provocative, and stylish women's clothing and accessories.\n"+
        "\n"+
        "     This shop operates like any other. To see what items are\n"+
        "  for sale at this time, please use <list>.\n"+
        "     Thank you for your patronage of Laurent's Silken Pillow.\n");
  return "";
}


