
// file name: /d/Avenir/common/dead/dead/obj/sarcophagus
// creator(s): Lilith July 2021
//             Based on Ilyian's coffins from 
//             /d/Avenir/common/ships/dead/obj/coffin
// purpose:   Special resting place for high lords
// note:
// bug(s):
// to-do:
// updates:   Lilith, Nov 2021: fixed bug that was showing up in the lplog


inherit "/std/receptacle";
inherit "/lib/unique";
#include "../dead.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include <cmdparse.h>
#include <language.h>
#include <money.h>

int keepshut;
string *adjs = (({"ornately carved", "decorated", "gold-embossed", "painted", 
    "massive", "jewel-encrusted"}));
string *types = (({"granite", "limestone", "basalt", "marble", "red carnelian",
    "red quartzite", "alabaster" }));
string adj, type, my_id;

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
    /* magical death mask or regular death mask */     
    if (!present("mask", TO))
	clone_unique(OBJ +"kesoit_mask", 5, OBJ +"death_mask", 0, 20)->move(TO,1);
    if(!present("coin", TO))	
	MONEY_MAKE_PC(2)->move(TO,1);
    if(!present("bones", TO))
	clone_object(DARK +"obj/bones")->move(TO, 1);	
    if(!present("cloth", TO))
	clone_object(OBJ +"rotted_cloth")->move(TO, 1);

    add_prop(CONT_I_CLOSED, 1);
    return 1;

}

void
create_container()
{
    seteuid(getuid());

    config_coffin();

    set_name(({"sarcophagus"}));
    set_pname("sarcophagi");

    add_item(({"lid","cover"}),"Made of a thick slab of "+ type 
      +", the cover is engraved with the stylized rendering "
      +"of a shadow-elf, presumaby bearing a resemblance "
      +"to the person laid to rest within it.\n");
    add_item(({"view","outside","out"}),"@@coffin_view");

    set_long("@@coffin_long");
    set_pick(90);
    add_prop(CONT_I_IN,1);
    add_prop(ROOM_I_IS,1);
    add_prop(CONT_I_WEIGHT, 900000);
    add_prop(CONT_I_VOLUME, 900000);
    add_prop(OBJ_I_VALUE, 10860);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_TRANSP,0);
    add_prop(CONT_I_MAX_VOLUME, 300000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(ROOM_I_LIGHT, -1);

    add_prop(CONT_I_CLOSED, 1);

    set_cf(TO);

    reset_placed_functions();

}

// carried over from Ilyian's coffin code.
void
init()
{
	::init();
		
    add_action("do_leave","climb",0);
    add_action("do_leave","leave",0);
    add_action("do_leave","out");
    add_action("do_leave","exit");
    add_action("do_enter","enter",0);
    //add_action("do_nolight","light",0);
    //add_action("do_inshout","shout",0);

    add_action("do_inopen","open",0);
    add_action("do_inclose","close",0);
    
}

int
do_inlock(string str)
{ 
    return 0;
}

int
do_unlock()
{
    return 0;
}


int
do_inshout(string str)
{
    if (str == "" || !str)
	return 0;

    if(TO != ENV(TP))
    {
	tell_room(TO, "From outside the coffin you hear someone "
	  +"shout: "+str+"\n");
	return 0;
    }

    if(TO->query_prop(CONT_I_CLOSED))
    {
	write("Your shouts are muffled by the lid of the "
	  +short()+".\n");
	tell_room(ENV(TO),"Muffled shouts can be heard from "
	  +"within the "+short()+"\n");
	return 1;
    }

    tell_room(ENV(TO), "From within the "+short()+" you "
      +"hear a voice shout: "+str+"\n");
    return 0;
}

