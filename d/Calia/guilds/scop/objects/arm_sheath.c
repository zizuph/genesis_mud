
/*
 * arm_sheathe.c
 *
 * An arm sheathe for the ceremonial dagger for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, August 15th, 2003
 *
 * Based off of the Golden Scabbard code
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "defs.h"
#include SPIRIT_HEADER

#define ASHEATH_SUBLOC   "_spirit_armsheath_subloc"

static object  Worn = 0;

/*
 * Function   : query_worn()
 * Description: Am I worn?
 * Returns    : the object who wears me
 */

public object
query_worn()
{
    return Worn;
}

/*
 * Function   : query_sheathed()
 * Description: Is anything sheathed in me?
 * Returns    : the object that is sheathed in me or 0
 */

public mixed
query_sheathed()
{
    if (sizeof(all_inventory(TO)))
        return all_inventory(TO)[0];

    return 0;
}

/*
 * Function   : filter_weapon()
 * Arguments  : obj: the object to test
 * Description: Test an object to see if it is a weapon
 * Returns    : true if it is a weapon, false if it is not
 */
static int
filter_weapon(object obj)
{
    return (function_exists("create_object", obj) == "/std/weapon");
}

/*
 * Function   : filter_knife()
 * Arguments  : obj: the object to test
 * Description: Test an object to see if it is a knife
 * Returns    : true if it is a knife, false if it is not
 */
static int
filter_knife(object obj)
{
    return (obj->query_wt() == W_KNIFE);
}

public int
can_i_drop()
{
    if (query_worn())
        return 1;

    return 0;
}

public string
short_desc()
{
    if (query_worn())
	    return "sheath strapped around the lower arm";
    else
        return "white cloth sheath";
}

public string
short_other()
{
    if (query_worn())
	    return "sheath strapped around "+environment(TO)->query_possessive()+
            " lower arm";
    else
        return "white cloth sheath";
}

public string
short_me()
{
    if (query_worn())
	    return "sheath strapped around your lower arm";
    else
        return "white cloth sheath";
}

public string
long_desc()
{
    string tmp;

    if (query_worn())
	tmp = "It has been strapped around the lower arm, and can be "+
        "unstrapped at any time.\n";
    else
        tmp = "It can be strapped around the lower arm.\n";

    return "It is a small sheath made from some type of white cloth-like "+
        "material. There are straps on the sheathe used to strap it to "+
        "the lower arm. It is the perfect sheath for a ceremonial dagger "+
        "or small dagger/knife.\n"+tmp+"";
}

/*
 * Function   : create_container()
 * Description: create a container object
 * Returns    : void
 */
public void
create_container()
{
    set_name("sheath");
    add_name("sheathe");
    set_adj(({"white", "cloth"}));
    add_name(({"arm-sheath", "armsheath"}));
    set_short("@@short_desc");
    set_long("@@long_desc");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_DROP,"@@can_i_drop");
    add_prop(CONT_I_WEIGHT,500);
    add_prop(CONT_I_VOLUME,500);
    add_prop(CONT_I_MAX_WEIGHT,50000);
    add_prop(CONT_I_MAX_VOLUME,25000);
    add_prop(OBJ_I_VALUE,250);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_M_NO_INS,"You may use 'cdsheathe' to put a knife into the "+
	"sheath.\n" );
    setuid();
    seteuid(getuid());
}

/*
 * Function   : do_sheathe()
 * Arguments  : str: the string that follows the verb 'cdsheathe'
 * Description: Sheathe a weapon in this item
 * Returns    : true if the weapon is sheathed, false if it is not
 */
