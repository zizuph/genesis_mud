#include "defs.h"
#include "/d/Shire/common/defs.h"

create_eastroad()
{

   object hob;
    set_short("On Great Eastroad");
    set_long("@@my_long@@");

    add_item(({"bree-hill","bree","town","slopes"}),
	"The hill slopes quite gently some hundred meters. On the top you "+
	"can see some hobbit holes, and further down you see a hobbit village.\n");
    add_item(({"staddle","village"}),
	"Well, you can't tell so much of it from here.\n");
    add_item(({"forest","wood","chetwood"}),
	"The forest consists mostly of firs and hemlocks, so it does not "+
	"look so inviting\n.");

    add_exit(STAND_PARENT + "bree/egate", "southwest",0);
   hob = clone_object("/d/Shire/common/eastroad/npc/fathob");
   hob->move(TO);
    add_exit(STAND_DIR + "chet2", "northeast", 0);
}

string
my_long()
{
    if(TP->query_skill(SS_LOC_SENSE)>10)
	return
	    "You are standing on the Great Eastroad somewhat east of "+
	    "Bree-Hill. You can not see the town from here, but on "+
	    "the hill there are several holes, which must be the hobbit "+
	    "village Staddle. The Great Eastroad continues southwest to "+
	    "Bree and northeast into a large forest called Chetwood.";
    else
	return
	    "You are standing on the Great Eastroad somewhat east of "+
	    "a large hill. On the hill there are several holes, which "+
	    "must be a hobbit village. The Great Eastroad continues southwest "+
	    "to Bree and northeast into a large forest.";
}
