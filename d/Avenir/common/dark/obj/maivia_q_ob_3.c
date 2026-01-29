// Scroll from Maivia to Nochipa
// Lilith, Aug 2014

inherit "/std/object";
inherit "/lib/keep";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/dark/maivia_quests.h"

private int do_open(string str);
private int do_read(string str);

private void
create_object()
{
	set_name("scroll");
	add_name(M_N_O);
	set_adj(({"sealed","red-trimmed"}));
	set_short("sealed red-trimmed scroll");
	set_long("This is a rolled up scroll that is trimmed in red "+
			 "on the edges. There is a chimera-shaped seal on "+
			 "it.\n");
	add_item(({"seal", "wax", "chimera"}), 
			 "The seal on the letter is made from "+
			 "black wax, and impressed in the wax is a "+
			 "majestic chimera.\n");
	
	add_prop(OBJ_I_VALUE,  25);
    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VOLUME, 30);
	
    set_keep(1);
	
}


public void
init(void)
{
    ::init();
	
    if (ENV(TO) != TP)
		return;
	
    add_action("do_open","open");
    add_action("do_open","unseal");
    add_action("do_open","break");
    add_action("do_read", "read");
	
	
}

private int
do_open(string str)
{
    if(!str || str == "")
        return 0;
    if(str == "scroll" || str == "seal")
    {
        write("You break the seal on the red-trimmed scroll. "+
			  "It crumbles into tiny pieces.\n");
		TO->set_short("blackened scroll");
		TO->set_long("This is a rolled up scroll that is red along "+
					 "the edges.\n");
		TO->remove_item("seal");
		TO->remove_item("wax");
		TO->remove_item("chimera");
		TO->remove_adj("sealed");
		TO->add_prop(Q_OB_OPENED, 1);
        return 1;
    }
    return 0;
}

private int
do_read(string str)
{
	if(!str || str == "")
        return 0;
    if(str == "scroll")
    {
		if (TO->query_prop(Q_OB_OPENED))
		{	
	        write("The scroll reads:\n\n\n"+
				"  Chiba Nochipa Jainalae,\n"+
				"  Ae grigosa sur yan disdagrigu Sybarus abinhalagraka.\n"+
			    "  Kilinku bent qa goralus hun alimtu beara wei.\n"+
			    "  Su hadar palanyu firutu oposrewn iw yan manudurindal est.\n"+
			    "  Ae dridin wrenda yan limno apabo.\n\n"+
			    "     Maivia \n");
		    return 1;
		}
		else
		{
			write("You must break the seal before you can read it.\n");
			return 1;			
		}
	}
	return 0;
}
