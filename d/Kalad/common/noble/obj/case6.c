inherit "/std/object";
#include "/d/Kalad/defs.h"
/* sarr */

object ob;

void
create_object()
{
    set_name("case");
    set_adj("glass");
    set_short("glass case");
    add_name("_case6_");
    set_long("This is a wooden table with a glass case over it. "+
    "Underneath the glass you see an artifact being displayed. A"+
    " gold plaque is placed under it.\n"+
    "The glass case contains:\n"+
    "   A glowing blue sphere.\n");
    seteuid(getuid());
    ob = clone_object("/d/Emerald/kroad/graveyard/obj/sphere1.c");
    add_item("sphere",ob->query_long()+"\n");
    add_item("shape","You can't see it well within the glass.\n");
    add_prop(OBJ_M_NO_GET,"A strange magical force is protecting it.\n");
    add_item(({"gold plaque","plaque"}),"This strange item was "+
    "taken from the drow during the raids of Kabal. There is a strange "+
    "story behind it, although all is not clear. It was held by an "+
    "ancient drow mage, who has said to have gotten it by a drow "+
    "from a far away land, who brought it to have it hidden. There "+
    "is also mention of some strange power placed in it by someone "+
    "named Telen-Ri. But, we have no idea what that means, and all "+
    "the sages in the world could not figure it out. It remains "+
    "a mystery.\n");

}

