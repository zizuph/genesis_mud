/* Link to n1.c e1.c s1.c w1.c
 * Access to L5 of the ogre lair
 * Shop (npc) and Bank for the Deep parts of the Underdark.
 * Banker charges 33% fee, because he can.
 * --Lilith, May 2022: added bank func
 */

inherit"/std/room";
inherit "/d/Avenir/inherit/sair_wall";
inherit "/lib/bank";
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/merchant.h"
#include <money.h>
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <files.h>

void
reset_room()
{
  object merchant, tr = this_object();
  
  if (!STORE->merchant_alive())
    {
      merchant = clone_object (MERCHANT);
      merchant->set_m_in ("arrives drawing a cute pony loaded with packs.");
      merchant->set_m_out ( "draws the reins of his pony and leaves");
      merchant->move(tr);
    }
}

/* Amblo charges 33% fee because he can. */
void
fee()
{
	set_bank_fee(33);
	config_trade_data();
	return;
}

void
create_room()
{
  set_short("tunnel crossing");
  set_long(
   "You stand in a roughly-hewn circular chamber.\n" +
   "Tunnels from the cardinal directions meet and cross " +
   "here.  Peering into each, you can see only darkness.  " +
   "Small stalactites hang down from the rocky ceiling, " +
   "and the floor beneath your feet is heavy with a gravelly "+ 
   "mixture of stones, dirt, and water.\n");

  AI(({"stalactite", "stalactites"}),
   "The stalactites are phallic shapes hanging from " +
   "the ceiling above and formed of minerals deposited " +
   "by dripping water.\n");
  
  AI(({"puddle", "water"}),
   "You didn't see it before you walked into the room " +
   "because it covers the entire floor. Very shallow and inky-" +
   "black, it makes the gravel underfoot slippery, so step " +
   "carefully.\n");
  
  AI(({"gravel", "mixture", "stones", "stone", "dirt", "floor", "ground"}),
   "The floor of this large chamber is covered in a mixture " +
   "of small stones and sandy dirt.  It is rather damp, and a " +
   "slightly moldy smell emanates from it.\n");   

  AI(({"wall", "walls"}), "The walls are roughly-hewn from the "+
   "living stone and glisten with moisture.\n");
   
  set_sair_dest(({L2+"add/t36", L1+"center", L2+"center"}));  
  add_sair_wall();   

  add_exit(L4 + "s1","south",0);
  add_exit(L4 + "w1","west",0);
  add_exit(L4 + "e1","east",0);
  add_exit(L4 + "n1","north",0);
  
  BLACK;
  IN;
  
    config_default_trade();
    config_trade_data();

    object gndep = clone_object("/d/Genesis/obj/deposit");
    gndep->set_short("deposit");
    gndep->set_bank_id(3904, "Bank of Amblo");
    gndep->set_no_show_composite(1);
    gndep->move(this_object());
	
    reset_room();
}


int
change(string str)
{
    fee();
    return ::change(str);
}

int
test(string str)
{
    fee();
    return ::test(str);
}

int
minimize(string str)
{
    fee();
    return ::minimize(str);
}

string
standard_bank_sign()
{
    fee();
    return ::standard_bank_sign();
}


public void
init()
{
    ::init();
    sair_init();  
	bank_init();
}

