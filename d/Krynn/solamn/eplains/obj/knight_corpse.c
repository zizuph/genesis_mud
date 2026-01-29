inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


int bag_taken = 0;
object lance;

void
create_object()
{
    set_name(({"skeleton","knight skeleton", "skeleton of a knight of solamnia"}));
    set_short("the skeleton of a knight of Solamnia");
    set_long("This bleached and gnawed skeleton is all that remains of a knight " +
      "of Solamnia. This brave, or perhaps foolish, warrior obviously fought hard " +
      "before finally joining Huma in Paladine's arms. His ornamented plate armour " +
      "is scorched and broken from what looks like lightning, with great rents in " +
      "the chain from what looks like great claws. " +
      "@@bag_message@@" +"\n");
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_WEIGHT,100000);
    add_prop(OBJ_M_NO_GET, 1);

    add_cmd_item(({"lance from skeleton", "lance from corpse",
	"lance from skeleton of a knight of solamnia"}),
      ({"get","take"}),"@@get_bag");
    setuid; seteuid(getuid());
}

void
remove_remains()
{
    tell_room(E(TO),"The skeleton decays into dust.\n");
    TO->remove_object();
}

string
bag_message()
{
    if(bag_taken == 1)
    {
	return "";
    }
    else
	return "You notice its skeletal hand still holds tightly to an intact lance.";
}

string
get_bag()
{

    if(P("dragon", E(TO)))
    {
       write("The dragon turns quickly towards you, driving you away from " +
         "the skeleton.\n");
       return "";
    }
 


    if(bag_taken == 1)
    {
	write("There is lance to get from the skeleton.\n");
	return "";
    }
    else
	write("You pry the lance from the dead knight's hand...\n");
    say(QCTNAME(TP)+ " pries the lance from the dead knight's hand.\n");
    lance = clone_object("/d/Krynn/solamn/vin/weapon/s_halberd");
    lance->move(TP);


    bag_taken = 1;
    set_alarm(30.0,0.0,&remove_remains());
    return "";
}