public int
do_sheathe(string str)
{
    int     result;
    object *dagger, tp, here;

    tp = TP;
    here = environment(tp);
    
    if (!str)
    {
        dagger = tp->query_weapon(-1);
    }
    else
    {
        dagger = filter(FIND_STR_IN_OBJECT(str,tp), "filter_weapon",
            TO);
    }

    dagger = filter(dagger, "filter_knife", TO);

    if (sizeof(dagger) != 1)
    {
        NF("Sheathe which dagger/knife?\n");
        return 0;
    }

    if (sizeof(all_inventory(TO)))
    {
        NF("You cannot sheathe your "+dagger[0]->short()+
            ", there is already "+ LANG_ASHORT(all_inventory(TO)[0])+
            " in the "+ short()+ ".\n");
        return 0;
    }

    if (dagger[0]->query_wielded() == tp)
    {
        dagger[0]->unwield_me();
        if (dagger[0]->query_wielded() == tp)
        {
            NF("You cannot unwield your "+dagger[0]->short()+ ".\n");
            return 0;
        }
    }

    remove_prop(CONT_M_NO_INS);
    if (result = dagger[0]->move(TO))
    {
        switch (result)
        {
        case 1:
            NF("Your "+ dagger[0]->short()+ " is too heavy for "+
                "the "+ short()+ ".\n");
            break;
        case 8:
            NF("Your "+ dagger[0]->short()+ " is too large for "+
                "the "+ short()+ ".\n");
            break;
        default:
            NF("Strangely, you cannot sheathe your "+
                dagger[0]->short()+ " in the "+ short()+ ".\n");
            break;
        }
        return 0;
    }

    if(objectp(environment(tp)))
    {
        environment(tp)->update_light(1);
    }

    if (query_worn() != tp)
    {
        tp->catch_msg("You sheathe your "+dagger[0]->short()+" in the "+
	        short_me()+" that you carry.\n");
        tell_room(here, QCTNAME(tp)+" sheathes "+tp->query_possessive()+
	    " "+dagger[0]->short()+" in the "+short_other()+".\n", tp);
    }
    else     
    {
        tp->catch_msg("You sheathe your "+dagger[0]->short()+ 
            " in the "+short_me()+".\n" );
        tell_room(here, QCTNAME( tp )+ " sheathes "+tp->query_possessive()+ 
            " "+dagger[0]->short()+ " in the "+short_other()+".\n", tp);
    }
    
    add_prop(CONT_M_NO_INS, "You may use 'cdsheathe' to put a dagger/knife "+
        "into the sheathe.\n");

    return 1;
}

/*
 * Function   : do_draw()
 * Arguments  : str: the string that follows the verb cddraw
 * Description: draw a sheathed/holstered weapon from this object
 * Returns    : true if a weapon is drawn, false if one is not
 */
public int
do_draw( string str )
{
 object *dagger, to, tp, here;
 mixed res;


    tp  = this_player();
    here = environment(tp);

    if (!str)
    {
        dagger = all_inventory(TO);
    }
    else
    {
        dagger = FIND_STR_IN_OBJECT(str, TO);
    }

    if (!sizeof(dagger))
    {
        if (!str)
        {
            NF("Your "+ short()+ " is empty!\n");
        }

        else
        {
            NF("There is no "+ str+ " in your "+ short()+ "!\n");
        }

        return 0;
    }

    if (query_worn() != tp)
    {
        tp->catch_msg("You draw your "+dagger[0]->short()+" from the "+
	        short_me()+" that you carry.\n");
        tell_room(here, QCTNAME(tp)+" draws "+tp->query_possessive()+
	        " "+dagger[0]->short()+" from the "+short_other()+" that "+
	        tp->query_pronoun()+" carries.\n", tp);
    }

    else 
    {
        tp->catch_msg("You draw your "+dagger[0]->short()+ 
            " from the "+short_me()+".\n" );
        tell_room(here,QCTNAME(tp)+ " draws "+tp->query_possessive()+ 
            " "+ dagger[0]->short()+" from the "+short_other()+".\n", tp);
    }
    
    if (dagger[0]->move(tp))
    {
        dagger[0]->move(tp, 1);
    }
    
    if (stringp(res = dagger[0]->command_wield()))
    {
        write(res);
    }

    return 1;
}

