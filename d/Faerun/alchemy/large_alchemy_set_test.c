/* 
* /d/Faerun/alchemy/large_alchemy_set.c
*
*
* A large alchemy set for the general public.
*
* Nerull 2021
*/

inherit "/std/receptacle";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <ss_types.h>
#include "defs.h"


string component1;
string component2;
string component3;
string component4;
string component5;

string herb_component1;
string herb_component2;
string herb_component3;
string herb_component4;
string herb_component5;

int large_flasks = 2;
int volatile_chemicals = 4;
int fuel = 2000;
int beakers = 4;

int burner_on = 0;
int in_use = 0;
int timer_end;

int process_timer = 0;

object product;

string product_string;


int
query_flasks()
{
    return large_flasks;
}


int
query_volatile_chemicals()
{
    return volatile_chemicals;
}


int
query_fuel()
{
    return fuel;
}


int
set_flasks(int i)
{
    large_flasks = i;
    
    return 1;
}


int
set_volatile_chemicals(int i)
{
    volatile_chemicals = i;
    
    return 1;
}


int
set_fuel(int i)
{
    fuel = i;
    
    if (fuel > 2000)
    {
        fuel = 2000;
    }
    
    return 1;
}


int
burn_messages()
{
    if (burner_on == 0)
    {        
        return 1;
    }
    
    if (environment(this_object())->query_prop(ROOM_I_TYPE) == 2)
    {
        if (burner_on == 1)
        {
            write("The burner on the "
            +"large alchemy set is extinguished because of the "
            +"surrounding water.\n");
            
            burner_on = 0;
            in_use = 0;
                
            return 1;
        }
        
    }
    
    tell_room(environment(this_object()), "The burner on the "
    +"large alchemy set gives off a nice warm light.\n");

    fuel = fuel + 60;

    if (fuel >= 2000)
    {
        fuel = 2000;
        
        tell_room(environment(this_object()), "The burner on the "
        +"large alchemy set is extinguished as ran out of fuel.\n");
        
        burner_on = 0;
        
        return 1;
    }

    set_alarm(60.0, 0.0, &burn_messages());    
}


int
set_burneron(string str)
{
    if (str == "burner")
    {
        if (environment(this_object())!=environment(this_player()))
        {
            write("The large alchemy set must he placed on the "
            +"ground first.\n");
            
            return 1;
        }
        
        if (fuel >= 2000)
        {
            write("There is no fuel in the burner. You need "
            +"to refill it.\n");
            
            return 1;
        }
            
        if (burner_on == 1)
        {
            write("The burner is on already.\n");
            
            return 1;
        }
        
        if (environment(this_object())->query_prop(ROOM_I_TYPE) == 2)
        {
            write("The burner will not ignite because you are "
            +"under water.\n");
            
            return 1;
        }
        
        write("You ignite the burner.\n");
         
        burner_on = 1;   

        set_alarm(1.0, 0.0, &burn_messages());     
        
        return 1;
    }
    
    return 0;
}


int
set_burneroff(string str)
{
    if (str == "burner")
    {
         if (burner_on == 0)
        {
            write("The burner is extinguished already.\n");
            
            return 1;
        }
        
        write("You extinguish the burner.\n");
         
        burner_on = 0;     
        
        return 1;
    }
    
    return 0;
}


int
do_refill_alchset(string str)
{
 //   int oil=0;
 
    if (str == "set" || str == "burner")
    {
        if (environment(this_object())!=environment(this_player()))
        {
            write("The large alchemy set must he placed on the "
            +"ground first.\n");
            
            return 1;
        }

        object * 
        oil_flasks = filter(all_inventory(this_player()),
            &->id("_gondorian_flask_with_oil_"));
            
            
        if (!sizeof(oil_flasks))
        {
            write("You don't have any flasks of oil.\n");
            return 1;
        }

        if (fuel <= 0)
        {
            fuel = 0;
            
            write("The burner is filled with oil.\n");
            return 1;
        }
 
        foreach (object flask : oil_flasks)
        {
            if (flask->query_amount() == 0)
            {
                write("The flask is empty, and is discarded.\n");
                
                flask->remove_object();
            }
            
            int to_remove=min(flask->query_amount(),fuel);
            
            if (to_remove>0)
            {
                write("You add more oil to the burner.\n");
                
                flask->remove_oil(to_remove);
                fuel-=to_remove;
            }
        }
            
        return 1;
    }
    
    return 0;
}