int
do_inopen(string str)
{

    if (str == "" || !str)
	return 0;

    if (TO != ENV(TP))
	return 0;

    if(str=="coffin" || str=="lid" || str =="sarcophagus")
    {
	if(keepshut)
	{
	    write("Something is holding the lid closed.\n");
	    return 1;
	}
	if(!TO->query_prop(CONT_I_CLOSED))
	{
	    write("The "+query_short()+" is already open.\n");
	    return 1;
	}

	write("With a great heave, you push the lid of the "+
      query_short()+" open.\n");
	tell_room(ENV(TO),"The lid of the "+query_short()
	  +" slides open with a loud grinding noise.\n");
	remove_prop(CONT_I_CLOSED);

	return 1;
    }

    notify_fail("Open what?\n");
    return 0;
}

int
do_inclose(string str)
{
    if (str == "" || !str)
	return 0;

    if (TO != ENV(TP))
    {
	return(0);
    }
    if(str=="coffin" || str=="lid" || str=="sarcophagus")
    {
	if(TO->query_prop(CONT_I_CLOSED))
	{
	    write("The "+query_short()+" is already closed.\n");
	    return 1;
	}
	write("Finding hand-holds inside, you pull the lid of the "
	  +query_short()+" closed with a few great heaves.\n");
	tell_room(ENV(TO),"The lid of the "+query_short()
	  +" slides closed, bit by bit.\n");
	add_prop(CONT_I_CLOSED, 1);
	return 1;
    }
    return 0;
}

int
do_leave(string str)
{
    if(TO != ENV(TP))
	return 0;

    notify_fail(CAP(QVB)+" what?\n");
    if(TO->query_prop(CONT_I_CLOSED))
    {
	write("The "+query_short()+" is closed.\n");
	return 1;
    }

    write("You climb out of the "+query_short()+".\n");
    if (!living(ENV(TO)))
	TP->move_living("M", ENV(TO));
    else
	TP->move_living("M", ENV(ENV(TO)));
    say(QCNAME(TP) + " climbs out of the "+query_short()+".\n");
    return 1;
}

int 
do_enter(string str)
{
    object *ob;
    int i;
    string fail_msg = "";

    if (str == "" || !str)
	return 0;

    notify_fail("You are already inside the "+query_short()+".\n");
    if (TO == ENV(TP))
	return 0;

    notify_fail("Enter what?\n");
    ob = normal_access(str, "%i");
    if (!sizeof(ob))
	return 0;

    for( i = 0; i < sizeof(ob); i++ )
    {
	if (ob[i]->query_prop(CONT_I_CLOSED))
	{
	    write("The "+ob[i]->query_short()+" is closed.\n");
	    return 1;
	}
	if(TP->move(ob[i]))
	{
	    write("There is not enough room in the "+ob[i]->query_short()+".\n");
	    return 1;
	}

	tell_room(ENV(TO), QCTNAME(TP)+" enters the "+ob[i]->query_short()+".\n");
	write("You enter the "+ob[i]->query_short()+".\n");
	STATSERV_LOG_EVENT("crypt", "Sarcophagus entered");
	return 1;
    }

    notify_fail("Enter what?\n");
    return 0;
}


varargs int open(object ob)
{
    object rev;
    if (rev = present("_crypt_crawler", ENV(TO)))
    {
	write("You cannot open this while the " + rev->short() + " is here.\n");
	return 3;
    }
    return 0;
}

string
coffin_long()
{
    if (ENV(TP) == TO)
    {
	return("This sarcophagus lies deep within the catacombs of "
	  +"Sybarus. It is dark and dank, reminding you of the "
	  +"dead laid to rest in it.\n");
    }
    else
    {
	return("This is a "+adj+" sarcophagus, made "
	  +"of a single piece of "+type+". It is very ornate. "
	  +"It is beautifully carved with realistic flowers and "
	  +"vines, jewels and precious metals. It is probably "
	  +"the final resting place of someone of great importance.\n");
    }
}

string
coffin_view()
{
    if (TO == ENV(TP))
    {
	if(TO->query_prop(CONT_I_CLOSED))
	    return("The lid of the sarcophagus is closed.\n");
	else
	    return("You peer out of the sarcophagus and see:\n"
	      +ENV(TO)->query_long());
    }
    return("You are not inside the "+query_short()+".\n");
}
