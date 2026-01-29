/* Created by Dajala
 * Questitem for the Gnomes' guild entrance quest.
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

string stext;
int sset;

void
remove_sign()
{
    tell_room(E(TO), "The sign withers away.\n");
    E(TO)->remove_my_desc();
    TO->remove_object();
}

void
create_object()
{
    set_name("sign");
    set_pname("signs");
    add_name("Gnomish_Sign");
    set_adj("gnomish");
    set_short("gnomish sign");
    set_long("The sign consists of a wooden board nailed to short pole."
		+ " There is a label stamped onto the pole.\n");
    add_item(({"label","label on sign","sign label"}),  "There is "
		+ "something written on it!\n");
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 100);

    sset = 0;
}

init()
{
    ::init();
    if (sset == 0)
	ADA("plant");
    ADA("read");
}

int 
read(string str)
{
    if (str == "label" || str == "label on sign" || str == "sign label")
    {
	write("The label reads: A product of Gnomish Industries.\n"
		+ "This product can 'plant sign <text>'.\n");
	return 1;
    }				
    if ((sset != 0) && (str == "sign"))
    {
	write("You can decipher the words:\n" + stext + "\n");	
	return 1;
    }				
    NF("Read what?\n");
    return 0;
}

int 
plant(string str)
{
    string *first;
    NF("Plant what?\n");
    if (!str)
	return 0;
    first = explode(str, " ");
    if (first[0] != "sign")
	return 0;
    if (P("Gnomish_Sign", E(TP)) && sset == 0)
    {
	NF("There is already a sign here. You should not "
		+ "try to confuse people with too many signs.\n");
	return 0;
    }
    if (sset != 0)
    {
	NF("There is already an important message written "
		+ "on the sign. You do not dare to erase it.\n");
	return 0;
    }
    stext = extract(str, 5, strlen(str));
    if (strlen(stext) > 70)
    {
	NF("You wouldn't be able to fit all that on the sign.\n");
	return 0;
    }
    if (strlen(stext) < 5)
    {
	NF("Don't you think that your message is too "
		+ "unimportant for this fine sign?\n");
	return 0;
    }
    sset++;
    stext = stext + "\nSigned: " + TP->query_name();
    write("You inscribe the message as legibly as you can, sign "
	+ "it and plunge the pole into the ground as deeply "
	+ "as possible.\n");
    say(QCTNAME(TP) + " scribbles something onto " + HIS(TP)
	+ " sign and plunges it deeply into the ground.\n");
    TO->move(E(TP)); 
    E(TP)->add_my_desc("Someone planted a sign here.\n");
    add_prop(OBJ_M_NO_GET, "The sign sticks too deep in the ground.\n");
    add_prop(OBJ_I_INVIS, 1);
    set_alarm(1500.0, -1.0, remove_sign);
    return 1;
}

string
check_for_text()
{
    return stext;
}
