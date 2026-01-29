#include "defs.h"

create_eastroad()
{
    set_short("On Great Eastroad");
    set_long("@@my_long@@");

    WEST("chet3"); SOUTHEAST("chet5");

    add_item(({"forest","wood","chetwood"}),
	"The forest consists mostly of firs and hemlocks, so it does not "+
	"look so inviting.\n");
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
	"The road continues south-east into more light woods, "+
	"and further west into the forest.";
}
