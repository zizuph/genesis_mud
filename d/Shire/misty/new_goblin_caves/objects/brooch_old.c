inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

static int worn;

void 
create_object()
{
    set_name(({"club","brooch","_club_sup_guru_"}));
    set_adj(({"silver","small"}));
    set_short("small silver club");
    set_long("This is a nice silver brooch in the shape of a club. It has "+
      "a silver handle two inches long with a pin attached to it so you "+
      "can wear it on your clothes. At the end of the handle is silver "+
      "chain with a small spiked silver ball so the whole brooch looks "+
      "like a morning-star. When you move the ball swings on the chain "+
      "and gives nice lively effect.\n");

    add_prop(OBJ_I_VOLUME, 23);
    add_prop(OBJ_I_WEIGHT, 57);
    add_prop(OBJ_I_VALUE,  100000);
    add_prop(OBJ_M_NO_SELL,"No! This brooch is so nice that you would rather "+
      "starve to death than sell it!\n");
    add_prop(OBJ_M_NO_DROP,"No! You would never give such a beauty out of "+
      "your hands!\n");
}

void
init()
{
    ::init();
    add_action("wear", "wear");
    add_action("remove", "remove");
} 

int
wear(string arg)
{
    notify_fail("Wear what?\n");
    if(!parse_command(arg, TO, " %o ")) return 0;
    NF("First you must have it!\n");
    if(ENV(TO) != TP) return 0;
    NF("But you already wear it!\n");
    if(worn) return 0;

    write("You pin the "+short()+" on your chest.\n");
    say(QCTNAME(TP)+" pins a "+short()+" on "+HIS_HER(TP)+" chest.\n");

    worn = 1;
    TP->add_subloc(file_name(TO), TO);
    set_no_show_composite(1);
    return 1;
}

int
remove(string arg)
{
    NF("Remove what?\n");
    if(!parse_command(arg, TO, " %o ")) return 0;
    NF("First you must have it!\n");
    if(ENV(TO) != TP) return 0;
    NF("But you don't wear it!\n");
    if(!worn) return 0;

    write("You remove the "+short()+" from your chest.\n");
    say(QCTNAME(TP)+" removes a "+short()+" from "+HIS_HER(TP)+" chest.\n");

    worn = 0;
    TP->remove_subloc(file_name(TO));
    set_no_show_composite(1);
    return 1;
}

string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != file_name(TO))
	return "";

    if (for_obj != on)
	return CAP(HE_SHE(on))+" is wearing a small silver club-brooch on "+HIS_HER(on)+
	" chest. The small spiked ball on the chain swings with "+
	HIS_HER(on)+" every move.\n";
    else
	return "You are wearing the small silver club-brooch on your chest.\n";
}

string 
query_auto_load() 
{
    return MASTER+":"; 
}

int id_aa_sup_guru_club(){ return 1; }


/* Person shouldn't be able to carry more than one of these around */ 
void
enter_env(object dest, object old)
{
    object *obs;
    int i, change;

    obs = all_inventory(dest);

    change = 0;
    for (i = 0; i < sizeof(obs); i++)
    {
	if (obs[i]->id_aa_sup_guru_club() && obs[i] != this_object())
	{
	    obs[i]->remove_object();
	    change++;
	}
    }

    if (change)
	dest->catch_msg("You have lost something!\n");
    ::enter_env(dest, old);
}