int
reset_set()
{
    // We only move the product when the item resets.
    product->set_heap_size(1);
    product->move(this_object(), 1);
    
    LARGE_CRAFTING_LOG("crafting_log",
    "The player "+this_player()->query_name()
    +" crafted a "+product->query_short()+".\n");
    
    in_use = 0;
    
    return 1;
}


int
checkstates()
{ 
    if (in_use == 1)
    {
        write("The large alchemy set is in use. Wait until it's finished.\n");
        
        return 1;
    }
    
    if (burner_on == 1)
    {
        write("The burner on the large alchemy set is "
        +"still running. Extinguish it first.\n");
        
        return 1;
    }
    
    return 0;
}



void
create_receptacle()
{
    set_name("large_alchemy_set");
    add_name("alchemy set");
    add_name("set");
    
    set_adj("large");
    add_adj("alchemy");
    
    set_short("large alchemy set");
    set_pshort("large alchemy sets");
    
    set_long("The large alchemy set consists of a foldable large metal "
    +"base holding various tubes and beakers which "
    +"contain various hazardious chemicals, metals and colours "
    +"for various uses such "
    +"as strengthening, conditioning, separating and creating different "
    +"reagents, poisons, other components and field tools. It is also "
    +"complete with a burner, a "
    +"mortar and a grinder.\nIf you know the recipe and have "
    +"the necessary components, you may 'craft <product>'. You may also "
    +"do a <status alchemyset> to check its remaining inventory.\n");
    
    add_item("burner", "You can light or extinguish the burner.\n");

    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_MAX_WEIGHT,250000);
    add_prop(CONT_I_WEIGHT,15000);
    add_prop(CONT_I_MAX_VOLUME,250000);
    add_prop(CONT_I_VOLUME,10000);
    
    add_prop(OBJ_M_NO_GET,checkstates);
    
    add_prop(CONT_I_CLOSED, 0);
}


// Physical components
int
set_component1(string str)
{
    component1 = str;

    return 1;
}


string
query_component1()
{
    return component1;
}


int
set_component2(string str)
{
    component2 = str;

    return 1;
}


string
query_component2()
{
    return component2;
}


int
set_component3(string str)
{
    component3 = str;

    return 1;
}


string
query_component3()
{
    return component3;
}


int
set_component4(string str)
{
    component4 = str;

    return 1;
}


string
query_component4()
{
    return component4;
}


int
set_component5(string str)
{
    component5 = str;

    return 1;
}


string
query_component5()
{
    return component5;
}


// Herbal components
int
set_herb_component1(string str)
{
    herb_component1 = str;

    return 1;
}


string
query_herb_component1()
{
    return herb_component1;
}


int
set_herb_component2(string str)
{
    herb_component2 = str;

    return 1;
}


string
query_herb_component2()
{
    return herb_component2;
}


int
set_herb_component3(string str)
{
    herb_component3 = str;

    return 1;
}


string
query_herb_component3()
{
    return herb_component3;
}


int
set_herb_component4(string str)
{
    herb_component4 = str;

    return 1;
}


string
query_herb_component4()
{
    return herb_component4;
}


int
set_herb_component5(string str)
{
    herb_component5 = str;

    return 1;
}


string
query_herb_component5()
{
    return herb_component5;
}


int
do_alchemysetstatus(string str)
{
    write("After inspecting the large alchemy set thoroughly, you notice "
    +"that there are: "+large_flasks+" large flasks, "
    +volatile_chemicals+" containers of volatile chemicals and "
    +beakers+" left.\n");
    
    if (fuel >= 2000)
    {
        write("The burner contains no fuel.\n");
    }
    else
    {
        write("The burner contains fuel.\n");
    }
     
    return 1;
}


