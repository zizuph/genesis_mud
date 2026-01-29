/*
 *
*/

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
inherit "/std/armour";
inherit "/lib/keep";


int charges = 3;
 
string
check_events()
{
    if (charges == 3)
    {
        return "a picture of a black-haired girl wearing a white dress standing in"
        +" a distance of a beautiful garden, facing you. Her long black"
        +" hair obscures her face entirely";
    }
    
    if (charges == 2)
    {
        return "a picture of a black-haired girl wearing a white dress standing in"
        +" a distance of a beautiful garden, facing you. Her long black"
        +" hair partially obscure a small skeletal face";
    }
    
    if (charges == 1)
    {
        return "a picture of a black-haired girl wearing a white dress standing in"
        +" a distance of a beautiful garden, facing you. Her long black"
        +" hair obscures nothing of her small and dreadful skeletal face";
    }

    return "a ghasty skeletal face of a black-haired girl staring right " +
    "at you in a looming threatening manner, as if anticipating your " +
    "imminent Death";
}

void
create_armour()
{
	set_name("medallion");
	add_name("spectre_med");
	set_adj("white");
	add_adj("ghostly");
	set_short("small ghostly medallion");
	set_long("This is a small ghostly medallion shaped like a" 
	+" triangle pointing upwards. It is transparent and partly ethereal. In"
	+" its center you see "+check_events()+". A long silvery cord is"
	+" attached to it, making it wearable around the neck.\n");

	set_ac(5);
	set_at(A_NECK);
	set_af(this_object());
	set_wf(this_object());
	add_prop(OBJ_I_NO_STEAL, 1);
	add_prop(OBJ_I_VALUE, 1093); 
  add_prop(OBJ_I_VOLUME, 500); 
  add_prop(OBJ_I_WEIGHT, 50); 

        
         setuid();
    seteuid(getuid());
}


public mixed
wear(object ob)
{

	return 1;
}

public mixed
remove(object ob)
{
	
	return 1;
	
}


void
do_depart_message()
{
    write("The dreadful spirit leaves " +
    "your body and fades away.\n");
    	  
    write("Your "+short()+" crumbles to dust!\n");
    say(QCTNAME(this_player())+"'s small ghostly medallion crumbles to dust!\n");
    remove_object();
}


int
do_use_med(string str)
{

    if (str != "medallion")
    {
        return 0;     
    }

    

// Insert nifty effects here

    if (charges == 0)
    {
    	
    	  write("A dreadful spirit of a skeletal black-haired girl bursts out of " +
    	  "the "+short()+" and enters your body!\nYou feel veins and arteries tear " +
    	  "apart from within!\n\nYou are dying!!\n\n");
    	  
    	  this_player()->set_hp(10);
    	  
    	  set_alarm(6.0, 0.0, &do_depart_message());
 
    	  return 1;
    	  
    }

    write("You feel magical energies flow from the "+short()+
    ", regenerating some of your wounds.\n");
    
    if (charges == 3)
    {
        write("You feel a lethal menace closing in.\n");
    } 
    
    if (charges == 2)
    {
        write("You feel a dreadful presence in close vicinity, " +
        "threatening your life!\n");
    } 
    
    if (charges == 1)
    {
        write("You feel as if Death itself is behind you, readying " +
        "its dreadful scythe!\n");
    } 

    say(QCTNAME(this_player())+"'s small ghostly medallion appears to regenerate " +
    "some of "+this_player()->query_possessive()+" wounds.\n");

    this_player()->heal_hp(500);
    charges = charges -1;
    
    set_long("This is a small ghostly medallion shaped like a" 
	  +" triangle pointing upwards. It is transparent and partly ethereal. In"
	  +" its center you see "+check_events()+". A long silvery cord is"
	  +" attached to it, making it wearable around the neck.\n");
    
    
    return 1;
}

void
init()
{
    ::init();


    add_action(do_use_med, "use");
    
   
}















