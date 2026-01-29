/*
 * A family heirloom sword for the Dunlending quest
 * in Edoras.
 * 
 * Raymundo, April 2020
 */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h"


string quest_status; //a control for whether or not a non-quester has picked up the sword.

string
my_short()
{
    if(quest_status == "yes")
    {
        remove_adj("ancient");
        remove_name("_dunlending_quest_sword");
        return("gold-inlaid longsword");
    }
    else
    return("ancient gold-inlaid longsword");
}
    

void
create_weapon()
{
  set_name(({"longsword","sword", "weapon"}));
   add_name("_dunlending_object");
   add_name("_dunlending_quest_sword");
  set_pname("longswords");
  set_short("@@my_short@@");
    set_adj(({"ancient", "gold", "inlaid", "inlay", "gold-inlaid"}));
  set_long("This longsword is about one meter long. There are notches in the "
    + "blade, indicating that this sword was used in battle and then not "
    + "not maintained well afterwards. Gold inlays run the length of the "
    + "blade.\n");
  add_item( ({"notch", "notches"}), "The notches are quite severe, some "
    + "big enough that you can fit your finger into them. Whatever "
    + "battle this sword was in was hard fought.\n");
  add_item( ({"inlay", "inlays", "gold", "gold inlays", "gold inlay"}),
    "The inlays depict a valiant horseman chasing down orcs on an "
    + "open plain.\n");

  set_default_weapon(28,27,W_SWORD,W_SLASH,W_BOTH,0);
  add_prop(OBJ_I_WEIGHT,10000);
  add_prop(OBJ_I_VOLUME,900);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,27)+random(200)-100);
  add_prop(OBJ_M_NO_BUY, 1);
}

//If a non-quester picks up the sword, it becomes worthless for the quest.
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if(!living(dest))
    {
        return;
    }
    if(dest->query_prop(QUESTING))
    {
        return;
    }
    if(quest_status == "yes")
    {
        return;
    }
    else
    {
        write("As you get a closer look at the sword, you realize "
            + "that it doesn't seem nearly as ancient as it once did.\n");
        set_short("gold-inlaid longsword");
        remove_adj("ancient");
        remove_name("_dunlending_quest_sword");
        quest_status = ("yes");
        return;
    }
}

        
void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    
    if (sizeof(a) >= 1)
    {
        quest_status = a[1];
       
        
    }

    init_wep_recover(arg);
    
}

string
query_recover()
{
    return ::query_recover() + "&&" + quest_status;
}






