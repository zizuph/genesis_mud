#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include "../nov.h"
#include <stdproperties.h>

inherit "/std/object";

void 
create_object()
{
        set_name("workbench");
        set_adj("iron");
        add_adj("runecrafter");
        set_short("iron runecrafter workbench");
        
        set_long("This is an iron runecrafter workbench. Its filled with carving tools, " +
        "stonecutters, a magical heater and a bucket of water. Different " +
        "types of runes can be crafted by carving into prepared stones and gems.\n");

        add_prop(OBJ_M_NO_GET,"No, you would not even dare to nudge this runecrafter " +
        "workbench with all the very expensive tools on it.\n");
        
        
        setuid();
        seteuid(getuid());
}



int
make_rune(string str)
{
	if (!str)
	{
		write("Create what?\n");
		return 1;
	}
	
	if (str == "methyl")
	{
		// tresprit text mekking etc "wood spirits"
		
	    /*write("You begin to imbue the "+oblist[0]->query_short()+" with a "+short()+"!\n");
            
           
            tell_room(environment(this_player()), QCTNAME(this_player())+" begins " +
            "to imbue the "+oblist[0]->query_short()+"!\n", this_player());
            
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(43);
            paralyze -> set_fail_message("You are busy imbuing the "+oblist[0]->query_short()+"!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player(), 1);
        
            shadow = clone_object(NOV_DIR +"shadows/imb1_sh");
            shadow->shadow_me(oblist[0]);
 
            set_alarm(3.0,0.0, &tell_room(environment(this_player()), QCTNAME(this_player())+" heats " +
            "the "+oblist[0]->query_short()+" in the forge until it is red-hot.\n", this_player()));     
            set_alarm(3.0,0.0, &write("You heat the "+oblist[0]->query_short()+" in the forge until its red-hot.\n"));
            
            set_alarm(10.0,0.0, &tell_room(environment(this_player()), QCTNAME(this_player())+" starts " +
            "to carve out a small grove on the red-hot "+oblist[0]->query_short()+".\n", this_player()));
            set_alarm(10.0,0.0, &write("You start to carve out a small grove on " +
            "the red-hot "+oblist[0]->query_short()+".\n"));
            
            set_alarm(20.0,0.0, &tell_room(environment(this_player()), QCTNAME(this_player())+" carefully " +
            "hammers the "+short()+" into place in the grove on the red-hot "+oblist[0]->query_short()+".\n", this_player()));
            set_alarm(20.0,0.0, &write("You carefully hammer the "+short()+" into place in the " +
            "grove on the red-hot "+oblist[0]->query_short()+".\n"));
            
            set_alarm(30.0,0.0, &tell_room(environment(this_player()), "The red-hot "+oblist[0]->query_short()+" " +
            "sparks with magical powers emanating from the imbued "+short()+"!\n", this_player()));
            set_alarm(30.0,0.0, &write("The red-hot "+oblist[0]->query_short()+" sparks with magical " +
            "powers emanating from the imbued "+short()+"!\n"));
            
            set_alarm(40.0,0.0, &tell_room(environment(this_player()), QCTNAME(this_player())+" has " +
            "finished imbuing the "+oblist[0]->query_short()+" with a "+short()+"!\n", this_player()));
            set_alarm(40.0,0.0, &write("You finish imbuing the "+oblist[0]->query_short()+" with " +
            "a "+short()+".\n"));
            
            oblist[0]->add_prop(I_AM_IMB, 1);
            oblist[0]->add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment" }));
            oblist[0]->add_prop(MAGIC_AM_ID_INFO,({ "The "+oblist[0]->short()+" seems to be magical.\n",1,
            "It's glyph rune will glow when invisible creatures are nearby.\n",15,
            "It's glyph rune will glow when invisible creatures are nearby.\n",30}));
            
            set_alarm(41.0,0.0, &shadow->init_imb1_shadow());
            set_alarm(42.0,0.0, &remove_object());*/
		
		return 1;
	}
	
	return 1;
}



void
init()
{
        ::init();
        add_action(make_rune, "create");
       
}