void
do_processing()
{
    setuid();
    seteuid(getuid());

    if (process_timer == 0)
    {
        write("You start to craft something using the large alchemy set.\n");
    
        tell_room(environment(this_object()), QCTNAME(this_player())
        +" starts to craft something using the large alchemy set.\n", this_player());        
    }
    
    if (process_timer >= 1)
    {
        tell_room(environment(this_object()), "The large alchemy "
        +"set gives off boiling sounds.\n");        
    }
    
    if (process_timer == timer_end)
    {   
        product = clone_object(ALCHEMY_PRODUCT_DIR 
        + product_string);
        product->set_heap_size(1);
        product->move(this_object(), 1);
        
        tell_room(environment(this_object()), "The large alchemy "
        +"set produces "+product->short()+".\n");        
        
        LARGE_CRAFTING_LOG("crafting_log",
        "The player "+this_player()->query_name()
        +" crafted a "+product->query_short()+".\n");
        
        in_use = 0;
        process_timer = 0;
        
        return;
    }
     
    process_timer = process_timer + 1;
    
    set_alarm(5.0, 0.0, &do_processing());
    
    return;
}


int
do_craftcomponents(string str)
 {
    object *obj1_component;
    object *obj2_component;
    object *obj3_component;
    object *obj4_component;
    object *obj5_component;
       
    object *obj1_herbal_component;
    object *obj2_herbal_component;
    object *obj3_herbal_component;
    object *obj4_herbal_component;
    object *obj5_herbal_component;

    if (!str)
    {
        write("Create what?\n");
        
        return 1;
    }
    
    if (environment(this_object())!=environment(this_player()))
    {
        write("The large alchemy set must he placed on the "
        +"ground first.\n");
        
        return 1;
    }
    
    if (in_use == 1)
    {
        write("The large alchemy set is in use for the moment.\n");
        
        return 1;
    }
    
    if (burner_on == 0)
    {
        write("You need to turn on the burner first.\n");
        
        return 1;
    }
    
    if (fuel >= 2000)
    {
        write("The burner on the large alchemy set is out "
        +"of fuel. Bring some oil to refill it.\n");
        
        return 1;
    }
    
    if (beakers <= 0)
    {
        write("There are no more beakers left on the "
        +"large alchemy set.\n");
        
        return 1;
    }
 
    // Recipes.
    switch(str)
    {
        // ------------ END PRODUCTS ----------
        /*case "oblivion":       
        set_herb_component1("nightshade");        
        product_string = "oblivion";       
        break;*/
        
        case "hellfire":
        set_component1("_rust_powder");
        set_herb_component1("nethra");                        
        product_string = "hellfire";       
        break;

        // ------------ INTERMEDIATE ----------

        case "rust powder":
        set_component1("_pile_of_rusty_nails");    
        product_string = "rust_powder";       
        break;
        
        default:
        write("Create what?\n");
        return 1;
    }
    
    // Craft oblivion product
    /*if (str == "oblivion")
    {
        // Herb component 1
        obj1_herbal_component = filter(deep_inventory(this_player()),
        &operator(==)(query_herb_component1()) @&->query_herb_name());

        if (!sizeof(obj1_herbal_component))
        {
            write("You are missing a herbal component!\n");
            return 1;
        }
        
        write("You use "+obj1_herbal_component[0]->query_short()+" as ingredient.\n");

        obj1_herbal_component[0]->reduce_heap_size();
        
        timer_end = 12;
    }*/
    
    // Craft hellfire product
    if (str == "hellfire")
    {
        // Physical component
        obj1_component = filter(deep_inventory(this_object()),
        &operator(==)(query_component1()) @&->query_name());

        if (!sizeof(obj1_component))
        {
            write("A component is missing in the large alchemy set!\n");
            return 1;
        }
        
        // Herb component 1
        obj1_herbal_component = filter(deep_inventory(this_object()),
        &operator(==)(query_herb_component1()) @&->query_herb_name());

        if (!sizeof(obj1_herbal_component))
        {
            write("A herbal component is missing in the large alchemy set!\n");
            return 1;
        }
        
        if (large_flasks == 0)
        {
            write("There are no large flasks left to use on the large alchemy set.\n");
            return 1;
        }

        //write("You use "+obj1_component[0]->query_short()+" as ingredient.\n");
        //write("You use "+obj1_herbal_component[0]->query_short()+" as ingredient.\n");
                       
        obj1_component[0]->reduce_heap_size();
        obj1_herbal_component[0]->reduce_heap_size();
        
        large_flasks = large_flasks - 1;
        beakers = beakers - 1;
               
        timer_end = 15;
    }
    
    
    /////////////////////////////////////////////////////////////////
    
    if (str == "rust powder")
    {
        // Physical component
        obj1_component = filter(deep_inventory(this_object()),
        &operator(==)(query_component1()) @&->query_name());

        if (!sizeof(obj1_component))
        {
            write("A component is missing in the large alchemy set!\n");
            return 1;
        }
        
        if (volatile_chemicals == 0)
        {
            write("There are no more volatile chemicals left on the large alchemy set.\n");
            return 1;
        }
        
        //write("You use "+obj1_component[0]->query_short()+" as ingredient.\n");
                   
        obj1_component[0]->remove_object();
        
        volatile_chemicals = volatile_chemicals - 1;
        beakers = beakers - 1;
              
        timer_end = 10;
    }
    
    setuid();
    seteuid(getuid());
    
    int alchemy_skill;
    alchemy_skill = this_player()->query_skill(SS_ALCHEMY);
    
    int result = random(42);
    
    
    // Failure.
    if (result > alchemy_skill)
    {
        int failure = random(100);
        
        switch(failure)
        {
            case 0..50:
            write("You try to create something with the use of "
            +"the large alchemy set, but you fail.\n");
    
            tell_room(environment(this_player()), QCTNAME(this_player())
            +" uses a large alchemy set to create something, "
            +"but fails.\nYou ruin a beaker.\n", this_player());
            
            beakers = beakers - 1;
            if (beakers < 0)
            {
                beakers = 0;
            }
            break;
            
            case 51..90:
            write("You try to create something with the use of "
            +"the large alchemy set, but you fail.\n");
    
            tell_room(environment(this_player()), QCTNAME(this_player())
            +" uses a large alchemy set to create something, "
            +"but fails badly.\nYou ruin a couple of beakers.\n", this_player());
            
            beakers = beakers - 2;
            if (beakers < 0)
            {
                beakers = 0;
            }
            break;
            
            case 91..95:
            write("You try to create something with the use of "
            +"the large alchemy set, but you fail horribly.\n");
    
            tell_room(environment(this_player()), QCTNAME(this_player())
            +" uses a large alchemy set to create something, but "
            +"fails horribly.\n", this_player());
            
            beakers = beakers - 5;
            if (beakers < 0)
            {
                beakers = 0;
            }
            break;
            
            case 96..99:
            write("You try to create something with the use of "
            +"the large alchemy set, but you fail horribly. The large "
            +"alchemy set catches fire and rapidly grows unstable, before "
            +"blowing up in your face in a BIG BANG!\nYou are "
            +"severly injured!\n");
    
            tell_room(environment(this_player()), QCTNAME(this_player())
            +" uses a large alchemy set to create something, but it suddenly "
            +"catches fire and blows up with a BIG BANG!\n", this_player());
            
            this_player()->set_hp(10);
            this_player()->command("scream");
            this_player()->run_away();
            
            LARGE_CRAFTING_LOG("crafting_log",
            "The player "+this_player()->query_name()
            +" failed crafting a product. Set blew up.\n");
            
            remove_object();
            break;
        }
        
        LARGE_CRAFTING_LOG("crafting_log",
        "The player "+this_player()->query_name()
        +" failed crafting a product.\n");
        
        return 1;
    }

    in_use = 1;
    
    set_alarm(1.0, 0.0, &do_processing());

    return 1;
}


void
init()
{
    ::init();
	
    add_action(do_craftcomponents, "craft");
    add_action(do_alchemysetstatus, "status");
    add_action(do_refill_alchset, "refill");
    add_action(set_burneron, "light");
    add_action(set_burneroff, "extinguish");
}