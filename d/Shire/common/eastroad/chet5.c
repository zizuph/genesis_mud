#include "defs.h"

create_eastroad()
{
    set_short("On Great Eastroad");
    set_long("@@my_long@@");

    NORTHWEST("chet4"); EAST("forsaken");

    add_item(({"forest","wood","chetwood"}),
	"The forest consists mostly of firs and hemlocks, so it does not "+
	"look so inviting.\n");
    add_item(({ "fir","firs","hemlock","hemlocks"}),
    "They stand tall and silent in the gloomy forest.\n");
    add_item("house",
    "You will need to get closed to make out any detail.\n");
}

string
my_long()
{
    string str =
	"You are standing on the Great Eastroad from Bree to Rivendell. ";

    if(TP->query_skill(SS_LOC_SENSE)>10) str =
	"A dark forest called Chetwood surrounds you ";
    else str =
	"A dark forest surrounds you ";

    if(TP->query_skill(SS_HERBALISM)>5)
	str += "consisting of firs and hemlocks";
    else
	str += "here";

    return str + ". " +
	"A path continues into the forest to the northwest. " +
	"The road also continues east towards an abandoned house.";
}
