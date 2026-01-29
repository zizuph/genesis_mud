// creator(s):  Lilith Aug 2021
// last update:  
// purpose:     Crate for the BOGL camp
//              customized for use with SMIS placer.
// bug(s):
// to-do:

inherit "/std/receptacle";
inherit "/lib/unique";
#include "../dead.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include <cmdparse.h>
#include <language.h>
#include <money.h>


string *adjs = (({"ornately carved", "decorated", "gold-embossed", "painted", 
     "massive", "jewel-encrusted"}));
string *types = (({"granite", "limestone", "basalt", "marble", "red carnelian",
     "red quartzite", "alabaster" }));
string adj, type, my_id;


/* Function name: reset_placed_functions
 * Description:   This function is called from the placer module to 
 *                reset the object. Can be used to fill the object with 
 *                contents. 
 *
 *    For when it is called see:
 *    /d/Avenir/smis/std/placer_mod.c
 *
 *    If it returns 1, the placer will do nothing, but if it returns 0,
 *    the placer will clone a new object.
 *
 */
public int
reset_placed_functions()
{
	seteuid(getuid());
    if (sizeof(all_inventory(this_object())) < 3)
    {
        MONEY_MAKE_PC(2)->move(TO,1);
	    clone_object(OBJ +"rotted_cloth")->move(TO, 1);
	    clone_object(DARK +"obj/bones")->move(TO, 1);	
	    /* magical death mask or regular death mask */
        //  no kesoit mask for now, waiting for balance review.
        //	clone_unique(OBJ +"kesoit_mask", 5, OBJ +"death_mask", 0, 40, 0)->move(TO,1);
        clone_object(OBJ +"death_mask")->move(TO, 1);
    }
    return 1;
}

int 
config_coffin()
{
    adj = adjs[random(sizeof(adjs))];
    set_adj(adj);
    type = types[random(sizeof(types))];
    add_adj(type);

    set_short(adj+" "+type+" sarcophagus");   
    set_pshort(adj+" "+type+" sarcophagi");
    add_name("_Avenir_sarcophagus");

   return 1;
}


void
create_receptacle()
{
    ::create_receptacle();

    seteuid(getuid(TO));

    reset_placed_functions();
}

