
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include "../nov.h";

inherit "std/monster";


object PLAYER;
string p_name;

void
destruct_skull()
{
   tell_room(environment(), "The floating green eerie skull dissolves into black smoke!\n");
        remove_object();
}
   

void
update_nlight()
{
	int x, y;
	
       x = environment(this_object())->light();
       y = environment(this_object())->light() * 2;
       
       y = x - y;              
       
       if (x < 1)
       {
       	
         this_object()->add_prop(OBJ_I_LIGHT, y);
         return;
        }
        
        return;
}

       

void
create_monster() 
{
 

    set_name("Boney");
    set_race_name("skull");
    set_adj("floating");
    add_adj("green");
    add_adj("eerie");
    set_short("floating green eerie skull");
    set_long("This is a skull made of dark energies. It luminates the area with a " +
    "sick green eerie radiation that seems to pierce through all darkness, as if its " +
    "sucking it up.");
    
    set_alignment(-1000);
    set_stats(({20,20,20,20,20,20}));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VOLUME, 3500);

    set_mm_in("floats in.");
    set_mm_out("floats out.");
    
    set_hitloc_unarmed(0,20,20,"skull");
    set_attack_unarmed(0, 20, 20, W_IMPALE, 100, "forehead");

         setuid();
    seteuid(getuid());
    
    set_alarm(20.0,0.0, &destruct_skull());
    set_alarm(3.0,3.0, &update_nlight());
    
}


int
do_discard(string str)
{
        
        if (str != "sphere")
        {
                return 0;
        }
        
        
        if (this_player()->query_guild_name_lay() == GUILDNAME)
        {
                write("You dispel the sphere.\n");
                this_object()->destruct_skeleton();
                return 1;
        }
        //write("What ?\n");
        return 0;
}


/*void
init()
{
    ::init();
    add_action(do_discard, "dismiss");
    
}*/


void
goto_player()
{
    if(environment(PLAYER) != environment(this_object())) move_living("X", environment(PLAYER));
}


void
init_pet(object pl)
{
    PLAYER = pl;
    p_name = PLAYER -> query_real_name();
    
    set_alarm(0.0, 1.0, goto_player);
    
}


