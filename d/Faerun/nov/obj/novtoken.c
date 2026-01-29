#pragma strict_types
#pragma save_binary

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "../nov.h";

inherit "/lib/keep";
inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";


mapping token_spells = ([ ]);
int energy_stored;

void
create_object()
{
    set_name("orb");
    add_name("_novtoken");
    add_adj("small");
    add_adj("jet-black");
    set_short("small jet-black orb");
    set_long("A small jet-black orb. 'nhelp' for more information.\n");

    add_prop(OBJ_I_WEIGHT,5);
    add_prop(OBJ_I_VOLUME,5);
    add_prop(OBJ_I_VALUE,1000);
    add_prop(OBJ_M_NO_SELL,"Uhm........no.\n");
    add_prop(OBJ_M_NO_DROP,"Uhm........nay.\n");
    add_prop(OBJ_M_NO_STEAL,"You cannot seem to steal anything by that description.\n");
    
    add_spell(NOV_DIR +"spells/planetravel");

    setuid();
    seteuid(getuid());
}


int
query_energy()
{
	return energy_stored;
}



void
setup_my_spells(object owner)
{
    string *my_spells;
    string *allspells;
    int i;
    


     if (this_player()->query_guild_name_lay() != "Necromancers of Vile Darkness")
        {
                write("Since you are not a member of the Necromancers, your " +
                "jet-black orb suddenly disappears!\n");

                token_spells = restore_map(NOV_DIR +"log/token_spells");
                token_spells = m_delete(token_spells, lower_case(this_player()->query_real_name()));
                save_map(token_spells, NOV_DIR +"log/token_spells");  
                remove_object();             

                return;
        }

    
     if (this_player()->query_skill(PUNISHED) == 1)
        {
                write("You are punished by the High Maguses, therefore you " +
                "cannot cast any Necromancer spells.\n");
                return;
        }
        
    allspells = SPELL_LIST[1];
    allspells += SPELL_LIST[2];
    allspells += SPELL_LIST[3];


    for (i = 0; i < sizeof(allspells); i++)
    {
        remove_spell(allspells[i]);
       // add_spell(BANEDEAD_DIR +"spells/planetravel");
    }

    token_spells = restore_map(NOV_DIR +"log/token_spells");
    
    my_spells = token_spells[owner->query_real_name()];
    
    if (owner->query_real_name() == "tilorop") my_spells = allspells;
    //if (owner->query_real_name() == "tiloropjr") my_spells = allspells;
    
    if (owner->query_wiz_level()) my_spells = allspells;
    if (!sizeof(my_spells)) return;
    
    for (i = 0; i < sizeof(my_spells); i++)
    {
        
        
        //**************************************
        
        //if ((my_spells[i] == "deathcoil") && (this_player()->query_skill(ABILITY1) == 1))  
       
        if ((my_spells[i] == "venomspike"))  
        {
          add_spell(NOV_DIR +"spells/venomspike");
        }
        
        if ((my_spells[i] == "regeneration"))  
        {
          add_spell(NOV_DIR +"spells/regeneration");
        } 
                
        if ((my_spells[i] == "deathcoil"))  
        {
          add_spell(NOV_DIR +"spells/deathcoil");
        }
        
        //***************************************
               
         if ((my_spells[i] == "bonedust"))  
        {
          add_spell(NOV_DIR +"spells/bonedust");
        }
        
        if ((my_spells[i] == "wraithform"))  
        {
          add_spell(NOV_DIR +"spells/wraithform");
        }
        
        if ((my_spells[i] == "scrutinize"))  
        {
          add_spell(NOV_DIR +"spells/scrutinize");
        }
        
        /*if ((my_spells[i] == "bonemagus"))  
        {
          add_spell(NOV_DIR +"spells/bonemagus");
        }*/
        
        //***************************************
               
        if ((my_spells[i] == "darkvision"))  
        {
          add_spell(NOV_DIR +"spells/darkvision");
        }
        
        if ((my_spells[i] == "fear"))  
        {
          add_spell(NOV_DIR +"spells/fear");
        }
        
        if ((my_spells[i] == "ghostlink"))  
        {
          add_spell(NOV_DIR +"spells/ghostlink");
        }
        
        if ((my_spells[i] != "planetravel"))  
        {
          add_spell(NOV_DIR +"spells/planetravel");
        }
        
    }

    // for debugging:
    if (owner->query_real_name() == "tilorop")
    {
    }

}


void
enter_env(object env, object from)
{
     ::enter_env(env, from);
    
     set_alarm(1.0, 0.0, &setup_my_spells(env));
     add_spell_object(env);
     
     if (sizeof(filter(all_inventory(env),&->id("_novtoken")) - ({ this_object() }))) 
     {
     // One is enough.
     set_alarm(0.0, 0.0, remove_object);
     return;
     }
   
     

}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
     remove_spell_object(env);
}


string
query_auto_load()
{
    return NOV_DIR +"obj/novtoken"; 
}

