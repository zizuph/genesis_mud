inherit "/std/container";
#include <stdproperties.h>

public void
create_container(void)
{
    reset_euid();

    object dust = clone_object("/std/heap");
    dust->set_name("dust");
    dust->set_short("pile of dust");
    dust->set_pshort("pile of dust");
    dust->set_long("It is a small pile of grey dust, smelling of "+
	"incense, memories, and death.\nThe dust is as fine "+
	"grained as ash.\n");
    dust->add_cmd_item(({"dust","pile"}),
	({"touch","rub","feel"}), "It feels warm.\n");
    dust->add_cmd_item(({"dust","pile"}),
	({"smell","sniff"}), "It smells strongly of incense.\n");

    dust->add_prop(HEAP_S_UNIQUE_ID, "_Avenir_union_tomb_dust");
    dust->add_prop(OBJ_I_WEIGHT, 2);
    dust->add_prop(OBJ_I_VOLUME, 2);
    dust->add_prop(OBJ_I_VALUE, 1);
    dust->set_heap_size(1 + random(10));
    dust->move(this_object());

    set_name("urn");

    switch(random(2))
    {
    case 0:
	set_short("small urn");
	add_adj("small");
	set_long("This is a small urn made from a reddish-brown "+
	    "pottery. Along the surface of the urn run tiny, "+
	    "waving lines in no descernable pattern.\n");
	add_prop(CONT_I_WEIGHT, 1000);
	add_prop(CONT_I_VOLUME, 900);
	add_prop(OBJ_I_VALUE, 40);
	break;

    case 1:
	set_short("large urn");
	add_adj("large");
	set_long("This enormous urn stands on a wide base. It is forged "+
	    "from dark grey clay, perfectly smooth and unmarked.\n");
	add_prop(CONT_I_WEIGHT, 20000);
	add_prop(CONT_I_VOLUME, 16000);
	add_prop(OBJ_I_VALUE, 150);
	break;
    }
}
