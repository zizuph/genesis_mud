/*
*  /d/Faerun/guilds/fire_knives/obj/dark_suit.c
*
*  2019, Nerull
*
*/

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../guild.h";
#define TO  this_object()
#define TP  this_player()

inherit "/std/armour.c";
inherit "/lib/wearable_item";

static  object  Shadow;

public void
create_armour()
{
    setuid();
    seteuid(getuid());  
    
    set_name(({"leather coat","coat", "cloak", "fireknife_guild_object"}));
    add_name(GUILD_ITEM_NAME);
    add_name("dark leather coat");
    add_name("hooded dark leather coat");
    add_name("dark coat");
    add_name("hooded leather coat");
    add_name("hooded dark coat");
    add_name("hooded coat");
    set_adj(({"dark", "hooded", "leather", "coat"}));
    set_short("dark leather coat");
    
    set_long("The coat is made of soft dark leather "
    +"of fine quality with the seams transitioning almost invisibly, "
    +"marking it as quality craftsmanship. It buttons down from the "
    +"right chest to right hip with overlapping layers of leather, but "
    +"the coat itself goes down to about knee height. The inside of the coat "
    +"from hood to about waist length is lined with black velvet, giving it "
    +"a soft and comfortable touch. In the seam inside the coat you can "
    +"see a small tag.\n");
    
    add_item(({"tag"}),
    "The small tag reads <fihelp>.\n");
    
    add_item(({"seam"}),
    "This seam is of exceptional quality and barely noticeable "
    +"from the outside.\n");
    
    add_item(({"buttons"}),
    "These are polished oval oak buttons.\n");
    
    add_item(({"hood"}),
    "The dark leather hood is line with black velvet. You seem to be "
    +"able to  <wear hood> if you wish to remain anonymous, or "
    +"<remove hood> if you want to show your face.\n");
    
    set_ac(1);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
    
    set_looseness(20);
    set_layers(1);
}


public mixed
remove(object ob)
{
    if (this_player()->query_dark_clothed())
        Shadow->remove_darkclothes_shadow();
    
    return 0;
}


public mixed
wear(object ob)
{
    if (this_player()->query_guild_name_occ() != FIREKNIVES_GUILD_NAME 
    && !FIREKNIVES_MASTER->is_fireknife(this_player()->query_name()))
    {
        return "You are not entirely sure how to wear this "
        +"dark leather coat.\n";
        
        return 1;
    }
    
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) <= MAX_PROSPECT_RANK)
    {
        return "You have not yet earned the priviliege to wear the "
        +"dark leather coat. For now, your duty is to care for it.\n";
        
        return 1;
    }
    
    write("You wear the "+query_short()+" around your body.\n");
    
    say(QCTNAME(this_player())+" wears "+LANG_ASHORT(this_object())+".\n");
     
    return 1;
}


public void
leave_env(object from, object to)
{
    if (objectp(from) && from->query_dark_clothed())
    {
		tell_room(environment(this_player()), QCTNAME(this_player())
		+ " pulls back the hood of "+this_player()->query_possessive()
		+" dark leather coat, revealing "+this_player()->query_possessive()
		+" features again.\n", this_player());
		
		this_player()->catch_tell("You pull back the hood of your "
		+"dark leather coat, revealing your features.\n");
		
        Shadow->remove_shadow();
    }
	
    ::leave_env(from, to);
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from);
   
    if (sizeof(filter(all_inventory(to),&->id(GUILD_ITEM_NAME)) - ({this_object() })))
    {
        // One is enough.
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
}


int
wear_hood(string str)
{
	if (str == "hood")
	{
		Shadow = clone_object(FIREKNIVES_GUILD_DIR + "obj/dark_suit_sh");
    
        Shadow->shadow_me(this_player());
		
		tell_room(environment(this_player()), QCTNAME(this_player())
            + " wears the hood of "+this_player()->query_possessive()
			+" dark leather coat, hiding "+this_player()->query_possessive()
			+" features.\n", this_player());
			
		this_player()->catch_tell("You wear the hood of your "
		+"dark leather coat, hiding your features.\n");
    
        this_player()->init_darkclothes_shadow();
				
		return 1;
	}
	
	return 0;
}


int
remove_hood(string str)
{
	if (str == "hood")
	{
	    if (this_player()->query_dark_clothed())
        Shadow->remove_darkclothes_shadow();
	
		tell_room(environment(this_player()), QCTNAME(this_player())
		+ " pulls back the hood of "+this_player()->query_possessive()
		+" dark leather coat, revealing "+this_player()->query_possessive()
		+" features again .\n", this_player());
		
		this_player()->catch_tell("You pull back the hood of your "
		+"dark leather coat, revealing your features.\n");
				
		return 1;
	}
	
	return 0;
}


void
init()
{
    ::init();
    add_action(wear_hood, "wear");
    add_action(remove_hood, "remove");
}