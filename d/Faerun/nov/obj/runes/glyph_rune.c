#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "../../nov.h"

inherit "/std/object";

//object *oblist;

#define OBJ_I_BELLOW_USED "_obj_i_bellow_used"


void
create_object()
{
    set_name("rune");
    set_adj("glyph");
    set_short("glyph rune");
    set_long("This is a magical "+short()+". Blacksmiths can use " +
    "this rune to imbue a nonmagical item by forging it into a weapon or an armour.\n");
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE, 45);
    
    setuid();
    seteuid(getuid()); 
}




int
imbue_item(string str)
{
	

        object *oblist, shadow, forge, paralyze, tools;
        
        //object forge, shadow;
        
        if (this_player()->query_guild_name_lay() != "The Smiths Guild")
        {
        	write("Only a blacksmith may have hope of success to " +
        	"imbue the "+short()+" into anything!\n");
        	return 1;
        }
        
       /* if (!present(environment(this_object())),"_smiths_forging_tools")
        {
            write("You need to be holding the tools before you can forge.\n");
            return 1;
        }*/


       /*  if (!objectp(tools = present("_great_forging_tools",this_player())))
        {
        write("You need to be holding the tools before you can forge.\n");
        return 1;

        }*/

        if (!objectp(forge = present("_great_smith_forge",environment(this_player()))))
        {
        write("The Great Forge of the Blacksmiths seems to be missing.\n");
        return 1;

        }


        if (this_player()->query_fatigue() < (this_player()->query_max_fatigue() / 2))
        {
            write("You feel too tired to imbue anything right now.\n");
            return 1;
        }

     /*   forge = present("_great_smith_forge",environment(environment(this_object())));
        
        if (!forge->query_prop(OBJ_I_BELLOW_USED))
        {
            write("The forge is not warm enough for imbuing items.\n");
            return 1;
        }*/

        this_player()->set_fatigue(this_player()->query_fatigue()-(this_player()->query_max_fatigue()/10));
       // return 1;

        
        if (!strlen(str) || !parse_command(str, all_inventory(this_player()),
        "[on] [the] %i", oblist) || !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
        {
        notify_fail("What do you wish to target?\n");
        return 0;
        }

        if (oblist[0]->query_prop(I_AM_IMB))
        {
        	write("The "+oblist[0]->query_short()+" is already imbued with a rune.\n");
        	return 1;
        }
        


            write("You begin to imbue the "+oblist[0]->query_short()+" with a "+short()+"!\n");
            
           
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
            set_alarm(42.0,0.0, &remove_object());
            
         //   remove_object();
            
        return 1;
}

void
init()
{
        ::init();
        add_action(imbue_item, "imbue");
}



/*

  add_prop(MAGIC_AM_MAGIC,({ 33, "enchantment" }));
  add_prop(MAGIC_AM_ID_INFO,({ "The silvery sword seems to be magical.\n",1,
    "It seems to burn with magical flames, scorching the opponent.\n",25,
    "It will help you to resist magic calling on the power of the air.\n",70}));

    
    */
