inherit "/d/Genesis/gems/gem_shop";
inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/shop";

#include <macros.h>
#include <stdproperties.h>

object gem_trader;

void
reset_room()
{
    if (!gem_trader)
    {
        setuid();
        seteuid(getuid());
	     
        gem_trader=clone_object("/d/Emerald/telberin/mercantile/gem_shop/gem_trader");
                
        gem_trader->move(this_object(), 1);
        tell_room(this_object(), QCTNAME(gem_trader)+" walks into the shop.\n");
    }    
        
}


void
create_emerald_room()
{
    string sign="                WELCOME TO YLIAR'S GEMSHOP\n " +
        "      Here you may 'sell' and 'buy' gems of all kinds.\n"; 
    
    set_short("You are in a gem shop\n");
    set_em_long("This is the gemshop of Telberin. Along the walls there " +
        "are several glass cabinets filled with gems in all shapes and " +
        "sizes. Especially you notice a glass casing supported by a marble " +
        "base, which seem to contain a very special gem. Under your feet " +
        "lies a beatiful and colourful carpet, almost covering the whole " +
        "floor. Opposite to the entrance wall stands a small counter with " +
        "papers and a scale on top of it. The whole shop is extremely " +
        "clean, both the cabinets and the carpet seem devoid of any dust. " +
        "Behind the counter you see a framed parchment hung up " +
        "on the wall.\n");
    
    
    add_item(({"glass cabinets","cabinets"}),"Along the walls stands glass " +
        "cabinets with a wooden frame. They contain quite a few gems on " +
        "display. There are both small, common gems and some precious " +
        "stones of considerably worth indeed. On each gem you see a little " +
        "paper tag attached, with facts about the stone's size and value.\n");
        
    add_item(({"glass casing","casing"}),"This casing is oval shaped on top " +
        "and open in the bottom. It is placed over a red pillow which rests " +
        "on a carved marble base. On top of the red pillow you see a gem of " +
        "spectacular qualities. It is an unusually large emerald, but what " +
        "is really astounding is its colour. The green light which the gem " +
        "reflect is so pure and strong, it is almost as if this gem is the  " +
        "source from which the concept of green has been arrived.\n");
       
    add_item("carpet", "This is a beatiful, colourful carpet. A number of " +
        "figures are woven into the carpet, resembling some animals but the "+
        "shapes are too abstract to identify the species they describe.\n");    
        
    add_item("counter", "The wooden counter is small, with a few papers and " +
        "a scale placed on it. There is also a wooden plate on the desk, " +
        "with a few gems placed on it.\n");
    add_item("scale", "It is a small scale used to determine the weight of " +
        "gems.\n");         
             
    add_item("parchment","You see a framed parchment with something " +
        "written on it:\n" + sign);
    add_cmd_item("parchment", "read", sign);
    
    create_gem_shop();
    set_store_room("/d/Emerald/telberin/gem_shop/mercantile/gem_store");
   
    reset_room();
}
 
void
init()
{
    ::init();
    init_gem_shop();
}
	
	

int
do_buy(string str)
{
    if (!present(gem_trader)) 
    {
    	notify_fail("The shop keeper is not here!\n");
        return 0;
    }
	
    return ::do_buy(str);
    
}



int
do_sell(string str)
{
    if (!present(gem_trader)) 
    {
    	notify_fail("The shop keeper is not here!\n");
        return 0;
    }
	
    return ::do_sell(str);  
}      	