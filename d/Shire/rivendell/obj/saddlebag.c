/*
 * Made pouch recoverable and keepable
 * -- Finwe, April 2002
 *
 * 2003/01/20 Last update
 * 2011/07/20 Lavellan - Really made it recoverable

 */

inherit "/d/Terel/calathin/obj/saddlebag";
inherit "/lib/keep";
#include <stdproperties.h>
#include <macros.h>

void
create_wearable_pack()
{
    set_name("saddlebag");
    add_name( ({"bag", "light saddlebag", "light gray saddlebag" }) );
    add_pname( ({"saddlebags", "bags", "light saddlebags",
        "light gray saddlebags"}) );

    set_name("saddlebag");
    add_name(({"light saddlebag", "large gray saddlebag"}));
    set_short("light gray saddlebag");
    set_long("This is a light gray saddlebag made of some gray " +
        "material. It was expertly crafted by elves and is " +
        "designed to be draped over their horses. The saddlebag " +
        "has two large pouches which can hold many supplies when " +
        "travelling. There is a small tag sticking out from under " +
        "one of the flaps.\n");

    add_item("tag", "Maybe you should read it.\n");
    add_cmd_item("tag", "read", "@@read_tag@@");

    add_prop(CONT_I_WEIGHT, 2500);      /* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000);      /* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VALUE, 450);                 /* Worth 450 cc */

    set_keep(1);
    set_mass_storage(1);

}


string
read_tag()
{
    return "On the tag you read the following:\n\n"+
        "\t+---------------------------------------------+\n"+
        "\t| When draped on a horse, the following       |\n"+
        "\t| commands are available:                     |\n"+
        "\t|                                             |\n"+
        "\t| strap saddlebag on horse                    |\n"+
        "\t| unstrap saddlebag on horse                  |\n"+
        "\t| fill saddlebag on horse                     |\n"+
        "\t| open saddlebag on horse                     |\n"+
        "\t| close saddlebag on horse                    |\n"+
        "\t| empty saddlebag on horse                    |\n"+
        "\t|                                             |\n"+
        "\t| When sadlebag is not on a horse, it acts    |\n"+
        "\t| like a normal backpack.                     |\n"+
        "\t|. . . . . . . . . . . . . . . . . . . . . . .|\n"+
        "\t| Saddlebag courtesy of Eleithiel of Imladris |\n"+
        "\t+---------------------------------------------+\n";

}


string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg); 
}

