/*
 * Study of the Elemental Temple of Calia
 * 
 * Created by Jaacar, June 2016
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Calia/guilds/scop/specials/scop.h"

inherit TEMPLE_ROOM_BASE;

// Defines
#define SEA_OBJS        "/d/Calia/sea/objects/"
#define SPIRIT_OBJECTS  "/d/Calia/guilds/scop/objects/"

// Prototypes

// Global Variables
object closet;

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

public void
create_temple_room()
{
    set_short("Elemental Study");
    set_long("This chamber is much smaller than any other you "+
        "have been in while inside of this temple. All four walls "+
        "are polished wood, the ceiling and floor both a smoothly "+
        "polished grey stone. Upon entering this small chamber, "+
        "your eyes focus upon a small stand sitting against "+
        "the western wall and a tall double-doored closet on the "+
        "northern wall. The stand has several drawers to hold "+
        "different items. On the wall above the stand is a small "+
        "rack. The main hallway lies back out to the "+
        "northeast.\n\n");   
                   
    add_exit(ELEMENTALIST_TEMPLE + "stairwell3", "northeast");     
    
    try_item(({"ingot","ingots","silver ingot","silver ingots"}),
        "These silver ingots are thin rods delicately carved with "+
        "tiny pentacles in a repetitive pattern around the shafts. "+
        "You could probably unhook one if you wanted one to take with you. "+
        "<unhook ingot>\n");
    try_item(({"rack","small rack"}),"It is a small wooden rack hanging "+
        "on the wall above the stand. Hanging from the rack are several "+
        "silver ingots, some ceremonial daggers and some cloaks.\n");     
    try_item(({"cloak","cloaks"}),"They are cloaks hanging on a rack. You "+
        "could probably unfasten one if you wanted on to take with you. "+
        "<unhook cloak>\n");    
    try_item(({"dagger","daggers","ceremonial dagger","ceremonial daggers"}),
        "They are ceremonial daggers hanging on a rack. You "+
        "could probably unhook one if you wanted on to take with you. "+
        "<unhook dagger>\n");  
    try_item(({"drawer","drawers"}),"There are several drawers in the "+
        "small stand to hold different items and components.\n");
    try_item(({"stone","grey stone","polished stone","polished grey stone"}),
        "Both the walls and the ceiling are made of polished grey stone.\n");
    try_item("sleeping chamber","The sleeping chamber lies back out "+
        "to the west.\n");
    try_item(({"floor","roof","ceiling"}),"The floor and ceiling are "+
        "both constructed with a grey stone and then smoothed and "+
        "polished afterwards. The floor is quite comfortable to "+
        "walk on.\n");
    try_item(({"wall","walls"}),"The walls here are covered in a "+
        "polished wood, light brown, almost red, in colour. They are "+
        "extremely smooth to the touch.\n");
    try_item("ceiling", "The floor and ceiling are both constructed with a "+
      "grey stone and then smoothed and polished afterwards.\n");

    clone_object(ELEMENTALIST_OBJS+"small_stand")->move(TO);
        
    // Add the leftover closet
    closet = clone_object(ELEMENTALIST_OBJS +"leftover_closet");
    closet->move(TO, 1);
    closet->set_no_show_composite(1);
}

int
do_unhook(string str)
{
    object item;

    if (!str)
    {
        NF("Unhook what? An ingot? <unhook ingot> A dagger? <unhook dagger> A cloak? <unhook cloak>\n");
        return 0;
    }

    if ((!parse_command(str, ({}),"[an] [a] [the] [silver] 'ingot'")) &&
    	(!parse_command(str, ({}),"[a] [the] [ceremonial] 'dagger'")) &&
    	(!parse_command(str, ({}),"[a] [the] 'cloak'")))
    {
        NF("Unhook what? An ingot? <unhook ingot> A dagger? <unhook dagger> A cloak? <unhook cloak>\n");
        return 0;
    }
    
    if (parse_command(str, ({}),"[an] [a] [the] [silver] 'ingot'"))
    {
    	if (!present("pentacled silver ingot",TP))
	    {
	        item = clone_object(SEA_OBJS+"corpse_cleaner");
	        write("You unhook an ingot from the rack and take it.\n");
	        say(QCTNAME(TP)+" unhooks an ingot from the small rack and takes it.\n");
	        item->move(TP);
	        return 1;
	    }
	    NF("You already have a silver ingot, no use having two!\n");
	    return 0;
	}
	if (parse_command(str, ({}),"[a] [the] [ceremonial] 'dagger'"))
    {
    	if (!present("_spirit_ceremonial_dagger_",TP))
	    {
	        item = clone_object(ELEMENTALIST_OBJS+"ceremonial_dagger");
	        write("You unhook a dagger from the rack and take it.\n");
	        say(QCTNAME(TP)+" unhooks a dagger from the small rack and takes it.\n");
	        item->move(TP);
	        return 1;
	    }
	    NF("You already have a ceremonial dagger, no use having two!\n");
	    return 0;
	}
	if (parse_command(str, ({}),"[a] [the] 'cloak'"))
    {
    	if (!present("_wor_cloak_",TP))
	    {
	        item = clone_object(ELEMENTALIST_OBJS+"cloak");
	        write("You unhook a cloak from the rack and take it.\n");
	        say(QCTNAME(TP)+" unhooks a cloak from the small rack and takes it.\n");
	        item->move(TP);
	        return 1;
	    }
	    NF("You already have a cloak, no use having two!\n");
	    return 0;
	}
	NF("Unhook what? An ingot? <unhook ingot> A dagger? <unhook dagger> A cloak? <unhook cloak>\n");
    return 0;
}

int
do_hook(string str)
{
    object item;

    if (!str)
    {
        NF("Hook what? An ingot? <hook ingot> A dagger? <hook dagger> A cloak? <hook cloak>\n");
        return 0;
    }

    if ((!parse_command(str, ({}),"[an] [a] [the] [silver] 'ingot'")) &&
    	(!parse_command(str, ({}),"[a] [the] [ceremonial] 'dagger'")) &&
    	(!parse_command(str, ({}),"[a] [the] 'cloak'")))
    {
        NF("Hook what? An ingot? <hook ingot> A dagger? <hook dagger> A cloak? <hook cloak>\n");
        return 0;
    }
    
    if (parse_command(str, ({}),"[an] [a] [the] [silver] 'ingot'"))
    {
    	item = present("pentacled silver ingot",TP);
    	if (!item)
	    {
	        NF("You do not have an ingot to hang back on the hook.\n");
	        return 0;
	    }
    	write("You carefully wash the silver ingot, making sure it is "+
	        "clean and ready for the next person to use. When you are sure it "+
	        "is clean, you hang the ingot back on the hook.\n");
	    say(QCTNAME(TP)+" carefully washes the silver ingot that "+
	        TP->query_pronoun()+" is holding. When "+TP->query_pronoun()+
	        " is sure it is clean, "+TP->query_pronoun()+" hangs the ingot "+
	        "back on the hook.\n");
	    item->remove_object();
	    return 1;
	}
	if (parse_command(str, ({}),"[a] [the] [ceremonial] 'dagger'"))
    {
    	item = present("_spirit_ceremonial_dagger_",TP);
    	if (!item)
	    {
	        NF("You do not have a ceremonial dagger to hang back on the hook.\n");
	        return 0;
	    }
    	write("You carefully wash the ceremonial dagger, making sure it is "+
	        "clean and ready for the next person to use. When you are sure it "+
	        "is clean, you hang the dagger back on the hook.\n");
	    say(QCTNAME(TP)+" carefully washes the ceremonial dagger that "+
	        TP->query_pronoun()+" is holding. When "+TP->query_pronoun()+
	        " is sure it is clean, "+TP->query_pronoun()+" hangs the dagger "+
	        "back on the hook.\n");
	    item->remove_object();
	    return 1;
	}
	if (parse_command(str, ({}),"[a] [the] 'cloak'"))
    {
    	item = present("_wor_cloak_",TP);
    	if (!item)
	    {
	        NF("You do not have a cloak to hang back on the hook.\n");
	        return 0;
	    }
    	write("You carefully brush off any dirt from the cloak, making sure it is "+
	        "clean and ready for the next person to use. When you are sure it "+
	        "is clean, you hang the cloak back on the hook.\n");
	    say(QCTNAME(TP)+" carefully brushes any dirt from the cloak that "+
	        TP->query_pronoun()+" is holding. When "+TP->query_pronoun()+
	        " is sure it is clean, "+TP->query_pronoun()+" hangs the cloak "+
	        "back on the hook.\n");
	    item->remove_object();
	    return 1;
	}
	NF("Hook what? An ingot? <hook ingot> A dagger? <hook dagger> A cloak? <hook cloak>\n");
    return 0;
}

int
do_read(string str)
{
    if (str != "sign")
    {
        NF("Read what? The sign? <read sign>\n");
        return 0;
    }

    write("The sign reads:\nIf for some reason you have lost your "+
        "holy symbol, simply return to this place and type <recover "+
        "symbol>.\n");
    return 1;
}

int
do_recover(string str)
{
    if (!is_spirit(TP))
    {
        NF("Recover what?\n");
        return 0;
    }

    if (str != "symbol")
    {
        NF("Recover what? Your holy symbol? <recover symbol>\n");
        return 0;
    }

    if (present("spirit_holy_symbol",TP))
    {
        NF("You already have your holy symbol!\n");
        return 0;
    }

    write("A shadowy hand appears from the wall, holding a new "+
        "holy symbol for you. You reach out and take it.\n");
    clone_object(SPIRIT_OBJECTS+"holy_symbol")->move(TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_unhook,"unhook");
    add_action(do_hook,"hook");
    add_action(do_read,"read");
    add_action(do_recover,"recover");
}