/*
 * Function   : do_strap()
 * Arguments  : str: the string that follows the verb 'strap'
 * Description: Strap this item on
 * Returns    : True if it is strapped, false if it is not
 */
public int
do_strap(string str)
{
    int i;
    object *sc, tp, *armours;

    tp = this_player();

    if (!str)
    {
        NF("Strap what? The sheath on your lower arm?\n");
        return 0;
    }

    if (str == "all")
	    return 0;

    sc = FIND_STR_IN_OBJECT(str, tp);

    if (member_array(TO, sc) == -1)
    {
        NF("Do you want to strap on the "+short()+"?\n" );
        return 0;
    }

    if (objectp(Worn))
    {
        NF("You already have it strapped on!\n" );
        return 0;
    }

    if (member_array(ASHEATH_SUBLOC, tp->query_sublocs() ) > -1)
    { 
        if (str != "all")
        {
            write( "You already have another "+short()+" strapped on!\n" );
            return 1;
        }
        return 0;
    } 

    write("You strap the sheath around your lower arm.\n" );
    say(QCTNAME(tp)+ " straps a sheath around "+tp->query_possessive()+ 
        " lower arm.\n");
    
    tp->add_subloc(ASHEATH_SUBLOC, TO);

    Worn = tp;
                                 /*Do not display in the inventory.          */
    set_no_show_composite(1);
    return 1;
}

/*
 * Function   : do_remove()
 * Arguments  : str: the string that follows the verb 'remove'
 * Description: remove this item
 * Returns    : true if the item is removed, false if it is not
 */
public int
do_remove(string str)
{
    object *sc, tp;

    tp = this_player();

    if (!str)
        return 0;

    if (str == "all")
	    return 0;
    
    sc = FIND_STR_IN_OBJECT(str, tp);

    if (member_array(TO, sc) == -1)
    {
        NF("Do you want to remove the "+short()+"?\n");
        return 0;
    }

    if (!objectp(Worn))
    {
        NF("You are not wearing it!\n");
        return 0;
    }

    tp->remove_subloc(ASHEATH_SUBLOC);

    write("You unstrap the sheath and remove it from your lower arm.\n" );
    say(QCTNAME(tp)+ " unstraps a sheath and removes it from "+
	    tp->query_possessive()+" lower arm.\n" );
        
    Worn = 0;
                                /*Display back in the inventory.          */
    set_no_show_composite(0);

    return 1;
}

/*
 * Function   : show_subloc()
 * Arguments  : subloc: the string subloc
 *              on: the object the subloc is attached to
 *              for_obj: the object who is viewing the subloc
 * Description: Show a subloc message
 * Returns    : the string of the subloc
 */
public string
show_subloc( string subloc, object on, object for_obj )
{
    string data;

    if (subloc == ASHEATH_SUBLOC)
    {
        if (for_obj != on)
        {
            data = "";
        }
        else
        {
            if (query_worn())
            {
                if (query_sheathed())
		            data = "You have a "+query_sheathed()->short()+
                        " in your arm sheath.\n";
		        else
		            data = "You have a sheath strapped around your "+
                        "lower arm.\n";
            }
        }
        return data;
    }
    return 0;
}

/*
 * Function   : init()
 * Description: initialize this object
 * Returns    : void
 */
void
init()
{
    ::init();

    add_action(do_sheathe,"cdsheathe");
    add_action(do_draw,"cddraw");
    add_action(do_sheathe,"cdsheath");
    add_action(do_draw,"draw");
    add_action(do_sheathe,"sheath");
    add_action(do_sheathe,"sheathe");
    add_action(do_strap,"wear");
    add_action(do_remove,"remove");

}

string
query_auto_load()
{
    if (IS_MEMBER(environment(TO)))
	    return MASTER_OB(TO)+":";

    return 0;
}

