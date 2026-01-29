#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <macros.h>

inherit SANCINROOM;

object  herb_rack,
        misc_rack,
        armour_rack,
        sword_rack,
        rack_attendant;
    

public object
query_rack_object()
{
    return sword_rack;
}

void
create_sanction_room()
{
    set_short("inside the armoury of the Blue Dragonarmy");
    set_long("@@long_descr");

    add_item(({"white canvas tent","canvas tent","tent"}),
      "@@long_descr");

    add_exit(SBLUE + "r4","south",0);
    add_cmd_item(({"uniform","dragonarmy uniform"}),"request","@@request_uniform");

    /* Pointless to use the ifs, but copy paste from other code and lazy.
     * Should be in reset_krynn_room, but it has been masked.
     */
    
    if (!herb_rack)
    {
        herb_rack = clone_object(SOBJ + "rack/rack_bda_herb.c");
        herb_rack->move(this_object(), 1);
    }
    
    if (!misc_rack)
    {
        misc_rack = clone_object(SOBJ + "rack/rack_bda_misc.c");
        misc_rack->set_rack_log_file(SOBJ + "rack/bda_armoury_log");
        misc_rack->move(this_object(), 1);
    }
    
    if (!armour_rack)
    {
        armour_rack = clone_object(SOBJ + "rack/rack_bda_armour.c");
        armour_rack->set_rack_log_file(SOBJ + "rack/bda_armoury_log");
        armour_rack->move(this_object(), 1);
    }
    
    if (!sword_rack)
    {
        sword_rack = clone_object(SOBJ + "rack/rack_bda_sword.c");
        sword_rack->set_rack_log_file(SOBJ + "rack/bda_armoury_log");
        sword_rack->move(this_object(), 1);
    }
    
    if (!rack_attendant)
    {
        rack_attendant = clone_object(SNPC + "rack_attendant.c");
        rack_attendant->set_color("blue");
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
    uniform->set_colour("blue");
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
    return "You stand within a white canvas tent used by the " +
    "Blue Dragonarmy soldiers as their armoury. " +
    "Weapons and armours are left here neatly for future use " +
    "by soldiers. Here one can 'request dragonarmy uniform' "+
    "for appropriate soldier attire. The heat in here is rather " +
    "oppressive, not surprising considering the tents location, " +
    "on the edge of the city of fire and lava, Sanction." +
    "\n";
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