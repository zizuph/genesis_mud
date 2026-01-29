#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

#define BARRELHOLE_I_MORTAL_DENIED_ENTRY "_barrelhole_i_mortal_denied_entry"

inherit DWARF_IN;

void
reset_dwarf_room()
{
}

void
create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"pallet","straw","disturbed straw"}),
            "The straw pallet is disturbed as though people "+
            "have rolled heavily upon it.\n");

    add_item(({"barrel-end","open end"}),
     "The open end of the barrelcot will not close from the inside; "+
       "So it is too noisy to rest inside.\n");

    add_item(({"graffiti","closed end"}),
        "The scratched lettering of the graffiti in the "+
        "closed end of the barrelcot spell out "+
        "words in the common tongue; easy enough to <read>.\n");

    add_exit(IRON + "brewery1","south");

    reset_dwarf_room();

}

public void
hook_smelled(string str)
{
    write("The scent of straw and old brew prevail.\n");
}

string
short_descr()
{
    return "inside an open barrelcot in the Iron Delving Brewery";
}

string
long_descr()
{
    return "The interior of this barrelcot is large enough "+
     "for you to comfortably stand within. It is a large barrel, "+
     "formerly used for aging brew, now furnished with a "+
     "a simple straw pallet on which to rest. Or rather, "+
     "you could rest upon it if you could close the "+
     "barrel-end to find some peace and quiet. There is "+
     "graffiti scratched into the wood of the closed "+
     "barrel-end.\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    ob->remove_prop(BARRELHOLE_I_MORTAL_DENIED_ENTRY);
}

int
read_it(string str)
{
    if (!str)
    {
        return 0;
    }

    if (!strlen(str))
    {
        write("Read what?\n");
        return 0;
    }

    if (str == "graffiti" || str == "words")
    {
        write(" \n" +
          "I would while away the hours\n"+
          "using divine Powers;\n"+
          "I'd tear away the Veil!\n"+
          "I'd rise to God-like station,\n"+
          "all from pouring sweet libations,\n"+
          "If I only had a Grail.\n\n");
        return 1;
    }
}

void
init()
{
    ::init();
    add_action(read_it, "read");
}
