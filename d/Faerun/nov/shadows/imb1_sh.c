#include <stdproperties.h>
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>

#include "../nov.h";


inherit "/std/shadow";

string
short()
{
    return "glyph-runed "+shadow_who->short();
}

string
long()
{
	return shadow_who->long()+"Its enchanted by a glyph rune.\n";
}



//void
//enter_env(object ob, object ob2)

void
check_invis()
{
         //::enter_env;

         int i;
         object *arr;
        
         arr = filter(all_inventory(environment(environment(shadow_who))),
        &->query_prop(OBJ_I_INVIS));
        
    for (i = 0; i < sizeof(arr); i++)
    {
        
        if (environment(shadow_who)->query_prop(OBJ_I_INVIS))
        {    
              if(living(environment(shadow_who)))
              {
               tell_object(environment(shadow_who),"The glyph rune on your "+short()+" glows a brief moment with a green eerie light.\n");
               return;
              }
         }
        
              if(living(environment(shadow_who)))
              {
               tell_room(environment(environment(shadow_who)),"The glyph rune " +
               "on "+QCTNAME(environment(shadow_who))+"'s "+short()+" glows a brief moment with a green " +
               "eerie light.\n",environment(shadow_who));
               tell_object(environment(shadow_who),"The glyph rune on your "+short()+" glows for a brief moment with a green eerie light.\n");
               return;
              }
 
              return;

        }

       return;
}



int
query_imb1_shadow()
{
    return 1;
}

void
init_imb1_shadow()
{   
    shadow_who->add_prop(I_AM_IMB, 1);
    shadow_who->add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment" }));
    shadow_who->add_prop(MAGIC_AM_ID_INFO,({ "The "+short()+" seems to be magical.\n",1,
    "It's glyph rune will glow when invisible creatures are nearby.\n",15,
    "It's glyph rune will glow when invisible creatures are nearby.\n",30}));

    set_alarm(2.0,5.0, &check_invis());
 
}