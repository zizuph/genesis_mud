#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <macros.h>

inherit SANCINROOM;

object  herb_rack,
        misc_rack,
        armour_rack,
        polearm_rack,
        rack_attendant;


public object
query_rack_object()
{
    return polearm_rack;
}

void
create_sanction_room()
{
    seteuid(getuid());
    
    set_short("inside a military depot of the Red Dragonarmy");
    set_long("@@long_descr");

    add_item(({"small stone building","stone building","building",
	"depot","military depot"}),"@@long_descr");
    add_item("door","The door out of the military depot " +
      "is to your northeast.\n");

    add_exit(SRED + "r3","northeast",0);
    add_cmd_item(({"uniform","dragonarmy uniform"}),"request","@@request_uniform");

    /* Pointless to use the ifs, but copy paste from other code and lazy.
     * Should be in reset_krynn_room, but it has been masked.
     */
    
    if (!herb_rack)
    {
        herb_rack = clone_object(SOBJ + "rack/rack_rda_herb.c");
        herb_rack->move(this_object(), 1);
    }
    
    if (!misc_rack)
    {
        misc_rack = clone_object(SOBJ + "rack/rack_rda_misc.c");
        misc_rack->set_rack_log_file(SOBJ + "rack/rda_armoury_log");
        misc_rack->move(this_object(), 1);
    }
    
    if (!armour_rack)
    {
        armour_rack = clone_object(SOBJ + "rack/rack_rda_armour.c");
        armour_rack->set_rack_log_file(SOBJ + "rack/rda_armoury_log");
        armour_rack->move(this_object(), 1);
    }
    
    if (!polearm_rack)
    {
        polearm_rack = clone_object(SOBJ + "rack/rack_rda_polearm.c");
        polearm_rack->set_rack_log_file(SOBJ + "rack/rda_armoury_log");
        polearm_rack->move(this_object(), 1);
    }
    
    if (!rack_attendant)
    {
        rack_attendant = clone_object(SNPC + "rack_attendant.c");
        rack_attendant->set_color("red");
        rack_attendant->move(this_object(), 1);
    }
}

int
request_uniform()
{
    object uniform;

    if(!IS_MEMBER(TP))
    {
        write("The quartermaster ignores you.\n");
        return 1;
    }

    uniform = clone_object("/d/Ansalon/guild/dragonarmy/obj/uniform");
    uniform->set_colour("red");
    uniform->set_dalevel(TP->query_dragonarmy_promotions());
    uniform->move(TP);

    write("A surly quartermaster steps up to you and hands you "+
      "a "+uniform->short()+".\n");
    say("A surly quartermaster steps up to " +QTNAME(TP)+ " and "+
      "hands " +HIM(TP)+ " a "+uniform->short()+".\n");
    return 1;
}

string
long_descr()
{
    return "You stand within a small stone building used by " +
    "the Red Dragonarmy as their military depot. Here, " +
    "all sorts of equipment ranging from training weapons to " +
    "armours worn on the field are left by soldiers for other " +
    "soldiers to use. Here one may 'request dragonarmy uniform' to "+
    "be issued with suitable soldier attire. To your northeast, "+
    "a door leads out.\n";
}

public void
leave_inv(object ob, object to)
{
    object *books;
    
    if (sizeof(books = filter(deep_inventory(ob), &->query_rack_log())))
    {
        if (rack_attendant)
        {
            ob->catch_msg(QCTNAME(rack_attendant) + " runs after you as you "
            + "are about to leave and retrieves the " + books[0]->short() + " "
            + "from your possession.\n");
            rack_attendant->tell_watcher(QCTNAME(ob) + " tries to leave but is "
            + "stopped by " + QTNAME(rack_attendant) + ", forced to return "
            + LANG_ADDART(books[0]->short()) + " before continuing on "
            + ob->query_possessive() + " way.\n", ({ ob }));
        }
        
        books->remove_object();
    }
    
    ::leave_inv(ob, to);
}