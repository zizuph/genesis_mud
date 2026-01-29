/* 
 * A shirt for the Union of the Warriors
 * of Shadow. Cirion 031696
 *     Updated by Lilith 17 June 2001
 *                Lilith 18 June 2004: changed wear to members only.
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";
inherit "/lib/keep";
inherit "/lib/wearable_item";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>

#define SHIRT_SUBLOC	"_union_shirt_subloc" 


public void
create_object()
{
    set_keep(1);
    config_wearable_item(A_TORSO, 2, 20, this_object());

    set_name("shirt");
    add_name(({"vestment", "garment"}));
    set_adj(({"fine","black","wool","woolen", "long-sleeved"}));
    add_adj("union");
    add_adj("unworn");
    set_pshort("black shirts");
    set_short("black shirt");
    set_long("A black shirt made of the finest wool that "+      
      "Sybarus has to offer. It is a fairly loose, "+
      "long-sleeved garment that can be worn over armour. "+
      "Its purpose is ornamental "+
      "rather than protective, for this vestment bears "+
      "the symbol of the dark-blue flame rising from a black "+
      "sphere against a grey stone background. Those who are "+
      "privileged to wear it do so with pride and restraint, "+
      "for it is the proof of their dedication to Sybarus and Jazur, "+
      "and its wearer commands the respect of all sybarites.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE,  300);  

    if (IS_CLONE)
      set_item_expiration(); 
}

public mixed 
wear(object ob)
{
    object tp = environment();

    if ((tp != TP) || (ob != TO))
	return -1;

    if (member_array(SHIRT_SUBLOC, tp->query_sublocs()) > -1)
	return "You are already wearing a "+ short() +".\n";

    if (!IS_MEMBER(TP))
	return "You cannot seem to fit it over your head.\n";

    /* Successful wear */
    write("You wear "+ LANG_THESHORT(TO) +" with pride.\n");
    say(QCTNAME(TP) +" wears "+ LANG_THESHORT(TO) +" with pride.\n");

    tp->add_subloc(SHIRT_SUBLOC, TO);
    return 1;
}

public int 
remove(object ob)
{
    if ((ob != TO) && (TP != query_worn()))
	return -1;

    TP->remove_subloc(SHIRT_SUBLOC);
    return 0;
}

public void
leave_env(object dest, object old)
{
    ::leave_env(dest, old);
    wearable_item_leave_env(dest, old);    
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != SHIRT_SUBLOC)
	return "";

    if (for_obj != on)
    {
	return CAP(HIS(on)) +" black shirt bears the symbol "+
	    "of a dark flame rising from a black sphere.\n";
    }
    else
    {
	return "Your black shirt bears the symbol of a dark "+
	    "flame rising from a black sphere.\n";
    }
}


public void
appraise_object(int num)
{
    ::appraise_object(num);

}

public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);

}
